#include <iostream>
#include <vector>
#include <random>
#include "plotlib/scatter_plot.h"

int main() {
    std::cout << "=== Testing Legend Functionality ===" << std::endl;
    
    // Generate test data
    std::vector<plotlib::Point2D> data1, data2, data3;
    std::random_device rd;
    std::mt19937 gen(42);
    std::normal_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < 30; ++i) {
        data1.emplace_back(dis(gen), dis(gen));
        data2.emplace_back(dis(gen) + 2, dis(gen) + 2);
        data3.emplace_back(dis(gen) - 2, dis(gen) - 2);
    }
    
    // Test 1: Full legend with background box
    std::cout << "\n1. Testing full legend with background box..." << std::endl;
    {
        plotlib::ScatterPlot plot(800, 600);
        plot.set_labels("Full Legend Test", "X Values", "Y Values");
        
        plot.add_series("Series A", data1, {3.0, 1.0, 0.0, 0.0, 0.8}); // Red
        plot.add_series("Series B", data2, {3.0, 0.0, 1.0, 0.0, 0.8}); // Green
        plot.add_series("Series C", data3, {3.0, 0.0, 0.0, 1.0, 0.8}); // Blue
        
        bool success = plot.save_png("output/legend_full.png");
        std::cout << "Full legend: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 2: Selective legend (hide one series)
    std::cout << "\n2. Testing selective legend (hiding Series B)..." << std::endl;
    {
        plotlib::ScatterPlot plot(800, 600);
        plot.set_labels("Selective Legend Test", "X Values", "Y Values");
        
        plot.add_series("Series A", data1, {3.0, 1.0, 0.0, 0.0, 0.8}); // Red
        plot.add_series("Series B", data2, {3.0, 0.0, 1.0, 0.0, 0.8}); // Green
        plot.add_series("Series C", data3, {3.0, 0.0, 0.0, 1.0, 0.8}); // Blue
        
        // Hide Series B from legend
        plot.hide_legend_item("Series B");
        
        bool success = plot.save_png("output/legend_selective.png");
        std::cout << "Selective legend: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 3: Disabled legend
    std::cout << "\n3. Testing disabled legend..." << std::endl;
    {
        plotlib::ScatterPlot plot(800, 600);
        plot.set_labels("No Legend Test", "X Values", "Y Values");
        
        plot.add_series("Series A", data1, {3.0, 1.0, 0.0, 0.0, 0.8}); // Red
        plot.add_series("Series B", data2, {3.0, 0.0, 1.0, 0.0, 0.8}); // Green
        plot.add_series("Series C", data3, {3.0, 0.0, 0.0, 1.0, 0.8}); // Blue
        
        // Disable legend completely
        plot.set_legend_enabled(false);
        
        bool success = plot.save_png("output/legend_disabled.png");
        std::cout << "Disabled legend: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 4: Cluster legend with selective hiding
    std::cout << "\n4. Testing cluster legend with selective hiding..." << std::endl;
    {
        // Generate cluster data
        std::vector<plotlib::Point2D> cluster_points;
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
        
        // Cluster 2
        for (int i = 0; i < 15; ++i) {
            cluster_points.emplace_back(dis(gen), dis(gen) + 3);
            cluster_labels.push_back(2);
        }
        
        // Outliers
        for (int i = 0; i < 5; ++i) {
            cluster_points.emplace_back(dis(gen) * 3, dis(gen) * 3);
            cluster_labels.push_back(-1);
        }
        
        plotlib::ScatterPlot plot(800, 600);
        plot.set_labels("Cluster Legend Test", "X Values", "Y Values");
        plot.add_cluster_data("Clusters", cluster_points, cluster_labels);
        
        // Hide Cluster 1 from legend
        plot.hide_legend_item("Cluster 1");
        
        bool success = plot.save_png("output/legend_cluster_selective.png");
        std::cout << "Cluster selective legend: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 5: Subplot with selective legends
    std::cout << "\n5. Testing subplots with different legend configurations..." << std::endl;
    {
        plotlib::SubplotManager manager(2, 2, 1200, 900);
        manager.set_main_title("Legend Configuration Test");
        
        // Plot 1: Full legend
        auto& plot1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        plot1.set_labels("Full Legend", "X", "Y");
        plot1.add_series("A", data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        plot1.add_series("B", data2, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        // Plot 2: Selective legend
        auto& plot2 = manager.get_subplot<plotlib::ScatterPlot>(0, 1);
        plot2.set_labels("Selective Legend", "X", "Y");
        plot2.add_series("A", data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        plot2.add_series("B", data2, {3.0, 0.0, 1.0, 0.0, 0.8});
        plot2.hide_legend_item("B");
        
        // Plot 3: No legend
        auto& plot3 = manager.get_subplot<plotlib::ScatterPlot>(1, 0);
        plot3.set_labels("No Legend", "X", "Y");
        plot3.add_series("A", data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        plot3.add_series("B", data2, {3.0, 0.0, 1.0, 0.0, 0.8});
        plot3.set_legend_enabled(false);
        
        // Plot 4: Show all after hiding
        auto& plot4 = manager.get_subplot<plotlib::ScatterPlot>(1, 1);
        plot4.set_labels("Show All", "X", "Y");
        plot4.add_series("A", data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        plot4.add_series("B", data2, {3.0, 0.0, 1.0, 0.0, 0.8});
        plot4.add_series("C", data3, {3.0, 0.0, 0.0, 1.0, 0.8});
        plot4.hide_legend_item("B");
        plot4.hide_legend_item("C");
        plot4.show_all_legend_items(); // Show all again
        
        bool success = manager.save_png("output/legend_subplots.png");
        std::cout << "Subplot legends: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    std::cout << "\n=== Legend Test Complete ===" << std::endl;
    std::cout << "Check the output/ directory for generated plots:" << std::endl;
    std::cout << "- legend_full.png: Full legend with background box" << std::endl;
    std::cout << "- legend_selective.png: Selective legend (Series B hidden)" << std::endl;
    std::cout << "- legend_disabled.png: No legend" << std::endl;
    std::cout << "- legend_cluster_selective.png: Cluster legend with Cluster 1 hidden" << std::endl;
    std::cout << "- legend_subplots.png: Subplots with different legend configurations" << std::endl;
    
    return 0;
} 