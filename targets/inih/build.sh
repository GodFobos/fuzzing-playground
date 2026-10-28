#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
LIB=lib/inih
[ -d "$LIB" ] || git clone --depth 1 https://github.com/benhoyt/inih.git "$LIB"
clang -g -O1 -fsanitize=fuzzer,address -I"$LIB" "$LIB/ini.c" harness.c -o fuzz_inih
echo "Built ./fuzz_inih  —  run with ./run.sh"
