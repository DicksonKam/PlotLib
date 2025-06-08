# Tests CMakeLists.txt

# Find testing framework (we'll use a simple approach for now)
# In the future, you might want to use Google Test or Catch2

# Basic test executable
add_executable(basic_tests basic_tests.cpp)
target_link_libraries(basic_tests plotlib)

# Add test
add_test(NAME BasicTests COMMAND basic_tests)

# Set output directory
set_target_properties(basic_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
) 