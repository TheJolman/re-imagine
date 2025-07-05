@echo off

REM Check if clang-tidy is available
where clang-tidy >nul 2>&1
if %errorlevel% == 0 (
    echo Running clang-tidy...
    clang-tidy -p build %*
) else (
    echo Error: clang-tidy not found in PATH
    exit /b 1
)
