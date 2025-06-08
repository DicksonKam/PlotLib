# 🚀 Quick Start Guide

Get up and running with PlotLib in 5 minutes!

## 📦 Installation

```bash
# Clone and build
git clone <repository-url>
cd plotlib
./build.sh

# The library is now ready in the build/ directory
```

## 🎯 Your First Plot in 30 Seconds

Create a file called `my_plot.cpp`:

```cpp
#include "plotlib/scatter_plot.h"
#include <vector>

int main() {
    // Create data
    std::vector<plotlib::Point2D> data = {{1, 2}, {2, 4}, {3, 6}};
    
    // Create plot
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels("My Plot", "X", "Y");
    plot.add_data("Data", data);
    
    // Save
    plot.save_png("my_plot.png");
    return 0;
}
```

Compile and run:
```bash
g++ -std=c++17 -I./include my_plot.cpp -L./build -lplotlib `pkg-config --cflags --libs cairo cairo-svg` -o my_plot
./my_plot
```

## 🎨 Common Patterns

### Scatter Plot with Colors
```cpp
plotlib::ScatterPlot plot(800, 600);
plot.add_data("Series 1", data1, "blue");
plot.add_data("Series 2", data2, "red");
plot.save_png("scatter.png");
```

### Line Plot from X,Y Vectors
```cpp
plotlib::LinePlot plot(800, 600);
std::vector<double> x = {1, 2, 3, 4};
std::vector<double> y = {2, 4, 6, 8};
plot.add_line("Trend", x, y, "green");
plot.save_png("line.png");
```

### Histogram with Custom Bins
```cpp
plotlib::HistogramPlot plot(800, 600);
plot.add_histogram("Data", values, "purple", 20);  // 20 bins
plot.save_png("histogram.png");
```

### Simple 2x2 Dashboard
```cpp
plotlib::SubplotManager manager(2, 2, 1200, 900);
auto& plot1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
auto& plot2 = manager.get_subplot<plotlib::LinePlot>(0, 1);
// ... configure each plot
manager.save_png("dashboard.png");
```

## 🎓 Learning Path

1. **Start here**: [Beginner Tutorial](tutorial/beginner.md)
2. **Try examples**: Run examples in `examples/beginner/`
3. **Explore**: Check out the [Gallery](gallery/README.md)
4. **Advanced**: Read [API Reference](api/README.md)

## 🆘 Need Help?

- **Examples not working?** Make sure you built the library first: `./build.sh`
- **Compilation errors?** Check that Cairo is installed: `brew install cairo` (macOS) or `sudo apt install libcairo2-dev` (Ubuntu)
- **Want more features?** Check the [full documentation](tutorial/beginner.md)

## 🎯 Available Colors

`"red"`, `"blue"`, `"green"`, `"orange"`, `"purple"`, `"cyan"`, `"magenta"`, `"yellow"`, `"black"`, `"gray"`

## 📊 Plot Types

- **ScatterPlot**: Points, relationships, clusters
- **LinePlot**: Trends, time series, functions  
- **HistogramPlot**: Distributions, frequencies

Happy plotting! 🎉 