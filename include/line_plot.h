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
 * std::vector<double> x_values = {1, 2, 3};
 * std::vector<double> y_values = {2, 4, 6};
 * plot.add_line(x_values, y_values, "Data", "red");
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
     * @brief Set line style for Cairo context
     * @param cr Cairo context
     * @param style Line style to apply
     * @param line_width Line width
     */
    void set_line_style(cairo_t* cr, LineStyle style, double line_width);
    
public:
    /**
     * @brief Constructor for LinePlot
     * @param width Canvas width in pixels (default: 800)
     * @param height Canvas height in pixels (default: 600)
     */
    LinePlot(int width = 800, int height = 600);
    
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~LinePlot() = default;
    
    /**
     * @brief Set the default line style for new series
     * @param style The line style to use as default
     */
    void set_default_line_style(LineStyle style);
    
    /**
     * @brief Set the default line width for new series
     * @param width Line width in pixels
     */
    void set_default_line_width(double width);
    
    /**
     * @brief Enable or disable markers at data points by default
     * @param enabled Whether to show markers by default
     */
    void set_default_show_markers(bool enabled);
    
    /**
     * @brief Set the default marker type when markers are enabled
     * @param marker_type The marker type to use
     */
    void set_default_marker_type(MarkerType marker_type);
    
    /**
     * @brief Add a line series with custom color (beginner-friendly)
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param name Series name for legend
     * @param color_name Color name {"blue", "green", "orange", "purple", "cyan", "magenta", "yellow", "red"}
     */
    void add_line(const std::vector<double>& x_values, const std::vector<double>& y_values,
                  const std::string& name, const std::string& color_name);
    
    /**
     * @brief Add a line series with automatic styling (beginner-friendly)
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     * @param name Series name for legend
     */
    void add_line(const std::vector<double>& x_values, const std::vector<double>& y_values,
                  const std::string& name);
    
    /**
     * @brief Add a line series with auto-generated name and styling
     * @param x_values Vector of X coordinates
     * @param y_values Vector of Y coordinates
     */
    void add_line(const std::vector<double>& x_values, const std::vector<double>& y_values);
};

} // namespace plotlib

#endif // PLOTLIB_LINE_PLOT_H 