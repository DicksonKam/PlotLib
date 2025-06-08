# Contributing to PlotLib

Thank you for your interest in contributing to PlotLib! This document provides guidelines for contributing to the project.

## Development Setup

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.12 or higher
- Cairo graphics library
- pkg-config

### Building the Project

```bash
# Clone the repository
git clone <repository-url>
cd plotlib

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run examples
./examples/centralized_demo

# Run tests
make test
```

## Code Style

- Use 4 spaces for indentation
- Follow C++ Core Guidelines
- Use meaningful variable and function names
- Add Doxygen comments for public APIs
- Keep line length under 100 characters

## Adding New Plot Types

When adding new plot types:

1. Create header file in `include/plotlib/`
2. Create implementation file in `src/`
3. Add to CMakeLists.txt
4. Create example in `examples/`
5. Add unit tests in `tests/`
6. Update documentation

## Testing

- Write unit tests for all new functionality
- Ensure all tests pass before submitting PR
- Test on multiple platforms if possible

## Documentation

- Use Doxygen for API documentation
- Update README.md for new features
- Add examples for new functionality

## Submitting Changes

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests
5. Update documentation
6. Submit a pull request

## Code Review Process

- All changes require review
- Maintain backward compatibility
- Follow existing patterns and conventions
- Ensure CI passes

## Questions?

Feel free to open an issue for questions or discussions about contributing. 