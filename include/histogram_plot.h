/**
 * @file histogram_plot.h
 * @brief Histogram plotting implementation using PlotManager
 * @author PlotLib Contributors
 * @version 1.0.0
 * @date 2024-06-08
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
    std::vector<double> values;         ///< Raw data values (for continuous data)
    std::vector<double> bins;           ///< Bin edges (n+1 edges for n bins, for continuous data)
    std::vector<int> counts;            ///< Frequency counts for each bin
    std::string name;                   ///< Series name
    PlotStyle style;                    ///< Visual style
    
    // Discrete histogram data
    std::vector<std::string> categories; ///< Category names (for discrete data)
    std::vector<PlotStyle> styles;       ///< Individual styles for each category (for discrete data)
    bool is_discrete = false;            ///< Flag to indicate if this is discrete data
    std::string category_prefix = "";    ///< Prefix for category labels (e.g., "structure")
    
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
     * @brief Check if mixing histogram types is allowed
     * @param is_new_discrete Whether the new histogram being added is discrete
     * @throws std::invalid_argument if mixing continuous and discrete histograms
     */
    void validate_histogram_type_compatibility(bool is_new_discrete);
    
    /**
     * @brief Check if we have any discrete histograms in the current series
     * @return true if any discrete histograms exist
     */
    bool has_discrete_histograms() const;
    
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
    
    /**
     * @brief Internal method to add discrete histogram data (used by public methods)
     * @param name Series name
     * @param counts Frequency counts for each category
     * @param category_prefix Prefix for category labels
     * @param styles Visual styles for each category
     */
    void add_discrete_data(const std::string& name, const std::vector<int>& counts, 
                          const std::string& category_prefix, const std::vector<PlotStyle>& styles);
    
    /**
     * @brief Internal method to add simplified discrete histogram data (used by new API)
     * @param name Series name
     * @param counts Frequency counts for each category
     * @param names Category names (used for both legend and x-axis labels)
     * @param styles Visual styles for each category
     */
    void add_discrete_data_simplified(const std::string& name, const std::vector<int>& counts, 
                                     const std::vector<std::string>& names, const std::vector<PlotStyle>& styles);

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
     * @brief Add continuous histogram data with custom color and bin count
     * @param values Raw data values for histogram
     * @param name Series name for legend
     * @param color_name Color name ("red", "blue", "green", "orange", "purple", "cyan", "magenta", "yellow")
     * @param bin_count Number of bins (0 for automatic)
     */
    void add_histogram(const std::vector<double>& values, const std::string& name, 
                      const std::string& color_name, int bin_count = 0);
    
    /**
     * @brief Add continuous histogram data with automatic styling
     * @param values Raw data values for histogram
     * @param name Series name for legend
     * @param bin_count Number of bins (0 for automatic)
     */
    void add_histogram(const std::vector<double>& values, const std::string& name, int bin_count = 0);
    
    /**
     * @brief Add continuous histogram data with auto-generated name
     * @param values Raw data values for histogram
     * @param bin_count Number of bins (0 for automatic)
     */
    void add_histogram(const std::vector<double>& values, int bin_count = 0);
    
    /**
     * @brief Add discrete histogram data with custom colors
     * @param counts Frequency counts for each discrete category
     * @param names Category names for X-axis labels and legend
     * @param color_names Vector of color names for each category
     */
    void add_histogram(const std::vector<int>& counts, const std::vector<std::string>& names,
                      const std::vector<std::string>& color_names);
    
    /**
     * @brief Add discrete histogram data with automatic styling
     * @param counts Frequency counts for each discrete category
     * @param names Category names for X-axis labels and legend
     */
    void add_histogram(const std::vector<int>& counts, const std::vector<std::string>& names);
    
    /**
     * @brief Add discrete histogram data with auto-generated names (idx 1, idx 2, ...)
     * @param counts Frequency counts for each discrete category
     */
    void add_histogram(const std::vector<int>& counts);
    
    
    /**
     * @brief Add vertical reference line with color name (restricted for discrete histograms)
     * @param x_value X-axis value for the line
     * @param label Label for the line in legend
     * @param color_name Color name ("red", "blue", "green", etc.)
     * @throws std::invalid_argument if called on discrete histograms
     */
    void add_vertical_line(double x_value, const std::string& label, const std::string& color_name) override;
    
    /**
     * @brief Add horizontal reference line with color name (allowed for all histogram types)
     * @param y_value Y-axis value for the line
     * @param label Label for the line in legend
     * @param color_name Color name ("red", "blue", "green", etc.)
     */
    void add_horizontal_line(double y_value, const std::string& label, const std::string& color_name) override;
    
    /**
     * @brief Add vertical reference line with custom label (restricted for discrete histograms)
     * @param x_value X-axis value for the line
     * @param label Label for the line in legend
     * @throws std::invalid_argument if called on discrete histograms
     */
    void add_vertical_line(double x_value, const std::string& label) override;
    
    /**
     * @brief Add vertical reference line with auto-generated label (restricted for discrete histograms)
     * @param x_value X-axis value for the line
     * @throws std::invalid_argument if called on discrete histograms
     */
    void add_vertical_line(double x_value) override;
    
    /**
     * @brief Add horizontal reference line with custom label (allowed for all histogram types)
     * @param y_value Y-axis value for the line
     * @param label Label for the line in legend
     */
    void add_horizontal_line(double y_value, const std::string& label) override;
    
    /**
     * @brief Add horizontal reference line with auto-generated label (allowed for all histogram types)
     * @param y_value Y-axis value for the line
     */
    void add_horizontal_line(double y_value) override;
    

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
     * @brief Draw custom axis labels for discrete histograms
     * @param cr Cairo context
     */
    void draw_axis_labels(cairo_t* cr) override;
    
    /**
     * @brief Draw custom axis ticks for discrete histograms (disable x-axis numeric ticks)
     * @param cr Cairo context
     */
    void draw_axis_ticks(cairo_t* cr) override;
    
    /**
     * @brief Draw custom legend for discrete histograms
     * @param cr Cairo context
     */
    void draw_legend(cairo_t* cr) override;
    
    /**
     * @brief Clear all histogram data
     */
    void clear() override;
};

} // namespace plotlib 

#endif // PLOTLIB_HISTOGRAM_PLOT_H