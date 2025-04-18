cmake_minimum_required(VERSION 3.10)

# Set C++ compiler to g++
set(CMAKE_CXX_COMPILER g++)

project(CPPAlgorithms VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Add unit test executable
# Note: The source files are included through #include in the test files
add_executable(unit_tests unit_test/main.cpp)

# Set include directories
target_include_directories(unit_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/files
)

# Enable testing
enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)

# Custom target for running tests
add_custom_target(run_tests
    COMMAND unit_tests
    COMMENT "Running unit tests..."
) 