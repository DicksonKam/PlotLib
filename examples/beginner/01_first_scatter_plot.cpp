/**
 * @file 01_first_scatter_plot.cpp
 * @brief Your very first scatter plot - the simplest possible example
 * 
 * This example shows how to create a basic scatter plot with just a few lines of code.
 * Perfect for beginners who want to get started quickly!
 */

#include "scatter_plot.h"
#include <vector>
#include <iostream>

int main() {
    std::cout << "Creating your first scatter plot..." << std::endl;
    
    // Step 1: Create some simple data
    // Separate X and Y coordinate vectors
    std::vector<double> x_values = {1, 2, 3, 4, 5};    // X coordinates
    std::vector<double> y_values = {2, 4, 6, 8, 10};   // Y coordinates
    
    // Step 2: Create a scatter plot
    // The numbers (800, 600) are the width and height in pixels
    plotlib::ScatterPlot plot(800, 600);
    
    // Step 3: Give your plot a title and label the axes
    plot.set_labels("My First Scatter Plot", "X Values", "Y Values");
    
    // Step 4: Add your data to the plot
    // The library will automatically choose a nice blue color
    plot.add_scatter(x_values, y_values, "My Data");
    
    // Step 5: Save the plot as a PNG image
    bool success = plot.save_png("output/beginner_01_first_scatter_plot.png");
    
    if (success) {
        std::cout << "✅ Success! Your plot was saved as 'beginner_01_first_scatter_plot.png'" << std::endl;
        std::cout << "📁 Look in the output/ folder to see your plot!" << std::endl;
    } else {
        std::cout << "❌ Something went wrong. Make sure the output/ folder exists." << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to create data using separate X and Y vectors
 * - How to create a scatter plot with set dimensions
 * - How to add titles and axis labels
 * - How to add data with automatic coloring using add_scatter()
 * - How to save your plot as an image
 * 
 * 🚀 Next steps:
 * - Try changing the data values
 * - Try different plot dimensions
 * - Run example 02 to learn about colors!
 */ 