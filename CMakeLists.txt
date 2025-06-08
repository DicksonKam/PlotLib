cmake_minimum_required(VERSION 3.12)
project(PlotLib VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED IMPORTED_TARGET cairo)
pkg_check_modules(CAIRO_SVG REQUIRED IMPORTED_TARGET cairo-svg)

# Include directories
include_directories(include)

# Library source files
set(PLOTLIB_SOURCES
    src/plot_manager.cpp
    src/scatter_plot.cpp
    src/line_plot.cpp
    src/histogram_plot.cpp
)

# Create the library
add_library(plotlib STATIC ${PLOTLIB_SOURCES})

# Link libraries
target_link_libraries(plotlib PUBLIC PkgConfig::CAIRO PkgConfig::CAIRO_SVG)
target_include_directories(plotlib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Examples
option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
install(TARGETS plotlib
    EXPORT PlotLibTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

# Export targets
install(EXPORT PlotLibTargets
    FILE PlotLibTargets.cmake
    NAMESPACE PlotLib::
    DESTINATION lib/cmake/PlotLib
)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    PlotLibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    cmake/PlotLibConfig.cmake.in
    PlotLibConfig.cmake
    INSTALL_DESTINATION lib/cmake/PlotLib
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/PlotLibConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/PlotLibConfigVersion.cmake
    DESTINATION lib/cmake/PlotLib
) 