# PlotLib - Easy C++ Plotting Library

A simple, beginner-friendly C++ plotting library for creating beautiful scatter plots, line plots, and histograms with support for subplots and advanced customization.

## 🚀 Quick Start

### Installation

```bash
# Clone the repository
git clone <repository-url>
cd plotlib

# Build the library
./build.sh

# The library will be built in the build/ directory
```

### Your First Plot

```cpp
#include "plotlib/scatter_plot.h"
#include <vector>

int main() {
    // Create some data
    std::vector<plotlib::Point2D> data = {{1, 2}, {2, 4}, {3, 6}, {4, 8}};
    
    // Create a scatter plot
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels("My First Plot", "X Values", "Y Values");
    plot.add_data("My Data", data);
    
    // Save the plot
    plot.save_png("my_first_plot.png");
    
    return 0;
}
```

## 📊 Plot Types

### 1. Scatter Plots
Perfect for showing relationships between two variables or displaying clusters.

```cpp
plotlib::ScatterPlot plot(800, 600);
plot.add_data("Series 1", data1, "blue");
plot.add_data("Series 2", data2, "red");
plot.save_png("scatter.png");
```

### 2. Line Plots
Ideal for time series data or continuous functions.

```cpp
plotlib::LinePlot plot(800, 600);
plot.add_line("Function", x_values, y_values, "green");
plot.save_png("line.png");
```

### 3. Histograms
Great for showing data distributions.

```cpp
plotlib::HistogramPlot plot(800, 600);
plot.add_histogram("Distribution", data, "purple", 20); // 20 bins
plot.save_png("histogram.png");
```

## 🎨 Easy Customization

### Colors
Use simple color names:
- `"red"`, `"blue"`, `"green"`, `"orange"`
- `"purple"`, `"cyan"`, `"magenta"`, `"yellow"`
- `"black"`, `"gray"`

### Automatic Colors
Don't specify colors and the library will choose them automatically:

```cpp
plot.add_data("Series 1", data1);  // Automatically blue
plot.add_data("Series 2", data2);  // Automatically red
plot.add_data("Series 3", data3);  // Automatically green
```

### Histogram Bins
Control the number of bins in histograms:

```cpp
plot.add_histogram("Data", values);        // Automatic bin count
plot.add_histogram("Data", values, 15);    // 15 bins
plot.add_histogram("Data", values, "red", 25); // 25 red bins
```

## 📈 Subplots

Create multiple plots in one figure:

```cpp
plotlib::SubplotManager manager(2, 2, 1200, 900); // 2x2 grid
manager.set_main_title("My Dashboard");

// Top-left: Scatter plot
auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
scatter.set_labels("Scatter", "X", "Y");
scatter.add_data("Data", scatter_data, "blue");

// Top-right: Line plot
auto& line = manager.get_subplot<plotlib::LinePlot>(0, 1);
line.set_labels("Line", "X", "Y");
line.add_line("Function", line_data, "red");

// Bottom-left: Histogram
auto& hist = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
hist.set_labels("Distribution", "Value", "Frequency");
hist.add_histogram("Data", hist_data, "green");

manager.save_png("dashboard.png");
```

## 🔧 Advanced Features

### Legend Control
```cpp
plot.hide_legend_item("Series 2");     // Hide specific series
plot.set_legend_enabled(false);        // Hide entire legend
plot.show_all_legend_items();          // Show all items
```

### Histogram Options
```cpp
hist.set_normalize(true);               // Probability density
hist.set_cumulative(true);              // Cumulative distribution
hist.set_default_bin_count(30);         // Default bins for auto-binning
```

### Line Plot Options
```cpp
line.set_show_markers(true);            // Show markers on lines
line.set_default_line_width(3.0);       // Thicker lines
```

### Cluster Analysis
```cpp
std::vector<plotlib::Point2D> points = {{1,1}, {2,2}, {5,5}, {6,6}};
std::vector<int> labels = {0, 0, 1, 1};  // Cluster labels
plot.add_clusters(points, labels);       // Automatic cluster coloring
```

## 📁 Project Structure

```
plotlib/
├── include/plotlib/          # Header files
│   ├── scatter_plot.h
│   ├── line_plot.h
│   ├── histogram_plot.h
│   └── plot_manager.h
├── src/                      # Source files
├── examples/                 # Example programs
│   ├── beginner/            # Beginner-friendly examples
│   ├── intermediate/        # More advanced examples
│   └── advanced/            # Complex use cases
├── docs/                    # Documentation
│   ├── tutorial/            # Step-by-step tutorials
│   ├── api/                 # API reference
│   └── gallery/             # Plot gallery
└── tests/                   # Unit tests
```

## 📚 Learning Resources

- **[Beginner Tutorial](docs/tutorial/beginner.md)** - Start here if you're new to plotting
- **[API Reference](docs/api/README.md)** - Complete function documentation
- **[Example Gallery](docs/gallery/README.md)** - Visual examples with code
- **[Advanced Guide](docs/tutorial/advanced.md)** - Complex plotting techniques

## 🎯 Examples

Check out the `examples/` directory for:
- **Beginner examples**: Simple, well-commented code
- **Intermediate examples**: Real-world use cases
- **Advanced examples**: Complex visualizations and customizations

## 🛠️ Building Your Project

### CMake Integration
```cmake
find_package(PlotLib REQUIRED)
target_link_libraries(your_target PlotLib::plotlib)
```

### Manual Compilation
```bash
g++ -std=c++17 -I./include your_code.cpp -L./build -lplotlib `pkg-config --cflags --libs cairo cairo-svg` -o your_program
```

## 🤝 Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## 📄 License

This project is licensed under the MIT License - see [LICENSE](LICENSE) for details.

## 🆘 Getting Help

- Check the [documentation](docs/)
- Look at [examples](examples/)
- Open an issue on GitHub

---

**Happy Plotting! 📊✨** 