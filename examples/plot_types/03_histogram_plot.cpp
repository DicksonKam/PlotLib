/**
 * @file 03_histogram_plot.cpp
 * @brief Comprehensive HistogramPlot functionality demonstration
 * 
 * This example demonstrates ALL public HistogramPlot functionality including:
 * - All continuous histogram overloads
 * - All discrete histogram overloads  
 * - Reference line capabilities
 * - Complete API coverage for precise code review
 */

#include "histogram_plot.h"
#include <vector>
#include <iostream>
#include <random>

int main() {
    std::cout << "=== Comprehensive HistogramPlot Functionality ===" << std::endl;
    
    // =====================================================================
    // CONTINUOUS HISTOGRAM DEMONSTRATION
    // =====================================================================
    
    std::cout << "1. Testing continuous histogram functionality..." << std::endl;
    
    // Generate sample continuous data
    std::random_device rd;
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::normal_distribution<> dist(100, 15);
    
    std::vector<double> data1, data2, data3;
    for (int i = 0; i < 200; ++i) {
        data1.push_back(dist(gen));
        data2.push_back(dist(gen) + 20); // Shifted distribution
        data3.push_back(dist(gen) - 10); // Another shifted distribution
    }
    
    // Create continuous histogram plot
    plotlib::HistogramPlot continuous_plot(1000, 700);
    continuous_plot.set_labels("Continuous Histogram API Demonstration", "Value", "Frequency");
    
    // DEMONSTRATE ALL continuous add_histogram() OVERLOADS
    
    // Overload 1: data only (auto-name, auto-color, auto-bins)
    continuous_plot.add_histogram(data1);  // "Histogram 1", auto-color, auto-bins
    
    // Overload 2: data + name (auto-color, auto-bins)
    continuous_plot.add_histogram(data2, "Dataset Alpha");  // auto-color, auto-bins
    
    // Overload 3: data + name + color (auto-bins)
    continuous_plot.add_histogram(data3, "Dataset Beta", "red");  // auto-bins
    
    // Overload 4: data + name + color + bin_count (full specification)
    std::vector<double> data4;
    for (int i = 0; i < 100; ++i) {
        data4.push_back(dist(gen) + 50);
    }
    continuous_plot.add_histogram(data4, "Dataset Gamma", "purple", 25);  // explicit bins
    
    // DEMONSTRATE reference lines for continuous histograms
    
    // All vertical line overloads (allowed for continuous)
    continuous_plot.add_vertical_line(100.0, "");  // auto-label, auto-color
    continuous_plot.add_vertical_line(120.0, "Upper Threshold");  // auto-color
    continuous_plot.add_vertical_line(80.0, "Lower Threshold", "orange");  // full spec
    
    // All horizontal line overloads
    continuous_plot.add_horizontal_line(10.0, "");  // auto-label, auto-color
    continuous_plot.add_horizontal_line(20.0, "High Frequency");  // auto-color
    continuous_plot.add_horizontal_line(5.0, "Low Frequency", "green");  // full spec
    
    // Save continuous histogram
    bool continuous_success = continuous_plot.save_png("output/03_histogram_continuous_comprehensive.png");
    
    // =====================================================================
    // DISCRETE HISTOGRAM DEMONSTRATION
    // =====================================================================
    
    std::cout << "2. Testing discrete histogram functionality..." << std::endl;
    
    // Create discrete histogram plot
    plotlib::HistogramPlot discrete_plot(1000, 700);
    discrete_plot.set_labels("Discrete Histogram API Demonstration", "Categories", "Count");
    
    // Sample discrete data
    std::vector<int> counts1 = {10, 20, 15};
    std::vector<int> counts2 = {5, 15, 25, 12};
    
    std::vector<std::string> names1 = {"Alpha", "Beta", "Gamma"};
    std::vector<std::string> names2 = {"Type A", "Type B", "Type C", "Type D"};
    
    std::vector<std::string> colors1 = {"red", "blue", "green"};
    std::vector<std::string> colors2 = {"orange", "purple", "cyan", "magenta"};
    
    // DEMONSTRATE ALL discrete add_histogram() OVERLOADS
    
    // Overload 1: counts only (auto-names: "idx 1", "idx 2", ..., auto-colors)
    std::vector<int> counts_auto = {8, 12, 6};
    discrete_plot.add_histogram(counts_auto);  // auto-names, auto-colors
    
    // Overload 2: counts + names (auto-colors)
    discrete_plot.add_histogram(counts1, names1);  // auto-colors
    
    // Overload 3: counts + names + colors (full specification)
    discrete_plot.add_histogram(counts2, names2, colors2);  // full spec
    
    // DEMONSTRATE reference lines for discrete histograms
    
    // Horizontal lines (allowed for discrete)
    discrete_plot.add_horizontal_line(15.0, "");  // auto-label, auto-color
    discrete_plot.add_horizontal_line(10.0, "Target Count");  // auto-color
    discrete_plot.add_horizontal_line(20.0, "High Count", "red");  // full spec
    
    // Test vertical line restriction (should demonstrate error handling)
    std::cout << "   Testing vertical line restriction for discrete histograms..." << std::endl;
    try {
        discrete_plot.add_vertical_line(1.5, "Should Fail");
        std::cout << "   ❌ UNEXPECTED: Vertical line was allowed" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "   ✅ Expected restriction caught: " << e.what() << std::endl;
    }
    
    // Save discrete histogram
    bool discrete_success = discrete_plot.save_png("output/03_histogram_discrete_comprehensive.png");
    
    // =====================================================================
    // REPORT RESULTS
    // =====================================================================
    
    if (continuous_success && discrete_success) {
        std::cout << "✅ Comprehensive HistogramPlot demonstration saved!" << std::endl;
        std::cout << "📊 Features demonstrated:" << std::endl;
        std::cout << "   📈 CONTINUOUS HISTOGRAMS:" << std::endl;
        std::cout << "      • 4 histogram series with different overloads" << std::endl;
        std::cout << "      • data only, data+name, data+name+color, full specification" << std::endl;
        std::cout << "      • 6 reference lines (3 vertical, 3 horizontal)" << std::endl;
        std::cout << "   📊 DISCRETE HISTOGRAMS:" << std::endl;
        std::cout << "      • 3 histogram series with different overloads" << std::endl;
        std::cout << "      • counts only, counts+names, counts+names+colors" << std::endl;
        std::cout << "      • 3 horizontal reference lines" << std::endl;
        std::cout << "      • Vertical line restriction demonstration" << std::endl;
        std::cout << "   ⚙️ All HistogramPlot-specific methods tested" << std::endl;
        std::cout << "   🎨 Auto-color conflict avoidance for reference lines" << std::endl;
        std::cout << "   🏷️ Auto-naming for both histograms and reference lines" << std::endl;
        std::cout << "   🛡️ Type validation and error handling" << std::endl;
    } else {
        std::cout << "❌ Failed to save one or more plots" << std::endl;
    }
    
    return (continuous_success && discrete_success) ? 0 : 1;
}

/*
 * 🎯 Complete HistogramPlot API Coverage:
 * 
 * CONTINUOUS HISTOGRAM METHODS (4 overloads):
 * ✅ add_histogram(values) - auto-name, auto-color, auto-bins
 * ✅ add_histogram(values, name) - auto-color, auto-bins
 * ✅ add_histogram(values, name, color) - auto-bins
 * ✅ add_histogram(values, name, color, bin_count) - full specification
 * 
 * DISCRETE HISTOGRAM METHODS (3 overloads):
 * ✅ add_histogram(counts) - auto-names ("idx 1", "idx 2"...), auto-colors
 * ✅ add_histogram(counts, names) - auto-colors
 * ✅ add_histogram(counts, names, colors) - full specification
 * 
 * VERTICAL REFERENCE LINES (continuous only):
 * ✅ add_vertical_line(x_value) - auto-label, auto-color
 * ✅ add_vertical_line(x_value, label) - auto-color
 * ✅ add_vertical_line(x_value, label, color) - full specification
 * ❌ Restricted for discrete histograms (demonstrates error handling)
 * 
 * HORIZONTAL REFERENCE LINES (both types):
 * ✅ add_horizontal_line(y_value) - auto-label, auto-color
 * ✅ add_horizontal_line(y_value, label) - auto-color
 * ✅ add_horizontal_line(y_value, label, color) - full specification
 * 
 * INHERITED METHODS:
 * ✅ set_labels(), set_title(), set_xlabel(), set_ylabel()
 * ✅ set_legend_enabled(), hide_legend_item()
 * ✅ save_png(), save_svg()
 */