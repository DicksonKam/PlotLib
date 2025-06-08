#include "scatter_plot.h"
#include <vector>
#include <random>
#include <iostream>
#include <filesystem>

int main() {
    std::cout << "Creating cluster-based scatter plot demonstration..." << std::endl;
    
    ScatterPlot plot(900, 700);
    
    // Set plot labels and title
    plot.set_labels("Clustering Results Visualization", "Feature 1", "Feature 2");
    
    // Generate sample clustered data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normal_dist(0.0, 0.5);
    std::uniform_real_distribution<> uniform_dist(-4.0, 4.0);
    
    std::vector<Point2D> points;
    std::vector<int> cluster_labels;
    
    // Cluster 0: Points around (1, 1)
    for (int i = 0; i < 50; ++i) {
        double x = 1.0 + normal_dist(gen);
        double y = 1.0 + normal_dist(gen);
        points.emplace_back(x, y);
        cluster_labels.push_back(0);
    }
    
    // Cluster 1: Points around (-1, 1)
    for (int i = 0; i < 45; ++i) {
        double x = -1.0 + normal_dist(gen);
        double y = 1.0 + normal_dist(gen);
        points.emplace_back(x, y);
        cluster_labels.push_back(1);
    }
    
    // Cluster 2: Points around (0, -1.5)
    for (int i = 0; i < 40; ++i) {
        double x = 0.0 + normal_dist(gen);
        double y = -1.5 + normal_dist(gen);
        points.emplace_back(x, y);
        cluster_labels.push_back(2);
    }
    
    // Cluster 3: Points around (2, -1)
    for (int i = 0; i < 35; ++i) {
        double x = 2.0 + normal_dist(gen) * 0.7;
        double y = -1.0 + normal_dist(gen) * 0.7;
        points.emplace_back(x, y);
        cluster_labels.push_back(3);
    }
    
    // Outliers (cluster label -1): Random scattered points
    for (int i = 0; i < 20; ++i) {
        double x = uniform_dist(gen);
        double y = uniform_dist(gen);
        // Make sure outliers are not too close to clusters
        if (abs(x - 1.0) > 1.5 && abs(x + 1.0) > 1.5 && abs(x) > 1.5 && abs(x - 2.0) > 1.5) {
            points.emplace_back(x, y);
            cluster_labels.push_back(-1);  // Outlier label
        }
    }
    
    // Add the cluster data to the plot
    plot.add_cluster_data("DBSCAN Results", points, cluster_labels, 4.0, 0.8);
    
    // Create output directory if it doesn't exist
    std::filesystem::create_directories("output");
    
    // Save the cluster plot
    if (plot.save_png("output/cluster_plot.png")) {
        std::cout << "✅ Cluster PNG saved successfully to output/cluster_plot.png" << std::endl;
    } else {
        std::cout << "❌ Failed to save cluster PNG" << std::endl;
    }
    
    if (plot.save_svg("output/cluster_plot.svg")) {
        std::cout << "✅ Cluster SVG saved successfully to output/cluster_plot.svg" << std::endl;
    } else {
        std::cout << "❌ Failed to save cluster SVG" << std::endl;
    }
    
    // Demonstrate individual cluster point addition
    std::cout << "\nDemonstrating individual cluster point addition..." << std::endl;
    ScatterPlot incremental_plot(800, 600);
    incremental_plot.set_title("Incremental Cluster Building");
    incremental_plot.set_xlabel("X Coordinate");
    incremental_plot.set_ylabel("Y Coordinate");
    
    // Add points one by one with cluster labels
    for (int i = 0; i < 30; ++i) {
        double x = normal_dist(gen);
        double y = normal_dist(gen);
        int cluster = (i < 10) ? 0 : (i < 20) ? 1 : -1;  // Mix of cluster 0, 1, and outliers
        incremental_plot.add_cluster_point("Incremental Data", x, y, cluster);
    }
    
    incremental_plot.save_png("output/incremental_cluster_plot.png");
    std::cout << "✅ Incremental cluster plot saved to output/incremental_cluster_plot.png" << std::endl;
    
    std::cout << "\nCluster visualization features demonstrated:" << std::endl;
    std::cout << "- Automatic color assignment for clusters (0, 1, 2, 3, ...)" << std::endl;
    std::cout << "- Red crosses for outliers (label -1)" << std::endl;
    std::cout << "- Outliers drawn in background, clusters in foreground" << std::endl;
    std::cout << "- Automatic legend with cluster names and outlier identification" << std::endl;
    std::cout << "- Support for both batch and incremental data addition" << std::endl;
    
    return 0;
} 