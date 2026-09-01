#!/usr/bin/env sh
set -eu

cd "$(dirname "$0")/.."

cmake -S . -B build
cmake --build build
exec ./build/minicad
