#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include "plotlib/scatter_plot.h"
#include "plotlib/line_plot.h"

int main() {
    std::cout << "=== Testing Mixed Plot Types in Subplots ===" << std::endl;
    
    // Generate test data
    std::vector<plotlib::Point2D> scatter_data1, scatter_data2;
    std::vector<plotlib::Point2D> line_data1, line_data2, line_data3;
    
    std::random_device rd;
    std::mt19937 gen(42);
    std::normal_distribution<> dis(0.0, 1.0);
    
    // Generate scatter plot data
    for (int i = 0; i < 50; ++i) {
        scatter_data1.emplace_back(dis(gen), dis(gen));
        scatter_data2.emplace_back(dis(gen) + 2, dis(gen) + 2);
    }
    
    // Generate line plot data (mathematical functions)
    for (int i = 0; i <= 100; ++i) {
        double x = i * 0.1;
        line_data1.emplace_back(x, std::sin(x));
        line_data2.emplace_back(x, std::cos(x));
        line_data3.emplace_back(x, std::sin(x) * std::cos(x));
    }
    
    // Generate cluster data for scatter plots
    std::vector<plotlib::Point2D> cluster_points;
    std::vector<int> cluster_labels;
    
    // Cluster 0
    for (int i = 0; i < 25; ++i) {
        cluster_points.emplace_back(dis(gen) + 1, dis(gen) + 1);
        cluster_labels.push_back(0);
    }
    
    // Cluster 1
    for (int i = 0; i < 25; ++i) {
        cluster_points.emplace_back(dis(gen) - 1, dis(gen) - 1);
        cluster_labels.push_back(1);
    }
    
    // Outliers
    for (int i = 0; i < 5; ++i) {
        cluster_points.emplace_back(dis(gen) * 3, dis(gen) * 3);
        cluster_labels.push_back(-1);
    }
    
    // Test 1: 2x2 Mixed Layout
    std::cout << "\n1. Testing 2x2 mixed layout (2 scatter + 2 line plots)..." << std::endl;
    {
        plotlib::SubplotManager manager(2, 2, 1200, 900);
        manager.set_main_title("2x2 Mixed Plot Types");
        
        // Top-left: Scatter plot with multiple series
        auto& scatter1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        scatter1.set_labels("Scatter Plot 1", "X Values", "Y Values");
        scatter1.add_series("Series A", scatter_data1, {3.0, 1.0, 0.0, 0.0, 0.8}); // Red
        scatter1.add_series("Series B", scatter_data2, {3.0, 0.0, 1.0, 0.0, 0.8}); // Green
        
        // Top-right: Line plot with trigonometric functions
        auto& line1 = manager.get_subplot<plotlib::LinePlot>(0, 1);
        line1.set_labels("Trigonometric Functions", "X", "Y");
        line1.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9}); // Red line
        line1.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9}); // Blue line
        
        // Bottom-left: Scatter plot with clusters
        auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 0);
        scatter2.set_labels("Cluster Analysis", "Feature 1", "Feature 2");
        scatter2.add_cluster_data("Clusters", cluster_points, cluster_labels);
        
        // Bottom-right: Line plot with combined function
        auto& line2 = manager.get_subplot<plotlib::LinePlot>(1, 1);
        line2.set_labels("Combined Function", "X", "sin(x)*cos(x)");
        line2.add_series("sin(x)*cos(x)", line_data3, {2.0, 0.6, 0.2, 0.8, 0.9}); // Purple line
        
        bool success = manager.save_png("output/mixed_2x2.png");
        std::cout << "2x2 mixed layout: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 2: 3x2 Mixed Layout
    std::cout << "\n2. Testing 3x2 mixed layout (alternating plot types)..." << std::endl;
    {
        plotlib::SubplotManager manager(3, 2, 1400, 1200);
        manager.set_main_title("3x2 Mixed Plot Types Dashboard");
        
        // Row 1: Scatter, Line
        auto& scatter1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        scatter1.set_labels("Scatter 1", "X", "Y");
        scatter1.add_series("Data A", scatter_data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        
        auto& line1 = manager.get_subplot<plotlib::LinePlot>(0, 1);
        line1.set_labels("Line 1", "X", "sin(x)");
        line1.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        
        // Row 2: Line, Scatter
        auto& line2 = manager.get_subplot<plotlib::LinePlot>(1, 0);
        line2.set_labels("Line 2", "X", "cos(x)");
        line2.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        
        auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 1);
        scatter2.set_labels("Scatter 2", "X", "Y");
        scatter2.add_series("Data B", scatter_data2, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        // Row 3: Scatter with clusters, Line with multiple series
        auto& scatter3 = manager.get_subplot<plotlib::ScatterPlot>(2, 0);
        scatter3.set_labels("Cluster Data", "Feature 1", "Feature 2");
        scatter3.add_cluster_data("Clusters", cluster_points, cluster_labels);
        
        auto& line3 = manager.get_subplot<plotlib::LinePlot>(2, 1);
        line3.set_labels("Multi-Line", "X", "Y");
        line3.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        line3.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        line3.add_series("sin*cos", line_data3, {2.0, 0.6, 0.2, 0.8, 0.9});
        
        bool success = manager.save_png("output/mixed_3x2.png");
        std::cout << "3x2 mixed layout: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 3: 1x4 Mixed Layout (horizontal strip)
    std::cout << "\n3. Testing 1x4 mixed layout (horizontal strip)..." << std::endl;
    {
        plotlib::SubplotManager manager(1, 4, 1600, 400);
        manager.set_main_title("1x4 Mixed Plot Types Strip");
        
        auto& scatter1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        scatter1.set_labels("Scatter", "X", "Y");
        scatter1.add_series("Data", scatter_data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        
        auto& line1 = manager.get_subplot<plotlib::LinePlot>(0, 1);
        line1.set_labels("Line", "X", "sin(x)");
        line1.add_series("sin(x)", line_data1, {2.0, 0.0, 1.0, 0.0, 0.9});
        
        auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(0, 2);
        scatter2.set_labels("Clusters", "X", "Y");
        scatter2.add_cluster_data("Data", cluster_points, cluster_labels);
        
        auto& line2 = manager.get_subplot<plotlib::LinePlot>(0, 3);
        line2.set_labels("Multi-Line", "X", "Y");
        line2.add_series("sin(x)", line_data1, {1.5, 1.0, 0.0, 0.0, 0.7});
        line2.add_series("cos(x)", line_data2, {1.5, 0.0, 0.0, 1.0, 0.7});
        
        bool success = manager.save_png("output/mixed_1x4.png");
        std::cout << "1x4 mixed layout: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 4: 4x1 Mixed Layout (vertical strip)
    std::cout << "\n4. Testing 4x1 mixed layout (vertical strip)..." << std::endl;
    {
        plotlib::SubplotManager manager(4, 1, 600, 1400);
        manager.set_main_title("4x1 Mixed Plot Types Stack");
        
        auto& line1 = manager.get_subplot<plotlib::LinePlot>(0, 0);
        line1.set_labels("Sine Wave", "X", "sin(x)");
        line1.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        
        auto& scatter1 = manager.get_subplot<plotlib::ScatterPlot>(1, 0);
        scatter1.set_labels("Random Data", "X", "Y");
        scatter1.add_series("Points", scatter_data1, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        auto& line2 = manager.get_subplot<plotlib::LinePlot>(2, 0);
        line2.set_labels("Cosine Wave", "X", "cos(x)");
        line2.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        
        auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(3, 0);
        scatter2.set_labels("Cluster Analysis", "X", "Y");
        scatter2.add_cluster_data("Clusters", cluster_points, cluster_labels);
        
        bool success = manager.save_png("output/mixed_4x1.png");
        std::cout << "4x1 mixed layout: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 5: Legend customization in mixed plots
    std::cout << "\n5. Testing legend customization in mixed plots..." << std::endl;
    {
        plotlib::SubplotManager manager(2, 2, 1200, 900);
        manager.set_main_title("Mixed Plots with Custom Legends");
        
        // Scatter with full legend
        auto& scatter1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        scatter1.set_labels("Full Legend", "X", "Y");
        scatter1.add_series("Series A", scatter_data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        scatter1.add_series("Series B", scatter_data2, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        // Line with selective legend
        auto& line1 = manager.get_subplot<plotlib::LinePlot>(0, 1);
        line1.set_labels("Selective Legend", "X", "Y");
        line1.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        line1.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        line1.add_series("sin*cos", line_data3, {2.0, 0.6, 0.2, 0.8, 0.9});
        line1.hide_legend_item("cos(x)"); // Hide cos(x) from legend
        
        // Scatter with no legend
        auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 0);
        scatter2.set_labels("No Legend", "X", "Y");
        scatter2.add_cluster_data("Clusters", cluster_points, cluster_labels);
        scatter2.set_legend_enabled(false);
        
        // Line with cluster-style legend hiding
        auto& line2 = manager.get_subplot<plotlib::LinePlot>(1, 1);
        line2.set_labels("Custom Legend", "X", "Y");
        line2.add_series("Function A", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        line2.add_series("Function B", line_data2, {2.0, 0.0, 1.0, 0.0, 0.9});
        line2.add_series("Function C", line_data3, {2.0, 0.0, 0.0, 1.0, 0.9});
        line2.hide_legend_item("Function B");
        
        bool success = manager.save_png("output/mixed_custom_legends.png");
        std::cout << "Mixed plots with custom legends: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    std::cout << "\n=== Mixed Subplot Test Complete ===" << std::endl;
    std::cout << "Generated test plots:" << std::endl;
    std::cout << "- mixed_2x2.png: 2x2 grid with scatter and line plots" << std::endl;
    std::cout << "- mixed_3x2.png: 3x2 dashboard with alternating plot types" << std::endl;
    std::cout << "- mixed_1x4.png: Horizontal strip with mixed plot types" << std::endl;
    std::cout << "- mixed_4x1.png: Vertical stack with mixed plot types" << std::endl;
    std::cout << "- mixed_custom_legends.png: Mixed plots with various legend configurations" << std::endl;
    
    return 0;
} 