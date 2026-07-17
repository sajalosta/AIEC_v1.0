from app.s02_config import *  # noqa: F401,F403

VerdictValue = Literal["PASS", "FAIL"]
PhaseStatus  = Literal["pass", "fail"]


class BuildReport(BaseModel):  ##did the build work
    ok: bool          # the simulation binary exists after the build attempt
    log_tail: str     # compile-log tail: the evidence the orchestrator judges


class IngestReport(BaseModel):   ##did ingestion work
    ok: bool          # ingestion completed without error


class OrchestratorDecision(BaseModel):   ##the orchestrator's go/no-go after seeing build + ingest, with its reason.
    proceed: bool
    reason: str = Field(description="Judgment over the build and ingest tool results")
    build_log_tail: str = ""


class TestSpec(BaseModel):  ## testplan specifics of the test
    test_id: str            # e.g. T3
    name: str               # e.g. fill_sixteen
    feature: str = ""       # feature under test (F-catalog citation from the plan)
    stimulus: str           # stimulus text extracted from the test plan


class GenResult(BaseModel):  #one TestGenAgent's outcome: which test it built, for which feature, pass/fail, compile-log tail.
    test_name: str = ""     # full name, e.g. T3_fill_sixteen (from retrieval)
    feature: str = ""       # the feature this agent was asked to cover
    status: PhaseStatus
    gen_log_tail: str = ""
    error: str = ""


class GenPhaseReport(BaseModel): ##gen rollup: names ready to run; failures to the reporter.
    passed: list[str] = Field(default_factory=list,
                              description="full test names ready to run")
    failed: list[GenResult] = Field(default_factory=list)


class RunResult(BaseModel):   ##one RunAgent's outcome: which test it ran, pass/fail, log tail.
    test_name: str
    status: Literal["completed", "timeout", "crash", "not_run"]
    log_tail: str = ""
    error: str = ""


class RunPhaseReport(BaseModel):  ##run rollup: names with usable logs; failures to the reporter.
    done: list[str] = Field(default_factory=list,
                            description="full test names with usable logs")
    failed: list[RunResult] = Field(default_factory=list)


class RuleCitation(BaseModel):  ##one checker's outcome: which rule it checked, what the rule required vs what the log shows
    rule_id: str            # e.g. R4
    finding: str            # what the rule required vs what the log shows

class CheckVerdict(BaseModel):  ##one checker's outcome: which test it checked, pass/fail, reason.
    test_name: str
    verdict: VerdictValue
    reason: str = Field(
        default="",
        description="Required when verdict is FAIL: violated rule + log evidence",
    )
    citations: list[RuleCitation] = Field(default_factory=list)

class CheckRecord(BaseModel):  ##one checker's outcome: verdict plus its RAGAS tuple (stored separately).
    """One checker invocation: verdict plus its RAGAS tuple (stored separately)."""
    verdict: CheckVerdict
    retrieval_query: str = ""
    retrieved_rule_ids: list[str] = Field(default_factory=list)
    retrieved_chunks: list[str] = Field(default_factory=list)
    test_log: str = ""
    errors: list[str] = Field(default_factory=list)


class CheckPhaseReport(BaseModel): #check rollup: judged vs couldn't-judge.
    checked: list[str] = Field(default_factory=list,
                               description="test_names whose check completed")
    failed_to_check: list[str] = Field(default_factory=list)


class FinalReport(BaseModel): #the reporter's output: summary, results table, failure detail, trust notes.
    title: str
    summary: str
    results_table_markdown: str
    failures_detail_markdown: str = ""
    trust_notes: str = Field(default="", description="RAGAS-based trust commentary")


from typing import Annotated as _Annotated
from langgraph.graph.message import add_messages as _add_messages


class PipelineState(TypedDict, total=False):
    messages: _Annotated[list, _add_messages]   # chat frontend channel #the shared state each stage writes its report into.
    user_query: str                     # the features the user wants tested
    orchestrator: OrchestratorDecision
    build: BuildReport
    ingest: IngestReport
    gen_phase: GenPhaseReport
    run_phase: RunPhaseReport
    check_records: list[CheckRecord]
    ragas_summary: dict
    report: FinalReport
    errors: list[str]

print("Contracts defined.")
