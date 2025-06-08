#include "plotlib/line_plot.h"
#include "plotlib/scatter_plot.h"
#include <vector>
#include <random>
#include <iostream>
#include <filesystem>
#include <cmath>

int main() {
    std::cout << "=== LinePlot Demonstration ===" << std::endl;
    std::cout << "Demonstrating the new LinePlot functionality..." << std::endl;
    
    // Create output directory
    std::filesystem::create_directories("output");
    
    // =================================================================
    // DEMO 1: Basic Line Plot
    // =================================================================
    std::cout << "\n1. Creating basic line plot..." << std::endl;
    {
        LinePlot plot(800, 600);
        plot.set_labels("Basic Line Plot", "X Values", "Y Values");
        
        // Create some mathematical functions
        std::vector<Point2D> sine_data, cosine_data, linear_data;
        for (int i = 0; i <= 50; ++i) {
            double x = i * 0.2;
            sine_data.emplace_back(x, sin(x));
            cosine_data.emplace_back(x, cos(x));
            linear_data.emplace_back(x, 0.1 * x + 0.5);
        }
        
        PlotStyle sine_style = {2.0, 1.0, 0.0, 0.0, 0.8};  // Red line
        PlotStyle cosine_style = {2.0, 0.0, 0.0, 1.0, 0.8}; // Blue line
        PlotStyle linear_style = {2.0, 0.0, 0.8, 0.0, 0.8}; // Green line
        
        plot.add_series("sin(x)", sine_data, sine_style);
        plot.add_series("cos(x)", cosine_data, cosine_style);
        plot.add_series("linear", linear_data, linear_style);
        
        plot.save_png("output/line_plot_basic.png");
        std::cout << "✅ Basic line plot saved to output/line_plot_basic.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 2: Line Plot with Markers
    // =================================================================
    std::cout << "\n2. Creating line plot with markers..." << std::endl;
    {
        LinePlot plot(800, 600);
        plot.set_labels("Line Plot with Markers", "X Values", "Y Values");
        plot.set_show_markers(true);
        plot.set_default_marker_type(MarkerType::CIRCLE);
        
        // Create some data with fewer points to show markers clearly
        std::vector<Point2D> data1, data2;
        for (int i = 0; i <= 10; ++i) {
            double x = i;
            data1.emplace_back(x, x * x * 0.1);
            data2.emplace_back(x, 5 - x * 0.3);
        }
        
        PlotStyle style1 = {4.0, 0.8, 0.2, 0.2, 0.8}; // Red
        PlotStyle style2 = {4.0, 0.2, 0.2, 0.8, 0.8}; // Blue
        
        plot.add_series("Quadratic", data1, style1);
        plot.add_series("Linear", data2, style2);
        
        plot.save_png("output/line_plot_markers.png");
        std::cout << "✅ Line plot with markers saved to output/line_plot_markers.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 3: Mixed Plot Types in Subplots
    // =================================================================
    std::cout << "\n3. Creating mixed plot types demonstration..." << std::endl;
    {
        SubplotManager layout(2, 2, 1200, 900, 0.08);
        layout.set_main_title("Mixed Plot Types: Scatter vs Line Plots");
        
        // Subplot 1: Scatter plot
        {
            auto& plot = layout.get_subplot<ScatterPlot>(0, 0);
            plot.set_labels("Scatter Plot", "X", "Y");
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> dist(0.0, 1.0);
            
            std::vector<Point2D> scatter_data;
            for (int i = 0; i < 50; ++i) {
                scatter_data.emplace_back(dist(gen), dist(gen));
            }
            
            PlotStyle scatter_style = {3.0, 0.8, 0.2, 0.2, 0.7};
            plot.add_series("Random Data", scatter_data, scatter_style);
        }
        
        // Subplot 2: Line plot
        {
            auto& plot = layout.get_subplot<LinePlot>(0, 1);
            plot.set_labels("Line Plot", "X", "Y");
            
            std::vector<Point2D> line_data;
            for (int i = 0; i <= 30; ++i) {
                double x = i * 0.3;
                line_data.emplace_back(x, sin(x) * exp(-x * 0.1));
            }
            
            PlotStyle line_style = {2.0, 0.2, 0.8, 0.2, 0.8};
            plot.add_series("Damped Sine", line_data, line_style);
        }
        
        // Subplot 3: Line plot with markers
        {
            auto& plot = layout.get_subplot<LinePlot>(1, 0);
            plot.set_labels("Line + Markers", "X", "Y");
            plot.set_show_markers(true);
            
            std::vector<Point2D> data;
            for (int i = 0; i <= 15; ++i) {
                double x = i * 0.5;
                data.emplace_back(x, log(x + 1));
            }
            
            PlotStyle style = {3.0, 0.2, 0.2, 0.8, 0.8};
            plot.add_series("log(x+1)", data, style);
        }
        
        // Subplot 4: Multiple line series
        {
            auto& plot = layout.get_subplot<LinePlot>(1, 1);
            plot.set_labels("Multiple Series", "X", "Y");
            
            std::vector<Point2D> exp_data, log_data, sqrt_data;
            for (int i = 1; i <= 20; ++i) {
                double x = i * 0.2;
                exp_data.emplace_back(x, exp(-x));
                log_data.emplace_back(x, log(x));
                sqrt_data.emplace_back(x, sqrt(x));
            }
            
            PlotStyle exp_style = {2.0, 1.0, 0.0, 0.0, 0.8};   // Red
            PlotStyle log_style = {2.0, 0.0, 1.0, 0.0, 0.8};   // Green
            PlotStyle sqrt_style = {2.0, 0.0, 0.0, 1.0, 0.8};  // Blue
            
            plot.add_series("exp(-x)", exp_data, exp_style);
            plot.add_series("log(x)", log_data, log_style);
            plot.add_series("sqrt(x)", sqrt_data, sqrt_style);
        }
        
        layout.save_png("output/mixed_plot_types.png");
        std::cout << "✅ Mixed plot types saved to output/mixed_plot_types.png" << std::endl;
    }
    
    std::cout << "\n=== LinePlot Demo Complete ===" << std::endl;
    std::cout << "Generated demonstrations:" << std::endl;
    std::cout << "1. Basic line plot with multiple series" << std::endl;
    std::cout << "2. Line plot with markers enabled" << std::endl;
    std::cout << "3. Mixed plot types in subplots (scatter + line)" << std::endl;
    std::cout << "\nAll outputs saved to output/ directory" << std::endl;
    
    return 0;
} 