from app.s05_ingest import *  # noqa: F401,F403

@tool(
    "build_model",
    description=(
        "Compile the DUT with the testbench (sanity build). Returns a "
        "BuildReport JSON: ok flag and compile-log tail."
    ),
)
def build_model(reason: str = "sanity build") -> str:
    report = verilator_build("sanity")
    return report.model_dump_json(indent=1)


@tool(
    "ingest_documents",
    description=(
        "Parse the test-plan and rule-book PDFs into the two vector "
        "collections. Returns an IngestReport JSON."
    ),
)
def ingest_documents(reason: str = "ingest docs") -> str:
    return build_collections().model_dump_json(indent=1)


ORCHESTRATOR_PROMPT = f"""
You are the orchestrator of an ASIC verification pipeline. Today is {TODAY}.

Call BOTH tools in your first response, in the same turn, so they run in
parallel: build_model and ingest_documents.

Then judge the results:
- Read the build log tail the way a verification engineer reads a compile log.
  A build can be unusable even when ok=true (empty binary, fatal warnings).
- Read the ingest report. Missing tests or rules make checking impossible.

Return OrchestratorDecision. proceed=true only if both results are usable.
If the build failed, set proceed=false and put the build log tail in
build_log_tail with a plain-language reason: the pipeline must stop and the
user must see why. Do not invent log content. Test selection is NOT your
job; the feature request passes through to the test generation stage.
"""

orchestrator_agent = create_agent(
    model=llm,
    tools=[build_model, ingest_documents],
    system_prompt=ORCHESTRATOR_PROMPT,
    middleware=[
        ModelCallLimitMiddleware(run_limit=4, exit_behavior="end"),
        ToolCallLimitMiddleware(tool_name="build_model", run_limit=2,
                                exit_behavior="continue"),
        ToolCallLimitMiddleware(tool_name="ingest_documents", run_limit=2,
                                exit_behavior="continue"),
    ],
    response_format=OrchestratorDecision,
    name="orchestrator",
)
print("Orchestrator agent ready.")
