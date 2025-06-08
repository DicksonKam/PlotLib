#include "plotlib/plot_manager.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <set>
#include <stdexcept>

namespace plotlib {

PlotManager::PlotManager(int w, int h) : width(w), height(h) {
    initialize_cluster_colors();
}

void PlotManager::initialize_cluster_colors() {
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

std::vector<double> PlotManager::get_cluster_color(int cluster_label) {
    if (cluster_label == -1) {
        return {1.0, 0.0, 0.0}; // Red for outliers
    }
    
    // Use modulo to cycle through colors if we have more clusters than colors
    int color_index = cluster_label % cluster_colors.size();
    return cluster_colors[color_index];
}

void PlotManager::add_series(const std::string& name, const std::vector<Point2D>& points, const PlotStyle& style) {
    DataSeries series(name);
    series.points = points;
    series.style = style;
    data_series.push_back(series);
    bounds_set = false;
}

void PlotManager::add_series_point(const std::string& series_name, double x, double y) {
    // Find existing series or create new one
    auto it = std::find_if(data_series.begin(), data_series.end(),
                          [&series_name](const DataSeries& s) { return s.name == series_name; });
    
    if (it != data_series.end()) {
        it->points.emplace_back(x, y);
    } else {
        DataSeries new_series(series_name);
        new_series.points.emplace_back(x, y);
        data_series.push_back(new_series);
    }
    bounds_set = false;
}

void PlotManager::add_cluster_data(const std::string& name, const std::vector<Point2D>& points, 
                                  const std::vector<int>& cluster_labels, double point_size, double alpha) {
    if (points.size() != cluster_labels.size()) {
        std::cerr << "Error: Number of points (" << points.size() << ") must match number of cluster labels (" << cluster_labels.size() << ")" << std::endl;
        return;
    }
    
    ClusterSeries series(name);
    series.point_size = point_size;
    series.alpha = alpha;
    
    for (size_t i = 0; i < points.size(); ++i) {
        series.points.emplace_back(points[i], cluster_labels[i]);
    }
    
    cluster_series.push_back(series);
    bounds_set = false;
}

void PlotManager::add_cluster_point(const std::string& series_name, double x, double y, int cluster_label) {
    // Find existing cluster series or create new one
    auto it = std::find_if(cluster_series.begin(), cluster_series.end(),
                          [&series_name](const ClusterSeries& s) { return s.name == series_name; });
    
    if (it != cluster_series.end()) {
        it->points.emplace_back(x, y, cluster_label);
    } else {
        ClusterSeries new_series(series_name);
        new_series.points.emplace_back(x, y, cluster_label);
        cluster_series.push_back(new_series);
    }
    bounds_set = false;
}

void PlotManager::set_title(const std::string& plot_title) {
    title = plot_title;
}

void PlotManager::set_xlabel(const std::string& x_axis_label) {
    x_label = x_axis_label;
}

void PlotManager::set_ylabel(const std::string& y_axis_label) {
    y_label = y_axis_label;
}

void PlotManager::set_labels(const std::string& plot_title, const std::string& x_axis_label, const std::string& y_axis_label) {
    title = plot_title;
    x_label = x_axis_label;
    y_label = y_axis_label;
}

void PlotManager::calculate_bounds() {
    if (data_series.empty() && cluster_series.empty()) return;
    
    bool first = true;
    
    // Calculate bounds from regular data series
    for (const auto& series : data_series) {
        for (const auto& pt : series.points) {
            if (first) {
                min_x = max_x = pt.x;
                min_y = max_y = pt.y;
                first = false;
            } else {
                min_x = std::min(min_x, pt.x);
                max_x = std::max(max_x, pt.x);
                min_y = std::min(min_y, pt.y);
                max_y = std::max(max_y, pt.y);
            }
        }
    }
    
    // Calculate bounds from cluster series
    for (const auto& series : cluster_series) {
        for (const auto& cluster_pt : series.points) {
            const auto& pt = cluster_pt.point;
            if (first) {
                min_x = max_x = pt.x;
                min_y = max_y = pt.y;
                first = false;
            } else {
                min_x = std::min(min_x, pt.x);
                max_x = std::max(max_x, pt.x);
                min_y = std::min(min_y, pt.y);
                max_y = std::max(max_y, pt.y);
            }
        }
    }
    
    // Add some padding
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

void PlotManager::set_bounds(double min_x, double max_x, double min_y, double max_y) {
    this->min_x = min_x;
    this->max_x = max_x;
    this->min_y = min_y;
    this->max_y = max_y;
    bounds_set = true;
}

void PlotManager::transform_point(double data_x, double data_y, double& screen_x, double& screen_y) {
    double plot_width = width - margin_left - margin_right;
    double plot_height = height - margin_top - margin_bottom;
    
    // Apply subplot transformations if this is a subplot
    if (is_subplot) {
        plot_width *= subplot_width_scale;
        plot_height *= subplot_height_scale;
    }
    
    screen_x = margin_left + (data_x - min_x) / (max_x - min_x) * plot_width;
    screen_y = height - margin_bottom - (data_y - min_y) / (max_y - min_y) * plot_height;
    
    // Apply subplot offset if this is a subplot
    if (is_subplot) {
        screen_x += subplot_x_offset;
        screen_y += subplot_y_offset;
    }
}

std::string PlotManager::format_number(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    std::string str = oss.str();
    
    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    
    return str;
}

std::vector<double> PlotManager::generate_nice_ticks(double min_val, double max_val, int target_ticks) {
    std::vector<double> ticks;
    
    if (min_val >= max_val) return ticks;
    
    double range = max_val - min_val;
    double raw_step = range / target_ticks;
    
    // Find a "nice" step size
    double magnitude = std::pow(10, std::floor(std::log10(raw_step)));
    double normalized_step = raw_step / magnitude;
    
    double nice_step;
    if (normalized_step <= 1) nice_step = 1;
    else if (normalized_step <= 2) nice_step = 2;
    else if (normalized_step <= 5) nice_step = 5;
    else nice_step = 10;
    
    nice_step *= magnitude;
    
    // Generate ticks
    double start = std::ceil(min_val / nice_step) * nice_step;
    for (double tick = start; tick <= max_val + nice_step * 0.001; tick += nice_step) {
        ticks.push_back(tick);
    }
    
    return ticks;
}

void PlotManager::draw_axes(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1.0);
    
    double plot_width = width - margin_left - margin_right;
    double plot_height = height - margin_top - margin_bottom;
    
    // Apply subplot transformations
    if (is_subplot) {
        plot_width *= subplot_width_scale;
        plot_height *= subplot_height_scale;
    }
    
    double left = margin_left + (is_subplot ? subplot_x_offset : 0);
    double bottom = height - margin_bottom + (is_subplot ? subplot_y_offset : 0);
    double right = left + plot_width;
    double top = bottom - plot_height;
    
    // Draw X axis
    cairo_move_to(cr, left, bottom);
    cairo_line_to(cr, right, bottom);
    cairo_stroke(cr);
    
    // Draw Y axis
    cairo_move_to(cr, left, bottom);
    cairo_line_to(cr, left, top);
    cairo_stroke(cr);
}

void PlotManager::draw_axis_ticks(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1.0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 10);
    
    double plot_width = width - margin_left - margin_right;
    double plot_height = height - margin_top - margin_bottom;
    
    if (is_subplot) {
        plot_width *= subplot_width_scale;
        plot_height *= subplot_height_scale;
    }
    
    double left = margin_left + (is_subplot ? subplot_x_offset : 0);
    double bottom = height - margin_bottom + (is_subplot ? subplot_y_offset : 0);
    
    // X-axis ticks
    auto x_ticks = generate_nice_ticks(min_x, max_x);
    for (double tick : x_ticks) {
        double x = left + (tick - min_x) / (max_x - min_x) * plot_width;
        
        // Draw tick mark
        cairo_move_to(cr, x, bottom);
        cairo_line_to(cr, x, bottom + 5);
        cairo_stroke(cr);
        
        // Draw tick label
        std::string label = format_number(tick);
        cairo_text_extents_t extents;
        cairo_text_extents(cr, label.c_str(), &extents);
        cairo_move_to(cr, x - extents.width / 2, bottom + 18);
        cairo_show_text(cr, label.c_str());
    }
    
    // Y-axis ticks
    auto y_ticks = generate_nice_ticks(min_y, max_y);
    for (double tick : y_ticks) {
        double y = bottom - (tick - min_y) / (max_y - min_y) * plot_height;
        
        // Draw tick mark
        cairo_move_to(cr, left, y);
        cairo_line_to(cr, left - 5, y);
        cairo_stroke(cr);
        
        // Draw tick label
        std::string label = format_number(tick);
        cairo_text_extents_t extents;
        cairo_text_extents(cr, label.c_str(), &extents);
        cairo_move_to(cr, left - extents.width - 10, y + extents.height / 2);
        cairo_show_text(cr, label.c_str());
    }
}

void PlotManager::draw_grid(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
    cairo_set_line_width(cr, 0.5);
    
    double plot_width = width - margin_left - margin_right;
    double plot_height = height - margin_top - margin_bottom;
    
    if (is_subplot) {
        plot_width *= subplot_width_scale;
        plot_height *= subplot_height_scale;
    }
    
    double left = margin_left + (is_subplot ? subplot_x_offset : 0);
    double bottom = height - margin_bottom + (is_subplot ? subplot_y_offset : 0);
    double top = bottom - plot_height;
    
    // Vertical grid lines (X-axis ticks)
    auto x_ticks = generate_nice_ticks(min_x, max_x);
    for (double tick : x_ticks) {
        double x = left + (tick - min_x) / (max_x - min_x) * plot_width;
        cairo_move_to(cr, x, bottom);
        cairo_line_to(cr, x, top);
        cairo_stroke(cr);
    }
    
    // Horizontal grid lines (Y-axis ticks)
    auto y_ticks = generate_nice_ticks(min_y, max_y);
    for (double tick : y_ticks) {
        double y = bottom - (tick - min_y) / (max_y - min_y) * plot_height;
        cairo_move_to(cr, left, y);
        cairo_line_to(cr, left + plot_width, y);
        cairo_stroke(cr);
    }
}

void PlotManager::draw_axis_labels(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12);
    
    double plot_width = width - margin_left - margin_right;
    double plot_height = height - margin_top - margin_bottom;
    
    if (is_subplot) {
        plot_width *= subplot_width_scale;
        plot_height *= subplot_height_scale;
    }
    
    double left = margin_left + (is_subplot ? subplot_x_offset : 0);
    double bottom = height - margin_bottom + (is_subplot ? subplot_y_offset : 0);
    
    // X-axis label
    if (!x_label.empty()) {
        cairo_text_extents_t extents;
        cairo_text_extents(cr, x_label.c_str(), &extents);
        double x = left + plot_width / 2 - extents.width / 2;
        double y = bottom + 40;
        cairo_move_to(cr, x, y);
        cairo_show_text(cr, x_label.c_str());
    }
    
    // Y-axis label (rotated)
    if (!y_label.empty()) {
        cairo_text_extents_t extents;
        cairo_text_extents(cr, y_label.c_str(), &extents);
        double x = left - 50;
        double y = bottom - plot_height / 2 + extents.width / 2;
        
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_rotate(cr, -M_PI / 2);
        cairo_move_to(cr, 0, 0);
        cairo_show_text(cr, y_label.c_str());
        cairo_restore(cr);
    }
}

void PlotManager::draw_title(cairo_t* cr) {
    if (title.empty()) return;
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14);
    
    cairo_text_extents_t extents;
    cairo_text_extents(cr, title.c_str(), &extents);
    
    double plot_width = width - margin_left - margin_right;
    if (is_subplot) {
        plot_width *= subplot_width_scale;
    }
    
    double left = margin_left + (is_subplot ? subplot_x_offset : 0);
    double x = left + plot_width / 2 - extents.width / 2;
    double y = margin_top / 2 + extents.height / 2 + (is_subplot ? subplot_y_offset : 0);
    
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, title.c_str());
}

void PlotManager::draw_marker(cairo_t* cr, double x, double y, MarkerType type, double size, 
                             double r, double g, double b, double alpha) {
    cairo_set_source_rgba(cr, r, g, b, alpha);
    
    switch (type) {
        case MarkerType::CIRCLE:
            cairo_arc(cr, x, y, size, 0, 2 * M_PI);
            cairo_fill(cr);
            break;
            
        case MarkerType::CROSS:
            cairo_set_line_width(cr, 2.0);
            cairo_move_to(cr, x - size, y - size);
            cairo_line_to(cr, x + size, y + size);
            cairo_move_to(cr, x - size, y + size);
            cairo_line_to(cr, x + size, y - size);
            cairo_stroke(cr);
            break;
            
        case MarkerType::SQUARE:
            cairo_rectangle(cr, x - size, y - size, 2 * size, 2 * size);
            cairo_fill(cr);
            break;
            
        case MarkerType::TRIANGLE:
            cairo_move_to(cr, x, y - size);
            cairo_line_to(cr, x - size, y + size);
            cairo_line_to(cr, x + size, y + size);
            cairo_close_path(cr);
            cairo_fill(cr);
            break;
    }
}

void PlotManager::draw_legend(cairo_t* cr) {
    // Collect all series for legend
    std::vector<std::pair<std::string, PlotStyle>> legend_items;
    
    // Add regular series
    for (const auto& series : data_series) {
        if (!series.name.empty()) {
            legend_items.emplace_back(series.name, series.style);
        }
    }
    
    // Add cluster series
    std::set<int> cluster_labels_seen;
    for (const auto& series : cluster_series) {
        if (!series.name.empty()) {
            // Add cluster labels
            for (const auto& cluster_pt : series.points) {
                if (cluster_labels_seen.find(cluster_pt.cluster_label) == cluster_labels_seen.end()) {
                    cluster_labels_seen.insert(cluster_pt.cluster_label);
                    
                    PlotStyle cluster_style;
                    auto color = get_cluster_color(cluster_pt.cluster_label);
                    cluster_style.r = color[0];
                    cluster_style.g = color[1];
                    cluster_style.b = color[2];
                    cluster_style.point_size = series.point_size;
                    cluster_style.alpha = series.alpha;
                    
                    std::string label = (cluster_pt.cluster_label == -1) ? "Outliers" : 
                                       ("Cluster " + std::to_string(cluster_pt.cluster_label));
                    legend_items.emplace_back(label, cluster_style);
                }
            }
        }
    }
    
    if (legend_items.empty()) return;
    
    // Calculate legend position and size
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 10);
    
    double legend_x = width - margin_right + 10 + (is_subplot ? subplot_x_offset : 0);
    double legend_y = margin_top + 20 + (is_subplot ? subplot_y_offset : 0);
    double line_height = 16;
    
    // Draw legend items
    for (size_t i = 0; i < legend_items.size(); ++i) {
        double y = legend_y + i * line_height;
        
        // Draw marker
        draw_marker(cr, legend_x + 6, y, MarkerType::CIRCLE, legend_items[i].second.point_size,
                   legend_items[i].second.r, legend_items[i].second.g, legend_items[i].second.b,
                   legend_items[i].second.alpha);
        
        // Draw text
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, legend_x + 15, y + 4);
        cairo_show_text(cr, legend_items[i].first.c_str());
    }
}

void PlotManager::set_subplot_transform(double x_offset, double y_offset, double width_scale, double height_scale) {
    is_subplot = true;
    subplot_x_offset = x_offset;
    subplot_y_offset = y_offset;
    subplot_width_scale = width_scale;
    subplot_height_scale = height_scale;
}

void PlotManager::render_to_context(cairo_t* cr) {
    if (!bounds_set) {
        calculate_bounds();
    }
    
    // Draw all components
    draw_grid(cr);
    draw_axes(cr);
    draw_axis_ticks(cr);
    draw_axis_labels(cr);
    draw_title(cr);
    draw_data(cr);  // This will be implemented by derived classes
    draw_legend(cr);
}

bool PlotManager::save_png(const std::string& filename) {
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);
    
    // White background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    
    render_to_context(cr);
    
    cairo_status_t status = cairo_surface_write_to_png(surface, filename.c_str());
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
    return status == CAIRO_STATUS_SUCCESS;
}

bool PlotManager::save_svg(const std::string& filename) {
    cairo_surface_t* surface = cairo_svg_surface_create(filename.c_str(), width, height);
    cairo_t* cr = cairo_create(surface);
    
    // White background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    
    render_to_context(cr);
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
    return true;
}

void PlotManager::clear() {
    data_series.clear();
    cluster_series.clear();
    title = "";
    x_label = "";
    y_label = "";
    bounds_set = false;
}

// SubplotManager implementation

SubplotManager::SubplotManager(int rows, int cols, int width, int height, double spacing)
    : rows(rows), cols(cols), total_width(width), total_height(height), spacing(spacing) {
    
    // Initialize subplot grid with nullptr (will be set by specific plot types)
    subplots.resize(rows);
    for (int i = 0; i < rows; ++i) {
        subplots[i].resize(cols);
    }
}



void SubplotManager::set_main_title(const std::string& title) {
    main_title = title;
}

double SubplotManager::get_title_height(cairo_t* cr) {
    if (main_title.empty()) return 0.0;
    
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 16);
    
    cairo_text_extents_t extents;
    cairo_text_extents(cr, main_title.c_str(), &extents);
    
    return extents.height + 20; // Add some padding
}

void SubplotManager::render_to_context(cairo_t* cr) {
    // Draw main title if present
    if (!main_title.empty()) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 16);
        
        cairo_text_extents_t extents;
        cairo_text_extents(cr, main_title.c_str(), &extents);
        
        double x = total_width / 2 - extents.width / 2;
        double y = 30;
        
        cairo_move_to(cr, x, y);
        cairo_show_text(cr, main_title.c_str());
    }
    
    // Render all subplots
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (subplots[row][col]) {
                subplots[row][col]->render_to_context(cr);
            }
        }
    }
}

bool SubplotManager::save_png(const std::string& filename) {
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, total_width, total_height);
    cairo_t* cr = cairo_create(surface);
    
    // White background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    
    render_to_context(cr);
    
    cairo_status_t status = cairo_surface_write_to_png(surface, filename.c_str());
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
    return status == CAIRO_STATUS_SUCCESS;
}

bool SubplotManager::save_svg(const std::string& filename) {
    cairo_surface_t* surface = cairo_svg_surface_create(filename.c_str(), total_width, total_height);
    cairo_t* cr = cairo_create(surface);
    
    // White background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    
    render_to_context(cr);
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
    return true;
}

} // namespace plotlib 