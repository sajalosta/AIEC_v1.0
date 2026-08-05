export type FinalReportShape = {
  title?: string;
  summary?: string;
  results_table_markdown?: string;
  failures_detail_markdown?: string;
  trust_notes?: string;
};

export type ReportRow = {
  test: string;
  outcome: string;
  notes: string;
  testRecall: string;
  rulesP: string;
  rulesR: string;
  faith: string;
};

export type ParsedReport = {
  title: string;
  summary: string;
  rows: ReportRow[];
  failures: string;
  trustNotes: string;
};

const HEADER_ALIASES: Record<keyof Omit<ReportRow, never>, string[]> = {
  test: ["test"],
  outcome: ["outcome"],
  notes: ["notes", "reason / notes", "reason", "reason/notes"],
  testRecall: ["test recall", "context recall (test)", "context recall test"],
  rulesP: ["rules p", "context precision (rules)", "context precision"],
  rulesR: ["rules r", "context recall (rules)"],
  faith: ["faith", "faithfulness (checker)", "faithfulness"],
};

function splitRow(line: string): string[] {
  return line
    .trim()
    .replace(/^\|/, "")
    .replace(/\|$/, "")
    .split("|")
    .map((c) => c.trim());
}

function isSeparator(line: string): boolean {
  return /^\|?\s*:?-+:?\s*(\|\s*:?-+:?\s*)+\|?$/.test(line.trim());
}

function normalizeHeader(h: string): string {
  return h.trim().toLowerCase().replace(/\s+/g, " ");
}

function mapHeaders(headers: string[]): Partial<Record<keyof ReportRow, number>> {
  const map: Partial<Record<keyof ReportRow, number>> = {};
  headers.forEach((header, idx) => {
    const norm = normalizeHeader(header);
    (Object.keys(HEADER_ALIASES) as (keyof ReportRow)[]).forEach((key) => {
      if (map[key] != null) return;
      if (HEADER_ALIASES[key].some((alias) => norm === alias || norm.includes(alias))) {
        map[key] = idx;
      }
    });
  });
  return map;
}

export function parseMarkdownTable(md: string): ReportRow[] {
  const lines = md
    .replace(/\r\n/g, "\n")
    .split("\n")
    .map((l) => l.trim())
    .filter((l) => l.includes("|"));
  if (lines.length < 2) return [];

  let headerIdx = 0;
  for (let i = 0; i < lines.length - 1; i += 1) {
    if (isSeparator(lines[i + 1])) {
      headerIdx = i;
      break;
    }
  }
  const headers = splitRow(lines[headerIdx]);
  const col = mapHeaders(headers);
  if (col.test == null || col.outcome == null) return [];

  return lines.slice(headerIdx + 2).map((line) => {
    const cells = splitRow(line);
    const at = (key: keyof ReportRow) =>
      col[key] != null ? (cells[col[key]!] ?? "n/a") : "n/a";
    return {
      test: at("test"),
      outcome: at("outcome"),
      notes: at("notes"),
      testRecall: at("testRecall"),
      rulesP: at("rulesP"),
      rulesR: at("rulesR"),
      faith: at("faith"),
    };
  });
}

export function tryParseFinalReport(text: string): FinalReportShape | null {
  const trimmed = text.trim();
  if (!trimmed.startsWith("{") || !trimmed.includes("results_table_markdown")) {
    return null;
  }
  try {
    const parsed = JSON.parse(trimmed) as FinalReportShape;
    if (
      parsed &&
      typeof parsed === "object" &&
      typeof parsed.results_table_markdown === "string"
    ) {
      return parsed;
    }
  } catch {
    return null;
  }
  return null;
}

export function tryParseReport(text: string): ParsedReport | null {
  const json = tryParseFinalReport(text);
  if (json) {
    return {
      title: json.title?.trim() || "Verification report",
      summary: json.summary?.trim() || "",
      rows: parseMarkdownTable(json.results_table_markdown || ""),
      failures: (json.failures_detail_markdown || "").trim(),
      trustNotes: (json.trust_notes || "").trim(),
    };
  }

  const trimmed = text.trim();
  const looksLikeReport =
    /verification pipeline report|fifo regression report|## results/i.test(
      trimmed
    ) ||
    (/^#\s+/m.test(trimmed) && /\|.*outcome.*\|/i.test(trimmed));
  if (!looksLikeReport) return null;

  const titleMatch = trimmed.match(/^#\s+(.+)$/m);
  const summaryMatch = trimmed.match(/^#\s+.+\n+([^\n|#]+)/);
  const trustMatch = trimmed.match(/##\s*trust notes\s*\n+([\s\S]*?)(?=\n##|\s*$)/i);
  const failMatch = trimmed.match(
    /##\s*failures\s*\/?\s*review\s*\n+([\s\S]*?)(?=\n##|\s*$)/i
  );

  const rows = parseMarkdownTable(trimmed);
  if (!rows.length && !titleMatch) return null;

  return {
    title: titleMatch?.[1]?.trim() || "Verification report",
    summary: summaryMatch?.[1]?.trim() || "",
    rows,
    failures: failMatch?.[1]?.trim() || "",
    trustNotes: trustMatch?.[1]?.trim() || "",
  };
}
