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
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to plot multiple data series on one plot using separate X/Y vectors
 * - How automatic coloring works (blue, red, green, orange, ...)
 * - How to specify custom colors using color names with add_scatter()
 * - Available color names: "red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow"
 * - How legends automatically show all your series
 * 
 * 🚀 Try this:
 * - Change the colors of the datasets
 * - Add more datasets
 * - Try colors like "purple" or "cyan"
 * - Run example 03 to learn about line plots!
 */ 