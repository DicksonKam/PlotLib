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
RUN mkdir -p output && chmod 755 output

# Copy only the built artifacts from builder stage
COPY --from=builder /app/build /app/build

# Set proper ownership and permissions
RUN chown -R plotlib:plotlib /app && \
    chmod -R 755 /app && \
    chmod 777 /app/output

# Switch to non-root user
USER plotlib

# Set environment variables
ENV PLOTLIB_OUTPUT_DIR=/app/output

# Volume for output
VOLUME ["/app/output"]

# Default command
CMD ["/bin/sh", "-c", "echo '🐳 PlotLib Optimized Container Ready!' && echo 'Built successfully on Alpine Linux' && echo '✅ Available examples:' && ls -la /app/build/examples/ | grep -E '^-.*\\.' && echo '' && echo '📖 Usage Examples:' && BEGINNER_COUNT=$(ls /app/build/examples/[0-9][0-9]_* 2>/dev/null | wc -l) && ADVANCED_COUNT=$(ls /app/build/examples/advanced_* 2>/dev/null | wc -l) && PLOT_TYPES_COUNT=$(ls /app/build/examples/plot_types_* 2>/dev/null | wc -l) && echo \"  # Beginner Examples (${BEGINNER_COUNT} total):\" && FIRST_BEGINNER=$(ls /app/build/examples/[0-9][0-9]_* 2>/dev/null | head -1) && [ -n \"$FIRST_BEGINNER\" ] && echo \"  docker run -v ./output:/app/output plotlib $FIRST_BEGINNER\" && echo \"  # Advanced Examples (${ADVANCED_COUNT} total):\" && FIRST_ADVANCED=$(ls /app/build/examples/advanced_* 2>/dev/null | head -1) && [ -n \"$FIRST_ADVANCED\" ] && echo \"  docker run -v ./output:/app/output plotlib $FIRST_ADVANCED\" && echo \"  # Plot Types Examples (${PLOT_TYPES_COUNT} total):\" && FIRST_PLOT_TYPES=$(ls /app/build/examples/plot_types_* 2>/dev/null | head -1) && [ -n \"$FIRST_PLOT_TYPES\" ] && echo \"  docker run -v ./output:/app/output plotlib $FIRST_PLOT_TYPES\" && echo '' && echo '  # Run all examples:' && echo '  docker run -v ./output:/app/output plotlib /bin/sh -c \"make -C /app/build run_all_examples\"'"]

# Labels for documentation
LABEL org.opencontainers.image.title="PlotLib"
LABEL org.opencontainers.image.description="Cross-platform C++ plotting library with Cairo graphics (Optimized)"
LABEL org.opencontainers.image.version="1.0.0"
LABEL org.opencontainers.image.authors="PlotLib Contributors" 