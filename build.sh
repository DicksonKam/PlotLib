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
# Dynamically list all built examples
if [ -d "examples" ]; then
    # List beginner examples (numbered)
    for example in examples/[0-9][0-9]_*; do
        if [ -x "$example" ]; then
            echo "  ./$example"
        fi
    done
    # List advanced examples  
    for example in examples/advanced_*; do
        if [ -x "$example" ]; then
            echo "  ./$example"
        fi
    done
else
    echo "  (No examples directory found - run build first)"
fi
echo ""
echo "📁 Generated plots will be saved to output/ directory"
echo "📖 See examples/README.md for detailed documentation"
echo ""
echo "🎯 Quick start: make run_beginner_examples" 