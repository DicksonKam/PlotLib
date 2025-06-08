#include "scatter_plot.h"
#include "line_plot.h"
#include "histogram_plot.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <filesystem>

// Simple test framework
int test_count = 0;
int passed_tests = 0;

void test_assert(bool condition, const std::string& test_name) {
    test_count++;
    if (condition) {
        std::cout << "✅ PASS: " << test_name << std::endl;
        passed_tests++;
    } else {
        std::cout << "❌ FAIL: " << test_name << std::endl;
    }
}

void test_basic_plot_creation() {
    try {
        plotlib::ScatterPlot plot(800, 600);
        plot.set_labels("Test Plot", "X", "Y");
        
        std::vector<plotlib::Point2D> data = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 1.0}};
        plot.add_data("Test Series", data, "blue");
        
        test_assert(true, "Basic plot creation and data addition");
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        test_assert(false, "Basic plot creation and data addition");
    }
}

void test_line_plot_creation() {
    try {
        plotlib::LinePlot plot(600, 400);
        plot.set_labels("Line Test", "X", "Y");
        
        std::vector<double> x_vals = {1.0, 2.0, 3.0, 4.0};
        std::vector<double> y_vals = {1.0, 4.0, 9.0, 16.0};
        plot.add_line("Square Function", x_vals, y_vals, "red");
        
        test_assert(true, "Line plot creation");
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        test_assert(false, "Line plot creation");
    }
}

void test_histogram_creation() {
    try {
        plotlib::HistogramPlot plot(600, 400);
        plot.set_labels("Histogram Test", "Value", "Frequency");
        
        std::vector<double> data = {1.0, 1.5, 2.0, 2.2, 2.5, 3.0, 3.1, 3.5, 4.0};
        plot.add_histogram("Test Data", data, "green");
        
        test_assert(true, "Histogram creation");
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        test_assert(false, "Histogram creation");
    }
}

void test_subplot_creation() {
    try {
        plotlib::SubplotManager manager(2, 2, 800, 600);
        manager.set_main_title("Test Subplots");
        
        auto& subplot = manager.get_subplot<plotlib::ScatterPlot>(0, 0);
        subplot.set_labels("Test", "X", "Y");
        
        std::vector<plotlib::Point2D> data = {{0.0, 0.0}, {1.0, 1.0}};
        subplot.add_data("Test", data, "blue");
        
        test_assert(true, "Subplot creation and configuration");
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        test_assert(false, "Subplot creation and configuration");
    }
}

void test_cluster_visualization() {
    try {
        plotlib::ScatterPlot plot(600, 400);
        plot.set_labels("Cluster Test", "X", "Y");
        
        std::vector<plotlib::Point2D> points = {{1.0, 1.0}, {1.1, 1.1}, {-1.0, -1.0}, {-1.1, -1.1}};
        std::vector<int> labels = {0, 0, 1, 1};
        
        plot.add_clusters(points, labels);
        
        test_assert(true, "Cluster visualization");
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        test_assert(false, "Cluster visualization");
    }
}

void test_file_output() {
    try {
        // Create test output directory
        std::filesystem::create_directories("test_output");
        
        plotlib::ScatterPlot plot(400, 300);
        plot.set_labels("Output Test", "X", "Y");
        
        std::vector<plotlib::Point2D> data = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 0.5}};
        plot.add_data("Test", data, "red");
        
        plot.save_png("test_output/test_plot.png");
        
        // Check if file was created
        bool file_exists = std::filesystem::exists("test_output/test_plot.png");
        test_assert(file_exists, "PNG file output");
        
        // Clean up
        if (file_exists) {
            std::filesystem::remove("test_output/test_plot.png");
        }
        std::filesystem::remove("test_output");
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        test_assert(false, "PNG file output");
    }
}

void test_point2d_operations() {
    plotlib::Point2D p1(1.0, 2.0);
    plotlib::Point2D p2(3.0, 4.0);
    
    test_assert(p1.x == 1.0 && p1.y == 2.0, "Point2D construction");
    
    // Test copy constructor if available
    plotlib::Point2D p3 = p1;
    test_assert(p3.x == p1.x && p3.y == p1.y, "Point2D copy");
}

void test_plot_style() {
    plotlib::PlotStyle style;
    style.point_size = 3.0;
    style.line_width = 2.0;
    style.r = 1.0;
    style.g = 0.5;
    style.b = 0.0;
    style.alpha = 0.8;
    
    test_assert(style.point_size == 3.0, "PlotStyle point size");
    test_assert(style.r == 1.0, "PlotStyle red component");
    test_assert(style.g == 0.5, "PlotStyle green component");
    test_assert(style.b == 0.0, "PlotStyle blue component");
    test_assert(style.alpha == 0.8, "PlotStyle alpha");
}

int main() {
    std::cout << "=== PlotLib Basic Tests ===" << std::endl;
    std::cout << "Running basic functionality tests...\n" << std::endl;
    
    // Run all tests
    test_point2d_operations();
    test_plot_style();
    test_basic_plot_creation();
    test_line_plot_creation();
    test_histogram_creation();
    test_subplot_creation();
    test_cluster_visualization();
    test_file_output();
    
    // Print results
    std::cout << "\n=== Test Results ===" << std::endl;
    std::cout << "Passed: " << passed_tests << "/" << test_count << " tests" << std::endl;
    
    if (passed_tests == test_count) {
        std::cout << "🎉 All tests passed!" << std::endl;
        return 0;
    } else {
        std::cout << "❌ Some tests failed!" << std::endl;
        return 1;
    }
} 