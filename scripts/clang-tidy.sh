#!/usr/bin/env sh

# usage: if run empty, tidy all .cpp files in src/tests
# if given an argument, tidy just that file
(
    if [ -z $1 ]; then
        clang-tidy -p build $(find src -type f -iname "*.cpp" &&
                              find tests -type f -iname "*.cpp" &&
                              find benchmarks -type f -iname "*.cpp")
    else
        clang-tidy -p build $@
    fi
)
