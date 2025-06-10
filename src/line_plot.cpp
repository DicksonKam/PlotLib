#include "line_plot.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>

namespace plotlib {

LinePlot::LinePlot(int width, int height) : PlotManager(width, height) {
    // Constructor delegates to PlotManager
}

void LinePlot::set_default_line_style(LineStyle style) {
    default_line_style = style;
}

void LinePlot::set_default_line_width(double width) {
    default_line_width = width;
}

void LinePlot::set_default_show_markers(bool enabled) {
    show_markers = enabled;
}

void LinePlot::set_default_marker_type(MarkerType marker_type) {
    default_marker_type = marker_type;
}

void LinePlot::set_line_style(cairo_t* cr, LineStyle style, double line_width) {
    cairo_set_line_width(cr, line_width);
    
    switch (style) {
        case LineStyle::SOLID:
            cairo_set_dash(cr, nullptr, 0, 0);
            break;
            
        case LineStyle::DASHED: {
            double dashes[] = {10.0, 5.0};
            cairo_set_dash(cr, dashes, 2, 0);
            break;
        }
        
        case LineStyle::DOTTED: {
            double dashes[] = {2.0, 3.0};
            cairo_set_dash(cr, dashes, 2, 0);
            break;
        }
    }
}

void LinePlot::draw_data(cairo_t* cr) {
    // Draw lines
    draw_lines(cr);
    
    // Draw markers on top if enabled
    if (show_markers) {
        draw_markers(cr);
    }
}

void LinePlot::draw_lines(cairo_t* cr) {
    for (const auto& series : data_series) {
        if (series.points.size() < 2) continue; // Need at least 2 points for a line
        
        // Set line style and color
        cairo_set_source_rgba(cr, series.style.r, series.style.g, series.style.b, series.style.alpha);
        set_line_style(cr, default_line_style, default_line_width);
        
        // Start the path
        bool first_point = true;
        for (const auto& pt : series.points) {
            double screen_x, screen_y;
            transform_point(pt.x, pt.y, screen_x, screen_y);
            
            if (first_point) {
                cairo_move_to(cr, screen_x, screen_y);
                first_point = false;
            } else {
                cairo_line_to(cr, screen_x, screen_y);
            }
        }
        
        // Stroke the path
        cairo_stroke(cr);
    }
}

void LinePlot::draw_markers(cairo_t* cr) {
    for (const auto& series : data_series) {
        for (const auto& pt : series.points) {
            double screen_x, screen_y;
            transform_point(pt.x, pt.y, screen_x, screen_y);
            
            draw_marker(cr, screen_x, screen_y, default_marker_type, 
                       series.style.point_size, series.style.r, series.style.g, 
                       series.style.b, series.style.alpha);
        }
    }
}

// Beginner-friendly convenience methods
void LinePlot::add_line(const std::vector<double>& x_values, const std::vector<double>& y_values,
                       const std::string& name, const std::string& color_name) {
    if (x_values.size() != y_values.size()) {
        std::cerr << "Error: X and Y vectors must have the same size" << std::endl;
        return;
    }
    
    DataSeries series(name);
    for (size_t i = 0; i < x_values.size(); ++i) {
        series.points.emplace_back(x_values[i], y_values[i]);
    }
    series.style = color_to_style(color_name, 3.0, 2.0);
    
    data_series.push_back(series);
    bounds_set = false;
}

void LinePlot::add_line(const std::vector<double>& x_values, const std::vector<double>& y_values,
                       const std::string& name) {
    if (x_values.size() != y_values.size()) {
        std::cerr << "Error: X and Y vectors must have the same size" << std::endl;
        return;
    }
    
    DataSeries series(name);
    for (size_t i = 0; i < x_values.size(); ++i) {
        series.points.emplace_back(x_values[i], y_values[i]);
    }
    
    std::string color = get_auto_color(data_series.size());
    series.style = color_to_style(color, 3.0, 2.0);
    
    data_series.push_back(series);
    bounds_set = false;
}

void LinePlot::add_line(const std::vector<double>& x_values, const std::vector<double>& y_values) {
    std::string auto_name = "Line " + std::to_string(data_series.size() + 1);
    add_line(x_values, y_values, auto_name);
}

} // namespace plotlib 