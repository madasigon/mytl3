cmake_minimum_required(VERSION 3.10)
project(CPPAlgorithms VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Compile options
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra)
endif()

# Define all source files
set(SOURCE_FILES
    src/base.cpp
    src/binary_search.cpp
    src/container.cpp
    src/convenience.cpp
    src/corasick.cpp
    src/geom.cpp
    src/instant_zero.cpp
    src/io.cpp
    src/modulo.cpp
    src/modulo_typesafe.cpp
    src/pow.cpp
    src/recursion.cpp
    src/segtree.cpp
    src/tracker.cpp
    src/trie.cpp
)

# Create the main library (header-only)
add_library(cpp_algorithms INTERFACE)
target_include_directories(cpp_algorithms INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Enable testing
enable_testing()

# Add unit_test subdirectory
add_subdirectory(unit_test)

# Custom target for building and running tests
add_custom_target(run_tests
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unit_tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/unit_test/unit_tests
    COMMENT "Building and running tests..."
) 