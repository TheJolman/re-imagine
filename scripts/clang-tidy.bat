@echo off

REM Check if run-clang-tidy is available first, then fallback to clang-tidy
where run-clang-tidy >nul 2>&1
if %errorlevel% == 0 (
    echo Running run-clang-tidy...
    run-clang-tidy %*
) else (
    echo Error: run-clang-tidy not found in PATH
    exit /b 1
)
