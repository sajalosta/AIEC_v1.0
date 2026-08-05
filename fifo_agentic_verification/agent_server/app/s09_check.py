from app.s08_run import *  # noqa: F401,F403
from app.s05_ingest import debug_fmt_hits  # explicit: star-import omits _-prefixed names

CHECKER_PROMPT = f"""
You are a hardware verification checker. Today is {TODAY}.

INPUT: one test's event log from a FIFO simulation (produced by a passive
monitor: pin/flag change events with cycle timestamps, plus [TST] status
lines), together with the rule-book sections retrieved for the feature(s)
this test covers. You have no tools: judge only from what is given.

METHOD:
1. Read the log. Reconstruct what the stimulus did (accepted writes, accepted
   reads, blocked attempts, flag transitions) and the running occupancy.
2. Derive what the provided rules require given the observed stimulus, then
   judge the observed behavior against each applicable rule.

HARD RULES:
- Judge ONLY from the provided rule text and the log. No outside knowledge
  of FIFOs. If the rules and the log disagree with your intuition, they win.
- Events are logged at the first cycle the new value is observable (one
  cycle after the causing clock edge). Do not flag this sampling skew.
- The test FAILS if any applicable provided rule is violated.
- A log showing status=timeout, or lacking a status=completed line, is a
  FAILED test: verdict FAIL and the reason must start with TIMEOUT.
- If no provided rule covers an observed behavior, do not guess and do not
  invent rules: judge the rules you have and note the gap in the reason.
- Every citation must name a rule_id from the provided rules and quote the
  log evidence you used. Do not invent rules, values, or log lines.

Return CheckVerdict: verdict PASS or FAIL; when FAIL, reason must state the
violated rule and the exact log evidence.
"""

checker_agent = create_agent(
    model=checker_llm,
    tools=[],   # rules arrive with the log — retrieved per feature under test
    system_prompt=CHECKER_PROMPT,
    middleware=[
        ModelCallLimitMiddleware(run_limit=CHECKER_MODEL_CALL_LIMIT,
                                 exit_behavior="end"),
    ],
    response_format=CheckVerdict,
    name="rule_checker",
)


def sanitize_verdict(verdict: CheckVerdict,
                     retrieved_ids: list[str]) -> tuple[CheckVerdict, list[str]]:
    """Citation-provenance guard: cited rules must have been retrieved."""
    errors: list[str] = []
    kept = [c for c in verdict.citations if c.rule_id in retrieved_ids]
    dropped = [c.rule_id for c in verdict.citations if c.rule_id not in retrieved_ids]
    if dropped:
        errors.append(f"Citations dropped (never retrieved): {dropped}")
    if verdict.verdict == "FAIL" and not verdict.reason:
        errors.append("FAIL verdict without a reason.")
    return verdict.model_copy(update={"citations": kept}), errors


FEATURE_SPLIT = re.compile(r"(?=\bF\d+\s*[—-])")
RULES_PER_FEATURE = 6         # RRF keeps top 6 per feature (dense 3 + BM25 3 fused)
RULES_RERANK_PER_FEATURE = 2  # cross-encoder keeps top 2 (same slot count as MMR)
RULES_MMR_PER_FEATURE = 2     # kept for MMR restore
MAX_RULES = 6                 # cap after merging 2-per-feature across features


def split_features(feature_line: str) -> list[str]:
    """A test's feature line can name several features (T2 covers F2 and F3)."""
    parts = [p.strip() for p in FEATURE_SPLIT.split(feature_line) if p.strip()]
    return parts or [feature_line]


def rules_for_features(feature_line: str) -> list[dict]:
    """Per feature: hybrid RRF → cross-encoder rerank → merge/dedupe → cap."""
    seen: set[str] = set()
    merged: list[dict] = []
    # --- DEBUG_RULES_RETRIEVAL (temporary) ---
    if DEBUG_RULES_RETRIEVAL:
        print(f"\n=== rules_for_features ===\nfeature_line: {feature_line[:200]}")
    # -----------------------------------------
    for feature in split_features(feature_line):
        dense = dense_retrieve_rules(feature, k=FIRST_STAGE_K_RULES)
        bm25 = bm25_retrieve_rules(feature, k=FIRST_STAGE_K_RULES)
        rrf = reciprocal_rank_fusion([dense, bm25], limit=RULES_PER_FEATURE)
        cands = [{"rule_id": d.metadata.get("rule_id", "?"), "text": d.text,
                  "score": d.score} for d in rrf]
        # --- DEBUG_RULES_RETRIEVAL (temporary) ---
        if DEBUG_RULES_RETRIEVAL:
            print(f"\n--- feature ---\n{feature[:180]}")
            print(f"Dense top {FIRST_STAGE_K_RULES}: {debug_fmt_hits(dense)}")
            print(f"BM25  top {FIRST_STAGE_K_RULES}: {debug_fmt_hits(bm25)}")
            print(f"RRF   top {RULES_PER_FEATURE}: {debug_fmt_hits(rrf)}")
        # -----------------------------------------
        if USE_RULES_RERANK:
            cands = rerank_select_rules(feature, cands, RULES_RERANK_PER_FEATURE)
            stage_name, stage_k = "Rerank", RULES_RERANK_PER_FEATURE
        elif USE_RULES_MMR:
            cands = mmr_select_rules(feature, cands, RULES_MMR_PER_FEATURE)
            stage_name, stage_k = "MMR", RULES_MMR_PER_FEATURE
        else:
            cands = cands[:RULES_RERANK_PER_FEATURE]
            stage_name, stage_k = "Top", RULES_RERANK_PER_FEATURE
        # --- DEBUG_RULES_RETRIEVAL (temporary) ---
        if DEBUG_RULES_RETRIEVAL:
            print(f"{stage_name} top {stage_k}: {debug_fmt_hits(cands)}")
        # -----------------------------------------
        for rule in cands:
            rule_id = rule.get("rule_id")
            if rule_id in seen:
                continue
            seen.add(rule_id)
            merged.append(rule)
    out = merged[:MAX_RULES]
    # --- DEBUG_RULES_RETRIEVAL (temporary) ---
    if DEBUG_RULES_RETRIEVAL:
        print(f"\nMerged final (cap {MAX_RULES}): {debug_fmt_hits(out)}\n")
    # -----------------------------------------
    return out


def test_feature(test_name: str) -> str:
    """The feature this test covers, captured when testgen retrieved the test.
    Falls back to the test name itself at the gates (no testgen ran)."""
    return TESTGEN_RECORDS.get(test_name, {}).get("feature") or test_name


async def run_checker(test_name: str) -> CheckRecord:
    test_name = sanitize_name(test_name)
    log_path = LOG_DIR / f"{test_name}.log"
    if not log_path.exists():
        return CheckRecord(
            verdict=CheckVerdict(test_name=test_name, verdict="FAIL",
                                 reason="No log file was produced for this test."),
            errors=["missing log file"],
        )
    log_text = log_path.read_text()
    # one retrieval per feature named in the test's feature line
    feature = test_feature(test_name)
    rules = rules_for_features(feature)
    rules_block = ("\n\nRule-book sections retrieved for the feature under test:\n"
                   + json.dumps(rules, indent=1))
    try:
        result = await checker_agent.ainvoke(
            {"messages": [{"role": "user", "content": (
                f"Test: {test_name}\nFeature under test: {feature}"
                f"{rules_block}\n\nEvent log:\n{log_text}"
            )}]}
        )
        verdict = CheckVerdict.model_validate(result["structured_response"])
        verdict = verdict.model_copy(update={"test_name": test_name})
        rule_ids = [r.get("rule_id", "?") for r in rules]
        chunks = [f"[{r.get('rule_id', '?')}] {r.get('text', '')}" for r in rules]
        verdict, errors = sanitize_verdict(verdict, rule_ids)
        return CheckRecord(verdict=verdict, retrieval_query=feature,
                           retrieved_rule_ids=rule_ids,
                           retrieved_chunks=chunks, test_log=log_text,
                           errors=errors)
    except Exception as exc:
        return CheckRecord(
            verdict=CheckVerdict(test_name=test_name, verdict="FAIL",
                                 reason=f"Checker did not complete: {exc}"),
            test_log=log_text,
            errors=[f"{type(exc).__name__}: {exc}"],
        )

print("Checker agent + provenance sanitizer ready.")


# side channels: full CheckRecords are too large to route through the router
# LLM's context; the compact verdict JSON goes to the router, the full record
# (log, chunks, tuple for RAGAS) is stored here, keyed by test_name.
CHECK_RECORDS: dict[str, CheckRecord] = {}


@tool(
    "run_check_agent",
    description=(
        "Delegate ONE completed test to a CheckerAgent, which retrieves the "
        "applicable rules and judges the test's event log. Input: the full "
        "test_name (e.g. T3_fill_sixteen). Returns the compact verdict JSON."
    ),
)
async def run_check_agent(test_name: str) -> str:
    record = await run_checker(test_name.strip())
    CHECK_RECORDS[record.verdict.test_name] = record
    return record.verdict.model_dump_json(indent=1)


TESTCHECK_ROUTER_PROMPT = f"""
You are TestCheckRouterLLM in an ASIC verification pipeline. Today is {TODAY}.

You receive the list of test_names whose simulations completed. Every one of
them must be checked exactly once. Work in waves: each model turn, emit
min(remaining, {VER_PARALLEL_LIMIT}) run_check_agent tool calls TOGETHER so
they execute in parallel, one test per call, and keep invoking further waves
until no tests remain.

Each call returns that checker's verdict. Do not re-judge or alter verdicts:
the checker is the authority on pass/fail. Your job is dispatch and
collection. Return CheckPhaseReport: checked = test_names whose check
completed (returned any verdict); failed_to_check = test_names whose check
call errored and returned no verdict.
"""

testcheck_router = create_agent(
    model=llm,
    tools=[run_check_agent],
    system_prompt=TESTCHECK_ROUTER_PROMPT,
    middleware=[
        ModelCallLimitMiddleware(run_limit=ROUTER_MODEL_CALL_LIMIT,
                                 exit_behavior="end"),
        ToolCallLimitMiddleware(tool_name="run_check_agent", run_limit=12,
                                exit_behavior="continue"),
    ],
    response_format=CheckPhaseReport,
    name="testcheck_router",
)
print("TestCheckRouterLLM ready.")
