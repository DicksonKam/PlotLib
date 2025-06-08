#include <iostream>
#include <vector>
#include <random>
#include "plotlib/scatter_plot.h"

int main() {
    std::cout << "=== Testing Current Implementation ===" << std::endl;
    
    // Generate test data
    std::vector<plotlib::Point2D> test_data;
    std::random_device rd;
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::normal_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < 50; ++i) {
        test_data.emplace_back(dis(gen), dis(gen));
    }
    
    // Test 1: Single plot functionality
    std::cout << "\n1. Testing single plot functionality..." << std::endl;
    {
        plotlib::ScatterPlot plot(800, 600);
        plot.set_labels("Test Single Plot", "X Values", "Y Values");
        plotlib::PlotStyle style = {3.0, 1.0, 0.0, 0.0, 0.8}; // Red points
        plot.add_series("Test Data", test_data, style);
        bool success = plot.save_png("output/test_single_plot.png");
        std::cout << "Single plot: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 2: Subplot functionality
    std::cout << "\n2. Testing subplot functionality..." << std::endl;
    {
        plotlib::SubplotManager manager(2, 2, 1200, 900);
        manager.set_main_title("Test Subplots");
        
        auto& plot1 = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        plot1.set_labels("Plot 1", "X", "Y");
        plot1.add_series("Data 1", test_data, {3.0, 1.0, 0.0, 0.0, 0.8});
        
        auto& plot2 = manager.get_subplot<plotlib::ScatterPlot>(0, 1);
        plot2.set_labels("Plot 2", "X", "Y");
        plot2.add_series("Data 2", test_data, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        auto& plot3 = manager.get_subplot<plotlib::ScatterPlot>(1, 0);
        plot3.set_labels("Plot 3", "X", "Y");
        plot3.add_series("Data 3", test_data, {3.0, 0.0, 0.0, 1.0, 0.8});
        
        auto& plot4 = manager.get_subplot<plotlib::ScatterPlot>(1, 1);
        plot4.set_labels("Plot 4", "X", "Y");
        plot4.add_series("Data 4", test_data, {3.0, 1.0, 1.0, 0.0, 0.8});
        
        bool success = manager.save_png("output/test_subplots.png");
        std::cout << "Subplots: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 3: Cluster functionality
    std::cout << "\n3. Testing cluster functionality..." << std::endl;
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
        
        // Outliers
        for (int i = 0; i < 5; ++i) {
            cluster_points.emplace_back(dis(gen) * 3, dis(gen) * 3);
            cluster_labels.push_back(-1);
        }
        
        plotlib::ScatterPlot plot(800, 600);
        plot.set_labels("Test Clusters", "X Values", "Y Values");
        plot.add_cluster_data("Clusters", cluster_points, cluster_labels);
        bool success = plot.save_png("output/test_clusters.png");
        std::cout << "Clusters: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    std::cout << "\n=== Test Complete ===" << std::endl;
    std::cout << "Check the output/ directory for generated plots." << std::endl;
    
    return 0;
} 