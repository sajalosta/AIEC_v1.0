from app.s10_ragas import *  # noqa: F401,F403

REPORTER_PROMPT = f"""
You are the reporter of an ASIC verification pipeline. Today is {TODAY}.

You receive: check verdicts (with reasons and rule citations), generation
failures, run failures, and RAGAS trust scores per verdict.

Produce FinalReport:
- results_table_markdown: a GitHub-flavored markdown table, one row per
  requested test, with EXACTLY these short headers (keep them short for UI):
  | Test | Outcome | Notes | Test recall | Rules P | Rules R | Faith |
  Map scores as: Test recall = context recall (testgen_retrieval);
  Rules P = context precision (rules_retrieval);
  Rules R = context recall (rules_retrieval);
  Faith = faithfulness (verdicts). Never reuse one table's score in another
  column; write n/a when that table has no row for the test.
  Keep Notes to one short sentence. Round scores to 2 decimals.
  Outcome for a checked test is decided ONLY from the numeric RAGAS metrics
  present for that test (ignore n/a). The four metrics are Test recall,
  Rules P, Rules R, and Faith.
    * PASS   — every available metric is >= 0.8
    * REVIEW — no metric is < 0.66, but at least one is in [0.66, 0.8)
    * FAIL   — any available metric is < 0.66
  Also use FAIL if the checker verdict is FAIL (including TIMEOUT), even when
  metrics are high. Put the checker PASS/FAIL and key reason in Notes.
  GEN-FAIL / RUN-FAIL are only for tests that never produced a log (no metrics).
  PASS rows need no prose beyond a short checker note if useful.
- failures_detail_markdown: for each FAIL or REVIEW, the violated rule (if
  any), the log evidence, the checker's reasoning, and which metric(s)
  triggered REVIEW/FAIL; for GEN/RUN failures, the log tail.
- trust_notes: list REVIEW and FAIL rows with the metric that caused the
  band; remind the reader to hand-check REVIEW cases.
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
    lines = [
        "| Test | Outcome | Notes | Test recall | Rules P | Rules R | Faith |",
        "|---|---|---|---:|---:|---:|---:|",
    ]
    for rec in state.get("check_records", []):
        v = rec.verdict
        note = (v.reason or "").replace("|", "/").replace("\n", " ")[:120]
        lines.append(
            f"| {v.test_name} | {v.verdict} | {note} | n/a | n/a | n/a | n/a |"
        )
    for g in state.get("gen_phase", GenPhaseReport()).failed:
        note = (g.error or g.gen_log_tail[:120]).replace("|", "/").replace("\n", " ")
        lines.append(
            f"| {g.test_name or g.feature} | GEN-FAIL | {note} | n/a | n/a | n/a | n/a |"
        )
    for r in state.get("run_phase", RunPhaseReport()).failed:
        note = (r.error or r.status or "").replace("|", "/").replace("\n", " ")
        lines.append(
            f"| {r.test_name} | RUN-FAIL | {note} | n/a | n/a | n/a | n/a |"
        )
    return FinalReport(
        title="FIFO regression report (deterministic fallback)",
        summary="Reporter LLM unavailable; table assembled by code.",
        results_table_markdown="\n".join(lines),
    )
