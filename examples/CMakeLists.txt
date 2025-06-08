# Examples CMakeLists.txt

# Centralized demo example
add_executable(centralized_demo centralized_demo.cpp)
target_link_libraries(centralized_demo plotlib)

# Line plot demo example
add_executable(line_plot_demo line_plot_demo.cpp)
target_link_libraries(line_plot_demo plotlib)

# Set output directory
set_target_properties(centralized_demo line_plot_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
) 