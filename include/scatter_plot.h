/**
 * @file scatter_plot.h
 * @brief Scatter plot implementation using PlotManager
 * @author PlotLib Contributors
 * @version 1.0.0
 * @date 2025-06-08
 * 
 * This file contains the ScatterPlot class which extends PlotManager
 * to provide scatter plot specific functionality.
 */

#ifndef PLOTLIB_SCATTER_PLOT_H
#define PLOTLIB_SCATTER_PLOT_H

#include "plot_manager.h"
#include <map>
#include <set>

namespace plotlib {

/**
 * @brief Represents a data point with cluster label information
 */
struct ClusterPoint {
    double x, y;          ///< 2D coordinates of the point
    int cluster_label;    ///< Cluster ID (0, 1, 2, ...) or -1 for outliers
    
    /**
     * @brief Constructor from coordinates and label
     * @param x_coord X coordinate
     * @param y_coord Y coordinate  
     * @param label Cluster label (-1 for outliers, 0+ for clusters)
     */
    ClusterPoint(double x_coord, double y_coord, int label) : x(x_coord), y(y_coord), cluster_label(label) {}
};

/**
 * @brief Represents a cluster-based data series for clustering visualization
 */
struct ClusterSeries {
    std::vector<ClusterPoint> points; ///< Collection of cluster-labeled points
    std::string name;                 ///< Series name for legend (legacy, kept for compatibility)
    double point_size = 3.0;          ///< Size of cluster points
    double alpha = 0.8;               ///< Transparency of cluster points
    
    // Enhanced cluster legend management
    std::map<int, std::string> cluster_names;  ///< Custom names per cluster label (-1=outliers, 0+=clusters)
    std::map<int, std::string> cluster_colors; ///< Custom colors per cluster label (-1=outliers, 0+=clusters)
    bool use_auto_naming = true;               ///< Whether to use automatic naming ("Outliers", "Cluster 1", etc.)
    bool use_auto_coloring = true;             ///< Whether to use automatic coloring
    
    /**
     * @brief Constructor for ClusterSeries
     * @param series_name Name of the cluster series (default: empty)
     */
    ClusterSeries(const std::string& series_name = "") : name(series_name) {}
};

/**
 * @brief Scatter plot class that extends PlotManager
 * 
 * The ScatterPlot class provides scatter plot functionality by inheriting
 * from PlotManager and implementing the draw_data method to render points
 * as circles, crosses, squares, or triangles.
 * 
 * Features:
 * - Multiple marker types (circle, cross, square, triangle)
 * - Automatic and manual styling
 * - Cluster-based visualization with automatic coloring
 * - All PlotManager features (axes, legends, titles, subplots)
 * 
 * @example
 * @code
 * ScatterPlot plot(800, 600);
 * plot.set_labels("My Scatter Plot", "X Values", "Y Values");
 * 
 * std::vector<double> x_values = {1, 2, 3};
 * std::vector<double> y_values = {2, 4, 6};
 * plot.add_scatter(x_values, y_values, "Data", "red");
 * 
 * plot.save_png("scatter.png");
 * @endcode
 */
class ScatterPlot : public PlotManager {
private:
    MarkerType default_marker_type = MarkerType::CIRCLE; ///< Default marker type for new series
    
    // Cluster-related data and methods
    std::vector<ClusterSeries> cluster_series; ///< Collection of cluster-based series
    
    /**
     * @brief Get color for a specific cluster label
     * @param cluster_label Cluster ID (-1 for outliers, 0+ for clusters)
     * @return RGB color vector [r, g, b]
     */
    std::vector<double> get_cluster_color(int cluster_label);
    
protected:
    /**
     * @brief Draw scatter plot data points
     * @param cr Cairo context for rendering
     * 
     * This method implements the pure virtual draw_data method from PlotManager
     * to render scatter plot points using the specified marker types and styles.
     */
    void draw_data(cairo_t* cr) override;
    
    /**
     * @brief Draw regular data series points
     * @param cr Cairo context for rendering
     */
    void draw_points(cairo_t* cr);
    
    /**
     * @brief Draw cluster-based data points
     * @param cr Cairo context for rendering
     */
    void draw_cluster_points(cairo_t* cr);
    
    /**
     * @brief Calculate bounds including cluster data
     */
    void calculate_bounds() override;
    
    /**
     * @brief Check if scatter plot is empty (no data series and no cluster series)
     */
    bool is_plot_empty() const override;
    
    /**
     * @brief Draw legend including cluster legend entries
     * @param cr Cairo context for rendering
     */
    void collect_legend_items(std::vector<LegendItem>& items) override;
    
    /**
     * @brief Add cluster data series (internal method)
     * @param x_values X coordinates
     * @param y_values Y coordinates
     * @param cluster_labels Cluster labels for each point
     * @param names Custom names for clusters (optional, empty for auto-naming)
     * @param colors Custom colors for clusters (optional, empty for auto-coloring)
     * @param point_size Size of cluster points
     * @param alpha Transparency of cluster points
     */
    void add_cluster_data(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                         const std::vector<int>& cluster_labels, 
                         const std::vector<std::string>& names = {},
                         const std::vector<std::string>& colors = {},
                         double point_size = 3.0, double alpha = 0.8);
    
public:
    /**
     * @brief Constructor for ScatterPlot
     * @param width Canvas width in pixels (default: 800)
     * @param height Canvas height in pixels (default: 600)
     */
    ScatterPlot(int width = 800, int height = 600);
    
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~ScatterPlot() = default;
    
    /**
     * @brief Set the default marker type for new series
     * @param marker_type The marker type to use as default
     */
    void set_default_marker_type(MarkerType marker_type);
    
    /**
     * @brief Add a scatter series with custom color (beginner-friendly)
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param name Series name for legend
     * @param color_name Color name {"blue", "green", "orange", "purple", "cyan", "magenta", "yellow", "red"}
     */
    void add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values,
                     const std::string& name, const std::string& color_name);
    
    /**
     * @brief Add a scatter series with automatic styling (beginner-friendly)
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param name Series name for legend
     */
    void add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values,
                     const std::string& name);
    
    /**
     * @brief Add a scatter series with auto-generated name and styling
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     */
    void add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values);
    
    /**
     * @brief Add cluster data with automatic styling and naming (beginner-friendly)
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param labels Cluster labels for each point (-1 for outliers, 0+ for clusters)
     * 
     * Automatic naming: "Outliers", "Cluster 1", "Cluster 2", ...
     * Automatic coloring: Red cross for outliers, auto-colors for clusters
     */
    void add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                      const std::vector<int>& labels);
    
    /**
     * @brief Add cluster data with custom names and automatic coloring
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param labels Cluster labels for each point (-1 for outliers, 0+ for clusters)
     * @param names Custom names for each cluster (index corresponds to cluster label)
     * 
     * Note: names[0] = outlier name, names[1] = cluster 0 name, names[2] = cluster 1 name, etc.
     * Automatic coloring: Red cross for outliers, auto-colors for clusters
     */
    void add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                      const std::vector<int>& labels, const std::vector<std::string>& names);
    
    /**
     * @brief Add cluster data with custom names and colors (full control)
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param labels Cluster labels for each point (-1 for outliers, 0+ for clusters)
     * @param names Custom names for each cluster (index corresponds to cluster label)
     * @param colors Custom colors for each cluster (index corresponds to cluster label)
     * 
     * Note: names[0]/colors[0] = outlier, names[1]/colors[1] = cluster 0, etc.
     * Fixed markers: Red cross for outliers, circles for clusters
     */
    void add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                      const std::vector<int>& labels, const std::vector<std::string>& names, 
                      const std::vector<std::string>& colors);
};

} // namespace plotlib

#endif // PLOTLIB_SCATTER_PLOT_H
