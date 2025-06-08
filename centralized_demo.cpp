#include "plotting_library/scatter_plot.h"
#include <vector>
#include <random>
#include <iostream>
#include <filesystem>
#include <cmath>

int main() {
    std::cout << "=== Centralized Plotting Library Demonstration ===" << std::endl;
    std::cout << "Testing various subplot dimensions and all library features..." << std::endl;
    
    // Create output directory
    std::filesystem::create_directories("output");
    
    // Random number generators
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normal_dist(0.0, 1.0);
    std::uniform_real_distribution<> uniform_dist(-3.0, 3.0);
    std::exponential_distribution<> exp_dist(1.0);
    
    // =================================================================
    // DEMO 1: Single Plot - Basic Functionality
    // =================================================================
    std::cout << "\n1. Creating single plot demonstration..." << std::endl;
    {
        ScatterPlot single_plot(800, 600);
        single_plot.set_labels("Basic Scatter Plot Features", "X Values", "Y Values");
        
        // Multiple series with different styles
        std::vector<Point2D> sine_data, cosine_data, linear_data;
        for (int i = 0; i <= 50; ++i) {
            double x = i * 0.2;
            sine_data.emplace_back(x, sin(x));
            cosine_data.emplace_back(x, cos(x));
            linear_data.emplace_back(x, 0.1 * x + 0.5 + 0.1 * sin(x * 3));
        }
        
        PlotStyle sine_style = {1.0, 0.0, 0.0, 3.0, 0.8};  // Red
        PlotStyle cosine_style = {0.0, 0.0, 1.0, 3.0, 0.8}; // Blue
        PlotStyle linear_style = {0.0, 0.8, 0.0, 2.5, 0.7}; // Green
        
        single_plot.add_series("sin(x)", sine_data, sine_style);
        single_plot.add_series("cos(x)", cosine_data, cosine_style);
        single_plot.add_series("Linear", linear_data, linear_style);
        
        single_plot.save_png("output/01_single_plot_demo.png");
        std::cout << "✅ Single plot saved to output/01_single_plot_demo.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 2: Cluster Visualization
    // =================================================================
    std::cout << "\n2. Creating cluster visualization demonstration..." << std::endl;
    {
        ScatterPlot cluster_plot(900, 700);
        cluster_plot.set_labels("Clustering Results Visualization", "Feature 1", "Feature 2");
        
        std::vector<Point2D> points;
        std::vector<int> cluster_labels;
        
        // Generate 4 clusters + outliers
        // Cluster 0: Around (1, 1)
        for (int i = 0; i < 50; ++i) {
            double x = 1.0 + normal_dist(gen) * 0.5;
            double y = 1.0 + normal_dist(gen) * 0.5;
            points.emplace_back(x, y);
            cluster_labels.push_back(0);
        }
        
        // Cluster 1: Around (-1, 1)
        for (int i = 0; i < 45; ++i) {
            double x = -1.0 + normal_dist(gen) * 0.5;
            double y = 1.0 + normal_dist(gen) * 0.5;
            points.emplace_back(x, y);
            cluster_labels.push_back(1);
        }
        
        // Cluster 2: Around (0, -1.5)
        for (int i = 0; i < 40; ++i) {
            double x = 0.0 + normal_dist(gen) * 0.5;
            double y = -1.5 + normal_dist(gen) * 0.5;
            points.emplace_back(x, y);
            cluster_labels.push_back(2);
        }
        
        // Outliers
        for (int i = 0; i < 20; ++i) {
            double x = uniform_dist(gen);
            double y = uniform_dist(gen);
            points.emplace_back(x, y);
            cluster_labels.push_back(-1);
        }
        
        cluster_plot.add_cluster_data("DBSCAN Results", points, cluster_labels, 4.0, 0.8);
        cluster_plot.save_png("output/02_cluster_demo.png");
        std::cout << "✅ Cluster plot saved to output/02_cluster_demo.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 3: 1x6 Layout - Ultra-wide Configuration
    // =================================================================
    std::cout << "\n3. Creating 1x6 ultra-wide layout..." << std::endl;
    {
        SubplotManager layout_1x6(1, 6, 2400, 400, 0.03);
        layout_1x6.set_main_title("1x6 Layout: Six Different Data Patterns");
        
        // Subplot 1: Normal distribution
        {
            auto& plot = layout_1x6.get_subplot(0, 0);
            plot.set_labels("Normal", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 80; ++i) {
                data.emplace_back(normal_dist(gen), normal_dist(gen));
            }
            PlotStyle style = {0.8, 0.2, 0.2, 2.0, 0.7};
            plot.add_series("Normal", data, style);
        }
        
        // Subplot 2: Uniform distribution
        {
            auto& plot = layout_1x6.get_subplot(0, 1);
            plot.set_labels("Uniform", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 60; ++i) {
                data.emplace_back(uniform_dist(gen), uniform_dist(gen));
            }
            PlotStyle style = {0.2, 0.8, 0.2, 2.0, 0.7};
            plot.add_series("Uniform", data, style);
        }
        
        // Subplot 3: Exponential
        {
            auto& plot = layout_1x6.get_subplot(0, 2);
            plot.set_labels("Exponential", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 50; ++i) {
                data.emplace_back(exp_dist(gen), exp_dist(gen));
            }
            PlotStyle style = {0.2, 0.2, 0.8, 2.0, 0.7};
            plot.add_series("Exponential", data, style);
        }
        
        // Subplot 4: Sine wave
        {
            auto& plot = layout_1x6.get_subplot(0, 3);
            plot.set_labels("Sine Wave", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i <= 30; ++i) {
                double x = i * 0.3;
                data.emplace_back(x, sin(x));
            }
            PlotStyle style = {0.8, 0.0, 0.8, 2.5, 0.8};
            plot.add_series("sin(x)", data, style);
        }
        
        // Subplot 5: Quadratic
        {
            auto& plot = layout_1x6.get_subplot(0, 4);
            plot.set_labels("Quadratic", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i <= 20; ++i) {
                double x = i * 0.2 - 2.0;
                data.emplace_back(x, x * x);
            }
            PlotStyle style = {0.0, 0.8, 0.8, 2.5, 0.8};
            plot.add_series("x²", data, style);
        }
        
        // Subplot 6: Circular pattern
        {
            auto& plot = layout_1x6.get_subplot(0, 5);
            plot.set_labels("Circle", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 40; ++i) {
                double angle = i * 2 * M_PI / 40;
                double radius = 1.0 + normal_dist(gen) * 0.1;
                data.emplace_back(radius * cos(angle), radius * sin(angle));
            }
            PlotStyle style = {0.8, 0.8, 0.0, 2.0, 0.7};
            plot.add_series("Circle", data, style);
        }
        
        layout_1x6.save_png("output/03_layout_1x6.png");
        std::cout << "✅ 1x6 layout saved to output/03_layout_1x6.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 4: 3x2 Layout - Mixed Analysis Dashboard
    // =================================================================
    std::cout << "\n4. Creating 3x2 mixed analysis dashboard..." << std::endl;
    {
        SubplotManager layout_3x2(3, 2, 1200, 1500, 0.08);
        layout_3x2.set_main_title("3x2 Layout: Comprehensive Data Analysis Dashboard");
        
        // Row 1, Col 1: Multi-cluster analysis
        {
            auto& plot = layout_3x2.get_subplot(0, 0);
            plot.set_labels("Multi-Cluster", "X", "Y");
            
            std::vector<Point2D> points;
            std::vector<int> labels;
            
            // 5 clusters
            for (int cluster = 0; cluster < 5; ++cluster) {
                double center_x = (cluster % 3 - 1) * 2.0;
                double center_y = (cluster / 3 - 1) * 2.0;
                
                for (int i = 0; i < 20; ++i) {
                    double x = center_x + normal_dist(gen) * 0.3;
                    double y = center_y + normal_dist(gen) * 0.3;
                    points.emplace_back(x, y);
                    labels.push_back(cluster);
                }
            }
            
            // Outliers
            for (int i = 0; i < 15; ++i) {
                points.emplace_back(uniform_dist(gen), uniform_dist(gen));
                labels.push_back(-1);
            }
            
            plot.add_cluster_data("5-Cluster", points, labels, 2.0, 0.8);
        }
        
        // Row 1, Col 2: Statistical distributions
        {
            auto& plot = layout_3x2.get_subplot(0, 1);
            plot.set_labels("Distributions", "X", "Y");
            
            std::vector<Point2D> normal_data, uniform_data;
            for (int i = 0; i < 60; ++i) {
                normal_data.emplace_back(normal_dist(gen), normal_dist(gen));
                uniform_data.emplace_back(uniform_dist(gen) * 0.8, uniform_dist(gen) * 0.8);
            }
            
            PlotStyle normal_style = {0.2, 0.4, 0.8, 2.5, 0.7};
            PlotStyle uniform_style = {0.8, 0.2, 0.2, 2.5, 0.7};
            
            plot.add_series("Normal", normal_data, normal_style);
            plot.add_series("Uniform", uniform_data, uniform_style);
        }
        
        // Row 2, Col 1: Time series
        {
            auto& plot = layout_3x2.get_subplot(1, 0);
            plot.set_labels("Time Series", "Time", "Value");
            
            std::vector<Point2D> trend_data, noisy_data;
            for (int i = 0; i < 50; ++i) {
                double t = i * 0.2;
                double trend = 2.0 + 0.5 * t + 0.3 * sin(t);
                trend_data.emplace_back(t, trend);
                noisy_data.emplace_back(t, trend + normal_dist(gen) * 0.5);
            }
            
            PlotStyle trend_style = {0.0, 0.0, 1.0, 2.5, 0.9};
            PlotStyle noisy_style = {0.6, 0.6, 0.6, 1.5, 0.6};
            
            plot.add_series("Trend", trend_data, trend_style);
            plot.add_series("Noisy", noisy_data, noisy_style);
        }
        
        // Row 2, Col 2: Mathematical functions
        {
            auto& plot = layout_3x2.get_subplot(1, 1);
            plot.set_labels("Functions", "X", "Y");
            
            std::vector<Point2D> sine_data, cosine_data;
            for (int i = 0; i <= 40; ++i) {
                double x = i * 0.3;
                sine_data.emplace_back(x, sin(x));
                cosine_data.emplace_back(x, cos(x));
            }
            
            PlotStyle sine_style = {1.0, 0.0, 0.0, 2.0, 0.8};
            PlotStyle cosine_style = {0.0, 0.8, 0.0, 2.0, 0.8};
            
            plot.add_series("sin(x)", sine_data, sine_style);
            plot.add_series("cos(x)", cosine_data, cosine_style);
        }
        
        // Row 3, Col 1: Sparse vs Dense
        {
            auto& plot = layout_3x2.get_subplot(2, 0);
            plot.set_labels("Density Test", "X", "Y");
            
            std::vector<Point2D> sparse_data, dense_data;
            
            // Sparse data (few points)
            for (int i = 0; i < 8; ++i) {
                sparse_data.emplace_back(uniform_dist(gen) * 0.5, uniform_dist(gen) * 0.5);
            }
            
            // Dense data (many points)
            for (int i = 0; i < 200; ++i) {
                dense_data.emplace_back(normal_dist(gen) * 0.3 + 1.0, normal_dist(gen) * 0.3 + 1.0);
            }
            
            PlotStyle sparse_style = {0.9, 0.1, 0.9, 6.0, 0.9};
            PlotStyle dense_style = {0.1, 0.9, 0.1, 1.0, 0.3};
            
            plot.add_series("Sparse", sparse_data, sparse_style);
            plot.add_series("Dense", dense_data, dense_style);
        }
        
        // Row 3, Col 2: Extreme ranges
        {
            auto& plot = layout_3x2.get_subplot(2, 1);
            plot.set_labels("Extreme Range", "X", "Y");
            
            std::vector<Point2D> micro_data, macro_data;
            
            // Micro scale
            for (int i = 0; i < 20; ++i) {
                micro_data.emplace_back(normal_dist(gen) * 0.01, normal_dist(gen) * 0.01);
            }
            
            // Macro scale
            for (int i = 0; i < 15; ++i) {
                macro_data.emplace_back(uniform_dist(gen) * 10, uniform_dist(gen) * 10);
            }
            
            PlotStyle micro_style = {0.8, 0.2, 0.2, 4.0, 0.8};
            PlotStyle macro_style = {0.2, 0.2, 0.8, 3.0, 0.7};
            
            plot.add_series("Micro", micro_data, micro_style);
            plot.add_series("Macro", macro_data, macro_style);
        }
        
        layout_3x2.save_png("output/04_layout_3x2.png");
        std::cout << "✅ 3x2 layout saved to output/04_layout_3x2.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 5: 6x1 Layout - Ultra-tall Configuration
    // =================================================================
    std::cout << "\n5. Creating 6x1 ultra-tall layout..." << std::endl;
    {
        SubplotManager layout_6x1(6, 1, 500, 2400, 0.03);
        layout_6x1.set_main_title("6x1 Layout: Vertical Data Analysis Stack");
        
        // Row 1: Linear trend
        {
            auto& plot = layout_6x1.get_subplot(0, 0);
            plot.set_labels("Linear", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 30; ++i) {
                double x = i * 0.2;
                data.emplace_back(x, 0.5 * x + normal_dist(gen) * 0.2);
            }
            PlotStyle style = {0.8, 0.2, 0.2, 2.5, 0.8};
            plot.add_series("Linear", data, style);
        }
        
        // Row 2: Quadratic
        {
            auto& plot = layout_6x1.get_subplot(1, 0);
            plot.set_labels("Quadratic", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 25; ++i) {
                double x = i * 0.2 - 2.5;
                data.emplace_back(x, x * x + normal_dist(gen) * 0.1);
            }
            PlotStyle style = {0.2, 0.8, 0.2, 2.5, 0.8};
            plot.add_series("x²", data, style);
        }
        
        // Row 3: Exponential
        {
            auto& plot = layout_6x1.get_subplot(2, 0);
            plot.set_labels("Exponential", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 20; ++i) {
                double x = i * 0.2;
                data.emplace_back(x, exp(x * 0.3) + normal_dist(gen) * 0.1);
            }
            PlotStyle style = {0.2, 0.2, 0.8, 2.5, 0.8};
            plot.add_series("exp(x)", data, style);
        }
        
        // Row 4: Logarithmic
        {
            auto& plot = layout_6x1.get_subplot(3, 0);
            plot.set_labels("Logarithmic", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 1; i <= 30; ++i) {
                double x = i * 0.2;
                data.emplace_back(x, log(x + 1) + normal_dist(gen) * 0.1);
            }
            PlotStyle style = {0.8, 0.0, 0.8, 2.5, 0.8};
            plot.add_series("log(x)", data, style);
        }
        
        // Row 5: Sine wave
        {
            auto& plot = layout_6x1.get_subplot(4, 0);
            plot.set_labels("Sine", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i <= 40; ++i) {
                double x = i * 0.2;
                data.emplace_back(x, sin(x) + normal_dist(gen) * 0.1);
            }
            PlotStyle style = {0.0, 0.8, 0.8, 2.5, 0.8};
            plot.add_series("sin(x)", data, style);
        }
        
        // Row 6: Random walk
        {
            auto& plot = layout_6x1.get_subplot(5, 0);
            plot.set_labels("Random Walk", "Step", "Value");
            
            std::vector<Point2D> data;
            double value = 0.0;
            for (int i = 0; i < 50; ++i) {
                value += normal_dist(gen) * 0.3;
                data.emplace_back(i, value);
            }
            PlotStyle style = {0.8, 0.8, 0.0, 2.0, 0.8};
            plot.add_series("Walk", data, style);
        }
        
        layout_6x1.save_png("output/05_layout_6x1.png");
        std::cout << "✅ 6x1 layout saved to output/05_layout_6x1.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 6: 2x3 Layout - Mixed Patterns
    // =================================================================
    std::cout << "\n6. Creating 2x3 mixed patterns layout..." << std::endl;
    {
        SubplotManager layout_2x3(2, 3, 1500, 1000, 0.06);
        layout_2x3.set_main_title("2x3 Layout: Mixed Data Patterns and Edge Cases");
        
        // Row 1, Col 1: Negative values
        {
            auto& plot = layout_2x3.get_subplot(0, 0);
            plot.set_labels("Negative", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 40; ++i) {
                data.emplace_back(normal_dist(gen) - 2.0, normal_dist(gen) - 2.0);
            }
            PlotStyle style = {0.8, 0.2, 0.2, 2.5, 0.7};
            plot.add_series("Negative", data, style);
        }
        
        // Row 1, Col 2: Zero-centered
        {
            auto& plot = layout_2x3.get_subplot(0, 1);
            plot.set_labels("Zero-Centered", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 50; ++i) {
                data.emplace_back(normal_dist(gen) * 0.5, normal_dist(gen) * 0.5);
            }
            PlotStyle style = {0.2, 0.8, 0.2, 2.5, 0.7};
            plot.add_series("Centered", data, style);
        }
        
        // Row 1, Col 3: Positive only
        {
            auto& plot = layout_2x3.get_subplot(0, 2);
            plot.set_labels("Positive", "X", "Y");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 35; ++i) {
                data.emplace_back(abs(normal_dist(gen)) + 1.0, abs(normal_dist(gen)) + 1.0);
            }
            PlotStyle style = {0.2, 0.2, 0.8, 2.5, 0.7};
            plot.add_series("Positive", data, style);
        }
        
        // Row 2, Col 1: Time series
        {
            auto& plot = layout_2x3.get_subplot(1, 0);
            plot.set_labels("Time Series", "Time", "Value");
            
            std::vector<Point2D> data;
            for (int i = 0; i < 60; ++i) {
                double t = i * 0.1;
                data.emplace_back(t, sin(t) + 0.5 * sin(3 * t) + normal_dist(gen) * 0.1);
            }
            PlotStyle style = {0.8, 0.0, 0.8, 2.0, 0.8};
            plot.add_series("Signal", data, style);
        }
        
        // Row 2, Col 2: Clustering
        {
            auto& plot = layout_2x3.get_subplot(1, 1);
            plot.set_labels("Clusters", "X", "Y");
            
            std::vector<Point2D> points;
            std::vector<int> labels;
            
            // 3 clusters
            for (int cluster = 0; cluster < 3; ++cluster) {
                double center_x = (cluster - 1) * 1.5;
                double center_y = (cluster % 2) * 1.5 - 0.75;
                
                for (int i = 0; i < 25; ++i) {
                    double x = center_x + normal_dist(gen) * 0.3;
                    double y = center_y + normal_dist(gen) * 0.3;
                    points.emplace_back(x, y);
                    labels.push_back(cluster);
                }
            }
            
            plot.add_cluster_data("3-Cluster", points, labels, 2.5, 0.8);
        }
        
        // Row 2, Col 3: Random walk
        {
            auto& plot = layout_2x3.get_subplot(1, 2);
            plot.set_labels("Random Walk", "X", "Y");
            
            std::vector<Point2D> data;
            double x = 0.0, y = 0.0;
            for (int i = 0; i < 100; ++i) {
                x += normal_dist(gen) * 0.1;
                y += normal_dist(gen) * 0.1;
                data.emplace_back(x, y);
            }
            PlotStyle style = {0.0, 0.8, 0.8, 1.5, 0.6};
            plot.add_series("Walk", data, style);
        }
        
        layout_2x3.save_png("output/06_layout_2x3.png");
        std::cout << "✅ 2x3 layout saved to output/06_layout_2x3.png" << std::endl;
    }
    
    // =================================================================
    // DEMO 7: 4x2 Layout - Comprehensive Feature Test
    // =================================================================
    std::cout << "\n7. Creating 4x2 comprehensive feature test..." << std::endl;
    {
        SubplotManager layout_4x2(4, 2, 1200, 1600, 0.05);
        layout_4x2.set_main_title("4x2 Layout: Comprehensive Library Feature Test");
        
        // Test all major features across 8 subplots
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 2; ++j) {
                auto& plot = layout_4x2.get_subplot(i, j);
                int subplot_idx = i * 2 + j;
                
                switch (subplot_idx) {
                    case 0: // Multiple series
                    {
                        plot.set_labels("Multi-Series", "X", "Y");
                        std::vector<Point2D> data1, data2, data3;
                        for (int k = 0; k < 20; ++k) {
                            double x = k * 0.2;
                            data1.emplace_back(x, sin(x));
                            data2.emplace_back(x, cos(x));
                            data3.emplace_back(x, sin(x) * cos(x));
                        }
                        PlotStyle style1 = {1.0, 0.0, 0.0, 2.0, 0.8};
                        PlotStyle style2 = {0.0, 1.0, 0.0, 2.0, 0.8};
                        PlotStyle style3 = {0.0, 0.0, 1.0, 2.0, 0.8};
                        plot.add_series("sin", data1, style1);
                        plot.add_series("cos", data2, style2);
                        plot.add_series("sin*cos", data3, style3);
                        break;
                    }
                    case 1: // Large dataset
                    {
                        plot.set_labels("Large Dataset", "X", "Y");
                        std::vector<Point2D> data;
                        for (int k = 0; k < 500; ++k) {
                            data.emplace_back(normal_dist(gen), normal_dist(gen));
                        }
                        PlotStyle style = {0.5, 0.5, 0.5, 1.0, 0.3};
                        plot.add_series("Large", data, style);
                        break;
                    }
                    case 2: // Small dataset
                    {
                        plot.set_labels("Small Dataset", "X", "Y");
                        std::vector<Point2D> data;
                        for (int k = 0; k < 5; ++k) {
                            data.emplace_back(uniform_dist(gen), uniform_dist(gen));
                        }
                        PlotStyle style = {0.8, 0.2, 0.8, 8.0, 1.0};
                        plot.add_series("Small", data, style);
                        break;
                    }
                    case 3: // Extreme values
                    {
                        plot.set_labels("Extreme Values", "X", "Y");
                        std::vector<Point2D> data;
                        data.emplace_back(-1000, -1000);
                        data.emplace_back(1000, 1000);
                        data.emplace_back(0, 0);
                        PlotStyle style = {0.8, 0.8, 0.0, 6.0, 0.9};
                        plot.add_series("Extreme", data, style);
                        break;
                    }
                    case 4: // Clustering with many clusters
                    {
                        plot.set_labels("Many Clusters", "X", "Y");
                        std::vector<Point2D> points;
                        std::vector<int> labels;
                        
                        for (int cluster = 0; cluster < 8; ++cluster) {
                            double center_x = (cluster % 4 - 1.5) * 1.0;
                            double center_y = (cluster / 4 - 0.5) * 1.0;
                            
                            for (int k = 0; k < 10; ++k) {
                                double x = center_x + normal_dist(gen) * 0.2;
                                double y = center_y + normal_dist(gen) * 0.2;
                                points.emplace_back(x, y);
                                labels.push_back(cluster);
                            }
                        }
                        plot.add_cluster_data("8-Cluster", points, labels, 1.5, 0.8);
                        break;
                    }
                    case 5: // Spiral pattern
                    {
                        plot.set_labels("Spiral", "X", "Y");
                        std::vector<Point2D> data;
                        for (int k = 0; k < 50; ++k) {
                            double t = k * 0.3;
                            double r = t * 0.1;
                            data.emplace_back(r * cos(t), r * sin(t));
                        }
                        PlotStyle style = {0.2, 0.8, 0.8, 2.5, 0.8};
                        plot.add_series("Spiral", data, style);
                        break;
                    }
                    case 6: // Step function
                    {
                        plot.set_labels("Step Function", "X", "Y");
                        std::vector<Point2D> data;
                        for (int k = 0; k < 40; ++k) {
                            double x = k * 0.2;
                            double y = floor(x);
                            data.emplace_back(x, y);
                        }
                        PlotStyle style = {0.8, 0.4, 0.0, 3.0, 0.9};
                        plot.add_series("Step", data, style);
                        break;
                    }
                    case 7: // Mixed positive/negative
                    {
                        plot.set_labels("Mixed Signs", "X", "Y");
                        std::vector<Point2D> pos_data, neg_data;
                        for (int k = 0; k < 25; ++k) {
                            pos_data.emplace_back(abs(normal_dist(gen)), abs(normal_dist(gen)));
                            neg_data.emplace_back(-abs(normal_dist(gen)), -abs(normal_dist(gen)));
                        }
                        PlotStyle pos_style = {0.0, 0.8, 0.0, 2.5, 0.7};
                        PlotStyle neg_style = {0.8, 0.0, 0.0, 2.5, 0.7};
                        plot.add_series("Positive", pos_data, pos_style);
                        plot.add_series("Negative", neg_data, neg_style);
                        break;
                    }
                }
            }
        }
        
        layout_4x2.save_png("output/07_layout_4x2.png");
        std::cout << "✅ 4x2 layout saved to output/07_layout_4x2.png" << std::endl;
    }
    
    // =================================================================
    // Summary
    // =================================================================
    std::cout << "\n=== Centralized Demo Complete ===" << std::endl;
    std::cout << "Generated demonstrations:" << std::endl;
    std::cout << "1. Single plot with multiple series and legend" << std::endl;
    std::cout << "2. Cluster visualization with automatic coloring" << std::endl;
    std::cout << "3. 1x6 ultra-wide layout with varied data types" << std::endl;
    std::cout << "4. 3x2 comprehensive analysis dashboard" << std::endl;
    std::cout << "5. 6x1 ultra-tall vertical stack" << std::endl;
    std::cout << "6. 2x3 mixed patterns and edge cases" << std::endl;
    std::cout << "7. 4x2 comprehensive feature test" << std::endl;
    std::cout << "\nAll outputs saved to output/ directory" << std::endl;
    std::cout << "\nLibrary features demonstrated:" << std::endl;
    std::cout << "✅ Single plots with multiple series" << std::endl;
    std::cout << "✅ Cluster visualization with automatic coloring" << std::endl;
    std::cout << "✅ Subplot layouts: 1x6, 3x2, 6x1, 2x3, 4x2" << std::endl;
    std::cout << "✅ Automatic axis scaling and tick generation" << std::endl;
    std::cout << "✅ Legend support and proper positioning" << std::endl;
    std::cout << "✅ Title and axis label support" << std::endl;
    std::cout << "✅ Aspect ratio preservation" << std::endl;
    std::cout << "✅ Proper centering of title + subplots groups" << std::endl;
    std::cout << "✅ Various data patterns and edge cases" << std::endl;
    
    return 0;
}