#include "scatter_plot.h"
#include <vector>
#include <cmath>
#include <iostream>

int main() {
    // Create a scatter plot
    ScatterPlot plot(800, 600);
    
    // Set title and axis labels
    plot.set_title("Simple Function Visualization");
    plot.set_xlabel("X Values");
    plot.set_ylabel("Y Values");
    
    // Create some sample data
    std::vector<Point2D> sine_data, cosine_data, linear_data;
    
    for (int i = 0; i <= 50; ++i) {
        double x = i * 0.2;
        
        // Sine wave data
        sine_data.emplace_back(x, sin(x));
        
        // Cosine wave data
        cosine_data.emplace_back(x, cos(x));
        
        // Linear data with some noise
        linear_data.emplace_back(x, 0.1 * x + 0.5 + 0.1 * sin(x * 3));
    }
    
    // Define styles for each series
    PlotStyle sine_style;
    sine_style.r = 1.0; sine_style.g = 0.0; sine_style.b = 0.0;  // Red
    sine_style.point_size = 3.0;
    sine_style.alpha = 0.8;
    
    PlotStyle cosine_style;
    cosine_style.r = 0.0; cosine_style.g = 0.0; cosine_style.b = 1.0;  // Blue
    cosine_style.point_size = 3.0;
    cosine_style.alpha = 0.8;
    
    PlotStyle linear_style;
    linear_style.r = 0.0; linear_style.g = 0.8; linear_style.b = 0.0;  // Green
    linear_style.point_size = 2.5;
    linear_style.alpha = 0.7;
    
    // Add data series to the plot
    plot.add_series("sin(x)", sine_data, sine_style);
    plot.add_series("cos(x)", cosine_data, cosine_style);
    plot.add_series("Linear", linear_data, linear_style);
    
    // Save the plot
    plot.save_png("output/example_plot.png");
    plot.save_svg("output/example_plot.svg");
    
    std::cout << "Example plot saved to output/example_plot.png and output/example_plot.svg" << std::endl;
    
    return 0;
} 