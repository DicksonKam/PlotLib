#include <vector>
#include <iostream>
#include <cmath>
#include "plot_manager.h"
#include "scatter_plot.h"
#include "line_plot.h"
#include "histogram_plot.h"

using namespace plotlib;

int main() {
    std::cout << "Reference Lines and Plot Annotations" << std::endl;
    std::cout << "====================================" << std::endl;
    
    std::cout << "Creating reference line examples..." << std::endl;
    
    // Create some sample data
    std::vector<Point2D> data_points;
    std::vector<double> histogram_data;
    
    // Generate sample data
    for (int i = 0; i < 100; ++i) {
        double x = i * 0.1;
        double y = sin(x) * 2 + 1.5;
        data_points.push_back(Point2D(x, y));
        histogram_data.push_back(y);
    }
    
    // Example 1: Scatter plot with reference lines
    std::cout << "1. Scatter plot with reference lines..." << std::endl;
    
    ScatterPlot scatter_plot(800, 600);
    scatter_plot.set_labels("Scatter Plot with Reference Lines", "X Values", "Y Values");
    
    PlotStyle red_style = PlotManager::color_to_style("red", 3.0, 2.0);
    scatter_plot.add_series("Sine Wave", data_points, red_style);
    
    // Add vertical reference line at x = 5
    scatter_plot.add_vertical_line(5.0, "X = 5 (Vertical)");
    
    // Add horizontal reference line at y = 1.5
    scatter_plot.add_horizontal_line(1.5, "Y = 1.5 (Horizontal)");
    
    // Add a custom styled reference line
    PlotStyle green_style = PlotManager::color_to_style("green", 3.0, 2.0);
    scatter_plot.add_vertical_line(7.5, "Important X", green_style);
    
    scatter_plot.save_png("output/advanced_04_reference_lines_scatter.png");
    std::cout << "✅ Scatter plot with reference lines saved!" << std::endl;
    
    // Example 2: Line plot with reference lines
    std::cout << "2. Line plot with reference lines..." << std::endl;
    
    LinePlot line_plot(800, 600);
    line_plot.set_labels("Line Plot with Reference Lines", "X Values", "Y Values");
    line_plot.set_show_markers(true);
    
    PlotStyle blue_style = PlotManager::color_to_style("blue", 3.0, 2.0);
    line_plot.add_series("Sine Wave", data_points, blue_style);
    
    // Add reference lines
    line_plot.add_vertical_line(3.14, "π (Pi)");
    line_plot.add_horizontal_line(0.0, "Zero Line");
    line_plot.add_horizontal_line(3.5, "Max Line");
    
    line_plot.save_png("output/advanced_04_reference_lines_line.png");
    std::cout << "✅ Line plot with reference lines saved!" << std::endl;
    
    // Example 3: Histogram with reference lines
    std::cout << "3. Histogram with statistical reference lines..." << std::endl;
    
    HistogramPlot histogram(800, 600);
    histogram.set_labels("Histogram with Reference Lines", "Values", "Frequency");
    
    PlotStyle purple_style = PlotManager::color_to_style("purple", 3.0, 2.0);
    histogram.add_data("Sample Data", histogram_data, purple_style, 20);
    
    // Add reference lines for statistical measures
    double mean = 0.0;
    for (double val : histogram_data) mean += val;
    mean /= histogram_data.size();
    
    histogram.add_vertical_line(mean, "Mean");
    histogram.add_vertical_line(0.0, "Zero");
    histogram.add_vertical_line(3.0, "Upper Bound");
    
    histogram.save_png("output/advanced_04_reference_lines_histogram.png");
    std::cout << "✅ Histogram with reference lines saved!" << std::endl;
    
    // Example 4: Custom reference line styles
    std::cout << "4. Custom reference line styling..." << std::endl;
    
    ScatterPlot custom_plot(800, 600);
    custom_plot.set_labels("Custom Reference Line Styles", "X Values", "Y Values");
    
    PlotStyle blue_style2 = PlotManager::color_to_style("blue", 3.0, 2.0);
    custom_plot.add_series("Data", data_points, blue_style2);
    
    // Create custom styles for reference lines
    PlotStyle red_ref_style;
    red_ref_style.r = 1.0; red_ref_style.g = 0.0; red_ref_style.b = 0.0;
    red_ref_style.line_width = 2.0;
    red_ref_style.alpha = 0.9;
    
    PlotStyle orange_ref_style;
    orange_ref_style.r = 1.0; orange_ref_style.g = 0.5; orange_ref_style.b = 0.0;
    orange_ref_style.line_width = 1.0;
    orange_ref_style.alpha = 0.7;
    
    custom_plot.add_vertical_line(2.0, "Red Line", red_ref_style);
    custom_plot.add_horizontal_line(2.5, "Orange Line", orange_ref_style);
    
    custom_plot.save_png("output/advanced_04_reference_lines_custom.png");
    std::cout << "✅ Custom styled reference lines saved!" << std::endl;
    
    // Example 5: Subplot compatibility testing
    std::cout << "5. Reference lines in subplot dashboard..." << std::endl;
    
    SubplotManager dashboard(2, 2, 1200, 900);
    dashboard.set_main_title("Reference Lines in Subplots Dashboard");
    
    // (0,0) - Scatter plot with reference lines
    auto& subplot_scatter = dashboard.get_subplot<ScatterPlot>(0, 0);
    subplot_scatter.set_labels("Subplot Scatter", "X", "Y");
    subplot_scatter.add_series("Data", data_points, red_style);
    subplot_scatter.add_vertical_line(5.0, "Vertical Ref");
    subplot_scatter.add_horizontal_line(1.5, "Horizontal Ref");
    
    // (0,1) - Line plot with reference lines
    auto& subplot_line = dashboard.get_subplot<LinePlot>(0, 1);
    subplot_line.set_labels("Subplot Line", "X", "Y");
    subplot_line.add_series("Signal", data_points, blue_style);
    subplot_line.add_vertical_line(3.14, "π");
    subplot_line.add_horizontal_line(0.0, "Zero");
    
    // (1,0) - Histogram with reference lines
    auto& subplot_hist = dashboard.get_subplot<HistogramPlot>(1, 0);
    subplot_hist.set_labels("Subplot Histogram", "Value", "Freq");
    subplot_hist.add_data("Distribution", histogram_data, purple_style, 15);
    subplot_hist.add_vertical_line(mean, "Mean");
    subplot_hist.add_vertical_line(3.0, "Threshold");
    
    // (1,1) - Mixed data and reference lines with legend management
    auto& subplot_mixed = dashboard.get_subplot<ScatterPlot>(1, 1);
    subplot_mixed.set_labels("Legend Management", "X", "Y");
    
    // Add multiple data series
    subplot_mixed.add_series("Primary Data", data_points, red_style);
    
    // Generate secondary data
    std::vector<Point2D> secondary_data;
    for (int i = 0; i < 50; ++i) {
        double x = i * 0.2;
        double y = cos(x) * 1.5 + 2.0;
        secondary_data.push_back(Point2D(x, y));
    }
    subplot_mixed.add_series("Secondary Data", secondary_data, green_style);
    
    // Add reference lines
    subplot_mixed.add_vertical_line(4.0, "Critical X");
    subplot_mixed.add_horizontal_line(2.0, "Baseline");
    subplot_mixed.add_vertical_line(8.0, "Max X");
    
    // Test selective legend hiding
    subplot_mixed.hide_legend_item("Secondary Data");  // Hide data series
    subplot_mixed.hide_legend_item("Max X");           // Hide reference line
    
    dashboard.save_png("output/advanced_04_reference_lines_subplots.png");
    std::cout << "✅ Subplot dashboard with reference lines saved!" << std::endl;
    
    // Example 6: Advanced legend management testing
    std::cout << "6. Advanced legend management with reference lines..." << std::endl;
    
    ScatterPlot legend_test(1000, 700);
    legend_test.set_labels("Advanced Legend Management", "X Values", "Y Values");
    
    // Add multiple data series
    legend_test.add_series("Dataset A", data_points, red_style);
    
    std::vector<Point2D> dataset_b;
    for (int i = 0; i < 80; ++i) {
        double x = i * 0.125;
        double y = sin(x * 0.8) * 1.8 + 1.0;
        dataset_b.push_back(Point2D(x, y));
    }
    legend_test.add_series("Dataset B", dataset_b, blue_style);
    
    std::vector<Point2D> dataset_c;
    for (int i = 0; i < 60; ++i) {
        double x = i * 0.17;
        double y = cos(x * 1.2) * 2.2 + 2.0;
        dataset_c.push_back(Point2D(x, y));
    }
    PlotStyle yellow_style = PlotManager::color_to_style("orange", 3.0, 2.0);
    legend_test.add_series("Dataset C", dataset_c, yellow_style);
    
    // Add multiple reference lines
    legend_test.add_vertical_line(2.0, "Ref Line 1");
    legend_test.add_vertical_line(5.0, "Ref Line 2", green_style);
    legend_test.add_horizontal_line(0.5, "Lower Bound");
    legend_test.add_horizontal_line(3.5, "Upper Bound", orange_ref_style);
    legend_test.add_vertical_line(8.0, "Ref Line 3");
    
    // Selectively hide some items for cleaner legend
    legend_test.hide_legend_item("Dataset B");        // Hide data series
    legend_test.hide_legend_item("Ref Line 1");       // Hide reference line
    legend_test.hide_legend_item("Lower Bound");      // Hide reference line
    legend_test.hide_legend_item("Ref Line 3");       // Hide reference line
    
    legend_test.save_png("output/advanced_04_reference_lines_legend.png");
    std::cout << "✅ Advanced legend management test saved!" << std::endl;
    
    std::cout << "\n🎯 Advanced Example 4 Complete!" << std::endl;
    std::cout << "Generated 6 reference line plots demonstrating:" << std::endl;
    std::cout << "  • Basic scatter plot reference line integration" << std::endl;
    std::cout << "  • Line plot reference line markers" << std::endl;
    std::cout << "  • Statistical reference lines in histograms" << std::endl;
    std::cout << "  • Custom reference line styling and colors" << std::endl;
    std::cout << "  • Reference lines in subplot dashboards" << std::endl;
    std::cout << "  • Advanced legend management with reference lines" << std::endl;
    
    return 0;
} 