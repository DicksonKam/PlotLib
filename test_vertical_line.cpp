#include "include/histogram_plot.h"
#include <iostream>

int main() {
    try {
        plotlib::HistogramPlot plot(800, 600);
        plot.set_labels("Test Histogram", "Value", "Frequency");
        
        // Add some continuous histogram data
        std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
        plot.add_histogram(data, "Test Data");
        
        // This should now work without ambiguity - calling with default parameter
        plot.add_vertical_line(15.0);  // Should use default label = ""
        
        plot.save_png("output/test_vertical_line.png");
        std::cout << "✅ SUCCESS: add_vertical_line(15.0) call succeeded without ambiguity!" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cout << "❌ ERROR: " << e.what() << std::endl;
        return 1;
    }
}