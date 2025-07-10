cmake_minimum_required(VERSION 3.13)

project(llvm-nm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib)
add_subdirectory(tools)
# add_subdirectory(unittests)

set(NM_TARGET "LLVM" CACHE STRING "Semicolon-separated list of formats to support")

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

