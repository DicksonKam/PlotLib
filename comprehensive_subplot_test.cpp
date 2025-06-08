#include "scatter_plot.h"
#include <vector>
#include <random>
#include <iostream>
#include <filesystem>
#include <cmath>

int main() {
    std::cout << "Comprehensive subplot stress test..." << std::endl;
    
    // Random number generators
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normal_dist(0.0, 1.0);
    std::uniform_real_distribution<> uniform_dist(-10.0, 10.0);
    std::exponential_distribution<> exp_dist(1.0);
    
    // Create output directory
    std::filesystem::create_directories("output");
    
    // Test 1: 1x4 layout with very different data ranges and types
    std::cout << "\n=== Test 1: 1x4 Layout with Varied Data Types ===" << std::endl;
    SubplotManager test_1x4(1, 4, 2000, 500, 0.05);
    test_1x4.set_main_title("1x4 Layout: Varied Data Types and Ranges");
    
    // Subplot 1: Very small values (micro scale)
    {
        auto& plot = test_1x4.get_subplot(0, 0);
        plot.set_labels("Micro Scale", "X (μm)", "Y (μm)");
        
        std::vector<Point2D> micro_data;
        for (int i = 0; i < 50; ++i) {
            double x = normal_dist(gen) * 0.001;  // Very small values
            double y = normal_dist(gen) * 0.001;
            micro_data.emplace_back(x, y);
        }
        
        PlotStyle micro_style;
        micro_style.r = 0.8; micro_style.g = 0.2; micro_style.b = 0.2;
        micro_style.point_size = 3.0;
        micro_style.alpha = 0.8;
        
        plot.add_series("Micro Data", micro_data, micro_style);
    }
    
    // Subplot 2: Large values (macro scale)
    {
        auto& plot = test_1x4.get_subplot(0, 1);
        plot.set_labels("Macro Scale", "X (km)", "Y (km)");
        
        std::vector<Point2D> macro_data;
        for (int i = 0; i < 40; ++i) {
            double x = uniform_dist(gen) * 1000;  // Very large values
            double y = uniform_dist(gen) * 1000;
            macro_data.emplace_back(x, y);
        }
        
        PlotStyle macro_style;
        macro_style.r = 0.2; macro_style.g = 0.8; macro_style.b = 0.2;
        macro_style.point_size = 2.5;
        macro_style.alpha = 0.7;
        
        plot.add_series("Macro Data", macro_data, macro_style);
    }
    
    // Subplot 3: Exponential distribution
    {
        auto& plot = test_1x4.get_subplot(0, 2);
        plot.set_labels("Exponential Dist", "X", "Y");
        
        std::vector<Point2D> exp_data;
        for (int i = 0; i < 60; ++i) {
            double x = exp_dist(gen);
            double y = exp_dist(gen);
            exp_data.emplace_back(x, y);
        }
        
        PlotStyle exp_style;
        exp_style.r = 0.2; exp_style.g = 0.2; exp_style.b = 0.8;
        exp_style.point_size = 2.0;
        exp_style.alpha = 0.6;
        
        plot.add_series("Exponential", exp_data, exp_style);
    }
    
    // Subplot 4: Simple incremental data
    {
        auto& plot = test_1x4.get_subplot(0, 3);
        plot.set_labels("Incremental", "Step", "Value");
        
        std::vector<Point2D> increment_data;
        for (int i = 0; i < 20; ++i) {
            increment_data.emplace_back(i, i * i);  // Quadratic growth
        }
        
        PlotStyle inc_style;
        inc_style.r = 0.8; inc_style.g = 0.8; inc_style.b = 0.2;
        inc_style.point_size = 4.0;
        inc_style.alpha = 0.9;
        
        plot.add_series("y = x²", increment_data, inc_style);
    }
    
    test_1x4.save_png("output/test_1x4_varied.png");
    std::cout << "✅ 1x4 varied data test saved" << std::endl;
    
    // Test 2: 3x2 layout with clustering and varied distributions
    std::cout << "\n=== Test 2: 3x2 Layout with Clustering and Distributions ===" << std::endl;
    SubplotManager test_3x2(3, 2, 1200, 1500, 0.08);
    test_3x2.set_main_title("3x2 Layout: Clustering and Distribution Analysis");
    
    // Row 1, Col 1: Many clusters
    {
        auto& plot = test_3x2.get_subplot(0, 0);
        plot.set_labels("Many Clusters", "X", "Y");
        
        std::vector<Point2D> cluster_points;
        std::vector<int> cluster_labels;
        
        // Generate 6 clusters
        for (int cluster = 0; cluster < 6; ++cluster) {
            double center_x = (cluster % 3 - 1) * 3.0;
            double center_y = (cluster / 3 - 0.5) * 3.0;
            
            for (int i = 0; i < 15; ++i) {
                double x = center_x + normal_dist(gen) * 0.4;
                double y = center_y + normal_dist(gen) * 0.4;
                cluster_points.emplace_back(x, y);
                cluster_labels.push_back(cluster);
            }
        }
        
        // Add outliers
        for (int i = 0; i < 10; ++i) {
            double x = uniform_dist(gen) * 0.8;
            double y = uniform_dist(gen) * 0.8;
            cluster_points.emplace_back(x, y);
            cluster_labels.push_back(-1);
        }
        
        plot.add_cluster_data("Multi-Cluster", cluster_points, cluster_labels, 2.5, 0.8);
    }
    
    // Row 1, Col 2: Sparse data
    {
        auto& plot = test_3x2.get_subplot(0, 1);
        plot.set_labels("Sparse Data", "X", "Y");
        
        std::vector<Point2D> sparse_data;
        for (int i = 0; i < 8; ++i) {  // Very few points
            double x = uniform_dist(gen) * 0.5;
            double y = uniform_dist(gen) * 0.5;
            sparse_data.emplace_back(x, y);
        }
        
        PlotStyle sparse_style;
        sparse_style.r = 0.9; sparse_style.g = 0.1; sparse_style.b = 0.9;
        sparse_style.point_size = 6.0;  // Large points for visibility
        sparse_style.alpha = 0.9;
        
        plot.add_series("Sparse", sparse_data, sparse_style);
    }
    
    // Row 2, Col 1: Dense data
    {
        auto& plot = test_3x2.get_subplot(1, 0);
        plot.set_labels("Dense Data", "X", "Y");
        
        std::vector<Point2D> dense_data;
        for (int i = 0; i < 500; ++i) {  // Many points
            double x = normal_dist(gen) * 2.0;
            double y = normal_dist(gen) * 2.0;
            dense_data.emplace_back(x, y);
        }
        
        PlotStyle dense_style;
        dense_style.r = 0.1; dense_style.g = 0.9; dense_style.b = 0.1;
        dense_style.point_size = 1.0;  // Small points
        dense_style.alpha = 0.3;  // Low alpha for overlap
        
        plot.add_series("Dense", dense_data, dense_style);
    }
    
    // Row 2, Col 2: Extreme range data
    {
        auto& plot = test_3x2.get_subplot(1, 1);
        plot.set_labels("Extreme Range", "X", "Y");
        
        std::vector<Point2D> extreme_data;
        // Mix of very small and very large values
        for (int i = 0; i < 30; ++i) {
            if (i < 15) {
                double x = normal_dist(gen) * 0.01;  // Very small
                double y = normal_dist(gen) * 0.01;
                extreme_data.emplace_back(x, y);
            } else {
                double x = uniform_dist(gen) * 50;   // Very large
                double y = uniform_dist(gen) * 50;
                extreme_data.emplace_back(x, y);
            }
        }
        
        PlotStyle extreme_style;
        extreme_style.r = 0.5; extreme_style.g = 0.0; extreme_style.b = 0.8;
        extreme_style.point_size = 3.0;
        extreme_style.alpha = 0.8;
        
        plot.add_series("Extreme", extreme_data, extreme_style);
    }
    
    // Row 3, Col 1: Logarithmic pattern
    {
        auto& plot = test_3x2.get_subplot(2, 0);
        plot.set_labels("Logarithmic", "X", "log(Y)");
        
        std::vector<Point2D> log_data;
        for (int i = 1; i <= 50; ++i) {
            double x = i * 0.2;
            double y = std::log(x + 1) + normal_dist(gen) * 0.1;
            log_data.emplace_back(x, y);
        }
        
        PlotStyle log_style;
        log_style.r = 0.8; log_style.g = 0.4; log_style.b = 0.0;
        log_style.point_size = 2.5;
        log_style.alpha = 0.8;
        
        plot.add_series("log(x+1)", log_data, log_style);
    }
    
    // Row 3, Col 2: Circular pattern
    {
        auto& plot = test_3x2.get_subplot(2, 1);
        plot.set_labels("Circular Pattern", "X", "Y");
        
        std::vector<Point2D> circle_data;
        for (int i = 0; i < 60; ++i) {
            double angle = i * 2 * M_PI / 60;
            double radius = 2.0 + normal_dist(gen) * 0.2;
            double x = radius * cos(angle);
            double y = radius * sin(angle);
            circle_data.emplace_back(x, y);
        }
        
        PlotStyle circle_style;
        circle_style.r = 0.0; circle_style.g = 0.6; circle_style.b = 0.8;
        circle_style.point_size = 2.0;
        circle_style.alpha = 0.7;
        
        plot.add_series("Circle", circle_data, circle_style);
    }
    
    test_3x2.save_png("output/test_3x2_complex.png");
    std::cout << "✅ 3x2 complex data test saved" << std::endl;
    
    // Test 3: Edge case layouts
    std::cout << "\n=== Test 3: Edge Case Layouts ===" << std::endl;
    
    // 1x6 - Very wide
    SubplotManager test_1x6(1, 6, 2400, 400, 0.03);
    test_1x6.set_main_title("1x6 Ultra-Wide Layout");
    
    for (int j = 0; j < 6; ++j) {
        auto& plot = test_1x6.get_subplot(0, j);
        plot.set_labels("Plot " + std::to_string(j), "X", "Y");
        
        std::vector<Point2D> simple_data;
        for (int i = 0; i < 20; ++i) {
            double x = i * 0.1;
            double y = sin(x + j) + normal_dist(gen) * 0.1;
            simple_data.emplace_back(x, y);
        }
        
        PlotStyle style;
        style.r = (j % 3) * 0.4 + 0.2;
        style.g = ((j + 1) % 3) * 0.4 + 0.2;
        style.b = ((j + 2) % 3) * 0.4 + 0.2;
        style.point_size = 2.5;
        style.alpha = 0.8;
        
        plot.add_series("sin(x+" + std::to_string(j) + ")", simple_data, style);
    }
    
    test_1x6.save_png("output/test_1x6_wide.png");
    std::cout << "✅ 1x6 ultra-wide test saved" << std::endl;
    
    // 6x1 - Very tall
    SubplotManager test_6x1(6, 1, 600, 2400, 0.03);
    test_6x1.set_main_title("6x1 Ultra-Tall Layout");
    
    for (int i = 0; i < 6; ++i) {
        auto& plot = test_6x1.get_subplot(i, 0);
        plot.set_labels("Plot " + std::to_string(i), "X", "Y");
        
        std::vector<Point2D> simple_data;
        for (int j = 0; j < 25; ++j) {
            double x = j * 0.2;
            double y = pow(x, i * 0.5 + 0.5) + normal_dist(gen) * 0.2;
            simple_data.emplace_back(x, y);
        }
        
        PlotStyle style;
        style.r = 0.8 - i * 0.1;
        style.g = 0.2 + i * 0.1;
        style.b = 0.5;
        style.point_size = 3.0;
        style.alpha = 0.8;
        
        plot.add_series("x^" + std::to_string(i * 0.5 + 0.5), simple_data, style);
    }
    
    test_6x1.save_png("output/test_6x1_tall.png");
    std::cout << "✅ 6x1 ultra-tall test saved" << std::endl;
    
    // Test 4: Mixed data types in single layout
    std::cout << "\n=== Test 4: 2x3 Mixed Data Types ===" << std::endl;
    SubplotManager test_2x3(2, 3, 1500, 1000, 0.06);
    test_2x3.set_main_title("2x3 Mixed Data Types and Scales");
    
    // Different data types and scales in each subplot
    std::vector<std::string> titles = {
        "Negative Values", "Zero-Centered", "Positive Only",
        "Time Series", "Clustered", "Random Walk"
    };
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto& plot = test_2x3.get_subplot(i, j);
            int idx = i * 3 + j;
            plot.set_labels(titles[idx], "X", "Y");
            
            std::vector<Point2D> data;
            PlotStyle style;
            style.point_size = 2.5;
            style.alpha = 0.8;
            
            switch (idx) {
                case 0: // Negative values
                    for (int k = 0; k < 40; ++k) {
                        data.emplace_back(-abs(normal_dist(gen)), -abs(normal_dist(gen)));
                    }
                    style.r = 0.8; style.g = 0.2; style.b = 0.2;
                    break;
                    
                case 1: // Zero-centered
                    for (int k = 0; k < 50; ++k) {
                        data.emplace_back(normal_dist(gen), normal_dist(gen));
                    }
                    style.r = 0.2; style.g = 0.8; style.b = 0.2;
                    break;
                    
                case 2: // Positive only
                    for (int k = 0; k < 45; ++k) {
                        data.emplace_back(abs(normal_dist(gen)), abs(normal_dist(gen)));
                    }
                    style.r = 0.2; style.g = 0.2; style.b = 0.8;
                    break;
                    
                case 3: // Time series
                    for (int k = 0; k < 60; ++k) {
                        double t = k * 0.1;
                        data.emplace_back(t, sin(t) + cos(t * 0.5) + normal_dist(gen) * 0.1);
                    }
                    style.r = 0.8; style.g = 0.8; style.b = 0.2;
                    break;
                    
                case 4: // Clustered
                    {
                        std::vector<int> labels;
                        for (int cluster = 0; cluster < 3; ++cluster) {
                            for (int k = 0; k < 20; ++k) {
                                double x = cluster * 2.0 + normal_dist(gen) * 0.3;
                                double y = normal_dist(gen) * 0.5;
                                data.emplace_back(x, y);
                                labels.push_back(cluster);
                            }
                        }
                        plot.add_cluster_data("Clusters", data, labels, 2.0, 0.8);
                        continue;  // Skip regular series addition
                    }
                    
                case 5: // Random walk
                    {
                        double x = 0, y = 0;
                        for (int k = 0; k < 100; ++k) {
                            x += normal_dist(gen) * 0.1;
                            y += normal_dist(gen) * 0.1;
                            data.emplace_back(x, y);
                        }
                        style.r = 0.8; style.g = 0.2; style.b = 0.8;
                        style.point_size = 1.5;
                        break;
                    }
            }
            
            if (idx != 4) {  // Skip if already added as cluster data
                plot.add_series("Data", data, style);
            }
        }
    }
    
    test_2x3.save_png("output/test_2x3_mixed.png");
    std::cout << "✅ 2x3 mixed data types test saved" << std::endl;
    
    std::cout << "\n=== Comprehensive Test Summary ===" << std::endl;
    std::cout << "Generated test files:" << std::endl;
    std::cout << "- output/test_1x4_varied.png (varied data types and ranges)" << std::endl;
    std::cout << "- output/test_3x2_complex.png (clustering and distributions)" << std::endl;
    std::cout << "- output/test_1x6_wide.png (ultra-wide layout)" << std::endl;
    std::cout << "- output/test_6x1_tall.png (ultra-tall layout)" << std::endl;
    std::cout << "- output/test_2x3_mixed.png (mixed data types)" << std::endl;
    std::cout << "\nCheck these files for:" << std::endl;
    std::cout << "1. Proper aspect ratio preservation" << std::endl;
    std::cout << "2. Correct centering and positioning" << std::endl;
    std::cout << "3. No overlapping or shifting" << std::endl;
    std::cout << "4. Consistent appearance across different layouts" << std::endl;
    std::cout << "5. Proper handling of varied data ranges and distributions" << std::endl;
    
    return 0;
} 