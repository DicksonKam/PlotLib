# PlotLib Examples

This directory contains comprehensive examples demonstrating all features of PlotLib, organized by skill level.

## 🎯 Quick Start

```bash
# Build all examples
cd build
make

# Run all beginner examples
make run_beginner_examples

# Or run individual examples
./examples/01_first_scatter_plot
./examples/02_colors_and_multiple_series
# ... etc
```

## 📚 Example Categories

### 🟢 Beginner Examples (`beginner/`)

Perfect for newcomers to plotting or PlotLib. Each example focuses on one concept with detailed comments.

| Example | Description | What You'll Learn |
|---------|-------------|-------------------|
| `01_first_scatter_plot.cpp` | Your very first plot | Basic plotting workflow |
| `02_colors_and_multiple_series.cpp` | Colors and multiple data series | Color usage, automatic vs manual coloring |
| `03_first_line_plot.cpp` | Line plots and mathematical functions | Time series, functions, X/Y vectors |
| `04_first_histogram.cpp` | Data distributions | Histograms, bin control, comparisons |
| `05_simple_subplots.cpp` | Multiple plots in one figure | Subplot layouts, dashboards |

**Generated plots:** 14 example plots showing all basic functionality

### 🔴 Advanced Examples (`advanced/`)

For experienced developers who want professional-quality visualizations, performance optimization, and complex data analysis.

| Example | Description | What You'll Learn |
|---------|-------------|-------------------|
| `01_custom_styling_and_advanced_features.cpp` | Advanced styling and customization | Precise RGB control, legend management, cluster analysis |
| `02_complex_dashboards_and_layouts.cpp` | Professional dashboard design | Executive dashboards, scientific layouts, design principles |
| `03_performance_optimization_and_large_datasets.cpp` | Performance and scalability | Large datasets, memory optimization, benchmarking |

**Generated plots:** 12+ advanced plots demonstrating professional techniques

## 🎨 What Each Example Demonstrates

### 01 - First Scatter Plot
- Creating Point2D data
- Basic plot setup (dimensions, labels)
- Adding data with automatic styling
- Saving plots as PNG

**Output:** `01_first_scatter_plot.png`

### 02 - Colors and Multiple Series
- Automatic color assignment
- Manual color specification
- Multiple data series on one plot
- Color showcase with all available colors

**Output:** `02_colors_and_multiple_series.png`, `02_color_showcase.png`

### 03 - Line Plots
- Line plots from X/Y vectors (easiest method)
- Mathematical functions (sin, cos)
- Time series data
- Multiple lines on same plot

**Output:** `03_temperature_line.png`, `03_math_functions.png`, `03_growth_trend.png`

### 04 - Histograms
- Basic histogram creation
- Controlling bin counts
- Comparing distributions
- Real-world data examples

**Output:** `04_test_scores.png`, `04_iq_10_bins.png`, `04_iq_30_bins.png`, `04_group_comparison.png`, `04_loading_times.png`

### 05 - Subplots
- 2x2 dashboard layout
- 1x3 horizontal comparison
- 3x1 vertical analysis
- Mixing different plot types

**Output:** `05_first_dashboard.png`, `05_horizontal_layout.png`, `05_vertical_layout.png`

## 🚀 Running Examples

### Method 1: Build and Run All
```bash
cd build
# Build and run beginner examples
make beginner_examples
make run_beginner_examples

# Build and run advanced examples
make advanced_examples
make run_advanced_examples

# Or run everything
make run_all_examples
```

### Method 2: Individual Compilation
```bash
g++ -std=c++17 -I./include examples/beginner/01_first_scatter_plot.cpp \
    -L./build -lplotlib `pkg-config --cflags --libs cairo cairo-svg` \
    -o my_example
./my_example
```

### Method 3: Using CMake
```bash
cd build
make 01_first_scatter_plot
./examples/01_first_scatter_plot
```

## 📊 Generated Output

All examples save their plots to the `output/` directory. After running all examples, you'll have:

**Beginner Examples (14 plots):**
- **3 plot types**: scatter, line, histogram
- **Various layouts**: single plots and subplots
- **Color demonstrations**: automatic and manual coloring
- **Real-world examples**: test scores, temperature, loading times

**Advanced Examples (12+ plots):**
- **Professional styling**: Custom RGB colors, precise control
- **Complex dashboards**: Executive (3x3), scientific (4x2) layouts
- **Performance optimization**: Large datasets, memory management
- **Advanced features**: Cluster analysis, statistical visualization

## 🎓 Learning Path

1. **Start with `01_first_scatter_plot.cpp`** - Get familiar with the basic workflow
2. **Try `02_colors_and_multiple_series.cpp`** - Learn about colors and multiple data
3. **Explore `03_first_line_plot.cpp`** - Understand line plots and functions
4. **Study `04_first_histogram.cpp`** - Master distribution visualization
5. **Practice with `05_simple_subplots.cpp`** - Create complex layouts

## 🔧 Customization Ideas

Try modifying the examples:

### Easy Modifications
- Change colors: `"blue"` → `"red"`, `"green"`, etc.
- Adjust plot dimensions: `(800, 600)` → `(1200, 800)`
- Modify data: Add your own points or values
- Change titles and labels

### Intermediate Modifications
- Add more data series to existing plots
- Try different subplot layouts: `(3, 2)`, `(4, 1)`, etc.
- Experiment with different bin counts in histograms
- Mix different plot types in subplots

### Advanced Modifications
- Create your own data generators
- Implement custom color schemes
- Build interactive dashboards
- Add statistical analysis

## 🆘 Troubleshooting

### Common Issues

**"No such file or directory"**
- Make sure you built the library: `./build.sh`
- Run from the project root directory

**"Cannot find -lplotlib"**
- Build the library first: `cd build && make`
- Check that `libplotlib.a` exists in `build/`

**"output/ folder doesn't exist"**
- Create it: `mkdir -p output`
- Or run from project root where it already exists

**Compilation errors**
- Make sure Cairo is installed: `brew install cairo` (macOS) or `sudo apt install libcairo2-dev` (Ubuntu)
- Use C++17: `-std=c++17`

### Getting Help

1. Check the [Beginner Tutorial](../docs/tutorial/beginner.md)
2. Read the [API Reference](../docs/api/README.md)
3. Look at working examples in this directory
4. Open an issue on GitHub

## 📝 Example Template

Use this template to create your own examples:

```cpp
#include "plotlib/scatter_plot.h"  // or line_plot.h, histogram_plot.h
#include <vector>
#include <iostream>

int main() {
    std::cout << "Creating my custom plot..." << std::endl;
    
    // 1. Create your data
    std::vector<plotlib::Point2D> data = {{1, 2}, {3, 4}};
    
    // 2. Create plot
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels("My Plot", "X Axis", "Y Axis");
    
    // 3. Add data
    plot.add_data("My Data", data, "blue");
    
    // 4. Save
    bool success = plot.save_png("output/my_plot.png");
    
    if (success) {
        std::cout << "✅ Plot saved successfully!" << std::endl;
    } else {
        std::cout << "❌ Failed to save plot" << std::endl;
    }
    
    return 0;
}
```

## 🎯 Next Steps

After mastering these examples:

1. **Create your own plots** with real data
2. **Explore advanced features** in the API reference
3. **Build dashboards** for your projects
4. **Contribute examples** to help other users

Happy plotting! 📊✨ 