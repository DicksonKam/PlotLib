# PlotLib Docker Image
# Multi-stage build for cross-platform compatibility
FROM ubuntu:22.04 as builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libcairo2-dev \
    libcairo2-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Build the library and examples
RUN mkdir -p build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make plotlib -j$(nproc) && \
    make beginner_examples -j$(nproc) && \
    make advanced_examples -j$(nproc) && \
    make basic_tests

# Create output directory
RUN mkdir -p /app/output

# Runtime stage - minimal image with just what's needed to run
FROM ubuntu:22.04 as runtime

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libcairo2 \
    libcairo-gobject2 \
    libcairo-script-interpreter2 \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user for security
RUN useradd -m -u 1000 plotlib

# Set working directory
WORKDIR /app

# Copy built library and examples from builder stage
COPY --from=builder /app/build/libplotlib.a /app/lib/
COPY --from=builder /app/build/examples/ /app/examples/
COPY --from=builder /app/build/tests/basic_tests /app/tests/
COPY --from=builder /app/include/ /app/include/
COPY --from=builder /app/examples/ /app/source_examples/
COPY --from=builder /app/README.md /app/
COPY --from=builder /app/docs/ /app/docs/

# Create output directory with proper permissions
RUN mkdir -p /app/output && chown -R plotlib:plotlib /app

# Switch to non-root user
USER plotlib

# Set environment variables
ENV PLOTLIB_OUTPUT_DIR=/app/output
ENV PLOTLIB_EXAMPLES_DIR=/app/examples

# Default command - run all beginner examples
CMD ["/bin/bash", "-c", "echo 'PlotLib Docker Container - Running Examples...' && cd /app/examples && for example in 01_first_scatter_plot 02_colors_and_multiple_series 03_first_line_plot 04_first_histogram 05_simple_subplots; do echo \"Running $example...\"; ./$example; done && echo 'All examples completed! Check /app/output for generated plots.'"]

# Labels for documentation
LABEL org.opencontainers.image.title="PlotLib"
LABEL org.opencontainers.image.description="Cross-platform C++ plotting library with Cairo graphics"
LABEL org.opencontainers.image.version="1.0.0"
LABEL org.opencontainers.image.authors="PlotLib Contributors" 