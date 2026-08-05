"use client";

import { Badge } from "@/components/ui/badge";
import { cn } from "@/lib/utils";
import type { ParsedReport, ReportRow } from "@/lib/report";

function outcomeTone(outcome: string): {
  badge: string;
  bar: string;
} {
  const o = outcome.trim().toUpperCase();
  if (o === "PASS") {
    return {
      badge: "border-transparent bg-emerald-600 text-white",
      bar: "bg-emerald-500",
    };
  }
  if (o === "REVIEW") {
    return {
      badge: "border-transparent bg-amber-500 text-white",
      bar: "bg-amber-400",
    };
  }
  return {
    badge: "border-transparent bg-red-600 text-white",
    bar: "bg-red-500",
  };
}

function Score({ label, value }: { label: string; value: string }) {
  const v = value.trim();
  const empty = !v || v.toLowerCase() === "n/a";
  return (
    <div className="min-w-[4.5rem] rounded-md border bg-background px-2 py-1">
      <div className="text-[10px] uppercase tracking-wide text-muted-foreground">
        {label}
      </div>
      <div
        className={cn(
          "font-mono text-sm tabular-nums",
          empty ? "text-muted-foreground" : "text-foreground"
        )}
      >
        {empty ? "—" : v}
      </div>
    </div>
  );
}

function ResultRow({ row }: { row: ReportRow }) {
  const tone = outcomeTone(row.outcome);
  return (
    <div className="relative overflow-hidden rounded-xl border bg-background">
      <div className={cn("absolute inset-y-0 left-0 w-1", tone.bar)} />
      <div className="flex flex-col gap-3 p-4 pl-5">
        <div className="flex flex-wrap items-start justify-between gap-2">
          <div className="min-w-0">
            <p className="truncate font-mono text-sm font-semibold tracking-tight">
              {row.test}
            </p>
            {row.notes && row.notes.toLowerCase() !== "n/a" && (
              <p className="mt-1 text-sm leading-snug text-muted-foreground">
                {row.notes}
              </p>
            )}
          </div>
          <Badge className={cn("shrink-0", tone.badge)}>
            {row.outcome.toUpperCase()}
          </Badge>
        </div>
        <div className="flex flex-wrap gap-2">
          <Score label="Test recall" value={row.testRecall} />
          <Score label="Rules P" value={row.rulesP} />
          <Score label="Rules R" value={row.rulesR} />
          <Score label="Faith" value={row.faith} />
        </div>
      </div>
    </div>
  );
}

export function ReportCard({ report }: { report: ParsedReport }) {
  const hideFailures =
    !report.failures ||
    report.failures.toLowerCase().startsWith("no fail") ||
    report.failures.toLowerCase().startsWith("no review");

  return (
    <div className="w-full overflow-hidden rounded-2xl border bg-card shadow-sm">
      <div className="border-b bg-muted/40 px-5 py-4">
        <p className="text-xs font-medium uppercase tracking-[0.14em] text-muted-foreground">
          Final report
        </p>
        <h2 className="mt-1 text-lg font-semibold tracking-tight">
          {report.title}
        </h2>
        {report.summary && (
          <p className="mt-2 max-w-2xl text-sm leading-relaxed text-muted-foreground">
            {report.summary}
          </p>
        )}
      </div>

      <div className="space-y-3 px-5 py-4">
        {report.rows.length > 0 ? (
          report.rows.map((row) => <ResultRow key={row.test} row={row} />)
        ) : (
          <p className="text-sm text-muted-foreground">No result rows.</p>
        )}
      </div>

      {(!hideFailures || report.trustNotes) && (
        <div className="space-y-3 border-t px-5 py-4">
          {!hideFailures && (
            <div>
              <p className="mb-1 text-xs font-medium uppercase tracking-wide text-muted-foreground">
                Failures / review
              </p>
              <p className="whitespace-pre-wrap text-sm leading-relaxed text-foreground">
                {report.failures}
              </p>
            </div>
          )}
          {report.trustNotes && (
            <div>
              <p className="mb-1 text-xs font-medium uppercase tracking-wide text-muted-foreground">
                Trust notes
              </p>
              <p className="text-sm leading-relaxed text-muted-foreground">
                {report.trustNotes}
              </p>
            </div>
          )}
        </div>
      )}
    </div>
  );
}
