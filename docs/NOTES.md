# Fuzzing notes (cheat-sheet)

## The mental model
A fuzzer throws millions of mutated/garbage inputs at a function and waits for
it to crash. "Coverage-guided" means it watches which code paths each input
hits and keeps the inputs that reach *new* code, so it digs deeper over time.

## The pieces
- **Target** — the library under test (a parser of untrusted input).
- **Harness** — a tiny adapter *you* write. The fuzzer only knows how to call
  one fixed function; the harness receives its bytes and calls the library the
  way that library expects.
- **libFuzzer** — the engine, linked in by `-fsanitize=fuzzer`. It looks for a
  function named exactly `LLVMFuzzerTestOneInput` and calls it in a loop.
- **ASan** (AddressSanitizer) — `-fsanitize=address`. A memory "alarm": without
  it many memory bugs stay silent; with it the program stops and prints exactly
  what broke and where.

## The harness is just shape-matching
The fuzzer always hands you `(const uint8_t *data, size_t size)`.
Each library wants a different call shape, so the harness adapts:
- needs a NUL-terminated string? -> malloc(size+1), copy, set last byte '\0'.
- a push parser (inih)? -> also pass a handler callback (a do-nothing one that
  returns 1 is enough; it only exists to fill the required argument).
- returns an allocated tree? -> free it (toml_free / json_value_free).
Rule of thumb: every malloc you make needs a free; call the library's own free
function for whatever it allocated.

## Build & run
```bash
clang -g -O1 -fsanitize=fuzzer,address lib.c harness.c -o fuzz_x
mkdir corpus && echo '<valid sample>' > corpus/seed
./fuzz_x corpus
```

## Reading output
- `cov:` rising   -> harness works, reaching new code.
- `cov:` flat     -> weak corpus/dict, or harness misses the interesting code.
- `ERROR: AddressSanitizer` -> bug found; reproducer saved (artifact_prefix).

## Running a real campaign
- bigger corpus (collect real sample files of the format)
- `-jobs=N -workers=N` to use many cores
- let it run for hours/overnight
- `./fuzz_x -merge=1 corpus_min corpus` to minimise the corpus

## Triage a crash
```bash
./fuzz_x findings/crash-xxxx     # replay the single input
```
Read the ASan report: bug type (heap-buffer-overflow, use-after-free, ...),
the stack trace, and the source line. Decide: real memory-safety bug, or just
a benign assert/early-exit.

## Responsible disclosure
Report privately first (SECURITY.md or a minimal issue). Give the maintainer a
reproducer. Don't publish a working exploit before a fix exists.
