#!/bin/bash

# Check if run-clang-tidy is available first, then fallback to clang-tidy
if command -v run-clang-tidy &> /dev/null; then
    echo "Running run-clang-tidy..."
    run-clang-tidy "$@"
else
    echo "Error: run-clang-tidy found in PATH"
    exit 1
fi
