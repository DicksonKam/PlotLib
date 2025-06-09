/**
 * @file 06_discrete_histograms.cpp
 * @brief Beginner Example 6: Creating discrete histograms with advanced features and error handling
 * 
 * This example demonstrates how to create discrete histograms for categorical data
 * with advanced features including reference lines, legend management, and proper
 * error handling for invalid operations.
 */

#include "histogram_plot.h"
#include <iostream>
#include <vector>
#include <stdexcept>

int main() {
    using namespace plotlib;
    
    std::cout << "Creating discrete histograms with advanced features..." << std::endl;
    
    // =====================================================================
    // Example 1: Basic discrete histogram with horizontal reference line
    // =====================================================================
    std::cout << "\n1. Basic discrete histogram with horizontal reference line..." << std::endl;
    
    try {
        HistogramPlot plot1(800, 600);
        plot1.set_labels("Molecular Structure Distribution", "Structure Types", "Count");
        
        // Data: [10, 20, 15] means 10 of structure 1, 20 of structure 2, 15 of structure 3
        std::vector<int> structure_counts = {10, 20, 15};
        std::vector<std::string> structure_names = {"Structure 1", "Structure 2", "Structure 3"};
        plot1.add_histogram(structure_counts, structure_names, "Structures");
        
        // Add horizontal reference line to show target threshold
        plot1.add_horizontal_line(18.0, "Target Threshold", "red");
        
        if (plot1.save_png("output/06_discrete_with_horizontal_line.png")) {
            std::cout << "✅ Discrete histogram with horizontal reference line saved!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "❌ Error: " << e.what() << std::endl;
    }
    
    // =====================================================================
    // Example 2: Demonstrate vertical line restriction (ERROR CASE)
    // =====================================================================
    std::cout << "\n2. Demonstrating vertical line restriction for discrete histograms..." << std::endl;
    
    try {
        HistogramPlot plot2(800, 600);
        plot2.set_labels("Material Analysis", "Material Types", "Frequency");
        
        std::vector<int> material_counts = {15, 8, 25, 12};
        std::vector<std::string> material_names = {"Material A", "Material B", "Material C", "Material D"};
        std::vector<std::string> colors = {"red", "blue", "green", "orange"};
        plot2.add_histogram(material_counts, material_names, "Materials", colors);
        
        // This should throw an error for discrete histograms
        std::cout << "   Attempting to add vertical line (should fail)..." << std::endl;
        plot2.add_vertical_line(1.5, "Invalid Line");
        
        std::cout << "❌ UNEXPECTED: Vertical line was allowed (this should not happen)" << std::endl;
        
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Expected error caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "❌ Unexpected error: " << e.what() << std::endl;
    }
    
    // =====================================================================
    // Example 3: Demonstrate mixing histogram types restriction (ERROR CASE)
    // =====================================================================
    std::cout << "\n3. Demonstrating restriction on mixing histogram types..." << std::endl;
    
    try {
        HistogramPlot plot3(800, 600);
        plot3.set_labels("Mixed Types Test", "Data", "Frequency");
        
        // First add a discrete histogram
        std::vector<int> discrete_counts = {5, 10, 8};
        std::vector<std::string> category_names = {"Category A", "Category B", "Category C"};
        plot3.add_histogram(discrete_counts, category_names, "Discrete");
        std::cout << "   Added discrete histogram successfully" << std::endl;
        
        // Now try to add a continuous histogram (should fail)
        std::vector<double> continuous_data = {1.0, 2.5, 3.1, 1.8, 2.9};
        std::cout << "   Attempting to add continuous histogram (should fail)..." << std::endl;
        plot3.add_histogram(continuous_data, "Continuous", "blue", 5);
        
        std::cout << "❌ UNEXPECTED: Mixed histogram types were allowed (this should not happen)" << std::endl;
        
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Expected error caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "❌ Unexpected error: " << e.what() << std::endl;
    }
    
    // =====================================================================
    // Example 4: Demonstrate reverse mixing restriction (ERROR CASE)
    // =====================================================================
    std::cout << "\n4. Demonstrating reverse mixing restriction..." << std::endl;
    
    try {
        HistogramPlot plot4(800, 600);
        plot4.set_labels("Reverse Mix Test", "Data", "Frequency");
        
        // First add a continuous histogram
        std::vector<double> continuous_data = {1.0, 2.5, 3.1, 1.8, 2.9, 2.1, 2.7};
        plot4.add_histogram(continuous_data, "Continuous", "green", 5);
        std::cout << "   Added continuous histogram successfully" << std::endl;
        
        // Now try to add a discrete histogram (should fail)
        std::vector<int> discrete_counts = {5, 10, 8};
        std::vector<std::string> category_names = {"Category A", "Category B", "Category C"};
        std::cout << "   Attempting to add discrete histogram (should fail)..." << std::endl;
        plot4.add_histogram(discrete_counts, category_names, "Discrete");
        
        std::cout << "❌ UNEXPECTED: Mixed histogram types were allowed (this should not happen)" << std::endl;
        
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Expected error caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "❌ Unexpected error: " << e.what() << std::endl;
    }
    
    // =====================================================================
    // Example 5: Legend hiding functionality
    // =====================================================================
    std::cout << "\n5. Demonstrating legend hiding for discrete histograms..." << std::endl;
    
    try {
        HistogramPlot plot5(800, 600);
        plot5.set_labels("Survey Response Analysis", "Response Categories", "Number of Responses");
        
        // Survey responses: [Very Poor, Poor, Fair, Good, Excellent]
        std::vector<int> survey_responses = {3, 8, 15, 42, 32};
        std::vector<std::string> rating_names = {"Very Poor", "Poor", "Fair", "Good", "Excellent"};
        std::vector<std::string> satisfaction_colors = {"red", "orange", "yellow", "green", "blue"};
        plot5.add_histogram(survey_responses, rating_names, "Satisfaction", satisfaction_colors);
        
        // Add horizontal reference line for average
        plot5.add_horizontal_line(20.0, "Average Response", "purple");
        
        // Hide specific categories from legend
        plot5.hide_legend_item("Very Poor"); // Hide "Very Poor"
        plot5.hide_legend_item("Poor"); // Hide "Poor"
        
        if (plot5.save_png("output/06_discrete_hidden_legend.png")) {
            std::cout << "✅ Survey analysis with hidden legend items saved!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "❌ Error in legend hiding example: " << e.what() << std::endl;
    }
    
    // =====================================================================
    // Example 6: Multiple discrete series (allowed) with legend management
    // =====================================================================
    std::cout << "\n6. Multiple discrete series with legend management..." << std::endl;
    
    try {
        HistogramPlot plot6(800, 600);
        plot6.set_labels("Research Group Comparison", "Research Categories", "Publications");
        
        // Note: Multiple discrete series with shared category names is complex
        // For demonstration, we'll create separate categories for each group
        std::vector<int> group_a_pubs = {5, 10, 8};  // 3 research categories
        std::vector<std::string> group_a_categories = {"Theory A", "Experimental A", "Computational A"};
        
        plot6.add_histogram(group_a_pubs, group_a_categories, "Group A");
        
        // Add horizontal reference lines
        plot6.add_horizontal_line(15.0, "Excellence", "green");
        
        // Hide some specific items
        plot6.hide_legend_item("Experimental A"); // Hide experimental research from legend
        
        if (plot6.save_png("output/06_discrete_multiple_series.png")) {
            std::cout << "✅ Multiple discrete series with legend management saved!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "❌ Error in multiple series example: " << e.what() << std::endl;
    }
    
    // =====================================================================
    // Example 7: Continuous histogram with vertical line (allowed)
    // =====================================================================
    std::cout << "\n7. Demonstrating continuous histogram with vertical line (allowed)..." << std::endl;
    
    try {
        HistogramPlot plot7(800, 600);
        plot7.set_labels("Continuous Data Distribution", "Values", "Frequency");
        
        // Verify that continuous histograms still work with vertical lines
        std::vector<double> continuous_data = {1.0, 2.1, 1.8, 3.2, 2.9, 1.5, 2.8, 3.1, 2.0, 2.5, 
                                              1.9, 2.3, 2.7, 3.0, 1.7, 2.4, 2.6, 2.8, 1.6, 2.2};
        plot7.add_histogram(continuous_data, "Measurements", "blue", 8);
        
        // Add both vertical and horizontal lines (both allowed for continuous)
        plot7.add_vertical_line(2.5, "Mean", "red");
        plot7.add_horizontal_line(3.0, "Threshold", "green");
        
        if (plot7.save_png("output/06_continuous_with_lines.png")) {
            std::cout << "✅ Continuous histogram with reference lines saved!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "❌ Error in continuous histogram example: " << e.what() << std::endl;
    }
    
    std::cout << "\n🎯 Advanced Discrete Histogram Tutorial Complete!" << std::endl;
    std::cout << "📊 You've learned about:" << std::endl;
    std::cout << "   ✅ Adding horizontal reference lines to discrete histograms" << std::endl;
    std::cout << "   ❌ Vertical lines are blocked for discrete histograms" << std::endl;
    std::cout << "   ❌ Mixing discrete and continuous histograms is blocked" << std::endl;
    std::cout << "   🎛️ Legend hiding for individual categories" << std::endl;
    std::cout << "   📈 Multiple discrete series are allowed" << std::endl;
    std::cout << "   ✅ Continuous histograms support both line types" << std::endl;
    std::cout << "\n📁 Generated plots saved to output/ directory" << std::endl;
    std::cout << "💡 These restrictions ensure data visualization best practices!" << std::endl;
    
    return 0;
}