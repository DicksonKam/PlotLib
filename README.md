# PlotLib - Easy C++ Plotting Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Docker](https://img.shields.io/badge/Docker-✅%20tested-brightgreen.svg)](docs/DOCKER.md)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](docs/DOCKER.md)
[![Documentation](https://img.shields.io/badge/docs-complete-green.svg)](docs/)

A simple, beginner-friendly C++ plotting library for creating beautiful scatter plots, line plots, and histograms with support for subplots and advanced customization.

## 🎨 What You Can Create

<table>
<tr>
<td width="50%">

**📊 Scatter Plots**
- Relationship analysis
- Cluster visualization
- Data point correlation

</td>
<td width="50%">

**📈 Line Plots**
- Time series data
- Mathematical functions
- Trend analysis

</td>
</tr>
<tr>
<td width="50%">

**📋 Histograms**
- Data distribution
- Statistical analysis
- Frequency visualization

</td>
<td width="50%">

**🗃️ Subplots**
- Complex dashboards
- Multi-plot analysis
- Professional reports

</td>
</tr>
</table>

> 💡 **Try it now!** Generate 30+ example plots in seconds with Docker:
> ```bash
> git clone https://github.com/DicksonKam/PlotLib && cd PlotLib
> docker run --rm -v ./output:/app/output plotlib /app/build/examples/01_first_scatter_plot
> ```

## 🚀 Quick Start

### 🐳 Docker (Recommended - Works on Any Platform)

**Instant cross-platform setup** - Works on Windows, macOS, and Linux:

```bash
# Clone the repository
git clone https://github.com/DicksonKam/PlotLib
cd PlotLib

# Build the Docker image
docker build -t plotlib .

# Run a quick example
docker run --rm -v ./output:/app/output plotlib /app/build/examples/01_first_scatter_plot

# Run advanced examples
docker run --rm -v ./output:/app/output plotlib /app/build/examples/05_simple_subplots

# Or use docker-compose for conveniently building and running examples all at once
docker-compose up plotlib
```

### 🔧 Native Build

```bash
# Clone the repository
git clone https://github.com/DicksonKam/PlotLib
cd PlotLib

# Build the library
./build.sh

# The library will be built in the build/ directory
```

### Your First Plot

```cpp
#include "scatter_plot.h"
#include <vector>

int main() {
    // Create some data
    std::vector<double> x_values = {1, 2, 3, 4};
    std::vector<double> y_values = {2, 4, 6, 8};
    
    // Create a scatter plot
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels("My First Plot", "X Values", "Y Values");
    plot.add_scatter(x_values, y_values, "My Data");
    
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
plot.add_scatter(x_values1, y_values1, "Series 1", "blue");
plot.add_scatter(x_values2, y_values2, "Series 2", "red");
plot.save_png("scatter.png");
```

### 2. Line Plots
Ideal for time series data or continuous functions.

```cpp
plotlib::LinePlot plot(800, 600);
plot.add_line(x_values, y_values, "Function", "green");
plot.save_png("line.png");
```

### 3. Histograms
Great for showing data distributions.

```cpp
plotlib::HistogramPlot plot(800, 600);
plot.add_histogram(data, "Distribution", "purple", 20); // 20 bins

// Or create discrete histograms for categorical data
std::vector<int> counts = {10, 20, 15};
std::vector<std::string> names = {"Type A", "Type B", "Type C"};
plot.add_histogram(counts, names); // Discrete histogram
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
plot.add_scatter(x_values1, y_values1, "Series 1");  // Automatically blue
plot.add_scatter(x_values2, y_values2, "Series 2");  // Automatically red
plot.add_scatter(x_values3, y_values3, "Series 3");  // Automatically green
```

### Histogram Bins
Control the number of bins in histograms:

```cpp
plot.add_histogram(values);                  // Automatic bin count
plot.add_histogram(values, "Data", 15);      // 15 bins
plot.add_histogram(values, "Data", "red", 25); // 25 red bins
```

## 📈 Subplots

Create multiple plots in one figure:

```cpp
plotlib::SubplotManager manager(2, 2, 1200, 900); // 2x2 grid
manager.set_main_title("My Dashboard");

// Top-left: Scatter plot
auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
scatter.set_labels("Scatter", "X", "Y");
scatter.add_scatter(scatter_x, scatter_y, "Data", "blue");

// Top-right: Line plot
auto& line = manager.get_subplot<plotlib::LinePlot>(0, 1);
line.set_labels("Line", "X", "Y");
line.add_line(line_x, line_y, "Function", "red");

// Bottom-left: Histogram
auto& hist = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
hist.set_labels("Distribution", "Value", "Frequency");
hist.add_histogram(hist_data, "Data", "green");

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
std::vector<double> x_values = {1, 2, 5, 6};
std::vector<double> y_values = {1, 2, 5, 6};
std::vector<int> labels = {0, 0, 1, 1};  // Cluster labels
plot.add_clusters(x_values, y_values, labels);  // Automatic cluster coloring
```

## ⚡ Performance & Features

- **🚀 Fast**: Optimized Cairo rendering for smooth performance
- **📦 Lightweight**: Alpine Linux Docker images (~50MB)
- **🎯 Memory Efficient**: Smart data aggregation for large datasets
- **🌍 Cross-Platform**: Works on Windows, macOS, Linux via Docker
- **🔧 Zero Dependencies**: Everything included in Docker container
- **📊 Production Ready**: Used for scientific visualization and dashboards

## 🆚 Why PlotLib?

| Feature | PlotLib | matplotlib | plotly | gnuplot |
|---------|---------|------------|--------|---------|
| **C++ Native** | ✅ | ❌ | ❌ | ❌ |
| **Easy Setup** | ✅ Docker | ❌ Python env | ❌ Node.js | ❌ Dependencies |
| **Cross-Platform** | ✅ Universal | ❌ Python-specific | ❌ Web-based | ❌ Unix-focused |
| **Learning Curve** | 🟢 Simple | 🟡 Moderate | 🟡 Moderate | 🔴 Complex |
| **Performance** | 🟢 Fast | 🟡 Good | 🟡 Good | 🟢 Fast |
| **Deployment** | 🟢 Single binary | 🔴 Runtime needed | 🔴 Browser needed | 🔴 Interpreter |

## 📁 Project Structure

```
plotlib/
├── include/                  # Header files
│   ├── scatter_plot.h
│   ├── line_plot.h
│   ├── histogram_plot.h
│   └── plot_manager.h
├── src/                      # Source files
├── examples/                 # Example programs
│   ├── beginner/            # Beginner-friendly examples
│   └── advanced/            # Professional techniques
├── docs/                    # Documentation
│   ├── tutorial/            # Step-by-step tutorials
│   ├── api/                 # API reference
│   └── gallery/             # Plot gallery
└── tests/                   # Unit tests
```

## 📚 Learning Resources

- **[Docker Guide](docs/DOCKER.md)** - Cross-platform Docker usage (Windows, macOS, Linux)
- **[Beginner Tutorial](docs/tutorial/beginner.md)** - Start here if you're new to plotting
- **[API Reference](docs/api/README.md)** - Complete function documentation
- **[Example Gallery](docs/gallery/README.md)** - Visual examples with code
- **[Advanced Guide](docs/tutorial/advanced.md)** - Complex plotting techniques
- **[Changelog](CHANGELOG.md)** - Release history and version changes
- **[Roadmap](ROADMAP.md)** - Future development plans and features

## 🎯 Examples

### Running Examples

After building with `./build.sh`, you can run examples:

```bash
cd build

# Run all beginner examples (recommended first)
make run_beginner_examples

# Run all advanced examples
make run_advanced_examples

# Run all plot_types examples (comprehensive API demos)
make run_plot_types_examples

# Run everything
make run_all_examples

# Or run individual examples
./examples/01_first_scatter_plot
./examples/advanced_01_custom_styling
./examples/advanced_04_reference_lines
```

### Example Categories

- **Beginner examples** (`examples/beginner/`): Simple, well-commented code
  - 7 progressive examples covering all basic features
  - Includes continuous and discrete histograms
  - Generates 7+ example plots
  
- **Advanced examples** (`examples/advanced/`): Professional techniques
  - Custom styling and RGB color control
  - Complex dashboards (3x3, 4x2 layouts)
  - Performance optimization for large datasets
  - Reference lines and plot annotations
  - Generates 25+ advanced plots

- **Plot Types examples** (`examples/plot_types/`): Comprehensive API demonstrations
  - 4 focused examples showing complete API usage
  - Line plots, scatter plots, histograms, and comprehensive plots
  - Professional code patterns and best practices
  - Generates 4+ demonstration plots

All generated plots are saved to the `output/` directory.

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