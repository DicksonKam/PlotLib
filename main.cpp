#include "scatter_plot.h"
#include <random>
#include <iostream>
#include <filesystem> // C++17 feature

int main() {
    std::cout << "Creating enhanced scatter plot on macOS..." << std::endl;
    
    ScatterPlot plot(900, 700);  // Slightly larger to accommodate legend
    
    // Set plot labels and title
    plot.set_labels("Statistical Data Comparison", "X Values", "Y Values");
    
    // Generate sample data with different distributions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normal_dist(0.0, 1.0);
    std::uniform_real_distribution<> uniform_dist(-3.0, 3.0);
    
    // Dataset 1: Normal distribution (blue points)
    PlotStyle blue_style;
    blue_style.r = 0.2; blue_style.g = 0.4; blue_style.b = 0.8;
    blue_style.point_size = 3.0;
    blue_style.alpha = 0.7;
    
    std::vector<Point2D> normal_points;
    for (int i = 0; i < 150; ++i) {
        double x = normal_dist(gen);
        double y = normal_dist(gen);
        normal_points.emplace_back(x, y);
    }
    plot.add_series("Normal Distribution", normal_points, blue_style);
    
    // Dataset 2: Uniform distribution (red points)
    PlotStyle red_style;
    red_style.r = 0.8; red_style.g = 0.2; red_style.b = 0.2;
    red_style.point_size = 4.0;
    red_style.alpha = 0.6;
    
    std::vector<Point2D> uniform_points;
    for (int i = 0; i < 100; ++i) {
        double x = uniform_dist(gen);
        double y = uniform_dist(gen) * 0.5;
        uniform_points.emplace_back(x, y);
    }
    plot.add_series("Uniform Distribution", uniform_points, red_style);
    
    // Dataset 3: Clustered data (green points)
    PlotStyle green_style;
    green_style.r = 0.2; green_style.g = 0.7; green_style.b = 0.3;
    green_style.point_size = 2.5;
    green_style.alpha = 0.8;
    
    std::vector<Point2D> clustered_points;
    for (int i = 0; i < 75; ++i) {
        double x = normal_dist(gen) * 0.5 + 1.5;
        double y = normal_dist(gen) * 0.5 - 1.5;
        clustered_points.emplace_back(x, y);
    }
    plot.add_series("Clustered Data", clustered_points, green_style);
    
    // Dataset 4: Linear relationship (purple points)
    PlotStyle purple_style;
    purple_style.r = 0.6; purple_style.g = 0.2; purple_style.b = 0.8;
    purple_style.point_size = 3.5;
    purple_style.alpha = 0.7;
    
    std::vector<Point2D> linear_points;
    std::normal_distribution<> noise_dist(0.0, 0.3);
    for (int i = 0; i < 80; ++i) {
        double x = uniform_dist(gen) * 0.8;
        double y = 0.7 * x + 1.2 + noise_dist(gen);  // Linear relationship with noise
        linear_points.emplace_back(x, y);
    }
    plot.add_series("Linear Trend", linear_points, purple_style);
    
    // Create output directory if it doesn't exist
    std::filesystem::create_directories("output");
    
    // Save plots with full paths
    if (plot.save_png("output/enhanced_scatter_plot.png")) {
        std::cout << "✅ Enhanced PNG saved successfully to output/enhanced_scatter_plot.png" << std::endl;
    } else {
        std::cout << "❌ Failed to save PNG" << std::endl;
    }
    
    if (plot.save_svg("output/enhanced_scatter_plot.svg")) {
        std::cout << "✅ Enhanced SVG saved successfully to output/enhanced_scatter_plot.svg" << std::endl;
    } else {
        std::cout << "❌ Failed to save SVG" << std::endl;
    }
    
    // Demonstrate individual series addition
    std::cout << "\nDemonstrating individual point addition..." << std::endl;
    ScatterPlot simple_plot(600, 500);
    simple_plot.set_title("Simple Example");
    simple_plot.set_xlabel("Time (seconds)");
    simple_plot.set_ylabel("Temperature (°C)");
    
    // Add some temperature data points
    PlotStyle temp_style;
    temp_style.r = 1.0; temp_style.g = 0.5; temp_style.b = 0.0;
    temp_style.point_size = 4.0;
    
    for (int i = 0; i < 20; ++i) {
        double time = i * 0.5;
        double temp = 20 + 5 * sin(time * 0.5) + normal_dist(gen) * 0.5;
        plot.add_series_point("Temperature", time, temp);
    }
    
    // Set style for the temperature series (this would need to be done differently in practice)
    // For now, we'll create a separate plot to demonstrate
    
    std::cout << "Enhanced scatter plot library demonstration completed!" << std::endl;
    std::cout << "\nLibrary Features:" << std::endl;
    std::cout << "- Automatic axis scaling and tick generation" << std::endl;
    std::cout << "- Customizable axis labels and plot titles" << std::endl;
    std::cout << "- Legend support for multiple data series" << std::endl;
    std::cout << "- Grid lines aligned with axis ticks" << std::endl;
    std::cout << "- Support for both series-based and individual point addition" << std::endl;
    
    return 0;
}
