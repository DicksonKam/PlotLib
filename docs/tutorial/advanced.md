# Advanced User Guide

This guide is for experienced developers who want to leverage the full power of the plotting library for complex visualizations, performance optimization, and advanced customization.

## Table of Contents

1. [Advanced Styling and Customization](#advanced-styling-and-customization)
2. [Performance Optimization](#performance-optimization)
3. [Complex Dashboard Design](#complex-dashboard-design)
4. [Memory Management](#memory-management)
5. [Advanced Plot Types](#advanced-plot-types)
6. [Integration Patterns](#integration-patterns)
7. [Troubleshooting and Debugging](#troubleshooting-and-debugging)

## Advanced Styling and Customization

### Professional Color Usage

The simplified API provides an elegant color system with automatic color assignment and manual color specification:

```cpp
// Automatic color assignment (recommended for beginners)
plot.add_scatter(x1, y1, "Series 1");  // Auto-assigned blue
plot.add_scatter(x2, y2, "Series 2");  // Auto-assigned red
plot.add_scatter(x3, y3, "Series 3");  // Auto-assigned green

// Manual color specification (for precise control)
plot.add_scatter(x_treat, y_treat, "Treatment", "red");
plot.add_scatter(x_control, y_control, "Control", "blue");
```

### Advanced Legend Management

```cpp
// Selective legend control
plot.hide_legend_item("Outliers");
plot.hide_legend_item("Baseline");
plot.show_legend_item("Primary Results");

// Show/hide all at once
plot.set_legend_enabled(false);  // Hide entire legend
plot.show_all_legend_items();    // Show all items
```

### Custom Bounds and Scaling

```cpp
// Manual axis bounds for precise control
plot.set_bounds(x_min, x_max, y_min, y_max);

// Example: Focus on specific data range
plot.set_bounds(0, 100, -50, 150);
```

## Performance Optimization

### Large Dataset Strategies

#### 1. Data Sampling
For datasets > 10,000 points, consider sampling:

```cpp
template<typename T>
std::vector<T> sample_data(const std::vector<T>& data, size_t target_size) {
    if (data.size() <= target_size) return data;
    
    std::vector<T> sampled;
    sampled.reserve(target_size);
    
    double step = static_cast<double>(data.size()) / target_size;
    for (size_t i = 0; i < target_size; ++i) {
        size_t index = static_cast<size_t>(i * step);
        sampled.push_back(data[index]);
    }
    return sampled;
}

// Usage with separate x/y vectors
auto sampled_x = sample_data(large_x_data, 5000);
auto sampled_y = sample_data(large_y_data, 5000);
plot.add_scatter(sampled_x, sampled_y, "Sampled", "blue");
```

#### 2. Data Aggregation
For trend analysis with massive datasets:

```cpp
void aggregate_points(const std::vector<double>& x_data, const std::vector<double>& y_data,
                     size_t bin_count, std::vector<double>& agg_x, std::vector<double>& agg_y) {
    
    // Find bounds
    auto x_minmax = std::minmax_element(x_data.begin(), x_data.end());
    double x_min = *x_minmax.first;
    double x_max = *x_minmax.second;
    double bin_width = (x_max - x_min) / bin_count;
    
    std::vector<std::vector<double>> bins(bin_count);
    std::vector<double> bin_centers(bin_count);
    
    // Populate bins
    for (size_t i = 0; i < x_data.size(); ++i) {
        int bin_idx = static_cast<int>((x_data[i] - x_min) / bin_width);
        bin_idx = std::max(0, std::min(static_cast<int>(bin_count - 1), bin_idx));
        bins[bin_idx].push_back(y_data[i]);
        bin_centers[bin_idx] = x_min + (bin_idx + 0.5) * bin_width;
    }
    
    // Calculate means
    agg_x.clear();
    agg_y.clear();
    for (size_t i = 0; i < bin_count; ++i) {
        if (!bins[i].empty()) {
            double mean_y = std::accumulate(bins[i].begin(), bins[i].end(), 0.0) / bins[i].size();
            agg_x.push_back(bin_centers[i]);
            agg_y.push_back(mean_y);
        }
    }
}
```

### Performance Benchmarking

```cpp
class PerformanceTimer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::string operation_name;
    
public:
    PerformanceTimer(const std::string& name) : operation_name(name) {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    ~PerformanceTimer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        std::cout << operation_name << " took " << duration.count() << "ms" << std::endl;
    }
};

// Usage
{
    PerformanceTimer timer("Large dataset plotting");
    plot.add_scatter(huge_x_data, huge_y_data, "Large Dataset", "blue");
    plot.save_png("output.png");
}
```

## Complex Dashboard Design

### Professional Layout Principles

#### 1. Information Hierarchy
```cpp
// Executive dashboard (3x3)
plotlib::SubplotManager dashboard(3, 3, 1800, 1200);
dashboard.set_main_title("Executive Performance Dashboard - Q4 2024");

// Row 1: High-level metrics (revenue, satisfaction, regional)
// Row 2: Operational details (efficiency, costs, products)  
// Row 3: Strategic insights (trends, risks, positioning)
```

#### 2. Consistent Color Schemes
```cpp
// Define domain-specific colors
const std::string REVENUE_COLOR = "green";
const std::string COST_COLOR = "red";
const std::string EFFICIENCY_COLOR = "blue";
const std::string RISK_COLOR = "orange";

// Apply consistently across related plots
revenue_plot.add_line(time_data, revenue_data, "Revenue", REVENUE_COLOR);
cost_plot.add_histogram(cost_data, "Costs", COST_COLOR);
```

#### 3. Logical Grouping
```cpp
// Group related metrics spatially
// Financial metrics: (0,0), (0,1), (0,2)
auto& revenue = dashboard.get_subplot<plotlib::LinePlot>(0, 0);
auto& costs = dashboard.get_subplot<plotlib::HistogramPlot>(0, 1);
auto& profit = dashboard.get_subplot<plotlib::ScatterPlot>(0, 2);

// Operational metrics: (1,0), (1,1), (1,2)
auto& efficiency = dashboard.get_subplot<plotlib::LinePlot>(1, 0);
auto& quality = dashboard.get_subplot<plotlib::HistogramPlot>(1, 1);
auto& capacity = dashboard.get_subplot<plotlib::ScatterPlot>(1, 2);
```

### Real-World Dashboard Examples

#### Scientific Research Dashboard
```cpp
// Research analysis with multiple data types
plotlib::SubplotManager research(2, 3, 1400, 1000);
research.set_main_title("Experimental Analysis Dashboard");

// Correlation analysis
auto& correlation = research.get_subplot<plotlib::ScatterPlot>(0, 0);
correlation.set_labels("Variable Correlation", "X", "Y");
std::vector<double> corr_x, corr_y;
// ... generate correlation data
correlation.add_scatter(corr_x, corr_y, "Experimental Data", "purple");

// Time series
auto& timeseries = research.get_subplot<plotlib::LinePlot>(0, 1);
timeseries.set_labels("Signal Over Time", "Time", "Amplitude");
timeseries.add_line(time_data, control_signal, "Control", "blue");
timeseries.add_line(time_data, treatment_signal, "Treatment", "red");

// Distribution comparison
auto& distributions = research.get_subplot<plotlib::HistogramPlot>(0, 2);
distributions.set_labels("Response Distribution", "Value", "Frequency");
distributions.add_histogram(before_data, "Before", "red", 30);
distributions.add_histogram(after_data, "After", "green", 30);
```

## Memory Management

### Efficient Data Handling

#### 1. Memory Pre-allocation
```cpp
// Reserve memory for known data sizes
std::vector<double> large_x, large_y;
large_x.reserve(expected_size);
large_y.reserve(expected_size);

// Use efficient data generation
for (size_t i = 0; i < expected_size; ++i) {
    large_x.push_back(generate_x(i));
    large_y.push_back(generate_y(i));
}
```

#### 2. Memory-Efficient Processing
```cpp
// Process large datasets in chunks
const size_t CHUNK_SIZE = 10000;
plotlib::ScatterPlot plot(800, 600);

for (size_t start = 0; start < total_data_size; start += CHUNK_SIZE) {
    size_t end = std::min(start + CHUNK_SIZE, total_data_size);
    
    std::vector<double> chunk_x(x_data.begin() + start, x_data.begin() + end);
    std::vector<double> chunk_y(y_data.begin() + start, y_data.begin() + end);
    
    plot.add_scatter(chunk_x, chunk_y, "Chunk " + std::to_string(start/CHUNK_SIZE));
}
```

## Advanced Plot Types

### Cluster Visualization
```cpp
// Generate clustered data
std::vector<double> cluster_x, cluster_y;
std::vector<int> cluster_labels;

// ... populate cluster data

// Use clustering functionality
plotlib::ScatterPlot cluster_plot(800, 600);
cluster_plot.set_labels("Cluster Analysis", "X", "Y");
cluster_plot.add_clusters(cluster_x, cluster_y, cluster_labels);
```

### Multi-Series Analysis
```cpp
// Compare multiple datasets efficiently
plotlib::LinePlot comparison(1000, 600);
comparison.set_labels("Performance Comparison", "Time", "Metric");

// Add multiple series with descriptive names
comparison.add_line(time_data, baseline_data, "Baseline", "black");
comparison.add_line(time_data, opt_v1_data, "Optimized v1", "blue");
comparison.add_line(time_data, opt_v2_data, "Optimized v2", "red");
comparison.add_line(time_data, target_data, "Target", "green");
```

## Integration Patterns

### Template-Based Plotting
```cpp
template<typename DataContainer>
void create_comparison_plot(const DataContainer& data1, const DataContainer& data2,
                          const std::string& title) {
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels(title, "X", "Y");
    
    // Convert container data to vectors
    std::vector<double> x1, y1, x2, y2;
    // ... extract data from containers
    
    plot.add_scatter(x1, y1, "Dataset 1", "blue");
    plot.add_scatter(x2, y2, "Dataset 2", "red");
    plot.save_png(title + ".png");
}
```

### Factory Pattern for Plot Creation
```cpp
class PlotFactory {
public:
    static std::unique_ptr<plotlib::ScatterPlot> create_scatter(
        const std::string& title, int width = 800, int height = 600) {
        auto plot = std::make_unique<plotlib::ScatterPlot>(width, height);
        plot->set_labels(title, "X", "Y");
        return plot;
    }
    
    static std::unique_ptr<plotlib::LinePlot> create_timeseries(
        const std::string& title, int width = 1000, int height = 400) {
        auto plot = std::make_unique<plotlib::LinePlot>(width, height);
        plot->set_labels(title, "Time", "Value");
        return plot;
    }
};
```

## Troubleshooting and Debugging

### Common Performance Issues

1. **Large datasets without sampling**
   ```cpp
   // Problem: Direct plotting of 100K+ points
   plot.add_scatter(huge_x, huge_y, "Raw");  // Slow!
   
   // Solution: Sample or aggregate
   auto sampled_x = sample_data(huge_x, 5000);
   auto sampled_y = sample_data(huge_y, 5000);
   plot.add_scatter(sampled_x, sampled_y, "Sampled");
   ```

2. **Memory inefficient data handling**
   ```cpp
   // Problem: Creating unnecessary copies
   std::vector<double> x_copy = original_x;  // Unnecessary copy
   
   // Solution: Use references or move semantics
   const auto& x_ref = original_x;  // No copy
   ```

### Debugging Visualization Issues

```cpp
// Add debug information to plots
plot.set_labels("Debug: " + debug_info, "X (range: " + x_range + ")", "Y");

// Verify data ranges
auto x_minmax = std::minmax_element(x_data.begin(), x_data.end());
auto y_minmax = std::minmax_element(y_data.begin(), y_data.end());
std::cout << "X range: [" << *x_minmax.first << ", " << *x_minmax.second << "]" << std::endl;
std::cout << "Y range: [" << *y_minmax.first << ", " << *y_minmax.second << "]" << std::endl;
```

## Best Practices Summary

1. **Use the simplified API**: Prefer `add_scatter()` with x/y vectors over complex data structures
2. **Sample large datasets**: Don't plot more than 10,000 points without sampling
3. **Pre-allocate memory**: Use `reserve()` for known data sizes
4. **Choose appropriate plot types**: Scatter for relationships, lines for trends, histograms for distributions
5. **Use consistent color schemes**: Maintain visual coherence across dashboards
6. **Profile performance**: Use timing tools for optimization
7. **Plan your layout**: Design dashboard hierarchy before implementation

## Advanced Resources

- **Examples**: Check `examples/advanced/` for complete working examples
- **Performance**: Study `03_performance_optimization_and_large_datasets.cpp`
- **Dashboards**: Explore `02_complex_dashboards_and_layouts.cpp`
- **Styling**: Reference `01_custom_styling_and_advanced_features.cpp`

Happy advanced plotting! 🚀📊 