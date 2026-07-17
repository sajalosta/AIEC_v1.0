# FIFO Agentic Verification — Pilot

AI-driven verification of `snix_sync_fifo`: LLM routers dispatch test generation and
test runs as parallel tool calls, checker agents judge monitor event logs against a
retrieved rule book (RAG inside the checker), RAGAS scores every verdict's retrieval
and faithfulness, and a reporter compiles the final report.

## Contents
- `fifo_agentic_verification.ipynb` — the whole pipeline (LangChain + LangGraph)
- `hw/` — DUT (`snix_sync_fifo.sv`), plusarg testbench `tb_top.sv` (holds the 9
  pre-decided test sequences, selected by +TEST=<name>), passive event monitor
  (`fifo_event_monitor.sv`)
- `docs/` — test plan (features F1–F10 + tests T1–T9) and rule book R1–R11
- `logs/`, `build/`, `chroma_store/` — created/filled by the pipeline

## Prerequisites
- Python 3.10+ with: `pip install langchain langgraph langchain-openai
  pdfplumber ragas datasets nbformat jupyter langchain-qdrant qdrant-client rank_bm25`
- Verilator 5.x on PATH (`pip install verilator` gives `verilator-cli`, which the
  notebook auto-detects; if the binary link step fails, the notebook retries with
  `make CXX="c++ -fcoroutines"`)
- An OpenAI API key (prompted on first run). Optional: LANGSMITH_API_KEY for tracing.

## Run
Open the notebook, run cells top to bottom. The final cells run the full regression
(all 9 tests) and render the report. To run a subset: `await run_verification(["T3"])`.

## Architecture (as specified by the project owner)
- The USER names the features to test (they own the test plan). The orchestrator
  (AGENT1) builds ∥ ingests — ingest ingests only — and routes the request onward.
- **TestGenRouterLLM** determines how many tests are needed and calls that many
  **TestGenAgents** in min(n, 4) waves. Each TestGenAgent is an LLM with two tools
  called in sequence: `retrieve_test` (hybrid BM25+semantic over the testplan
  collection: feature → test_name) then `gen_test` (one-line Verilator compile of
  the plusarg testbench → binary only). Gen logs go back to the router:
  pass → run stage, fail → reporter.
- The same user query also pre-retrieves matching rules into the checkers' context.
- **Rule retrieval lives inside the checker agent**; a deterministic sanitizer
  enforces cited rules were actually retrieved. Both BM25 retrievers lowercase.
- One test = one simulation run (+TEST plusarg) = one log file.
- Build/ingest failure aborts and surfaces the build log to the user.
- Temperature 0 everywhere; verdicts binary, reason required on FAIL.

## Validated in advance (no API needed)
- DUT + harness + separate-module test compile and run under Verilator 5.49
- PDF parsing yields exactly 9 test specs and 11 rules from the shipped documents
- Citation-provenance sanitizer and RAGAS row composition covered by the synthetic
  test cell inside the notebook

## Deliverables & Status (submission)

- **`fifo_final.ipynb`** — the full pipeline, executed end to end: 5-feature and
  2-feature runs, checker verdicts (incl. catching a deliberately planted reset
  bug), three RAGAS score tables, and the reporter's final table with trust notes.
- **`agent_server/`** — the pipeline packaged as a LangGraph server (one module
  per stage). Proven live: `langgraph dev --allow-blocking` on the laptop,
  full run driven from LangGraph Studio (orchestrate → generate → run → check
  → ragas → report, all green).
- **`frontend/`** — Next.js chat UI, deployed: https://fifo-verification.vercel.app
  Backend stays on the laptop (RTL/Verilator/documents never leave the machine);
  Vercel reaches it through a Cloudflare tunnel. The proxy chain is verified
  end-to-end (`/api/ok` on the Vercel domain answers `{"ok":true}` from the
  laptop server). Known issue at submission time: the chat's streaming call
  errors client-side ("Failed to fetch") — under investigation; the same
  deployed server runs fine when driven via LangGraph Studio / SDK.
- **Architecture notes** — `FUTURE_FEATURES.md` (production hardening: async
  wrapping instead of --allow-blocking, auth on the tunnel, named tunnel,
  RAGAS gating, parallel judge calls).
