# PlotLib Cross-Platform Docker Image
FROM alpine:latest

# Install dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    pkgconfig \
    cairo-dev \
    cairo \
    libstdc++ \
    git

# Create non-root user
RUN adduser -D -u 1000 plotlib

# Create working directory
WORKDIR /app

# Copy source code
COPY CMakeLists.txt .
COPY cmake/ cmake/
COPY include/ include/
COPY src/ src/
COPY examples/ examples/
COPY tests/ tests/

# Set proper ownership
RUN chown -R plotlib:plotlib /app

# Switch to non-root user for build
USER plotlib

# Build PlotLib
RUN mkdir -p build && \
    cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make

# Create output directory
RUN mkdir -p output

# Set environment variables
ENV PLOTLIB_OUTPUT_DIR=/app/output

# Volume for output
VOLUME ["/app/output"]

# Default command
CMD ["/bin/sh", "-c", "echo '🐳 PlotLib Cross-Platform Container Ready!' && echo 'Built successfully on Alpine Linux' && echo '✅ Available examples:' && ls -la /app/build/examples/ | grep -E '^-.*\\.' && echo '' && echo '📖 Usage:' && echo '  docker run -v ./output:/app/output plotlib /app/build/examples/01_first_scatter_plot' && echo '  docker run -v ./output:/app/output plotlib /app/build/examples/05_simple_subplots'"]

# Labels for documentation
LABEL org.opencontainers.image.title="PlotLib"
LABEL org.opencontainers.image.description="Cross-platform C++ plotting library with Cairo graphics"
LABEL org.opencontainers.image.version="1.0.0"
LABEL org.opencontainers.image.authors="PlotLib Contributors" 