# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Developer Preferences

**Code Consistency Philosophy:**
- Maintain strict consistency across all functions, class declarations, and implementations throughout the entire project
- Eliminate duplicate or overlapping functionality - consolidate similar functions into single, parameterized functions
- Prefer centralized control over discrete, scattered implementations for better consistency management
- Avoid hard-coding values - use parameters and embedded variables instead
- These preferences apply across all projects and codebases

**Function Parameter Ordering Standard:**
For ALL library functions, maintain consistent parameter order:
1. **Data values first** - The core data being processed (x_values, y_values, counts, values, etc.)
2. **Naming second** - Labels, names, identifiers for legend and axis labels
3. **Colors last** - Visual styling parameters (color_name, color_names)

Examples:
```cpp
// ✅ CORRECT ordering: data → naming → colors
add_scatter(x_values, y_values, "Series Name", "red");
add_line(x_values, y_values, "Line Name", "blue"); 
add_histogram(values, "Histogram Name", "green");
add_vertical_line(x_value, "Line Label", "red");

// ❌ INCORRECT - don't put naming before data
add_scatter("Series Name", x_values, y_values, "red"); // WRONG ORDER
```

This ordering ensures intuitive, consistent API usage across all plot types and operations.

## Build Commands

### Quick Build and Test

**Linux/macOS:**
```bash
./build.sh
```

**Windows:**
```powershell
# Use Docker (recommended)
docker compose up plotlib

# OR manual CMake (if Cairo is installed)
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target plotlib
```

The build.sh script automatically:
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
make plot_types_examples        # Build plot_types examples
make basic_tests               # Build and run tests
```

### Running Examples

**IMPORTANT: Always run executables from the project root directory (not from build/)**

```bash
# Run all examples (recommended)
cd build
make run_beginner_examples     # Run all beginner examples
make run_advanced_examples     # Run all advanced examples
make run_plot_types_examples   # Run all plot_types examples
make run_all_examples          # Run everything

# Run individual examples (from project root)
./build/examples/01_first_scatter_plot      # Basic scatter plot
./build/examples/02_colors_and_multiple_series  # Colors and styling
./build/examples/03_first_line_plot         # Basic line plot
./build/examples/04_first_histogram         # Continuous histograms
./build/examples/05_simple_subplots         # Subplot layouts
./build/examples/06_discrete_histograms     # Discrete categorical histograms
./build/examples/07_empty_plots            # Empty plot handling
./build/examples/advanced_01_custom_styling_and_advanced_features  # Advanced styling
./build/examples/plot_types_01_line_plot    # Comprehensive line plot API
./build/examples/plot_types_02_scatter_plot # Comprehensive scatter plot API
```

**Execution Rules:**
- ✅ **DO**: Run from project root: `./build/examples/example_name`
- ❌ **DON'T**: Run from build directory: `cd build && ./examples/example_name`
- 📁 All output files are saved to `output/` directory
- 🚨 **CRITICAL**: ALWAYS execute all binaries from the project root directory, never from within the build directory

### Docker Commands
```bash
docker build -t plotlib .
docker run --rm -v ./output:/app/output plotlib /app/build/examples/01_first_scatter_plot
docker compose up plotlib      # Run all examples (simplest approach)
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
  - **HistogramPlot** - Implements both continuous and discrete histograms:
    - Continuous: automatic/manual binning for numeric data
    - Discrete: categorical data with individual colors per category
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