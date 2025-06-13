#include "histogram_plot.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iostream>
#include <stdexcept>

namespace plotlib {

HistogramPlot::HistogramPlot(int width, int height) : PlotManager(width, height) {
    // Set default Y label for histograms
    y_label = "Frequency";
}

std::vector<double> HistogramPlot::calculate_bins(const std::vector<double>& data, int bin_count) {
    if (data.empty()) return {};
    
    auto minmax = std::minmax_element(data.begin(), data.end());
    double min_val = *minmax.first;
    double max_val = *minmax.second;
    
    // Use Sturges' rule if bin_count is 0
    if (bin_count <= 0) {
        bin_count = std::max(1, static_cast<int>(std::ceil(std::log2(data.size()) + 1)));
        bin_count = std::min(bin_count, default_bin_count); // Cap at default
    }
    
    std::vector<double> bins;
    double bin_width = (max_val - min_val) / bin_count;
    
    for (int i = 0; i <= bin_count; ++i) {
        bins.push_back(min_val + i * bin_width);
    }
    
    // Ensure the last bin includes the maximum value
    if (!bins.empty()) {
        bins.back() = max_val + 1e-10; // Small epsilon to include max value
    }
    
    return bins;
}

std::vector<int> HistogramPlot::calculate_counts(const std::vector<double>& data, const std::vector<double>& bins) {
    if (bins.size() < 2) return {};
    
    std::vector<int> counts(bins.size() - 1, 0);
    
    for (double value : data) {
        // Find the appropriate bin
        for (size_t i = 0; i < bins.size() - 1; ++i) {
            if (value >= bins[i] && value < bins[i + 1]) {
                counts[i]++;
                break;
            }
        }
    }
    
    return counts;
}

std::vector<int> HistogramPlot::calculate_cumulative(const std::vector<int>& counts) {
    std::vector<int> cumulative(counts.size());
    if (!counts.empty()) {
        cumulative[0] = counts[0];
        for (size_t i = 1; i < counts.size(); ++i) {
            cumulative[i] = cumulative[i - 1] + counts[i];
        }
    }
    return cumulative;
}

bool HistogramPlot::has_discrete_histograms() const {
    for (const auto& hist_data : histogram_series) {
        if (hist_data.is_discrete) {
            return true;
        }
    }
    return false;
}

void HistogramPlot::validate_histogram_type_compatibility(bool is_new_discrete) {
    if (histogram_series.empty()) {
        return; // First histogram, no conflict possible
    }
    
    bool has_discrete = has_discrete_histograms();
    bool has_continuous = false;
    
    for (const auto& hist_data : histogram_series) {
        if (!hist_data.is_discrete) {
            has_continuous = true;
            break;
        }
    }
    
    if (is_new_discrete && has_continuous) {
        throw std::invalid_argument("Error: Cannot mix discrete and continuous histograms in the same plot. "
                                   "Discrete histograms use categorical X-axis while continuous histograms use numeric X-axis. "
                                   "Please create separate plots for different histogram types.");
    }
    
    if (!is_new_discrete && has_discrete) {
        throw std::invalid_argument("Error: Cannot mix continuous and discrete histograms in the same plot. "
                                   "Continuous histograms use numeric X-axis while discrete histograms use categorical X-axis. "
                                   "Please create separate plots for different histogram types.");
    }
}

void HistogramPlot::add_data(const std::string& name, const std::vector<double>& data, 
                            const PlotStyle& style, int bin_count) {
    if (data.empty()) {
        std::cerr << "Error: Empty data provided for histogram series '" << name << "'" << std::endl;
        return;
    }
    
    // Validate that we're not mixing histogram types
    validate_histogram_type_compatibility(false); // false = continuous
    
    HistogramData hist_data(name);
    hist_data.values = data;
    hist_data.style = style;
    hist_data.bins = calculate_bins(data, bin_count);
    hist_data.counts = calculate_counts(data, hist_data.bins);
    
    histogram_series.push_back(hist_data);
    bounds_set = false;
}



void HistogramPlot::calculate_bounds() {
    if (histogram_series.empty()) return;
    
    bool first = true;
    bool has_discrete = false;
    double discrete_max_x = 0;
    
    for (const auto& hist_data : histogram_series) {
        if (hist_data.counts.empty()) continue;
        
        double series_min_x, series_max_x;
        
        if (hist_data.is_discrete) {
            // For discrete data, X bounds are based on category indices
            has_discrete = true;
            series_min_x = 0.0;
            series_max_x = static_cast<double>(hist_data.counts.size() - 1);  // Use last index, not count
            discrete_max_x = std::max(discrete_max_x, series_max_x);
        } else {
            // For continuous data, X bounds from bin edges
            if (hist_data.bins.empty()) continue;
            series_min_x = hist_data.bins.front();
            series_max_x = hist_data.bins.back();
        }
        
        // Y bounds from counts
        auto minmax_y = std::minmax_element(hist_data.counts.begin(), hist_data.counts.end());
        double series_min_y = 0.0; // Histograms always start from 0
        double series_max_y = static_cast<double>(*minmax_y.second);
        
        if (first) {
            min_x = series_min_x;
            max_x = series_max_x;
            min_y = series_min_y;
            max_y = series_max_y;
            first = false;
        } else {
            min_x = std::min(min_x, series_min_x);
            max_x = std::max(max_x, series_max_x);
            min_y = std::min(min_y, series_min_y);
            max_y = std::max(max_y, series_max_y);
        }
    }
    
    // Add some padding
    double x_range = max_x - min_x;
    double y_range = max_y - min_y;
    
    if (x_range == 0) x_range = 1;
    if (y_range == 0) y_range = 1;
    
    if (has_discrete) {
        // For discrete data, provide padding for category visualization
        min_x = -0.5;
        max_x = discrete_max_x + 0.5;
    } else {
        // For continuous data, use minimal padding
        min_x -= x_range * 0.02;
        max_x += x_range * 0.02;
    }
    
    min_y = 0; // Keep Y minimum at 0 for histograms
    max_y += y_range * 0.05;
    
    bounds_set = true;
}

void HistogramPlot::draw_data(cairo_t* cr) {
    if (!bounds_set) {
        calculate_bounds();
    }
    
    for (const auto& hist_data : histogram_series) {
        if (hist_data.counts.empty()) continue;
        
        if (hist_data.is_discrete) {
            // Draw discrete histogram bars
            double bar_width = 0.8; // Width of each discrete bar (leave space between bars)
            
            for (size_t i = 0; i < hist_data.counts.size(); ++i) {
                double count = static_cast<double>(hist_data.counts[i]);
                if (count == 0) continue; // Skip empty categories
                
                // Use individual style for each category
                const PlotStyle& category_style = (i < hist_data.styles.size()) ? hist_data.styles[i] : hist_data.style;
                cairo_set_source_rgba(cr, category_style.r, category_style.g, category_style.b, category_style.alpha);
                
                // Calculate bar position (centered on integer x-values)
                double x_center = static_cast<double>(i);
                double bar_left = x_center - bar_width / 2.0;
                double bar_right = x_center + bar_width / 2.0;
                
                // Transform to screen coordinates
                double screen_left, screen_bottom, screen_right, screen_top;
                transform_point(bar_left, 0, screen_left, screen_bottom);
                transform_point(bar_right, count, screen_right, screen_top);
                
                // Draw filled rectangle
                cairo_rectangle(cr, screen_left, screen_top, screen_right - screen_left, screen_bottom - screen_top);
                cairo_fill_preserve(cr);
                
                // Draw border with darker color
                cairo_set_source_rgba(cr, category_style.r * 0.7, category_style.g * 0.7, category_style.b * 0.7, category_style.alpha);
                cairo_set_line_width(cr, 1.0);
                cairo_stroke(cr);
            }
        } else {
            // Draw continuous histogram bars
            if (hist_data.bins.empty()) continue;
            
            // Set color and style
            cairo_set_source_rgba(cr, hist_data.style.r, hist_data.style.g, hist_data.style.b, hist_data.style.alpha);
            
            // Draw histogram bars
            for (size_t i = 0; i < hist_data.counts.size() && i < hist_data.bins.size() - 1; ++i) {
                double bin_left = hist_data.bins[i];
                double bin_right = hist_data.bins[i + 1];
                double count = static_cast<double>(hist_data.counts[i]);
                
                // Transform to screen coordinates
                double screen_left, screen_bottom, screen_right, screen_top;
                transform_point(bin_left, 0, screen_left, screen_bottom);
                transform_point(bin_right, count, screen_right, screen_top);
                
                // Draw filled rectangle
                cairo_rectangle(cr, screen_left, screen_top, screen_right - screen_left, screen_bottom - screen_top);
                cairo_fill_preserve(cr);
                
                // Draw border
                cairo_set_source_rgba(cr, hist_data.style.r * 0.7, hist_data.style.g * 0.7, hist_data.style.b * 0.7, hist_data.style.alpha);
                cairo_set_line_width(cr, 1.0);
                cairo_stroke(cr);
                
                // Restore fill color for next bar
                cairo_set_source_rgba(cr, hist_data.style.r, hist_data.style.g, hist_data.style.b, hist_data.style.alpha);
            }
        }
    }
}

void HistogramPlot::draw_axis_ticks(cairo_t* cr) {
    // Check if we have any discrete data
    bool has_discrete = false;
    for (const auto& hist_data : histogram_series) {
        if (hist_data.is_discrete) {
            has_discrete = true;
            break;
        }
    }
    
    if (has_discrete) {
        // For discrete histograms, only draw Y-axis ticks (no X-axis numeric ticks)
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 1.0);
        cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10);
        
        // Y-axis ticks only
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
    } else {
        // Use parent implementation for continuous data
        PlotManager::draw_axis_ticks(cr);
    }
}

void HistogramPlot::draw_axis_labels(cairo_t* cr) {
    // Check if we have any discrete data
    bool has_discrete = false;
    for (const auto& hist_data : histogram_series) {
        if (hist_data.is_discrete) {
            has_discrete = true;
            break;
        }
    }
    
    if (has_discrete) {
        // Draw custom X-axis labels for discrete data
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12);
        
        // Draw discrete category labels
        for (const auto& hist_data : histogram_series) {
            if (hist_data.is_discrete && !hist_data.categories.empty()) {
                for (size_t i = 0; i < hist_data.categories.size(); ++i) {
                    double x_pos = static_cast<double>(i);
                    double screen_x, screen_y;
                    transform_point(x_pos, min_y, screen_x, screen_y);
                    
                    // Draw category label
                    const std::string& label = hist_data.categories[i];
                    cairo_text_extents_t extents;
                    cairo_text_extents(cr, label.c_str(), &extents);
                    cairo_move_to(cr, screen_x - extents.width/2, height - margin_bottom + 20);
                    cairo_show_text(cr, label.c_str());
                }
                break; // Only use the first discrete series for labels
            }
        }
        
        // Draw axis labels (X and Y)
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
    } else {
        // Use parent implementation for continuous data
        PlotManager::draw_axis_labels(cr);
    }
}

void HistogramPlot::draw_legend(cairo_t* cr) {
    if (!show_legend) return;
    
    // Check if we have any discrete data
    bool has_discrete = false;
    for (const auto& hist_data : histogram_series) {
        if (hist_data.is_discrete) {
            has_discrete = true;
            break;
        }
    }
    
    if (has_discrete) {
        // Custom legend for discrete histograms
        std::vector<std::pair<std::string, PlotStyle>> legend_items;
        
        // Add discrete histogram categories
        for (const auto& hist_data : histogram_series) {
            if (hist_data.is_discrete && !hist_data.categories.empty()) {
                for (size_t i = 0; i < hist_data.categories.size(); ++i) {
                    if (i < hist_data.styles.size() && hist_data.counts[i] > 0 && 
                        hidden_legend_items.find(hist_data.categories[i]) == hidden_legend_items.end()) {
                        // Only show categories that have data and are not hidden
                        legend_items.emplace_back(hist_data.categories[i], hist_data.styles[i]);
                    }
                }
            }
        }
        
        // Add continuous histogram series if any
        for (const auto& hist_data : histogram_series) {
            if (!hist_data.is_discrete && !hist_data.name.empty() && hist_data.name != "Default") {
                legend_items.emplace_back(hist_data.name, hist_data.style);
            }
        }
        
        if (legend_items.empty()) return;
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10);
        
        double legend_x = width - margin_right + 10;
        double legend_y = margin_top + 20;
        double line_height = 20;
        
        // Draw legend background
        double legend_width = 120;
        double legend_height = legend_items.size() * line_height + 10;
        cairo_set_source_rgba(cr, 1, 1, 1, 0.9);
        cairo_rectangle(cr, legend_x - 5, legend_y - 15, legend_width, legend_height);
        cairo_fill(cr);
        
        cairo_set_source_rgba(cr, 0, 0, 0, 0.3);
        cairo_rectangle(cr, legend_x - 5, legend_y - 15, legend_width, legend_height);
        cairo_stroke(cr);
        
        // Draw legend items
        for (size_t i = 0; i < legend_items.size(); ++i) {
            double y_pos = legend_y + i * line_height;
            
            // Draw colored rectangle for histogram bars
            cairo_set_source_rgba(cr, legend_items[i].second.r, legend_items[i].second.g, 
                                 legend_items[i].second.b, legend_items[i].second.alpha);
            cairo_rectangle(cr, legend_x + 2, y_pos - 4, 12, 8);
            cairo_fill(cr);
            
            // Draw border
            cairo_set_source_rgba(cr, legend_items[i].second.r * 0.7, legend_items[i].second.g * 0.7, 
                                 legend_items[i].second.b * 0.7, legend_items[i].second.alpha);
            cairo_rectangle(cr, legend_x + 2, y_pos - 4, 12, 8);
            cairo_stroke(cr);
            
            // Draw text
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_move_to(cr, legend_x + 20, y_pos + 4);
            cairo_show_text(cr, legend_items[i].first.c_str());
        }
    } else {
        // Use parent implementation for continuous data
        PlotManager::draw_legend(cr);
    }
}

void HistogramPlot::clear() {
    PlotManager::clear();
    histogram_series.clear();
    y_label = "Frequency";
}

// Continuous histogram methods with new parameter ordering (data->naming->colors)
void HistogramPlot::add_histogram(const std::vector<double>& values, const std::string& name, 
                                 const std::string& color_name, int bin_count) {
    add_data(name, values, color_to_style(color_name, 3.0, 2.0), bin_count);
}

void HistogramPlot::add_histogram(const std::vector<double>& values, const std::string& name, int bin_count) {
    // Use automatic color based on series count
    std::string color = get_auto_color(histogram_series.size());
    add_data(name, values, color_to_style(color, 3.0, 2.0), bin_count);
}

void HistogramPlot::add_histogram(const std::vector<double>& values, int bin_count) {
    std::string auto_name = "Histogram " + std::to_string(histogram_series.size() + 1);
    add_histogram(values, auto_name, bin_count);
}

// Discrete histogram methods with simplified API (counts and names only)
void HistogramPlot::add_histogram(const std::vector<int>& counts, const std::vector<std::string>& names,
                                 const std::vector<std::string>& color_names) {
    if (color_names.size() != counts.size()) {
        std::cerr << "Error: Number of colors (" << color_names.size() << ") must match number of categories (" << counts.size() << ")" << std::endl;
        return;
    }
    
    if (names.size() != counts.size()) {
        std::cerr << "Error: Number of names (" << names.size() << ") must match number of categories (" << counts.size() << ")" << std::endl;
        return;
    }
    
    // Convert color names to PlotStyle objects
    std::vector<PlotStyle> styles;
    for (const auto& color_name : color_names) {
        styles.push_back(color_to_style(color_name, 3.0, 2.0));
    }
    
    add_discrete_data_simplified("Discrete", counts, names, styles);
}

void HistogramPlot::add_histogram(const std::vector<int>& counts, const std::vector<std::string>& names) {
    if (names.size() != counts.size()) {
        std::cerr << "Error: Number of names (" << names.size() << ") must match number of categories (" << counts.size() << ")" << std::endl;
        return;
    }
    
    // Generate automatic colors for each category
    std::vector<PlotStyle> styles;
    for (size_t i = 0; i < counts.size(); ++i) {
        std::string color = get_auto_color(histogram_series.size() * counts.size() + i);
        styles.push_back(color_to_style(color, 3.0, 2.0));
    }
    
    add_discrete_data_simplified("Discrete", counts, names, styles);
}

void HistogramPlot::add_histogram(const std::vector<int>& counts) {
    // Generate automatic names: idx 1, idx 2, idx 3, ...
    std::vector<std::string> auto_names;
    for (size_t i = 0; i < counts.size(); ++i) {
        auto_names.push_back("idx " + std::to_string(i + 1));
    }
    
    add_histogram(counts, auto_names);
}

void HistogramPlot::add_discrete_data(const std::string& name, const std::vector<int>& counts, 
                                     const std::string& category_prefix, const std::vector<PlotStyle>& styles) {
    if (counts.empty()) {
        std::cerr << "Error: Empty count data provided for discrete histogram series '" << name << "'" << std::endl;
        return;
    }
    
    // Validate that we're not mixing histogram types
    validate_histogram_type_compatibility(true); // true = discrete
    
    if (styles.size() != counts.size()) {
        std::cerr << "Error: Number of styles (" << styles.size() << ") must match number of categories (" << counts.size() << ")" << std::endl;
        return;
    }
    
    HistogramData hist_data(name);
    hist_data.is_discrete = true;
    hist_data.category_prefix = category_prefix;
    hist_data.counts = counts;
    hist_data.styles = styles;
    
    // Generate category names
    for (size_t i = 0; i < counts.size(); ++i) {
        hist_data.categories.push_back(category_prefix + " " + std::to_string(i + 1));
    }
    
    // Use the first style as the main style for legend purposes
    hist_data.style = styles[0];
    
    histogram_series.push_back(hist_data);
    bounds_set = false;
}

void HistogramPlot::add_discrete_data_simplified(const std::string& name, const std::vector<int>& counts, 
                                                const std::vector<std::string>& names, const std::vector<PlotStyle>& styles) {
    if (counts.empty()) {
        std::cerr << "Error: Empty count data provided for discrete histogram series '" << name << "'" << std::endl;
        return;
    }
    
    // Validate that we're not mixing histogram types
    validate_histogram_type_compatibility(true); // true = discrete
    
    if (styles.size() != counts.size()) {
        std::cerr << "Error: Number of styles (" << styles.size() << ") must match number of categories (" << counts.size() << ")" << std::endl;
        return;
    }
    
    if (names.size() != counts.size()) {
        std::cerr << "Error: Number of names (" << names.size() << ") must match number of categories (" << counts.size() << ")" << std::endl;
        return;
    }
    
    HistogramData hist_data(name);
    hist_data.is_discrete = true;
    hist_data.counts = counts;
    hist_data.styles = styles;
    hist_data.categories = names; // Use provided names directly
    
    // Use the first style as the main style for legend purposes
    hist_data.style = styles[0];
    
    histogram_series.push_back(hist_data);
    bounds_set = false;
}

bool HistogramPlot::is_plot_empty() const {
    // HistogramPlot is empty if the histogram_series collection is empty
    // OR if all histogram series contain no data points
    if (histogram_series.empty()) {
        return true;
    }
    
    // Check if all histogram series have empty data
    for (const auto& hist : histogram_series) {
        if (!hist.bins.empty() || !hist.counts.empty()) {
            return false;  // Found non-empty histogram data
        }
    }
    
    return true;  // All histograms are empty
}

} // namespace plotlib 