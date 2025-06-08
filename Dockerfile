# PlotLib Docker Image
# Multi-stage build for cross-platform compatibility
FROM alpine:latest as builder

# Install build dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    pkgconfig \
    cairo-dev \
    git

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Build the library and examples
RUN mkdir -p build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make plotlib && \
    make beginner_examples && \
    make advanced_examples && \
    make basic_tests

# Create output directory
RUN mkdir -p /app/output

# Runtime stage - minimal image with just what's needed to run
FROM alpine:latest as runtime

# Install runtime dependencies
RUN apk add --no-cache \
    cairo \
    libstdc++

# Create non-root user
RUN adduser -D -u 1000 plotlib

# Create directories
WORKDIR /app
RUN mkdir -p /app/output && \
    chown -R plotlib:plotlib /app

# Copy built binaries and libraries from builder stage
COPY --from=builder /app/build/plotlib /app/lib/
COPY --from=builder /app/build/examples/ /app/examples/
COPY --from=builder /app/build/tests/ /app/tests/

# Switch to non-root user
USER plotlib

# Set environment variables
ENV PLOTLIB_OUTPUT_DIR=/app/output
ENV LD_LIBRARY_PATH=/app/lib

# Volume for output
VOLUME ["/app/output"]

# Default command
CMD ["/bin/sh", "-c", "echo 'PlotLib Docker Container Ready!' && echo 'Available examples:' && ls /app/examples/ && echo 'Run: docker run -v ./output:/app/output plotlib-image /app/examples/01_first_scatter_plot'"]

# Labels for documentation
LABEL org.opencontainers.image.title="PlotLib"
LABEL org.opencontainers.image.description="Cross-platform C++ plotting library with Cairo graphics"
LABEL org.opencontainers.image.version="1.0.0"
LABEL org.opencontainers.image.authors="PlotLib Contributors" 