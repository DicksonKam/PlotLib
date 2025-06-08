#include "scatter_plot.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <set>
#include <stdexcept>

ScatterPlot::ScatterPlot(int w, int h) : width(w), height(h) {
    initialize_cluster_colors();
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

void ScatterPlot::add_point(double x, double y, const PlotStyle& style) {
    // For backward compatibility, add to a default series
    if (data_series.empty()) {
        data_series.emplace_back("Default");
        data_series[0].style = style;
    }
    data_series[0].points.emplace_back(x, y);
    bounds_set = false;
}

void ScatterPlot::add_points(const std::vector<Point2D>& pts, const PlotStyle& style) {
    // For backward compatibility, add to a default series
    if (data_series.empty()) {
        data_series.emplace_back("Default");
        data_series[0].style = style;
    }
    for (const auto& pt : pts) {
        data_series[0].points.push_back(pt);
    }
    bounds_set = false;
}

void ScatterPlot::add_series(const std::string& name, const std::vector<Point2D>& points, const PlotStyle& style) {
    DataSeries series(name);
    series.points = points;
    series.style = style;
    data_series.push_back(series);
    bounds_set = false;
}

void ScatterPlot::add_series_point(const std::string& series_name, double x, double y) {
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

void ScatterPlot::add_cluster_data(const std::string& name, const std::vector<Point2D>& points, const std::vector<int>& cluster_labels, double point_size, double alpha) {
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

void ScatterPlot::add_cluster_point(const std::string& series_name, double x, double y, int cluster_label) {
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

void ScatterPlot::set_title(const std::string& plot_title) {
    title = plot_title;
}

void ScatterPlot::set_xlabel(const std::string& x_axis_label) {
    x_label = x_axis_label;
}

void ScatterPlot::set_ylabel(const std::string& y_axis_label) {
    y_label = y_axis_label;
}

void ScatterPlot::set_labels(const std::string& plot_title, const std::string& x_axis_label, const std::string& y_axis_label) {
    title = plot_title;
    x_label = x_axis_label;
    y_label = y_axis_label;
}

void ScatterPlot::calculate_bounds() {
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

void ScatterPlot::set_bounds(double min_x, double max_x, double min_y, double max_y) {
    this->min_x = min_x;
    this->max_x = max_x;
    this->min_y = min_y;
    this->max_y = max_y;
    bounds_set = true;
}

void ScatterPlot::transform_point(double data_x, double data_y, double& screen_x, double& screen_y) {
    double plot_width = width - margin_left - margin_right;
    double plot_height = height - margin_top - margin_bottom;
    
    screen_x = margin_left + (data_x - min_x) / (max_x - min_x) * plot_width;
    screen_y = height - margin_bottom - (data_y - min_y) / (max_y - min_y) * plot_height;
}

std::string ScatterPlot::format_number(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    std::string str = oss.str();
    
    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    
    return str;
}

std::vector<double> ScatterPlot::generate_nice_ticks(double min_val, double max_val, int target_ticks) {
    std::vector<double> ticks;
    
    double range = max_val - min_val;
    if (range == 0) {
        ticks.push_back(min_val);
        return ticks;
    }
    
    // Calculate nice step size
    double raw_step = range / target_ticks;
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

void ScatterPlot::draw_marker(cairo_t* cr, double x, double y, MarkerType type, double size, double r, double g, double b, double alpha) {
    cairo_set_source_rgba(cr, r, g, b, alpha);
    
    switch (type) {
        case MarkerType::CIRCLE:
            cairo_arc(cr, x, y, size, 0, 2 * M_PI);
            cairo_fill(cr);
            break;
            
        case MarkerType::CROSS:
            cairo_set_line_width(cr, size * 0.4);
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
            cairo_line_to(cr, x - size * 0.866, y + size * 0.5);
            cairo_line_to(cr, x + size * 0.866, y + size * 0.5);
            cairo_close_path(cr);
            cairo_fill(cr);
            break;
    }
}

void ScatterPlot::draw_axes(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1.5);
    
    // X-axis
    cairo_move_to(cr, margin_left, height - margin_bottom);
    cairo_line_to(cr, width - margin_right, height - margin_bottom);
    cairo_stroke(cr);
    
    // Y-axis
    cairo_move_to(cr, margin_left, margin_top);
    cairo_line_to(cr, margin_left, height - margin_bottom);
    cairo_stroke(cr);
}

void ScatterPlot::draw_axis_ticks(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1.0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 10);
    
    // X-axis ticks
    auto x_ticks = generate_nice_ticks(min_x, max_x, 6);
    for (double tick : x_ticks) {
        double screen_x, screen_y;
        transform_point(tick, min_y, screen_x, screen_y);
        
        // Draw tick mark
        cairo_move_to(cr, screen_x, height - margin_bottom);
        cairo_line_to(cr, screen_x, height - margin_bottom + 5);
        cairo_stroke(cr);
        
        // Draw tick label
        std::string label = format_number(tick);
        cairo_text_extents_t extents;
        cairo_text_extents(cr, label.c_str(), &extents);
        cairo_move_to(cr, screen_x - extents.width/2, height - margin_bottom + 20);
        cairo_show_text(cr, label.c_str());
    }
    
    // Y-axis ticks
    auto y_ticks = generate_nice_ticks(min_y, max_y, 6);
    for (double tick : y_ticks) {
        double screen_x, screen_y;
        transform_point(min_x, tick, screen_x, screen_y);
        
        // Draw tick mark
        cairo_move_to(cr, margin_left, screen_y);
        cairo_line_to(cr, margin_left - 5, screen_y);
        cairo_stroke(cr);
        
        // Draw tick label
        std::string label = format_number(tick);
        cairo_text_extents_t extents;
        cairo_text_extents(cr, label.c_str(), &extents);
        cairo_move_to(cr, margin_left - extents.width - 10, screen_y + extents.height/2);
        cairo_show_text(cr, label.c_str());
    }
}

void ScatterPlot::draw_axis_labels(cairo_t* cr) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 12);
    
    // X-axis label
    if (!x_label.empty()) {
        cairo_text_extents_t extents;
        cairo_text_extents(cr, x_label.c_str(), &extents);
        double x_pos = margin_left + (width - margin_left - margin_right) / 2 - extents.width / 2;
        cairo_move_to(cr, x_pos, height - 15);
        cairo_show_text(cr, x_label.c_str());
    }
    
    // Y-axis label (rotated)
    if (!y_label.empty()) {
        cairo_text_extents_t extents;
        cairo_text_extents(cr, y_label.c_str(), &extents);
        double y_pos = margin_top + (height - margin_top - margin_bottom) / 2 + extents.width / 2;
        
        cairo_save(cr);
        cairo_move_to(cr, 15, y_pos);
        cairo_rotate(cr, -M_PI / 2);
        cairo_show_text(cr, y_label.c_str());
        cairo_restore(cr);
    }
}

void ScatterPlot::draw_title(cairo_t* cr) {
    if (title.empty()) return;
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 16);
    
    cairo_text_extents_t extents;
    cairo_text_extents(cr, title.c_str(), &extents);
    double x_pos = (width - extents.width) / 2;
    cairo_move_to(cr, x_pos, 25);
    cairo_show_text(cr, title.c_str());
}

void ScatterPlot::draw_grid(cairo_t* cr) {
    cairo_set_source_rgba(cr, 0.9, 0.9, 0.9, 0.8);
    cairo_set_line_width(cr, 0.5);
    
    // Vertical grid lines (based on x-axis ticks)
    auto x_ticks = generate_nice_ticks(min_x, max_x, 6);
    for (double tick : x_ticks) {
        double screen_x, screen_y;
        transform_point(tick, min_y, screen_x, screen_y);
        cairo_move_to(cr, screen_x, margin_top);
        cairo_line_to(cr, screen_x, height - margin_bottom);
        cairo_stroke(cr);
    }
    
    // Horizontal grid lines (based on y-axis ticks)
    auto y_ticks = generate_nice_ticks(min_y, max_y, 6);
    for (double tick : y_ticks) {
        double screen_x, screen_y;
        transform_point(min_x, tick, screen_x, screen_y);
        cairo_move_to(cr, margin_left, screen_y);
        cairo_line_to(cr, width - margin_right, screen_y);
        cairo_stroke(cr);
    }
}

void ScatterPlot::draw_cluster_points(cairo_t* cr) {
    for (const auto& series : cluster_series) {
        // First pass: Draw outliers (cluster_label == -1) in the background
        for (const auto& cluster_pt : series.points) {
            if (cluster_pt.cluster_label == -1) {
                double screen_x, screen_y;
                transform_point(cluster_pt.point.x, cluster_pt.point.y, screen_x, screen_y);
                
                auto color = get_cluster_color(-1); // Red for outliers
                draw_marker(cr, screen_x, screen_y, MarkerType::CROSS, series.point_size + 1, 
                           color[0], color[1], color[2], series.alpha);
            }
        }
        
        // Second pass: Draw cluster points (cluster_label >= 0) in the foreground
        for (const auto& cluster_pt : series.points) {
            if (cluster_pt.cluster_label >= 0) {
                double screen_x, screen_y;
                transform_point(cluster_pt.point.x, cluster_pt.point.y, screen_x, screen_y);
                
                auto color = get_cluster_color(cluster_pt.cluster_label);
                draw_marker(cr, screen_x, screen_y, MarkerType::CIRCLE, series.point_size, 
                           color[0], color[1], color[2], series.alpha);
            }
        }
    }
}

void ScatterPlot::draw_points(cairo_t* cr) {
    for (const auto& series : data_series) {
        const PlotStyle& style = series.style;
        cairo_set_source_rgba(cr, style.r, style.g, style.b, style.alpha);
        
        for (const auto& point : series.points) {
            double screen_x, screen_y;
            transform_point(point.x, point.y, screen_x, screen_y);
            
            cairo_arc(cr, screen_x, screen_y, style.point_size, 0, 2 * M_PI);
            cairo_fill(cr);
        }
    }
}

void ScatterPlot::draw_legend(cairo_t* cr) {
    // Count total legend items
    int legend_items = 0;
    
    // Count regular series (skip if only one default series)
    if (data_series.size() > 1 || (data_series.size() == 1 && data_series[0].name != "Default")) {
        legend_items += data_series.size();
    }
    
    // Count cluster series items
    std::set<int> unique_clusters;
    for (const auto& series : cluster_series) {
        for (const auto& cluster_pt : series.points) {
            unique_clusters.insert(cluster_pt.cluster_label);
        }
    }
    legend_items += unique_clusters.size();
    
    if (legend_items == 0) return;
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 10);
    
    double legend_x = width - margin_right + 10;
    double legend_y = margin_top + 20;
    double line_height = 20;
    
    // Draw legend background
    double legend_width = 120;
    double legend_height = legend_items * line_height + 10;
    cairo_set_source_rgba(cr, 1, 1, 1, 0.9);
    cairo_rectangle(cr, legend_x - 5, legend_y - 15, legend_width, legend_height);
    cairo_fill(cr);
    
    cairo_set_source_rgba(cr, 0, 0, 0, 0.3);
    cairo_rectangle(cr, legend_x - 5, legend_y - 15, legend_width, legend_height);
    cairo_stroke(cr);
    
    int item_index = 0;
    
    // Draw regular series legend items
    if (data_series.size() > 1 || (data_series.size() == 1 && data_series[0].name != "Default")) {
        for (const auto& series : data_series) {
            double y_pos = legend_y + item_index * line_height;
            
            // Draw colored circle
            cairo_set_source_rgba(cr, series.style.r, series.style.g, series.style.b, series.style.alpha);
            cairo_arc(cr, legend_x + 8, y_pos, series.style.point_size + 1, 0, 2 * M_PI);
            cairo_fill(cr);
            
            // Draw series name
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_move_to(cr, legend_x + 20, y_pos + 4);
            cairo_show_text(cr, series.name.c_str());
            
            item_index++;
        }
    }
    
    // Draw cluster legend items
    for (int cluster_label : unique_clusters) {
        double y_pos = legend_y + item_index * line_height;
        auto color = get_cluster_color(cluster_label);
        
        if (cluster_label == -1) {
            // Draw red cross for outliers
            draw_marker(cr, legend_x + 8, y_pos, MarkerType::CROSS, 4, color[0], color[1], color[2], 0.8);
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_move_to(cr, legend_x + 20, y_pos + 4);
            cairo_show_text(cr, "Outliers");
        } else {
            // Draw colored circle for clusters
            draw_marker(cr, legend_x + 8, y_pos, MarkerType::CIRCLE, 4, color[0], color[1], color[2], 0.8);
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_move_to(cr, legend_x + 20, y_pos + 4);
            std::string cluster_name = "Cluster " + std::to_string(cluster_label);
            cairo_show_text(cr, cluster_name.c_str());
        }
        
        item_index++;
    }
}

bool ScatterPlot::save_png(const std::string& filename) {
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

bool ScatterPlot::save_svg(const std::string& filename) {
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

void ScatterPlot::set_subplot_transform(double x_offset, double y_offset, double width_scale, double height_scale) {
    is_subplot = true;
    subplot_x_offset = x_offset;
    subplot_y_offset = y_offset;
    subplot_width_scale = width_scale;
    subplot_height_scale = height_scale;
    
    // Don't adjust margins here - they will be handled in the transformation
}

void ScatterPlot::render_to_context(cairo_t* cr) {
    if (!bounds_set) calculate_bounds();
    
    if (is_subplot) {
        // Save the current transformation matrix
        cairo_save(cr);
        
        // Apply subplot transformation: translate first, then scale
        cairo_translate(cr, subplot_x_offset, subplot_y_offset);
        cairo_scale(cr, subplot_width_scale, subplot_height_scale);
        
        // Draw all plot elements within the transformed coordinate system
        draw_grid(cr);
        draw_axes(cr);
        draw_axis_ticks(cr);
        draw_axis_labels(cr);
        draw_title(cr);
        draw_cluster_points(cr);
        draw_points(cr);
        draw_legend(cr);
        
        // Restore the transformation matrix
        cairo_restore(cr);
    } else {
        // Regular single plot rendering
        draw_grid(cr);
        draw_axes(cr);
        draw_axis_ticks(cr);
        draw_axis_labels(cr);
        draw_title(cr);
        draw_cluster_points(cr);
        draw_points(cr);
        draw_legend(cr);
    }
}

std::unique_ptr<ScatterPlot> ScatterPlot::clone() const {
    auto cloned = std::make_unique<ScatterPlot>(width, height);
    
    // Copy all data
    cloned->data_series = data_series;
    cloned->cluster_series = cluster_series;
    cloned->title = title;
    cloned->x_label = x_label;
    cloned->y_label = y_label;
    cloned->min_x = min_x;
    cloned->max_x = max_x;
    cloned->min_y = min_y;
    cloned->max_y = max_y;
    cloned->bounds_set = bounds_set;
    
    return cloned;
}

void ScatterPlot::clear() {
    data_series.clear();
    cluster_series.clear();
    bounds_set = false;
    title = "";
    x_label = "";
    y_label = "";
    is_subplot = false;
    subplot_x_offset = 0;
    subplot_y_offset = 0;
    subplot_width_scale = 1.0;
    subplot_height_scale = 1.0;
}

// SubplotManager implementation
SubplotManager::SubplotManager(int rows, int cols, int width, int height, double spacing) 
    : layout(rows, cols, spacing), total_width(width), total_height(height) {
    
    // Calculate available space for plots (excluding spacing and title)
    double total_spacing_width = spacing * width * (cols + 1);
    double total_spacing_height = spacing * height * (rows + 1);
    
    // Reserve space for main title - will be calculated more precisely later
    double title_height = 30.0;  // Conservative estimate
    double available_width = width - total_spacing_width;
    double available_height = height - total_spacing_height - title_height;
    
    // Calculate individual subplot dimensions
    double subplot_width = available_width / cols;
    double subplot_height = available_height / rows;
    
    // Initialize subplot grid
    subplots.resize(rows);
    for (int i = 0; i < rows; ++i) {
        subplots[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            // Create subplot with standard size (will be scaled during rendering)
            subplots[i][j] = std::make_unique<ScatterPlot>(800, 600);
            
            // Calculate position for this subplot
            double x_offset = spacing * width + j * (subplot_width + spacing * width);
            double y_offset = spacing * height + i * (subplot_height + spacing * height);
            
            // Calculate the total height of the subplot grid
            double total_subplot_height = rows * subplot_height + (rows - 1) * spacing * height;
            double total_content_height = total_subplot_height + title_height;
            
            // Center the entire content (title + subplots) vertically
            double vertical_center_offset = (height - total_content_height) / 2.0;
            y_offset += vertical_center_offset + title_height;
            
            // Calculate scale factors to fit the subplot into the allocated space while preserving aspect ratio
            double width_scale = subplot_width / 800.0;   // Scale from standard 800 width
            double height_scale = subplot_height / 600.0; // Scale from standard 600 height
            
            // Use the smaller scale factor to preserve aspect ratio
            double uniform_scale = std::min(width_scale, height_scale);
            
            // Center the subplot within its allocated space
            double actual_width = 800.0 * uniform_scale;
            double actual_height = 600.0 * uniform_scale;
            double center_x_offset = (subplot_width - actual_width) / 2.0;
            double center_y_offset = (subplot_height - actual_height) / 2.0;
            
            x_offset += center_x_offset;
            y_offset += center_y_offset;
            
            subplots[i][j]->set_subplot_transform(x_offset, y_offset, uniform_scale, uniform_scale);
        }
    }
}

ScatterPlot& SubplotManager::get_subplot(int row, int col) {
    if (row < 0 || row >= layout.rows || col < 0 || col >= layout.cols) {
        throw std::out_of_range("Subplot indices out of range");
    }
    return *subplots[row][col];
}

void SubplotManager::set_main_title(const std::string& title) {
    main_title = title;
}

double SubplotManager::get_title_height(cairo_t* cr) const {
    if (main_title.empty()) return 0.0;
    
    cairo_save(cr);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    
    cairo_text_extents_t extents;
    cairo_text_extents(cr, main_title.c_str(), &extents);
    cairo_restore(cr);
    
    return extents.height + 10;  // Text height + minimal padding
}

void SubplotManager::draw_main_title(cairo_t* cr) {
    if (main_title.empty()) return;
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    
    cairo_text_extents_t extents;
    cairo_text_extents(cr, main_title.c_str(), &extents);
    double x_pos = (total_width - extents.width) / 2;
    
    // Calculate the same centering offset as used for subplots
    double actual_title_height = get_title_height(cr);
    double total_spacing_height = layout.spacing * total_height * (layout.rows + 1);
    double available_height = total_height - total_spacing_height - actual_title_height;
    double subplot_height = available_height / layout.rows;
    double total_subplot_height = layout.rows * subplot_height + (layout.rows - 1) * layout.spacing * total_height;
    double total_content_height = total_subplot_height + actual_title_height;
    double vertical_center_offset = (total_height - total_content_height) / 2.0;
    
    // Position title at the top of the centered content
    double title_y = vertical_center_offset + extents.height + 5;  // Minimal padding from top
    cairo_move_to(cr, x_pos, title_y);
    cairo_show_text(cr, main_title.c_str());
}

void SubplotManager::render_to_context(cairo_t* cr) {
    // White background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    
    // Recalculate positions with actual title height
    double actual_title_height = get_title_height(cr);
    double total_spacing_width = layout.spacing * total_width * (layout.cols + 1);
    double total_spacing_height = layout.spacing * total_height * (layout.rows + 1);
    double available_width = total_width - total_spacing_width;
    double available_height = total_height - total_spacing_height - actual_title_height;
    
    double subplot_width = available_width / layout.cols;
    double subplot_height = available_height / layout.rows;
    
    // Calculate total content dimensions for centering
    double total_subplot_height = layout.rows * subplot_height + (layout.rows - 1) * layout.spacing * total_height;
    double total_content_height = total_subplot_height + actual_title_height;
    double vertical_center_offset = (total_height - total_content_height) / 2.0;
    
    // Update subplot positions
    for (int i = 0; i < layout.rows; ++i) {
        for (int j = 0; j < layout.cols; ++j) {
            if (subplots[i][j]) {
                double x_offset = layout.spacing * total_width + j * (subplot_width + layout.spacing * total_width);
                double y_offset = layout.spacing * total_height + i * (subplot_height + layout.spacing * total_height);
                y_offset += vertical_center_offset + actual_title_height;
                
                // Calculate scale factors with aspect ratio preservation
                double width_scale = subplot_width / 800.0;
                double height_scale = subplot_height / 600.0;
                double uniform_scale = std::min(width_scale, height_scale);
                
                // Center the subplot within its allocated space
                double actual_width = 800.0 * uniform_scale;
                double actual_height = 600.0 * uniform_scale;
                double center_x_offset = (subplot_width - actual_width) / 2.0;
                double center_y_offset = (subplot_height - actual_height) / 2.0;
                
                x_offset += center_x_offset;
                y_offset += center_y_offset;
                
                subplots[i][j]->set_subplot_transform(x_offset, y_offset, uniform_scale, uniform_scale);
            }
        }
    }
    
    // Draw main title
    draw_main_title(cr);
    
    // Render each subplot
    for (int i = 0; i < layout.rows; ++i) {
        for (int j = 0; j < layout.cols; ++j) {
            subplots[i][j]->render_to_context(cr);
        }
    }
}

bool SubplotManager::save_png(const std::string& filename) {
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, total_width, total_height);
    cairo_t* cr = cairo_create(surface);
    
    render_to_context(cr);
    
    cairo_status_t status = cairo_surface_write_to_png(surface, filename.c_str());
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
    return status == CAIRO_STATUS_SUCCESS;
}

bool SubplotManager::save_svg(const std::string& filename) {
    cairo_surface_t* surface = cairo_svg_surface_create(filename.c_str(), total_width, total_height);
    cairo_t* cr = cairo_create(surface);
    
    render_to_context(cr);
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
    return true;
}
