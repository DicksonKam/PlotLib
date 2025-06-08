#include <iostream>
#include <vector>
#include <random>

// Test both old and new implementations
#include "include/plotlib/scatter_plot.h"

// Include the old implementation directly
#include "include/plotlib/scatter_plot_old.h"

int main() {
    std::cout << "=== Scatter Plot Implementation Comparison ===" << std::endl;
    
    // Generate test data
    std::vector<Point2D> test_data;
    std::random_device rd;
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::normal_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < 50; ++i) {
        test_data.emplace_back(dis(gen), dis(gen));
    }
    
    // Test 1: Single plot functionality
    std::cout << "\n1. Testing single plot functionality..." << std::endl;
    
    // New implementation
    {
        plotlib::ScatterPlot new_plot(800, 600);
        new_plot.set_labels("New Implementation", "X Values", "Y Values");
        PlotStyle style = {3.0, 1.0, 0.0, 0.0, 0.8}; // Red points
        new_plot.add_series("Test Data", test_data, style);
        bool success = new_plot.save_png("output/new_single_plot.png");
        std::cout << "New implementation single plot: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Old implementation
    {
        ::ScatterPlot old_plot(800, 600);
        old_plot.set_labels("Old Implementation", "X Values", "Y Values");
        PlotStyle style = {3.0, 1.0, 0.0, 0.0, 0.8}; // Red points
        old_plot.add_series("Test Data", test_data, style);
        bool success = old_plot.save_png("output/old_single_plot.png");
        std::cout << "Old implementation single plot: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 2: Subplot functionality
    std::cout << "\n2. Testing subplot functionality..." << std::endl;
    
    // New implementation
    {
        plotlib::SubplotManager new_manager(2, 2, 1200, 900);
        new_manager.set_main_title("New Implementation Subplots");
        
        auto& plot1 = new_manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        plot1.set_labels("Plot 1", "X", "Y");
        plot1.add_series("Data 1", test_data, {3.0, 1.0, 0.0, 0.0, 0.8});
        
        auto& plot2 = new_manager.get_subplot<plotlib::ScatterPlot>(0, 1);
        plot2.set_labels("Plot 2", "X", "Y");
        plot2.add_series("Data 2", test_data, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        auto& plot3 = new_manager.get_subplot<plotlib::ScatterPlot>(1, 0);
        plot3.set_labels("Plot 3", "X", "Y");
        plot3.add_series("Data 3", test_data, {3.0, 0.0, 0.0, 1.0, 0.8});
        
        auto& plot4 = new_manager.get_subplot<plotlib::ScatterPlot>(1, 1);
        plot4.set_labels("Plot 4", "X", "Y");
        plot4.add_series("Data 4", test_data, {3.0, 1.0, 1.0, 0.0, 0.8});
        
        bool success = new_manager.save_png("output/new_subplots.png");
        std::cout << "New implementation subplots: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Old implementation
    {
        ::SubplotManager old_manager(2, 2, 1200, 900);
        old_manager.set_main_title("Old Implementation Subplots");
        
        auto& plot1 = old_manager.get_subplot(0, 0);
        plot1.set_labels("Plot 1", "X", "Y");
        plot1.add_series("Data 1", test_data, {3.0, 1.0, 0.0, 0.0, 0.8});
        
        auto& plot2 = old_manager.get_subplot(0, 1);
        plot2.set_labels("Plot 2", "X", "Y");
        plot2.add_series("Data 2", test_data, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        auto& plot3 = old_manager.get_subplot(1, 0);
        plot3.set_labels("Plot 3", "X", "Y");
        plot3.add_series("Data 3", test_data, {3.0, 0.0, 0.0, 1.0, 0.8});
        
        auto& plot4 = old_manager.get_subplot(1, 1);
        plot4.set_labels("Plot 4", "X", "Y");
        plot4.add_series("Data 4", test_data, {3.0, 1.0, 1.0, 0.0, 0.8});
        
        bool success = old_manager.save_png("output/old_subplots.png");
        std::cout << "Old implementation subplots: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 3: Cluster functionality
    std::cout << "\n3. Testing cluster functionality..." << std::endl;
    
    // Generate cluster data
    std::vector<Point2D> cluster_points;
    std::vector<int> cluster_labels;
    
    // Cluster 0
    for (int i = 0; i < 20; ++i) {
        cluster_points.emplace_back(dis(gen) + 2, dis(gen) + 2);
        cluster_labels.push_back(0);
    }
    
    // Cluster 1
    for (int i = 0; i < 20; ++i) {
        cluster_points.emplace_back(dis(gen) - 2, dis(gen) - 2);
        cluster_labels.push_back(1);
    }
    
    // Outliers
    for (int i = 0; i < 5; ++i) {
        cluster_points.emplace_back(dis(gen) * 3, dis(gen) * 3);
        cluster_labels.push_back(-1);
    }
    
    // New implementation
    {
        plotlib::ScatterPlot new_plot(800, 600);
        new_plot.set_labels("New Implementation Clusters", "X Values", "Y Values");
        new_plot.add_cluster_data("Clusters", cluster_points, cluster_labels);
        bool success = new_plot.save_png("output/new_clusters.png");
        std::cout << "New implementation clusters: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Old implementation
    {
        ::ScatterPlot old_plot(800, 600);
        old_plot.set_labels("Old Implementation Clusters", "X Values", "Y Values");
        old_plot.add_cluster_data("Clusters", cluster_points, cluster_labels);
        bool success = old_plot.save_png("output/old_clusters.png");
        std::cout << "Old implementation clusters: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    std::cout << "\n=== Comparison Complete ===" << std::endl;
    std::cout << "Check the output/ directory for generated plots to compare visually." << std::endl;
    
    return 0;
} 