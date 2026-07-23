FIFO Agentic Verification — Master Cheatsheet
PART 1 · NOTEBOOK
First time only
cd ~/DrGreggCourse/code/AIEC_v1.0/fifo_agentic_verification
uv sync
Open notebook → select kernel .venv/bin/python
Run
Cells top to bottom: imports → config (enter OpenAI key) → contracts → tools → ingest → gate 2 (Enter twice past probes) → orch → gen → run → check → RAGAS → gate 6 → full-run cell (type features)




PART 2 · BACKEND (local agent server)
First time only
cd agent_server
uv sync
Edit agent_server/.env:
OPENAI_API_KEY=sk-...
LANGSMITH_API_KEY=lsv2_...
LANGSMITH_TRACING=true
LANGSMITH_PROJECT=fifo-agentic-verification
Every launch
cd agent_server
uv run langgraph dev --allow-blocking
Wait for 🚀 API: http://127.0.0.1:2024
Confirm: curl http://localhost:2024/ok → {"ok":true}
(Optional) Test in Studio: open printed studio link → pick fifo_verification → submit {"user_query":"test the full flag"} → runs to report; traces at smith.langchain.com




PART 3 · FRONTEND — LOCAL
First time only
Edit frontend/.env:
NEXT_PUBLIC_API_URL=http://localhost:3000/api
LANGGRAPH_API_URL=http://localhost:2024
chat.tsx apiUrl:
typescript
const apiUrl =
  process.env.NEXT_PUBLIC_LANGGRAPH_API_URL ??
  (typeof window !== "undefined"
    ? `${window.location.origin}/api`
    : (process.env.NEXT_PUBLIC_API_URL ?? "http://localhost:3000/api"));
route.ts has runtime: "nodejs"
cd <frontend> → npm install
Every launch (needs backend from Part 2 running)
cd <frontend> → npm run dev
Open http://localhost:3000 → chat





PART 4 · FRONTEND — VERCEL (public site, laptop backend)
First time only
npm install -g vercel
vercel login
cd frontend → vercel (links project fifo-verification)
Every deploy
Backend up (Part 2 running) + confirm curl localhost:2024/ok
Tunnel — new terminal:
cloudflared tunnel --url http://localhost:2024    ##SajOst this is the cmd with the cloudflare command! 
## SajOst you need to execute the above cmd to get a cloudflare link which will be used to provide to vercel as a link to your local desktop! 
Copy the https://….trycloudflare.com URL.


24. Set BOTH env vars to the new tunnel URL — before deploying:

vercel env rm NEXT_PUBLIC_LANGGRAPH_API_URL production
vercel env add NEXT_PUBLIC_LANGGRAPH_API_URL production   # paste tunnel URL this is cloudflare link
vercel env rm LANGGRAPH_API_URL production
vercel env add LANGGRAPH_API_URL production               # paste same tunnel URL this is the cloudflare link


Deploy:
cd frontend
vercel --prod
Test:
https://fifo-verification.vercel.app/api/ok → {"ok":true}
Open site → hard-refresh (Ctrl+Shift+R) → chat



TROUBLESHOOTING

"Failed to fetch" / HTTP 500 on chat:

curl http://localhost:2024/ok — backend alive?
Send message, watch server terminal: prints = request arrived (backend issue); silent = never arrived (proxy/tunnel/env issue)
F12 → Network → click failed row → note URL + Status

Env var changes did nothing: NEXT_PUBLIC_* vars bake in at build → must vercel --prod after changing.

CORS error in console: direct-to-tunnel path needs backend CORS enabled (small server edit — flag me).


##don't bother understanding this below. 

RULES
uv sync / npm install = one-time, not per launch
--allow-blocking = always
Two separate venvs: project-root .venv (notebook) vs agent_server/.venv (server) — never cross them
First ingest needs network (docling OCR model cache); offline after
Tunnel URL changes every restart → redo step 24 (both vars) + step 25 every time
LangSmith cloud deploy won't run this backend (needs Verilator + RTL local) — backend stays on your machine, LangSmith only observes
To kill the per-session tunnel churn: set up a named cloudflared tunnel (permanent URL)