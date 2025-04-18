# Collect all test files
file(GLOB TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/files/*.cpp
)

# Add test executable
add_executable(unit_tests 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# Set include directories for unit tests
target_include_directories(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/files
)

# Link against the main library
target_link_libraries(unit_tests PRIVATE cpp_algorithms)

# Register test
add_test(NAME UnitTests COMMAND unit_tests)

# Define a custom target for running tests only
add_custom_target(run_tests_only
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../unit_tests
    COMMENT "Running unit tests..."
    DEPENDS unit_tests
) 