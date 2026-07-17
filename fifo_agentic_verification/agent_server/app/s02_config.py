from app.s01_imports import *  # noqa: F401,F403

if not os.environ.get("OPENAI_API_KEY"):
    raise RuntimeError("OPENAI_API_KEY missing - set it in agent_server/.env")

# Optional LangSmith tracing: per-run latency of every node, agent turn,
# tool call, and judge call at smith.langchain.com. Blank key = tracing off.
if os.environ.get("LANGSMITH_API_KEY"):
    os.environ.setdefault("LANGSMITH_TRACING", "true")
    os.environ.setdefault("LANGSMITH_PROJECT", "fifo-agentic-verification")

TODAY = date.today().isoformat()

CHAT_MODEL_NAME    = os.environ.get("VER_CHAT_MODEL", "gpt-5.4-mini")
CHECKER_MODEL_NAME = os.environ.get("VER_CHECKER_MODEL", "gpt-5.6-sol")
WRITER_MODEL_NAME  = os.environ.get("VER_WRITER_MODEL", CHAT_MODEL_NAME)
# Model assignment (project owner's): routers/orchestrator/reporter on the
# cheap tier; checker on the flagship; RAGAS judge on a DIFFERENT strong
# model so the judge does not share the checker's blind spots.
JUDGE_MODEL_NAME   = os.environ.get("VER_JUDGE_MODEL", "gpt-5.6-terra")

VER_PARALLEL_LIMIT        = int(os.environ.get("VER_PARALLEL_LIMIT", "4"))
ROUTER_MODEL_CALL_LIMIT   = int(os.environ.get("VER_ROUTER_MODEL_CALL_LIMIT", "8"))
CHECKER_MODEL_CALL_LIMIT  = int(os.environ.get("VER_CHECKER_MODEL_CALL_LIMIT", "6"))
RULE_RETRIEVAL_CALL_LIMIT = int(os.environ.get("VER_RULE_RETRIEVAL_CALL_LIMIT", "3"))

# package lives at <project>/agent_server/app/ - hw/ and docs/ sit at <project>/
PROJECT_DIR = Path(__file__).resolve().parents[2]
HW_DIR      = PROJECT_DIR / "hw"
DOCS_DIR    = PROJECT_DIR / "docs"
LOG_DIR     = PROJECT_DIR / "logs"
BUILD_DIR   = Path.home() / "fifo_build"
for d in (LOG_DIR, BUILD_DIR):
    d.mkdir(exist_ok=True)

TEST_PLAN_PDF = DOCS_DIR / "snix_fifo_test_plan.pdf"
RULE_BOOK_PDF = DOCS_DIR / "snix_fifo_rule_book.pdf"

# temperature 0: verdicts must be reproducible
llm         = ChatOpenAI(model=CHAT_MODEL_NAME, temperature=0)
checker_llm = ChatOpenAI(model=CHECKER_MODEL_NAME, temperature=0)
writer_llm  = ChatOpenAI(model=WRITER_MODEL_NAME, temperature=0)
judge_llm   = ChatOpenAI(model=JUDGE_MODEL_NAME, temperature=0)
embeddings  = OpenAIEmbeddings(model="text-embedding-3-small")

print(f"Date: {TODAY}")
print(f"Router/orchestrator model: {CHAT_MODEL_NAME}")
print(f"Checker model: {CHECKER_MODEL_NAME}")
print(f"RAGAS judge model (distinct): {JUDGE_MODEL_NAME}")
print(f"Parallel dispatch width: min(n, {VER_PARALLEL_LIMIT})")
print(f"Hardware kit present: {HW_DIR.exists()} | Docs present: {DOCS_DIR.exists()}")
