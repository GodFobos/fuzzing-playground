#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
LIB=lib/tomlc99
[ -d "$LIB" ] || git clone --depth 1 https://github.com/cktan/tomlc99.git "$LIB"
clang -g -O1 -fsanitize=fuzzer,address -I"$LIB" "$LIB/toml.c" harness.c -o fuzz_tomlc99
echo "Built ./fuzz_tomlc99  —  run with ./run.sh"
