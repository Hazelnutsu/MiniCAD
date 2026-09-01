# MiniCAD

A small C++20 console project for working with 2D geometry.

## Requirements

- CMake 3.20 or newer
- A C++20-compatible compiler

## Run

Linux:

```sh
sh scripts/run.sh
```

Windows:

```bat
.\scripts\run.cmd
```

The script configures the project, builds it, and runs MiniCAD.

## Test

```sh
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```
