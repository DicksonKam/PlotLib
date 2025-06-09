# PlotLib Gallery

Visual showcase of what you can create with PlotLib. All examples include source code and are beginner-friendly!

## 🎯 Basic Plot Types

### Scatter Plots
Perfect for showing relationships between variables and cluster analysis.

#### Simple Scatter Plot
```cpp
plotlib::ScatterPlot plot(800, 600);
plot.set_labels("My First Plot", "X Values", "Y Values");
plot.add_scatter("Data", x_values, y_values, "blue");
plot.save_png("scatter.png");
```
*Shows individual data points with automatic styling*

#### Multiple Series with Colors
```cpp
plot.add_scatter("Series A", x_a, y_a, "blue");
plot.add_scatter("Series B", x_b, y_b, "red");
plot.add_scatter("Series C", x_c, y_c, "green");
```
*Multiple datasets with different colors and automatic legend*

#### Cluster Visualization
```cpp
plot.add_clusters(x_values, y_values, cluster_labels);
```
*Automatic coloring for clustering results with outlier detection*

### Line Plots
Ideal for time series data and mathematical functions.

#### Temperature Over Time
```cpp
plotlib::LinePlot plot(800, 600);
plot.add_line("Temperature", time, temperature, "red");
```
*Simple time series visualization*

#### Mathematical Functions
```cpp
plot.add_line("sin(x)", x_values, sine_values, "blue");
plot.add_line("cos(x)", x_values, cosine_values, "green");
```
*Multiple mathematical functions on the same plot*

#### Growth Trends
```cpp
plot.add_line("Revenue", years, revenue, "purple");
```
*Business data visualization with clear trends*

### Histograms
Great for understanding data distributions.

#### Test Score Distribution
```cpp
plotlib::HistogramPlot plot(800, 600);
plot.add_histogram("Scores", test_scores, "blue");
```
*Shows how data is distributed across ranges*

#### Comparing Groups
```cpp
plot.add_histogram("Group A", group_a_data, "blue", 20);
plot.add_histogram("Group B", group_b_data, "orange", 20);
```
*Side-by-side comparison of two distributions*

#### Different Bin Counts
```cpp
// Fewer bins - general pattern
plot.add_histogram("Data", values, "green", 10);

// More bins - detailed distribution  
plot.add_histogram("Data", values, "red", 30);
```
*Same data with different levels of detail*

## 📊 Subplot Layouts

### 2x2 Dashboard
```cpp
plotlib::SubplotManager manager(2, 2, 1200, 900);
manager.set_main_title("Analysis Dashboard");

auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
auto& line = manager.get_subplot<plotlib::LinePlot>(0, 1);
auto& hist = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
auto& clusters = manager.get_subplot<plotlib::ScatterPlot>(1, 1);
```
*Four different plot types in one comprehensive dashboard*

### Horizontal Comparison (1x3)
```cpp
plotlib::SubplotManager horizontal(1, 3, 1500, 500);
// Sales | Satisfaction | Response Times
```
*Three related metrics side by side for easy comparison*

### Vertical Analysis (3x1)
```cpp
plotlib::SubplotManager vertical(3, 1, 600, 1200);
// Temperature
// Humidity  
// Wind Speed
```
*Stacked plots showing related data over time*

## 🎨 Color Showcase

### Available Colors
PlotLib supports these color names:
- `"red"` - Classic red
- `"blue"` - Default blue  
- `"green"` - Nature green
- `"orange"` - Vibrant orange
- `"purple"` - Royal purple
- `"cyan"` - Bright cyan
- `"magenta"` - Bold magenta
- `"yellow"` - Bright yellow
- `"black"` - Pure black
- `"gray"` - Neutral gray

### Automatic Color Assignment
```cpp
plot.add_scatter("Series 1", x1, y1);  // Automatically blue
plot.add_scatter("Series 2", x2, y2);  // Automatically red
plot.add_scatter("Series 3", x3, y3);  // Automatically green
```
*Library automatically chooses contrasting colors*

## 📈 Real-World Examples

### Business Analytics
- **Sales trends** over time with line plots
- **Customer satisfaction** scatter plots
- **Response time distributions** with histograms
- **Performance dashboards** with mixed subplot layouts

### Scientific Data
- **Experimental results** with error visualization
- **Mathematical function** plotting
- **Statistical distributions** analysis
- **Multi-variable** correlation studies

### Educational Use
- **Test score** distributions
- **Grade trends** over time
- **Student performance** comparisons
- **Learning progress** dashboards

## 🔧 Customization Examples

### Professional Styling
```cpp
plot.set_labels("Quarterly Revenue Analysis", 
                "Quarter", 
                "Revenue ($ millions)");
plot.add_line("2023", q2023, revenue_2023, "blue");
plot.add_line("2024", q2024, revenue_2024, "red");
```

### Scientific Plots
```cpp
plot.set_labels("Experimental Results", 
                "Time (seconds)", 
                "Amplitude (mV)");
plot.add_scatter("Control", control_x, control_y, "black");
plot.add_scatter("Treatment", treatment_x, treatment_y, "red");
```

### Educational Dashboards
```cpp
manager.set_main_title("Student Performance Analysis");
// Multiple subplots showing different aspects of performance
```

## 🎯 Plot Type Selection Guide

### When to Use Scatter Plots
- ✅ Showing relationships between two variables
- ✅ Cluster analysis and classification results
- ✅ Outlier detection
- ✅ Correlation analysis

### When to Use Line Plots  
- ✅ Time series data (stock prices, temperature)
- ✅ Mathematical functions
- ✅ Trend analysis
- ✅ Continuous data where order matters

### When to Use Histograms
- ✅ Understanding data distribution
- ✅ Comparing groups or populations
- ✅ Quality control analysis
- ✅ Statistical analysis

### When to Use Subplots
- ✅ Comparing multiple related datasets
- ✅ Creating comprehensive dashboards
- ✅ Showing different aspects of the same phenomenon
- ✅ Before/after comparisons

## 🚀 Getting Started

1. **Pick a plot type** based on your data and goals
2. **Start with a simple example** from the gallery
3. **Customize colors and labels** to match your needs
4. **Add more data series** if needed
5. **Create subplots** for comprehensive analysis

## 📝 Code Templates

### Quick Scatter Plot
```cpp
#include "scatter_plot.h"
plotlib::ScatterPlot plot(800, 600);
plot.set_labels("Title", "X", "Y");
plot.add_scatter("Data", x_values, y_values, "blue");
plot.save_png("output.png");
```

### Quick Line Plot
```cpp
#include "line_plot.h"
plotlib::LinePlot plot(800, 600);
plot.set_labels("Title", "X", "Y");
plot.add_line("Data", x_vals, y_vals, "red");
plot.save_png("output.png");
```

### Quick Histogram
```cpp
#include "histogram_plot.h"
plotlib::HistogramPlot plot(800, 600);
plot.set_labels("Title", "Value", "Frequency");
plot.add_histogram("Data", values, "green", 20);
plot.save_png("output.png");
```

### Quick Dashboard
```cpp
#include "plot_manager.h"
plotlib::SubplotManager manager(2, 2, 1200, 900);
auto& plot1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
auto& plot2 = manager.get_subplot<plotlib::LinePlot>(0, 1);
// Configure each subplot...
manager.save_png("dashboard.png");
```

## 🎨 Design Tips

### Color Harmony
- Use **2-3 main colors** for clarity
- Choose **contrasting colors** for different series
- Consider **colorblind-friendly** palettes
- Use **consistent colors** across related plots

### Layout Best Practices
- **Clear, descriptive titles** for all plots
- **Meaningful axis labels** with units
- **Appropriate plot dimensions** for your data
- **Logical subplot arrangements** (related plots together)

### Data Presentation
- **Start with simple plots** before adding complexity
- **Use appropriate bin counts** for histograms
- **Show trends clearly** with line plots
- **Highlight important patterns** with colors

## 🔗 Related Resources

- **[Beginner Tutorial](../tutorial/beginner.md)** - Step-by-step learning
- **[API Reference](../api/README.md)** - Complete function documentation  
- **[Examples Directory](../../examples/)** - Working code examples
- **[Quick Start Guide](../QUICK_START.md)** - Get running in 5 minutes

---

*All gallery examples are available as working code in the `examples/` directory. Try them out and modify them to create your own visualizations!* 