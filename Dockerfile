# PlotLib Optimized Multi-Stage Docker Image

# Build stage
FROM alpine:latest AS builder

# Install build dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    pkgconfig \
    cairo-dev

# Create working directory
WORKDIR /app

# Copy source code
COPY CMakeLists.txt .
COPY cmake/ cmake/
COPY include/ include/
COPY src/ src/
COPY examples/ examples/
COPY tests/ tests/

# Build PlotLib
RUN mkdir -p build && \
    cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make

# Runtime stage
FROM alpine:latest

# Install only runtime dependencies
RUN apk add --no-cache \
    cairo \
    libstdc++ \
    libgcc

# Create non-root user
RUN adduser -D -u 1000 plotlib

# Create working directory and output directory
WORKDIR /app
RUN mkdir -p output

# Copy only the built artifacts from builder stage
COPY --from=builder /app/build /app/build

# Set proper ownership
RUN chown -R plotlib:plotlib /app

# Switch to non-root user
USER plotlib

# Set environment variables
ENV PLOTLIB_OUTPUT_DIR=/app/output

# Volume for output
VOLUME ["/app/output"]

# Default command
CMD ["/bin/sh", "-c", "echo '🐳 PlotLib Optimized Container Ready!' && echo 'Built successfully on Alpine Linux' && echo '✅ Available examples:' && ls -la /app/build/examples/ | grep -E '^-.*\\.' && echo '' && echo '📖 Usage:' && echo '  docker run -v ./output:/app/output plotlib /app/build/examples/01_first_scatter_plot' && echo '  docker run -v ./output:/app/output plotlib /app/build/examples/05_simple_subplots'"]

# Labels for documentation
LABEL org.opencontainers.image.title="PlotLib"
LABEL org.opencontainers.image.description="Cross-platform C++ plotting library with Cairo graphics (Optimized)"
LABEL org.opencontainers.image.version="1.0.1"
LABEL org.opencontainers.image.authors="PlotLib Contributors" 