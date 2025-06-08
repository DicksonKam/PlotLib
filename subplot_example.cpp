#include "scatter_plot.h"
#include <vector>
#include <random>
#include <iostream>
#include <filesystem>
#include <cmath>

int main() {
    std::cout << "Creating subplot demonstration..." << std::endl;
    
    // Create a 2x2 subplot layout
    SubplotManager subplots(2, 2, 1400, 1000, 0.08);
    subplots.set_main_title("Comprehensive Data Analysis Dashboard");
    
    // Generate random data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normal_dist(0.0, 1.0);
    std::uniform_real_distribution<> uniform_dist(-3.0, 3.0);
    
    // Subplot 1 (top-left): Normal vs Uniform Distribution
    {
        auto& plot = subplots.get_subplot(0, 0);
        plot.set_labels("Statistical Distributions", "X Values", "Y Values");
        
        // Normal distribution data
        PlotStyle normal_style;
        normal_style.r = 0.2; normal_style.g = 0.4; normal_style.b = 0.8;
        normal_style.point_size = 2.5;
        normal_style.alpha = 0.7;
        
        std::vector<Point2D> normal_points;
        for (int i = 0; i < 100; ++i) {
            double x = normal_dist(gen);
            double y = normal_dist(gen);
            normal_points.emplace_back(x, y);
        }
        plot.add_series("Normal", normal_points, normal_style);
        
        // Uniform distribution data
        PlotStyle uniform_style;
        uniform_style.r = 0.8; uniform_style.g = 0.2; uniform_style.b = 0.2;
        uniform_style.point_size = 2.5;
        uniform_style.alpha = 0.7;
        
        std::vector<Point2D> uniform_points;
        for (int i = 0; i < 80; ++i) {
            double x = uniform_dist(gen);
            double y = uniform_dist(gen) * 0.6;
            uniform_points.emplace_back(x, y);
        }
        plot.add_series("Uniform", uniform_points, uniform_style);
    }
    
    // Subplot 2 (top-right): Clustering Results
    {
        auto& plot = subplots.get_subplot(0, 1);
        plot.set_labels("Clustering Analysis", "Feature 1", "Feature 2");
        
        std::vector<Point2D> cluster_points;
        std::vector<int> cluster_labels;
        
        // Cluster 0: Points around (1, 1)
        for (int i = 0; i < 30; ++i) {
            double x = 1.0 + normal_dist(gen) * 0.3;
            double y = 1.0 + normal_dist(gen) * 0.3;
            cluster_points.emplace_back(x, y);
            cluster_labels.push_back(0);
        }
        
        // Cluster 1: Points around (-1, -1)
        for (int i = 0; i < 25; ++i) {
            double x = -1.0 + normal_dist(gen) * 0.3;
            double y = -1.0 + normal_dist(gen) * 0.3;
            cluster_points.emplace_back(x, y);
            cluster_labels.push_back(1);
        }
        
        // Outliers
        for (int i = 0; i < 8; ++i) {
            double x = uniform_dist(gen);
            double y = uniform_dist(gen);
            if (abs(x - 1.0) > 1.0 && abs(x + 1.0) > 1.0) {
                cluster_points.emplace_back(x, y);
                cluster_labels.push_back(-1);
            }
        }
        
        plot.add_cluster_data("DBSCAN", cluster_points, cluster_labels, 3.0, 0.8);
    }
    
    // Subplot 3 (bottom-left): Function Visualization
    {
        auto& plot = subplots.get_subplot(1, 0);
        plot.set_labels("Mathematical Functions", "X", "Y");
        
        std::vector<Point2D> sine_data, cosine_data;
        
        for (int i = 0; i <= 40; ++i) {
            double x = i * 0.3;
            sine_data.emplace_back(x, sin(x));
            cosine_data.emplace_back(x, cos(x));
        }
        
        PlotStyle sine_style;
        sine_style.r = 1.0; sine_style.g = 0.0; sine_style.b = 0.0;
        sine_style.point_size = 2.0;
        sine_style.alpha = 0.8;
        
        PlotStyle cosine_style;
        cosine_style.r = 0.0; cosine_style.g = 0.8; cosine_style.b = 0.0;
        cosine_style.point_size = 2.0;
        cosine_style.alpha = 0.8;
        
        plot.add_series("sin(x)", sine_data, sine_style);
        plot.add_series("cos(x)", cosine_data, cosine_style);
    }
    
    // Subplot 4 (bottom-right): Time Series-like Data
    {
        auto& plot = subplots.get_subplot(1, 1);
        plot.set_labels("Time Series Analysis", "Time", "Value");
        
        std::vector<Point2D> trend_data, noisy_data;
        
        for (int i = 0; i < 50; ++i) {
            double t = i * 0.2;
            
            // Trend data
            double trend_value = 2.0 + 0.5 * t + 0.3 * sin(t);
            trend_data.emplace_back(t, trend_value);
            
            // Noisy data
            double noisy_value = trend_value + normal_dist(gen) * 0.5;
            noisy_data.emplace_back(t, noisy_value);
        }
        
        PlotStyle trend_style;
        trend_style.r = 0.0; trend_style.g = 0.0; trend_style.b = 1.0;
        trend_style.point_size = 2.5;
        trend_style.alpha = 0.9;
        
        PlotStyle noisy_style;
        noisy_style.r = 0.6; noisy_style.g = 0.6; noisy_style.b = 0.6;
        noisy_style.point_size = 1.5;
        noisy_style.alpha = 0.6;
        
        plot.add_series("Trend", trend_data, trend_style);
        plot.add_series("Noisy", noisy_data, noisy_style);
    }
    
    // Create output directory if it doesn't exist
    std::filesystem::create_directories("output");
    
    // Save the subplot figure
    if (subplots.save_png("output/subplots_2x2.png")) {
        std::cout << "✅ 2x2 Subplots PNG saved successfully to output/subplots_2x2.png" << std::endl;
    } else {
        std::cout << "❌ Failed to save 2x2 subplots PNG" << std::endl;
    }
    
    if (subplots.save_svg("output/subplots_2x2.svg")) {
        std::cout << "✅ 2x2 Subplots SVG saved successfully to output/subplots_2x2.svg" << std::endl;
    } else {
        std::cout << "❌ Failed to save 2x2 subplots SVG" << std::endl;
    }
    
    // Demonstrate 1x2 layout
    std::cout << "\nCreating 1x2 subplot layout..." << std::endl;
    SubplotManager horizontal_subplots(1, 2, 1200, 600, 0.1);
    horizontal_subplots.set_main_title("Side-by-Side Comparison");
    
    // Left subplot: Cluster data
    {
        auto& plot = horizontal_subplots.get_subplot(0, 0);
        plot.set_labels("Before Clustering", "X", "Y");
        
        std::vector<Point2D> mixed_data;
        for (int i = 0; i < 100; ++i) {
            double x = uniform_dist(gen);
            double y = uniform_dist(gen);
            mixed_data.emplace_back(x, y);
        }
        
        PlotStyle mixed_style;
        mixed_style.r = 0.5; mixed_style.g = 0.5; mixed_style.b = 0.5;
        mixed_style.point_size = 3.0;
        mixed_style.alpha = 0.7;
        
        plot.add_series("Raw Data", mixed_data, mixed_style);
    }
    
    // Right subplot: Same data with cluster labels
    {
        auto& plot = horizontal_subplots.get_subplot(0, 1);
        plot.set_labels("After Clustering", "X", "Y");
        
        std::vector<Point2D> clustered_points;
        std::vector<int> labels;
        
        // Generate some clustered data
        for (int i = 0; i < 80; ++i) {
            double x, y;
            int label;
            
            if (i < 30) {
                x = 1.0 + normal_dist(gen) * 0.4;
                y = 1.0 + normal_dist(gen) * 0.4;
                label = 0;
            } else if (i < 60) {
                x = -1.0 + normal_dist(gen) * 0.4;
                y = -1.0 + normal_dist(gen) * 0.4;
                label = 1;
            } else {
                x = uniform_dist(gen);
                y = uniform_dist(gen);
                label = -1;  // Outlier
            }
            
            clustered_points.emplace_back(x, y);
            labels.push_back(label);
        }
        
        plot.add_cluster_data("Clustered", clustered_points, labels, 3.0, 0.8);
    }
    
    horizontal_subplots.save_png("output/subplots_1x2.png");
    std::cout << "✅ 1x2 Subplots saved to output/subplots_1x2.png" << std::endl;
    
    // Demonstrate 2x1 layout
    std::cout << "\nCreating 2x1 subplot layout..." << std::endl;
    SubplotManager vertical_subplots(2, 1, 800, 1000, 0.1);
    vertical_subplots.set_main_title("Vertical Comparison");
    
    // Top subplot
    {
        auto& plot = vertical_subplots.get_subplot(0, 0);
        plot.set_labels("Dataset A", "X", "Y");
        
        std::vector<Point2D> dataset_a;
        for (int i = 0; i < 60; ++i) {
            double x = normal_dist(gen);
            double y = x * 0.5 + normal_dist(gen) * 0.3;  // Linear relationship
            dataset_a.emplace_back(x, y);
        }
        
        PlotStyle style_a;
        style_a.r = 0.8; style_a.g = 0.2; style_a.b = 0.2;
        style_a.point_size = 3.0;
        style_a.alpha = 0.8;
        
        plot.add_series("Linear Trend", dataset_a, style_a);
    }
    
    // Bottom subplot
    {
        auto& plot = vertical_subplots.get_subplot(1, 0);
        plot.set_labels("Dataset B", "X", "Y");
        
        std::vector<Point2D> dataset_b;
        for (int i = 0; i < 60; ++i) {
            double x = uniform_dist(gen);
            double y = x * x * 0.2 + normal_dist(gen) * 0.2;  // Quadratic relationship
            dataset_b.emplace_back(x, y);
        }
        
        PlotStyle style_b;
        style_b.r = 0.2; style_b.g = 0.2; style_b.b = 0.8;
        style_b.point_size = 3.0;
        style_b.alpha = 0.8;
        
        plot.add_series("Quadratic Trend", dataset_b, style_b);
    }
    
    vertical_subplots.save_png("output/subplots_2x1.png");
    std::cout << "✅ 2x1 Subplots saved to output/subplots_2x1.png" << std::endl;
    
    std::cout << "\nSubplot features demonstrated:" << std::endl;
    std::cout << "- 2x2 grid layout with comprehensive dashboard" << std::endl;
    std::cout << "- 1x2 horizontal comparison layout" << std::endl;
    std::cout << "- 2x1 vertical comparison layout" << std::endl;
    std::cout << "- Each subplot maintains full functionality (titles, legends, axes)" << std::endl;
    std::cout << "- Automatic scaling and positioning" << std::endl;
    std::cout << "- Main title for the entire figure" << std::endl;
    std::cout << "- Configurable spacing between subplots" << std::endl;
    
    return 0;
} 