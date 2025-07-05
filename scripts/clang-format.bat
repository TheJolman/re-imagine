@echo off

REM Check if clang-format is available
where clang-format >nul 2>&1
if %errorlevel% == 0 (
    echo Running clang-format...
    clang-format %*
) else (
    echo Error: clang-format not found in PATH
    exit /b 1
)