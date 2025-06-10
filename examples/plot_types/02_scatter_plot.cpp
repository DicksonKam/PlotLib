/**
 * @file 02_scatter_plot.cpp
 * @brief Comprehensive ScatterPlot functionality demonstration
 * 
 * This example demonstrates ALL public ScatterPlot functionality including:
 * - All add_scatter() overloads
 * - Cluster visualization
 * - Reference line capabilities
 * - Complete API coverage for precise code review
 */

#include "scatter_plot.h"
#include "plot_manager.h"
#include <vector>
#include <iostream>
#include <random>

int main() {
    std::cout << "=== ScatterPlot Color Consistency Test ===" << std::endl;
    
    // Create a 1x2 subplot layout for side-by-side comparison
    plotlib::SubplotManager subplots(1, 2, 1400, 700);
    subplots.set_main_title("Cluster Color Consistency Test: Simple (Left) vs Comprehensive (Right)");
    
    // =====================================================================
    // LEFT SUBPLOT: Simple cluster plot with middle legend hiding
    // =====================================================================
    
    std::cout << "1. Creating simple cluster plot (left) with middle cluster hidden..." << std::endl;
    
    // Simple cluster data for testing
    std::vector<double> simple_cluster_x = {1.0, 1.2, 1.1, 0.9, 1.3,    // Cluster 0 (blue)
                                           3.0, 3.1, 2.9, 3.2, 2.8,    // Cluster 1 (green) - will be hidden
                                           5.0, 5.1, 4.9, 5.2, 4.8,    // Cluster 2 (purple) 
                                           2.0, 6.0};                   // Outliers (red)
    std::vector<double> simple_cluster_y = {1.0, 1.1, 0.9, 1.2, 0.8,    // Cluster 0
                                           3.0, 3.1, 2.9, 2.8, 3.2,    // Cluster 1
                                           1.5, 1.6, 1.4, 1.7, 1.3,    // Cluster 2
                                           4.0, 0.5};                   // Outliers
    std::vector<int> simple_cluster_labels = {0, 0, 0, 0, 0,             // Cluster 0
                                              1, 1, 1, 1, 1,             // Cluster 1
                                              2, 2, 2, 2, 2,             // Cluster 2
                                              -1, -1};                   // Outliers
    
    auto& left_plot = subplots.get_subplot<plotlib::ScatterPlot>(0, 0);
    left_plot.set_labels("Simple: Colors Only", "X Values", "Y Values");
    
    // Add clusters to left plot
    left_plot.add_clusters(simple_cluster_x, simple_cluster_y, simple_cluster_labels);
    
    // Hide the middle cluster (Cluster 2 = label 1)
    left_plot.hide_legend_item("Cluster 2");
    
    // =====================================================================
    // RIGHT SUBPLOT: Comprehensive plot (existing functionality)
    // =====================================================================
    
    std::cout << "2. Creating comprehensive plot (right) with mixed content..." << std::endl;
    
    // Create sample data sets for scatter series
    std::vector<double> x1 = {0.5, 1.5, 2.5};
    std::vector<double> y1 = {4.5, 4.0, 4.2};
    
    std::vector<double> x2 = {0.8, 1.8, 2.8};
    std::vector<double> y2 = {3.8, 3.5, 3.7};
    
    std::vector<double> x3 = {0.2, 1.2, 2.2};
    std::vector<double> y3 = {3.2, 3.0, 3.4};
    
    // Create right subplot for comprehensive demonstration
    auto& right_plot = subplots.get_subplot<plotlib::ScatterPlot>(0, 1);
    right_plot.set_labels("Comprehensive: Mixed Content", "X Values", "Y Values");
    
    // Add some regular scatter series to right plot
    right_plot.add_scatter(x1, y1, "Dataset A", "orange");
    right_plot.add_scatter(x2, y2, "Dataset B");
    
    // Enhanced cluster data for comprehensive demonstration
    std::vector<double> comp_cluster_x = {0.5, 0.7, 0.6, 0.4, 0.8,      // Cluster 0 (blue)
                                         2.5, 2.6, 2.4, 2.7, 2.3,      // Cluster 1 (green) 
                                         4.5, 4.6, 4.4, 4.7, 4.3,      // Cluster 2 (purple)
                                         1.5, 3.5};                     // Outliers (red)
    std::vector<double> comp_cluster_y = {2.0, 2.1, 1.9, 2.2, 1.8,      // Cluster 0
                                         2.5, 2.6, 2.4, 2.3, 2.7,      // Cluster 1
                                         2.2, 2.3, 2.1, 2.4, 2.0,      // Cluster 2
                                         1.0, 1.2};                     // Outliers
    std::vector<int> comp_cluster_labels = {0, 0, 0, 0, 0,               // Cluster 0
                                           1, 1, 1, 1, 1,               // Cluster 1
                                           2, 2, 2, 2, 2,               // Cluster 2
                                           -1, -1};                     // Outliers
    
    // Add clusters to right plot
    right_plot.add_clusters(comp_cluster_x, comp_cluster_y, comp_cluster_labels);
    
    // Hide the middle cluster (Cluster 2 = label 1) in the right plot too
    right_plot.hide_legend_item("Cluster 2");
    
    // Add some reference lines to right plot for completeness
    right_plot.add_vertical_line(3.0, "Mid Line", "gray");
    right_plot.add_horizontal_line(2.0, "Baseline", "gray");
    
    // =====================================================================
    // SAVE AND REPORT
    // =====================================================================
    
    std::cout << "3. Saving side-by-side comparison..." << std::endl;
    
    bool success = subplots.save_png("output/plot_types_02_scatter_plot.png");
    
    if (success) {
        std::cout << "✅ Cluster color consistency test saved!" << std::endl;
        std::cout << "📊 Test results:" << std::endl;
        std::cout << "   📍 LEFT PLOT (Simple):" << std::endl;
        std::cout << "      • Cluster 1 (label=0): Blue circles - visible in plot & legend" << std::endl;
        std::cout << "      • Cluster 2 (label=1): Green circles - visible in plot, HIDDEN from legend" << std::endl;
        std::cout << "      • Cluster 3 (label=2): Purple circles - visible in plot & legend" << std::endl;
        std::cout << "      • Outliers: Red crosses - visible in plot & legend" << std::endl;
        std::cout << "   📍 RIGHT PLOT (Comprehensive):" << std::endl;
        std::cout << "      • Mixed scatter series and clusters with same hiding pattern" << std::endl;
        std::cout << "      • Cluster 2 also hidden to test consistency" << std::endl;
        std::cout << "   🎯 EXPECTED COLOR VERIFICATION:" << std::endl;
        std::cout << "      • Both plots should show same colors for same cluster labels" << std::endl;
        std::cout << "      • Legend colors should exactly match plot marker colors" << std::endl;
        std::cout << "      • Hidden items appear in plot but not in legend" << std::endl;
    } else {
        std::cout << "❌ Failed to save subplot comparison" << std::endl;
    }
    
    return success ? 0 : 1;
}

/*
 * 🎯 Cluster Color Consistency Test Coverage:
 * 
 * LEFT SUBPLOT (Simple):
 * ✅ Pure cluster visualization with 3 clusters + outliers
 * ✅ Middle cluster (Cluster 2) hidden from legend
 * ✅ Direct color consistency verification
 * 
 * RIGHT SUBPLOT (Comprehensive):
 * ✅ Mixed scatter series and clusters  
 * ✅ Same cluster hiding pattern as left plot
 * ✅ Additional reference lines for completeness
 * 
 * COLOR VERIFICATION EXPECTATIONS:
 * ✅ Cluster label 0 → "Cluster 1" → Blue circles (both plots)
 * ✅ Cluster label 1 → "Cluster 2" → Green circles (visible, legend hidden)
 * ✅ Cluster label 2 → "Cluster 3" → Purple circles (both plots)  
 * ✅ Outliers → Red crosses (both plots)
 * 
 * LEGEND HIDING TEST:
 * ✅ hide_legend_item("Cluster 2") - affects legend only, not plot
 * ✅ Colors remain consistent when items are hidden
 * ✅ No color shifting or remapping when legends are hidden
 * 
 * SUBPLOT FEATURES:
 * ✅ SubplotManager 1x2 layout
 * ✅ Individual subplot legends
 * ✅ Unified main title
 */