# 🐳 PlotLib Docker Guide

> **⚠️ Note**: This documentation references some Docker services that have been simplified in the current docker-compose.yml. The main `plotlib` service works as documented, but some advanced services mentioned here may not be available.

Run PlotLib on **any platform** (Windows, macOS, Linux) using Docker containers.

## 🚀 Quick Start

### Prerequisites
- [Docker](https://docs.docker.com/get-docker/) installed on your system
- [Docker Compose](https://docs.docker.com/compose/install/) (usually included with Docker Desktop)

### Run All Examples (Recommended First Try)
```bash
# Clone the repository
git clone <repository-url>
cd plotlib

# Run all examples and generate plots
docker compose up plotlib

# Check generated plots
ls output/
```

## 📋 Available Services

### 1. **Production Service** (`plotlib`)
Runs all examples and tests, generates output plots.
```bash
# Run all examples and tests
docker compose up plotlib

# Run in background
docker compose up -d plotlib

# View logs
docker compose logs plotlib
```

### 2. **Development Service** (`plotlib-dev`)
Interactive development environment with full source access.
```bash
# Start interactive development container
docker compose run --rm plotlib-dev

# Inside container:
cd build
make plotlib
make beginner_examples
./examples/01_first_scatter_plot
```

### 3. **Demo Service** (`plotlib-demo`)
Run specific examples for demonstrations.
```bash
# Run beginner examples only
DEMO_TYPE=beginner docker compose up plotlib-demo

# Run advanced examples only
DEMO_TYPE=advanced docker compose up plotlib-demo

# Run specific example
DEMO_TYPE=01_first_scatter_plot docker compose up plotlib-demo
```

### 4. **Test Service** (`plotlib-test`)
Run only the test suite.
```bash
# Run tests
docker compose up plotlib-test
```

## 🛠️ Development Workflows

### Interactive Development
```bash
# Start development container
docker compose run --rm plotlib-dev

# Inside container - full development environment
cd /app
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Run examples
cd examples
./01_first_scatter_plot

# Compile your own code
g++ -std=c++17 -I../include my_plot.cpp -L. -lplotlib \
    `pkg-config --cflags --libs cairo cairo-svg` -o my_plot
./my_plot
```

### Custom Plot Development
```bash
# Mount your custom code
docker compose run --rm -v ./my_plots:/app/my_plots plotlib-dev

# Inside container
cd /app/my_plots
g++ -std=c++17 -I../include -L../lib my_custom_plot.cpp \
    -lplotlib `pkg-config --cflags --libs cairo cairo-svg` \
    -o my_custom_plot
./my_custom_plot
```

## 🌍 Cross-Platform Usage

### Windows (PowerShell/CMD)
```powershell
# Clone and run
git clone <repository-url>
cd plotlib
docker compose up plotlib

# Development
docker compose run --rm plotlib-dev
```

### macOS (Terminal)
```bash
# Same commands as Linux
docker compose up plotlib
docker compose run --rm plotlib-dev
```

### Linux
```bash
# Standard Docker Compose commands
docker compose up plotlib
docker compose run --rm plotlib-dev
```

### Cloud Platforms (AWS, GCP, Azure)
```bash
# Works on any cloud platform with Docker support
docker build -t plotlib .
docker run -v $(pwd)/output:/app/output plotlib
```

## 📁 Volume Mapping

The Docker setup automatically maps the `output/` directory to preserve generated plots:

```bash
# Your host directory    # Container directory
./output            ->   /app/output
```

For development, source code is also mapped:
```bash
# Development mode volume mapping
./               ->   /app            # Full source access
./output         ->   /app/output     # Plot output
```

## 🔧 Customization

### Build Arguments
```bash
# Custom build with different base image
docker build --build-arg BASE_IMAGE=ubuntu:20.04 -t plotlib:custom .
```

### Environment Variables
```bash
# Custom output directory
PLOTLIB_OUTPUT_DIR=/custom/path docker compose up plotlib

# Custom demo type
DEMO_TYPE=histogram docker compose up plotlib-demo
```

### Custom Docker Compose Override
Create `docker compose.override.yml`:
```yaml
version: '3.8'
services:
  plotlib:
    volumes:
      - ./my_custom_output:/app/output
    environment:
      - CUSTOM_VAR=value
```

## 🐛 Troubleshooting

### Permission Issues (Linux)
```bash
# Fix output directory permissions
sudo chown -R $USER:$USER output/

# Or run with user mapping
docker compose run --rm --user $(id -u):$(id -g) plotlib
```

### Windows Path Issues
```powershell
# Use PowerShell (not CMD) for better path handling
# Or use absolute paths
docker run -v ${PWD}/output:/app/output plotlib
```

### Memory Issues
```bash
# For large datasets, increase Docker memory limit
# Docker Desktop -> Settings -> Resources -> Memory -> 4GB+
```

### Build Issues
```bash
# Clean rebuild
docker compose down
docker compose build --no-cache plotlib
docker compose up plotlib
```

## 📊 Example Outputs

After running any service, check the `output/` directory:

```
output/
├── 01_first_scatter_plot.png
├── 02_colors_and_multiple_series.png
├── 02_color_showcase.png
├── 03_temperature_line.png
├── 03_math_functions.png
├── 04_test_scores.png
├── 05_first_dashboard.png
├── advanced_01_rgb_precision.png
├── advanced_04_reference_lines_scatter.png
└── ... (16+ more plots)
```

## 🚀 Production Deployment

### Single Container
```bash
# Build and run production image
docker build -t plotlib:prod .
docker run -v $(pwd)/output:/app/output plotlib:prod
```

### With Orchestration
```yaml
# Kubernetes deployment example
apiVersion: apps/v1
kind: Deployment
metadata:
  name: plotlib
spec:
  replicas: 1
  selector:
    matchLabels:
      app: plotlib
  template:
    metadata:
      labels:
        app: plotlib
    spec:
      containers:
      - name: plotlib
        image: plotlib:prod
        volumeMounts:
        - name: output
          mountPath: /app/output
      volumes:
      - name: output
        persistentVolumeClaim:
          claimName: plotlib-output
```

## 🔗 Integration Examples

### CI/CD Pipeline
```yaml
# GitHub Actions example
- name: Run PlotLib Tests
  run: |
    docker compose up --exit-code-from plotlib-test plotlib-test
    
- name: Generate Example Plots
  run: |
    docker compose up plotlib
    
- name: Upload Artifacts
  uses: actions/upload-artifact@v4
  with:
    name: generated-plots
    path: output/
```

### Jupyter Notebooks
```python
# In Jupyter cell
import subprocess
import os

# Run PlotLib container
result = subprocess.run(['docker compose', 'up', 'plotlib'], 
                       capture_output=True, text=True)

# Display generated plots
from IPython.display import Image, display
for file in os.listdir('output'):
    if file.endswith('.png'):
        display(Image(f'output/{file}'))
```

## 📚 Next Steps

1. **Try the examples**: `docker compose up plotlib`
2. **Start developing**: `docker compose run --rm plotlib-dev`
3. **Read the API docs**: [API Reference](api/README.md)
4. **Check examples**: [Examples Guide](../examples/README.md)

## 🆘 Getting Help

- **Docker issues**: Check [Docker documentation](https://docs.docker.com/)
- **PlotLib issues**: See [main README](../README.md)
- **Examples**: Run `docker compose up plotlib-demo`

---

**🎯 Happy containerized plotting!** 🐳📊 