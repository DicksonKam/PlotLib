# Enhanced Scatter Plot Library

A C++ library for creating beautiful scatter plots with automatic axis scaling, legends, and customizable styling using Cairo graphics.

## Features

- ✅ **Automatic axis scaling and tick generation** - Smart tick placement based on data range
- ✅ **Customizable axis labels and plot titles** - Full control over plot labeling
- ✅ **Legend support for multiple data series** - Automatic legend generation in top-right corner
- ✅ **Grid lines aligned with axis ticks** - Professional-looking grid system
- ✅ **Multiple output formats** - Save as PNG or SVG
- ✅ **Series-based data management** - Organize data into named series
- ✅ **Cluster-based visualization** - Automatic coloring based on cluster labels with outlier detection
- ✅ **Subplot support** - Create multiple plots in grid layouts (2x2, 1x2, 2x1, etc.)
- ✅ **Backward compatibility** - Works with existing point-by-point addition methods

## Dependencies

- **Cairo Graphics Library** - For rendering
- **C++17 compiler** - For filesystem support

### Installation on macOS
```bash
brew install cairo
```

### Installation on Ubuntu/Debian
```bash
sudo apt-get install libcairo2-dev
```

## Building

```bash
g++ -std=c++17 -o your_program main.cpp scatter_plot.cpp `pkg-config --cflags --libs cairo cairo-svg`
```

## Quick Start

```cpp
#include "scatter_plot.h"
#include <vector>

int main() {
    // Create a scatter plot
    ScatterPlot plot(800, 600);
    
    // Set title and axis labels
    plot.set_title("My Data Visualization");
    plot.set_xlabel("X Values");
    plot.set_ylabel("Y Values");
    
    // Create data
    std::vector<Point2D> data1 = {{1, 2}, {2, 4}, {3, 6}};
    std::vector<Point2D> data2 = {{1, 1}, {2, 3}, {3, 5}};
    
    // Define styles
    PlotStyle red_style;
    red_style.r = 1.0; red_style.g = 0.0; red_style.b = 0.0;
    red_style.point_size = 4.0;
    
    PlotStyle blue_style;
    blue_style.r = 0.0; blue_style.g = 0.0; blue_style.b = 1.0;
    blue_style.point_size = 3.0;
    
    // Add data series
    plot.add_series("Series 1", data1, red_style);
    plot.add_series("Series 2", data2, blue_style);
    
    // Save the plot
    plot.save_png("my_plot.png");
    plot.save_svg("my_plot.svg");
    
    return 0;
}
```

## API Reference

### ScatterPlot Class

#### Constructor
```cpp
ScatterPlot(int width = 800, int height = 600)
```

#### Setting Labels and Title
```cpp
void set_title(const std::string& plot_title);
void set_xlabel(const std::string& x_axis_label);
void set_ylabel(const std::string& y_axis_label);
void set_labels(const std::string& plot_title, const std::string& x_axis_label, const std::string& y_axis_label);
```

#### Adding Data

**Series-based approach (recommended):**
```cpp
void add_series(const std::string& name, const std::vector<Point2D>& points, const PlotStyle& style);
void add_series_point(const std::string& series_name, double x, double y);
```

**Legacy point-by-point approach:**
```cpp
void add_point(double x, double y, const PlotStyle& style = PlotStyle());
void add_points(const std::vector<Point2D>& pts, const PlotStyle& style = PlotStyle());
```

**Cluster-based approach (for clustering results):**
```cpp
void add_cluster_data(const std::string& name, const std::vector<Point2D>& points, const std::vector<int>& cluster_labels, double point_size = 3.0, double alpha = 0.8);
void add_cluster_point(const std::string& series_name, double x, double y, int cluster_label);
```

#### Customization
```cpp
void set_bounds(double min_x, double max_x, double min_y, double max_y);  // Manual axis bounds
```

#### Saving
```cpp
bool save_png(const std::string& filename);
bool save_svg(const std::string& filename);
```

#### Utility
```cpp
void clear();  // Clear all data and reset labels
```

### SubplotManager Class

#### Constructor
```cpp
SubplotManager(int rows, int cols, int width = 1200, int height = 900, double spacing = 0.05)
```

#### Subplot Access
```cpp
ScatterPlot& get_subplot(int row, int col);  // Get subplot at position (row, col)
```

#### Configuration
```cpp
void set_main_title(const std::string& title);  // Set main title for entire figure
```

#### Saving
```cpp
bool save_png(const std::string& filename);
bool save_svg(const std::string& filename);
```

#### Layout Information
```cpp
int get_rows() const;
int get_cols() const;
```

### PlotStyle Structure

```cpp
struct PlotStyle {
    double point_size = 3.0;           // Point radius in pixels
    double r = 0.0, g = 0.0, b = 1.0;  // RGB color (0.0 to 1.0)
    double alpha = 1.0;                // Transparency (0.0 to 1.0)
    std::string label = "";            // For legend (optional)
};
```

### Point2D Structure

```cpp
struct Point2D {
    double x, y;
    Point2D(double x = 0, double y = 0);
};
```

## Examples

### Example 1: Basic Usage
See `example_usage.cpp` for a complete example showing sine, cosine, and linear data.

### Example 2: Statistical Data
See `main.cpp` for an example with multiple statistical distributions.

### Example 3: Cluster Visualization
See `cluster_example.cpp` for clustering results with automatic color assignment and outlier detection.

### Example 4: Subplot Layouts
See `subplot_example.cpp` for creating multiple plots in grid layouts with comprehensive dashboards.

### Compiling Examples
```bash
# Compile the main demonstration
g++ -std=c++17 -o enhanced_scatter_plot main.cpp scatter_plot.cpp `pkg-config --cflags --libs cairo cairo-svg`

# Compile the simple example
g++ -std=c++17 -o example example_usage.cpp scatter_plot.cpp `pkg-config --cflags --libs cairo cairo-svg`

# Compile the cluster example
g++ -std=c++17 -o cluster_demo cluster_example.cpp scatter_plot.cpp `pkg-config --cflags --libs cairo cairo-svg`

# Compile the subplot example
g++ -std=c++17 -o subplot_demo subplot_example.cpp scatter_plot.cpp `pkg-config --cflags --libs cairo cairo-svg`
```

## Advanced Features

### Automatic Axis Scaling
The library automatically determines appropriate axis bounds and tick marks based on your data range. Tick marks are placed at "nice" intervals (1, 2, 5, 10, etc.) for better readability.

### Legend Positioning
Legends are automatically positioned in the top-right corner and only appear when you have multiple named series.

### Grid Lines
Grid lines are automatically aligned with axis tick marks for a professional appearance.

### Color Customization
Colors are specified in RGB format with values from 0.0 to 1.0:
- Red: `{1.0, 0.0, 0.0}`
- Green: `{0.0, 1.0, 0.0}`
- Blue: `{0.0, 0.0, 1.0}`
- Purple: `{0.6, 0.2, 0.8}`
- Orange: `{1.0, 0.5, 0.0}`

### Cluster Visualization
The library provides specialized support for visualizing clustering results:

- **Automatic Color Assignment**: Clusters (labels 0, 1, 2, ...) get distinct colors automatically
- **Outlier Handling**: Points with label -1 are marked as red crosses and drawn in the background
- **Proper Layering**: Outliers are drawn first (background), then cluster points (foreground)
- **Smart Legend**: Automatically shows "Outliers" and "Cluster 0", "Cluster 1", etc.

#### Cluster Example
```cpp
std::vector<Point2D> points = {{1, 2}, {1.1, 2.1}, {5, 5}, {-1, -1}};
std::vector<int> labels = {0, 0, 1, -1};  // Two clusters + one outlier
plot.add_cluster_data("DBSCAN Results", points, labels);
```

### Subplot Support
Create multiple plots arranged in grid layouts for comprehensive data analysis:

- **Grid Layouts**: Support for any MxN grid (2x2, 1x2, 2x1, 3x2, etc.)
- **Independent Plots**: Each subplot is a complete plot with all features
- **Automatic Scaling**: Plots automatically scale to fit the grid
- **Main Title**: Optional main title for the entire figure
- **Configurable Spacing**: Adjust spacing between subplots

#### Subplot Example
```cpp
// Create a 2x2 subplot layout
SubplotManager subplots(2, 2, 1400, 1000);
subplots.set_main_title("Data Analysis Dashboard");

// Configure each subplot independently
auto& plot1 = subplots.get_subplot(0, 0);  // Top-left
plot1.set_labels("Distribution Analysis", "X", "Y");
plot1.add_series("Normal", normal_data, blue_style);

auto& plot2 = subplots.get_subplot(0, 1);  // Top-right
plot2.set_labels("Clustering Results", "Feature 1", "Feature 2");
plot2.add_cluster_data("DBSCAN", points, labels);

// Save the entire subplot figure
subplots.save_png("dashboard.png");
```

## Output Files

The library generates high-quality output in two formats:
- **PNG**: Raster format, good for web and presentations
- **SVG**: Vector format, scalable and good for publications

## License

This library is provided as-is for educational and research purposes. 