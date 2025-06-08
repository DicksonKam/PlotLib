/**
 * @file histogram_plot.h
 * @brief Histogram plotting functionality
 * 
 * This file contains the HistogramPlot class for creating histogram visualizations
 * with support for multiple series, custom binning, and subplot integration.
 */

#pragma once

#include "plot_manager.h"
#include <vector>
#include <string>

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
 */
class HistogramPlot : public PlotManager {
private:
    std::vector<HistogramData> histogram_series; ///< Collection of histogram data series
    int default_bin_count = 20;                  ///< Default number of bins for auto-binning
    bool normalize = false;                      ///< Whether to normalize histograms to probability density
    bool cumulative = false;                     ///< Whether to show cumulative distribution
    
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

public:
    /**
     * @brief Constructor
     * @param w Width of the plot in pixels
     * @param h Height of the plot in pixels
     */
    HistogramPlot(int w, int h);
    
    /**
     * @brief Add histogram data with automatic binning
     * @param name Series name
     * @param data Raw data values
     * @param style Visual style for the histogram
     * @param bin_count Number of bins (0 for automatic)
     */
    void add_data(const std::string& name, const std::vector<double>& data, 
                  const PlotStyle& style, int bin_count = 0);
    
    /**
     * @brief Add histogram data with custom bins
     * @param name Series name
     * @param data Raw data values
     * @param bins Custom bin edges
     * @param style Visual style for the histogram
     */
    void add_data_with_bins(const std::string& name, const std::vector<double>& data,
                           const std::vector<double>& bins, const PlotStyle& style);
    
    /**
     * @brief Set default number of bins for automatic binning
     * @param count Number of bins
     */
    void set_default_bin_count(int count);
    
    /**
     * @brief Enable or disable normalization to probability density
     * @param enable Whether to normalize
     */
    void set_normalize(bool enable);
    
    /**
     * @brief Enable or disable cumulative distribution
     * @param enable Whether to show cumulative distribution
     */
    void set_cumulative(bool enable);
    
    /**
     * @brief Get histogram statistics for a series
     * @param series_name Name of the series
     * @return Pair of (mean, standard_deviation)
     */
    std::pair<double, double> get_statistics(const std::string& series_name) const;

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