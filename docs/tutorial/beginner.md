# Beginner's Guide to PlotLib

Welcome to PlotLib! This guide will teach you everything you need to know to create beautiful plots, even if you're new to programming or data visualization.

## 🎯 What You'll Learn

By the end of this tutorial, you'll be able to:
- Create scatter plots, line plots, and histograms
- Use colors and customize your plots
- Create subplots (multiple plots in one figure)
- Save your plots as images
- Understand when to use each type of plot

## 📋 Prerequisites

- Basic C++ knowledge (variables, vectors, functions)
- PlotLib installed and working (see [Installation Guide](../README.md))

## 🚀 Let's Start!

### Step 1: Your Very First Plot

Let's create a simple scatter plot. A scatter plot shows individual data points and is great for seeing relationships between two variables.

```cpp
#include "scatter_plot.h"
#include <vector>

int main() {
    // Step 1: Create your data using separate x/y vectors
    std::vector<double> x_values = {1, 2, 3, 4};
    std::vector<double> y_values = {2, 4, 6, 8};
    
    // Step 2: Create a plot
    plotlib::ScatterPlot plot(800, 600);  // 800x600 pixels
    
    // Step 3: Add labels
    plot.set_labels("My First Plot", "X Values", "Y Values");
    
    // Step 4: Add your data
    plot.add_scatter("My Data", x_values, y_values);
    
    // Step 5: Save it
    plot.save_png("my_first_plot.png");
    
    return 0;
}
```

**What happened here?**
- We created 4 data points: (1,2), (2,4), (3,6), (4,8)
- We made a plot that's 800 pixels wide and 600 pixels tall
- We gave it a title and labeled the axes
- We added our data (the library automatically chose blue color)
- We saved it as a PNG image

### Step 2: Adding Colors

Colors make your plots more interesting and help distinguish different data series:

```cpp
plotlib::ScatterPlot plot(800, 600);
plot.set_labels("Colorful Plot", "X", "Y");

// Method 1: Let the library choose colors automatically
plot.add_scatter("Series 1", x1_values, y1_values);  // Automatically blue
plot.add_scatter("Series 2", x2_values, y2_values);  // Automatically red

// Method 2: Choose your own colors
plot.add_scatter("Series 3", x3_values, y3_values, "green");
plot.add_scatter("Series 4", x4_values, y4_values, "purple");
```

**Available colors:**
- `"red"`, `"blue"`, `"green"`, `"orange"`
- `"purple"`, `"cyan"`, `"magenta"`, `"yellow"`
- `"black"`, `"gray"`

### Step 3: Line Plots for Trends

Line plots are perfect for showing how something changes over time or for plotting mathematical functions:

```cpp
#include "line_plot.h"

// Easy way: Use separate X and Y vectors
std::vector<double> time = {0, 1, 2, 3, 4, 5};
std::vector<double> temperature = {20, 22, 25, 28, 26, 24};

plotlib::LinePlot plot(800, 600);
plot.set_labels("Temperature Over Time", "Hours", "Temperature (°C)");
plot.add_line("Temperature", time, temperature, "red");
plot.save_png("temperature.png");
```

**When to use line plots:**
- Time series data (stock prices, temperature over time)
- Mathematical functions (sin(x), x², etc.)
- Any data where the order matters

### Step 4: Histograms for Distributions

Histograms show you how your data is distributed - where most values fall and how spread out they are:

```cpp
#include "histogram_plot.h"

// Example: Test scores
std::vector<double> scores = {
    85, 92, 78, 88, 95, 82, 90, 87, 93, 79,
    86, 91, 84, 89, 96, 83, 88, 85, 92, 87
};

plotlib::HistogramPlot plot(800, 600);
plot.set_labels("Test Score Distribution", "Score", "Number of Students");

// Automatic bin count
plot.add_histogram("Scores", scores, "blue");

// Or specify number of bins
plot.add_histogram("Scores", scores, "blue", 10);  // 10 bins

plot.save_png("test_scores.png");
```

**Bin count tips:**
- **Few bins (5-10)**: Good for seeing general patterns
- **Many bins (20-50)**: Good for detailed distribution
- **Too many bins**: Makes the histogram look noisy

### Step 5: Multiple Plots (Subplots)

Sometimes you want to show several related plots together. That's where subplots come in:

```cpp
#include "plot_manager.h"  // For SubplotManager

// Create a 2x2 grid (2 rows, 2 columns)
plotlib::SubplotManager manager(2, 2, 1200, 900);
manager.set_main_title("My Dashboard");

// Top-left (row 0, column 0): Scatter plot
auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
scatter.set_labels("Scatter", "X", "Y");
scatter.add_scatter("Data", scatter_x, scatter_y, "blue");

// Top-right (row 0, column 1): Line plot
auto& line = manager.get_subplot<plotlib::LinePlot>(0, 1);
line.set_labels("Line", "Time", "Value");
line.add_line("Trend", time_data, value_data, "red");

// Bottom-left (row 1, column 0): Histogram
auto& hist = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
hist.set_labels("Distribution", "Value", "Count");
hist.add_histogram("Data", hist_data, "green");

// Bottom-right (row 1, column 1): Another plot
auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 1);
// ... configure this plot too

manager.save_png("dashboard.png");
```

**Common subplot layouts:**
- `2x2`: Four plots in a square
- `1x3`: Three plots side by side
- `3x1`: Three plots stacked vertically
- `2x3`: Six plots in a grid

## 🎨 Styling Tips

### Making Your Plots Look Professional

1. **Choose good titles and labels:**
   ```cpp
   plot.set_labels("Clear, Descriptive Title", "X Axis Label", "Y Axis Label");
   ```

2. **Use appropriate colors:**
   - Use contrasting colors for different series
   - Stick to a consistent color scheme
   - Consider colorblind-friendly colors

3. **Choose the right plot type:**
   - **Scatter plots**: For relationships between variables
   - **Line plots**: For trends over time or continuous data
   - **Histograms**: For understanding data distribution

## 🔧 Common Patterns

### Pattern 1: Comparing Groups
```cpp
plotlib::ScatterPlot plot(800, 600);
plot.set_labels("Group Comparison", "X", "Y");

plot.add_scatter("Group A", group_a_x, group_a_y, "blue");
plot.add_scatter("Group B", group_b_x, group_b_y, "red");
plot.add_scatter("Group C", group_c_x, group_c_y, "green");
```

### Pattern 2: Time Series Analysis
```cpp
plotlib::LinePlot plot(800, 600);
plot.set_labels("Sales Over Time", "Month", "Sales ($)");

plot.add_line("2023", months, sales_2023, "blue");
plot.add_line("2024", months, sales_2024, "red");
```

### Pattern 3: Distribution Analysis
```cpp
plotlib::HistogramPlot plot(800, 600);
plot.set_labels("Response Time Distribution", "Time (ms)", "Frequency");

plot.add_histogram("Before Optimization", before_data, "red", 20);
plot.add_histogram("After Optimization", after_data, "green", 20);
```

## 🚨 Common Mistakes to Avoid

1. **Too many colors**: Stick to 3-5 colors maximum
2. **Unclear labels**: Always label your axes and give your plot a title
3. **Wrong plot type**: Don't use line plots for unordered data
4. **Too many bins in histograms**: Start with automatic binning, then adjust
5. **Overcrowded plots**: If you have too much data, consider subplots

## 🎯 Practice Exercises

Try these exercises to practice what you've learned:

### Exercise 1: Personal Data
Create a scatter plot of your own data (height vs weight, study hours vs grades, etc.)

### Exercise 2: Mathematical Functions
Plot sin(x) and cos(x) on the same line plot from 0 to 2π

### Exercise 3: Random Data Analysis
Generate 1000 random numbers and create a histogram to see their distribution

### Exercise 4: Mini Dashboard
Create a 2x2 subplot with:
- Top-left: Your favorite scatter plot
- Top-right: A line plot of any trend
- Bottom-left: A histogram of some data
- Bottom-right: Another plot of your choice

## 🚀 Next Steps

Once you're comfortable with the basics:

1. **Check out the [Advanced Tutorial](advanced.md)** for professional features
2. **Browse the [Example Gallery](../gallery/README.md)** for inspiration
3. **Read the [API Reference](../api/README.md)** for complete function documentation

## 💡 Tips for Success

- **Start simple**: Begin with basic plots and add complexity gradually
- **Experiment**: Try different colors, layouts, and data
- **Look at examples**: The `examples/beginner/` folder has lots of working code
- **Ask for help**: Check the documentation or open an issue if you're stuck

Happy plotting! 📊✨ 