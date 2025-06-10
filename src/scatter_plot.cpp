#include "scatter_plot.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <map>

namespace plotlib {

ScatterPlot::ScatterPlot(int width, int height) : PlotManager(width, height) {
    // Constructor delegates to PlotManager
    initialize_cluster_colors();
}

void ScatterPlot::set_default_marker_type(MarkerType marker_type) {
    default_marker_type = marker_type;
}

void ScatterPlot::initialize_cluster_colors() {
    // Define a nice color palette for clusters (excluding red which is reserved for outliers)
    cluster_colors = {
        {0.0, 0.4, 0.8},   // Blue
        {0.0, 0.7, 0.3},   // Green
        {0.6, 0.2, 0.8},   // Purple
        {1.0, 0.5, 0.0},   // Orange
        {0.8, 0.8, 0.0},   // Yellow
        {0.0, 0.8, 0.8},   // Cyan
        {0.8, 0.0, 0.8},   // Magenta
        {0.5, 0.3, 0.1},   // Brown
        {0.7, 0.7, 0.7},   // Gray
        {0.0, 0.5, 0.5},   // Teal
        {0.5, 0.0, 0.5},   // Dark Purple
        {0.0, 0.3, 0.6},   // Dark Blue
        {0.3, 0.5, 0.0},   // Olive
        {0.6, 0.3, 0.0},   // Dark Orange
        {0.4, 0.0, 0.4}    // Dark Magenta
    };
}

std::vector<double> ScatterPlot::get_cluster_color(int cluster_label) {
    if (cluster_label == -1) {
        return {1.0, 0.0, 0.0}; // Red for outliers
    }
    
    // Use modulo to cycle through colors if we have more clusters than colors
    int color_index = cluster_label % cluster_colors.size();
    return cluster_colors[color_index];
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
        // Group points by cluster label for proper legend handling
        std::map<int, std::vector<ClusterPoint>> clusters_by_label;
        for (const auto& cluster_pt : series.points) {
            clusters_by_label[cluster_pt.cluster_label].push_back(cluster_pt);
        }
        
        // Draw outliers first (background) - Red cross (customizable if custom colors provided)
        if (clusters_by_label.count(-1) > 0) {
            for (const auto& cluster_pt : clusters_by_label[-1]) {
                double screen_x, screen_y;
                transform_point(cluster_pt.x, cluster_pt.y, screen_x, screen_y);
                
                // Get outlier color (red by default, or custom if provided)
                std::vector<double> outlier_color;
                if (!series.use_auto_coloring && series.cluster_colors.count(-1) > 0) {
                    // Use custom color if provided
                    PlotStyle custom_style = color_to_style(series.cluster_colors.at(-1), 3.0, 2.0);
                    outlier_color = {custom_style.r, custom_style.g, custom_style.b};
                } else {
                    // Default red for outliers
                    outlier_color = {1.0, 0.0, 0.0};
                }
                
                draw_marker(cr, screen_x, screen_y, MarkerType::CROSS, 
                           series.point_size, outlier_color[0], outlier_color[1], outlier_color[2], series.alpha);
            }
        }
        
        // Draw cluster points on top - Auto-colors or custom colors, circles
        for (const auto& cluster_pair : clusters_by_label) {
            int cluster_label = cluster_pair.first;
            if (cluster_label == -1) continue; // Skip outliers (already drawn)
            
            // Get cluster color (auto or custom)
            std::vector<double> cluster_color;
            if (!series.use_auto_coloring && series.cluster_colors.count(cluster_label) > 0) {
                // Use custom color if provided
                PlotStyle custom_style = color_to_style(series.cluster_colors.at(cluster_label), 3.0, 2.0);
                cluster_color = {custom_style.r, custom_style.g, custom_style.b};
            } else {
                // Use automatic coloring
                cluster_color = get_cluster_color(cluster_label);
            }
            
            for (const auto& cluster_pt : cluster_pair.second) {
                double screen_x, screen_y;
                transform_point(cluster_pt.x, cluster_pt.y, screen_x, screen_y);
                
                // Fixed marker type for clusters: circle
                draw_marker(cr, screen_x, screen_y, MarkerType::CIRCLE, 
                           series.point_size, cluster_color[0], cluster_color[1], cluster_color[2], series.alpha);
            }
        }
    }
}

void ScatterPlot::calculate_bounds() {
    // Call parent to calculate bounds from regular data series
    PlotManager::calculate_bounds();
    
    // Also include bounds from cluster series
    bool first = data_series.empty(); // If no regular data, cluster data determines initial bounds
    
    for (const auto& series : cluster_series) {
        for (const auto& cluster_pt : series.points) {
            if (first) {
                min_x = max_x = cluster_pt.x;
                min_y = max_y = cluster_pt.y;
                first = false;
            } else {
                min_x = std::min(min_x, cluster_pt.x);
                max_x = std::max(max_x, cluster_pt.x);
                min_y = std::min(min_y, cluster_pt.y);
                max_y = std::max(max_y, cluster_pt.y);
            }
        }
    }
    
    // Add padding if we have any data
    if (!first) {
        double x_range = max_x - min_x;
        double y_range = max_y - min_y;
        
        if (x_range == 0) x_range = 1;
        if (y_range == 0) y_range = 1;
        
        min_x -= x_range * 0.05;
        max_x += x_range * 0.05;
        min_y -= y_range * 0.05;
        max_y += y_range * 0.05;
        
        bounds_set = true;
    }
}

void ScatterPlot::draw_legend(cairo_t* cr) {
    if (!show_legend) return;
    
    // Collect all series for legend (including clusters)
    std::vector<std::pair<std::string, PlotStyle>> legend_items;
    std::vector<MarkerType> legend_markers;
    
    // Add regular scatter series (skip if only one default series)
    if (data_series.size() > 1 || (data_series.size() == 1 && data_series[0].name != "Default")) {
        for (const auto& series : data_series) {
            if (!series.name.empty() && hidden_legend_items.find(series.name) == hidden_legend_items.end()) {
                legend_items.emplace_back(series.name, series.style);
                legend_markers.push_back(MarkerType::CIRCLE);
            }
        }
    }
    
    // Add cluster legend entries (independent sequence for each cluster series)
    for (const auto& series : cluster_series) {
        // Find all unique cluster labels in this series
        std::set<int> unique_labels;
        for (const auto& cluster_pt : series.points) {
            unique_labels.insert(cluster_pt.cluster_label);
        }
        
        // Create legend entry for outliers first (if present)
        if (unique_labels.count(-1) > 0) {
            std::string outlier_name = "Outliers";
            if (!series.use_auto_naming && series.cluster_names.count(-1) > 0) {
                outlier_name = series.cluster_names.at(-1);
            }
            
            if (hidden_legend_items.find(outlier_name) == hidden_legend_items.end()) {
                // Use same color logic as drawing
                PlotStyle outlier_style;
                if (!series.use_auto_coloring && series.cluster_colors.count(-1) > 0) {
                    // Use custom color if provided
                    outlier_style = color_to_style(series.cluster_colors.at(-1), 3.0, 2.0);
                } else {
                    // Default red for outliers
                    outlier_style.point_size = 3.0;
                    outlier_style.r = 1.0;
                    outlier_style.g = 0.0;
                    outlier_style.b = 0.0;
                    outlier_style.alpha = 0.8;
                }
                legend_items.emplace_back(outlier_name, outlier_style);
                legend_markers.push_back(MarkerType::CROSS);
            }
        }
        
        // Create legend entries for clusters (using actual cluster labels for consistency)
        for (int label : unique_labels) {
            if (label == -1) continue; // Skip outliers (already handled)
            
            // Use actual cluster label + 1 for naming to match user expectation (Cluster 1, Cluster 2, etc.)
            std::string cluster_name = "Cluster " + std::to_string(label + 1);
            if (!series.use_auto_naming && series.cluster_names.count(label) > 0) {
                cluster_name = series.cluster_names.at(label);
            }
            
            if (hidden_legend_items.find(cluster_name) == hidden_legend_items.end()) {
                // Use same color logic as drawing
                PlotStyle cluster_style;
                if (!series.use_auto_coloring && series.cluster_colors.count(label) > 0) {
                    // Use custom color if provided
                    cluster_style = color_to_style(series.cluster_colors.at(label), 3.0, 2.0);
                } else {
                    // Use automatic coloring - use actual label for color consistency
                    auto color = get_cluster_color(label);
                    cluster_style.point_size = 3.0;
                    cluster_style.r = color[0];
                    cluster_style.g = color[1]; 
                    cluster_style.b = color[2];
                    cluster_style.alpha = 0.8;
                }
                legend_items.emplace_back(cluster_name, cluster_style);
                legend_markers.push_back(MarkerType::CIRCLE);
            }
        }
    }
    
    // Add reference lines
    for (const auto& ref_line : reference_lines) {
        if (!ref_line.label.empty() && hidden_legend_items.find(ref_line.label) == hidden_legend_items.end()) {
            legend_items.emplace_back(ref_line.label, ref_line.style);
            legend_markers.push_back(MarkerType::CIRCLE);
        }
    }
    
    // If no legend items, return early
    if (legend_items.empty()) return;
    
    // Legend positioning and sizing (copied from PlotManager logic)
    const double legend_padding = 10;
    const double legend_item_height = 20;
    const double legend_marker_size = 8;
    const double legend_text_offset = 15;
    
    double legend_x = width - margin_right + 10;
    double legend_y = margin_top + 20;
    double legend_width = margin_right - 20;
    double legend_height = legend_items.size() * legend_item_height + 2 * legend_padding;
    
    // Draw legend background
    cairo_set_source_rgba(cr, 1, 1, 1, 0.9);
    cairo_rectangle(cr, legend_x, legend_y, legend_width, legend_height);
    cairo_fill(cr);
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, legend_x, legend_y, legend_width, legend_height);
    cairo_stroke(cr);
    
    // Draw legend items
    cairo_set_font_size(cr, 12);
    for (size_t i = 0; i < legend_items.size(); ++i) {
        double item_y = legend_y + legend_padding + i * legend_item_height;
        
        // Draw marker
        double marker_x = legend_x + legend_padding;
        double marker_y = item_y + legend_item_height / 2;
        
        auto& style = legend_items[i].second;
        cairo_set_source_rgba(cr, style.r, style.g, style.b, style.alpha);
        
        // Draw the appropriate marker type
        MarkerType marker_type = legend_markers[i];
        if (marker_type == MarkerType::CROSS) {
            // Draw cross for outliers
            cairo_set_line_width(cr, 2);
            cairo_move_to(cr, marker_x - legend_marker_size/2, marker_y - legend_marker_size/2);
            cairo_line_to(cr, marker_x + legend_marker_size/2, marker_y + legend_marker_size/2);
            cairo_move_to(cr, marker_x - legend_marker_size/2, marker_y + legend_marker_size/2);
            cairo_line_to(cr, marker_x + legend_marker_size/2, marker_y - legend_marker_size/2);
            cairo_stroke(cr);
        } else {
            // Draw circle for clusters and regular series
            cairo_arc(cr, marker_x, marker_y, legend_marker_size/2, 0, 2 * M_PI);
            cairo_fill(cr);
        }
        
        // Draw text
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, legend_x + legend_padding + legend_text_offset, item_y + legend_item_height / 2 + 3);
        cairo_show_text(cr, legend_items[i].first.c_str());
    }
}

void ScatterPlot::add_cluster_data(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                                  const std::vector<int>& cluster_labels, 
                                  const std::vector<std::string>& names,
                                  const std::vector<std::string>& colors,
                                  double point_size, double alpha) {
    if (x_values.size() != y_values.size() || x_values.size() != cluster_labels.size()) {
        std::cerr << "Error: X, Y and labels vectors must have the same size" << std::endl;
        return;
    }
    
    // Create new cluster series with enhanced functionality
    ClusterSeries series("Clusters " + std::to_string(cluster_series.size() + 1));
    series.point_size = point_size;
    series.alpha = alpha;
    
    // Determine unique cluster labels in the data
    std::set<int> unique_labels;
    for (int label : cluster_labels) {
        unique_labels.insert(label);
    }
    
    // Set up naming and coloring based on provided parameters
    if (names.empty()) {
        // Automatic naming: restart cluster sequence for each add_clusters call
        series.use_auto_naming = true;
        // Names will be generated in draw_cluster_points: "Outliers", "Cluster 1", "Cluster 2", etc.
    } else {
        // Custom naming provided
        series.use_auto_naming = false;
        int name_index = 0;
        for (int label : unique_labels) {
            if (name_index < names.size()) {
                if (label == -1) {
                    series.cluster_names[label] = names[name_index++]; // Outlier name
                } else {
                    series.cluster_names[label] = names[name_index++]; // Cluster name
                }
            }
        }
    }
    
    if (colors.empty()) {
        // Automatic coloring: fixed red for outliers, auto-colors for clusters
        series.use_auto_coloring = true;
    } else {
        // Custom coloring provided
        series.use_auto_coloring = false;
        int color_index = 0;
        for (int label : unique_labels) {
            if (color_index < colors.size()) {
                series.cluster_colors[label] = colors[color_index++];
            }
        }
    }
    
    // Add all points to the series
    for (size_t i = 0; i < x_values.size(); ++i) {
        series.points.emplace_back(x_values[i], y_values[i], cluster_labels[i]);
    }
    
    cluster_series.push_back(series);
    bounds_set = false;
}

// Beginner-friendly convenience methods
void ScatterPlot::add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values,
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

void ScatterPlot::add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values,
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

void ScatterPlot::add_scatter(const std::vector<double>& x_values, const std::vector<double>& y_values) {
    std::string auto_name = "Scatter " + std::to_string(data_series.size() + 1);
    add_scatter(x_values, y_values, auto_name);
}

void ScatterPlot::add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                              const std::vector<int>& labels) {
    // Automatic naming and coloring
    add_cluster_data(x_values, y_values, labels);
}

void ScatterPlot::add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                              const std::vector<int>& labels, const std::vector<std::string>& names) {
    // Custom names, automatic coloring
    add_cluster_data(x_values, y_values, labels, names);
}

void ScatterPlot::add_clusters(const std::vector<double>& x_values, const std::vector<double>& y_values, 
                              const std::vector<int>& labels, const std::vector<std::string>& names, 
                              const std::vector<std::string>& colors) {
    // Custom names and colors
    add_cluster_data(x_values, y_values, labels, names, colors);
}

} // namespace plotlib
