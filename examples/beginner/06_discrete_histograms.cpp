/**
 * @file 06_discrete_histograms.cpp
 * @brief Beginner Example 6: Creating discrete histograms for categorical data
 * 
 * This example demonstrates how to create discrete histograms for categorical data
 * such as counting different types of structures, materials, or classifications.
 * Unlike continuous histograms that bin numeric data, discrete histograms display
 * exact counts for predefined categories.
 */

#include "histogram_plot.h"
#include <iostream>
#include <vector>

int main() {
    using namespace plotlib;
    
    std::cout << "Creating discrete histograms..." << std::endl;
    
    // =====================================================================
    // Example 1: Basic discrete histogram with automatic colors
    // =====================================================================
    std::cout << "1. Basic discrete histogram with automatic colors..." << std::endl;
    
    HistogramPlot plot1(800, 600);
    plot1.set_labels("Molecular Structure Distribution", "Structure Types", "Count");
    
    // Data: [10, 20] means 10 of structure 1, 20 of structure 2
    std::vector<int> structure_counts = {10, 20};
    plot1.add_histogram("Structures", structure_counts, "structure");
    
    if (plot1.save_png("output/06_discrete_basic.png")) {
        std::cout << "✅ Basic discrete histogram saved!" << std::endl;
    } else {
        std::cout << "❌ Failed to save basic discrete histogram" << std::endl;
    }
    
    // =====================================================================
    // Example 2: Discrete histogram with custom colors
    // =====================================================================
    std::cout << "2. Discrete histogram with custom colors..." << std::endl;
    
    HistogramPlot plot2(800, 600);
    plot2.set_labels("Material Type Analysis", "Material Categories", "Frequency");
    
    // Data: counts for 4 different material types
    std::vector<int> material_counts = {15, 8, 25, 12};
    std::vector<std::string> colors = {"red", "blue", "green", "orange"};
    plot2.add_histogram("Materials", material_counts, "material", colors);
    
    if (plot2.save_png("output/06_discrete_custom_colors.png")) {
        std::cout << "✅ Custom colored discrete histogram saved!" << std::endl;
    } else {
        std::cout << "❌ Failed to save custom colored discrete histogram" << std::endl;
    }
    
    // =====================================================================
    // Example 3: Multiple discrete series comparison
    // =====================================================================
    std::cout << "3. Comparing multiple discrete datasets..." << std::endl;
    
    HistogramPlot plot3(800, 600);
    plot3.set_labels("Research Group Comparison", "Research Categories", "Publications");
    
    // Compare publication counts across categories for two groups
    std::vector<int> group_a_pubs = {5, 10, 8};  // 3 research categories
    std::vector<int> group_b_pubs = {12, 6, 15}; // same 3 research categories
    
    plot3.add_histogram("Group A", group_a_pubs, "category");
    plot3.add_histogram("Group B", group_b_pubs, "area", {"cyan", "magenta", "yellow"});
    
    if (plot3.save_png("output/06_discrete_comparison.png")) {
        std::cout << "✅ Multiple discrete series comparison saved!" << std::endl;
    } else {
        std::cout << "❌ Failed to save discrete series comparison" << std::endl;
    }
    
    // =====================================================================
    // Example 4: Practical application - Survey results
    // =====================================================================
    std::cout << "4. Practical example: Survey response analysis..." << std::endl;
    
    HistogramPlot plot4(800, 600);
    plot4.set_labels("Customer Satisfaction Survey", "Response Categories", "Number of Responses");
    
    // Survey responses: [Very Poor, Poor, Fair, Good, Excellent]
    std::vector<int> survey_responses = {3, 8, 15, 42, 32};
    std::vector<std::string> satisfaction_colors = {"red", "orange", "yellow", "green", "blue"};
    plot4.add_histogram("Satisfaction", survey_responses, "rating", satisfaction_colors);
    
    if (plot4.save_png("output/06_discrete_survey.png")) {
        std::cout << "✅ Survey analysis histogram saved!" << std::endl;
    } else {
        std::cout << "❌ Failed to save survey analysis histogram" << std::endl;
    }
    
    // =====================================================================
    // Example 5: Mixed with continuous histogram (compatibility test)
    // =====================================================================
    std::cout << "5. Verifying continuous histogram compatibility..." << std::endl;
    
    HistogramPlot plot5(800, 600);
    plot5.set_labels("Continuous Data Distribution", "Values", "Frequency");
    
    // Verify that continuous histograms still work perfectly
    std::vector<double> continuous_data = {1.0, 2.1, 1.8, 3.2, 2.9, 1.5, 2.8, 3.1, 2.0, 2.5, 
                                          1.9, 2.3, 2.7, 3.0, 1.7, 2.4, 2.6, 2.8, 1.6, 2.2};
    plot5.add_histogram("Measurements", continuous_data, "blue", 8);
    
    if (plot5.save_png("output/06_continuous_compatibility.png")) {
        std::cout << "✅ Continuous histogram compatibility verified!" << std::endl;
    } else {
        std::cout << "❌ Failed to save continuous histogram compatibility test" << std::endl;
    }
    
    std::cout << "\n🎯 Discrete Histogram Tutorial Complete!" << std::endl;
    std::cout << "📊 You've learned how to:" << std::endl;
    std::cout << "   • Create basic discrete histograms for categorical data" << std::endl;
    std::cout << "   • Customize colors for individual categories" << std::endl;
    std::cout << "   • Compare multiple discrete datasets" << std::endl;
    std::cout << "   • Apply discrete histograms to real-world data (surveys)" << std::endl;
    std::cout << "   • Maintain compatibility with continuous histograms" << std::endl;
    std::cout << "\n📁 Generated plots saved to output/ directory" << std::endl;
    std::cout << "💡 Try modifying the counts and categories to explore more!" << std::endl;
    
    return 0;
}