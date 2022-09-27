# CLogReader test task

Grep strings from file with filter mask matching.

# Prerequisites

* cmake
* c++ toolchain

# Build

## Windows

cmake --preset=windows-release
cmake --build --preset=windows-release


## Linux or OSX

cmake --preset=linux-release
cmake --build --preset=linux-release

# Usage

tool.exe 20190102.log *bbb*
