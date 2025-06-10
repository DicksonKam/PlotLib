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
    plot.add_line(time, temperature, "Temperature", "red");
    
    bool success = plot.save_png("output/beginner_03_temperature_line.png");
    
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
    math_plot.add_line(x_values, sine_values, "sin(x)", "blue");
    math_plot.add_line(x_values, cosine_values, "cos(x)", "green");
    
    bool math_success = math_plot.save_png("output/beginner_03_math_functions.png");
    
    if (math_success) {
        std::cout << "✅ Math functions plot saved!" << std::endl;
        std::cout << "📈 You can see both sine and cosine waves on the same plot!" << std::endl;
    }
    
    // Method 3: Create a growth trend plot with automatic colors
    std::cout << "Creating a growth trend plot..." << std::endl;
    
    std::vector<double> years = {2020, 2021, 2022, 2023, 2024};
    std::vector<double> revenue = {100, 120, 150, 180, 220};
    
    plotlib::LinePlot growth_plot(800, 600);
    growth_plot.set_labels("Company Growth", "Year", "Revenue (thousands)");
    
    // Use automatic color selection
    growth_plot.add_line(years, revenue, "Revenue");
    
    bool growth_success = growth_plot.save_png("output/beginner_03_growth_trend.png");
    
    if (growth_success) {
        std::cout << "✅ Growth trend plot saved!" << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to create line plots using X and Y vectors (simple and intuitive!)
 * - How to plot mathematical functions like sin(x) and cos(x)
 * - How to plot multiple lines on the same graph
 * - How to use both custom colors and automatic color selection
 * - Line plots are perfect for showing trends over time
 * 
 * 🚀 Try this:
 * - Change the temperature data to see different patterns
 * - Try other math functions like tan(x) or x²
 * - Create your own time series data
 * - Run example 04 to learn about histograms!
 */ 