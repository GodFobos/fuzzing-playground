#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
LIB=lib/json-parser
[ -d "$LIB" ] || git clone --depth 1 https://github.com/udp/json-parser.git "$LIB"
clang -g -O1 -fsanitize=fuzzer,address -I"$LIB" "$LIB/json.c" harness.c -o fuzz_json_parser
echo "Built ./fuzz_json_parser  —  run with ./run.sh"
