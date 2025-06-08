# Contributing to PlotLib

Thank you for your interest in contributing to PlotLib! This document provides guidelines for contributing to the project.

## 🚀 Getting Started

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.12 or higher
- Cairo graphics library (2.0+)
- pkg-config

### Building the Project

```bash
# Clone the repository
git clone <repository-url>
cd plotlib

# Build using the provided script
./build.sh

# Or build manually
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

## 📝 Code Standards

### Code Style
- **Indentation**: 4 spaces (no tabs)
- **Line length**: Maximum 100 characters
- **Naming**: 
  - Classes: `PascalCase` (e.g., `ScatterPlot`)
  - Functions/variables: `snake_case` (e.g., `add_data`)
  - Constants: `UPPER_SNAKE_CASE`
- **Braces**: K&R style (opening brace on same line)

### Modern C++ Practices
- Use `auto` where type is obvious
- Prefer `std::unique_ptr` over raw pointers
- Use range-based for loops where possible
- Prefer initialization over assignment
- Use `const` and `constexpr` where appropriate

### Documentation
- **Doxygen comments** for all public APIs
- **Brief and detailed descriptions** for classes and methods
- **Parameter documentation** with `@param`
- **Return value documentation** with `@return`
- **Example code** in complex functions

```cpp
/**
 * @brief Creates a new scatter plot with specified dimensions
 * @param width Plot width in pixels
 * @param height Plot height in pixels
 * @return True if successful, false otherwise
 * 
 * @example
 * @code
 * ScatterPlot plot(800, 600);
 * plot.add_data("My Data", points);
 * @endcode
 */
```

## 🧪 Testing Requirements

### Unit Tests
- Write tests for all new functionality
- Aim for >80% code coverage
- Test both success and failure cases
- Use descriptive test names

### Performance Tests
- Benchmark performance-critical code
- Ensure no regressions in large dataset handling
- Test memory usage patterns

### Integration Tests
- Test complete workflows
- Verify file output correctness
- Test multi-platform compatibility

## 📊 Adding New Plot Types

When adding new plot types, follow this checklist:

1. **Create header file** in `include/plotlib/`
   - Inherit from `PlotManager`
   - Document all public methods
   - Follow existing naming patterns

2. **Implement source file** in `src/`
   - Override `draw_data()` method
   - Implement plot-specific logic
   - Handle edge cases gracefully

3. **Update build system**
   - Add to `CMakeLists.txt`
   - Update library sources list

4. **Create examples**
   - Add beginner example in `examples/beginner/`
   - Add advanced example in `examples/advanced/`
   - Update examples README

5. **Write tests**
   - Add unit tests in `tests/`
   - Test boundary conditions
   - Verify file output

6. **Update documentation**
   - Add to main README
   - Create API documentation
   - Add to gallery with examples

## 🔄 Development Workflow

### Branch Strategy
- `main`: Stable releases only
- `develop`: Integration branch for features
- `feature/*`: New features
- `fix/*`: Bug fixes
- `hotfix/*`: Critical fixes

### Pull Request Process

1. **Fork and clone** the repository
2. **Create feature branch** from `develop`
3. **Implement changes** following code standards
4. **Add comprehensive tests**
5. **Update documentation**
6. **Run all tests** and ensure they pass
7. **Submit pull request** with clear description

### PR Requirements
- ✅ All tests pass
- ✅ No compiler warnings
- ✅ Documentation updated
- ✅ Examples provided (if applicable)
- ✅ Code review approval
- ✅ CI checks pass

## 🐛 Reporting Issues

When reporting bugs:
- Use the issue template
- Provide minimal reproduction case
- Include system information
- Attach relevant plots/outputs

## 📚 Documentation

### API Documentation
```bash
# Generate Doxygen documentation
doxygen Doxyfile
```

### Examples
- Keep examples simple and focused
- Include comments explaining each step
- Test all examples before committing

## 🤝 Community

- Be respectful and inclusive
- Help newcomers get started
- Share knowledge and best practices
- Follow the code of conduct

## 📄 License

By contributing, you agree that your contributions will be licensed under the MIT License.

## ❓ Questions?

- Open a discussion for general questions
- Open an issue for bugs or feature requests
- Check existing documentation first

---

**Happy Contributing! 🎉** 