# 🐳 Docker Setup Guide for PlotLib

## Step 1: Install Docker

### For macOS (your current system):
```bash
# Option 1: Download Docker Desktop (Recommended)
# Visit: https://docs.docker.com/desktop/install/mac/
# Download and install Docker Desktop for Mac

# Option 2: Using Homebrew
brew install --cask docker
```

### For Windows:
```powershell
# Download Docker Desktop for Windows
# Visit: https://docs.docker.com/desktop/install/windows/
# IMPORTANT: Ensure "Use WSL 2 based engine" is enabled (default)
```

### For Linux (Ubuntu/Debian):
```bash
# Update package index
sudo apt-get update

# Install Docker
sudo apt-get install -y docker.io docker-compose-plugin

# Add user to docker group
sudo usermod -aG docker $USER

# Restart or logout/login for group changes to take effect
```

## Step 2: Verify Docker Installation

After installing Docker, restart your terminal and run:

```bash
# Check Docker version
docker --version

# Check Docker Compose version
docker compose version

# Test Docker is working
docker run hello-world
```

Expected output:
```
Docker version 24.0.x, build xxx
Docker Compose version v2.x.x
Hello from Docker! (and additional success message)
```

## Step 3: Test PlotLib Docker Setup

Once Docker is installed, test our PlotLib Docker setup:

### Platform-Specific Notes:
- **Windows**: Use PowerShell or Command Prompt (Docker Desktop handles Linux containers)
- **macOS/Linux**: Use Terminal

### Quick Test (Run all examples):
```bash
# From the PlotLib directory
cd PlotLib

# Run all examples and generate plots
docker compose up plotlib

# Check generated plots
ls -la output/     # Linux/macOS
dir output\        # Windows (alternative)
```

### Alternative for Windows (if volume mounting issues):
```powershell
# Windows PowerShell alternative
docker build -t plotlib .
docker run --rm plotlib
# Note: Plots stay inside container (for testing only)
```

### Individual Example Test:
```bash
# Run individual examples directly
docker run --rm -v ./output:/app/output plotlib /app/build/examples/01_first_scatter_plot
```

## Step 4: Verify Everything Works

After running the Docker commands, you should see:

1. **Docker builds successfully** (may take 5-10 minutes first time)
2. **Examples run without errors**
3. **Generated plots in output/ directory**:
   ```
   output/
   ├── beginner_01_first_scatter_plot.png
   ├── beginner_02_colors_and_multiple_series.png
   ├── beginner_03_first_line_plot.png
   ├── advanced_01_custom_styling_and_advanced_features.png
   ├── plot_types_01_line_plot.png
   └── ... (15+ total plots from all categories)
   ```

## Troubleshooting

### "docker: command not found"
- Docker not installed or not in PATH
- Solution: Install Docker Desktop or restart terminal

### "permission denied" (Linux)
- User not in docker group
- Solution: `sudo usermod -aG docker $USER` and logout/login

### "Cannot connect to Docker daemon"
- Docker service not running
- Solution: Start Docker Desktop or `sudo systemctl start docker`

### Build takes too long
- First build downloads base images (normal)
- Subsequent builds use cache (much faster)

## Next Steps

Once Docker is working:
1. Read the full [Docker Guide](docs/DOCKER.md)
2. Try different services: `plotlib-dev`, `plotlib-demo`, `plotlib-test`
3. Create your own plots inside containers
4. Deploy to cloud platforms

## Benefits of Docker Setup

✅ **Cross-platform**: Works on Windows, macOS, Linux  
✅ **Consistent**: Same environment everywhere  
✅ **No dependencies**: Cairo, CMake all included  
✅ **Isolated**: Doesn't affect your system  
✅ **Portable**: Easy to share and deploy  

---

**Ready to start plotting with Docker!** 🎯🐳 