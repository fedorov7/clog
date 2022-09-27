cmake_minimum_required(VERSION 3.15)

project(CLog VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules/)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Generate compile_commands.json to make it easier to work with clang based
# tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

include(AddInstallTarget)

add_library(log clog.cpp)
add_executable(tool main.cpp)
target_link_libraries(tool PRIVATE log)
add_install_target(NAME tool)
