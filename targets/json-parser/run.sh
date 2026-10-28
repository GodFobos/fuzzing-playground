#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p findings
# -max_len caps input size; pass extra flags through, e.g. ./run.sh -jobs=4
./fuzz_json_parser corpus -artifact_prefix=findings/ -max_len=4096 "$@"
