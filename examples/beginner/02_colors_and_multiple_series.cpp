/**
 * @file 02_colors_and_multiple_series.cpp
 * @brief Learn how to use colors and plot multiple data series
 * 
 * This example shows how to:
 * - Use different colors for your data
 * - Plot multiple data series on the same plot
 * - Understand automatic vs manual coloring
 */

#include "scatter_plot.h"
#include <vector>
#include <iostream>

int main() {
    std::cout << "Learning about colors and multiple series..." << std::endl;
    
    // Create different datasets using separate X and Y vectors
    std::vector<double> x_a = {1, 2, 3, 4, 5};
    std::vector<double> y_a = {2, 3, 4, 5, 6};
    
    std::vector<double> x_b = {1, 2, 3, 4, 5};
    std::vector<double> y_b = {1, 2, 3, 4, 5};
    
    std::vector<double> x_c = {1, 2, 3, 4, 5};
    std::vector<double> y_c = {3, 5, 2, 6, 4};
    
    // Create a scatter plot
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels("Multiple Series with Colors", "X Values", "Y Values");
    
    // Method 1: Let the library choose colors automatically
    std::cout << "Adding data with automatic colors..." << std::endl;
    plot.add_scatter(x_a, y_a, "Dataset A");  // Will be blue (first automatic color)
    plot.add_scatter(x_b, y_b, "Dataset B");  // Will be red (second automatic color)
    
    // Method 2: Choose your own colors using color names
    std::cout << "Adding data with custom color..." << std::endl;
    plot.add_scatter(x_c, y_c, "Dataset C", "green");  // Explicitly green
    
    // Save the plot
    bool success = plot.save_png("output/beginner_02_colors_and_multiple_series.png");
    
    if (success) {
        std::cout << "✅ Success! Check out your colorful plot!" << std::endl;
        std::cout << "🎨 Notice how each series has a different color and appears in the legend" << std::endl;
    } else {
        std::cout << "❌ Something went wrong. Make sure the output/ folder exists." << std::endl;
    }
    
    // Let's create another plot showing all available colors
    std::cout << "\nCreating a color showcase..." << std::endl;
    
    plotlib::ScatterPlot color_demo(1000, 600);
    color_demo.set_labels("Available Colors Showcase", "X", "Y");
    
    // Show all available colors
    std::vector<std::string> colors = {"red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow"};
    
    for (size_t i = 0; i < colors.size(); ++i) {
        std::vector<double> x_color = {static_cast<double>(i), static_cast<double>(i), static_cast<double>(i)};
        std::vector<double> y_color = {1, 2, 3};
        color_demo.add_scatter(x_color, y_color, colors[i], colors[i]);
    }
    
    bool color_success = color_demo.save_png("output/beginner_02_color_showcase.png");
    
    if (color_success) {
        std::cout << "✅ Color showcase saved! See all available colors." << std::endl;
    }
    
    // Let's create three plots showing enhanced cluster visualization
    std::cout << "\nCreating enhanced cluster visualization demos..." << std::endl;
    
    // Demo 1: Basic automatic clustering
    plotlib::ScatterPlot cluster_plot1(800, 600);
    cluster_plot1.set_labels("Demo 1: Auto Cluster Names & Colors", "X Values", "Y Values");
    
    std::vector<double> cluster_x = {1.0, 1.2, 1.1, 0.9, 1.3,    // Cluster 0 (around point 1,1)
                                     4.0, 4.1, 3.9, 4.2, 3.8,    // Cluster 1 (around point 4,4)
                                     2.5, 6.0};                   // Outliers
    std::vector<double> cluster_y = {1.0, 1.1, 0.9, 1.2, 0.8,    // Cluster 0
                                     4.0, 4.1, 3.9, 3.8, 4.2,    // Cluster 1
                                     6.0, 1.5};                   // Outliers
    std::vector<int> cluster_labels = {0, 0, 0, 0, 0,             // First 5 points belong to cluster 0
                                       1, 1, 1, 1, 1,             // Next 5 points belong to cluster 1
                                       -1, -1};                   // Last 2 points are outliers (-1)
    
    // Overload 1: Basic automatic naming and coloring
    cluster_plot1.add_clusters(cluster_x, cluster_y, cluster_labels);
    
    bool cluster1_success = cluster_plot1.save_png("output/beginner_02_cluster_auto.png");
    
    // Demo 2: Custom names with automatic coloring
    plotlib::ScatterPlot cluster_plot2(800, 600);
    cluster_plot2.set_labels("Demo 2: Custom Names, Auto Colors", "X Values", "Y Values");
    
    std::vector<std::string> custom_names = {"Anomalies", "Group A", "Group B"};
    
    // Overload 2: Custom names, automatic coloring
    cluster_plot2.add_clusters(cluster_x, cluster_y, cluster_labels, custom_names);
    
    bool cluster2_success = cluster_plot2.save_png("output/beginner_02_cluster_custom_names.png");
    
    // Demo 3: Custom names and colors
    plotlib::ScatterPlot cluster_plot3(800, 600);
    cluster_plot3.set_labels("Demo 3: Custom Names & Colors", "X Values", "Y Values");
    
    std::vector<std::string> custom_colors = {"purple", "orange", "green"};
    
    // Overload 3: Custom names and colors
    cluster_plot3.add_clusters(cluster_x, cluster_y, cluster_labels, custom_names, custom_colors);
    
    bool cluster3_success = cluster_plot3.save_png("output/beginner_02_cluster_full_custom.png");
    
    if (cluster1_success && cluster2_success && cluster3_success) {
        std::cout << "✅ All cluster demos saved!" << std::endl;
        std::cout << "🔍 Demo 1: Auto names (Outliers, Cluster 1, Cluster 2) + auto colors" << std::endl;
        std::cout << "🎯 Demo 2: Custom names (Anomalies, Group A, Group B) + auto colors" << std::endl;
        std::cout << "🎨 Demo 3: Custom names + custom colors (purple, orange, green)" << std::endl;
        std::cout << "📌 Note: Outliers always use red cross markers!" << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to plot multiple data series on one plot using separate X/Y vectors
 * - How automatic coloring works (blue, red, green, orange, ...)
 * - How to specify custom colors using color names with add_scatter()
 * - Available color names: "red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow"
 * - How to visualize cluster data using add_clusters()
 * - How cluster labels work (0, 1, 2, ... for clusters, -1 for outliers)
 * - How legends automatically show all your series and clusters
 * 
 * 🚀 Try this:
 * - Change the colors of the datasets
 * - Add more datasets or clusters
 * - Try different cluster labels and see how colors change
 * - Try colors like "purple" or "cyan"
 * - Run example 03 to learn about line plots!
 */ 