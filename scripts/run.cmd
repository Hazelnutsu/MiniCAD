@echo off
setlocal
cd /d "%~dp0.."

cmake -S . -B build
if errorlevel 1 exit /b 1

cmake --build build --config Debug
if errorlevel 1 exit /b 1

if exist "build\Debug\minicad.exe" (
    "build\Debug\minicad.exe"
) else (
    "build\minicad.exe"
)
