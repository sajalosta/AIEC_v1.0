from app.s04_tools import *  # noqa: F401,F403

# --- Docling hierarchical chunking ------------------------------------------
# The PDFs are parsed by Docling's layout model; HierarchicalChunker emits one
# chunk per paragraph tagged with its heading breadcrumb. Chunks are grouped by
# the T/R id in their innermost matching heading: one section per test / rule.

TEST_HEADING = re.compile(r"(T\d+)\s*[—-]\s*(\w+)")
RULE_HEADING = re.compile(r"\b(R\d+)\b")


def load_document(source: Path):
    """Parse a PDF using Docling. Returns a DoclingDocument, not a string."""
    converter = DocumentConverter()
    result = converter.convert(str(source))
    return result.document


def convert_chunk(doc_chunk) -> dict:  # create a dict with headers and text beneath it.
    """
    Convert a Docling DocChunk into a plain dict.

    headings   -> list preserved as-is
    content    -> paragraph text
    chunk_text -> breadcrumb + content  (what gets embedded)
    """
    headings   = doc_chunk.meta.headings or []
    content    = doc_chunk.text.strip()
    breadcrumb = " > ".join(headings)
    chunk_text = f"{breadcrumb}\n\n{content}" if breadcrumb else content
    return {"headings": headings, "content": content, "chunk_text": chunk_text}


def group_sections(chunks: Iterable[dict], pattern: re.Pattern) -> dict[str, dict]: ## this function groups the chunks by the innermost heading matching `pattern`. so if heading is 4.3 T3 and 4 chunks with this header , then you combine all of them as they are part of the same test.
    """Group chunk dicts by the innermost heading matching `pattern`.
    Returns {section_id: {match, breadcrumb, parts}} in document order."""
    sections: dict[str, dict] = {}
    for chunk in chunks:
        match = None
        for heading in chunk["headings"]:
            m = pattern.search(heading)
            if m:
                match = m
        if match is None:
            continue
        section = sections.setdefault(match.group(1), {
            "match": match,
            "breadcrumb": " > ".join(chunk["headings"]),
            "parts": [],
        })
        section["parts"].append(chunk["content"])
    return sections


def docling_sections(path: Path, pattern: re.Pattern) -> dict[str, dict]:  ## this function loads the document, chunks it, and groups the chunks by the innermost heading matching `pattern` and returns a dictionary of header and the chunks.
    document = load_document(path)
    chunks = [convert_chunk(c) for c in HierarchicalChunker().chunk(document)]
    return group_sections(chunks, pattern)


def _section_text(section: dict) -> str:  ## this function returns the breadcrumb and the text beneath it.
    return section["breadcrumb"] + "\n" + "\n".join(section["parts"])


def parse_test_plan(path: Path) -> list[dict]:
    """Chunk labels only — no TestSpec here; ingestion just ingests."""
    out = []
    for tid, section in docling_sections(path, TEST_HEADING).items():
        body = _section_text(section)
        out.append({"test_id": tid, "name": section["match"].group(2),
                    "body": " ".join(body.split())})
    return out


def parse_rule_book(path: Path) -> list[tuple[str, str]]:
    return [(rid, " ".join(_section_text(section).split()))
            for rid, section in docling_sections(path, RULE_HEADING).items()]


# --- retrieval contract and helpers ----------------------------------------

@dataclass(frozen=True)
class RetrievedDocument:
    id: str
    text: str
    score: float | None
    evidence_ids: tuple[str, ...]
    metadata: dict


def as_retrieved_document(document: Document, score: float | None = None) -> RetrievedDocument:
    return RetrievedDocument(
        id=document.metadata["chunk_id"],
        text=document.page_content,
        score=float(score) if score is not None else None,
        evidence_ids=(document.metadata["page_id"],),
        metadata=dict(document.metadata),
    )


def print_results(results: Sequence[RetrievedDocument], text_limit: int = 260) -> None:
    for rank, result in enumerate(results, start=1):
        section = result.metadata.get("page_id", "?")
        score = "n/a" if result.score is None else f"{result.score:.4f}"
        print(f"#{rank} | {result.id} | section={section} | score={score}")
        print(result.text[:text_limit].replace("\n", " "))
        print()


def tokenize(text: str) -> list[str]:
    return re.findall(r"[a-z0-9]+", text.lower())


FIRST_STAGE_K = 2

TP_CHILDREN: list[Document] = []
RB_CHILDREN: list[Document] = []
TP_STORE = RB_STORE = None
TP_BM25 = RB_BM25 = None


def _section_documents() -> tuple[list[Document], list[Document]]:
    """One Document per test / per rule section; children inherit metadata."""
    tests = parse_test_plan(TEST_PLAN_PDF)
    rules = parse_rule_book(RULE_BOOK_PDF)

    testplan_sections = [
        Document(page_content=t["body"], metadata={
            "source": TEST_PLAN_PDF.name, "document_type": "test_plan",
            "page_id": t["test_id"], "test_id": t["test_id"],
            "name": t["name"],
        })
        for t in tests
    ]
    rule_sections = [
        Document(page_content=body, metadata={
            "source": RULE_BOOK_PDF.name, "document_type": "rule_book",
            "page_id": rule_id, "rule_id": rule_id,
        })
        for rule_id, body in rules
    ]
    return testplan_sections, rule_sections


def build_collections() -> IngestReport:
    global TP_CHILDREN, RB_CHILDREN, TP_STORE, RB_STORE, TP_BM25, RB_BM25
    try:
        testplan_sections, rule_sections = _section_documents()

        TP_CHILDREN = list(testplan_sections)   # one Docling section per chunk
        for index, child in enumerate(TP_CHILDREN):
            child.metadata["chunk_id"] = f"tp-child-{index:03d}"
        TP_STORE = QdrantVectorStore.from_documents(
            documents=TP_CHILDREN, embedding=embeddings,
            location=":memory:", collection_name="fifo_testplan",
        )
        TP_BM25 = BM25Okapi([tokenize(child.page_content) for child in TP_CHILDREN])

        RB_CHILDREN = list(rule_sections)       # one Docling section per chunk
        for index, child in enumerate(RB_CHILDREN):
            child.metadata["chunk_id"] = f"rb-child-{index:03d}"
        RB_STORE = QdrantVectorStore.from_documents(
            documents=RB_CHILDREN, embedding=embeddings,
            location=":memory:", collection_name="fifo_rules",
        )
        RB_BM25 = BM25Okapi([tokenize(child.page_content) for child in RB_CHILDREN])

        if len(testplan_sections) < 9:
            print(f"warning: only {len(testplan_sections)} tests parsed; expected 9")
        if len(rule_sections) < 11:
            print(f"warning: only {len(rule_sections)} rules parsed; expected 11")
        return IngestReport(ok=bool(testplan_sections and rule_sections))
    except Exception as exc:
        print(f"ingest error: {type(exc).__name__}: {exc}")
        return IngestReport(ok=False)


# --- reading the stores back at retrieval time ------------------------------

def dense_retrieve_testplan(question: str, k: int = 2) -> list[RetrievedDocument]:
    matches = TP_STORE.similarity_search_with_score(question, k=k)
    return [as_retrieved_document(document, score) for document, score in matches]


def dense_retrieve_rules(question: str, k: int = 2) -> list[RetrievedDocument]:
    matches = RB_STORE.similarity_search_with_score(question, k=k)
    return [as_retrieved_document(document, score) for document, score in matches]


def bm25_retrieve_testplan(question: str, k: int = 2) -> list[RetrievedDocument]:
    scores = TP_BM25.get_scores(tokenize(question))
    ranked = sorted(range(len(scores)), key=lambda i: scores[i], reverse=True)
    return [as_retrieved_document(TP_CHILDREN[i], float(scores[i])) for i in ranked[:k]]


def bm25_retrieve_rules(question: str, k: int = 2) -> list[RetrievedDocument]:
    scores = RB_BM25.get_scores(tokenize(question))
    ranked = sorted(range(len(scores)), key=lambda i: scores[i], reverse=True)
    return [as_retrieved_document(RB_CHILDREN[i], float(scores[i])) for i in ranked[:k]]


def reciprocal_rank_fusion(
    ranked_lists: Iterable[Sequence[RetrievedDocument]],
    *,
    limit: int,
    rrf_constant: int = 60,
) -> list[RetrievedDocument]:
    scores: dict[str, float] = {}
    documents_by_id: dict[str, RetrievedDocument] = {}
    for ranked_list in ranked_lists:
        for rank, document in enumerate(ranked_list, start=1):
            documents_by_id.setdefault(document.id, document)
            scores[document.id] = scores.get(document.id, 0.0) + 1 / (rrf_constant + rank)
    return [
        replace(
            documents_by_id[document_id],
            score=score,
            metadata={**documents_by_id[document_id].metadata, "rrf_score": score},
        )
        for document_id, score in
        sorted(scores.items(), key=lambda item: item[1], reverse=True)[:limit]
    ]


def hybrid_testplan_retrieve(question: str, k: int = 1) -> list[RetrievedDocument]:
    return reciprocal_rank_fusion(
        [dense_retrieve_testplan(question, k=FIRST_STAGE_K),
         bm25_retrieve_testplan(question, k=FIRST_STAGE_K)],
        limit=k,
    )


def hybrid_rules_retrieve(question: str, k: int = 2) -> list[RetrievedDocument]:
    return reciprocal_rank_fusion(
        [dense_retrieve_rules(question, k=FIRST_STAGE_K),
         bm25_retrieve_rules(question, k=FIRST_STAGE_K)],
        limit=k,
    )


def hybrid_rule_search(query: str, k: int = 2) -> list[dict]:
    """Query-seeded rules and the retrieve_rules tool share this."""
    return [{"rule_id": d.metadata.get("rule_id", "?"), "text": d.text}
            for d in hybrid_rules_retrieve(query, k=k)]


TESTGEN_RECORDS: dict[str, dict] = {}   # side channel -> RAGAS testgen scoring


@tool(
    "retrieve_test",
    description=(
        "Retrieve the test from the ingested test plan that covers a feature. "
        "Input: the feature to test, in natural language. Returns the matching "
        "test_name and its feature line."
    ),
)
def retrieve_test(feature_query: str) -> str:
    results = hybrid_testplan_retrieve(feature_query, k=1)
    if not results:
        return json.dumps({})
    hit = results[0]
    m = hit.metadata
    # TestSpec exists only from this moment on, built from the chosen chunk
    fm = re.search(r"Feature under test:\s*(.+?)(?:Description:|$)", hit.text, re.DOTALL)
    sm = re.search(r"Stimulus:\s*(.+?)(?:Expected results:|Pass criteria:|$)", hit.text, re.DOTALL)
    spec = TestSpec(test_id=m["test_id"], name=m["name"],
                    feature=" ".join(fm.group(1).split()) if fm else "",
                    stimulus=" ".join(sm.group(1).split()) if sm else "")
    test_name = f"{spec.test_id}_{spec.name}"
    TESTGEN_RECORDS[test_name] = {          # side channel: RAGAS scores this retrieval
        "user_input": feature_query,
        "feature": spec.feature,
        "retrieved_contexts": [hit.text],
        "response": test_name,
    }
    return json.dumps({"test_name": test_name, "feature": spec.feature}, indent=1)


@tool(
    "retrieve_rules",
    description=(
        "Retrieve the FIFO rule-book sections most relevant to a checking "
        "question, using hybrid BM25 + dense search. Input: a natural-language "
        "query about the behavior under judgment. Returns rule chunks tagged "
        "with rule_id."
    ),
)
def retrieve_rules(query: str) -> str:
    return json.dumps(hybrid_rule_search(query), indent=1)

print("Two Qdrant collections + BM25 indexes defined; hybrid retrieval ready.")
