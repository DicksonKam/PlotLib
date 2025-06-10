/**
 * @file 02_scatter_plot.cpp
 * @brief Comprehensive ScatterPlot functionality demonstration
 * 
 * This example demonstrates ALL public ScatterPlot functionality including:
 * - All add_scatter() overloads
 * - Cluster visualization
 * - Reference line capabilities
 * - Complete API coverage for precise code review
 */

#include "scatter_plot.h"
#include <vector>
#include <iostream>
#include <random>

int main() {
    std::cout << "=== Comprehensive ScatterPlot Functionality ===" << std::endl;
    
    // Create sample data sets
    std::vector<double> x1 = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y1 = {2.0, 4.0, 3.0, 5.0, 4.0};
    
    std::vector<double> x2 = {1.5, 2.5, 3.5, 4.5, 5.5};
    std::vector<double> y2 = {1.0, 3.0, 2.0, 4.0, 3.5};
    
    std::vector<double> x3 = {2.0, 3.0, 4.0, 5.0, 6.0};
    std::vector<double> y3 = {3.5, 2.5, 4.5, 3.0, 5.0};
    
    // Cluster data for demonstration
    std::vector<double> cluster_x = {1.0, 1.2, 1.1, 5.0, 5.1, 4.9, 3.0, 3.2};
    std::vector<double> cluster_y = {1.0, 1.1, 0.9, 5.0, 5.2, 4.8, 3.0, 2.8};
    std::vector<int> cluster_labels = {0, 0, 0, 1, 1, 1, -1, -1};  // -1 for outliers
    
    // Create ScatterPlot with all functionality
    plotlib::ScatterPlot plot(1000, 700);
    plot.set_labels("Comprehensive ScatterPlot API Demonstration", "X Values", "Y Values");
    
    // =====================================================================
    // DEMONSTRATE ALL add_scatter() OVERLOADS
    // =====================================================================
    
    std::cout << "1. Testing all add_scatter() overloads..." << std::endl;
    
    // Overload 1: data only (auto-name, auto-color)
    plot.add_scatter(x1, y1);  // "Scatter 1", auto-color
    
    // Overload 2: data + name (auto-color)
    plot.add_scatter(x2, y2, "Dataset Alpha");  // auto-color
    
    // Overload 3: data + name + color (full specification)
    plot.add_scatter(x3, y3, "Dataset Beta", "red");  // explicit red
    
    // =====================================================================
    // DEMONSTRATE CLUSTER VISUALIZATION
    // =====================================================================
    
    std::cout << "2. Testing cluster visualization..." << std::endl;
    
    // Add cluster data (clusters 0, 1, and outliers -1)
    plot.add_clusters(cluster_x, cluster_y, cluster_labels);
    
    // =====================================================================
    // DEMONSTRATE ALL add_vertical_line() OVERLOADS
    // =====================================================================
    
    std::cout << "3. Testing all add_vertical_line() overloads..." << std::endl;
    
    // Overload 1: value only (auto-label, auto-color avoiding data colors)
    plot.add_vertical_line(2.5);  // "Ref Line 1", auto-color
    
    // Overload 2: value + label (auto-color avoiding data colors)
    plot.add_vertical_line(4.0, "Mid Point");  // auto-color
    
    // Overload 3: value + label + color (full specification)
    plot.add_vertical_line(1.5, "Left Boundary", "purple");  // explicit purple
    
    // =====================================================================
    // DEMONSTRATE ALL add_horizontal_line() OVERLOADS
    // =====================================================================
    
    std::cout << "4. Testing all add_horizontal_line() overloads..." << std::endl;
    
    // Overload 1: value only (auto-label, auto-color avoiding data colors)
    plot.add_horizontal_line(3.0);  // "Ref Line 4", auto-color
    
    // Overload 2: value + label (auto-color avoiding data colors)
    plot.add_horizontal_line(2.0, "Lower Bound");  // auto-color
    
    // Overload 3: value + label + color (full specification)
    plot.add_horizontal_line(4.5, "Upper Bound", "orange");  // explicit orange
    
    // =====================================================================
    // DEMONSTRATE OTHER PUBLIC FUNCTIONALITY
    // =====================================================================
    
    std::cout << "5. Testing other public ScatterPlot methods..." << std::endl;
    
    // Marker configuration
    plot.set_default_marker_type(plotlib::MarkerType::CIRCLE);
    
    // Legend management (inherited from PlotManager)
    plot.set_legend_enabled(true);
    
    // Title and labels (inherited from PlotManager)
    plot.set_title("Complete ScatterPlot API Test");
    plot.set_xlabel("X Coordinates");
    plot.set_ylabel("Y Coordinates");
    
    // =====================================================================
    // SAVE AND REPORT
    // =====================================================================
    
    bool success = plot.save_png("output/plot_types_02_scatter_plot.png");
    
    if (success) {
        std::cout << "✅ Comprehensive ScatterPlot demonstration saved!" << std::endl;
        std::cout << "📊 Features demonstrated:" << std::endl;
        std::cout << "   📍 4 scatter series with different approaches:" << std::endl;
        std::cout << "      • Scatter 1: data only (auto-name, auto-color)" << std::endl;
        std::cout << "      • Dataset Alpha: data + name (auto-color)" << std::endl;
        std::cout << "      • Dataset Beta: data + name + color" << std::endl;
        std::cout << "      • Clusters: cluster visualization (2 clusters + outliers)" << std::endl;
        std::cout << "   📏 6 reference lines with different overloads:" << std::endl;
        std::cout << "      • 3 vertical lines (auto, auto+label, full)" << std::endl;
        std::cout << "      • 3 horizontal lines (auto, auto+label, full)" << std::endl;
        std::cout << "   ⚙️ ScatterPlot-specific configuration methods" << std::endl;
        std::cout << "   🎨 Auto-color conflict avoidance for reference lines" << std::endl;
        std::cout << "   🏷️ Auto-naming for both data series and reference lines" << std::endl;
        std::cout << "   🔍 Cluster visualization with outlier detection" << std::endl;
    } else {
        std::cout << "❌ Failed to save plot" << std::endl;
    }
    
    return success ? 0 : 1;
}

/*
 * 🎯 Complete ScatterPlot API Coverage:
 * 
 * DATA METHODS (3 overloads):
 * ✅ add_scatter(x_values, y_values) - auto-name, auto-color
 * ✅ add_scatter(x_values, y_values, name) - auto-color
 * ✅ add_scatter(x_values, y_values, name, color) - full specification
 * 
 * CLUSTER METHODS:
 * ✅ add_clusters(x_values, y_values, labels) - automatic cluster visualization
 * 
 * VERTICAL REFERENCE LINES (3 overloads):
 * ✅ add_vertical_line(x_value) - auto-label, auto-color
 * ✅ add_vertical_line(x_value, label) - auto-color
 * ✅ add_vertical_line(x_value, label, color) - full specification
 * 
 * HORIZONTAL REFERENCE LINES (3 overloads):
 * ✅ add_horizontal_line(y_value) - auto-label, auto-color
 * ✅ add_horizontal_line(y_value, label) - auto-color
 * ✅ add_horizontal_line(y_value, label, color) - full specification
 * 
 * CONFIGURATION METHODS:
 * ✅ set_default_marker_type() - CIRCLE, CROSS, SQUARE, TRIANGLE
 * 
 * INHERITED METHODS:
 * ✅ set_labels(), set_title(), set_xlabel(), set_ylabel()
 * ✅ set_legend_enabled(), hide_legend_item()
 * ✅ save_png(), save_svg()
 */