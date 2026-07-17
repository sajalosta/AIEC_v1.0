from app.s07_gen import *  # noqa: F401,F403

@tool(
    "run_test",
    description=(
        "Run one previously generated test binary. Input: the full "
        "test_name (e.g. T3_fill_sixteen). Returns RunResult JSON with the "
        "log tail to judge."
    ),
)
def run_test(test_name: str) -> str:
    result = run_simulation(test_name.strip())
    return result.model_dump_json(indent=1)


TESTRUN_ROUTER_PROMPT = f"""
You are TestRunRouterLLM in an ASIC verification pipeline. Today is {TODAY}.

You receive the list of test_names that passed generation.
Work in waves: each model turn, emit min(remaining, {VER_PARALLEL_LIMIT})
run_test tool calls TOGETHER for parallel execution, until every test has
been run exactly once.

Pass/fail judgment belongs to the checking phase, never to you. Both
status=completed and status=timeout leave a log, so both stream to checking
(the checkers judge a timeout as a failed test).

Return RunPhaseReport: done = test_names whose run produced a log (completed
or timeout); failed = RunResults where nothing executed (crash, not_run),
verbatim for the reporter. One test failing to run never blocks the others.
"""

testrun_router = create_agent(
    model=llm,
    tools=[run_test],
    system_prompt=TESTRUN_ROUTER_PROMPT,
    middleware=[
        ModelCallLimitMiddleware(run_limit=ROUTER_MODEL_CALL_LIMIT,
                                 exit_behavior="end"),
        ToolCallLimitMiddleware(tool_name="run_test", run_limit=12,
                                exit_behavior="continue"),
    ],
    response_format=RunPhaseReport,
    name="testrun_router",
)
print("Test run router ready.")
