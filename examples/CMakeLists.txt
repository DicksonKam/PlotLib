# CMakeLists.txt for PlotLib Examples
cmake_minimum_required(VERSION 3.12)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo cairo-svg)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CAIRO_INCLUDE_DIRS})

# Link directories
link_directories(${CAIRO_LIBRARY_DIRS})

# Compiler flags
add_compile_options(${CAIRO_CFLAGS_OTHER})

# Function to create an example executable
function(add_example example_name source_file)
    add_executable(${example_name} ${source_file})
    target_link_libraries(${example_name} plotlib ${CAIRO_LIBRARIES})
    set_target_properties(${example_name} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
endfunction()

# Beginner Examples
add_example(01_first_scatter_plot beginner/01_first_scatter_plot.cpp)
add_example(02_colors_and_multiple_series beginner/02_colors_and_multiple_series.cpp)
add_example(03_first_line_plot beginner/03_first_line_plot.cpp)
add_example(04_first_histogram beginner/04_first_histogram.cpp)
add_example(05_simple_subplots beginner/05_simple_subplots.cpp)

# Advanced Examples
add_example(advanced_01_custom_styling advanced/01_custom_styling_and_advanced_features.cpp)
add_example(advanced_02_complex_dashboards advanced/02_complex_dashboards_and_layouts.cpp)
add_example(advanced_03_performance_optimization advanced/03_performance_optimization_and_large_datasets.cpp)
add_example(advanced_04_reference_lines advanced/04_reference_lines_and_annotations.cpp)

# Create a target to build all beginner examples
add_custom_target(beginner_examples
    DEPENDS 
        01_first_scatter_plot
        02_colors_and_multiple_series
        03_first_line_plot
        04_first_histogram
        05_simple_subplots
)

# Create a target to build all advanced examples
add_custom_target(advanced_examples
    DEPENDS 
        advanced_01_custom_styling
        advanced_02_complex_dashboards
        advanced_03_performance_optimization
        advanced_04_reference_lines
)

# Create a target to run all beginner examples
add_custom_target(run_beginner_examples
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/output
    COMMAND echo "Running beginner examples..."
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/01_first_scatter_plot
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/02_colors_and_multiple_series
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/03_first_line_plot
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/04_first_histogram
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/05_simple_subplots
    COMMAND echo "All beginner examples completed!"
    DEPENDS beginner_examples
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Create a target to run all advanced examples
add_custom_target(run_advanced_examples
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/output
    COMMAND echo "Running advanced examples..."
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/advanced_01_custom_styling
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/advanced_02_complex_dashboards
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/advanced_03_performance_optimization
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/advanced_04_reference_lines
    COMMAND echo "All advanced examples completed!"
    DEPENDS advanced_examples
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Create a target to run all examples
add_custom_target(run_all_examples
    COMMAND echo "Running all examples..."
    DEPENDS run_beginner_examples run_advanced_examples
    COMMAND echo "All examples completed successfully!"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Set output directory for all examples
set_target_properties(
    01_first_scatter_plot
    02_colors_and_multiple_series
    03_first_line_plot
    04_first_histogram
    05_simple_subplots
    advanced_01_custom_styling
    advanced_02_complex_dashboards
    advanced_03_performance_optimization
    advanced_04_reference_lines
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
) 