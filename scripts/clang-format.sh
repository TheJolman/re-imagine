#!/usr/bin/env bash

# Check if clang-format is available
if command -v clang-format &> /dev/null; then
    echo "Running clang-format..."
    clang-format "$@"
else
    echo "Error: clang-format not found in PATH"
    exit 1
fi