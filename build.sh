#!/bin/bash

# PlotLib Build Script
# Convenience script for building the library and examples

set -e

echo "🔨 PlotLib Build Script"
echo "======================="

# Check if build directory exists
if [ -d "build" ]; then
    echo "🧹 Removing existing build directory..."
    rm -rf build
fi

# Create build directory
echo "📁 Creating build directory..."
mkdir build
cd build

# Configure with CMake
echo "⚙️  Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build library
echo "📚 Building library..."
make plotlib -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)

# Build examples
echo "📊 Building examples..."
make beginner_examples -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)
make advanced_examples -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)

# Build and run tests
echo "🧪 Building and running tests..."
make basic_tests
./tests/basic_tests

echo ""
echo "✅ Build completed successfully!"
echo ""
echo "🚀 Available commands:"
echo "  # Run all beginner examples (recommended first):"
echo "  make run_beginner_examples"
echo ""
echo "  # Run all advanced examples:"
echo "  make run_advanced_examples"
echo ""
echo "  # Run everything:"
echo "  make run_all_examples"
echo ""
echo "📊 Individual examples:"
echo "  ./examples/01_first_scatter_plot"
echo "  ./examples/02_colors_and_multiple_series"
echo "  ./examples/03_first_line_plot"
echo "  ./examples/04_first_histogram"
echo "  ./examples/05_simple_subplots"
echo "  ./examples/advanced_01_custom_styling"
echo "  ./examples/advanced_02_complex_dashboards"
echo "  ./examples/advanced_03_performance_optimization"
echo ""
echo "📁 Generated plots will be saved to ../output/ directory"
echo "📖 See examples/README.md for detailed documentation"
echo ""
echo "🎯 Quick start: make run_beginner_examples" 