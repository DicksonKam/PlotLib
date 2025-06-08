/**
 * @file 03_first_line_plot.cpp
 * @brief Your first line plot - perfect for showing trends and functions
 * 
 * This example shows how to create line plots, which are great for:
 * - Time series data (data that changes over time)
 * - Mathematical functions
 * - Showing trends and patterns
 */

#include "line_plot.h"
#include <vector>
#include <iostream>
#include <cmath>

int main() {
    std::cout << "Creating your first line plot..." << std::endl;
    
    // Method 1: Create line data using separate X and Y vectors
    std::vector<double> time = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> temperature = {20, 22, 25, 28, 30, 32, 30, 28, 25, 22, 20};
    
    plotlib::LinePlot plot(800, 600);
    plot.set_labels("Temperature Over Time", "Time (hours)", "Temperature (°C)");
    
    // Add the line using X and Y vectors - super easy!
    plot.add_line("Temperature", time, temperature, "red");
    
    bool success = plot.save_png("output/03_temperature_line.png");
    
    if (success) {
        std::cout << "✅ Temperature plot saved!" << std::endl;
    }
    
    // Method 2: Create mathematical functions
    std::cout << "Creating a mathematical function plot..." << std::endl;
    
    plotlib::LinePlot math_plot(800, 600);
    math_plot.set_labels("Mathematical Functions", "X", "Y");
    
    // Create data for sine and cosine functions
    std::vector<double> x_values;
    std::vector<double> sine_values;
    std::vector<double> cosine_values;
    
    // Generate points from 0 to 2π
    for (int i = 0; i <= 100; ++i) {
        double x = i * 2 * M_PI / 100;  // From 0 to 2π
        x_values.push_back(x);
        sine_values.push_back(std::sin(x));
        cosine_values.push_back(std::cos(x));
    }
    
    // Add both functions to the same plot
    math_plot.add_line("sin(x)", x_values, sine_values, "blue");
    math_plot.add_line("cos(x)", x_values, cosine_values, "green");
    
    bool math_success = math_plot.save_png("output/03_math_functions.png");
    
    if (math_success) {
        std::cout << "✅ Math functions plot saved!" << std::endl;
        std::cout << "📈 You can see both sine and cosine waves on the same plot!" << std::endl;
    }
    
    // Method 3: Using Point2D data (alternative way)
    std::cout << "Creating a growth trend plot..." << std::endl;
    
    std::vector<plotlib::Point2D> growth_data = {
        {2020, 100}, {2021, 120}, {2022, 150}, {2023, 180}, {2024, 220}
    };
    
    plotlib::LinePlot growth_plot(800, 600);
    growth_plot.set_labels("Company Growth", "Year", "Revenue (thousands)");
    growth_plot.add_line("Revenue", growth_data, "purple");
    
    bool growth_success = growth_plot.save_png("output/03_growth_trend.png");
    
    if (growth_success) {
        std::cout << "✅ Growth trend plot saved!" << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to create line plots using X and Y vectors (easiest method!)
 * - How to plot mathematical functions like sin(x) and cos(x)
 * - How to plot multiple lines on the same graph
 * - How to use Point2D data for line plots (alternative method)
 * - Line plots are perfect for showing trends over time
 * 
 * 🚀 Try this:
 * - Change the temperature data to see different patterns
 * - Try other math functions like tan(x) or x²
 * - Create your own time series data
 * - Run example 04 to learn about histograms!
 */ 