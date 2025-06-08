/**
 * @file 02_colors_and_multiple_series.cpp
 * @brief Learn how to use colors and plot multiple data series
 * 
 * This example shows how to:
 * - Use different colors for your data
 * - Plot multiple data series on the same plot
 * - Understand automatic vs manual coloring
 */

#include "plotlib/scatter_plot.h"
#include <vector>
#include <iostream>

int main() {
    std::cout << "Learning about colors and multiple series..." << std::endl;
    
    // Create different datasets
    std::vector<plotlib::Point2D> dataset_a = {
        {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}
    };
    
    std::vector<plotlib::Point2D> dataset_b = {
        {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}
    };
    
    std::vector<plotlib::Point2D> dataset_c = {
        {1, 3}, {2, 5}, {3, 2}, {4, 6}, {5, 4}
    };
    
    // Create a scatter plot
    plotlib::ScatterPlot plot(800, 600);
    plot.set_labels("Multiple Series with Colors", "X Values", "Y Values");
    
    // Method 1: Let the library choose colors automatically
    std::cout << "Adding data with automatic colors..." << std::endl;
    plot.add_data("Dataset A", dataset_a);  // Will be blue (first automatic color)
    plot.add_data("Dataset B", dataset_b);  // Will be red (second automatic color)
    
    // Method 2: Choose your own colors using color names
    std::cout << "Adding data with custom color..." << std::endl;
    plot.add_data("Dataset C", dataset_c, "green");  // Explicitly green
    
    // Save the plot
    bool success = plot.save_png("output/02_colors_and_multiple_series.png");
    
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
        std::vector<plotlib::Point2D> color_data = {
            {static_cast<double>(i), 1}, 
            {static_cast<double>(i), 2}, 
            {static_cast<double>(i), 3}
        };
        color_demo.add_data(colors[i], color_data, colors[i]);
    }
    
    bool color_success = color_demo.save_png("output/02_color_showcase.png");
    
    if (color_success) {
        std::cout << "✅ Color showcase saved! See all available colors." << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to plot multiple data series on one plot
 * - How automatic coloring works (blue, red, green, orange, ...)
 * - How to specify custom colors using color names
 * - Available color names: "red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow"
 * - How legends automatically show all your series
 * 
 * 🚀 Try this:
 * - Change the colors of the datasets
 * - Add more datasets
 * - Try colors like "purple" or "cyan"
 * - Run example 03 to learn about line plots!
 */ 