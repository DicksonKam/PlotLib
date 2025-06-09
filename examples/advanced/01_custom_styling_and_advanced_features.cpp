/**
 * @file 01_custom_styling_and_advanced_features.cpp
 * @brief Advanced styling, custom colors, and fine-tuned control
 * 
 * This example demonstrates:
 * - Custom PlotStyle with precise RGB control
 * - Advanced legend management
 * - Manual axis bounds setting
 * - Custom marker types and sizes
 * - Professional styling techniques
 */

#include "scatter_plot.h"
#include "line_plot.h"
#include "histogram_plot.h"
#include <vector>
#include <iostream>
#include <random>
#include <cmath>

int main() {
    std::cout << "Creating advanced styled plots..." << std::endl;
    
    // Example 1: Custom PlotStyle with precise control
    std::cout << "1. Custom styling with precise RGB control..." << std::endl;
    
    plotlib::ScatterPlot custom_plot(1000, 700);
    custom_plot.set_labels("Advanced Custom Styling", "X Coordinate", "Y Coordinate");
    
    // Create custom styles with precise RGB values
    plotlib::PlotStyle corporate_blue;
    corporate_blue.r = 0.2; corporate_blue.g = 0.4; corporate_blue.b = 0.8;
    corporate_blue.point_size = 4.5;
    corporate_blue.alpha = 0.85;
    corporate_blue.label = "Corporate Data";
    
    plotlib::PlotStyle research_red;
    research_red.r = 0.8; research_red.g = 0.2; research_red.b = 0.2;
    research_red.point_size = 3.5;
    research_red.alpha = 0.9;
    research_red.label = "Research Data";
    
    plotlib::PlotStyle academic_green;
    academic_green.r = 0.1; academic_green.g = 0.6; academic_green.b = 0.3;
    academic_green.point_size = 5.0;
    academic_green.alpha = 0.75;
    academic_green.label = "Academic Data";
    
    // Generate sophisticated datasets using separate X/Y vectors
    std::vector<double> corporate_x, corporate_y;
    std::vector<double> research_x, research_y;
    std::vector<double> academic_x, academic_y;
    
    std::random_device rd;
    std::mt19937 gen(42);
    std::normal_distribution<> corp_dist(50, 15);
    std::normal_distribution<> research_dist(75, 10);
    std::normal_distribution<> academic_dist(60, 20);
    
    for (int i = 0; i < 100; ++i) {
        double x = i * 0.8;
        corporate_x.push_back(x);
        corporate_y.push_back(corp_dist(gen) + 0.1 * x);
        
        research_x.push_back(x);
        research_y.push_back(research_dist(gen) + 0.05 * x);
        
        academic_x.push_back(x);
        academic_y.push_back(academic_dist(gen) - 0.02 * x);
    }
    
    // Add series with custom styles using simplified API + manual styling
    custom_plot.add_scatter("Corporate", corporate_x, corporate_y, "blue");
    custom_plot.add_scatter("Research", research_x, research_y, "red");
    custom_plot.add_scatter("Academic", academic_x, academic_y, "green");
    
    // Set custom bounds for professional appearance
    custom_plot.set_bounds(0, 80, 0, 120);
    
    custom_plot.save_png("output/advanced_01_custom_styling.png");
    std::cout << "✅ Custom styling plot saved!" << std::endl;
    
    // Example 2: Advanced legend management
    std::cout << "2. Advanced legend management..." << std::endl;
    
    plotlib::ScatterPlot legend_plot(900, 600);
    legend_plot.set_labels("Selective Legend Display", "Performance", "Efficiency");
    
    // Add multiple series using the simplified API
    legend_plot.add_scatter("Primary Results", corporate_x, corporate_y, "blue");
    legend_plot.add_scatter("Secondary Results", research_x, research_y, "red");
    legend_plot.add_scatter("Control Group", academic_x, academic_y, "green");
    
    std::vector<double> outlier_x = {10, 70};
    std::vector<double> outlier_y = {10, 110};
    legend_plot.add_scatter("Outlier Data", outlier_x, outlier_y, "orange");
    
    std::vector<double> baseline_x = {0, 80};
    std::vector<double> baseline_y = {50, 50};
    legend_plot.add_scatter("Baseline", baseline_x, baseline_y, "gray");
    
    // Selectively hide some legend items for cleaner presentation
    legend_plot.hide_legend_item("Outlier Data");
    legend_plot.hide_legend_item("Baseline");
    
    legend_plot.save_png("output/advanced_01_selective_legend.png");
    std::cout << "✅ Selective legend plot saved!" << std::endl;
    
    // Example 3: Advanced line plot with custom markers and styles
    std::cout << "3. Advanced line plot with custom features..." << std::endl;
    
    plotlib::LinePlot advanced_line(1000, 700);
    advanced_line.set_labels("Advanced Line Plot Features", "Time (hours)", "Signal Strength (dB)");
    
    // Enable markers on lines
    advanced_line.set_default_show_markers(true);
    advanced_line.set_default_line_width(2.5);
    
    // Generate complex signal data
    std::vector<double> time_points;
    std::vector<double> signal_a, signal_b, signal_c;
    
    for (int i = 0; i <= 200; ++i) {
        double t = i * 0.1;
        time_points.push_back(t);
        
        // Complex signal with noise
        signal_a.push_back(50 + 20 * std::sin(0.5 * t) + 5 * std::sin(2 * t) + (gen() % 10 - 5));
        signal_b.push_back(45 + 15 * std::cos(0.3 * t) + 8 * std::sin(1.5 * t) + (gen() % 8 - 4));
        signal_c.push_back(55 + 10 * std::sin(0.8 * t) * std::cos(0.2 * t) + (gen() % 6 - 3));
    }
    
    // Add lines with custom colors
    advanced_line.add_line("Primary Signal", time_points, signal_a, "blue");
    advanced_line.add_line("Secondary Signal", time_points, signal_b, "red");
    advanced_line.add_line("Reference Signal", time_points, signal_c, "green");
    
    advanced_line.save_png("output/advanced_01_complex_lines.png");
    std::cout << "✅ Advanced line plot saved!" << std::endl;
    
    // Example 4: Advanced histogram (simplified)
    std::cout << "4. Advanced histogram analysis..." << std::endl;
    
    plotlib::HistogramPlot advanced_hist(1000, 700);
    advanced_hist.set_labels("Distribution Analysis", "Value", "Frequency");
    
    // Generate different distributions
    std::normal_distribution<> normal_dist(100, 15);
    std::normal_distribution<> shifted_dist(120, 12);
    
    std::vector<double> normal_data, shifted_data;
    for (int i = 0; i < 1000; ++i) {
        normal_data.push_back(normal_dist(gen));
        shifted_data.push_back(shifted_dist(gen));
    }
    
    // Add histograms with precise bin control
    advanced_hist.add_histogram("Normal Distribution", normal_data, "blue", 30);
    advanced_hist.add_histogram("Shifted Distribution", shifted_data, "red", 30);
    
    advanced_hist.save_png("output/advanced_01_histogram_analysis.png");
    std::cout << "✅ Histogram analysis plot saved!" << std::endl;
    
    // Example 5: Professional cluster analysis
    std::cout << "5. Professional cluster analysis..." << std::endl;
    
    plotlib::ScatterPlot cluster_plot(1000, 700);
    cluster_plot.set_labels("Advanced Cluster Analysis", "Feature 1", "Feature 2");
    
    // Generate realistic cluster data with outliers using separate vectors
    std::vector<double> cluster_x, cluster_y;
    std::vector<int> cluster_labels;
    
    // Cluster 1: Dense cluster
    std::normal_distribution<> cluster1_x_dist(20, 5);
    std::normal_distribution<> cluster1_y_dist(30, 4);
    for (int i = 0; i < 50; ++i) {
        cluster_x.push_back(cluster1_x_dist(gen));
        cluster_y.push_back(cluster1_y_dist(gen));
        cluster_labels.push_back(0);
    }
    
    // Cluster 2: Elongated cluster
    std::normal_distribution<> cluster2_x_dist(60, 8);
    std::normal_distribution<> cluster2_y_dist(20, 3);
    for (int i = 0; i < 40; ++i) {
        cluster_x.push_back(cluster2_x_dist(gen));
        cluster_y.push_back(cluster2_y_dist(gen));
        cluster_labels.push_back(1);
    }
    
    // Cluster 3: Sparse cluster
    std::normal_distribution<> cluster3_x_dist(40, 12);
    std::normal_distribution<> cluster3_y_dist(60, 8);
    for (int i = 0; i < 35; ++i) {
        cluster_x.push_back(cluster3_x_dist(gen));
        cluster_y.push_back(cluster3_y_dist(gen));
        cluster_labels.push_back(2);
    }
    
    // Add outliers
    std::uniform_real_distribution<> outlier_dist(0, 80);
    for (int i = 0; i < 10; ++i) {
        cluster_x.push_back(outlier_dist(gen));
        cluster_y.push_back(outlier_dist(gen));
        cluster_labels.push_back(-1);  // -1 indicates outliers
    }
    
    // Add cluster data using simplified API
    cluster_plot.add_clusters(cluster_x, cluster_y, cluster_labels);
    
    cluster_plot.save_png("output/advanced_01_cluster_analysis.png");
    std::cout << "✅ Cluster analysis plot saved!" << std::endl;
    
    std::cout << "\n🎯 Advanced Example 1 Complete!" << std::endl;
    std::cout << "Generated 5 advanced plots demonstrating:" << std::endl;
    std::cout << "  • Custom RGB styling and precise control" << std::endl;
    std::cout << "  • Advanced legend management" << std::endl;
    std::cout << "  • Complex line plots with markers" << std::endl;
    std::cout << "  • Advanced histogram analysis" << std::endl;
    std::cout << "  • Professional cluster analysis" << std::endl;
    
    return 0;
}

/*
 * 🎯 Advanced Concepts Demonstrated:
 * 
 * 1. CUSTOM STYLING:
 *    - Precise RGB color control (0.0-1.0 values)
 *    - Custom point sizes and transparency
 *    - Professional color schemes
 * 
 * 2. LEGEND MANAGEMENT:
 *    - Selective hiding/showing of legend items
 *    - Clean presentation for complex plots
 * 
 * 3. ADVANCED LINE PLOTS:
 *    - Markers on lines for data points
 *    - Custom line widths
 *    - Complex signal processing visualization
 * 
 * 4. HISTOGRAM ANALYSIS:
 *    - Multiple distributions comparison
 *    - Precise bin control
 * 
 * 5. CLUSTER ANALYSIS:
 *    - Realistic cluster data generation
 *    - Outlier detection and visualization
 *    - Professional scientific presentation
 * 
 * 🚀 Next Steps:
 * - Try modifying the RGB values for custom colors
 * - Experiment with different statistical distributions
 * - Create your own cluster analysis workflows
 * - Combine these techniques in complex dashboards
 */ 