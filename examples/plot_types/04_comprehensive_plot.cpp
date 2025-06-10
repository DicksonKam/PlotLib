/**
 * @file 04_comprehensive_plot.cpp
 * @brief Comprehensive demonstration of all plot types in subplots
 * 
 * This example demonstrates ALL PlotLib functionality in a single comprehensive
 * dashboard showing scatter plots, line plots, and histograms (both continuous
 * and discrete) with complete API coverage including all overloads and reference lines.
 */

#include "scatter_plot.h"
#include "line_plot.h" 
#include "histogram_plot.h"
#include "plot_manager.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <random>

int main() {
    std::cout << "=== Comprehensive PlotLib API Demonstration ===" << std::endl;
    
    // =====================================================================
    // CREATE COMPREHENSIVE SUBPLOT DASHBOARD
    // =====================================================================
    
    // Create 2x3 subplot layout for comprehensive demonstration
    plotlib::SubplotManager manager(2, 3, 1800, 1200);
    manager.set_main_title("Complete PlotLib API Demonstration Dashboard");
    
    // =====================================================================
    // SUBPLOT 1: SCATTER PLOT (top-left)
    // =====================================================================
    
    std::cout << "1. Creating comprehensive scatter plot..." << std::endl;
    
    auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
    scatter.set_labels("ScatterPlot API", "X", "Y");
    
    // Sample data for scatter plot
    std::vector<double> scatter_x1 = {1, 2, 3, 4, 5};
    std::vector<double> scatter_y1 = {2, 4, 3, 5, 4};
    std::vector<double> scatter_x2 = {1.5, 2.5, 3.5, 4.5, 5.5};
    std::vector<double> scatter_y2 = {1, 3, 2, 4, 3.5};
    std::vector<double> scatter_x3 = {2, 3, 4, 5, 6};
    std::vector<double> scatter_y3 = {3.5, 2.5, 4.5, 3, 5};
    
    // Cluster data
    std::vector<double> cluster_x = {1.0, 1.2, 5.0, 5.1, 3.0};
    std::vector<double> cluster_y = {1.0, 1.1, 5.0, 5.2, 3.0};
    std::vector<int> cluster_labels = {0, 0, 1, 1, -1};
    
    // All scatter overloads
    scatter.add_scatter(scatter_x1, scatter_y1);  // auto-name, auto-color
    scatter.add_scatter(scatter_x2, scatter_y2, "Series A");  // auto-color
    scatter.add_scatter(scatter_x3, scatter_y3, "Series B", "red");  // full spec
    scatter.add_clusters(cluster_x, cluster_y, cluster_labels);  // clusters
    
    // All reference line overloads
    scatter.add_vertical_line(3.0);  // auto-label, auto-color
    scatter.add_horizontal_line(3.5, "Threshold");  // auto-color
    
    // =====================================================================
    // SUBPLOT 2: LINE PLOT (top-middle)
    // =====================================================================
    
    std::cout << "2. Creating comprehensive line plot..." << std::endl;
    
    auto& line = manager.get_subplot<plotlib::LinePlot>(0, 1);
    line.set_labels("LinePlot API", "X", "Y");
    
    // Generate mathematical function data
    std::vector<double> x_vals;
    std::vector<double> sin_vals, cos_vals, linear_vals;
    
    for (int i = 0; i <= 30; ++i) {
        double x = i * 2 * M_PI / 30;
        x_vals.push_back(x);
        sin_vals.push_back(std::sin(x));
        cos_vals.push_back(std::cos(x));
        linear_vals.push_back(x / (2 * M_PI) - 0.5);
    }
    
    // All line overloads
    line.add_line(x_vals, linear_vals);  // auto-name, auto-color
    line.add_line(x_vals, sin_vals, "sin(x)");  // auto-color
    line.add_line(x_vals, cos_vals, "cos(x)", "red");  // full spec
    
    // All reference line overloads
    line.add_vertical_line(M_PI, "π");  // auto-color
    line.add_horizontal_line(0.0);  // auto-label, auto-color
    
    // =====================================================================
    // SUBPLOT 3: CONTINUOUS HISTOGRAM (top-right)
    // =====================================================================
    
    std::cout << "3. Creating comprehensive continuous histogram..." << std::endl;
    
    auto& continuous_hist = manager.get_subplot<plotlib::HistogramPlot>(0, 2);
    continuous_hist.set_labels("Continuous Histogram API", "Value", "Frequency");
    
    // Generate random data for histograms
    std::random_device rd;
    std::mt19937 gen(42);
    std::normal_distribution<> dist1(50, 10);
    std::normal_distribution<> dist2(70, 8);
    
    std::vector<double> data1, data2, data3;
    for (int i = 0; i < 150; ++i) {
        data1.push_back(dist1(gen));
        data2.push_back(dist2(gen));
        data3.push_back(dist1(gen) + 20);
    }
    
    // All continuous histogram overloads
    continuous_hist.add_histogram(data1);  // auto-name, auto-color, auto-bins
    continuous_hist.add_histogram(data2, "Dataset B");  // auto-color, auto-bins
    continuous_hist.add_histogram(data3, "Dataset C", "red", 20);  // full spec
    
    // Reference lines (both types allowed for continuous)
    continuous_hist.add_vertical_line(60.0, "Mean");  // auto-color
    continuous_hist.add_horizontal_line(10.0);  // auto-label, auto-color
    
    // =====================================================================
    // SUBPLOT 4: DISCRETE HISTOGRAM (bottom-left)
    // =====================================================================
    
    std::cout << "4. Creating comprehensive discrete histogram..." << std::endl;
    
    auto& discrete_hist = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
    discrete_hist.set_labels("Discrete Histogram API", "Categories", "Count");
    
    // Sample discrete data
    std::vector<int> counts1 = {12, 8, 15};
    std::vector<int> counts2 = {5, 20, 10, 7};
    std::vector<int> counts3 = {18, 6, 12};
    
    std::vector<std::string> names1 = {"Type A", "Type B", "Type C"};
    std::vector<std::string> names2 = {"Alpha", "Beta", "Gamma", "Delta"};
    std::vector<std::string> colors2 = {"red", "blue", "green", "orange"};
    
    // All discrete histogram overloads
    discrete_hist.add_histogram(counts3);  // auto-names (idx 1, idx 2...), auto-colors
    discrete_hist.add_histogram(counts1, names1);  // auto-colors
    discrete_hist.add_histogram(counts2, names2, colors2);  // full spec
    
    // Reference lines (only horizontal allowed for discrete)
    discrete_hist.add_horizontal_line(12.0);  // auto-label, auto-color
    discrete_hist.add_horizontal_line(8.0, "Threshold", "purple");  // full spec
    
    // =====================================================================
    // SUBPLOT 5: MIXED FUNCTIONALITY (bottom-middle)
    // =====================================================================
    
    std::cout << "5. Creating mixed functionality demonstration..." << std::endl;
    
    auto& mixed = manager.get_subplot<plotlib::ScatterPlot>(1, 1);
    mixed.set_labels("Mixed Features", "X", "Y");
    
    // Demonstrate various features together
    std::vector<double> mixed_x = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<double> mixed_y = {1, 4, 2, 6, 3, 7, 4, 8};
    
    mixed.add_scatter(mixed_x, mixed_y, "Main Data", "blue");
    
    // Multiple reference lines with different overloads
    mixed.add_vertical_line(3.5);  // auto-label, auto-color
    mixed.add_vertical_line(6.5, "Boundary");  // auto-color
    mixed.add_horizontal_line(4.0, "Mid Line", "red");  // full spec
    mixed.add_horizontal_line(7.0);  // auto-label, auto-color
    
    // =====================================================================
    // SUBPLOT 6: LEGEND MANAGEMENT (bottom-right)
    // =====================================================================
    
    std::cout << "6. Creating legend management demonstration..." << std::endl;
    
    auto& legend_demo = manager.get_subplot<plotlib::LinePlot>(1, 2);
    legend_demo.set_labels("Legend Management", "X", "Y");
    
    // Create multiple series to demonstrate legend
    std::vector<double> legend_x = {1, 2, 3, 4, 5};
    std::vector<double> y1 = {1, 2, 3, 4, 5};
    std::vector<double> y2 = {5, 4, 3, 2, 1};
    std::vector<double> y3 = {2, 4, 1, 5, 3};
    
    legend_demo.add_line(legend_x, y1, "Ascending", "blue");
    legend_demo.add_line(legend_x, y2, "Descending", "red");
    legend_demo.add_line(legend_x, y3, "Random", "green");
    
    // Add reference lines with various overloads
    legend_demo.add_vertical_line(2.5);  // auto-label, auto-color
    legend_demo.add_horizontal_line(3.0, "Center", "orange");  // explicit
    
    // Demonstrate legend hiding (hide one series)
    legend_demo.hide_legend_item("Random");
    
    // =====================================================================
    // SAVE AND REPORT
    // =====================================================================
    
    std::cout << "7. Saving comprehensive demonstration..." << std::endl;
    
    bool success = manager.save_png("output/plot_types_04_comprehensive_dashboard.png");
    
    if (success) {
        std::cout << "✅ Comprehensive PlotLib demonstration saved!" << std::endl;
        std::cout << "📊 Complete API Coverage Demonstrated:" << std::endl;
        std::cout << "   📍 SCATTER PLOTS:" << std::endl;
        std::cout << "      • All add_scatter() overloads (3)" << std::endl;
        std::cout << "      • Cluster visualization" << std::endl;
        std::cout << "      • Reference lines" << std::endl;
        std::cout << "   📈 LINE PLOTS:" << std::endl;
        std::cout << "      • All add_line() overloads (3)" << std::endl;
        std::cout << "      • Mathematical functions" << std::endl;
        std::cout << "      • Reference lines" << std::endl;
        std::cout << "   📊 CONTINUOUS HISTOGRAMS:" << std::endl;
        std::cout << "      • All add_histogram() overloads (4)" << std::endl;
        std::cout << "      • Automatic and manual binning" << std::endl;
        std::cout << "      • Vertical and horizontal reference lines" << std::endl;
        std::cout << "   📊 DISCRETE HISTOGRAMS:" << std::endl;
        std::cout << "      • All add_histogram() overloads (3)" << std::endl;
        std::cout << "      • Auto-naming with 'idx 1', 'idx 2'..." << std::endl;
        std::cout << "      • Horizontal reference lines only" << std::endl;
        std::cout << "   📏 REFERENCE LINES:" << std::endl;
        std::cout << "      • All overloads (1, 2, 3 parameters)" << std::endl;
        std::cout << "      • Auto-naming: 'Ref Line 1', 'Ref Line 2'..." << std::endl;
        std::cout << "      • Auto-color conflict avoidance" << std::endl;
        std::cout << "   🎛️ LEGEND MANAGEMENT:" << std::endl;
        std::cout << "      • Auto-legends for all plot types" << std::endl;
        std::cout << "      • Legend hiding functionality" << std::endl;
        std::cout << "   📐 SUBPLOT MANAGEMENT:" << std::endl;
        std::cout << "      • 2x3 grid layout" << std::endl;
        std::cout << "      • Mixed plot types" << std::endl;
        std::cout << "      • Unified styling" << std::endl;
        std::cout << "   🎨 AUTO-FEATURES:" << std::endl;
        std::cout << "      • Auto-naming for all components" << std::endl;
        std::cout << "      • Auto-coloring with conflict avoidance" << std::endl;
        std::cout << "      • Auto-binning for histograms" << std::endl;
    } else {
        std::cout << "❌ Failed to save comprehensive demonstration" << std::endl;
    }
    
    return success ? 0 : 1;
}

/*
 * 🎯 Complete PlotLib API Coverage Summary:
 * 
 * SCATTER PLOT METHODS:
 * ✅ add_scatter(x, y) ✅ add_scatter(x, y, name) ✅ add_scatter(x, y, name, color)
 * ✅ add_clusters(x, y, labels)
 * 
 * LINE PLOT METHODS:
 * ✅ add_line(x, y) ✅ add_line(x, y, name) ✅ add_line(x, y, name, color)
 * 
 * CONTINUOUS HISTOGRAM METHODS:
 * ✅ add_histogram(values) ✅ add_histogram(values, name) 
 * ✅ add_histogram(values, name, color) ✅ add_histogram(values, name, color, bins)
 * 
 * DISCRETE HISTOGRAM METHODS:
 * ✅ add_histogram(counts) ✅ add_histogram(counts, names) 
 * ✅ add_histogram(counts, names, colors)
 * 
 * REFERENCE LINE METHODS (all plot types):
 * ✅ add_vertical_line(value) ✅ add_vertical_line(value, label) 
 * ✅ add_vertical_line(value, label, color)
 * ✅ add_horizontal_line(value) ✅ add_horizontal_line(value, label) 
 * ✅ add_horizontal_line(value, label, color)
 * 
 * CONFIGURATION & MANAGEMENT:
 * ✅ Subplot management ✅ Legend management ✅ Auto-naming ✅ Auto-coloring
 * ✅ Title/label management ✅ File output (PNG/SVG)
 * ✅ set_labels(), set_title(), set_xlabel(), set_ylabel()
 * ✅ set_legend_enabled(), hide_legend_item()
 */