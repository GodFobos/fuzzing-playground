# fuzzing-playground

Coverage-guided fuzzing harnesses for small C parsing libraries, built with
**libFuzzer + AddressSanitizer** (clang).

Each target is a self-contained folder: a harness, a seed corpus, and two
scripts (`build.sh`, `run.sh`). `build.sh` fetches the upstream library into a
git-ignored `lib/` folder and compiles it together with the harness, so the
whole thing runs with one command.

```bash
cd targets/inih
./build.sh
./run.sh
```

## Targets

| Target | Library | Format | Upstream |
|--------|---------|--------|----------|
| `inih` | benhoyt/inih | INI config | https://github.com/benhoyt/inih |
| `tomlc99` | cktan/tomlc99 | TOML config | https://github.com/cktan/tomlc99 |
| `json-parser` | udp/json-parser | JSON | https://github.com/udp/json-parser |

## How a target is laid out

```
targets/<name>/
├── harness.c     # the fuzz entry point (LLVMFuzzerTestOneInput)
├── build.sh      # clone lib + compile with -fsanitize=fuzzer,address
├── run.sh        # run the fuzzer against ./corpus
└── corpus/       # seed inputs to start from
```

## Reading the output

- `cov:` rising — the harness works, the fuzzer is reaching new code.
- `cov:` stuck for a long time — corpus/dictionary too weak, or the harness
  doesn't reach the interesting code.
- `ERROR: AddressSanitizer` — a bug was found. The reproducing input is saved
  under `findings/`.

## Responsible disclosure

Findings are reported privately to maintainers first (see each project's
`SECURITY.md`, or open a minimal issue). No working exploit is published before
a fix is available.

## Requirements

`clang` with the fuzzer + sanitizer runtime:

```bash
sudo apt install clang        # Ubuntu / WSL
```
