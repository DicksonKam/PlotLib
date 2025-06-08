#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <cairo.h>
#include <cairo-svg.h>

struct Point2D {
    double x, y;
    Point2D(double x = 0, double y = 0) : x(x), y(y) {}
};

struct PlotStyle {
    double point_size = 3.0;
    double r = 0.0, g = 0.0, b = 1.0;  // Blue by default
    double alpha = 1.0;
    std::string label = "";  // For legend
};

enum class MarkerType {
    CIRCLE,
    CROSS,
    SQUARE,
    TRIANGLE
};

struct ClusterPoint {
    Point2D point;
    int cluster_label;
    
    ClusterPoint(double x, double y, int label) : point(x, y), cluster_label(label) {}
    ClusterPoint(const Point2D& pt, int label) : point(pt), cluster_label(label) {}
};

struct DataSeries {
    std::vector<Point2D> points;
    PlotStyle style;
    std::string name;
    
    DataSeries(const std::string& series_name = "") : name(series_name) {}
};

struct ClusterSeries {
    std::vector<ClusterPoint> points;
    std::string name;
    double point_size = 3.0;
    double alpha = 0.8;
    
    ClusterSeries(const std::string& series_name = "") : name(series_name) {}
};

// Forward declaration
class ScatterPlot;

struct SubplotLayout {
    int rows;
    int cols;
    double spacing = 0.05;  // Spacing between subplots as fraction of total size
    
    SubplotLayout(int r, int c, double s = 0.05) : rows(r), cols(c), spacing(s) {}
};

class ScatterPlot {
    friend class SubplotManager;
private:
    std::vector<DataSeries> data_series;
    std::vector<ClusterSeries> cluster_series;
    
    // Plot area settings
    int width, height;
    double margin_left = 80, margin_right = 150;  // Increased margins for labels and legend
    double margin_top = 60, margin_bottom = 80;
    
    // Data bounds
    double min_x, max_x, min_y, max_y;
    bool bounds_set = false;
    
    // Plot labels
    std::string title = "";
    std::string x_label = "";
    std::string y_label = "";
    
    // Cluster color palette
    std::vector<std::vector<double>> cluster_colors;
    
    // Subplot support
    bool is_subplot = false;
    double subplot_x_offset = 0;
    double subplot_y_offset = 0;
    double subplot_width_scale = 1.0;
    double subplot_height_scale = 1.0;
    
    // Helper functions
    void calculate_bounds();
    void transform_point(double data_x, double data_y, double& screen_x, double& screen_y);
    void draw_axes(cairo_t* cr);
    void draw_axis_labels(cairo_t* cr);
    void draw_axis_ticks(cairo_t* cr);
    void draw_grid(cairo_t* cr);
    void draw_points(cairo_t* cr);
    void draw_cluster_points(cairo_t* cr);
    void draw_legend(cairo_t* cr);
    void draw_title(cairo_t* cr);
    void draw_marker(cairo_t* cr, double x, double y, MarkerType type, double size, double r, double g, double b, double alpha);
    
    // Subplot helper functions
    void set_subplot_transform(double x_offset, double y_offset, double width_scale, double height_scale);
    void render_to_context(cairo_t* cr);
    
    // Utility functions
    std::string format_number(double value, int precision = 2);
    std::vector<double> generate_nice_ticks(double min_val, double max_val, int target_ticks = 5);
    void initialize_cluster_colors();
    std::vector<double> get_cluster_color(int cluster_label);
    
public:
    ScatterPlot(int w = 800, int h = 600);
    
    // Add data points (legacy methods for backward compatibility)
    void add_point(double x, double y, const PlotStyle& style = PlotStyle());
    void add_points(const std::vector<Point2D>& pts, const PlotStyle& style = PlotStyle());
    
    // Enhanced methods for series-based data
    void add_series(const std::string& name, const std::vector<Point2D>& points, const PlotStyle& style);
    void add_series_point(const std::string& series_name, double x, double y);
    
    // Cluster-based methods
    void add_cluster_data(const std::string& name, const std::vector<Point2D>& points, const std::vector<int>& cluster_labels, double point_size = 3.0, double alpha = 0.8);
    void add_cluster_point(const std::string& series_name, double x, double y, int cluster_label);
    
    // Set plot labels
    void set_title(const std::string& plot_title);
    void set_xlabel(const std::string& x_axis_label);
    void set_ylabel(const std::string& y_axis_label);
    void set_labels(const std::string& plot_title, const std::string& x_axis_label, const std::string& y_axis_label);
    
    // Set plot bounds manually
    void set_bounds(double min_x, double max_x, double min_y, double max_y);
    
    // Save plot to file
    bool save_png(const std::string& filename);
    bool save_svg(const std::string& filename);
    
    // Clear all data
    void clear();
    
    // Create a copy of this plot (for subplots)
    std::unique_ptr<ScatterPlot> clone() const;
};

// Subplot manager class
class SubplotManager {
private:
    std::vector<std::vector<std::unique_ptr<ScatterPlot>>> subplots;
    SubplotLayout layout;
    int total_width, total_height;
    std::string main_title = "";
    
public:
    SubplotManager(int rows, int cols, int width = 1200, int height = 900, double spacing = 0.05);
    
    // Get a specific subplot for modification
    ScatterPlot& get_subplot(int row, int col);
    
    // Set main title for the entire subplot figure
    void set_main_title(const std::string& title);
    
    // Save the entire subplot figure
    bool save_png(const std::string& filename);
    bool save_svg(const std::string& filename);
    
    // Get layout information
    int get_rows() const { return layout.rows; }
    int get_cols() const { return layout.cols; }
    
private:
    void render_to_context(cairo_t* cr);
    void draw_main_title(cairo_t* cr);
    double get_title_height(cairo_t* cr) const;
};

#endif
