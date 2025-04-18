# CMake Setup for C++ Algorithms Project

This document explains how to build and run the project using CMake.

## Prerequisites

- CMake 3.10 or higher
- A C++17 compliant compiler (GCC, Clang, MSVC)
- VS Code with the following extensions (recommended):
  - C/C++ (Microsoft)
  - CMake Tools
  - CMake (twxs)

## Building the Project

### Command Line

```bash
# Configure the project
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build the project
cmake --build build --config Debug

# Run the tests
cd build && ctest --verbose
```

### VS Code Tasks

Several VS Code tasks have been created to make it easier to work with CMake:

1. **CMake: configure** - Configures the CMake project
2. **CMake: build** - Builds the project
3. **CMake: run tests** - Runs all the tests
4. **CMake: clean** - Cleans the build

To use these tasks, open the command palette (Ctrl+Shift+P) and type "Tasks: Run Task", then select the desired task.

## Debugging

A launch configuration has been created for debugging the unit tests:

1. Select the "(CMake) Debug Unit Tests" configuration from the drop-down menu in the Run and Debug view
2. Press F5 to start debugging

## Project Structure

- `src/` - Source files
- `unit_test/` - Unit test files
  - `files/` - Individual test files
  - `main.cpp` - Main test runner

## Adding New Files

When adding new source files:

1. Add them to the `SOURCE_FILES` list in the main `CMakeLists.txt` file
2. Include them in `unit_test/main.cpp` if they have corresponding tests

## Notes

- This is a header-only library setup, where the implementation is in `.cpp` files but they are used as headers.
- The tests include the source files directly rather than linking against a compiled library. 