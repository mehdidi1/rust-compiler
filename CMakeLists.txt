cmake_minimum_required(VERSION 3.20)
project(rustc-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(cmake/CompilerWarnings.cmake)
include(cmake/Sanitizers.cmake)

add_subdirectory(lib/Lexer)
add_subdirectory(tools/rustc-cpp)

if(RUSTC_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
