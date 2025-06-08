/**
 * @file line_plot.h
 * @brief Line plot implementation using PlotManager
 * @author PlotLib Contributors
 * @version 1.0.0
 * @date 2025-06-08
 * 
 * This file contains the LinePlot class which extends PlotManager
 * to provide line plot specific functionality for connecting data points
 * with straight lines.
 */

#ifndef PLOTLIB_LINE_PLOT_H
#define PLOTLIB_LINE_PLOT_H

#include "plot_manager.h"

namespace plotlib {

/**
 * @brief Line plot class that extends PlotManager
 * 
 * The LinePlot class provides line plot functionality by inheriting
 * from PlotManager and implementing the draw_data method to render
 * data points connected by straight lines.
 * 
 * Features:
 * - Connects data points with straight lines
 * - Optional markers at data points
 * - Multiple line styles (solid, dashed, dotted)
 * - Configurable line width and colors
 * - All PlotManager features (axes, legends, titles, subplots)
 * 
 * @example
 * @code
 * LinePlot plot(800, 600);
 * plot.set_labels("My Line Plot", "X Values", "Y Values");
 * 
 * std::vector<Point2D> data = {{1, 2}, {2, 4}, {3, 6}};
 * PlotStyle style = {2.0, 1.0, 0.0, 0.0, 0.8}; // Red line
 * plot.add_series("Data", data, style);
 * 
 * plot.save_png("line.png");
 * @endcode
 */
class LinePlot : public PlotManager {
public:
    /**
     * @brief Line style enumeration
     */
    enum class LineStyle {
        SOLID,    ///< Solid line (default)
        DASHED,   ///< Dashed line
        DOTTED    ///< Dotted line
    };

private:
    LineStyle default_line_style = LineStyle::SOLID; ///< Default line style for new series
    double default_line_width = 2.0;                ///< Default line width
    bool show_markers = false;                       ///< Whether to show markers at data points
    MarkerType default_marker_type = MarkerType::CIRCLE; ///< Default marker type when enabled
    
protected:
    /**
     * @brief Draw line plot data
     * @param cr Cairo context for rendering
     * 
     * This method implements the pure virtual draw_data method from PlotManager
     * to render line plots by connecting data points with straight lines.
     */
    void draw_data(cairo_t* cr) override;
    
    /**
     * @brief Draw lines connecting data points
     * @param cr Cairo context for rendering
     */
    void draw_lines(cairo_t* cr);
    
    /**
     * @brief Draw markers at data points (if enabled)
     * @param cr Cairo context for rendering
     */
    void draw_markers(cairo_t* cr);
    
    /**
     * @brief Draw cluster-based line data
     * @param cr Cairo context for rendering
     */
    void draw_cluster_lines(cairo_t* cr);
    
    /**
     * @brief Set line style for Cairo context
     * @param cr Cairo context
     * @param style Line style to apply
     * @param line_width Line width
     */
    void set_line_style(cairo_t* cr, LineStyle style, double line_width);
    
public:
    /**
     * @brief Constructor for LinePlot
     * @param w Canvas width in pixels (default: 800)
     * @param h Canvas height in pixels (default: 600)
     */
    LinePlot(int w = 800, int h = 600);
    
    /**
     * @brief Set the default line style for new series
     * @param style The line style to use as default
     */
    void set_default_line_style(LineStyle style);
    
    /**
     * @brief Get the current default line style
     * @return The current default line style
     */
    LineStyle get_default_line_style() const { return default_line_style; }
    
    /**
     * @brief Set the default line width for new series
     * @param width Line width in pixels
     */
    void set_default_line_width(double width);
    
    /**
     * @brief Get the current default line width
     * @return The current default line width
     */
    double get_default_line_width() const { return default_line_width; }
    
    /**
     * @brief Enable or disable markers at data points
     * @param enabled Whether to show markers
     */
    void set_show_markers(bool enabled);
    
    /**
     * @brief Check if markers are enabled
     * @return True if markers are shown
     */
    bool get_show_markers() const { return show_markers; }
    
    /**
     * @brief Set the default marker type when markers are enabled
     * @param marker_type The marker type to use
     */
    void set_default_marker_type(MarkerType marker_type);
    
    /**
     * @brief Get the current default marker type
     * @return The current default marker type
     */
    MarkerType get_default_marker_type() const { return default_marker_type; }
    
    /**
     * @brief Add a simple line series with automatic styling (beginner-friendly)
     * @param name Series name for legend
     * @param data Vector of 2D points
     */
    void add_line(const std::string& name, const std::vector<Point2D>& data);
    
    /**
     * @brief Add a simple line series with custom color (beginner-friendly)
     * @param name Series name for legend
     * @param data Vector of 2D points
     * @param color_name Color name ("red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow")
     */
    void add_line(const std::string& name, const std::vector<Point2D>& data, const std::string& color_name);
    
    /**
     * @brief Add line from X and Y vectors (beginner-friendly)
     * @param name Series name for legend
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param color_name Optional color name
     */
    void add_line(const std::string& name, const std::vector<double>& x_values, 
                  const std::vector<double>& y_values, const std::string& color_name = "auto");
};

} // namespace plotlib

// For backward compatibility, bring LinePlot into global namespace
using plotlib::LinePlot;

#endif // PLOTLIB_LINE_PLOT_H 