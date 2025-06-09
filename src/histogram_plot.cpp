#include "histogram_plot.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iostream>

namespace plotlib {

HistogramPlot::HistogramPlot(int w, int h) : PlotManager(w, h) {
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

void HistogramPlot::add_data(const std::string& name, const std::vector<double>& data, 
                            const PlotStyle& style, int bin_count) {
    if (data.empty()) {
        std::cerr << "Warning: Empty data provided for histogram series '" << name << "'" << std::endl;
        return;
    }
    
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
    
    for (const auto& hist_data : histogram_series) {
        if (hist_data.bins.empty() || hist_data.counts.empty()) continue;
        
        // X bounds from bin edges
        double series_min_x = hist_data.bins.front();
        double series_max_x = hist_data.bins.back();
        
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
    
    min_x -= x_range * 0.02; // Less padding for histograms
    max_x += x_range * 0.02;
    min_y = 0; // Keep Y minimum at 0 for histograms
    max_y += y_range * 0.05;
    
    bounds_set = true;
}

void HistogramPlot::draw_data(cairo_t* cr) {
    if (!bounds_set) {
        calculate_bounds();
    }
    
    for (const auto& hist_data : histogram_series) {
        if (hist_data.bins.empty() || hist_data.counts.empty()) continue;
        
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

void HistogramPlot::clear() {
    PlotManager::clear();
    histogram_series.clear();
    y_label = "Frequency";
}

// Beginner-friendly convenience methods
void HistogramPlot::add_histogram(const std::string& name, const std::vector<double>& data, int bins) {
    // Use automatic color based on series count
    std::string color = get_auto_color(histogram_series.size());
    add_data(name, data, color_to_style(color, 3.0, 2.0), bins);
}

void HistogramPlot::add_histogram(const std::string& name, const std::vector<double>& data, 
                                 const std::string& color_name, int bins) {
    add_data(name, data, color_to_style(color_name, 3.0, 2.0), bins);
}

} // namespace plotlib 