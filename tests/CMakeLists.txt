# Tests CMakeLists.txt

# Find testing framework (we'll use a simple approach for now)
# In the future, you might want to use Google Test or Catch2

# Basic test executable
add_executable(basic_tests basic_tests.cpp)

# Link against the plotlib library
target_link_libraries(basic_tests PRIVATE plotlib)

# Set C++ standard for tests
target_compile_features(basic_tests PRIVATE cxx_std_17)

# Add compiler warnings for better code quality
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(basic_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Register the test with CTest
add_test(NAME basic_tests COMMAND basic_tests)

# Set test properties
set_tests_properties(basic_tests PROPERTIES 
    TIMEOUT 30
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
) 