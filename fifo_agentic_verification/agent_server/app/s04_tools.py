from app.s03_contracts import *  # noqa: F401,F403

VERILATOR = shutil.which("verilator") or shutil.which("verilator-cli") or "verilator"  ## shutil.which is a function that returns the path of a command
HW_SOURCES = ["snix_sync_fifo.sv", "fifo_event_monitor.sv", "tb_top.sv"]  ## the source files of the FIFO hardware being tested.
SIM_TIMEOUT_S = 60


def run_cmd(cmd: list[str], cwd: Path, timeout: int = 300) -> tuple[int, str]: #this function runs a command and returns the return code and the output.
    proc = subprocess.run(
        cmd, cwd=cwd, capture_output=True, text=True, timeout=timeout
    )
    return proc.returncode, (proc.stdout + proc.stderr)


def tail(text: str, lines: int = 25) -> str:   ## captures the last n lines of a string.
    return "\n".join(text.strip().splitlines()[-lines:])


def sanitize_name(name: str) -> str:
    """Normalize hand-typed names ("T7 — lap_the_buffer") to pipeline form
    (T7_lap_the_buffer). Bare names ("lap_the_buffer") auto-complete from the
    testbench's test labels when unambiguous."""
    name = re.sub(r"_+", "_", re.sub(r"[^A-Za-z0-9_]+", "_", name.strip())).strip("_")
    if re.match(r"^T\d+_", name):
        return name
    labels = sorted(set(re.findall(r'"(T\d+_\w+)"', (HW_DIR / "tb_top.sv").read_text())))
    hits = [l for l in labels if l == name or l.endswith(f"_{name}") or l.split("_", 1)[-1] == name]
    if len(hits) == 1:
        return hits[0]
    return name  # unknown/ambiguous: leave as typed; downstream reports it


def verilator_build(work_name: str) -> BuildReport:  ## this function compiles the DUT + monitor + the plusarg tb_top (which holds the pre-decided test sequences) into build/<work_name>/.
    """One-line test generation: compile DUT + monitor + the plusarg tb_top
    (which holds the pre-decided test sequences) into build/<work_name>/."""
    work_name = sanitize_name(work_name)
    work = BUILD_DIR / work_name
    if work.exists():
        shutil.rmtree(work, ignore_errors=True)
    work.mkdir(parents=True, exist_ok=True)
    for src in HW_SOURCES:
        shutil.copy(HW_DIR / src, work)

    cmd = [
        VERILATOR, "--binary", "--timing", "-Wall",
        "-Wno-DECLFILENAME", "-Wno-SYNCASYNCNET", "-Wno-BLKSEQ",
        "tb_top.sv", *HW_SOURCES[:2],
        "--top-module", "tb_top",
    ]
    code, log = run_cmd(cmd, cwd=work)
    binary = work / "obj_dir" / "Vtb_top"
    if not binary.exists():
        # some builds need an explicit make pass (observed with pip verilator)
        mk = work / "obj_dir" / "Vtb_top.mk"
        if mk.exists():
            code2, log2 = run_cmd(
                ["make", "-s", "-C", str(work / "obj_dir"),
                 "-f", "Vtb_top.mk", "CXX=c++ -fcoroutines"],
                cwd=work,
            )
            log += "\n" + log2
    ok = binary.exists()
    return BuildReport(ok=ok, log_tail=tail(log))


def run_simulation(test_name: str) -> RunResult:  ## this function runs a simulation of the test.
    test_name = sanitize_name(test_name)
    binary = BUILD_DIR / test_name / "obj_dir" / "Vtb_top"
    if not binary.exists():
        return RunResult(test_name=test_name, status="not_run",
                         error="binary missing; generation failed upstream")
    log_path = LOG_DIR / f"{test_name}.log"
    try:
        proc = subprocess.run(
            [str(binary), f"+TEST={test_name}"],
            capture_output=True, text=True, timeout=SIM_TIMEOUT_S
        )
        text = "\n".join(
            line for line in proc.stdout.splitlines() if not line.startswith("-")
        )
        log_path.write_text(text)
        if "status=completed" in text:
            status = "completed"
        elif "status=timeout" in text:
            status = "timeout"
        else:
            status = "crash"
        return RunResult(test_name=test_name, status=status,
                         log_tail=tail(text, 40))
    except subprocess.TimeoutExpired:
        return RunResult(test_name=test_name, status="timeout",
                         error=f"wall-clock timeout after {SIM_TIMEOUT_S}s")
    except Exception as exc:
        return RunResult(test_name=test_name, status="crash",
                         error=f"{type(exc).__name__}: {exc}")

print(f"Verilator: {VERILATOR}")
