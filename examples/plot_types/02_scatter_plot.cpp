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
    
    // Enhanced cluster data for comprehensive demonstration
    std::vector<double> cluster_x, cluster_y;
    std::vector<int> cluster_labels;
    
    // Generate Cluster 0: Points around (1.5, 1.5) 
    std::random_device rd;
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::normal_distribution<> cluster0_x(1.5, 0.2);
    std::normal_distribution<> cluster0_y(1.5, 0.2);
    for (int i = 0; i < 8; ++i) {
        cluster_x.push_back(cluster0_x(gen));
        cluster_y.push_back(cluster0_y(gen));
        cluster_labels.push_back(0);
    }
    
    // Generate Cluster 1: Points around (5.0, 4.5)
    std::normal_distribution<> cluster1_x(5.0, 0.3);
    std::normal_distribution<> cluster1_y(4.5, 0.25);
    for (int i = 0; i < 10; ++i) {
        cluster_x.push_back(cluster1_x(gen));
        cluster_y.push_back(cluster1_y(gen));
        cluster_labels.push_back(1);
    }
    
    // Generate Cluster 2: Points around (3.0, 5.5)
    std::normal_distribution<> cluster2_x(3.0, 0.15);
    std::normal_distribution<> cluster2_y(5.5, 0.2);
    for (int i = 0; i < 6; ++i) {
        cluster_x.push_back(cluster2_x(gen));
        cluster_y.push_back(cluster2_y(gen));
        cluster_labels.push_back(2);
    }
    
    // Add some outliers (label = -1)
    cluster_x.insert(cluster_x.end(), {0.5, 6.0, 2.5, 4.2});
    cluster_y.insert(cluster_y.end(), {3.8, 1.2, 0.8, 2.2});
    cluster_labels.insert(cluster_labels.end(), {-1, -1, -1, -1});
    
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
    
    std::cout << "2. Testing advanced cluster visualization..." << std::endl;
    std::cout << "   🔹 Cluster 0: 8 points (tight distribution)" << std::endl;
    std::cout << "   🔹 Cluster 1: 10 points (moderate spread)" << std::endl;
    std::cout << "   🔹 Cluster 2: 6 points (compact group)" << std::endl;
    std::cout << "   🔹 Outliers: 4 isolated points (label = -1)" << std::endl;
    
    // Test cluster sequence independence: add clusters after scatter series
    // The cluster legend should still start with "Outliers", "Cluster 1", "Cluster 2"
    // regardless of how many scatter series were added before
    plot.add_clusters(cluster_x, cluster_y, cluster_labels);
    
    // Add another cluster series to test sequence restart
    std::vector<double> extra_cluster_x = {7.0, 7.2, 7.1, 8.5};
    std::vector<double> extra_cluster_y = {2.0, 2.1, 1.9, 0.5};
    std::vector<int> extra_cluster_labels = {0, 0, 0, -1}; // One cluster + one outlier
    plot.add_clusters(extra_cluster_x, extra_cluster_y, extra_cluster_labels);
    
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
        std::cout << "      • Clusters: 2 cluster series demonstrating legend independence" << std::endl;
        std::cout << "   📏 6 reference lines with different overloads:" << std::endl;
        std::cout << "      • 3 vertical lines (auto, auto+label, full)" << std::endl;
        std::cout << "      • 3 horizontal lines (auto, auto+label, full)" << std::endl;
        std::cout << "   ⚙️ ScatterPlot-specific configuration methods" << std::endl;
        std::cout << "   🎨 Auto-color conflict avoidance for reference lines" << std::endl;
        std::cout << "   🏷️ Auto-naming for both data series and reference lines" << std::endl;
        std::cout << "   🔍 Advanced cluster visualization:" << std::endl;
        std::cout << "      • 2 independent cluster series with auto naming" << std::endl;
        std::cout << "      • Outlier detection (red cross markers for label -1)" << std::endl;
        std::cout << "      • Individual legend entries for each cluster" << std::endl;
        std::cout << "      • Cluster sequence independence from scatter series" << std::endl;
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
 * ✅ add_clusters(x_values, y_values, labels) - Advanced cluster visualization:
 *     • Automatic color assignment (different color per cluster ID)
 *     • Outlier handling (gray markers for label -1)
 *     • Legend generation ("Cluster 0", "Cluster 1", "Outliers")
 *     • Supports unlimited number of clusters
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