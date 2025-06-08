#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include "plotlib/scatter_plot.h"
#include "plotlib/line_plot.h"
#include "plotlib/histogram_plot.h"

int main() {
    std::cout << "=== Testing All Plot Types Together ===" << std::endl;
    
    // Generate test data
    std::random_device rd;
    std::mt19937 gen(42);
    std::normal_distribution<> normal_dist(0.0, 1.0);
    std::normal_distribution<> normal_dist2(3.0, 1.5);
    std::uniform_real_distribution<> uniform_dist(-2.0, 2.0);
    
    // Scatter plot data
    std::vector<plotlib::Point2D> scatter_data1, scatter_data2;
    for (int i = 0; i < 100; ++i) {
        scatter_data1.emplace_back(normal_dist(gen), normal_dist(gen));
        scatter_data2.emplace_back(normal_dist2(gen), normal_dist2(gen));
    }
    
    // Line plot data (mathematical functions)
    std::vector<plotlib::Point2D> line_data1, line_data2, line_data3;
    for (int i = 0; i <= 100; ++i) {
        double x = i * 0.1;
        line_data1.emplace_back(x, std::sin(x));
        line_data2.emplace_back(x, std::cos(x));
        line_data3.emplace_back(x, std::exp(-x/5) * std::sin(x));
    }
    
    // Histogram data (different distributions)
    std::vector<double> hist_data1, hist_data2, hist_data3;
    for (int i = 0; i < 1000; ++i) {
        hist_data1.push_back(normal_dist(gen));
        hist_data2.push_back(normal_dist2(gen));
        hist_data3.push_back(uniform_dist(gen));
    }
    
    // Cluster data
    std::vector<plotlib::Point2D> cluster_points;
    std::vector<int> cluster_labels;
    
    // Generate 3 clusters
    for (int cluster = 0; cluster < 3; ++cluster) {
        std::normal_distribution<> cluster_x(cluster * 3.0, 0.8);
        std::normal_distribution<> cluster_y(cluster * 2.0, 0.8);
        
        for (int i = 0; i < 30; ++i) {
            cluster_points.emplace_back(cluster_x(gen), cluster_y(gen));
            cluster_labels.push_back(cluster);
        }
    }
    
    // Add some outliers
    for (int i = 0; i < 8; ++i) {
        cluster_points.emplace_back(uniform_dist(gen) * 5, uniform_dist(gen) * 5);
        cluster_labels.push_back(-1);
    }
    
    // Test 1: 3x1 Layout - One of each plot type
    std::cout << "\n1. Testing 3x1 layout (Histogram, Line, Scatter)..." << std::endl;
    {
        plotlib::SubplotManager manager(3, 1, 800, 1200);
        manager.set_main_title("All Plot Types: 3x1 Layout");
        
        // Top: Histogram
        auto& hist = manager.get_subplot<plotlib::HistogramPlot>(0, 0);
        hist.set_labels("Distribution Analysis", "Value", "Frequency");
        hist.add_data("Normal", hist_data1, {0.7, 0.2, 0.6, 0.8, 0.7}); // Purple
        hist.add_data("Shifted Normal", hist_data2, {0.7, 0.8, 0.2, 0.2, 0.7}); // Orange
        
        // Middle: Line plot
        auto& line = manager.get_subplot<plotlib::LinePlot>(1, 0);
        line.set_labels("Mathematical Functions", "X", "Y");
        line.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9}); // Red
        line.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9}); // Blue
        line.add_series("exp(-x/5)*sin(x)", line_data3, {2.0, 0.0, 0.7, 0.0, 0.9}); // Green
        
        // Bottom: Scatter plot
        auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(2, 0);
        scatter.set_labels("Cluster Analysis", "Feature 1", "Feature 2");
        scatter.add_cluster_data("Clusters", cluster_points, cluster_labels);
        
        bool success = manager.save_png("output/all_types_3x1.png");
        std::cout << "3x1 layout: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 2: 1x3 Layout - Horizontal arrangement
    std::cout << "\n2. Testing 1x3 layout (Scatter, Histogram, Line)..." << std::endl;
    {
        plotlib::SubplotManager manager(1, 3, 1500, 500);
        manager.set_main_title("All Plot Types: 1x3 Layout");
        
        // Left: Scatter plot
        auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        scatter.set_labels("Random Data", "X", "Y");
        scatter.add_series("Dataset A", scatter_data1, {3.0, 1.0, 0.0, 0.0, 0.8}); // Red
        scatter.add_series("Dataset B", scatter_data2, {3.0, 0.0, 1.0, 0.0, 0.8}); // Green
        
        // Middle: Histogram
        auto& hist = manager.get_subplot<plotlib::HistogramPlot>(0, 1);
        hist.set_labels("Data Distributions", "Value", "Frequency");
        hist.add_data("Normal", hist_data1, {0.7, 0.0, 0.0, 1.0, 0.7}); // Blue
        hist.add_data("Uniform", hist_data3, {0.7, 1.0, 0.5, 0.0, 0.7}); // Orange
        
        // Right: Line plot
        auto& line = manager.get_subplot<plotlib::LinePlot>(0, 2);
        line.set_labels("Trigonometry", "X", "Y");
        line.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        line.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        
        bool success = manager.save_png("output/all_types_1x3.png");
        std::cout << "1x3 layout: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 3: 2x3 Mixed Dashboard
    std::cout << "\n3. Testing 2x3 mixed dashboard..." << std::endl;
    {
        plotlib::SubplotManager manager(2, 3, 1800, 1200);
        manager.set_main_title("Comprehensive Data Analysis Dashboard");
        
        // Row 1: Histogram, Line, Scatter
        auto& hist1 = manager.get_subplot<plotlib::HistogramPlot>(0, 0);
        hist1.set_labels("Normal Distribution", "Value", "Frequency");
        hist1.add_data("Data", hist_data1, {0.7, 0.2, 0.8, 0.2, 0.8});
        
        auto& line1 = manager.get_subplot<plotlib::LinePlot>(0, 1);
        line1.set_labels("Sine Wave", "X", "sin(x)");
        line1.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        
        auto& scatter1 = manager.get_subplot<plotlib::ScatterPlot>(0, 2);
        scatter1.set_labels("Dataset A", "X", "Y");
        scatter1.add_series("Points", scatter_data1, {3.0, 0.0, 0.7, 0.0, 0.8});
        
        // Row 2: Scatter, Histogram, Line
        auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 0);
        scatter2.set_labels("Cluster Data", "Feature 1", "Feature 2");
        scatter2.add_cluster_data("Clusters", cluster_points, cluster_labels);
        
        auto& hist2 = manager.get_subplot<plotlib::HistogramPlot>(1, 1);
        hist2.set_labels("Multiple Distributions", "Value", "Frequency");
        hist2.add_data("Normal", hist_data1, {0.7, 1.0, 0.0, 0.0, 0.6});
        hist2.add_data("Shifted", hist_data2, {0.7, 0.0, 1.0, 0.0, 0.6});
        hist2.add_data("Uniform", hist_data3, {0.7, 0.0, 0.0, 1.0, 0.6});
        
        auto& line2 = manager.get_subplot<plotlib::LinePlot>(1, 2);
        line2.set_labels("Damped Oscillation", "X", "Y");
        line2.add_series("exp(-x/5)*sin(x)", line_data3, {2.0, 0.8, 0.2, 0.8, 0.9});
        
        bool success = manager.save_png("output/all_types_2x3_dashboard.png");
        std::cout << "2x3 dashboard: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 4: Advanced histogram features
    std::cout << "\n4. Testing advanced histogram features..." << std::endl;
    {
        plotlib::SubplotManager manager(2, 2, 1200, 900);
        manager.set_main_title("Advanced Histogram Features");
        
        // Top-left: Regular histogram
        auto& hist1 = manager.get_subplot<plotlib::HistogramPlot>(0, 0);
        hist1.set_labels("Regular Histogram", "Value", "Frequency");
        hist1.add_data("Normal", hist_data1, {0.7, 0.2, 0.6, 0.8, 0.8});
        
        // Top-right: Normalized histogram
        auto& hist2 = manager.get_subplot<plotlib::HistogramPlot>(0, 1);
        hist2.set_labels("Normalized Histogram", "Value", "Probability Density");
        hist2.add_data("Normal", hist_data1, {0.7, 0.8, 0.2, 0.2, 0.8});
        hist2.set_normalize(true);
        
        // Bottom-left: Cumulative histogram
        auto& hist3 = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
        hist3.set_labels("Cumulative Histogram", "Value", "Cumulative Frequency");
        hist3.add_data("Normal", hist_data1, {0.7, 0.2, 0.8, 0.2, 0.8});
        hist3.set_cumulative(true);
        
        // Bottom-right: Custom bins
        auto& hist4 = manager.get_subplot<plotlib::HistogramPlot>(1, 1);
        hist4.set_labels("Custom Bins", "Value", "Frequency");
        std::vector<double> custom_bins = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
        hist4.add_data_with_bins("Custom", hist_data2, custom_bins, {0.7, 0.0, 0.7, 0.7, 0.8});
        
        bool success = manager.save_png("output/histogram_features.png");
        std::cout << "Histogram features: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 5: Legend customization across all plot types
    std::cout << "\n5. Testing legend customization across all plot types..." << std::endl;
    {
        plotlib::SubplotManager manager(2, 3, 1800, 1200);
        manager.set_main_title("Legend Customization Across Plot Types");
        
        // Row 1: Full legends
        auto& hist1 = manager.get_subplot<plotlib::HistogramPlot>(0, 0);
        hist1.set_labels("Full Legend", "Value", "Frequency");
        hist1.add_data("Series A", hist_data1, {0.7, 1.0, 0.0, 0.0, 0.7});
        hist1.add_data("Series B", hist_data2, {0.7, 0.0, 1.0, 0.0, 0.7});
        
        auto& line1 = manager.get_subplot<plotlib::LinePlot>(0, 1);
        line1.set_labels("Full Legend", "X", "Y");
        line1.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        line1.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        
        auto& scatter1 = manager.get_subplot<plotlib::ScatterPlot>(0, 2);
        scatter1.set_labels("Full Legend", "X", "Y");
        scatter1.add_series("Data A", scatter_data1, {3.0, 1.0, 0.0, 0.0, 0.8});
        scatter1.add_series("Data B", scatter_data2, {3.0, 0.0, 1.0, 0.0, 0.8});
        
        // Row 2: Selective and disabled legends
        auto& hist2 = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
        hist2.set_labels("Selective Legend", "Value", "Frequency");
        hist2.add_data("Series A", hist_data1, {0.7, 1.0, 0.0, 0.0, 0.7});
        hist2.add_data("Series B", hist_data2, {0.7, 0.0, 1.0, 0.0, 0.7});
        hist2.add_data("Series C", hist_data3, {0.7, 0.0, 0.0, 1.0, 0.7});
        hist2.hide_legend_item("Series B");
        
        auto& line2 = manager.get_subplot<plotlib::LinePlot>(1, 1);
        line2.set_labels("No Legend", "X", "Y");
        line2.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        line2.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        line2.set_legend_enabled(false);
        
        auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 2);
        scatter2.set_labels("Cluster Legend", "X", "Y");
        scatter2.add_cluster_data("Clusters", cluster_points, cluster_labels);
        scatter2.hide_legend_item("Cluster 1");
        
        bool success = manager.save_png("output/all_types_legends.png");
        std::cout << "Legend customization: " << (success ? "✅ Success" : "❌ Failed") << std::endl;
    }
    
    // Test 6: Single plot demonstrations
    std::cout << "\n6. Testing individual plot types..." << std::endl;
    {
        // Histogram demo
        plotlib::HistogramPlot hist(800, 600);
        hist.set_labels("Histogram Demo", "Value", "Frequency");
        hist.add_data("Normal Distribution", hist_data1, {0.7, 0.2, 0.6, 0.8, 0.8});
        hist.add_data("Shifted Normal", hist_data2, {0.7, 0.8, 0.2, 0.2, 0.8});
        bool hist_success = hist.save_png("output/histogram_single.png");
        
        // Line plot demo
        plotlib::LinePlot line(800, 600);
        line.set_labels("Line Plot Demo", "X", "Y");
        line.add_series("sin(x)", line_data1, {2.0, 1.0, 0.0, 0.0, 0.9});
        line.add_series("cos(x)", line_data2, {2.0, 0.0, 0.0, 1.0, 0.9});
        line.add_series("exp(-x/5)*sin(x)", line_data3, {2.0, 0.0, 0.7, 0.0, 0.9});
        bool line_success = line.save_png("output/line_single.png");
        
        // Scatter plot demo
        plotlib::ScatterPlot scatter(800, 600);
        scatter.set_labels("Scatter Plot Demo", "X", "Y");
        scatter.add_cluster_data("Clusters", cluster_points, cluster_labels);
        bool scatter_success = scatter.save_png("output/scatter_single.png");
        
        std::cout << "Individual plots: " 
                  << (hist_success && line_success && scatter_success ? "✅ Success" : "❌ Failed") 
                  << std::endl;
    }
    
    std::cout << "\n=== All Plot Types Test Complete ===" << std::endl;
    std::cout << "Generated test plots:" << std::endl;
    std::cout << "- all_types_3x1.png: Vertical arrangement of all plot types" << std::endl;
    std::cout << "- all_types_1x3.png: Horizontal arrangement of all plot types" << std::endl;
    std::cout << "- all_types_2x3_dashboard.png: Comprehensive mixed dashboard" << std::endl;
    std::cout << "- histogram_features.png: Advanced histogram features" << std::endl;
    std::cout << "- all_types_legends.png: Legend customization across plot types" << std::endl;
    std::cout << "- histogram_single.png: Individual histogram plot" << std::endl;
    std::cout << "- line_single.png: Individual line plot" << std::endl;
    std::cout << "- scatter_single.png: Individual scatter plot" << std::endl;
    
    return 0;
} 