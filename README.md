# MiniCAD

A small C++20 CAD project.

## Requirements

- A C++20-compatible compiler
- CMake 3.20 or newer

## Build

```sh
cmake -S . -B build
cmake --build build
```

## Run

```sh
./build/minicad
```

On multi-config generators such as Visual Studio, the executable is usually at
`build/Debug/minicad.exe` after a default debug build.

## Test

```sh
ctest --test-dir build --output-on-failure
```
