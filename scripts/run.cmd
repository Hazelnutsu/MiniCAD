@echo off
setlocal

set "REPOSITORY_DIR=%~dp0.."
if "%~1"=="" (
    set "BUILD_DIR=%REPOSITORY_DIR%\build"
) else (
    set "BUILD_DIR=%~1"
)
if "%~2"=="" (
    set "CONFIGURATION=Debug"
) else (
    set "CONFIGURATION=%~2"
)

cmake -S "%REPOSITORY_DIR%" -B "%BUILD_DIR%"
if errorlevel 1 exit /b 1

cmake --build "%BUILD_DIR%" --config "%CONFIGURATION%"
if errorlevel 1 exit /b 1

if exist "%BUILD_DIR%\%CONFIGURATION%\minicad.exe" (
    set "EXECUTABLE=%BUILD_DIR%\%CONFIGURATION%\minicad.exe"
) else if exist "%BUILD_DIR%\minicad.exe" (
    set "EXECUTABLE=%BUILD_DIR%\minicad.exe"
) else (
    echo Could not find the MiniCAD executable in "%BUILD_DIR%" 1>&2
    exit /b 1
)

"%EXECUTABLE%"
exit /b %errorlevel%
