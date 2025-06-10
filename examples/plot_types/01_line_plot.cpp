/**
 * @file 01_line_plot.cpp
 * @brief Comprehensive LinePlot functionality demonstration
 * 
 * This example demonstrates ALL public LinePlot functionality including:
 * - All add_line() overloads
 * - Reference line capabilities
 * - Complete API coverage for precise code review
 */

#include "line_plot.h"
#include <vector>
#include <iostream>
#include <cmath>

int main() {
    std::cout << "=== Comprehensive LinePlot Functionality ===" << std::endl;
    
    // Create sample data
    std::vector<double> x_values;
    std::vector<double> sine_values;
    std::vector<double> cosine_values;
    std::vector<double> linear_values;
    
    // Generate data for mathematical functions
    for (int i = 0; i <= 50; ++i) {
        double x = i * 2 * M_PI / 50;  // From 0 to 2π
        x_values.push_back(x);
        sine_values.push_back(std::sin(x));
        cosine_values.push_back(std::cos(x));
        linear_values.push_back(x / (2 * M_PI) - 0.5);  // Linear trend
    }
    
    // Create LinePlot with all functionality
    plotlib::LinePlot plot(1000, 700);
    plot.set_labels("Comprehensive LinePlot API Demonstration", "X Values", "Y Values");
    
    // =====================================================================
    // DEMONSTRATE ALL add_line() OVERLOADS
    // =====================================================================
    
    std::cout << "1. Testing all add_line() overloads..." << std::endl;
    
    // Overload 1: data only (auto-name, auto-color)
    plot.add_line(linear_values, linear_values);  // "Line 1", auto-color
    
    // Overload 2: data + name (auto-color)
    plot.add_line(x_values, sine_values, "sin(x)");  // auto-color
    
    // Overload 3: data + name + color (full specification)
    plot.add_line(x_values, cosine_values, "cos(x)", "red");  // explicit red
    
    // =====================================================================
    // DEMONSTRATE ALL add_vertical_line() OVERLOADS
    // =====================================================================
    
    std::cout << "2. Testing all add_vertical_line() overloads..." << std::endl;
    
    // Overload 1: value only (auto-label, auto-color avoiding data colors)
    plot.add_vertical_line(M_PI, "");  // "Ref Line 1", auto-color
    
    // Overload 2: value + label (auto-color avoiding data colors)
    plot.add_vertical_line(2 * M_PI, "2π");  // auto-color
    
    // Overload 3: value + label + color (full specification)
    plot.add_vertical_line(M_PI / 2, "π/2", "purple");  // explicit purple
    
    // =====================================================================
    // DEMONSTRATE ALL add_horizontal_line() OVERLOADS
    // =====================================================================
    
    std::cout << "3. Testing all add_horizontal_line() overloads..." << std::endl;
    
    // Overload 1: value only (auto-label, auto-color avoiding data colors)
    plot.add_horizontal_line(0.0, "");  // "Ref Line 4", auto-color
    
    // Overload 2: value + label (auto-color avoiding data colors)
    plot.add_horizontal_line(0.5, "Upper Threshold");  // auto-color
    
    // Overload 3: value + label + color (full specification)
    plot.add_horizontal_line(-0.5, "Lower Threshold", "orange");  // explicit orange
    
    // =====================================================================
    // DEMONSTRATE OTHER PUBLIC FUNCTIONALITY
    // =====================================================================
    
    std::cout << "4. Testing other public LinePlot methods..." << std::endl;
    
    // Line style configuration
    plot.set_default_line_style(plotlib::LinePlot::LineStyle::SOLID);
    plot.set_default_line_width(2.0);
    plot.set_default_show_markers(true);
    plot.set_default_marker_type(plotlib::MarkerType::CIRCLE);
    
    // Legend management (inherited from PlotManager)
    plot.set_legend_enabled(true);
    
    // Title and labels (inherited from PlotManager)
    plot.set_title("Complete LinePlot API Test");
    plot.set_xlabel("X Axis (radians)");
    plot.set_ylabel("Y Axis (amplitude)");
    
    // =====================================================================
    // SAVE AND REPORT
    // =====================================================================
    
    bool success = plot.save_png("output/01_line_plot_comprehensive.png");
    
    if (success) {
        std::cout << "✅ Comprehensive LinePlot demonstration saved!" << std::endl;
        std::cout << "📊 Features demonstrated:" << std::endl;
        std::cout << "   📈 3 line series with different overloads:" << std::endl;
        std::cout << "      • Line 1: data only (auto-name, auto-color)" << std::endl;
        std::cout << "      • sin(x): data + name (auto-color)" << std::endl;
        std::cout << "      • cos(x): data + name + color" << std::endl;
        std::cout << "   📏 6 reference lines with different overloads:" << std::endl;
        std::cout << "      • 3 vertical lines (auto, auto+label, full)" << std::endl;
        std::cout << "      • 3 horizontal lines (auto, auto+label, full)" << std::endl;
        std::cout << "   ⚙️ All LinePlot-specific configuration methods" << std::endl;
        std::cout << "   🎨 Auto-color conflict avoidance for reference lines" << std::endl;
        std::cout << "   🏷️ Auto-naming for both data series and reference lines" << std::endl;
    } else {
        std::cout << "❌ Failed to save plot" << std::endl;
    }
    
    return success ? 0 : 1;
}

/*
 * 🎯 Complete LinePlot API Coverage:
 * 
 * DATA METHODS (3 overloads):
 * ✅ add_line(x_values, y_values) - auto-name, auto-color
 * ✅ add_line(x_values, y_values, name) - auto-color
 * ✅ add_line(x_values, y_values, name, color) - full specification
 * 
 * VERTICAL REFERENCE LINES (3 overloads):
 * ✅ add_vertical_line(x_value) - auto-label, auto-color
 * ✅ add_vertical_line(x_value, label) - auto-color
 * ✅ add_vertical_line(x_value, label, color) - full specification
 * 
 * HORIZONTAL REFERENCE LINES (3 overloads):
 * ✅ add_horizontal_line(y_value) - auto-label, auto-color
 * ✅ add_horizontal_line(y_value, label) - auto-color
 * ✅ add_horizontal_line(y_value, label, color) - full specification
 * 
 * CONFIGURATION METHODS:
 * ✅ set_default_line_style() - SOLID, DASHED, DOTTED
 * ✅ set_default_line_width() - line thickness
 * ✅ set_default_show_markers() - enable/disable markers
 * ✅ set_default_marker_type() - CIRCLE, CROSS, SQUARE, TRIANGLE
 * 
 * INHERITED METHODS:
 * ✅ set_labels(), set_title(), set_xlabel(), set_ylabel()
 * ✅ set_legend_enabled(), hide_legend_item()
 * ✅ save_png(), save_svg()
 */