from app.s10_ragas import *  # noqa: F401,F403

REPORTER_PROMPT = f"""
You are the reporter of an ASIC verification pipeline. Today is {TODAY}.

You receive: check verdicts (with reasons and rule citations), generation
failures, run failures, and RAGAS trust scores per verdict.

Produce FinalReport:
- results_table_markdown: one row per requested test with columns
  Test | Outcome | Reason / notes | Testgen precision | Rules precision | Rules recall | Faithfulness.
  Outcome is PASS, FAIL, GEN-FAIL, or RUN-FAIL. PASS and FAIL come verbatim
  from the checker verdicts — you never judge a test yourself (a timed-out
  test arrives already judged: the checker's FAIL with a TIMEOUT reason).
  GEN-FAIL / RUN-FAIL are only for tests that never produced a log.
  PASS rows need no prose.
- failures_detail_markdown: for each FAIL, the violated rule, the log
  evidence, and the checker's reasoning; for GEN/RUN failures, the log tail.
- trust_notes: flag any verdict whose faithfulness or recall is low; the
  reader should know which verdicts to double-check by hand.
- Do not invent tests, rules, scores, or log content.
"""

reporter_agent = create_agent(
    model=writer_llm,
    tools=[],
    system_prompt=REPORTER_PROMPT,
    response_format=FinalReport,
    name="reporter",
)


def fallback_report(state: "PipelineState") -> FinalReport:
    lines = ["| Test | Outcome | Notes |", "|---|---|---|"]
    for rec in state.get("check_records", []):
        v = rec.verdict
        lines.append(f"| {v.test_name} | {v.verdict} | {v.reason or ''} |")
    for g in state.get("gen_phase", GenPhaseReport()).failed:
        lines.append(f"| {g.test_name or g.feature} | GEN-FAIL | {g.error or g.gen_log_tail[:120]} |")
    for r in state.get("run_phase", RunPhaseReport()).failed:
        lines.append(f"| {r.test_name} | RUN-FAIL | {r.error or r.status} |")
    return FinalReport(
        title="FIFO regression report (deterministic fallback)",
        summary="Reporter LLM unavailable; table assembled by code.",
        results_table_markdown="\n".join(lines),
    )
