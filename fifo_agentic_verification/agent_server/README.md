# FIFO Agentic Verification — Agent Server

The notebook pipeline packaged for `langgraph dev`: features in, AI-checked and
RAGAS-scored regression report out. Backend runs on the laptop (RTL, testbench,
Verilator, and documents never leave the machine); the frontend is hosted on
Vercel and reaches this server through the API passthrough.

## Layout

```
agent_server/
├── langgraph.json        # graph + assistants manifest ("agent" = chat entry)
├── pyproject.toml
├── .env.example          # copy to .env, add OPENAI_API_KEY
└── app/
    ├── s01_imports.py    # one module per pipeline stage, in load order
    ├── s02_config.py     #   models, paths (hw/, docs/ resolved at repo root)
    ├── s03_contracts.py  #   typed handoffs + chat messages channel
    ├── s04_tools.py      #   verilator build / run (deterministic)
    ├── s05_ingest.py     #   Docling -> Qdrant + BM25 hybrid retrieval
    ├── s06_orch.py ... s11_report.py   # agents, routers, RAGAS, reporter
    ├── s12_graph.py      #   LangGraph wiring + chat adapter
    └── graph.py          # exports compiled `graph`
```

## Run the backend (WSL, from this directory)

```bash
source ~/.venvs/fifo/bin/activate          # the project venv (has all deps)
uv pip install -U "langgraph-cli[inmem]"   # first time only
cp .env.example .env                       # then put your OPENAI_API_KEY in it
langgraph dev                              # API on http://localhost:2024 + Studio
```

Smoke test in LangGraph Studio: pick the `agent` assistant, send
`1. reset behavior, 2. FIFO ordering` as a message, watch the graph walk
orchestrate -> generate -> run -> check -> ragas -> report. The final
assistant message is the rendered report.

## Point the frontend at it

Local dev: in `frontend/.env` set `LANGGRAPH_API_URL=http://localhost:2024`
and use `assistantId: "agent"`.

Vercel: expose the laptop with a tunnel —

```bash
cloudflared tunnel --url http://localhost:2024
```

— then set the Vercel project env `LANGGRAPH_API_URL` to the tunnel URL and
redeploy. The laptop (and WSL) must stay up while the site is live.

## Notes

- Chat input: the last user message becomes the feature request; numbered
  lists work ("1. blah, 2. blah").
- The graph also accepts direct state (`{"user_query": "..."}`) via the SDK.
- First request per server start is slow: Docling parses both PDFs during
  the orchestrator's ingest step.
