/**
 * @file 02_complex_dashboards_and_layouts.cpp
 * @brief Advanced subplot layouts and dashboard creation
 * 
 * This example demonstrates:
 * - Complex subplot layouts (3x3, 4x2, etc.)
 * - Mixed plot types in sophisticated arrangements
 * - Professional dashboard design principles
 * - Advanced subplot coordination and theming
 * - Real-world dashboard scenarios
 */

#include "scatter_plot.h"
#include "line_plot.h"
#include "histogram_plot.h"
#include "plot_manager.h"
#include <vector>
#include <iostream>
#include <random>
#include <cmath>

int main() {
    std::cout << "Creating complex dashboards and layouts..." << std::endl;
    
    // Example 1: Executive Dashboard (3x3 layout)
    std::cout << "1. Creating executive dashboard (3x3)..." << std::endl;
    
    plotlib::SubplotManager executive_dashboard(3, 3, 1800, 1200);
    executive_dashboard.set_main_title("Executive Performance Dashboard - Q4 2024");
    
    // Generate realistic business data
    std::random_device rd;
    std::mt19937 gen(42);
    std::normal_distribution<> revenue_dist(1000, 200);
    std::normal_distribution<> customer_dist(85, 10);
    std::uniform_real_distribution<> efficiency_dist(0.7, 0.95);
    
    // Row 1: Revenue Analysis
    // (0,0) - Monthly Revenue Trend
    auto& revenue_trend = executive_dashboard.get_subplot<plotlib::LinePlot>(0, 0);
    revenue_trend.set_labels("Monthly Revenue", "Month", "Revenue ($K)");
    
    std::vector<double> months = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector<double> revenue_2023, revenue_2024;
    for (int i = 0; i < 12; ++i) {
        revenue_2023.push_back(revenue_dist(gen) + i * 50);  // Growth trend
        revenue_2024.push_back(revenue_dist(gen) + i * 75);  // Better growth
    }
    revenue_trend.add_line(months, revenue_2023, "2023", "blue");
    revenue_trend.add_line(months, revenue_2024, "2024", "green");
    
    // (0,1) - Customer Satisfaction Distribution
    auto& satisfaction_dist = executive_dashboard.get_subplot<plotlib::HistogramPlot>(0, 1);
    satisfaction_dist.set_labels("Customer Satisfaction", "Rating", "Count");
    
    std::vector<double> satisfaction_scores;
    for (int i = 0; i < 500; ++i) {
        satisfaction_scores.push_back(std::max(0.0, std::min(100.0, customer_dist(gen))));
    }
    satisfaction_dist.add_histogram(satisfaction_scores, "Q4 Ratings", "orange", 20);
    
    // (0,2) - Regional Performance Scatter
    auto& regional_perf = executive_dashboard.get_subplot<plotlib::ScatterPlot>(0, 2);
    regional_perf.set_labels("Regional Performance", "Market Size", "Revenue");
    
    // Generate separate x/y vectors for regional data
    std::vector<double> north_x, north_y, south_x, south_y, west_x, west_y, east_x, east_y;
    for (int i = 0; i < 15; ++i) {
        north_x.push_back(gen() % 100 + 50);
        north_y.push_back(revenue_dist(gen));
        
        south_x.push_back(gen() % 80 + 30);
        south_y.push_back(revenue_dist(gen) * 0.8);
        
        west_x.push_back(gen() % 120 + 70);
        west_y.push_back(revenue_dist(gen) * 1.2);
        
        east_x.push_back(gen() % 90 + 40);
        east_y.push_back(revenue_dist(gen) * 0.9);
    }
    regional_perf.add_scatter(north_x, north_y, "North", "blue");
    regional_perf.add_scatter(south_x, south_y, "South", "red");
    regional_perf.add_scatter(west_x, west_y, "West", "green");
    regional_perf.add_scatter(east_x, east_y, "East", "orange");
    
    // Row 2: Operational Metrics
    // (1,0) - Efficiency Over Time
    auto& efficiency_trend = executive_dashboard.get_subplot<plotlib::LinePlot>(1, 0);
    efficiency_trend.set_labels("Operational Efficiency", "Week", "Efficiency %");
    
    std::vector<double> weeks;
    std::vector<double> production_eff, logistics_eff, sales_eff;
    for (int i = 1; i <= 52; ++i) {
        weeks.push_back(i);
        production_eff.push_back(efficiency_dist(gen) * 100);
        logistics_eff.push_back(efficiency_dist(gen) * 100);
        sales_eff.push_back(efficiency_dist(gen) * 100);
    }
    efficiency_trend.add_line(weeks, production_eff, "Production", "blue");
    efficiency_trend.add_line(weeks, logistics_eff, "Logistics", "red");
    efficiency_trend.add_line(weeks, sales_eff, "Sales", "green");
    
    // (1,1) - Cost Distribution
    auto& cost_analysis = executive_dashboard.get_subplot<plotlib::HistogramPlot>(1, 1);
    cost_analysis.set_labels("Cost Analysis", "Cost ($K)", "Frequency");
    
    std::normal_distribution<> cost_dist(500, 100);
    std::vector<double> operational_costs, marketing_costs;
    for (int i = 0; i < 200; ++i) {
        operational_costs.push_back(std::max(0.0, cost_dist(gen)));
        marketing_costs.push_back(std::max(0.0, cost_dist(gen) * 0.6));
    }
    cost_analysis.add_histogram(operational_costs, "Operational", "red", 25);
    cost_analysis.add_histogram(marketing_costs, "Marketing", "blue", 25);
    
    // (1,2) - Product Performance
    auto& product_perf = executive_dashboard.get_subplot<plotlib::ScatterPlot>(1, 2);
    product_perf.set_labels("Product Performance", "Units Sold", "Profit Margin %");
    
    // Generate separate x/y vectors for regional data
    std::vector<double> product_a_x, product_a_y, product_b_x, product_b_y, product_c_x, product_c_y;
    std::uniform_real_distribution<> units_dist(100, 1000);
    std::uniform_real_distribution<> margin_dist(10, 40);
    for (int i = 0; i < 20; ++i) {
        product_a_x.push_back(units_dist(gen));
        product_a_y.push_back(margin_dist(gen));
        
        product_b_x.push_back(units_dist(gen));
        product_b_y.push_back(margin_dist(gen));
        
        product_c_x.push_back(units_dist(gen));
        product_c_y.push_back(margin_dist(gen));
    }
    product_perf.add_scatter(product_a_x, product_a_y, "Product A", "blue");
    product_perf.add_scatter(product_b_x, product_b_y, "Product B", "red");
    product_perf.add_scatter(product_c_x, product_c_y, "Product C", "green");
    
    // Row 3: Strategic Insights
    // (2,0) - Market Trends
    auto& market_trends = executive_dashboard.get_subplot<plotlib::LinePlot>(2, 0);
    market_trends.set_labels("Market Trends", "Quarter", "Market Share %");
    
    std::vector<double> quarters = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<double> our_share = {15, 17, 19, 22, 25, 27, 30, 32};
    std::vector<double> competitor_share = {35, 34, 33, 31, 29, 28, 26, 25};
    market_trends.add_line(quarters, our_share, "Our Company", "green");
    market_trends.add_line(quarters, competitor_share, "Main Competitor", "red");
    
    // (2,1) - Risk Assessment
    auto& risk_assessment = executive_dashboard.get_subplot<plotlib::HistogramPlot>(2, 1);
    risk_assessment.set_labels("Risk Assessment", "Risk Score", "Count");
    
    std::normal_distribution<> risk_dist(30, 15);
    std::vector<double> financial_risks, operational_risks, market_risks;
    for (int i = 0; i < 100; ++i) {
        financial_risks.push_back(std::max(0.0, std::min(100.0, risk_dist(gen))));
        operational_risks.push_back(std::max(0.0, std::min(100.0, risk_dist(gen) + 10)));
        market_risks.push_back(std::max(0.0, std::min(100.0, risk_dist(gen) + 20)));
    }
    risk_assessment.add_histogram(financial_risks, "Financial", "green", 15);
    risk_assessment.add_histogram(operational_risks, "Operational", "orange", 15);
    risk_assessment.add_histogram(market_risks, "Market", "red", 15);
    
    // (2,2) - Strategic Positioning
    auto& strategic_pos = executive_dashboard.get_subplot<plotlib::ScatterPlot>(2, 2);
    strategic_pos.set_labels("Strategic Positioning", "Innovation Index", "Market Position");
    
    // Generate separate x/y vectors for regional data
    std::vector<double> current_x = {75}, current_y = {68};
    std::vector<double> target_x = {85}, target_y = {80};
    std::vector<double> competitors_x, competitors_y;
    for (int i = 0; i < 8; ++i) {
        competitors_x.push_back(gen() % 100);
        competitors_y.push_back(gen() % 100);
    }
    strategic_pos.add_scatter(current_x, current_y, "Current Position", "blue");
    strategic_pos.add_scatter(target_x, target_y, "Target Position", "green");
    strategic_pos.add_scatter(competitors_x, competitors_y, "Competitors", "red");
    
    executive_dashboard.save_png("output/advanced_02_executive_dashboard.png");
    std::cout << "✅ Executive dashboard saved!" << std::endl;
    
    // Example 2: Scientific Research Dashboard (4x2 layout)
    std::cout << "2. Creating scientific research dashboard (4x2)..." << std::endl;
    
    plotlib::SubplotManager research_dashboard(4, 2, 1600, 1400);
    research_dashboard.set_main_title("Experimental Research Analysis Dashboard");
    
    // Generate scientific data
    std::normal_distribution<> measurement_dist(0, 1);
    
    // (0,0) - Time Series Experiment
    auto& time_series = research_dashboard.get_subplot<plotlib::LinePlot>(0, 0);
    time_series.set_labels("Temporal Analysis", "Time (s)", "Signal (mV)");
    time_series.set_default_show_markers(true);
    
    std::vector<double> time_points;
    std::vector<double> control_signal, treatment_signal;
    for (int i = 0; i <= 100; ++i) {
        double t = i * 0.5;
        time_points.push_back(t);
        control_signal.push_back(measurement_dist(gen) + 0.1 * std::sin(0.2 * t));
        treatment_signal.push_back(measurement_dist(gen) + 0.3 * std::sin(0.2 * t) + 0.5);
    }
    time_series.add_line(time_points, control_signal, "Control", "blue");
    time_series.add_line(time_points, treatment_signal, "Treatment", "red");
    
    // (0,1) - Statistical Distribution
    auto& stat_dist = research_dashboard.get_subplot<plotlib::HistogramPlot>(0, 1);
    stat_dist.set_labels("Measurement Distribution", "Value", "Frequency");
    
    std::vector<double> control_measurements, treatment_measurements;
    for (int i = 0; i < 1000; ++i) {
        control_measurements.push_back(measurement_dist(gen));
        treatment_measurements.push_back(measurement_dist(gen) + 0.5);
    }
    stat_dist.add_histogram(control_measurements, "Control", "blue", 30);
    stat_dist.add_histogram(treatment_measurements, "Treatment", "red", 30);
    
    // (1,0) - Correlation Analysis
    auto& correlation = research_dashboard.get_subplot<plotlib::ScatterPlot>(1, 0);
    correlation.set_labels("Variable Correlation", "Variable X", "Variable Y");
    
    // Generate separate x/y vectors for regional data
    std::vector<double> corr_x, corr_y;
    for (int i = 0; i < 200; ++i) {
        double x = measurement_dist(gen);
        double y = 0.7 * x + 0.3 * measurement_dist(gen);  // Strong correlation
        corr_x.push_back(x);
        corr_y.push_back(y);
    }
    correlation.add_scatter(corr_x, corr_y, "Experimental Data", "purple");
    
    // (1,1) - Error Analysis
    auto& error_analysis = research_dashboard.get_subplot<plotlib::HistogramPlot>(1, 1);
    error_analysis.set_labels("Error Analysis", "Residual", "Count");
    
    std::vector<double> residuals;
    for (int i = 0; i < 500; ++i) {
        residuals.push_back(measurement_dist(gen) * 0.1);  // Small errors
    }
    error_analysis.add_histogram(residuals, "Residuals", "orange", 25);
    
    // (2,0) - Dose-Response Curve
    auto& dose_response = research_dashboard.get_subplot<plotlib::LinePlot>(2, 0);
    dose_response.set_labels("Dose-Response", "Concentration (μM)", "Response (%)");
    
    std::vector<double> concentrations;
    std::vector<double> response_a, response_b;
    for (int i = 0; i <= 20; ++i) {
        double conc = i * 0.5;
        concentrations.push_back(conc);
        // Sigmoid response curves
        response_a.push_back(100 / (1 + std::exp(-(conc - 5))));
        response_b.push_back(100 / (1 + std::exp(-(conc - 7))));
    }
    dose_response.add_line(concentrations, response_a, "Compound A", "blue");
    dose_response.add_line(concentrations, response_b, "Compound B", "red");
    
    // (2,1) - Quality Control
    auto& quality_control = research_dashboard.get_subplot<plotlib::ScatterPlot>(2, 1);
    quality_control.set_labels("Quality Control", "Batch", "Purity (%)");
    
    // Generate separate x/y vectors for regional data
    std::vector<double> qc_x, qc_y;
    std::normal_distribution<> purity_dist(98, 1);
    for (int i = 1; i <= 50; ++i) {
        qc_x.push_back(i);
        qc_y.push_back(std::max(90.0, std::min(100.0, purity_dist(gen))));
    }
    quality_control.add_scatter(qc_x, qc_y, "Batch Quality", "green");
    
    // (3,0) - Comparative Analysis
    auto& comparative = research_dashboard.get_subplot<plotlib::HistogramPlot>(3, 0);
    comparative.set_labels("Method Comparison", "Measurement", "Frequency");
    
    std::normal_distribution<> method1_dist(10, 2);
    std::normal_distribution<> method2_dist(12, 1.5);
    std::vector<double> method1_data, method2_data;
    for (int i = 0; i < 300; ++i) {
        method1_data.push_back(method1_dist(gen));
        method2_data.push_back(method2_dist(gen));
    }
    comparative.add_histogram(method1_data, "Method 1", "blue", 20);
    comparative.add_histogram(method2_data, "Method 2", "red", 20);
    
    // (3,1) - Cluster Analysis
    auto& cluster_analysis = research_dashboard.get_subplot<plotlib::ScatterPlot>(3, 1);
    cluster_analysis.set_labels("Sample Clustering", "PC1", "PC2");
    
    // Convert Point2D cluster data to separate x/y vectors
    std::vector<double> cluster_x, cluster_y;
    std::vector<int> cluster_labels;
    
    // Generate 3 distinct clusters
    std::normal_distribution<> cluster1_dist(-2, 0.5);
    std::normal_distribution<> cluster2_dist(0, 0.7);
    std::normal_distribution<> cluster3_dist(2, 0.6);
    
    for (int i = 0; i < 30; ++i) {
        cluster_x.push_back(cluster1_dist(gen));
        cluster_y.push_back(cluster1_dist(gen));
        cluster_labels.push_back(0);
    }
    for (int i = 0; i < 35; ++i) {
        cluster_x.push_back(cluster2_dist(gen));
        cluster_y.push_back(cluster2_dist(gen));
        cluster_labels.push_back(1);
    }
    for (int i = 0; i < 25; ++i) {
        cluster_x.push_back(cluster3_dist(gen));
        cluster_y.push_back(cluster3_dist(gen));
        cluster_labels.push_back(2);
    }
    
    cluster_analysis.add_clusters(cluster_x, cluster_y, cluster_labels);
    
    research_dashboard.save_png("output/advanced_02_research_dashboard.png");
    std::cout << "✅ Research dashboard saved!" << std::endl;
    
    std::cout << "\n🎯 Advanced Example 2 Complete!" << std::endl;
    std::cout << "Generated 2 complex dashboards:" << std::endl;
    std::cout << "  • Executive Dashboard (3x3) - 9 interconnected business metrics" << std::endl;
    std::cout << "  • Research Dashboard (4x2) - 8 scientific analysis plots" << std::endl;
    std::cout << "  • Total: 17 sophisticated plots in professional layouts" << std::endl;
    
    return 0;
}

/*
 * 🎯 Advanced Dashboard Concepts:
 * 
 * 1. EXECUTIVE DASHBOARD (3x3):
 *    - Revenue trends and forecasting
 *    - Customer satisfaction analysis
 *    - Regional performance comparison
 *    - Operational efficiency tracking
 *    - Cost analysis and optimization
 *    - Product performance metrics
 *    - Market trend analysis
 *    - Risk assessment visualization
 *    - Strategic positioning mapping
 * 
 * 2. RESEARCH DASHBOARD (4x2):
 *    - Temporal experimental data
 *    - Statistical distribution analysis
 *    - Correlation studies
 *    - Error and residual analysis
 *    - Dose-response relationships
 *    - Quality control monitoring
 *    - Method comparison studies
 *    - Cluster analysis and classification
 * 
 * 🚀 Professional Design Principles:
 * - Logical grouping of related metrics
 * - Consistent color schemes within domains
 * - Appropriate plot types for data characteristics
 * - Clear, descriptive titles and labels
 * - Balanced layout and visual hierarchy
 * - Comprehensive coverage of key metrics
 */ 