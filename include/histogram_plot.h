/**
 * @file histogram_plot.h
 * @brief Histogram plotting implementation using PlotManager
 * @author PlotLib Contributors
 * @version 1.0.0
 * @date 2025-06-08
 * 
 * This file contains the HistogramPlot class for creating histogram visualizations
 * with support for multiple series, custom binning, and subplot integration.
 */

#ifndef PLOTLIB_HISTOGRAM_PLOT_H
#define PLOTLIB_HISTOGRAM_PLOT_H

#include "plot_manager.h"

namespace plotlib {

/**
 * @brief Structure representing histogram data
 */
struct HistogramData {
    std::vector<double> values;  ///< Raw data values
    std::vector<double> bins;    ///< Bin edges (n+1 edges for n bins)
    std::vector<int> counts;     ///< Frequency counts for each bin
    std::string name;            ///< Series name
    PlotStyle style;             ///< Visual style
    
    HistogramData(const std::string& series_name = "Default") : name(series_name) {}
};

/**
 * @brief Histogram plot class for creating frequency distribution visualizations
 * 
 * The HistogramPlot class extends PlotManager to provide histogram-specific functionality
 * including automatic binning, custom bin specification, and multiple histogram series.
 * 
 * Features:
 * - Automatic and manual binning using Sturges' rule or custom bin counts
 * - Multiple histogram series with automatic coloring
 * - Configurable bin width and frequency counting
 * - Support for overlapping histograms and comparisons
 * - All PlotManager features (axes, legends, titles, subplots)
 * 
 * @example
 * @code
 * HistogramPlot plot(800, 600);
 * plot.set_labels("Data Distribution", "Values", "Frequency");
 * 
 * std::vector<double> data = {1.0, 2.1, 1.8, 3.2, 2.9, 1.5, 2.8, 3.1};
 * plot.add_histogram("Dataset 1", data, 10); // 10 bins
 * 
 * plot.save_png("histogram.png");
 * @endcode
 */
class HistogramPlot : public PlotManager {
private:
    std::vector<HistogramData> histogram_series; ///< Collection of histogram data series
    int default_bin_count = 20;                  ///< Default number of bins for auto-binning
    
    /**
     * @brief Calculate optimal bin edges using Sturges' rule or custom count
     * @param data Input data values
     * @param bin_count Number of bins (0 for automatic)
     * @return Vector of bin edges
     */
    std::vector<double> calculate_bins(const std::vector<double>& data, int bin_count = 0);
    
    /**
     * @brief Calculate histogram counts for given data and bins
     * @param data Input data values
     * @param bins Bin edges
     * @return Vector of frequency counts
     */
    std::vector<int> calculate_counts(const std::vector<double>& data, const std::vector<double>& bins);
    
    /**
     * @brief Calculate cumulative counts from frequency counts
     * @param counts Frequency counts
     * @return Vector of cumulative counts
     */
    std::vector<int> calculate_cumulative(const std::vector<int>& counts);
    
    /**
     * @brief Internal method to add histogram data (used by public methods)
     * @param name Series name
     * @param data Raw data values
     * @param style Visual style for the histogram
     * @param bin_count Number of bins (0 for automatic)
     */
    void add_data(const std::string& name, const std::vector<double>& data, 
                  const PlotStyle& style, int bin_count = 0);

public:
    /**
     * @brief Constructor for HistogramPlot
     * @param width Canvas width in pixels (default: 800)
     * @param height Canvas height in pixels (default: 600)
     */
    HistogramPlot(int width = 800, int height = 600);
    
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~HistogramPlot() = default;
    
    /**
     * @brief Add histogram data with automatic styling (beginner-friendly)
     * @param name Series name for legend
     * @param values Raw data values for histogram
     * @param bin_count Optional number of bins (0 for automatic)
     */
    void add_histogram(const std::string& name, const std::vector<double>& values, int bin_count = 0);
    
    /**
     * @brief Add histogram data with custom color (beginner-friendly)
     * @param name Series name for legend
     * @param values Raw data values for histogram
     * @param color_name Color name ("red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow")
     * @param bin_count Optional number of bins (0 for automatic)
     */
    void add_histogram(const std::string& name, const std::vector<double>& values, 
                      const std::string& color_name, int bin_count = 0);

protected:
    /**
     * @brief Draw histogram bars
     * @param cr Cairo context
     */
    void draw_data(cairo_t* cr) override;
    
    /**
     * @brief Calculate bounds from histogram data
     */
    void calculate_bounds() override;
    
    /**
     * @brief Clear all histogram data
     */
    void clear() override;
};

} // namespace plotlib 

#endif // PLOTLIB_HISTOGRAM_PLOT_H