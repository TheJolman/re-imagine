#!/usr/bin/env bash

# Check if clang-tidy is available
if command -v clang-tidy &> /dev/null; then
    echo "Running clang-tidy..."
    run-clang-tidy -fix -format -p build "$@"
else
    echo "Error: clang-tidy not found in PATH"
    exit 1
fi
