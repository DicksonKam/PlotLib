/**
 * @file 05_simple_subplots.cpp
 * @brief Your first subplots - multiple plots in one figure
 * 
 * This example shows how to create subplots, which let you:
 * - Show multiple related plots together
 * - Compare different datasets side by side
 * - Create dashboards and reports
 */

#include "plotlib/scatter_plot.h"
#include "plotlib/line_plot.h"
#include "plotlib/histogram_plot.h"
#include "plotlib/plot_manager.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <random>

int main() {
    std::cout << "Creating your first subplots..." << std::endl;
    
    // Example 1: Simple 2x2 grid (4 plots)
    std::cout << "Creating a 2x2 dashboard..." << std::endl;
    
    // Create a 2x2 subplot manager (2 rows, 2 columns)
    plotlib::SubplotManager manager(2, 2, 1200, 900);
    manager.set_main_title("My First Dashboard");
    
    // Top-left (0,0): Scatter plot
    auto& scatter = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
    scatter.set_labels("Scatter Plot", "X", "Y");
    
    std::vector<plotlib::Point2D> scatter_data = {
        {1, 2}, {2, 4}, {3, 3}, {4, 5}, {5, 4}, {6, 6}
    };
    scatter.add_data("Data Points", scatter_data, "blue");
    
    // Top-right (0,1): Line plot
    auto& line = manager.get_subplot<plotlib::LinePlot>(0, 1);
    line.set_labels("Line Plot", "Time", "Value");
    
    std::vector<double> time = {0, 1, 2, 3, 4, 5};
    std::vector<double> values = {10, 15, 12, 18, 16, 20};
    line.add_line("Trend", time, values, "red");
    
    // Bottom-left (1,0): Histogram
    auto& hist = manager.get_subplot<plotlib::HistogramPlot>(1, 0);
    hist.set_labels("Histogram", "Value", "Frequency");
    
    std::vector<double> hist_data = {
        1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7
    };
    hist.add_histogram("Distribution", hist_data, "green", 7);
    
    // Bottom-right (1,1): Another scatter plot
    auto& scatter2 = manager.get_subplot<plotlib::ScatterPlot>(1, 1);
    scatter2.set_labels("Clusters", "X", "Y");
    
    std::vector<plotlib::Point2D> cluster_data = {
        {1, 1}, {1.5, 1.2}, {2, 1.1}, {5, 5}, {5.2, 5.1}, {4.8, 5.2}
    };
    std::vector<int> labels = {0, 0, 0, 1, 1, 1};
    scatter2.add_clusters(cluster_data, labels);
    
    bool success = manager.save_png("output/05_first_dashboard.png");
    
    if (success) {
        std::cout << "✅ 2x2 dashboard saved!" << std::endl;
        std::cout << "📊 You now have 4 different plots in one figure!" << std::endl;
    }
    
    // Example 2: Simple 1x3 layout (horizontal strip)
    std::cout << "Creating a 1x3 horizontal layout..." << std::endl;
    
    plotlib::SubplotManager horizontal(1, 3, 1500, 500);
    horizontal.set_main_title("Horizontal Comparison");
    
    // Left plot: Sales data
    auto& sales = horizontal.get_subplot<plotlib::LinePlot>(0, 0);
    sales.set_labels("Sales", "Month", "Revenue");
    
    std::vector<double> months = {1, 2, 3, 4, 5, 6};
    std::vector<double> revenue = {1000, 1200, 1100, 1400, 1300, 1600};
    sales.add_line("Revenue", months, revenue, "blue");
    
    // Middle plot: Customer satisfaction
    auto& satisfaction = horizontal.get_subplot<plotlib::ScatterPlot>(0, 1);
    satisfaction.set_labels("Satisfaction", "Service", "Rating");
    
    std::vector<plotlib::Point2D> ratings = {
        {1, 4.2}, {2, 4.5}, {3, 4.1}, {4, 4.7}, {5, 4.3}, {6, 4.8}
    };
    satisfaction.add_data("Ratings", ratings, "orange");
    
    // Right plot: Response times
    auto& response = horizontal.get_subplot<plotlib::HistogramPlot>(0, 2);
    response.set_labels("Response Times", "Time (ms)", "Count");
    
    std::random_device rd;
    std::mt19937 gen(42);
    std::normal_distribution<> dist(200, 50);
    
    std::vector<double> times;
    for (int i = 0; i < 100; ++i) {
        times.push_back(std::max(50.0, dist(gen)));  // Minimum 50ms
    }
    response.add_histogram("Response Times", times, "purple", 15);
    
    bool horizontal_success = horizontal.save_png("output/05_horizontal_layout.png");
    
    if (horizontal_success) {
        std::cout << "✅ Horizontal layout saved!" << std::endl;
        std::cout << "📈 Three plots side by side for easy comparison!" << std::endl;
    }
    
    // Example 3: Simple 3x1 layout (vertical strip)
    std::cout << "Creating a 3x1 vertical layout..." << std::endl;
    
    plotlib::SubplotManager vertical(3, 1, 600, 1200);
    vertical.set_main_title("Vertical Analysis");
    
    // Top plot: Temperature over time
    auto& temp = vertical.get_subplot<plotlib::LinePlot>(0, 0);
    temp.set_labels("Temperature", "Hour", "°C");
    
    std::vector<double> hours = {0, 6, 12, 18, 24};
    std::vector<double> temperature = {15, 18, 25, 22, 16};
    temp.add_line("Temperature", hours, temperature, "red");
    
    // Middle plot: Humidity
    auto& humidity = vertical.get_subplot<plotlib::LinePlot>(1, 0);
    humidity.set_labels("Humidity", "Hour", "%");
    
    std::vector<double> humidity_values = {60, 65, 45, 55, 70};
    humidity.add_line("Humidity", hours, humidity_values, "blue");
    
    // Bottom plot: Wind speed distribution
    auto& wind = vertical.get_subplot<plotlib::HistogramPlot>(2, 0);
    wind.set_labels("Wind Speed", "Speed (km/h)", "Frequency");
    
    std::vector<double> wind_speeds = {
        5, 8, 12, 6, 9, 15, 7, 11, 13, 8, 10, 14, 6, 9, 12,
        7, 11, 16, 8, 10, 13, 9, 12, 15, 7, 10, 14, 8, 11
    };
    wind.add_histogram("Wind Speed", wind_speeds, "green", 10);
    
    bool vertical_success = vertical.save_png("output/05_vertical_layout.png");
    
    if (vertical_success) {
        std::cout << "✅ Vertical layout saved!" << std::endl;
        std::cout << "🌤️ Weather data stacked vertically for easy reading!" << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to create subplot grids (2x2, 1x3, 3x1)
 * - How to access individual subplots using get_subplot<PlotType>(row, col)
 * - How to mix different plot types in the same figure
 * - How to set a main title for the entire figure
 * - Subplots are perfect for dashboards and comparisons
 * 
 * 🚀 Try this:
 * - Change the grid size (try 2x3 or 4x1)
 * - Mix different combinations of plot types
 * - Add more data to each subplot
 * - Try different colors and titles
 * 
 * 💡 Layout tips:
 * - 2x2: Good for 4 related plots
 * - 1xN: Good for comparing similar data horizontally
 * - Nx1: Good for showing data that flows vertically (like time series)
 * - Larger grids: Good for comprehensive dashboards
 */ 