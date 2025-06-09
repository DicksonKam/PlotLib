/**
 * @file 04_first_histogram.cpp
 * @brief Your first histogram - perfect for understanding data distributions
 * 
 * This example shows how to create histograms, which are great for:
 * - Understanding how your data is distributed
 * - Finding patterns in large datasets
 * - Comparing different groups of data
 */

#include "histogram_plot.h"
#include <vector>
#include <iostream>
#include <random>

int main() {
    std::cout << "Creating your first histogram..." << std::endl;
    
    // Example 1: Simple test scores histogram
    std::vector<double> test_scores = {
        85, 92, 78, 88, 95, 82, 90, 87, 93, 79,
        86, 91, 84, 89, 96, 83, 88, 85, 92, 87,
        90, 94, 81, 88, 93, 86, 89, 91, 85, 88
    };
    
    plotlib::HistogramPlot plot(800, 600);
    plot.set_labels("Test Scores Distribution", "Score", "Number of Students");
    
    // Add histogram with automatic bin count and custom color
    plot.add_histogram(test_scores, "Test Scores", "blue");
    
    bool success = plot.save_png("output/04_test_scores.png");
    
    if (success) {
        std::cout << "✅ Test scores histogram saved!" << std::endl;
        std::cout << "📊 You can see how the scores are distributed!" << std::endl;
    }
    
    // Example 2: Controlling the number of bins
    std::cout << "Creating histograms with different bin counts..." << std::endl;
    
    // Generate some random data
    std::random_device rd;
    std::mt19937 gen(42);  // Fixed seed for reproducible results
    std::normal_distribution<> normal_dist(100, 15);  // Mean=100, StdDev=15
    
    std::vector<double> iq_scores;
    for (int i = 0; i < 1000; ++i) {
        iq_scores.push_back(normal_dist(gen));
    }
    
    // Create histogram with 10 bins
    plotlib::HistogramPlot hist_10(800, 600);
    hist_10.set_labels("IQ Scores (10 bins)", "IQ Score", "Frequency");
    hist_10.add_histogram(iq_scores, "IQ Scores", "green", 10);
    hist_10.save_png("output/04_iq_10_bins.png");
    
    // Create histogram with 30 bins
    plotlib::HistogramPlot hist_30(800, 600);
    hist_30.set_labels("IQ Scores (30 bins)", "IQ Score", "Frequency");
    hist_30.add_histogram(iq_scores, "IQ Scores", "red", 30);
    hist_30.save_png("output/04_iq_30_bins.png");
    
    std::cout << "✅ Different bin count histograms saved!" << std::endl;
    std::cout << "🔍 Compare how different bin counts show different levels of detail!" << std::endl;
    
    // Example 3: Comparing two groups
    std::cout << "Creating a comparison histogram..." << std::endl;
    
    // Generate data for two different groups
    std::normal_distribution<> group_a(75, 10);   // Group A: mean=75, std=10
    std::normal_distribution<> group_b(85, 8);    // Group B: mean=85, std=8
    
    std::vector<double> group_a_scores;
    std::vector<double> group_b_scores;
    
    for (int i = 0; i < 200; ++i) {
        group_a_scores.push_back(group_a(gen));
        group_b_scores.push_back(group_b(gen));
    }
    
    plotlib::HistogramPlot comparison(800, 600);
    comparison.set_labels("Group Comparison", "Score", "Frequency");
    
    // Add both groups with different colors
    comparison.add_histogram(group_a_scores, "Group A", "blue", 20);
    comparison.add_histogram(group_b_scores, "Group B", "orange", 20);
    
    bool comp_success = comparison.save_png("output/04_group_comparison.png");
    
    if (comp_success) {
        std::cout << "✅ Group comparison histogram saved!" << std::endl;
        std::cout << "👥 You can see how the two groups differ!" << std::endl;
    }
    
    // Example 4: Real-world example - website loading times
    std::cout << "Creating a real-world example..." << std::endl;
    
    std::vector<double> loading_times = {
        0.5, 0.8, 1.2, 0.9, 1.1, 0.7, 1.5, 0.6, 1.0, 0.8,
        1.3, 0.9, 1.1, 0.7, 1.4, 0.8, 1.0, 0.9, 1.2, 0.6,
        2.1, 1.8, 0.5, 1.0, 0.9, 1.3, 0.7, 1.1, 0.8, 1.5,
        0.9, 1.0, 0.8, 1.2, 0.7, 1.4, 0.6, 1.1, 0.9, 1.3
    };
    
    plotlib::HistogramPlot loading_plot(800, 600);
    loading_plot.set_labels("Website Loading Times", "Loading Time (seconds)", "Number of Requests");
    loading_plot.add_histogram(loading_times, "Loading Times", "purple", 15);
    
    bool loading_success = loading_plot.save_png("output/04_loading_times.png");
    
    if (loading_success) {
        std::cout << "✅ Loading times histogram saved!" << std::endl;
        std::cout << "⚡ Most requests load quickly, but some take longer!" << std::endl;
    }
    
    return 0;
}

/*
 * 🎯 What you learned:
 * - How to create histograms from data vectors
 * - How to control the number of bins (more bins = more detail)
 * - How to compare different groups using different colors
 * - Histograms show you the "shape" of your data
 * - Real-world applications like test scores and loading times
 * 
 * 🚀 Try this:
 * - Change the number of bins to see different levels of detail
 * - Try different colors for your histograms
 * - Create your own data and see its distribution
 * - Run example 05 to learn about subplots!
 * 
 * 💡 Tip: 
 * - Few bins (5-10): Good for seeing general patterns
 * - Many bins (20-50): Good for seeing detailed distribution
 * - Too many bins: Can make the histogram look noisy
 */ 