from app.s06_orch import *  # noqa: F401,F403

@tool(
    "gen_test",
    description=(
        "Generate one test: a one-line Verilator compile of the testbench for "
        "the given test_name (e.g. T3_fill_sixteen). Returns the compile "
        "report; its log tail is the gen log."
    ),
)
def gen_test(test_name: str) -> str:
    report = verilator_build(test_name.strip())
    return report.model_dump_json(indent=1)


TESTGEN_AGENT_PROMPT = f"""
You are a TestGenAgent in an ASIC verification pipeline. Today is {TODAY}.

You receive ONE test name. Work in exactly this order:
1. Call retrieve_test_by_name with that name. It returns the full test_name
   and the feature line the test covers.
2. When the lookup result arrives, call gen_test with that exact test_name.
3. When the build report arrives, return GenResult: the test_name, the
   feature line from the lookup, status pass if the build was ok (usable
   binary), fail otherwise, and the gen log tail. Never invent test names,
   features, or log content. If the lookup returns nothing, the test name is
   not in the plan: return status fail and say so.
"""

testgen_agent = create_agent(
    model=llm,
    tools=[retrieve_test_by_name, gen_test],
    system_prompt=TESTGEN_AGENT_PROMPT,
    middleware=[
        ModelCallLimitMiddleware(run_limit=5, exit_behavior="end"),
        ToolCallLimitMiddleware(tool_name="retrieve_test_by_name", run_limit=2,
                                exit_behavior="continue"),
        ToolCallLimitMiddleware(tool_name="gen_test", run_limit=2,
                                exit_behavior="continue"),
    ],
    response_format=GenResult,
    name="testgen_agent",
)


@tool(
    "run_testgen_agent",
    description=(
        "Delegate ONE test name to a TestGenAgent, which looks the test up in "
        "the plan and generates (compiles) it. Input: the test name (T3, "
        "fill_sixteen or T3_fill_sixteen). Returns the agent's GenResult JSON."
    ),
)
async def run_testgen_agent(test_name: str) -> str:
    try:
        result = await testgen_agent.ainvoke(
            {"messages": [{"role": "user",
                           "content": f"Test to generate: {test_name}"}]}
        )
        gen = GenResult.model_validate(result["structured_response"])
        if not gen.feature:   # feature comes from the plan, not the caller
            gen = gen.model_copy(update={
                "feature": TESTGEN_RECORDS.get(gen.test_name, {}).get("feature", "")})
        return gen.model_dump_json(indent=1)
    except Exception as exc:
        return GenResult(test_name=test_name, status="fail",
                         error=f"{type(exc).__name__}: {exc}"
                         ).model_dump_json(indent=1)


TESTGEN_ROUTER_PROMPT = f"""
You are TestGenRouterLLM in an ASIC verification pipeline. Today is {TODAY}.

You receive the user's request naming the tests to run, by test name (T3,
fill_sixteen, T3_fill_sixteen). One TestGenAgent call per distinct test
name. A request for everything ("all tests", "full regression") means one
call per test in the request context.

Work in waves: each model turn, emit min(remaining, {VER_PARALLEL_LIMIT})
run_testgen_agent tool calls TOGETHER so they execute in parallel, one test
name per call, until every test has been attempted exactly once.

Judge each GenResult like a verification engineer reading a compile log:
status pass with a clean build means the test generated; anything else
failed. Return GenPhaseReport: passed = the full test_names that generated
(they move to the run stage); failed = failed GenResults verbatim (they go
to the reporter). One failure never blocks the rest.
"""

testgen_router = create_agent(
    model=llm,
    tools=[run_testgen_agent],
    system_prompt=TESTGEN_ROUTER_PROMPT,
    middleware=[
        ModelCallLimitMiddleware(run_limit=ROUTER_MODEL_CALL_LIMIT,
                                 exit_behavior="end"),
        ToolCallLimitMiddleware(tool_name="run_testgen_agent", run_limit=12,
                                exit_behavior="continue"),
    ],
    response_format=GenPhaseReport,
    name="testgen_router",
)
print("TestGenAgent + TestGenRouterLLM ready.")
