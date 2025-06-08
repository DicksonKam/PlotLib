#include "scatter_plot.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace plotlib {

ScatterPlot::ScatterPlot(int w, int h) : PlotManager(w, h) {
    // Constructor delegates to PlotManager
}

void ScatterPlot::set_default_marker_type(MarkerType marker_type) {
    default_marker_type = marker_type;
}

void ScatterPlot::draw_data(cairo_t* cr) {
    // Draw cluster points first (background)
    draw_cluster_points(cr);
    
    // Draw regular points on top
    draw_points(cr);
}

void ScatterPlot::draw_points(cairo_t* cr) {
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

void ScatterPlot::draw_cluster_points(cairo_t* cr) {
    for (const auto& series : cluster_series) {
        // Draw outliers first (background)
        for (const auto& cluster_pt : series.points) {
            if (cluster_pt.cluster_label == -1) {
                double screen_x, screen_y;
                transform_point(cluster_pt.point.x, cluster_pt.point.y, screen_x, screen_y);
                
                auto color = get_cluster_color(cluster_pt.cluster_label);
                draw_marker(cr, screen_x, screen_y, MarkerType::CROSS, 
                           series.point_size, color[0], color[1], color[2], series.alpha);
            }
        }
        
        // Draw cluster points on top
        for (const auto& cluster_pt : series.points) {
            if (cluster_pt.cluster_label != -1) {
                double screen_x, screen_y;
                transform_point(cluster_pt.point.x, cluster_pt.point.y, screen_x, screen_y);
                
                auto color = get_cluster_color(cluster_pt.cluster_label);
                draw_marker(cr, screen_x, screen_y, MarkerType::CIRCLE, 
                           series.point_size, color[0], color[1], color[2], series.alpha);
            }
        }
    }
}

// Legacy methods for backward compatibility
void ScatterPlot::add_point(double x, double y, const PlotStyle& style) {
    // For backward compatibility, add to a default series
    if (data_series.empty()) {
        DataSeries default_series("Default");
        default_series.style = style;
        data_series.push_back(default_series);
    }
    data_series[0].points.emplace_back(x, y);
    bounds_set = false;
}

void ScatterPlot::add_points(const std::vector<Point2D>& pts, const PlotStyle& style) {
    // For backward compatibility, add to a default series
    if (data_series.empty()) {
        DataSeries default_series("Default");
        default_series.style = style;
        data_series.push_back(default_series);
    }
    for (const auto& pt : pts) {
        data_series[0].points.push_back(pt);
    }
    bounds_set = false;
}

// Beginner-friendly convenience methods
void ScatterPlot::add_data(const std::string& name, const std::vector<Point2D>& data) {
    // Use automatic color based on series count
    std::vector<std::string> auto_colors = {"blue", "red", "green", "orange", "purple", "cyan", "magenta", "yellow"};
    std::string color = auto_colors[data_series.size() % auto_colors.size()];
    add_series(name, data, color_to_style(color, 3.0, 2.0));
}

void ScatterPlot::add_data(const std::string& name, const std::vector<Point2D>& data, const std::string& color_name) {
    add_series(name, data, color_to_style(color_name, 3.0, 2.0));
}

void ScatterPlot::add_clusters(const std::vector<Point2D>& data, const std::vector<int>& labels) {
    add_cluster_data("Clusters", data, labels);
}

// Implementation of the non-template get_subplot method for backward compatibility
ScatterPlot& SubplotManager::get_subplot(int row, int col) {
    return get_subplot<ScatterPlot>(row, col);
}

} // namespace plotlib
