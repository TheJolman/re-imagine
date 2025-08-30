@echo off
setlocal enabledelayedexpansion

REM Check if clang-format is available
where clang-format >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: clang-format not found in PATH
    exit /b 1
)

REM Get the script directory to find project root
set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%.."

echo Running clang-format on C/C++ files...

REM Format all C/C++ source files in src and include directories
for /r "%PROJECT_ROOT%\src" %%f in (*.c *.h *.cpp *.hpp) do (
    if exist "%%f" (
        clang-format %* "%%f"
    )
)

for /r "%PROJECT_ROOT%\include" %%f in (*.c *.h *.cpp *.hpp) do (
    if exist "%%f" (
        clang-format %* "%%f"
    )
)

echo clang-format completed successfully!