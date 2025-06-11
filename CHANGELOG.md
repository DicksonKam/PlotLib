# Changelog

All notable changes to PlotLib will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Docker support for cross-platform compatibility
- Alpine Linux-based containers for lightweight deployment
- Multi-service Docker Compose configuration
- GitHub Actions CI/CD pipeline
- Comprehensive documentation structure
- Security policy and vulnerability reporting process
- GitHub issue templates for bugs and feature requests

### Changed
- Enhanced README with visual showcase and comparison table
- Improved project structure and organization
- Updated documentation with Docker-first approach

### Fixed
- GitHub Actions deprecation warnings (updated to v4)
- Missing `#include <stdexcept>` in plot_manager.h
- Ubuntu build failures in CI pipeline
- Docker Compose service configurations

## [1.0.0] - 2025-06-08

### Added
- Initial release of PlotLib
- Core plotting functionality:
  - ScatterPlot for point-based visualizations
  - LinePlot for time series and mathematical functions
  - HistogramPlot for distribution analysis
  - SubplotManager for complex dashboard layouts
- Comprehensive example suite:
  - 7 beginner examples with progressive complexity
  - 4 advanced examples for professional use
  - 4 plot_types examples for comprehensive API demonstrations
  - Complete API coverage in examples
- Color system with named colors and automatic assignment
- Cairo-based rendering engine for high-quality output
- PNG and SVG export capabilities
- CMake build system with cross-platform support
- Comprehensive documentation:
  - Beginner tutorial with step-by-step guides
  - Complete API reference
  - Visual gallery with code examples
  - Contributing guidelines
- Testing framework with basic test coverage
- MIT license for open source compatibility

### Core Features
- **Easy-to-use API**: Beginner-friendly with automatic styling
- **Professional output**: Cairo graphics for publication-quality plots
- **Flexible layouts**: Single plots and complex subplot arrangements
- **Color management**: Named colors with automatic color cycling
- **Data handling**: Support for various data formats and structures
- **Cross-platform**: Works on Windows, macOS, and Linux

### Supported Plot Types
- **Scatter plots**: Point visualization, cluster analysis, correlation studies
- **Line plots**: Time series, mathematical functions, trend analysis  
- **Histograms**: Distribution analysis, statistical visualization
- **Subplots**: Dashboard creation, comparative analysis

### Technical Specifications
- **Language**: C++17
- **Graphics**: Cairo/Cairo-SVG
- **Build**: CMake 3.10+
- **Dependencies**: pkg-config, Cairo development libraries
- **Output**: PNG, SVG formats
- **Architecture**: Header-only friendly with compiled library

### Documentation
- Complete API reference for all classes and methods
- Step-by-step beginner tutorial
- Visual gallery with 25+ example plots
- Advanced techniques and optimization guide
- Contributing guidelines and project standards

## [0.9.0] - Development Phase

### Added
- Initial development and testing
- Core architecture design
- Basic plotting functionality
- Example development and testing

---

## Release Notes

### Version 1.0.0 - Initial Public Release

PlotLib 1.0.0 represents the first stable release of our C++ plotting library. This release focuses on providing a simple, beginner-friendly API while maintaining the power and flexibility needed for professional data visualization.

**Key Highlights:**
- ✅ **Ready for Production**: Stable API with comprehensive testing
- ✅ **Beginner Friendly**: Simple function calls with automatic styling  
- ✅ **Professional Output**: Cairo-based rendering for publication quality
- ✅ **Cross-Platform**: Docker support for universal compatibility
- ✅ **Well Documented**: Complete tutorials, examples, and API reference
- ✅ **Active Development**: Regular updates and community support

**Who Should Use This Release:**
- C++ developers new to data visualization
- Researchers needing publication-quality plots
- Students learning data analysis and visualization
- Professionals requiring reliable, cross-platform plotting solutions

**Migration Notes:**
- This is the initial public release - no migration needed
- All APIs are stable and backward compatibility will be maintained
- Docker images provide consistent behavior across platforms

**Known Limitations:**
- Currently supports PNG and SVG output only (PDF support planned)
- Limited to 2D plotting (3D support in future versions)
- Basic statistical functions (advanced stats planned for v1.1)

**Next Release Preview (v1.1.0):**
- Enhanced statistical plotting functions
- PDF export capability
- Performance optimizations for large datasets
- Additional plot types (box plots, violin plots)
- Interactive plotting features

For detailed information about any release, see the documentation at [docs/](docs/) or visit our [GitHub repository](https://github.com/DicksonKam/PlotLib). 