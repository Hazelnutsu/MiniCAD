#!/usr/bin/env sh
set -eu

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
repository_dir=$(dirname "$script_dir")
build_dir=${1:-build}
configuration=${2:-Debug}

case "$build_dir" in
    /*) build_path=$build_dir ;;
    *) build_path="$repository_dir/$build_dir" ;;
esac

cmake -S "$repository_dir" -B "$build_path"
cmake --build "$build_path" --config "$configuration"

if [ -x "$build_path/$configuration/minicad" ]; then
    executable="$build_path/$configuration/minicad"
elif [ -x "$build_path/minicad" ]; then
    executable="$build_path/minicad"
else
    printf '%s\n' "Could not find the MiniCAD executable in $build_path." >&2
    exit 1
fi

exec "$executable"
