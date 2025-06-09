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

namespace plotlib {

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
 * std::vector<Point2D> data = {{1, 2}, {2, 4}, {3, 6}};
 * PlotStyle style = {3.0, 1.0, 0.0, 0.0, 0.8}; // Red circles
 * plot.add_series("Data", data, style);
 * 
 * plot.save_png("scatter.png");
 * @endcode
 */
class ScatterPlot : public PlotManager {
private:
    MarkerType default_marker_type = MarkerType::CIRCLE; ///< Default marker type for new series
    
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
    
public:
    /**
     * @brief Constructor for ScatterPlot
     * @param w Canvas width in pixels (default: 800)
     * @param h Canvas height in pixels (default: 600)
     */
    ScatterPlot(int w = 800, int h = 600);
    
    /**
     * @brief Set the default marker type for new series
     * @param marker_type The marker type to use as default
     */
    void set_default_marker_type(MarkerType marker_type);
    
    /**
     * @brief Add a scatter series with automatic styling (beginner-friendly)
     * @param name Series name for legend
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     */
    void add_scatter(const std::string& name, const std::vector<double>& x_values, 
                     const std::vector<double>& y_values);
    
    /**
     * @brief Add a scatter series with custom color (beginner-friendly)
     * @param name Series name for legend
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param color_name Color name ("red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow")
     */
    void add_scatter(const std::string& name, const std::vector<double>& x_values, 
                     const std::vector<double>& y_values, const std::string& color_name);
    
    /**
     * @brief Add cluster data with automatic styling (beginner-friendly)
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param labels Cluster labels for each point (-1 for outliers, 0+ for clusters)
     */
    void add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                      const std::vector<int>& labels);
};

} // namespace plotlib

#endif // PLOTLIB_SCATTER_PLOT_H
