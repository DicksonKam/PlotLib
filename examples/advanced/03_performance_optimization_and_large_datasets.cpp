/**
 * @file 03_performance_optimization_and_large_datasets.cpp
 * @brief Performance optimization and large dataset handling
 * 
 * This example demonstrates:
 * - Handling large datasets efficiently
 * - Memory optimization techniques
 * - Performance benchmarking
 * - Data sampling and aggregation strategies
 * - Advanced rendering optimizations
 */

#include "scatter_plot.h"
#include "line_plot.h"
#include "histogram_plot.h"
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>

class PerformanceTimer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::string operation_name;
    
public:
    PerformanceTimer(const std::string& name) : operation_name(name) {
        start_time = std::chrono::high_resolution_clock::now();
        std::cout << "⏱️  Starting: " << operation_name << "..." << std::endl;
    }
    
    ~PerformanceTimer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "✅ Completed: " << operation_name << " in " << duration.count() << "ms" << std::endl;
    }
};

// Utility function for data sampling
template<typename T>
std::vector<T> sample_data(const std::vector<T>& data, size_t target_size) {
    if (data.size() <= target_size) return data;
    
    std::vector<T> sampled;
    sampled.reserve(target_size);
    
    double step = static_cast<double>(data.size()) / target_size;
    for (size_t i = 0; i < target_size; ++i) {
        size_t index = static_cast<size_t>(i * step);
        sampled.push_back(data[index]);
    }
    
    return sampled;
}

// Utility function for data aggregation - updated to work with separate x/y vectors
void aggregate_points(const std::vector<double>& x_data, const std::vector<double>& y_data, 
                     size_t bin_count, std::vector<double>& agg_x, std::vector<double>& agg_y) {
    if (x_data.empty() || y_data.empty()) return;
    
    // Find data bounds
    auto x_minmax = std::minmax_element(x_data.begin(), x_data.end());
    double x_min = *x_minmax.first;
    double x_max = *x_minmax.second;
    double bin_width = (x_max - x_min) / bin_count;
    
    std::vector<std::vector<double>> bins(bin_count);
    std::vector<double> bin_centers(bin_count);
    
    // Populate bins
    for (size_t i = 0; i < x_data.size(); ++i) {
        int bin_idx = static_cast<int>((x_data[i] - x_min) / bin_width);
        bin_idx = std::max(0, std::min(static_cast<int>(bin_count - 1), bin_idx));
        bins[bin_idx].push_back(y_data[i]);
        bin_centers[bin_idx] = x_min + (bin_idx + 0.5) * bin_width;
    }
    
    // Calculate aggregated points (mean of each bin)
    agg_x.clear();
    agg_y.clear();
    for (size_t i = 0; i < bin_count; ++i) {
        if (!bins[i].empty()) {
            double mean_y = std::accumulate(bins[i].begin(), bins[i].end(), 0.0) / bins[i].size();
            agg_x.push_back(bin_centers[i]);
            agg_y.push_back(mean_y);
        }
    }
}

int main() {
    std::cout << "Performance Optimization and Large Dataset Handling" << std::endl;
    std::cout << "====================================================" << std::endl;
    
    std::random_device rd;
    std::mt19937 gen(42);  // Fixed seed for reproducibility
    
    // Example 1: Large Dataset Performance Comparison
    std::cout << "\n1. Large Dataset Performance Analysis" << std::endl;
    
    const size_t LARGE_SIZE = 100000;  // 100K points
    const size_t MEDIUM_SIZE = 10000;  // 10K points
    const size_t SMALL_SIZE = 1000;    // 1K points
    
    std::normal_distribution<> large_dist(0, 1);
    
    // Generate large dataset using separate x/y vectors
    std::vector<double> large_x, large_y;
    {
        PerformanceTimer timer("Generating 100K data points");
        large_x.reserve(LARGE_SIZE);
        large_y.reserve(LARGE_SIZE);
        for (size_t i = 0; i < LARGE_SIZE; ++i) {
            double x = i * 0.01;
            double y = large_dist(gen) + 0.1 * std::sin(0.01 * x);
            large_x.push_back(x);
            large_y.push_back(y);
        }
    }
    
    // Test 1: Direct plotting (not recommended for large datasets)
    std::cout << "\nTest 1: Direct plotting performance..." << std::endl;
    {
        PerformanceTimer timer("Direct plotting of 100K points");
        plotlib::ScatterPlot large_plot(1200, 800);
        large_plot.set_labels("Large Dataset - Direct Plot", "X", "Y");
        large_plot.add_scatter("Raw Data", large_x, large_y, "blue");
        large_plot.save_png("output/advanced_03_large_direct.png");
    }
    
    // Test 2: Sampled plotting (recommended approach)
    std::cout << "\nTest 2: Sampled plotting performance..." << std::endl;
    {
        PerformanceTimer timer("Sampled plotting (10K from 100K points)");
        auto sampled_x = sample_data(large_x, MEDIUM_SIZE);
        auto sampled_y = sample_data(large_y, MEDIUM_SIZE);
        
        plotlib::ScatterPlot sampled_plot(1200, 800);
        sampled_plot.set_labels("Large Dataset - Sampled Plot", "X", "Y");
        sampled_plot.add_scatter("Sampled Data", sampled_x, sampled_y, "red");
        sampled_plot.save_png("output/advanced_03_large_sampled.png");
    }
    
    // Test 3: Aggregated plotting (best for trend analysis)
    std::cout << "\nTest 3: Aggregated plotting performance..." << std::endl;
    {
        PerformanceTimer timer("Aggregated plotting (1K bins from 100K points)");
        std::vector<double> agg_x, agg_y;
        aggregate_points(large_x, large_y, SMALL_SIZE, agg_x, agg_y);
        
        plotlib::ScatterPlot aggregated_plot(1200, 800);
        aggregated_plot.set_labels("Large Dataset - Aggregated Plot", "X", "Y");
        aggregated_plot.add_scatter("Aggregated Data", agg_x, agg_y, "green");
        aggregated_plot.save_png("output/advanced_03_large_aggregated.png");
    }
    
    // Example 2: Memory-Efficient Time Series Analysis
    std::cout << "\n2. Memory-Efficient Time Series Analysis" << std::endl;
    
    const size_t TIME_SERIES_SIZE = 50000;  // 50K time points
    
    // Generate time series data efficiently
    std::vector<double> time_points, signal_values;
    {
        PerformanceTimer timer("Generating 50K time series points");
        time_points.reserve(TIME_SERIES_SIZE);
        signal_values.reserve(TIME_SERIES_SIZE);
        
        std::normal_distribution<> noise_dist(0, 0.1);
        
        for (size_t i = 0; i < TIME_SERIES_SIZE; ++i) {
            double t = i * 0.001;  // 1ms resolution
            time_points.push_back(t);
            
            // Complex signal with multiple components
            double signal = 2.0 * std::sin(2 * M_PI * 10 * t) +     // 10 Hz component
                           1.0 * std::sin(2 * M_PI * 50 * t) +      // 50 Hz component
                           0.5 * std::sin(2 * M_PI * 100 * t) +     // 100 Hz component
                           noise_dist(gen);                          // Noise
            signal_values.push_back(signal);
        }
    }
    
    // Efficient plotting with downsampling
    {
        PerformanceTimer timer("Time series plotting with downsampling");
        
        // Downsample for visualization (every 10th point)
        std::vector<double> downsampled_time, downsampled_signal;
        for (size_t i = 0; i < TIME_SERIES_SIZE; i += 10) {
            downsampled_time.push_back(time_points[i]);
            downsampled_signal.push_back(signal_values[i]);
        }
        
        plotlib::LinePlot time_series_plot(1400, 600);
        time_series_plot.set_labels("High-Frequency Time Series", "Time (s)", "Amplitude");
        time_series_plot.add_line("Signal", downsampled_time, downsampled_signal, "blue");
        time_series_plot.save_png("output/advanced_03_time_series.png");
    }
    
    // Example 3: Efficient Histogram with Large Dataset
    std::cout << "\n3. Efficient Histogram Analysis" << std::endl;
    
    const size_t HISTOGRAM_SIZE = 1000000;  // 1M data points
    
    {
        PerformanceTimer timer("Generating and plotting 1M point histogram");
        
        // Generate large dataset for histogram
        std::vector<double> histogram_data;
        histogram_data.reserve(HISTOGRAM_SIZE);
        
        std::normal_distribution<> hist_dist(100, 25);
        for (size_t i = 0; i < HISTOGRAM_SIZE; ++i) {
            histogram_data.push_back(hist_dist(gen));
        }
        
        // Create histogram with optimal bin count
        plotlib::HistogramPlot large_histogram(1200, 800);
        large_histogram.set_labels("Large Dataset Histogram", "Value", "Frequency");
        
        // Use optimal bin count (automatic bin calculation)
        large_histogram.add_histogram("1M Data Points", histogram_data, "purple");
        large_histogram.save_png("output/advanced_03_large_histogram.png");
        
        // Calculate basic statistics manually since get_statistics is removed
        double mean = std::accumulate(histogram_data.begin(), histogram_data.end(), 0.0) / histogram_data.size();
        double sq_sum = std::inner_product(histogram_data.begin(), histogram_data.end(), histogram_data.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / histogram_data.size() - mean * mean);
        
        std::cout << "📊 Dataset Statistics:" << std::endl;
        std::cout << "   Mean: " << mean << std::endl;
        std::cout << "   Std Dev: " << stdev << std::endl;
    }
    
    // Example 4: Performance Comparison Dashboard
    std::cout << "\n4. Performance Comparison Dashboard" << std::endl;
    
    {
        PerformanceTimer timer("Creating performance comparison dashboard");
        
        plotlib::SubplotManager perf_dashboard(2, 2, 1600, 1200);
        perf_dashboard.set_main_title("Performance Optimization Comparison");
        
        // (0,0) - Dataset Size vs Rendering Time
        auto& size_vs_time = perf_dashboard.get_subplot<plotlib::LinePlot>(0, 0);
        size_vs_time.set_labels("Rendering Performance", "Dataset Size (K points)", "Render Time (ms)");
        
        std::vector<double> sizes = {1, 5, 10, 25, 50, 100};
        std::vector<double> direct_times = {10, 45, 95, 240, 480, 950};      // Simulated times
        std::vector<double> sampled_times = {8, 12, 15, 18, 22, 25};         // Much better
        std::vector<double> aggregated_times = {5, 6, 7, 8, 9, 10};         // Best
        
        size_vs_time.add_line("Direct Plotting", sizes, direct_times, "red");
        size_vs_time.add_line("Sampled Plotting", sizes, sampled_times, "blue");
        size_vs_time.add_line("Aggregated Plotting", sizes, aggregated_times, "green");
        
        // (0,1) - Memory Usage Comparison
        auto& memory_usage = perf_dashboard.get_subplot<plotlib::HistogramPlot>(0, 1);
        memory_usage.set_labels("Memory Usage", "Memory (MB)", "Frequency");
        
        std::vector<double> direct_memory = {50, 250, 500, 1250, 2500, 5000};
        std::vector<double> optimized_memory = {5, 25, 50, 125, 250, 500};
        
        memory_usage.add_histogram("Direct Method", direct_memory, "red", 10);
        memory_usage.add_histogram("Optimized Method", optimized_memory, "green", 10);
        
        // (1,0) - Accuracy vs Performance Trade-off
        auto& accuracy_perf = perf_dashboard.get_subplot<plotlib::ScatterPlot>(1, 0);
        accuracy_perf.set_labels("Accuracy vs Performance", "Rendering Speed (fps)", "Data Accuracy (%)");
        
        // Convert Point2D data to separate x/y vectors
        std::vector<double> method_x = {1.0, 15.0, 30.0, 25.0};
        std::vector<double> method_y = {100.0, 95.0, 85.0, 90.0};
        accuracy_perf.add_scatter("Optimization Methods", method_x, method_y, "purple");
        
        // (1,1) - Scalability Analysis
        auto& scalability = perf_dashboard.get_subplot<plotlib::LinePlot>(1, 1);
        scalability.set_labels("Scalability Analysis", "Dataset Size (log scale)", "Performance Score");
        
        std::vector<double> log_sizes = {1, 2, 3, 4, 5, 6};  // 10^1 to 10^6
        std::vector<double> direct_score = {100, 80, 60, 30, 10, 2};
        std::vector<double> optimized_score = {100, 98, 95, 90, 85, 80};
        
        scalability.add_line("Direct Method", log_sizes, direct_score, "red");
        scalability.add_line("Optimized Method", log_sizes, optimized_score, "green");
        
        perf_dashboard.save_png("output/advanced_03_performance_dashboard.png");
    }
    
    // Example 5: Real-time Data Simulation
    std::cout << "\n5. Real-time Data Simulation" << std::endl;
    
    {
        PerformanceTimer timer("Real-time data simulation and plotting");
        
        const size_t BUFFER_SIZE = 1000;  // Rolling buffer
        std::vector<double> time_buffer, data_buffer;
        time_buffer.reserve(BUFFER_SIZE);
        data_buffer.reserve(BUFFER_SIZE);
        
        // Simulate real-time data acquisition
        std::normal_distribution<> sensor_noise(0, 0.05);
        
        for (size_t i = 0; i < BUFFER_SIZE; ++i) {
            double t = i * 0.1;
            double sensor_value = std::sin(0.5 * t) + 0.3 * std::cos(2 * t) + sensor_noise(gen);
            
            time_buffer.push_back(t);
            data_buffer.push_back(sensor_value);
        }
        
        // Create real-time style plot
        plotlib::LinePlot realtime_plot(1400, 600);
        realtime_plot.set_labels("Real-time Sensor Data", "Time (s)", "Sensor Value");
        realtime_plot.set_show_markers(false);  // Disable markers for performance
        realtime_plot.add_line("Live Data", time_buffer, data_buffer, "blue");
        realtime_plot.save_png("output/advanced_03_realtime.png");
    }
    
    // Example 6: Memory Profiling and Optimization Tips
    std::cout << "\n6. Memory Optimization Demonstration" << std::endl;
    
    {
        PerformanceTimer timer("Memory optimization techniques");
        
        // Technique 1: Reserve memory upfront
        std::vector<double> optimized_x, optimized_y;
        optimized_x.reserve(MEDIUM_SIZE);  // Avoid reallocations
        optimized_y.reserve(MEDIUM_SIZE);
        
        // Technique 2: Use efficient data generation
        for (size_t i = 0; i < MEDIUM_SIZE; ++i) {
            optimized_x.push_back(i * 0.01);
            optimized_y.push_back(large_dist(gen));
        }
        
        // Technique 3: Clear unused data
        large_x.clear();
        large_x.shrink_to_fit();  // Release memory
        large_y.clear();
        large_y.shrink_to_fit();
        
        plotlib::ScatterPlot memory_optimized(1200, 800);
        memory_optimized.set_labels("Memory Optimized Plot", "X", "Y");
        memory_optimized.add_scatter("Optimized Data", optimized_x, optimized_y, "orange");
        memory_optimized.save_png("output/advanced_03_memory_optimized.png");
    }
    
    std::cout << "\n🎯 Advanced Example 3 Complete!" << std::endl;
    std::cout << "Performance optimization techniques demonstrated:" << std::endl;
    std::cout << "  • Large dataset handling (100K+ points)" << std::endl;
    std::cout << "  • Data sampling and aggregation strategies" << std::endl;
    std::cout << "  • Memory-efficient time series analysis" << std::endl;
    std::cout << "  • Efficient histogram processing (1M points)" << std::endl;
    std::cout << "  • Performance comparison dashboard" << std::endl;
    std::cout << "  • Real-time data simulation techniques" << std::endl;
    std::cout << "  • Memory optimization best practices" << std::endl;
    
    return 0;
}

/*
 * 🎯 Performance Optimization Techniques:
 * 
 * 1. DATA SAMPLING:
 *    - Uniform sampling for large datasets
 *    - Maintains visual trends while reducing points
 *    - Significant performance improvement
 * 
 * 2. DATA AGGREGATION:
 *    - Bin-based aggregation for scatter plots
 *    - Statistical summaries (mean, median, etc.)
 *    - Preserves overall patterns
 * 
 * 3. MEMORY OPTIMIZATION:
 *    - Reserve vector capacity upfront
 *    - Use efficient data structures
 *    - Clear and shrink unused containers
 *    - Avoid unnecessary data copies
 * 
 * 4. RENDERING OPTIMIZATION:
 *    - Disable markers for line plots when not needed
 *    - Use appropriate plot types for data characteristics
 *    - Consider downsampling for visualization
 * 
 * 5. REAL-TIME CONSIDERATIONS:
 *    - Rolling buffers for continuous data
 *    - Efficient update strategies
 *    - Minimal memory allocations in loops
 * 
 * 🚀 Best Practices:
 * - Profile your specific use case
 * - Choose appropriate sampling strategies
 * - Balance accuracy vs performance
 * - Monitor memory usage patterns
 * - Use benchmarking for optimization decisions
 */ 