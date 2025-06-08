# Examples CMakeLists.txt

# Centralized demo example
add_executable(centralized_demo centralized_demo.cpp)
target_link_libraries(centralized_demo plotlib)

# Set output directory
set_target_properties(centralized_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
) 