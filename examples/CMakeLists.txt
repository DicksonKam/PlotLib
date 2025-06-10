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
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
    )
endfunction()

# Dynamically discover and build beginner examples
file(GLOB BEGINNER_SOURCES "beginner/[0-9][0-9]_*.cpp")
set(BEGINNER_TARGETS "")
foreach(source_file ${BEGINNER_SOURCES})
    get_filename_component(example_name ${source_file} NAME_WE)
    add_example(${example_name} ${source_file})
    list(APPEND BEGINNER_TARGETS ${example_name})
endforeach()

# Dynamically discover and build advanced examples  
file(GLOB ADVANCED_SOURCES "advanced/[0-9][0-9]_*.cpp")
set(ADVANCED_TARGETS "")
foreach(source_file ${ADVANCED_SOURCES})
    get_filename_component(base_name ${source_file} NAME_WE)
    # Create consistent naming: 01_file_name -> advanced_01_file_name
    string(REGEX REPLACE "^([0-9]+)_(.+)" "advanced_\\1_\\2" example_name ${base_name})
    add_example(${example_name} ${source_file})
    list(APPEND ADVANCED_TARGETS ${example_name})
endforeach()

# Dynamically discover and build plot_types examples
file(GLOB PLOT_TYPES_SOURCES "plot_types/[0-9][0-9]_*.cpp")
set(PLOT_TYPES_TARGETS "")
foreach(source_file ${PLOT_TYPES_SOURCES})
    get_filename_component(base_name ${source_file} NAME_WE)
    # Create consistent naming: 01_file_name -> plot_types_01_file_name
    string(REGEX REPLACE "^([0-9]+)_(.+)" "plot_types_\\1_\\2" example_name ${base_name})
    add_example(${example_name} ${source_file})
    list(APPEND PLOT_TYPES_TARGETS ${example_name})
endforeach()

# Create a target to build all beginner examples
add_custom_target(beginner_examples DEPENDS ${BEGINNER_TARGETS})

# Create a target to build all advanced examples
add_custom_target(advanced_examples DEPENDS ${ADVANCED_TARGETS})

# Create a target to build all plot_types examples
add_custom_target(plot_types_examples DEPENDS ${PLOT_TYPES_TARGETS})

# Function to generate run commands for a list of targets
function(generate_run_commands target_list output_commands)
    set(commands "")
    foreach(target ${target_list})
        list(APPEND commands "COMMAND" "${CMAKE_CURRENT_BINARY_DIR}/${target}")
    endforeach()
    set(${output_commands} ${commands} PARENT_SCOPE)
endfunction()

# Generate run commands for beginner examples
generate_run_commands("${BEGINNER_TARGETS}" BEGINNER_RUN_COMMANDS)

# Generate run commands for advanced examples  
generate_run_commands("${ADVANCED_TARGETS}" ADVANCED_RUN_COMMANDS)

# Generate run commands for plot_types examples
generate_run_commands("${PLOT_TYPES_TARGETS}" PLOT_TYPES_RUN_COMMANDS)

# Create a target to run all beginner examples
add_custom_target(run_beginner_examples
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/output
    COMMAND echo "Running beginner examples..."
    ${BEGINNER_RUN_COMMANDS}
    COMMAND echo "All beginner examples completed!"
    DEPENDS beginner_examples
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Create a target to run all advanced examples
add_custom_target(run_advanced_examples
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/output
    COMMAND echo "Running advanced examples..."
    ${ADVANCED_RUN_COMMANDS}
    COMMAND echo "All advanced examples completed!"
    DEPENDS advanced_examples
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Create a target to run all plot_types examples
add_custom_target(run_plot_types_examples
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/output
    COMMAND echo "Running plot_types examples..."
    ${PLOT_TYPES_RUN_COMMANDS}
    COMMAND echo "All plot_types examples completed!"
    DEPENDS plot_types_examples
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Create a target to run all examples
add_custom_target(run_all_examples
    COMMAND echo "Running all examples..."
    DEPENDS run_beginner_examples run_advanced_examples run_plot_types_examples
    COMMAND echo "All examples completed successfully!"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)