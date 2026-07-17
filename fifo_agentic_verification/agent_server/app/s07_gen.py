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

You receive ONE feature to test. Work in exactly this order:
1. Call retrieve_test with the feature. It returns the matching test_name
   from the test plan.
2. When the retrieval result arrives, call gen_test with that exact
   test_name.
3. When the build report arrives, return GenResult: the test_name, the
   feature, status pass if the build was ok (usable binary), fail otherwise,
   and the gen log tail. Never invent test names or log content.
"""

testgen_agent = create_agent(
    model=llm,
    tools=[retrieve_test, gen_test],
    system_prompt=TESTGEN_AGENT_PROMPT,
    middleware=[
        ModelCallLimitMiddleware(run_limit=5, exit_behavior="end"),
        ToolCallLimitMiddleware(tool_name="retrieve_test", run_limit=2,
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
        "Delegate ONE feature to a TestGenAgent, which retrieves the matching "
        "test and generates (compiles) it. Input: the feature to test, in "
        "natural language. Returns the agent's GenResult JSON."
    ),
)
async def run_testgen_agent(feature: str) -> str:
    try:
        result = await testgen_agent.ainvoke(
            {"messages": [{"role": "user",
                           "content": f"Feature to test: {feature}"}]}
        )
        gen = GenResult.model_validate(result["structured_response"])
        if not gen.feature:
            gen = gen.model_copy(update={"feature": feature})
        return gen.model_dump_json(indent=1)
    except Exception as exc:
        return GenResult(feature=feature, status="fail",
                         error=f"{type(exc).__name__}: {exc}"
                         ).model_dump_json(indent=1)


TESTGEN_ROUTER_PROMPT = f"""
You are TestGenRouterLLM in an ASIC verification pipeline. Today is {TODAY}.

You receive the user's request naming the features to test. Determine how
many tests are needed: one TestGenAgent call per distinct feature. A request
for everything ("all features", "full regression") means one call per
feature in the request context.

Work in waves: each model turn, emit min(remaining, {VER_PARALLEL_LIMIT})
run_testgen_agent tool calls TOGETHER so they execute in parallel, one
feature per call, until every feature has been attempted exactly once.

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
