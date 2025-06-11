# Security Policy

## Supported Versions

| Version | Supported          |
| ------- | ------------------ |
| 1.0.x   | ✅                |
| < 1.0   | ❌                |

## Reporting a Vulnerability

If you discover a security vulnerability in PlotLib, please report it responsibly:

### How to Report

1. **GitHub**: Create a private security advisory on GitHub
2. **Include**: 
   - Description of the vulnerability
   - Steps to reproduce
   - Potential impact
   - Suggested fix (if any)

### What to Expect

- **Response Time**: We aim to respond within 48 hours
- **Investigation**: We'll investigate and provide updates within 7 days
- **Fix Timeline**: Critical issues will be addressed within 14 days
- **Credit**: Security researchers will be credited in release notes

## Security Best Practices

### For Users

- Always use the latest version
- Use Docker containers for isolation
- Don't run with root privileges
- Validate input data before plotting

### For Docker Users

- Use non-root user (default in our images)
- Mount output directories with proper permissions
- Don't expose Docker daemon
- Use specific image tags, not `latest`

### For Developers

- Follow secure coding practices
- Validate all input parameters
- Use bounds checking for arrays
- Avoid buffer overflows in C++ code

## Dependencies

PlotLib uses these trusted dependencies:

- **Cairo**: Graphics library (system package)
- **pkg-config**: Build configuration (build time only)
- **CMake**: Build system (build time only)

All runtime dependencies are included in our Docker images and regularly updated.

## Docker Security

Our Docker images follow security best practices:

- ✅ Non-root user by default
- ✅ Minimal Alpine Linux base
- ✅ No unnecessary packages
- ✅ Regular security updates
- ✅ Signed images (when published)

## Vulnerability Disclosure

We follow responsible disclosure principles and will:

1. Acknowledge receipt of vulnerability reports
2. Work with researchers to verify issues
3. Develop and test fixes
4. Coordinate public disclosure timing
5. Credit researchers in security advisories

Thank you for helping keep PlotLib secure! 🔐 