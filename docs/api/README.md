# API Reference

Complete reference for all PlotLib classes and functions.

## 📊 Core Classes

### ScatterPlot

Perfect for showing relationships between variables and cluster analysis.

#### Constructor
```cpp
ScatterPlot(int width = 800, int height = 600)
```

#### Beginner-Friendly Methods
```cpp
// Add data with automatic coloring
void add_data(const std::string& name, const std::vector<Point2D>& data);

// Add data with custom color
void add_data(const std::string& name, const std::vector<Point2D>& data, 
              const std::string& color_name);

// Add cluster data with automatic coloring
void add_clusters(const std::vector<Point2D>& data, const std::vector<int>& labels);
```

#### Advanced Methods
```cpp
// Add series with full style control
void add_series(const std::string& name, const std::vector<Point2D>& points, 
                const PlotStyle& style);

// Add cluster data with full control
void add_cluster_data(const std::string& name, const std::vector<Point2D>& points, 
                      const std::vector<int>& cluster_labels, 
                      double point_size = 3.0, double alpha = 0.8);

// Legacy point-by-point methods
void add_point(double x, double y, const PlotStyle& style = PlotStyle());
void add_points(const std::vector<Point2D>& pts, const PlotStyle& style = PlotStyle());
```

### LinePlot

Ideal for time series data and mathematical functions.

#### Constructor
```cpp
LinePlot(int width = 800, int height = 600)
```

#### Beginner-Friendly Methods
```cpp
// Add line with automatic coloring
void add_line(const std::string& name, const std::vector<Point2D>& data);

// Add line with custom color
void add_line(const std::string& name, const std::vector<Point2D>& data, 
              const std::string& color_name);

// Add line from X and Y vectors (easiest method!)
void add_line(const std::string& name, const std::vector<double>& x_values, 
              const std::vector<double>& y_values, 
              const std::string& color_name = "auto");
```

#### Advanced Methods
```cpp
// Add series with full style control
void add_series(const std::string& name, const std::vector<Point2D>& points, 
                const PlotStyle& style);

// Line style configuration
void set_default_line_style(LineStyle style);
void set_default_line_width(double width);
void set_show_markers(bool enabled);
void set_default_marker_type(MarkerType marker_type);
```

#### Line Styles
```cpp
enum class LineStyle {
    SOLID,    // ——————————
    DASHED,   // — — — — —
    DOTTED    // ··········
};
```

### HistogramPlot

Great for understanding data distributions.

#### Constructor
```cpp
HistogramPlot(int width = 800, int height = 600)
```

#### Beginner-Friendly Methods
```cpp
// Add histogram with automatic styling
void add_histogram(const std::string& name, const std::vector<double>& data, 
                   int bins = 0);  // 0 = automatic bin count

// Add histogram with custom color
void add_histogram(const std::string& name, const std::vector<double>& data, 
                   const std::string& color_name, int bins = 0);
```

#### Advanced Methods
```cpp
// Add data with full control
void add_data(const std::string& name, const std::vector<double>& data, 
              const PlotStyle& style, int bins = 0);

// Distribution options
void set_normalize(bool normalize);     // Probability density
void set_cumulative(bool cumulative);   // Cumulative distribution
void set_default_bin_count(int count);  // Default for automatic binning

// Statistics
std::pair<double, double> get_statistics(const std::string& series_name) const;
```

### SubplotManager

Create multiple plots in grid layouts.

#### Constructor
```cpp
SubplotManager(int rows, int cols, int width = 1200, int height = 900, 
               double spacing = 0.05)
```

#### Methods
```cpp
// Get subplot at position (row, col)
template<typename PlotType>
PlotType& get_subplot(int row, int col);

// Configuration
void set_main_title(const std::string& title);

// Saving
bool save_png(const std::string& filename);
bool save_svg(const std::string& filename);

// Layout info
int get_rows() const;
int get_cols() const;
```

## 🎨 Styling System

### PlotStyle Structure
```cpp
struct PlotStyle {
    double point_size = 3.0;           // Point radius in pixels
    double line_width = 2.0;           // Line width in pixels
    double r = 0.0, g = 0.0, b = 1.0;  // RGB color (0.0 to 1.0)
    double alpha = 0.8;                // Transparency (0.0 to 1.0)
    std::string label = "";            // For legend (optional)
};
```

### Color Utility
```cpp
// Convert color name to PlotStyle
static PlotStyle color_to_style(const std::string& color_name, 
                                double point_size = 3.0, 
                                double line_width = 2.0);
```

**Available color names:**
- `"red"`, `"blue"`, `"green"`, `"orange"`
- `"purple"`, `"cyan"`, `"magenta"`, `"yellow"`
- `"black"`, `"gray"` (or `"grey"`)

### MarkerType Enum
```cpp
enum class MarkerType {
    CIRCLE,     // ●
    SQUARE,     // ■
    TRIANGLE,   // ▲
    DIAMOND,    // ♦
    CROSS,      // ✕
    PLUS        // +
};
```

## 📐 Data Structures

### Point2D
```cpp
struct Point2D {
    double x, y;
    Point2D(double x = 0, double y = 0);
};
```

### ClusterPoint
```cpp
struct ClusterPoint {
    Point2D point;
    int cluster_label;  // -1 for outliers
};
```

## 🎛️ Common Methods (All Plot Types)

### Labels and Titles
```cpp
void set_title(const std::string& plot_title);
void set_xlabel(const std::string& x_axis_label);
void set_ylabel(const std::string& y_axis_label);
void set_labels(const std::string& plot_title, 
                const std::string& x_axis_label, 
                const std::string& y_axis_label);
```

### Bounds Control
```cpp
void set_bounds(double min_x, double max_x, double min_y, double max_y);
void auto_bounds();  // Reset to automatic bounds
```

### Legend Control
```cpp
void set_legend_enabled(bool enabled);
void hide_legend_item(const std::string& series_name);
void show_legend_item(const std::string& series_name);
void show_all_legend_items();
```

### Saving
```cpp
bool save_png(const std::string& filename);
bool save_svg(const std::string& filename);
```

### Utility
```cpp
void clear();  // Clear all data and reset labels
```

## 🔧 Advanced Features

### Cluster Visualization
Automatic color assignment for clustering results:
- Clusters (labels 0, 1, 2, ...) get distinct colors
- Outliers (label -1) are shown as red crosses
- Proper layering: outliers in background, clusters in foreground

### Automatic Axis Scaling
- Smart tick placement at "nice" intervals (1, 2, 5, 10, etc.)
- Automatic bounds based on data range
- Grid lines aligned with tick marks

### Legend System
- Automatic positioning in top-right corner
- Only appears when multiple named series exist
- Selective hiding/showing of legend items
- Proper handling of cluster data

## 📊 Usage Patterns

### Pattern 1: Quick Plotting
```cpp
plotlib::ScatterPlot plot(800, 600);
plot.set_labels("Title", "X", "Y");
plot.add_data("Data", points, "blue");
plot.save_png("output.png");
```

### Pattern 2: Multiple Series Comparison
```cpp
plotlib::LinePlot plot(800, 600);
plot.set_labels("Comparison", "Time", "Value");
plot.add_line("Series A", data_a, "blue");
plot.add_line("Series B", data_b, "red");
plot.add_line("Series C", data_c, "green");
plot.save_png("comparison.png");
```

### Pattern 3: Distribution Analysis
```cpp
plotlib::HistogramPlot plot(800, 600);
plot.set_labels("Distribution", "Value", "Frequency");
plot.add_histogram("Before", before_data, "red", 20);
plot.add_histogram("After", after_data, "green", 20);
plot.save_png("distribution.png");
```

### Pattern 4: Dashboard Creation
```cpp
plotlib::SubplotManager manager(2, 2, 1200, 900);
manager.set_main_title("Analysis Dashboard");

auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
auto& line = manager.get_subplot<plotlib::LinePlot>(0, 1);
auto& hist = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 1);

// Configure each subplot...
manager.save_png("dashboard.png");
```

## 🚨 Error Handling

Most methods return `bool` for success/failure:
- `save_png()` and `save_svg()` return `false` if file cannot be written
- Invalid parameters are handled gracefully with console warnings
- Empty data sets are handled without crashing

## 🔗 Dependencies

- **Cairo Graphics Library**: For rendering
- **C++17**: For filesystem and modern C++ features
- **pkg-config**: For finding Cairo libraries

## 📝 Notes

- All coordinates use double precision
- Colors are specified in RGB format (0.0 to 1.0)
- Alpha values: 0.0 = transparent, 1.0 = opaque
- Subplot indices are 0-based: (0,0) is top-left
- File paths can be relative or absolute 