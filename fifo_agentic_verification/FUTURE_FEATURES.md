# Future Features — FIFO Agentic Verification

Running list of features discussed but deliberately NOT in the current build.
Nothing here is committed; every item needs the project owner's explicit go.
(Maintained by Claude at the owner's request. Last updated: 2026-07-14)

## 1. Streaming pipeline with real backpressure
Today the stages are lock-step: gen fully drains, then run, then check. The
"buffer" between stages is just the LangGraph state list (e.g.
`GenPhaseReport.passed`) — unbounded, handed over once per stage boundary.
Future: per-test pipelines via LangGraph `Send` (one gen->run->check subgraph
per test) with `max_concurrency` as the admission semaphore, so a test can be
checking while another is still generating. Alternative: an explicit bounded
`asyncio.Queue` between stage coroutines (put() blocks when full = producer
stall). Effort: days. Value: stage overlap, closer to the original streaming
diagram.

## 2. Hard code-enforced wave cap
The min(n, 4) wave width for routers is prompt-enforced; the runtime would
execute a 5th call if a router emitted one. Future: a code gate that truncates
any turn's tool calls to VER_PARALLEL_LIMIT and re-queues the excess. Effort:
small. Value: the cap becomes physics instead of good behavior.

## 3. TestRun stage in router->agents format
Gen and check are RouterLLM -> 4 agents -> tools. Run is still RouterLLM ->
tools directly. Future: mirror run into TestRunAgents for full symmetry.
Effort: small. Decision pending from owner.

## 4. Calibration set / answer-correctness activation
The RAGAS answer-correctness metric exists but has no reference verdicts to
score against (planted-bug runs were removed from scope). Future: any source
of known-truth runs would activate it and calibrate faithfulness/recall
against actual verdict accuracy. Effort: small once a truth source is chosen.

## 5. Open-source / local model swap
Closed-source models for now. Future: swap checker/routers to local open
weights (Ollama/vLLM), local embeddings, RAGAS judge included — the on-prem,
IP-safe, reproducible deployment story — and measure the cloud-vs-local
verdict accuracy delta. Fine-tuning explicitly excluded from this project.

## 6. Random / constrained-random testing
Rules-based checking extends naturally to random stimulus (rules are stimulus-
independent). Needs: seeded random sequences in the TB, seed logging, and the
checker strategies below. Brainstormed, out of scope.

## 7. Divide-and-conquer checking for long logs
Rule-split checkers (one invariant per checker over a filtered event stream)
and the checkpointed streaming checker (verify state, commit, consume next
chunk; carried state as rigid schema). Also the measurable question: at what
log length does a single checker get lost, and how much does chunking move
that point. Research-grade material.

## 8. CPU-pipeline scale-up
Per-stage checkers (IF/ID/EX/MEM/WB), five stage logs with instruction ids,
50-instruction windows, seams checker for cross-stage consistency, relay/baton
architectural state. The "scaling to real designs" chapter.

## 9. Coverage evidence
Cover properties (Verilator-supported subset) as machine evidence that a
test's stimulus actually reached its scenario; a coverage summary in the log
for the checker to weigh. Complements, does not replace, event logging.

## 10. RAGAS trust gating policy
Scores are currently reported per verdict. Future: thresholds that flag or
downgrade low-faithfulness/low-recall verdicts in the report automatically.
Threshold values are an owner decision, ideally informed by item 4.

## 11. Reporter -> Main LLM return path
The final report renders in the notebook (user = Main LLM). A future packaged
version would route the report back through an explicit user-facing agent.

## 12. IP / patent thread
Provisional filing consideration before public demo; university IP policy
check. Owner's call, time-sensitive around demo day.

## Web UI (Vercel) + local backend
- UI hosted on Vercel: feature-request box in, live stage progress + FinalReport
  + RAGAS trust tables out.
- Backend stays on the laptop (WSL): the RTL, testbench, Verilator, and vector
  stores never leave the machine — consistent with the on-prem/IP story.
- Plumbing: wrap the pipeline in a small FastAPI service (one POST /run
  endpoint invoking verification_graph); expose it to the Vercel frontend via
  a tunnel (cloudflared / ngrok) or LAN; stream stage events for progress.
- The notebook remains the reference implementation; the service imports the
  same cells' code, not a fork of it.
