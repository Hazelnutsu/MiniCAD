# MiniCAD

A small C++20 console CAD project for working with 2D points.

## Requirements

- CMake 3.20 or newer
- A C++20-compatible compiler

## Quick start

From the repository root, configure and build the project:

```sh
cmake -S . -B build
cmake --build build --config Debug
```

The `--config Debug` option selects Debug with multi-configuration generators
such as Visual Studio and is harmless with single-configuration generators.

Run MiniCAD with the launcher for your shell. Each launcher configures and
builds the project before starting the interactive program, and automatically
finds the right executable location for single- or multi-configuration builds.

Windows (PowerShell or Command Prompt):

```bat
scripts\run.cmd
```

PowerShell users can also run the PowerShell launcher:

```powershell
.\scripts\run.ps1
```

macOS/Linux:

```sh
sh scripts/run.sh
```

Pass a build directory and configuration as optional arguments when needed:

```bat
scripts\run.cmd build-release Release
```

```powershell
.\scripts\run.ps1 build-release Release
```

```sh
sh scripts/run.sh build-release Release
```

MiniCAD asks how many points to enter, then reads each point's `x` and `y`
coordinates. For example:

```text
How many points would you like to enter? 2
Enter x and y for point 1: 0 0
Enter x and y for point 2: 10 5
Points entered:
Point: (0, 0)
Point: (10, 5)
```

## Test

Build the project first, then run the test suite:

```sh
ctest --test-dir build -C Debug --output-on-failure
```

## Useful CMake commands

```sh
# Reconfigure after changing CMakeLists.txt
cmake -S . -B build

# Build one target
cmake --build build --target minicad --config Debug

# Run tests verbosely
ctest --test-dir build -C Debug -V
```

Build directories such as `build/` are intentionally ignored by Git.
