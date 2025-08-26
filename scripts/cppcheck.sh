#!/usr/bin/env bash

if command -v clang-tidy &> /dev/null; then
    echo "Running clang-tidy..."
    cppcheck --project=build/compile_commands.json "$@"
else
    echo "Error: cppcheck not found in PATH"
    exit 1
fi
