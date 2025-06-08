#include "scatter_plot.h"
#include <vector>
#include <iostream>
#include <filesystem>

int main() {
    std::cout << "Testing subplot scaling and positioning..." << std::endl;
    
    // Create a simple 2x2 layout to test scaling
    SubplotManager test_subplots(2, 2, 1000, 800, 0.1);
    test_subplots.set_main_title("Scaling Test - Each Plot Should Look Identical");
    
    // Create identical data for all subplots to test scaling consistency
    std::vector<Point2D> test_data;
    for (int i = 0; i < 20; ++i) {
        double x = i * 0.5;
        double y = x;  // Simple diagonal line
        test_data.emplace_back(x, y);
    }
    
    PlotStyle test_style;
    test_style.r = 0.8; test_style.g = 0.2; test_style.b = 0.2;
    test_style.point_size = 4.0;
    test_style.alpha = 0.8;
    
    // Add identical data to all 4 subplots
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto& plot = test_subplots.get_subplot(i, j);
            plot.set_labels(
                "Plot (" + std::to_string(i) + "," + std::to_string(j) + ")", 
                "X Axis", 
                "Y Axis"
            );
            plot.add_series("Test Line", test_data, test_style);
        }
    }
    
    // Create output directory if it doesn't exist
    std::filesystem::create_directories("output");
    
    // Save the test
    if (test_subplots.save_png("output/scaling_test.png")) {
        std::cout << "✅ Scaling test saved to output/scaling_test.png" << std::endl;
        std::cout << "All 4 subplots should have identical appearance and proper centering." << std::endl;
    } else {
        std::cout << "❌ Failed to save scaling test" << std::endl;
    }
    
    // Test different aspect ratios
    std::cout << "\nTesting different aspect ratios..." << std::endl;
    
    // Wide layout (1x3)
    SubplotManager wide_test(1, 3, 1500, 500, 0.05);
    wide_test.set_main_title("Wide Layout Test (1x3)");
    
    for (int j = 0; j < 3; ++j) {
        auto& plot = wide_test.get_subplot(0, j);
        plot.set_labels("Wide " + std::to_string(j), "X", "Y");
        plot.add_series("Data", test_data, test_style);
    }
    
    wide_test.save_png("output/wide_test.png");
    std::cout << "✅ Wide layout test saved to output/wide_test.png" << std::endl;
    
    // Tall layout (3x1)
    SubplotManager tall_test(3, 1, 500, 1200, 0.05);
    tall_test.set_main_title("Tall Layout Test (3x1)");
    
    for (int i = 0; i < 3; ++i) {
        auto& plot = tall_test.get_subplot(i, 0);
        plot.set_labels("Tall " + std::to_string(i), "X", "Y");
        plot.add_series("Data", test_data, test_style);
    }
    
    tall_test.save_png("output/tall_test.png");
    std::cout << "✅ Tall layout test saved to output/tall_test.png" << std::endl;
    
    std::cout << "\nScaling tests completed. Check the output files to verify:" << std::endl;
    std::cout << "1. All subplots have consistent appearance" << std::endl;
    std::cout << "2. Plots are properly centered in their allocated space" << std::endl;
    std::cout << "3. Aspect ratios are preserved" << std::endl;
    std::cout << "4. No overlapping or misalignment" << std::endl;
    
    return 0;
} 