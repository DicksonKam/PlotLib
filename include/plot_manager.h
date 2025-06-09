/**
 * @file plot_manager.h
 * @brief Core plotting management system for PlotLib
 * @author PlotLib Contributors
 * @version 1.0.0
 * @date 2025-06-08
 * 
 * This file contains the PlotManager class which serves as the central controller
 * for all plotting functionality including axis management, legends, titles,
 * subplot positioning, and rendering coordination.
 */

#ifndef PLOTLIB_PLOT_MANAGER_H
#define PLOTLIB_PLOT_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <set>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cairo.h>
#include <cairo-svg.h>

namespace plotlib {

// Forward declarations
class ScatterPlot;
class LinePlot;
class HistogramPlot;

/**
 * @brief Represents a 2D point with x and y coordinates
 */
struct Point2D {
    double x; ///< X coordinate
    double y; ///< Y coordinate
    
    /**
     * @brief Constructor for Point2D
     * @param x_val X coordinate (default: 0.0)
     * @param y_val Y coordinate (default: 0.0)
     */
    Point2D(double x_val = 0.0, double y_val = 0.0) : x(x_val), y(y_val) {}
};

/**
 * @brief Styling configuration for plot elements
 */
struct PlotStyle {
    double point_size = 3.0;           ///< Point radius in pixels
    double line_width = 2.0;           ///< Line width in pixels
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
 * @brief Represents a named data series with styling information
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
 * @brief Represents a data point with cluster label information
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
 * @brief Represents a cluster-based data series for clustering visualization
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

/**
 * @brief Represents a reference line (vertical or horizontal) with styling
 */
struct ReferenceLine {
    bool is_vertical;           ///< True for vertical line, false for horizontal
    double value;               ///< X value for vertical line, Y value for horizontal line
    PlotStyle style;            ///< Visual styling for the reference line
    std::string label;          ///< Label for legend
    
    /**
     * @brief Constructor for ReferenceLine
     * @param vertical True for vertical line, false for horizontal
     * @param val The X or Y value where the line should be drawn
     * @param line_label Label for the legend (default: auto-generated)
     * @param line_style Visual styling (default: dotted black line)
     */
    ReferenceLine(bool vertical, double val, const std::string& line_label = "", 
                  const PlotStyle& line_style = PlotStyle()) 
        : is_vertical(vertical), value(val), style(line_style), label(line_label) {
        // Set default dotted line style if not specified
        if (style.line_width == 2.0 && style.r == 0.0 && style.g == 0.0 && style.b == 1.0) {
            style.r = 0.0; style.g = 0.0; style.b = 0.0;  // Black color
            style.line_width = 1.5;
            style.alpha = 0.8;
        }
        
        // Auto-generate label if not provided
        if (label.empty()) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << val;
            std::string val_str = oss.str();
            // Remove trailing zeros
            val_str.erase(val_str.find_last_not_of('0') + 1, std::string::npos);
            val_str.erase(val_str.find_last_not_of('.') + 1, std::string::npos);
            label = is_vertical ? ("X = " + val_str) : ("Y = " + val_str);
        }
    }
};

/**
 * @brief Central plot management class that handles all common plotting functionality
 * 
 * The PlotManager class serves as the foundation for all plot types in PlotLib.
 * It manages axes, legends, titles, data bounds, transformations, and rendering
 * coordination. Specific plot types (scatter, line, bar, etc.) inherit from or
 * use this class to access common functionality.
 * 
 * Key responsibilities:
 * - Axis management (scaling, ticks, labels, grid)
 * - Legend positioning and rendering
 * - Title and label management
 * - Data bounds calculation and transformation
 * - Canvas and margin management
 * - Subplot positioning and coordination
 * - File output (PNG, SVG)
 * 
 * @example
 * @code
 * PlotManager manager(800, 600);
 * manager.set_labels("My Plot", "X Axis", "Y Axis");
 * manager.add_data_series("Series 1", data_points, style);
 * manager.save_png("output.png");
 * @endcode
 */
class PlotManager {
protected:
    // Canvas and layout settings
    int width, height;                        ///< Canvas dimensions in pixels
    double margin_left = 80, margin_right = 150;  ///< Margins for labels and legend
    double margin_top = 60, margin_bottom = 80;   ///< Top and bottom margins
    
    // Data storage
    std::vector<DataSeries> data_series;      ///< Collection of regular data series
    std::vector<ClusterSeries> cluster_series; ///< Collection of cluster-based series
    std::vector<ReferenceLine> reference_lines; ///< Collection of reference lines
    
    // Data bounds and transformation
    double min_x, max_x, min_y, max_y;        ///< Data range for axis scaling
    bool bounds_set = false;                  ///< Whether bounds were manually set
    
    // Plot labels and titles
    std::string title = "";                   ///< Main plot title
    std::string x_label = "";                 ///< X-axis label
    std::string y_label = "";                 ///< Y-axis label
    
    // Cluster color management
    std::vector<std::vector<double>> cluster_colors; ///< RGB colors for cluster visualization
    
    // Auto color management for series
    static std::vector<std::string> auto_colors; ///< Centralized auto colors for all plot types
    
    // Legend management
    std::set<std::string> hidden_legend_items; ///< Set of legend items to hide
    bool show_legend = true;                  ///< Whether to show legend at all
    
    // Subplot support
    bool is_subplot = false;                  ///< Whether this plot is part of a subplot grid
    double subplot_x_offset = 0;             ///< X offset for subplot positioning
    double subplot_y_offset = 0;             ///< Y offset for subplot positioning
    double subplot_width_scale = 1.0;        ///< Width scaling factor for subplots
    double subplot_height_scale = 1.0;       ///< Height scaling factor for subplots
    
    // Core functionality methods
    virtual void calculate_bounds();
    virtual void transform_point(double data_x, double data_y, double& screen_x, double& screen_y);
    
    // Rendering methods
    virtual void draw_axes(cairo_t* cr);
    virtual void draw_axis_labels(cairo_t* cr);
    virtual void draw_axis_ticks(cairo_t* cr);
    virtual void draw_grid(cairo_t* cr);
    virtual void draw_reference_lines(cairo_t* cr);
    virtual void draw_legend(cairo_t* cr);
    virtual void draw_title(cairo_t* cr);
    virtual void draw_marker(cairo_t* cr, double x, double y, MarkerType type, double size, 
                           double r, double g, double b, double alpha);
    
    // Plot-specific rendering (to be implemented by derived classes)
    virtual void draw_data(cairo_t* cr) = 0;
    
    // Subplot support methods
    virtual void set_subplot_transform(double x_offset, double y_offset, 
                                     double width_scale, double height_scale);
    virtual void render_to_context(cairo_t* cr);
    
    // Utility methods
    std::string format_number(double value, int precision = 2);
    std::vector<double> generate_nice_ticks(double min_val, double max_val, int target_ticks = 5);
    void initialize_cluster_colors();
    std::vector<double> get_cluster_color(int cluster_label);
    
public:
    /**
     * @brief Constructor for PlotManager
     * @param width Canvas width in pixels (default: 800)
     * @param height Canvas height in pixels (default: 600)
     */
    PlotManager(int width = 800, int height = 600);
    
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~PlotManager() = default;
    
    // Data management methods
    
    /**
     * @brief Add a data series to the plot
     * @param name Series name for legend
     * @param points Vector of 2D data points
     * @param style Visual styling for the series
     */
    virtual void add_series(const std::string& name, const std::vector<Point2D>& points, 
                           const PlotStyle& style);
    
    /**
     * @brief Add a single point to an existing or new series
     * @param series_name Name of the series
     * @param x X coordinate
     * @param y Y coordinate
     */
    virtual void add_series_point(const std::string& series_name, double x, double y);
    
    /**
     * @brief Add cluster-based data for clustering visualization
     * @param name Series name for legend
     * @param points Vector of 2D data points
     * @param cluster_labels Vector of cluster labels (same size as points)
     * @param point_size Size of cluster points (default: 3.0)
     * @param alpha Transparency of cluster points (default: 0.8)
     */
    virtual void add_cluster_data(const std::string& name, const std::vector<Point2D>& points, 
                                 const std::vector<int>& cluster_labels, 
                                 double point_size = 3.0, double alpha = 0.8);
    
    /**
     * @brief Add a single cluster point to an existing or new cluster series
     * @param series_name Name of the cluster series
     * @param x X coordinate
     * @param y Y coordinate
     * @param cluster_label Cluster label (-1 for outliers, 0+ for clusters)
     */
    virtual void add_cluster_point(const std::string& series_name, double x, double y, int cluster_label);
    
    // Label and title management
    
    /**
     * @brief Set the main plot title
     * @param plot_title Title text
     */
    virtual void set_title(const std::string& plot_title);
    
    /**
     * @brief Set the X-axis label
     * @param x_axis_label X-axis label text
     */
    virtual void set_xlabel(const std::string& x_axis_label);
    
    /**
     * @brief Set the Y-axis label
     * @param y_axis_label Y-axis label text
     */
    virtual void set_ylabel(const std::string& y_axis_label);
    
    /**
     * @brief Set all labels at once
     * @param plot_title Main plot title
     * @param x_axis_label X-axis label
     * @param y_axis_label Y-axis label
     */
    virtual void set_labels(const std::string& plot_title, const std::string& x_axis_label, 
                           const std::string& y_axis_label);
    
    // Bounds management
    
    /**
     * @brief Manually set the data bounds for the plot
     * @param min_x Minimum X value
     * @param max_x Maximum X value
     * @param min_y Minimum Y value
     * @param max_y Maximum Y value
     */
    virtual void set_bounds(double min_x, double max_x, double min_y, double max_y);
    
    // Output methods
    
    /**
     * @brief Save the plot as a PNG file
     * @param filename Output filename
     * @return true if successful, false otherwise
     */
    virtual bool save_png(const std::string& filename);
    
    /**
     * @brief Save the plot as an SVG file
     * @param filename Output filename
     * @return true if successful, false otherwise
     */
    virtual bool save_svg(const std::string& filename);
    
    // Utility methods
    
    /**
     * @brief Clear all data and reset labels
     */
    virtual void clear();
    
    // Legend management methods
    
    /**
     * @brief Enable or disable the legend display
     * @param enabled Whether to show the legend
     */
    virtual void set_legend_enabled(bool enabled);
    
    /**
     * @brief Hide a specific legend item
     * @param item_name Name of the legend item to hide
     */
    virtual void hide_legend_item(const std::string& item_name);
    
    /**
     * @brief Show a specific legend item (remove from hidden list)
     * @param item_name Name of the legend item to show
     */
    virtual void show_legend_item(const std::string& item_name);
    
    /**
     * @brief Clear all hidden legend items (show all)
     */
    virtual void show_all_legend_items();
    
    // Reference line management methods
    
    /**
     * @brief Add a vertical reference line
     * @param x_value X coordinate where the vertical line should be drawn
     * @param label Label for the legend
     * @param color_name Color name ("red", "blue", "green", etc.)
     */
    virtual void add_vertical_line(double x_value, const std::string& label, const std::string& color_name);
    
    /**
     * @brief Add a horizontal reference line
     * @param y_value Y coordinate where the horizontal line should be drawn
     * @param label Label for the legend
     * @param color_name Color name ("red", "blue", "green", etc.)
     */
    virtual void add_horizontal_line(double y_value, const std::string& label, const std::string& color_name);
    
    /**
     * @brief Add a vertical reference line with auto-generated label
     * @param x_value X coordinate where the vertical line should be drawn
     * @param label Label for the legend (optional)
     */
    virtual void add_vertical_line(double x_value, const std::string& label = "");
    
    /**
     * @brief Add a horizontal reference line with auto-generated label
     * @param y_value Y coordinate where the horizontal line should be drawn
     * @param label Label for the legend (optional)
     */
    virtual void add_horizontal_line(double y_value, const std::string& label = "");
    
    /**
     * @brief Add a vertical reference line (value only)
     * @param x_value X coordinate where the vertical line should be drawn
     */
    virtual void add_vertical_line(double x_value);
    
    /**
     * @brief Add a horizontal reference line (value only)
     * @param y_value Y coordinate where the horizontal line should be drawn
     */
    virtual void add_horizontal_line(double y_value);
    
    /**
     * @brief Add a reference line (vertical or horizontal)
     * @param is_vertical True for vertical line, false for horizontal
     * @param value X value for vertical line, Y value for horizontal line
     * @param label Label for the legend (default: auto-generated)
     * @param style Visual styling (default: dotted black line)
     */
    virtual void add_reference_line(bool is_vertical, double value, const std::string& label = "", 
                                   const PlotStyle& style = PlotStyle());
    
    /**
     * @brief Clear all reference lines
     */
    virtual void clear_reference_lines();
    
    /**
     * @brief Get the number of reference lines
     * @return Number of reference lines
     */
    size_t get_reference_line_count() const { return reference_lines.size(); }
    
    /**
     * @brief Convert color name to PlotStyle (utility for beginner-friendly API)
     * @param color_name Color name string
     * @param point_size Point size for scatter plots
     * @param line_width Line width for line plots
     * @return PlotStyle with the specified color
     */
    static PlotStyle color_to_style(const std::string& color_name, double point_size = 3.0, double line_width = 2.0);
    
    /**
     * @brief Get auto color for series index (utility for beginner-friendly API)
     * @param series_index Index of the data series
     * @return Color name string
     */
    static std::string get_auto_color(size_t series_index);
    
    /**
     * @brief Get the number of data series
     * @return Number of regular data series
     */
    size_t get_series_count() const { return data_series.size(); }
    
    /**
     * @brief Get the number of cluster series
     * @return Number of cluster series
     */
    size_t get_cluster_series_count() const { return cluster_series.size(); }
    
    // Friend classes for subplot management
    friend class SubplotManager;
};

/**
 * @brief Defines the layout configuration for subplot grids
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
 * @brief Manages multiple plots in a grid layout
 * 
 * The SubplotManager class coordinates multiple PlotManager instances
 * in a grid layout, handling positioning, scaling, and unified rendering.
 * It supports various subplot configurations and maintains proper aspect
 * ratios and spacing.
 */
class SubplotManager {
private:
    std::vector<std::vector<std::unique_ptr<PlotManager>>> subplots; ///< Grid of subplot instances
    int rows, cols;                                                  ///< Grid dimensions
    int total_width, total_height;                                   ///< Total canvas size
    double spacing;                                                  ///< Spacing between subplots
    std::string main_title = "";                                     ///< Main title for entire figure
    
    // Helper methods
    double get_title_height(cairo_t* cr);
    
public:
    /**
     * @brief Constructor for SubplotManager
     * @param rows Number of subplot rows
     * @param cols Number of subplot columns
     * @param width Total canvas width (default: 1200)
     * @param height Total canvas height (default: 900)
     * @param spacing Spacing between subplots (default: 0.05)
     */
    SubplotManager(int rows, int cols, int width = 1200, int height = 900, double spacing = 0.05);
    
    /**
     * @brief Get a reference to a specific subplot
     * @param row Row index (0-based)
     * @param col Column index (0-based)
     * @return Reference to the PlotManager at the specified position
     * @throws std::out_of_range if indices are invalid
     */
    template<typename PlotType>
    PlotType& get_subplot(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Subplot indices out of range");
        }
        
        if (!subplots[row][col]) {
            // Create a new subplot of the specified type with standard size
            // Positioning will be calculated dynamically during rendering
            subplots[row][col] = std::make_unique<PlotType>(800, 600);
        }
        
        return static_cast<PlotType&>(*subplots[row][col]);
    }
    
    /**
     * @brief Set a specific subplot to a particular plot type
     * @param row Row index (0-based)
     * @param col Column index (0-based)
     * @param plot_instance Unique pointer to the plot instance
     */
    template<typename PlotType>
    void set_subplot(int row, int col, std::unique_ptr<PlotType> plot_instance) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Subplot indices out of range");
        }
        
        subplots[row][col] = std::move(plot_instance);
        // Positioning will be calculated dynamically during rendering
    }
    
    /**
     * @brief Get a reference to a specific subplot (defaults to ScatterPlot)
     * @param row Row index (0-based)
     * @param col Column index (0-based)
     * @return Reference to the ScatterPlot at the specified position
     * @throws std::out_of_range if indices are invalid
     */
    ScatterPlot& get_subplot(int row, int col);
    
    /**
     * @brief Set the main title for the entire subplot figure
     * @param title Main title text
     */
    void set_main_title(const std::string& title);
    
    /**
     * @brief Save the complete subplot figure as PNG
     * @param filename Output filename
     * @return true if successful, false otherwise
     */
    bool save_png(const std::string& filename);
    
    /**
     * @brief Save the complete subplot figure as SVG
     * @param filename Output filename
     * @return true if successful, false otherwise
     */
    bool save_svg(const std::string& filename);
    
    /**
     * @brief Get the number of rows in the subplot grid
     * @return Number of rows
     */
    int get_rows() const { return rows; }
    
    /**
     * @brief Get the number of columns in the subplot grid
     * @return Number of columns
     */
    int get_cols() const { return cols; }
    
    /**
     * @brief Render the complete subplot figure to a Cairo context
     * @param cr Cairo context for rendering
     */
    void render_to_context(cairo_t* cr);
};

} // namespace plotlib

#endif // PLOTLIB_PLOT_MANAGER_H 