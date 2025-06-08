/**
 * @file 01_first_scatter_plot.cpp
 * @brief Your very first scatter plot - the simplest possible example
 * 
 * This example shows how to create a basic scatter plot with just a few lines of code.
 * Perfect for beginners who want to get started quickly!
 */

#include "plotlib/scatter_plot.h"
#include <vector>
#include <iostream>

int main() {
    std::cout << "Creating your first scatter plot..." << std::endl;
    
    // Step 1: Create some simple data points
    // Each point has an X and Y coordinate
    std::vector<plotlib::Point2D> my_data = {
        {1, 2},    // Point at (1, 2)
        {2, 4},    // Point at (2, 4)
        {3, 6},    // Point at (3, 6)
        {4, 8},    // Point at (4, 8)
        {5, 10}    // Point at (5, 10)
    };
    
    // Step 2: Create a scatter plot
    // The numbers (800, 600) are the width and height in pixels
    plotlib::ScatterPlot plot(800, 600);
    
    // Step 3: Give your plot a title and label the axes
    plot.set_labels("My First Scatter Plot", "X Values", "Y Values");
    
    // Step 4: Add your data to the plot
    // The library will automatically choose a nice blue color
    plot.add_data("My Data", my_data);
    
    // Step 5: Save the plot as a PNG image
    bool success = plot.save_png("output/01_first_scatter_plot.png");
    
    if (success) {
        std::cout << "✅ Success! Your plot was saved as '01_first_scatter_plot.png'" << std::endl;
        std::cout << "📁 Look in the output/ folder to see your plot!" << std::endl;
    } else {
        std::cout << "❌ Something went wrong. Make sure the output/ folder exists." << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to create data points using Point2D
 * - How to create a scatter plot with set dimensions
 * - How to add titles and axis labels
 * - How to add data with automatic coloring
 * - How to save your plot as an image
 * 
 * 🚀 Next steps:
 * - Try changing the data points
 * - Try different plot dimensions
 * - Run example 02 to learn about colors!
 */ 