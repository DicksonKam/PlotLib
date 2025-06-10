# API Reference

Complete reference for the simplified PlotLib API designed for ease of use.

## 📊 Core Classes

### ScatterPlot

Perfect for showing relationships between variables and cluster analysis.

#### Constructor
```cpp
ScatterPlot(int width = 800, int height = 600)
```

#### Methods
```cpp
// Add scatter data with automatic coloring
void add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                 const std::string& name);

// Add scatter data with custom color
void add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                 const std::string& name, const std::string& color_name);

// Add cluster data with automatic coloring by cluster label
void add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                  const std::vector<int>& labels);
```

**Example:**
```cpp
std::vector<double> x = {1, 2, 3, 4};
std::vector<double> y = {2, 4, 6, 8};
plot.add_scatter(x, y, "My Data", "blue");
```

### LinePlot

Ideal for time series data and mathematical functions.

#### Constructor
```cpp
LinePlot(int width = 800, int height = 600)
```

#### Methods
```cpp
// Add line with automatic coloring
void add_line(const std::vector<double>& x_values, const std::vector<double>& y_values, 
              const std::string& name);

// Add line with custom color
void add_line(const std::vector<double>& x_values, const std::vector<double>& y_values, 
              const std::string& name, const std::string& color_name);
```

#### Line Configuration
```cpp
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

**Example:**
```cpp
std::vector<double> time = {0, 1, 2, 3, 4};
std::vector<double> values = {10, 15, 12, 18, 20};
plot.add_line(time, values, "Trend", "red");
```

### HistogramPlot

Great for understanding data distributions.

#### Constructor
```cpp
HistogramPlot(int width = 800, int height = 600)
```

#### Methods
```cpp
// Add histogram with automatic bin count
void add_histogram(const std::vector<double>& data, const std::string& name);

// Add histogram with custom color
void add_histogram(const std::vector<double>& data, const std::string& name, 
                   const std::string& color_name);

// Add histogram with custom color and bin count
void add_histogram(const std::vector<double>& data, const std::string& name, 
                   const std::string& color_name, int bins);
```

**Example:**
```cpp
std::vector<double> scores = {85, 92, 78, 88, 95, 82, 90};
plot.add_histogram(scores, "Test Scores", "green", 10);
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

**Example:**
```cpp
SubplotManager manager(2, 2, 1200, 900);
auto& plot1 = manager.get_subplot<ScatterPlot>(0, 0);
auto& plot2 = manager.get_subplot<LinePlot>(0, 1);
```

## 🎨 Color System

### Available Colors
The simplified API uses string-based color names for easy use:

- `"red"`, `"blue"`, `"green"`, `"orange"`
- `"purple"`, `"cyan"`, `"magenta"`, `"yellow"`
- `"black"`, `"gray"`

### Automatic Color Assignment
When you don't specify a color, the library automatically assigns colors in this order:
1. Blue
2. Red  
3. Green
4. Orange
5. Purple
6. Cyan
7. Magenta
8. Yellow

**Example:**
```cpp
plot.add_scatter(x1, y1, "Series 1");        // Automatically blue
plot.add_scatter(x2, y2, "Series 2");        // Automatically red
plot.add_scatter(x3, y3, "Series 3", "green"); // Explicitly green
```

## 📐 Marker Types

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
The `add_clusters` method provides automatic visualization of clustering results:
- Each unique cluster label gets a distinct color
- Outliers (label -1) are shown as red crosses
- Normal clusters use standard markers with automatic colors

```cpp
std::vector<double> x = {1, 2, 10, 11, 1.5, 11.5};
std::vector<double> y = {1, 2, 10, 11, 1.2, 10.8};
std::vector<int> labels = {0, 0, 1, 1, 0, 1};  // Two clusters
plot.add_clusters(x, y, labels);
```

### Automatic Axis Scaling
- Smart tick placement at "nice" intervals (1, 2, 5, 10, etc.)
- Automatic bounds based on data range with appropriate margins
- Grid lines aligned with tick marks for easy reading

### Legend System
- Automatic positioning in top-right corner
- Only appears when multiple named series exist
- Selective hiding/showing of legend items
- Proper handling of cluster data

## 📊 Common Usage Patterns

### Pattern 1: Quick Scatter Plot
```cpp
plotlib::ScatterPlot plot(800, 600);
plot.set_labels("My Analysis", "X Variable", "Y Variable");
plot.add_scatter(x_values, y_values, "Data Points", "blue");
plot.save_png("scatter.png");
```

### Pattern 2: Multiple Line Comparison
```cpp
plotlib::LinePlot plot(1000, 600);
plot.set_labels("Performance Over Time", "Time", "Score");
plot.add_line(time, scores_a, "Algorithm A", "blue");
plot.add_line(time, scores_b, "Algorithm B", "red");
plot.add_line(time, target_scores, "Target", "green");
plot.save_png("comparison.png");
```

### Pattern 3: Distribution Analysis
```cpp
plotlib::HistogramPlot plot(800, 600);
plot.set_labels("Score Distribution", "Score", "Frequency");
plot.add_histogram(before_scores, "Before Training", "red", 20);
plot.add_histogram(after_scores, "After Training", "green", 20);
plot.save_png("distributions.png");
```

### Pattern 4: Dashboard Creation
```cpp
plotlib::SubplotManager dashboard(2, 2, 1200, 900);
dashboard.set_main_title("Data Analysis Dashboard");

// Top-left: Scatter plot
auto& scatter = dashboard.get_subplot<plotlib::ScatterPlot>(0, 0);
scatter.set_labels("Correlation", "Variable X", "Variable Y");
scatter.add_scatter(x_data, y_data, "Data");

// Top-right: Line plot
auto& line = dashboard.get_subplot<plotlib::LinePlot>(0, 1);
line.set_labels("Trend", "Time", "Value");
line.add_line(time_data, value_data, "Measurements");

// Bottom-left: Histogram
auto& hist = dashboard.get_subplot<plotlib::HistogramPlot>(1, 0);
hist.set_labels("Distribution", "Value", "Count");
hist.add_histogram(sample_data, "Sample");

// Bottom-right: Clusters
auto& clusters = dashboard.get_subplot<plotlib::ScatterPlot>(1, 1);
clusters.set_labels("Clusters", "Feature 1", "Feature 2");
clusters.add_clusters(feature1, feature2, cluster_labels);

dashboard.save_png("dashboard.png");
```

## 🚨 Error Handling and Tips

### File Operations
- `save_png()` and `save_svg()` return `false` if file cannot be written
- Check return values for error handling
- Ensure output directory exists

### Data Validation
- Empty data vectors are handled gracefully
- Mismatched x and y vector sizes will show error messages
- Invalid cluster labels are handled without crashing

### Performance Tips
- For datasets > 10,000 points, consider data sampling
- Use appropriate bin counts for histograms (10-50 bins typically)
- Reserve vector capacity when generating large datasets

### Common Mistakes
```cpp
// ❌ Wrong: Mismatched vector sizes
std::vector<double> x = {1, 2, 3};
std::vector<double> y = {1, 2};  // Different size!

// ✅ Correct: Same size vectors
std::vector<double> x = {1, 2, 3};
std::vector<double> y = {2, 4, 6};  // Same size
```

## 🔗 Dependencies

- **Cairo Graphics Library**: For rendering (install via package manager)
- **C++17**: For modern C++ features
- **pkg-config**: For finding Cairo libraries during compilation

## 📝 Compilation Example

```bash
g++ -std=c++17 -I./include my_plot.cpp -L./build -lplotlib \
    `pkg-config --cflags --libs cairo cairo-svg` -o my_plot
```

## 🎯 Design Philosophy

This simplified API prioritizes:
1. **Ease of use**: Simple method names and parameters
2. **Beginner friendly**: Automatic color assignment and sensible defaults  
3. **Consistency**: Similar patterns across all plot types
4. **Performance**: Efficient handling of large datasets
5. **Flexibility**: Support for advanced features when needed

The goal is to make beautiful plots with minimal code while maintaining the power needed for complex visualizations. 