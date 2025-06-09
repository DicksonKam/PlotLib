#include "scatter_plot.h"
#include "line_plot.h"
#include "histogram_plot.h"
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::cout << "=== PlotLib Advanced Plotting Demo ===" << std::endl;
    
    // Example 1: Scatter plot with advanced features
    std::cout << "\n1. Creating scatter plot with advanced styling..." << std::endl;
    
    plotlib::ScatterPlot scatter_plot(800, 600);
    scatter_plot.set_labels("Advanced Scatter Plot", "X Values", "Y Values");
    
    // Generate sample data using separate x/y vectors
    std::vector<double> data_x, data_y;
    for (int i = 0; i < 50; ++i) {
        double x = i * 0.2;
        double y = 2.5 * x + 3.0 + (rand() % 100 - 50) * 0.1;  // Linear trend with noise
        if (x > 5.0) {
            y += (x - 5.0) * 0.5;  // Add some curvature
        }
        data_x.push_back(x);
        data_y.push_back(y);
    }
    
    // Add data with custom color
    scatter_plot.add_scatter("Experimental Data", data_x, data_y, "red");
    
    scatter_plot.save_png("output/advanced_04_scatter_advanced.png");
    
    // Example 2: Line plot with multiple series
    std::cout << "2. Creating line plot with multiple temperature series..." << std::endl;
    
    plotlib::LinePlot line_plot(800, 600);
    line_plot.set_labels("Temperature Monitoring", "Time (hours)", "Temperature (°C)");
    
    // Generate temperature data
    std::vector<double> time_values, temp_values, target_temp;
    for (int i = 0; i <= 24; ++i) {
        double t = i;
        double temp = 20.0 + 8.0 * sin(t * M_PI / 12.0) + (rand() % 100 - 50) * 0.05;
        time_values.push_back(t);
        temp_values.push_back(temp);
        target_temp.push_back(24.0);  // Target temperature line
    }
    
    line_plot.add_line("Actual Temperature", time_values, temp_values, "blue");
    line_plot.add_line("Target Temperature", time_values, target_temp, "red");
    
    line_plot.save_png("output/advanced_04_line_multiSeries.png");
    
    // Example 3: Histogram with multiple distributions
    std::cout << "3. Creating histogram with multiple distributions..." << std::endl;
    
    plotlib::HistogramPlot hist_plot(800, 600);
    hist_plot.set_labels("Distribution Comparison", "Values", "Frequency");
    
    // Generate normal distribution data
    std::vector<double> normal_data, shifted_data;
    for (int i = 0; i < 1000; ++i) {
        // Box-Muller transform for normal distribution
        static bool has_spare = false;
        static double spare;
        
        if (has_spare) {
            has_spare = false;
            double val = spare * 2.0 + 10.0;  // Scale and shift
            normal_data.push_back(val);
            shifted_data.push_back(val + 3.0);  // Shifted distribution
        } else {
            has_spare = true;
            double u = (rand() + 1.0) / (RAND_MAX + 2.0);
            double v = (rand() + 1.0) / (RAND_MAX + 2.0);
            double mag = 2.0 * sqrt(-log(u));
            spare = mag * cos(2.0 * M_PI * v);
            double val = mag * sin(2.0 * M_PI * v) * 2.0 + 10.0;
            normal_data.push_back(val);
            shifted_data.push_back(val + 3.0);
        }
    }
    
    hist_plot.add_histogram("Original Distribution", normal_data, "blue", 30);
    hist_plot.add_histogram("Shifted Distribution", shifted_data, "orange", 30);
    
    hist_plot.save_png("output/advanced_04_histogram_multiDist.png");
    
    // Example 4: Complex subplot with multiple plot types
    std::cout << "4. Creating complex subplot with multiple plot types..." << std::endl;
    
    plotlib::SubplotManager subplots(2, 2, 1200, 900);
    subplots.set_main_title("Advanced Multi-Plot Analysis Dashboard");
    
    // Subplot 1: Scatter with correlation analysis
    auto& subplot1 = subplots.get_subplot<plotlib::ScatterPlot>(0, 0);
    subplot1.set_labels("Correlation Analysis", "Variable X", "Variable Y");
    
    std::vector<double> corr_x, corr_y;
    for (int i = 0; i < 30; ++i) {
        double x = i * 0.5;
        double y = 1.2 * x + 2.0 + (rand() % 100 - 50) * 0.2;
        corr_x.push_back(x);
        corr_y.push_back(y);
    }
    subplot1.add_scatter("Data Points", corr_x, corr_y, "blue");
    
    // Subplot 2: Line plot with performance monitoring
    auto& subplot2 = subplots.get_subplot<plotlib::LinePlot>(0, 1);
    subplot2.set_labels("Performance Monitoring", "Time", "Performance");
    
    std::vector<double> perf_time, perf_value, threshold_value;
    for (int i = 0; i <= 20; ++i) {
        double t = i;
        double perf = 50.0 + 20.0 * sin(t * 0.3) + (rand() % 100 - 50) * 0.3;
        perf_time.push_back(t);
        perf_value.push_back(perf);
        threshold_value.push_back(60.0);  // Performance threshold
    }
    subplot2.add_line("Performance", perf_time, perf_value, "green");
    subplot2.add_line("Target", perf_time, threshold_value, "red");
    
    // Subplot 3: Histogram with distribution analysis
    auto& subplot3 = subplots.get_subplot<plotlib::HistogramPlot>(1, 0);
    subplot3.set_labels("Distribution Analysis", "Values", "Count");
    
    std::vector<double> dist_data;
    for (int i = 0; i < 500; ++i) {
        double val = 25.0 + (rand() % 1000 - 500) * 0.02;
        dist_data.push_back(val);
    }
    subplot3.add_histogram("Sample Data", dist_data, "purple", 25);
    
    // Subplot 4: Multi-series scatter analysis
    auto& subplot4 = subplots.get_subplot<plotlib::ScatterPlot>(1, 1);
    subplot4.set_labels("Multi-Group Analysis", "Factor A", "Factor B");
    
    std::vector<double> group_a_x, group_a_y, group_b_x, group_b_y;
    for (int i = 0; i < 25; ++i) {
        // Group A data (lower range)
        group_a_x.push_back((rand() % 100) * 0.1);
        group_a_y.push_back((rand() % 100) * 0.1);
        
        // Group B data (higher range)
        group_b_x.push_back(5.0 + (rand() % 100) * 0.05);
        group_b_y.push_back(5.0 + (rand() % 100) * 0.05);
    }
    
    subplot4.add_scatter("Group A", group_a_x, group_a_y, "orange");
    subplot4.add_scatter("Group B", group_b_x, group_b_y, "cyan");
    
    subplots.save_png("output/advanced_04_complex_subplots.png");
    
    std::cout << "\n✅ All plots saved successfully!" << std::endl;
    std::cout << "Check the output/ directory for:" << std::endl;
    std::cout << "  - advanced_04_scatter_advanced.png" << std::endl;
    std::cout << "  - advanced_04_line_multiSeries.png" << std::endl;
    std::cout << "  - advanced_04_histogram_multiDist.png" << std::endl;
    std::cout << "  - advanced_04_complex_subplots.png" << std::endl;
    
    return 0;
} 