from app.s09_check import *  # noqa: F401,F403

# --- RAGAS scoring (per-row .ascore idiom; sync judge with async bridge) ----
# ragas 0.4.x still imports a Vertex-AI shim that langchain-community 1.x no
# longer ships; stub that one module so the import succeeds.
import sys as _sys, types as _types
if "langchain_community.chat_models.vertexai" not in _sys.modules:
    try:
        import langchain_community.chat_models.vertexai  # noqa: F401
    except ModuleNotFoundError:
        _stub = _types.ModuleType("langchain_community.chat_models.vertexai")
        _stub.ChatVertexAI = type("ChatVertexAI", (), {})
        _sys.modules["langchain_community.chat_models.vertexai"] = _stub

import asyncio
from concurrent.futures import ThreadPoolExecutor

import instructor
from openai import OpenAI
from ragas.llms import llm_factory
from ragas.metrics.collections import (
    ContextPrecision,
    ContextRecall,
    Faithfulness,
)

# Human-authored answer key: which rules apply to each test (from the rule book).
APPLICABLE_RULES: dict[str, list[str]] = {
    "T1": ["R1"],
    "T2": ["R2", "R6", "R7"],
    "T3": ["R4", "R3"],
    "T4": ["R8", "R4"],  # R2 is read-path; T4 does not read the FIFO
    "T5": ["R2", "R5", "R6", "R7"],
    "T6": ["R9", "R5"],
    "T7": ["R2", "R3"],
    "T8": ["R10", "R2", "R3"],
    "T9": ["R2", "R5", "R6"],
}

# Human-readable rule names (from the rule book) for reporting and references.
RULE_NAMES: dict[str, str] = {
    "R1": "Reset state",
    "R2": "FIFO ordering",
    "R3": "Conservation",
    "R4": "Full flag",
    "R5": "Empty flag",
    "R6": "Read latency",
    "R7": "Read data holding",
    "R8": "Blocked write",
    "R9": "Blocked read",
    "R10": "Simultaneous read and write",
    "R11": "Completion",
}


def format_rule(rule_id: str) -> str:
    return f"{rule_id} — {RULE_NAMES.get(rule_id, 'Unknown rule')}"


def build_sync_judge_llm():
    """Sync Gateway-free judge with an async-safe adapter (course session-6
    pattern): every real request is synchronous; only the Ragas coroutine
    boundary is bridged."""
    judge = llm_factory(
        JUDGE_MODEL_NAME,
        provider="openai",
        client=OpenAI(),
        mode=instructor.Mode.JSON,
    )
    # gpt-5.x rejects max_tokens; the current parameter is max_completion_tokens
    judge.model_args = {"max_completion_tokens": 4096, "max_retries": 3}

    async def agenerate_from_sync(prompt, response_model):
        return await asyncio.to_thread(
            judge.generate, prompt=prompt, response_model=response_model,
        )

    judge.agenerate = agenerate_from_sync
    return judge


def _run_coro_off_loop(async_function, *args):
    """Jupyter owns an event loop; run Ragas coroutines on a worker thread."""
    def invoke():
        return asyncio.run(async_function(*args))
    with ThreadPoolExecutor(max_workers=1) as executor:
        return executor.submit(invoke).result()


def _verdict_text(rec: CheckRecord) -> str:
    text = f"VERDICT: {rec.verdict.verdict}."
    if rec.verdict.reason:
        text += f" REASON: {rec.verdict.reason}"
    for c in rec.verdict.citations:
        text += f" [{c.rule_id}] {c.finding}"
    return text


def testgen_rows() -> list[dict]:
    """Scoring 1 — testgen retrieval: right test-plan chunk per feature query."""
    rows = []
    for test_name, rec in TESTGEN_RECORDS.items():
        chunk = rec["retrieved_contexts"][0] if rec["retrieved_contexts"] else ""
        fm = re.search(r"Feature under test:\s*(.+?)(?:Description:|$)", chunk, re.DOTALL)
        reference = f"The test plan covers this feature with {test_name}."
        if fm:
            reference += " Feature under test: " + " ".join(fm.group(1).split())
        rows.append({"test_id": test_name,
                     "user_input": rec["user_input"],
                     "retrieved_contexts": list(rec["retrieved_contexts"]),
                     "response": rec["response"],
                     "reference": reference})
    return rows


def rules_rows(records: list[CheckRecord]) -> list[dict]:
    """Scoring 2 — rules retrieval: right rules fetched for each judgment."""
    rows = []
    for rec in records:
        tname = rec.verdict.test_name
        gold_rule_ids = APPLICABLE_RULES.get(tname.split("_")[0], [])
        retrieved_rule_ids = rec.retrieved_rule_ids or []
        rows.append({
            "test_id": tname,
            "user_input": rec.retrieval_query or f"rules applicable to test {tname}",
            "retrieved_contexts": rec.retrieved_chunks or ["(no retrieval)"],
            "response": "Retrieved rules: " + ", ".join(retrieved_rule_ids or ["none"]),
            # One statement per gold rule, phrased as a claim about the
            # retrieved text so attribution is decidable from the chunks:
            # the rule book has no test-to-rule mapping to judge against.
            "reference": " ".join(
                f"The retrieved rule book sections include {format_rule(r)}."
                for r in gold_rule_ids
            ) or "No applicable rules.",
            "gold_rules": [format_rule(rule_id) for rule_id in gold_rule_ids],
            "retrieved_rules": [format_rule(rule_id) for rule_id in retrieved_rule_ids],
        })
    return rows


def verdict_rows(records: list[CheckRecord]) -> list[dict]:
    """Scoring 3 — verdicts: grounded in the retrieved rules + the log."""
    rows = []
    for rec in records:
        tname = rec.verdict.test_name
        rows.append({
            "test_id": tname,
            "user_input": rec.retrieval_query or f"rules applicable to test {tname}",
            "retrieved_contexts": (rec.retrieved_chunks or ["(no retrieval)"])
                                  + [rec.test_log],
            "response": _verdict_text(rec),
            "reference": "Applicable rules: "
                         + ", ".join(APPLICABLE_RULES.get(tname.split("_")[0], [])),
        })
    return rows


async def _score_all(records: list[CheckRecord]) -> dict:
    judge = build_sync_judge_llm()
    cp = ContextPrecision(llm=judge)
    cr = ContextRecall(llm=judge)
    fa = Faithfulness(llm=judge)

    async def safe(coro):
        try:
            return round((await coro).value, 4)
        except Exception as exc:
            return f"error: {type(exc).__name__}"

    summary: dict = {}

    async def score_table(name, rows, scorers):
        if not rows:
            summary[name] = {"skipped": "no records"}
            return
        per_test = []
        for row in rows:
            entry = {"test_id": row["test_id"]}
            for metric_name, coro_fn in scorers:
                entry[metric_name] = await safe(coro_fn(row))
            if name == "rules_retrieval":
                entry["gold_rules"] = row["gold_rules"]
                entry["retrieved_rules"] = row["retrieved_rules"]
            per_test.append(entry)
        table = {"per_test": per_test}
        for metric_name, _ in scorers:
            vals = [e[metric_name] for e in per_test if isinstance(e[metric_name], float)]
            if vals:
                table[f"{metric_name}_mean"] = round(sum(vals) / len(vals), 4)
        summary[name] = table

    # Testgen: recall only (k=1 — precision is redundant).
    testgen_scorers = [
        ("context_recall", lambda r: cr.ascore(
            user_input=r["user_input"], retrieved_contexts=r["retrieved_contexts"],
            reference=r["reference"])),
    ]
    rules_scorers = [
        ("context_precision", lambda r: cp.ascore(
            user_input=r["user_input"], reference=r["reference"],
            retrieved_contexts=r["retrieved_contexts"])),
        ("context_recall", lambda r: cr.ascore(
            user_input=r["user_input"], retrieved_contexts=r["retrieved_contexts"],
            reference=r["reference"])),
    ]
    verdict_scorers = [
        ("faithfulness", lambda r: fa.ascore(
            user_input=r["user_input"], response=r["response"],
            retrieved_contexts=r["retrieved_contexts"])),
    ]

    await score_table("testgen_retrieval", testgen_rows(), testgen_scorers)
    await score_table("rules_retrieval", rules_rows(records), rules_scorers)
    await score_table("verdicts", verdict_rows(records), verdict_scorers)

    # reporter contract unchanged: verdict trust scores also at top level
    summary.update({k: v for k, v in summary.get("verdicts", {}).items()})
    return summary


RULES_RECALL_LOG = PROJECT_DIR / "rules_context_recall.jsonl"


def record_rules_recall(summary: dict) -> Path | None:
    """Append this run's rules gold/retrieved/recall to rules_context_recall.jsonl."""
    table = summary.get("rules_retrieval") or {}
    if "per_test" not in table:
        return None
    from datetime import datetime, timezone
    rows = []
    for r in table["per_test"]:
        gold = list(r.get("gold_rules") or [])
        retrieved = list(r.get("retrieved_rules") or [])
        gold_set, ret_set = set(gold), set(retrieved)
        rows.append({
            "test_id": r["test_id"],
            "gold_rules": gold,
            "retrieved_rules": retrieved,
            "missing_rules": [g for g in gold if g not in ret_set],
            "extra_rules": [x for x in retrieved if x not in gold_set],
            "context_recall": r.get("context_recall"),
            "context_precision": r.get("context_precision"),
        })
    entry = {
        "ts": datetime.now(timezone.utc).isoformat(),
        "per_test": rows,
        "context_recall_mean": table.get("context_recall_mean"),
        "context_precision_mean": table.get("context_precision_mean"),
    }
    with RULES_RECALL_LOG.open("a", encoding="utf-8") as f:
        f.write(json.dumps(entry) + "\n")
    print(f"rules recall log -> {RULES_RECALL_LOG}")
    return RULES_RECALL_LOG


def run_ragas(records: list[CheckRecord]) -> dict:
    """One RAGAS stage, three scorings. Returns a summary dict; never raises."""
    try:
        summary = _run_coro_off_loop(_score_all, records)
        for name in ("testgen_retrieval", "rules_retrieval", "verdicts"):
            print(f"--- {name} ---")
            print(json.dumps(summary.get(name, {}), indent=1))
        record_rules_recall(summary)
        return summary
    except Exception as exc:
        return {"error": f"RAGAS did not complete: {type(exc).__name__}: {exc}"}

print("RAGAS stage ready (per-row ascore; sync judge; vertexai stub).")
