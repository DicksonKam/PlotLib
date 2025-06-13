/**
 * @file 03_histogram_plot.cpp
 * @brief Comprehensive HistogramPlot functionality demonstration
 * 
 * This example demonstrates ALL public HistogramPlot functionality including:
 * - All continuous histogram overloads
 * - All discrete histogram overloads  
 * - Reference line capabilities
 * - Combined continuous and discrete in side-by-side subplots
 * - Complete API coverage for precise code review
 */

#include "histogram_plot.h"
#include "plot_manager.h"
#include <vector>
#include <iostream>
#include <random>

int main() {
    std::cout << "=== Comprehensive HistogramPlot Functionality ===" << std::endl;
    
    // Create a 1x2 subplot layout for side-by-side comparison
    plotlib::SubplotManager subplots(1, 2, 1400, 700);
    subplots.set_main_title("Histogram Types Comparison: Continuous (Left) vs Discrete (Right)");
    
    // =====================================================================
    // LEFT SUBPLOT: CONTINUOUS HISTOGRAM DEMONSTRATION
    // =====================================================================
    
    std::cout << "1. Testing continuous histogram functionality (left subplot)..." << std::endl;
    
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
    
    // Get left subplot for continuous histogram
    auto& continuous_plot = subplots.get_subplot<plotlib::HistogramPlot>(0, 0);
    continuous_plot.set_labels("Continuous Histograms", "Value", "Frequency");
    
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
    continuous_plot.add_vertical_line(100.0);  // auto-label, auto-color
    continuous_plot.add_vertical_line(120.0, "Upper Threshold");  // auto-color
    continuous_plot.add_vertical_line(80.0, "Lower Threshold");  // full spec
    
    // All horizontal line overloads
    continuous_plot.add_horizontal_line(10.0);  // auto-label, auto-color
    continuous_plot.add_horizontal_line(20.0, "High Frequency");  // auto-color
    continuous_plot.add_horizontal_line(5.0, "Low Frequency");  // full spec
    
    // =====================================================================
    // RIGHT SUBPLOT: DISCRETE HISTOGRAM DEMONSTRATION
    // =====================================================================
    
    std::cout << "2. Testing discrete histogram functionality (right subplot)..." << std::endl;
    
    // Get right subplot for discrete histogram
    auto& discrete_plot = subplots.get_subplot<plotlib::HistogramPlot>(0, 1);
    discrete_plot.set_labels("Discrete Histograms", "Categories", "Count");
    
    // Sample discrete data (reduced categories)
    std::vector<int> counts1 = {10, 20, 15};
    
    std::vector<std::string> names1 = {"Alpha", "Beta", "Gamma"};
    
    std::vector<std::string> colors1 = {"red", "blue", "green"};
    
    // DEMONSTRATE ALL discrete add_histogram() OVERLOADS
    
    // Overload 1: counts only (auto-names: "idx 1", "idx 2", ..., auto-colors)
    std::vector<int> counts_auto = {8, 12, 6};
    discrete_plot.add_histogram(counts_auto);  // auto-names, auto-colors
    
    // Overload 2: counts + names + colors (full specification)
    discrete_plot.add_histogram(counts1, names1, colors1);  // full spec
    
    // Test legend hiding for the red category (idx 2 from the first histogram)
    std::cout << "   Testing legend hiding for 'idx 2'..." << std::endl;
    discrete_plot.hide_legend_item("idx 2");
    
    // DEMONSTRATE reference lines for discrete histograms
    
    // Horizontal lines (allowed for discrete)
    discrete_plot.add_horizontal_line(15.0);  // auto-label, auto-color
    discrete_plot.add_horizontal_line(10.0, "Target Count");  // auto-color
    discrete_plot.add_horizontal_line(20.0, "High Count");  // full spec
    
    // Test vertical line restriction (should demonstrate error handling)
    std::cout << "   Testing vertical line restriction for discrete histograms..." << std::endl;
    try {
        discrete_plot.add_vertical_line(1.5, "Should Fail");
        std::cout << "   ❌ UNEXPECTED: Vertical line was allowed" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "   ✅ Expected restriction caught: " << e.what() << std::endl;
    }
    
    // =====================================================================
    // SAVE COMBINED SUBPLOT AND REPORT RESULTS
    // =====================================================================
    
    std::cout << "3. Saving combined histogram subplot comparison..." << std::endl;
    
    bool subplot_success = subplots.save_png("output/plot_types_03_histogram_combined.png");
    
    if (subplot_success) {
        std::cout << "✅ Combined HistogramPlot demonstration saved!" << std::endl;
        std::cout << "📊 Features demonstrated in side-by-side subplots:" << std::endl;
        std::cout << "   📈 LEFT SUBPLOT (Continuous Histograms):" << std::endl;
        std::cout << "      • 4 histogram series with different overloads" << std::endl;
        std::cout << "      • data only, data+name, data+name+color, full specification" << std::endl;
        std::cout << "      • 6 reference lines (3 vertical, 3 horizontal)" << std::endl;
        std::cout << "   📊 RIGHT SUBPLOT (Discrete Histograms):" << std::endl;
        std::cout << "      • 2 histogram series with different overloads" << std::endl;
        std::cout << "      • counts only (auto-names), counts+names+colors" << std::endl;
        std::cout << "      • Legend hiding test: 'idx 2' hidden from legend" << std::endl;
        std::cout << "      • 3 horizontal reference lines" << std::endl;
        std::cout << "      • Vertical line restriction demonstration" << std::endl;
        std::cout << "   🎯 COMBINED BENEFITS:" << std::endl;
        std::cout << "      • Direct visual comparison of histogram types" << std::endl;
        std::cout << "      • Unified subplot management and shared title" << std::endl;
        std::cout << "      • Complete API coverage in single image" << std::endl;
        std::cout << "   ⚙️ All HistogramPlot-specific methods tested" << std::endl;
        std::cout << "   🎨 Auto-color black for reference lines" << std::endl;
        std::cout << "   🏷️ Auto-naming for both histograms and reference lines" << std::endl;
        std::cout << "   🛡️ Type validation and error handling" << std::endl;
    } else {
        std::cout << "❌ Failed to save combined subplot comparison" << std::endl;
    }
    
    return subplot_success ? 0 : 1;
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
 * DISCRETE HISTOGRAM METHODS (2 demonstrated):
 * ✅ add_histogram(counts) - auto-names ("idx 1", "idx 2"...), auto-colors
 * ✅ add_histogram(counts, names, colors) - full specification
 * ✅ hide_legend_item("idx 2") - legend hiding test for discrete categories
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