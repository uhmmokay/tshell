#!/bin/sh

SCRIPT_DIR=$(cd -- "$(dirname -- "$0")" &> /dev/null && pwd)
g++ -std=c++17 "$SCRIPT_DIR/main.cpp" -o "$SCRIPT_DIR/tshell" -lreadline
"$SCRIPT_DIR/tshell"