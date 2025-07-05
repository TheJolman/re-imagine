#!/bin/bash

# Check if run-clang-tidy is available first, then fallback to clang-tidy
if command -v run-clang-tidy &> /dev/null; then
    echo "Running run-clang-tidy..."
    run-clang-tidy "$@"
elif command -v clang-tidy &> /dev/null; then
    echo "Running clang-tidy..."
    clang-tidy "$@"
else
    echo "Error: Neither run-clang-tidy nor clang-tidy found in PATH"
    exit 1
fi