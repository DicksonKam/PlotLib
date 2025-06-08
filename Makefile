# Makefile for Centralized Plotting Library Demo
# Requires Cairo graphics library (install with: brew install cairo)

CXX = g++
CXXFLAGS = -std=c++17 -I.
CAIRO_FLAGS = $(shell pkg-config --cflags --libs cairo)
TARGET = centralized_demo
SOURCES = centralized_demo.cpp plotting_library/scatter_plot.cpp

# Default target
all: $(TARGET)

# Build the centralized demo
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(CAIRO_FLAGS) $(SOURCES) -o $(TARGET)

# Clean compiled files
clean:
	rm -f $(TARGET)

# Run the demo
run: $(TARGET)
	./$(TARGET)

# Install Cairo (macOS with Homebrew)
install-deps:
	brew install cairo

.PHONY: all clean run install-deps 