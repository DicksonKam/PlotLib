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

// Beginner-friendly convenience methods
void ScatterPlot::add_scatter(const std::string& name, const std::vector<double>& x_values, 
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

void ScatterPlot::add_scatter(const std::string& name, const std::vector<double>& x_values, 
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

void ScatterPlot::add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                              const std::vector<int>& labels) {
    if (x_values.size() != y_values.size() || x_values.size() != labels.size()) {
        std::cerr << "Error: X, Y and labels vectors must have the same size" << std::endl;
        return;
    }
    
    std::vector<Point2D> data;
    for (size_t i = 0; i < x_values.size(); ++i) {
        data.emplace_back(x_values[i], y_values[i]);
    }
    
    add_cluster_data("Clusters", data, labels);
}

} // namespace plotlib
