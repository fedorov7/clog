# CLogReader test task

[![CI](https://github.com/fedorov7/clog/actions/workflows/ci.yml/badge.svg)](https://github.com/fedorov7/clog/actions/workflows/ci.yml)

Grep strings from file with filter mask matching.

# Prerequisites

* cmake
* c++ toolchain

# Build

## Windows

```sh
cmake --preset=windows
cmake --build --preset=windows-release
 ```

## Linux or OSX

```sh
cmake --preset=linux-release
cmake --build --preset=linux-release
 ```

# Usage

```sh
tool.exe 20190102.log *bbb*
 ```

# Author

Alexander Fedorov <fedorov7@gmail.com>

# License

Distributed under the Unlicense. See `LICENSE` for more information.
