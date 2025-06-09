# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Developer Preferences

**Code Consistency Philosophy:**
- Maintain strict consistency across all functions, class declarations, and implementations throughout the entire project
- Eliminate duplicate or overlapping functionality - consolidate similar functions into single, parameterized functions
- Prefer centralized control over discrete, scattered implementations for better consistency management
- Avoid hard-coding values - use parameters and embedded variables instead
- These preferences apply across all projects and codebases

## Build Commands

### Quick Build and Test
```bash
./build.sh
```
This script automatically:
- Removes existing build directory
- Configures with CMake in Release mode
- Builds the library and all examples
- Runs tests and displays results
- Shows available commands for running examples

### Manual Build Process
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make plotlib                    # Build library only
make beginner_examples          # Build beginner examples
make advanced_examples          # Build advanced examples
make basic_tests               # Build and run tests
```

### Running Examples
```bash
cd build
make run_beginner_examples     # Run all 5 beginner examples
make run_advanced_examples     # Run all 4 advanced examples
make run_all_examples          # Run everything
./examples/01_first_scatter_plot  # Run individual example
```

### Docker Commands
```bash
docker build -t plotlib .
docker run --rm -v ./output:/app/output plotlib /app/build/examples/01_first_scatter_plot
docker-compose up plotlib      # Run all examples
docker-compose up plotlib-dev  # Development shell
docker-compose up plotlib-test # Tests only
```

### Testing
```bash
cd build
./tests/basic_tests            # Run tests directly
ctest                          # Use CTest
```

## Architecture Overview

PlotLib is a C++ plotting library built on Cairo graphics with a hierarchical inheritance-based architecture:

### Core Architecture
- **PlotManager** (base class) - Handles all common plotting functionality including axes, legends, titles, data bounds, transformations, and rendering coordination
- **Specific plot types** inherit from PlotManager:
  - **ScatterPlot** - Implements scatter plots with multiple marker types
  - **LinePlot** - Implements line plots with optional markers and line styles  
  - **HistogramPlot** - Implements histograms with automatic/manual binning
- **SubplotManager** - Manages multiple plots in grid layouts

### Key Design Patterns
1. **Template-based subplot creation** - `SubplotManager::get_subplot<PlotType>(row, col)` creates specific plot types dynamically
2. **Inheritance hierarchy** - All plot types inherit common functionality from PlotManager but implement their own `draw_data()` method
3. **Data structure separation** - Clear separation between data structures (`Point2D`, `DataSeries`, `ClusterSeries`) and rendering logic
4. **Beginner-friendly API** - Simple methods like `add_scatter()`, `add_line()`, `add_histogram()` with automatic styling alongside advanced PlotStyle configurations

### Data Flow
1. Data is stored in plot-specific collections (`data_series`, `cluster_series`, `histogram_series`)
2. `calculate_bounds()` determines axis ranges from all data
3. `transform_point()` converts data coordinates to screen coordinates
4. `draw_data()` (implemented by each plot type) renders the actual data visualization
5. Common elements (axes, legends, titles) are rendered by PlotManager base class

### Key Files
- `include/plot_manager.h` - Core base class with all shared functionality
- `include/scatter_plot.h`, `include/line_plot.h`, `include/histogram_plot.h` - Specific plot implementations  
- `src/*.cpp` - Implementation files corresponding to headers
- `examples/` - Comprehensive examples showing beginner and advanced usage patterns

### Cairo Integration
The library uses Cairo for cross-platform rendering with PNG and SVG output support. All rendering happens through Cairo contexts passed down through the inheritance hierarchy.

### Color Management
- Automatic color cycling for multiple series using centralized `auto_colors` array
- Named color support ("red", "blue", etc.) converted to RGB via `color_to_style()`
- Cluster visualization uses predefined color palettes for different cluster labels