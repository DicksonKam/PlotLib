#include "scatter_plot.h"
#include "line_plot.h"
#include "histogram_plot.h"
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::cout << "=== PlotLib Reference Lines and Annotations Demo ===" << std::endl;
    
    // Example 1: Scatter plot with reference lines
    std::cout << "\n1. Creating scatter plot with reference lines..." << std::endl;
    
    plotlib::ScatterPlot scatter_plot(800, 600);
    scatter_plot.set_labels("Scatter Plot with Reference Lines", "X Values", "Y Values");
    
    // Generate sample data
    std::vector<plotlib::Point2D> data_points;
    for (int i = 0; i < 50; ++i) {
        double x = i * 0.2;
        double y = 2.5 * x + 3.0 + (rand() % 100 - 50) * 0.1;  // Linear trend with noise
        if (x > 5.0) {
            y += (x - 5.0) * 0.5;  // Add some curvature
        }
        data_points.push_back(plotlib::Point2D(x, y));
    }
    
    // Add data with custom styling
    plotlib::PlotStyle red_style = plotlib::PlotManager::color_to_style("red", 3.0, 2.0);
    scatter_plot.add_series("Experimental Data", data_points, red_style);
    
    // Add vertical reference line at x = 5.0
    scatter_plot.add_vertical_line(5.0, "Threshold X = 5.0");
    
    // Add horizontal reference line at y = 15.0
    plotlib::PlotStyle green_style = plotlib::PlotManager::color_to_style("green", 3.0, 2.0);
    green_style.line_width = 2.0;
    scatter_plot.add_horizontal_line(15.0, "Target Y = 15.0", green_style);
    
    scatter_plot.save_png("output/advanced_04_scatter_refs.png");
    
    // Example 2: Line plot with multiple reference lines
    std::cout << "2. Creating line plot with multiple reference lines..." << std::endl;
    
    plotlib::LinePlot line_plot(800, 600);
    line_plot.set_labels("Line Plot with Reference Lines", "Time (hours)", "Temperature (°C)");
    
    // Generate temperature data
    std::vector<double> time_values, temp_values;
    for (int i = 0; i <= 24; ++i) {
        double t = i;
        double temp = 20.0 + 8.0 * sin(t * M_PI / 12.0) + (rand() % 100 - 50) * 0.05;
        time_values.push_back(t);
        temp_values.push_back(temp);
    }
    
    plotlib::PlotStyle blue_style = plotlib::PlotManager::color_to_style("blue", 3.0, 2.0);
    line_plot.add_line("Temperature", time_values, temp_values, "blue");
    
    // Add reference lines for comfort zone
    line_plot.add_horizontal_line(22.0, "Comfort Min");
    line_plot.add_horizontal_line(26.0, "Comfort Max");
    
    // Add reference lines for critical times
    plotlib::PlotStyle purple_style = plotlib::PlotManager::color_to_style("purple", 3.0, 2.0);
    purple_style.line_width = 1.5;
    line_plot.add_vertical_line(6.0, "Sunrise", purple_style);
    line_plot.add_vertical_line(18.0, "Sunset", purple_style);
    
    line_plot.save_png("output/advanced_04_line_refs.png");
    
    // Example 3: Histogram with statistical reference lines
    std::cout << "3. Creating histogram with statistical reference lines..." << std::endl;
    
    plotlib::HistogramPlot hist_plot(800, 600);
    hist_plot.set_labels("Histogram with Statistical References", "Values", "Frequency");
    
    // Generate normal distribution data
    std::vector<double> normal_data;
    for (int i = 0; i < 1000; ++i) {
        // Box-Muller transform for normal distribution
        static bool has_spare = false;
        static double spare;
        
        if (has_spare) {
            has_spare = false;
            normal_data.push_back(spare * 2.0 + 10.0);  // Scale and shift
        } else {
            has_spare = true;
            double u = (rand() + 1.0) / (RAND_MAX + 2.0);
            double v = (rand() + 1.0) / (RAND_MAX + 2.0);
            double mag = 2.0 * sqrt(-log(u));
            spare = mag * cos(2.0 * M_PI * v);
            normal_data.push_back(mag * sin(2.0 * M_PI * v) * 2.0 + 10.0);
        }
    }
    
    plotlib::PlotStyle blue_style2 = plotlib::PlotManager::color_to_style("blue", 3.0, 2.0);
    hist_plot.add_data("Normal Distribution", normal_data, blue_style2, 30);
    
    // Add reference lines for mean and standard deviations
    plotlib::PlotStyle red_ref_style;
    red_ref_style.r = 1.0; red_ref_style.g = 0.0; red_ref_style.b = 0.0;
    red_ref_style.line_width = 2.0;
    red_ref_style.alpha = 0.8;
    
    plotlib::PlotStyle orange_ref_style;
    orange_ref_style.r = 1.0; orange_ref_style.g = 0.5; orange_ref_style.b = 0.0;
    orange_ref_style.line_width = 1.5;
    orange_ref_style.alpha = 0.7;
    
    hist_plot.add_vertical_line(10.0, "Mean", red_ref_style);
    hist_plot.add_vertical_line(8.0, "-1σ", orange_ref_style);
    hist_plot.add_vertical_line(12.0, "+1σ", orange_ref_style);
    
    hist_plot.save_png("output/advanced_04_histogram_refs.png");
    
    // Example 4: Complex subplot with reference lines
    std::cout << "4. Creating complex subplot with reference lines..." << std::endl;
    
    plotlib::SubplotManager subplots(2, 2, 1200, 900);
    subplots.set_main_title("Reference Lines in Multiple Plot Types");
    
    // Subplot 1: Scatter with trend line reference
    auto& subplot1 = subplots.get_subplot<plotlib::ScatterPlot>(0, 0);
    subplot1.set_labels("Correlation Analysis", "Variable X", "Variable Y");
    
    std::vector<plotlib::Point2D> correlation_data;
    for (int i = 0; i < 30; ++i) {
        double x = i * 0.5;
        double y = 1.2 * x + 2.0 + (rand() % 100 - 50) * 0.2;
        correlation_data.push_back(plotlib::Point2D(x, y));
    }
    subplot1.add_data("Data Points", correlation_data, "blue");
    subplot1.add_vertical_line(7.5, "Midpoint");
    
    // Subplot 2: Line plot with thresholds
    auto& subplot2 = subplots.get_subplot<plotlib::LinePlot>(0, 1);
    subplot2.set_labels("Performance Monitoring", "Time", "Performance");
    
    std::vector<plotlib::Point2D> performance_data;
    for (int i = 0; i <= 20; ++i) {
        double x = i;
        double y = 50.0 + 20.0 * sin(x * 0.3) + (rand() % 100 - 50) * 0.3;
        performance_data.push_back(plotlib::Point2D(x, y));
    }
    subplot2.add_line("Performance", performance_data, "green");
    subplot2.add_horizontal_line(60.0, "Target");
    subplot2.add_horizontal_line(40.0, "Minimum");
    
    // Subplot 3: Histogram with percentiles
    auto& subplot3 = subplots.get_subplot<plotlib::HistogramPlot>(1, 0);
    subplot3.set_labels("Distribution Analysis", "Values", "Count");
    
    std::vector<double> dist_data;
    for (int i = 0; i < 500; ++i) {
        double val = 25.0 + (rand() % 1000 - 500) * 0.02;
        dist_data.push_back(val);
    }
    subplot3.add_histogram("Sample Data", dist_data, "purple", 25);
    subplot3.add_vertical_line(25.0, "Median");
    
    // Subplot 4: Multi-series scatter with reference grid
    auto& subplot4 = subplots.get_subplot<plotlib::ScatterPlot>(1, 1);
    subplot4.set_labels("Multi-Series Analysis", "Factor A", "Factor B");
    
    std::vector<plotlib::Point2D> dataset_b;
    for (int i = 0; i < 25; ++i) {
        double x = (rand() % 100) * 0.1;
        double y = (rand() % 100) * 0.1;
        dataset_b.push_back(plotlib::Point2D(x, y));
    }
    
    std::vector<plotlib::Point2D> dataset_c;
    for (int i = 0; i < 25; ++i) {
        double x = 5.0 + (rand() % 100) * 0.05;
        double y = 5.0 + (rand() % 100) * 0.05;
        dataset_c.push_back(plotlib::Point2D(x, y));
    }
    plotlib::PlotStyle yellow_style = plotlib::PlotManager::color_to_style("orange", 3.0, 2.0);
    subplot4.add_series("Group A", dataset_b, yellow_style);
    subplot4.add_data("Group B", dataset_c, "cyan");
    subplot4.add_vertical_line(5.0, "Separator");
    subplot4.add_horizontal_line(5.0, "Baseline");
    
    subplots.save_png("output/advanced_04_complex_subplots.png");
    
    std::cout << "\n✅ All plots saved successfully!" << std::endl;
    std::cout << "Check the output/ directory for:" << std::endl;
    std::cout << "  - advanced_04_scatter_refs.png" << std::endl;
    std::cout << "  - advanced_04_line_refs.png" << std::endl;
    std::cout << "  - advanced_04_histogram_refs.png" << std::endl;
    std::cout << "  - advanced_04_complex_subplots.png" << std::endl;
    
    return 0;
} 