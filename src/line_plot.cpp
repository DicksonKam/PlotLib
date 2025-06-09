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
    // Draw cluster lines first (background)
    draw_cluster_lines(cr);
    
    // Draw regular lines
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

void LinePlot::draw_cluster_lines(cairo_t* cr) {
    for (const auto& series : cluster_series) {
        if (series.points.size() < 2) continue;
        
        // Group points by cluster label
        std::map<int, std::vector<Point2D>> cluster_groups;
        for (const auto& cluster_pt : series.points) {
            cluster_groups[cluster_pt.cluster_label].push_back(cluster_pt.point);
        }
        
        // Draw lines for each cluster
        for (const auto& [cluster_label, points] : cluster_groups) {
            if (points.size() < 2) continue;
            
            auto color = get_cluster_color(cluster_label);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], series.alpha);
            
            // Use dashed lines for outliers
            LineStyle style = (cluster_label == -1) ? LineStyle::DASHED : default_line_style;
            set_line_style(cr, style, default_line_width);
            
            // Sort points by x-coordinate for better line visualization
            auto sorted_points = points;
            std::sort(sorted_points.begin(), sorted_points.end(), 
                     [](const Point2D& a, const Point2D& b) { return a.x < b.x; });
            
            // Draw the line
            bool first_point = true;
            for (const auto& pt : sorted_points) {
                double screen_x, screen_y;
                transform_point(pt.x, pt.y, screen_x, screen_y);
                
                if (first_point) {
                    cairo_move_to(cr, screen_x, screen_y);
                    first_point = false;
                } else {
                    cairo_line_to(cr, screen_x, screen_y);
                }
            }
            
            cairo_stroke(cr);
            
            // Draw markers for cluster points if enabled
            if (show_markers) {
                MarkerType marker = (cluster_label == -1) ? MarkerType::CROSS : MarkerType::CIRCLE;
                for (const auto& pt : points) {
                    double screen_x, screen_y;
                    transform_point(pt.x, pt.y, screen_x, screen_y);
                    
                    draw_marker(cr, screen_x, screen_y, marker, 
                               series.point_size, color[0], color[1], color[2], series.alpha);
                }
            }
        }
    }
}

// Beginner-friendly convenience methods
void LinePlot::add_line(const std::string& name, const std::vector<double>& x_values, 
                       const std::vector<double>& y_values) {
    if (x_values.size() != y_values.size()) {
        std::cerr << "Error: X and Y vectors must have the same size" << std::endl;
        return;
    }
    
    std::vector<Point2D> data;
    for (size_t i = 0; i < x_values.size(); ++i) {
        data.emplace_back(x_values[i], y_values[i]);
    }
    
    std::string color = get_auto_color(data_series.size());
    add_series(name, data, color_to_style(color, 3.0, 2.0));
}

void LinePlot::add_line(const std::string& name, const std::vector<double>& x_values, 
                       const std::vector<double>& y_values, const std::string& color_name) {
    if (x_values.size() != y_values.size()) {
        std::cerr << "Error: X and Y vectors must have the same size" << std::endl;
        return;
    }
    
    std::vector<Point2D> data;
    for (size_t i = 0; i < x_values.size(); ++i) {
        data.emplace_back(x_values[i], y_values[i]);
    }
    
    add_series(name, data, color_to_style(color_name, 3.0, 2.0));
}

} // namespace plotlib 