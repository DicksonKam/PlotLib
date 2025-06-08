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

### Precise Color Control

Use RGB values (0.0-1.0) for exact color specification:

```cpp
plotlib::PlotStyle custom_style;
custom_style.r = 0.2;      // 20% red
custom_style.g = 0.4;      // 40% green  
custom_style.b = 0.8;      // 80% blue
custom_style.alpha = 0.85; // 85% opacity
custom_style.point_size = 4.5;
custom_style.line_width = 2.0;
```

### Professional Color Schemes

```cpp
// Corporate blue palette
plotlib::PlotStyle corporate_blue = {0.2, 0.4, 0.8, 0.9, 4.0, 2.0, "Corporate"};
plotlib::PlotStyle corporate_light = {0.6, 0.7, 0.9, 0.7, 3.0, 1.5, "Light"};

// Scientific color schemes
plotlib::PlotStyle scientific_red = {0.8, 0.2, 0.2, 0.9, 3.5, 2.0, "Treatment"};
plotlib::PlotStyle scientific_blue = {0.2, 0.2, 0.8, 0.9, 3.5, 2.0, "Control"};
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

// Usage
auto sampled_data = sample_data(large_dataset, 5000);
plot.add_data("Sampled", sampled_data, "blue");
```

#### 2. Data Aggregation
For trend analysis with massive datasets:

```cpp
std::vector<plotlib::Point2D> aggregate_points(
    const std::vector<plotlib::Point2D>& points, 
    size_t bin_count) {
    
    // Find bounds
    auto x_minmax = std::minmax_element(points.begin(), points.end(),
        [](const auto& a, const auto& b) { return a.x < b.x; });
    
    double x_min = x_minmax.first->x;
    double x_max = x_minmax.second->x;
    double bin_width = (x_max - x_min) / bin_count;
    
    std::vector<std::vector<double>> bins(bin_count);
    
    // Populate bins
    for (const auto& point : points) {
        int bin_idx = static_cast<int>((point.x - x_min) / bin_width);
        bin_idx = std::max(0, std::min(static_cast<int>(bin_count - 1), bin_idx));
        bins[bin_idx].push_back(point.y);
    }
    
    // Calculate means
    std::vector<plotlib::Point2D> aggregated;
    for (size_t i = 0; i < bin_count; ++i) {
        if (!bins[i].empty()) {
            double mean_y = std::accumulate(bins[i].begin(), bins[i].end(), 0.0) / bins[i].size();
            double x_center = x_min + (i + 0.5) * bin_width;
            aggregated.emplace_back(x_center, mean_y);
        }
    }
    return aggregated;
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
    plot.add_data("Large Dataset", huge_dataset, "blue");
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
revenue_plot.add_line("Revenue", data, REVENUE_COLOR);
cost_plot.add_histogram("Costs", cost_data, COST_COLOR);
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

### Advanced Dashboard Patterns

#### Scientific Research Dashboard
```cpp
plotlib::SubplotManager research(4, 2, 1600, 1400);

// Time series analysis
auto& temporal = research.get_subplot<plotlib::LinePlot>(0, 0);
temporal.set_show_markers(true);
temporal.add_line("Control", time_data, control_signal, "blue");
temporal.add_line("Treatment", time_data, treatment_signal, "red");

// Statistical distributions
auto& distributions = research.get_subplot<plotlib::HistogramPlot>(0, 1);
distributions.set_normalize(true);  // Probability density
distributions.add_histogram("Control", control_data, "blue", 30);
distributions.add_histogram("Treatment", treatment_data, "red", 30);

// Correlation analysis
auto& correlation = research.get_subplot<plotlib::ScatterPlot>(1, 0);
correlation.add_data("Experimental Data", correlation_points, "purple");

// Error analysis
auto& errors = research.get_subplot<plotlib::HistogramPlot>(1, 1);
errors.add_histogram("Residuals", residual_data, "orange", 25);
```

## Memory Management

### Efficient Memory Usage

#### 1. Reserve Capacity
```cpp
// Reserve memory upfront to avoid reallocations
std::vector<plotlib::Point2D> data;
data.reserve(expected_size);

// Use emplace_back for efficiency
for (size_t i = 0; i < size; ++i) {
    data.emplace_back(x_values[i], y_values[i]);
}
```

#### 2. Memory Cleanup
```cpp
// Clear unused data
large_dataset.clear();
large_dataset.shrink_to_fit();  // Release memory to OS

// Use RAII for automatic cleanup
{
    std::vector<plotlib::Point2D> temp_data(1000000);
    // ... use temp_data
} // Automatically freed here
```

#### 3. Real-time Data Patterns
```cpp
// Rolling buffer for continuous data
class RollingBuffer {
private:
    std::vector<double> buffer;
    size_t capacity;
    size_t current_pos = 0;
    bool is_full = false;
    
public:
    RollingBuffer(size_t size) : capacity(size) {
        buffer.reserve(size);
    }
    
    void add_point(double value) {
        if (buffer.size() < capacity) {
            buffer.push_back(value);
        } else {
            buffer[current_pos] = value;
            current_pos = (current_pos + 1) % capacity;
            is_full = true;
        }
    }
    
    std::vector<double> get_data() const {
        if (!is_full) return buffer;
        
        std::vector<double> result;
        result.reserve(capacity);
        
        // Copy from current position to end
        result.insert(result.end(), 
                     buffer.begin() + current_pos, buffer.end());
        // Copy from beginning to current position
        result.insert(result.end(), 
                     buffer.begin(), buffer.begin() + current_pos);
        
        return result;
    }
};
```

## Advanced Plot Types

### Cluster Analysis Visualization

```cpp
// Generate cluster data with outliers
std::vector<plotlib::Point2D> points;
std::vector<int> labels;

// Cluster 1: Dense cluster
std::normal_distribution<> cluster1_x(20, 5);
std::normal_distribution<> cluster1_y(30, 4);
for (int i = 0; i < 50; ++i) {
    points.emplace_back(cluster1_x(gen), cluster1_y(gen));
    labels.push_back(0);
}

// Add outliers (label -1)
for (int i = 0; i < 10; ++i) {
    points.emplace_back(outlier_x(gen), outlier_y(gen));
    labels.push_back(-1);
}

// Visualize clusters
plot.add_cluster_data("DBSCAN Results", points, labels, 4.0, 0.8);
```

### Statistical Analysis

```cpp
// Normalized histograms for probability density
histogram.set_normalize(true);
histogram.add_histogram("Distribution A", data_a, "blue", 30);
histogram.add_histogram("Distribution B", data_b, "red", 30);

// Get statistics
auto stats_a = histogram.get_statistics("Distribution A");
auto stats_b = histogram.get_statistics("Distribution B");

std::cout << "Mean A: " << stats_a.first << ", Std A: " << stats_a.second << std::endl;
std::cout << "Mean B: " << stats_b.first << ", Std B: " << stats_b.second << std::endl;
```

### Signal Processing Visualization

```cpp
// Complex signal with multiple components
for (size_t i = 0; i < TIME_SERIES_SIZE; ++i) {
    double t = i * 0.001;  // 1ms resolution
    
    double signal = 2.0 * std::sin(2 * M_PI * 10 * t) +     // 10 Hz
                   1.0 * std::sin(2 * M_PI * 50 * t) +      // 50 Hz  
                   0.5 * std::sin(2 * M_PI * 100 * t) +     // 100 Hz
                   noise_dist(gen);                          // Noise
    
    time_points.push_back(t);
    signal_values.push_back(signal);
}

// Efficient plotting with downsampling
std::vector<double> downsampled_time, downsampled_signal;
for (size_t i = 0; i < TIME_SERIES_SIZE; i += 10) {  // Every 10th point
    downsampled_time.push_back(time_points[i]);
    downsampled_signal.push_back(signal_values[i]);
}

line_plot.add_line("Signal", downsampled_time, downsampled_signal, "blue");
```

## Integration Patterns

### Template-Based Generic Plotting

```cpp
template<typename DataContainer>
void plot_generic_data(const DataContainer& data, 
                      const std::string& title,
                      const std::string& color = "blue") {
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels(title, "X", "Y");
    
    std::vector<plotlib::Point2D> points;
    points.reserve(data.size());
    
    for (const auto& item : data) {
        points.emplace_back(item.x, item.y);
    }
    
    plot.add_data("Data", points, color);
    plot.save_png("output/" + title + ".png");
}
```

### Factory Pattern for Plot Creation

```cpp
class PlotFactory {
public:
    enum class PlotType { SCATTER, LINE, HISTOGRAM };
    
    template<typename PlotT>
    static std::unique_ptr<PlotT> create_plot(int width, int height) {
        return std::make_unique<PlotT>(width, height);
    }
    
    static std::unique_ptr<plotlib::PlotManager> create_plot(
        PlotType type, int width, int height) {
        switch (type) {
            case PlotType::SCATTER:
                return std::make_unique<plotlib::ScatterPlot>(width, height);
            case PlotType::LINE:
                return std::make_unique<plotlib::LinePlot>(width, height);
            case PlotType::HISTOGRAM:
                return std::make_unique<plotlib::HistogramPlot>(width, height);
            default:
                throw std::invalid_argument("Unknown plot type");
        }
    }
};
```

### Configuration-Driven Plotting

```cpp
struct PlotConfig {
    std::string title;
    std::string x_label;
    std::string y_label;
    int width = 800;
    int height = 600;
    std::string output_file;
    bool show_legend = true;
    bool normalize_histogram = false;
};

class ConfigurablePlot {
public:
    template<typename PlotT>
    static void create_from_config(const PlotConfig& config) {
        PlotT plot(config.width, config.height);
        plot.set_labels(config.title, config.x_label, config.y_label);
        plot.set_legend_enabled(config.show_legend);
        
        if constexpr (std::is_same_v<PlotT, plotlib::HistogramPlot>) {
            plot.set_normalize(config.normalize_histogram);
        }
        
        // Add data based on configuration...
        plot.save_png(config.output_file);
    }
};
```

## Troubleshooting and Debugging

### Performance Issues

#### Symptoms: Slow rendering with large datasets
**Solutions:**
1. Use data sampling: `sample_data(dataset, 5000)`
2. Implement data aggregation for trend analysis
3. Consider switching to line plots for time series
4. Disable markers: `line_plot.set_show_markers(false)`

#### Symptoms: High memory usage
**Solutions:**
1. Reserve vector capacity: `data.reserve(expected_size)`
2. Clear unused data: `data.clear(); data.shrink_to_fit()`
3. Use rolling buffers for real-time data
4. Process data in chunks

### Visual Quality Issues

#### Symptoms: Overlapping points in scatter plots
**Solutions:**
1. Reduce point size: `style.point_size = 2.0`
2. Increase transparency: `style.alpha = 0.6`
3. Use data aggregation or sampling
4. Consider switching to density plots

#### Symptoms: Legend overcrowding
**Solutions:**
1. Hide less important series: `plot.hide_legend_item("series")`
2. Use shorter labels: `style.label = "Short"`
3. Increase plot size to accommodate legend
4. Group similar series

### Common Compilation Issues

#### Missing includes:
```cpp
#include <vector>      // For std::vector
#include <random>      // For random number generation
#include <algorithm>   // For std::minmax_element
#include <numeric>     // For std::accumulate
#include <chrono>      // For performance timing
```

#### Template instantiation errors:
```cpp
// Explicit template instantiation
auto& subplot = dashboard.get_subplot<plotlib::LinePlot>(0, 0);
// Not: auto& subplot = dashboard.get_subplot(0, 0);
```

### Best Practices Summary

1. **Performance**: Always profile before optimizing
2. **Memory**: Reserve capacity, use RAII, clear unused data
3. **Visual Design**: Consistent colors, logical grouping, appropriate plot types
4. **Code Organization**: Use templates, factories, and configuration patterns
5. **Debugging**: Start simple, add complexity incrementally
6. **Documentation**: Comment complex algorithms and design decisions

### Advanced Example References

See the advanced examples for complete implementations:
- `examples/advanced/01_custom_styling_and_advanced_features.cpp`
- `examples/advanced/02_complex_dashboards_and_layouts.cpp`
- `examples/advanced/03_performance_optimization_and_large_datasets.cpp`

These examples demonstrate real-world usage patterns and advanced techniques for professional-quality visualizations. 