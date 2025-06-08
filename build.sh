#!/bin/bash

# PlotLib Build Script
# Convenience script for building the library

set -e

echo "=== PlotLib Build Script ==="

# Check if build directory exists
if [ -d "build" ]; then
    echo "Removing existing build directory..."
    rm -rf build
fi

# Create build directory
echo "Creating build directory..."
mkdir build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
echo "Building library and examples..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)

# Run tests
echo "Running tests..."
make test

echo ""
echo "✅ Build completed successfully!"
echo ""
echo "Available executables:"
echo "  - ./examples/centralized_demo  (Run comprehensive demo)"
echo "  - ./tests/basic_tests          (Run unit tests)"
echo ""
echo "To run the demo:"
echo "  cd build && ./examples/centralized_demo"
echo ""
echo "Generated plots will be saved to the output/ directory." 