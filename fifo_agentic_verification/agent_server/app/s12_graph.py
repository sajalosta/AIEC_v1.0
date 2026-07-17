from app.s11_report import *  # noqa: F401,F403

def _query_from_state(state: PipelineState) -> str:
    uq = (state.get("user_query") or "").strip()
    if uq:
        return uq
    msgs = state.get("messages") or []
    if msgs:
        last = msgs[-1]
        content = last.get("content") if isinstance(last, dict) else getattr(last, "content", "")
        return str(content or "").strip()
    return ""


def _report_markdown(rep: FinalReport) -> str:
    return "\n\n".join(filter(None, [
        f"# {getattr(rep, 'title', 'FIFO Regression Report')}",
        rep.summary,
        rep.results_table_markdown,
        rep.failures_detail_markdown,
        f"**Trust notes:** {rep.trust_notes}" if rep.trust_notes else "",
    ]))


async def orchestrate_node(state: PipelineState, config: RunnableConfig) -> dict:
    result = await orchestrator_agent.ainvoke(
        {"messages": [{"role": "user", "content":
            "Prepare the pipeline: build the model and ingest the documents, "
            "in parallel, then judge whether to proceed."}]},
        config=config,
    )
    decision = OrchestratorDecision.model_validate(result["structured_response"])

    return {"orchestrator": decision, "user_query": _query_from_state(state)}


def route_after_orchestrate(state: PipelineState) -> Literal["generate", "report"]:
    return "generate" if state["orchestrator"].proceed else "report"


async def generate_node(state: PipelineState, config: RunnableConfig) -> dict:
    request = (state.get("user_query") or "").strip() or "all features"
    try:
        result = await testgen_router.ainvoke(
            {"messages": [{"role": "user", "content":
                f"Features the user wants tested:\n{request}"}]},
            config=config,
        )
        report = GenPhaseReport.model_validate(result["structured_response"])
        return {"gen_phase": report}
    except Exception as exc:
        return {"gen_phase": GenPhaseReport(
                    failed=[GenResult(feature=request, status="fail",
                                      error=f"router: {exc}")]),
                "errors": state.get("errors", []) + [f"gen: {exc}"]}


async def run_node(state: PipelineState, config: RunnableConfig) -> dict:
    todo = state["gen_phase"].passed
    if not todo:
        return {"run_phase": RunPhaseReport()}
    try:
        result = await testrun_router.ainvoke(
            {"messages": [{"role": "user", "content":
                f"Run these tests:\n{json.dumps(todo, indent=1)}"}]},
            config=config,
        )
        report = RunPhaseReport.model_validate(result["structured_response"])
        return {"run_phase": report}
    except Exception as exc:
        return {"run_phase": RunPhaseReport(
                    failed=[RunResult(test_name=t, status="not_run",
                                      error=f"router: {exc}") for t in todo]),
                "errors": state.get("errors", []) + [f"run: {exc}"]}


async def check_node(state: PipelineState, config: RunnableConfig) -> dict:
    done = state["run_phase"].done
    if not done:
        return {"check_records": []}
    CHECK_RECORDS.clear()
    errors = list(state.get("errors", []))
    try:
        result = await testcheck_router.ainvoke(
            {"messages": [{"role": "user", "content":
                "Check these completed tests:\n" + json.dumps(done, indent=1)}]},
            config=config,
        )
        phase = CheckPhaseReport.model_validate(result["structured_response"])
        missing = [t for t in done if t not in CHECK_RECORDS]
        if missing:
            errors.append(f"router never dispatched checks for: {missing}")
    except Exception as exc:
        errors.append(f"check router: {type(exc).__name__}: {exc}")
        # fallback: check directly so verdicts are never lost
        for t in done:
            if t not in CHECK_RECORDS:
                CHECK_RECORDS[t] = await run_checker(t)
    records = [CHECK_RECORDS[t] for t in done if t in CHECK_RECORDS]
    return {"check_records": records, "errors": errors}


def ragas_node(state: PipelineState) -> dict:
    return {"ragas_summary": run_ragas(state.get("check_records", []))}


async def report_node(state: PipelineState, config: RunnableConfig) -> dict:
    if not state["orchestrator"].proceed:
        # stop-and-surface path: user must see why nothing ran
        report = FinalReport(
            title="Pipeline aborted before testing",
            summary=state["orchestrator"].reason,
            results_table_markdown="(no tests were generated or run)",
            failures_detail_markdown="```\n"
                + state["orchestrator"].build_log_tail + "\n```",
        )
        return {"report": report,
                "messages": [{"role": "assistant", "content": _report_markdown(report)}]}
    payload = {
        "verdicts": [r.verdict.model_dump() for r in state.get("check_records", [])],
        "gen_failures": state["gen_phase"].model_dump()["failed"],
        "run_failures": state["run_phase"].model_dump()["failed"],
        "ragas": state.get("ragas_summary", {}),
    }
    try:
        result = await reporter_agent.ainvoke(
            {"messages": [{"role": "user",
                           "content": json.dumps(payload, indent=1)}]},
            config=config,
        )
        rep = FinalReport.model_validate(result["structured_response"])
        return {"report": rep,
                "messages": [{"role": "assistant", "content": _report_markdown(rep)}]}
    except Exception as exc:
        rep = fallback_report(state)
        return {"report": rep,
                "messages": [{"role": "assistant", "content": _report_markdown(rep)}],
                "errors": state.get("errors", []) + [f"report: {exc}"]}


builder = StateGraph(PipelineState)
builder.add_node("orchestrate", orchestrate_node)
builder.add_node("generate", generate_node)
builder.add_node("run", run_node)
builder.add_node("check", check_node)
builder.add_node("ragas", ragas_node)
builder.add_node("report", report_node)

builder.add_edge(START, "orchestrate")
builder.add_conditional_edges("orchestrate", route_after_orchestrate,
                              {"generate": "generate", "report": "report"})
builder.add_edge("generate", "run")
builder.add_edge("run", "check")
builder.add_edge("check", "ragas")
builder.add_edge("ragas", "report")
builder.add_edge("report", END)

# the server provides persistence; no local checkpointer
verification_graph = builder.compile()
graph = verification_graph
print("Compiled verification_graph.")
