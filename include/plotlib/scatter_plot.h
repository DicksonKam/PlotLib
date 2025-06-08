/**
 * @file scatter_plot.h
 * @brief Enhanced C++ scatter plot library with Cairo graphics
 * @author Plotting Library Team
 * @version 1.0
 * @date 2025
 * 
 * A comprehensive C++ library for creating beautiful scatter plots with automatic 
 * axis scaling, legends, clustering support, and subplot functionality using Cairo graphics.
 */

#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <cairo.h>
#include <cairo-svg.h>

/**
 * @brief Represents a 2D point with x and y coordinates
 * 
 * Simple structure to hold 2D coordinate data for plotting.
 */
struct Point2D {
    double x; ///< X coordinate
    double y; ///< Y coordinate
    
    /**
     * @brief Constructor for Point2D
     * @param x X coordinate (default: 0)
     * @param y Y coordinate (default: 0)
     */
    Point2D(double x = 0, double y = 0) : x(x), y(y) {}
};

/**
 * @brief Defines the visual style for plot points
 * 
 * Contains all styling information for rendering data points including
 * size, color, transparency, and legend label.
 */
struct PlotStyle {
    double point_size = 3.0;           ///< Point radius in pixels
    double r = 0.0, g = 0.0, b = 1.0;  ///< RGB color values (0.0 to 1.0), blue by default
    double alpha = 1.0;                ///< Transparency (0.0 = transparent, 1.0 = opaque)
    std::string label = "";            ///< Label for legend (optional)
};

/**
 * @brief Enumeration of available marker types for data points
 */
enum class MarkerType {
    CIRCLE,   ///< Circular markers (default)
    CROSS,    ///< Cross-shaped markers (used for outliers)
    SQUARE,   ///< Square markers
    TRIANGLE  ///< Triangular markers
};

/**
 * @brief Represents a data point with cluster label information
 * 
 * Used for clustering visualization where each point belongs to a specific
 * cluster or is marked as an outlier (label = -1).
 */
struct ClusterPoint {
    Point2D point;        ///< 2D coordinates of the point
    int cluster_label;    ///< Cluster ID (0, 1, 2, ...) or -1 for outliers
    
    /**
     * @brief Constructor from coordinates and label
     * @param x X coordinate
     * @param y Y coordinate  
     * @param label Cluster label (-1 for outliers, 0+ for clusters)
     */
    ClusterPoint(double x, double y, int label) : point(x, y), cluster_label(label) {}
    
    /**
     * @brief Constructor from Point2D and label
     * @param pt 2D point coordinates
     * @param label Cluster label (-1 for outliers, 0+ for clusters)
     */
    ClusterPoint(const Point2D& pt, int label) : point(pt), cluster_label(label) {}
};

/**
 * @brief Represents a named data series with styling information
 * 
 * Groups related data points together with a common style and name
 * for legend display and organization.
 */
struct DataSeries {
    std::vector<Point2D> points; ///< Collection of 2D data points
    PlotStyle style;             ///< Visual styling for this series
    std::string name;            ///< Series name for legend
    
    /**
     * @brief Constructor for DataSeries
     * @param series_name Name of the data series (default: empty)
     */
    DataSeries(const std::string& series_name = "") : name(series_name) {}
};

/**
 * @brief Represents a cluster-based data series for clustering visualization
 * 
 * Contains points with cluster labels for automatic color assignment
 * and outlier detection in clustering analysis.
 */
struct ClusterSeries {
    std::vector<ClusterPoint> points; ///< Collection of cluster-labeled points
    std::string name;                 ///< Series name for legend
    double point_size = 3.0;          ///< Size of cluster points
    double alpha = 0.8;               ///< Transparency of cluster points
    
    /**
     * @brief Constructor for ClusterSeries
     * @param series_name Name of the cluster series (default: empty)
     */
    ClusterSeries(const std::string& series_name = "") : name(series_name) {}
};

// Forward declaration
class ScatterPlot;

/**
 * @brief Defines the layout configuration for subplot grids
 * 
 * Specifies the grid dimensions and spacing for organizing multiple
 * plots in a single figure.
 */
struct SubplotLayout {
    int rows;                    ///< Number of subplot rows
    int cols;                    ///< Number of subplot columns
    double spacing = 0.05;       ///< Spacing between subplots as fraction of total size
    
    /**
     * @brief Constructor for SubplotLayout
     * @param r Number of rows in the subplot grid
     * @param c Number of columns in the subplot grid
     * @param s Spacing between subplots (default: 0.05)
     */
    SubplotLayout(int r, int c, double s = 0.05) : rows(r), cols(c), spacing(s) {}
};

/**
 * @brief Main scatter plot class for creating and rendering 2D data visualizations
 * 
 * The ScatterPlot class provides comprehensive functionality for creating beautiful
 * scatter plots with automatic axis scaling, legends, multiple data series, and
 * clustering support. It uses Cairo graphics for high-quality rendering to PNG and SVG.
 * 
 * Key features:
 * - Automatic axis scaling and tick generation
 * - Multiple data series with custom styling
 * - Cluster-based visualization with automatic coloring
 * - Legend support with automatic positioning
 * - Grid lines aligned with axis ticks
 * - Professional axis labels and titles
 * - Support for both PNG and SVG output formats
 * 
 * @example
 * @code
 * ScatterPlot plot(800, 600);
 * plot.set_labels("My Plot", "X Axis", "Y Axis");
 * 
 * std::vector<Point2D> data = {{1, 2}, {2, 4}, {3, 6}};
 * PlotStyle style = {3.0, 1.0, 0.0, 0.0, 0.8}; // Red points
 * plot.add_series("Data", data, style);
 * 
 * plot.save_png("my_plot.png");
 * @endcode
 */
class ScatterPlot {
    friend class SubplotManager;
private:
    // Data storage
    std::vector<DataSeries> data_series;      ///< Collection of regular data series
    std::vector<ClusterSeries> cluster_series; ///< Collection of cluster-based series
    
    // Plot area settings
    int width, height;                        ///< Canvas dimensions in pixels
    double margin_left = 80, margin_right = 150;  ///< Margins for labels and legend
    double margin_top = 60, margin_bottom = 80;   ///< Top and bottom margins
    
    // Data bounds
    double min_x, max_x, min_y, max_y;        ///< Data range for axis scaling
    bool bounds_set = false;                  ///< Whether bounds were manually set
    
    // Plot labels
    std::string title = "";                   ///< Main plot title
    std::string x_label = "";                 ///< X-axis label
    std::string y_label = "";                 ///< Y-axis label
    
    // Cluster color palette
    std::vector<std::vector<double>> cluster_colors; ///< RGB colors for cluster visualization
    
    // Subplot support
    bool is_subplot = false;                  ///< Whether this plot is part of a subplot grid
    double subplot_x_offset = 0;             ///< X offset for subplot positioning
    double subplot_y_offset = 0;             ///< Y offset for subplot positioning
    double subplot_width_scale = 1.0;        ///< Width scaling factor for subplots
    double subplot_height_scale = 1.0;       ///< Height scaling factor for subplots
    
    // Helper functions
    void calculate_bounds();
    void transform_point(double data_x, double data_y, double& screen_x, double& screen_y);
    void draw_axes(cairo_t* cr);
    void draw_axis_labels(cairo_t* cr);
    void draw_axis_ticks(cairo_t* cr);
    void draw_grid(cairo_t* cr);
    void draw_points(cairo_t* cr);
    void draw_cluster_points(cairo_t* cr);
    void draw_legend(cairo_t* cr);
    void draw_title(cairo_t* cr);
    void draw_marker(cairo_t* cr, double x, double y, MarkerType type, double size, double r, double g, double b, double alpha);
    
    // Subplot helper functions
    void set_subplot_transform(double x_offset, double y_offset, double width_scale, double height_scale);
    void render_to_context(cairo_t* cr);
    
    // Utility functions
    std::string format_number(double value, int precision = 2);
    std::vector<double> generate_nice_ticks(double min_val, double max_val, int target_ticks = 5);
    void initialize_cluster_colors();
    std::vector<double> get_cluster_color(int cluster_label);
    
public:
    /**
     * @brief Constructor for ScatterPlot
     * @param w Canvas width in pixels (default: 800)
     * @param h Canvas height in pixels (default: 600)
     */
    ScatterPlot(int w = 800, int h = 600);
    
    // Add data points (legacy methods for backward compatibility)
    
    /**
     * @brief Add a single data point (legacy method)
     * @param x X coordinate
     * @param y Y coordinate
     * @param style Visual style for the point (default: blue circle)
     * @deprecated Use add_series() for better organization and legend support
     */
    void add_point(double x, double y, const PlotStyle& style = PlotStyle());
    
    /**
     * @brief Add multiple data points (legacy method)
     * @param pts Vector of 2D points
     * @param style Visual style for all points (default: blue circles)
     * @deprecated Use add_series() for better organization and legend support
     */
    void add_points(const std::vector<Point2D>& pts, const PlotStyle& style = PlotStyle());
    
    // Enhanced methods for series-based data
    
    /**
     * @brief Add a complete data series with styling
     * @param name Series name for legend
     * @param points Vector of 2D data points
     * @param style Visual styling for the series
     * 
     * This is the recommended method for adding data as it provides
     * proper legend support and series organization.
     */
    void add_series(const std::string& name, const std::vector<Point2D>& points, const PlotStyle& style);
    
    /**
     * @brief Add a single point to an existing or new series
     * @param series_name Name of the series to add to
     * @param x X coordinate
     * @param y Y coordinate
     * 
     * If the series doesn't exist, it will be created with default styling.
     */
    void add_series_point(const std::string& series_name, double x, double y);
    
    // Cluster-based methods
    
    /**
     * @brief Add cluster data with automatic color assignment
     * @param name Series name for legend
     * @param points Vector of 2D data points
     * @param cluster_labels Vector of cluster labels (same size as points)
     * @param point_size Size of cluster points (default: 3.0)
     * @param alpha Transparency of points (default: 0.8)
     * 
     * Cluster labels should be:
     * - -1 for outliers (displayed as red crosses)
     * - 0, 1, 2, ... for different clusters (automatic colors)
     */
    void add_cluster_data(const std::string& name, const std::vector<Point2D>& points, const std::vector<int>& cluster_labels, double point_size = 3.0, double alpha = 0.8);
    
    /**
     * @brief Add a single cluster point to an existing or new series
     * @param series_name Name of the cluster series
     * @param x X coordinate
     * @param y Y coordinate
     * @param cluster_label Cluster ID (-1 for outliers, 0+ for clusters)
     */
    void add_cluster_point(const std::string& series_name, double x, double y, int cluster_label);
    
    // Set plot labels
    
    /**
     * @brief Set the main plot title
     * @param plot_title Title text to display at the top of the plot
     */
    void set_title(const std::string& plot_title);
    
    /**
     * @brief Set the X-axis label
     * @param x_axis_label Label text for the X-axis
     */
    void set_xlabel(const std::string& x_axis_label);
    
    /**
     * @brief Set the Y-axis label
     * @param y_axis_label Label text for the Y-axis
     */
    void set_ylabel(const std::string& y_axis_label);
    
    /**
     * @brief Set all plot labels at once
     * @param plot_title Main plot title
     * @param x_axis_label X-axis label
     * @param y_axis_label Y-axis label
     */
    void set_labels(const std::string& plot_title, const std::string& x_axis_label, const std::string& y_axis_label);
    
    // Set plot bounds manually
    
    /**
     * @brief Manually set the axis bounds
     * @param min_x Minimum X value
     * @param max_x Maximum X value
     * @param min_y Minimum Y value
     * @param max_y Maximum Y value
     * 
     * By default, bounds are calculated automatically from the data.
     * Use this method to override automatic scaling.
     */
    void set_bounds(double min_x, double max_x, double min_y, double max_y);
    
    // Save plot to file
    
    /**
     * @brief Save the plot as a PNG image
     * @param filename Output filename (should end with .png)
     * @return true if successful, false otherwise
     */
    bool save_png(const std::string& filename);
    
    /**
     * @brief Save the plot as an SVG vector image
     * @param filename Output filename (should end with .svg)
     * @return true if successful, false otherwise
     */
    bool save_svg(const std::string& filename);
    
    // Clear all data
    
    /**
     * @brief Clear all data and reset labels
     * 
     * Removes all data series, cluster series, and resets
     * titles and labels to empty strings.
     */
    void clear();
    
    // Create a copy of this plot (for subplots)
    
    /**
     * @brief Create a deep copy of this plot
     * @return Unique pointer to the cloned plot
     * @note Used internally by SubplotManager
     */
    std::unique_ptr<ScatterPlot> clone() const;
};

/**
 * @brief Manager class for creating and organizing multiple subplots in a grid layout
 * 
 * The SubplotManager allows you to create complex data visualization dashboards
 * by organizing multiple ScatterPlot instances in a grid layout. Each subplot
 * maintains full functionality while being properly scaled and positioned.
 * 
 * Features:
 * - Flexible grid layouts (MxN subplots)
 * - Automatic scaling and positioning with aspect ratio preservation
 * - Main title support for the entire figure
 * - Configurable spacing between subplots
 * - Proper centering of the entire "title + subplots" group
 * - Independent data management for each subplot
 * 
 * @example
 * @code
 * SubplotManager manager(2, 2, 1200, 1000);
 * manager.set_main_title("Data Analysis Dashboard");
 * 
 * auto& plot1 = manager.get_subplot(0, 0);
 * plot1.set_labels("Plot 1", "X", "Y");
 * plot1.add_series("Data", data1, style1);
 * 
 * auto& plot2 = manager.get_subplot(0, 1);
 * plot2.set_labels("Plot 2", "X", "Y");
 * plot2.add_cluster_data("Clusters", points, labels);
 * 
 * manager.save_png("dashboard.png");
 * @endcode
 */
class SubplotManager {
private:
    std::vector<std::vector<std::unique_ptr<ScatterPlot>>> subplots; ///< 2D grid of subplot instances
    SubplotLayout layout;                                           ///< Grid layout configuration
    int total_width, total_height;                                  ///< Total canvas dimensions
    std::string main_title = "";                                    ///< Main title for entire figure
    
public:
    /**
     * @brief Constructor for SubplotManager
     * @param rows Number of subplot rows
     * @param cols Number of subplot columns
     * @param width Total canvas width in pixels (default: 1200)
     * @param height Total canvas height in pixels (default: 900)
     * @param spacing Spacing between subplots as fraction of total size (default: 0.05)
     */
    SubplotManager(int rows, int cols, int width = 1200, int height = 900, double spacing = 0.05);
    
    /**
     * @brief Get a reference to a specific subplot for modification
     * @param row Row index (0-based)
     * @param col Column index (0-based)
     * @return Reference to the ScatterPlot at the specified position
     * @throws std::out_of_range if indices are invalid
     */
    ScatterPlot& get_subplot(int row, int col);
    
    /**
     * @brief Set the main title for the entire subplot figure
     * @param title Main title text to display at the top
     */
    void set_main_title(const std::string& title);
    
    /**
     * @brief Save the entire subplot figure as a PNG image
     * @param filename Output filename (should end with .png)
     * @return true if successful, false otherwise
     */
    bool save_png(const std::string& filename);
    
    /**
     * @brief Save the entire subplot figure as an SVG vector image
     * @param filename Output filename (should end with .svg)
     * @return true if successful, false otherwise
     */
    bool save_svg(const std::string& filename);
    
    /**
     * @brief Get the number of subplot rows
     * @return Number of rows in the grid
     */
    int get_rows() const { return layout.rows; }
    
    /**
     * @brief Get the number of subplot columns
     * @return Number of columns in the grid
     */
    int get_cols() const { return layout.cols; }
    
private:
    /**
     * @brief Render all subplots to a Cairo context
     * @param cr Cairo graphics context
     */
    void render_to_context(cairo_t* cr);
    
    /**
     * @brief Calculate the height needed for the main title
     * @param cr Cairo graphics context
     * @return Title height in pixels (0 if no title)
     */
    double get_title_height(cairo_t* cr) const;
};

#endif
