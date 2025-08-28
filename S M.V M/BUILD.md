# Smart MA.VI Manager - Build Guide

This guide explains how to build the Smart MA.VI Manager application for different platforms.

## Prerequisites

### Common Requirements
- **CMake 3.16+**: Build system
- **C++17 compatible compiler**: GCC 7+, Clang 6+, or MSVC 2017+
- **Qt6**: GUI framework

### Platform-Specific Requirements

#### Linux
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential cmake
sudo apt install qt6-base-dev qt6-sql-dev qt6-network-dev qt6-charts-dev

# Fedora/CentOS/RHEL
sudo dnf install gcc-c++ cmake
sudo dnf install qt6-qtbase-devel qt6-qtsql-devel qt6-qtnetwork-devel qt6-qtcharts-devel

# Arch Linux
sudo pacman -S base-devel cmake
sudo pacman -S qt6-base qt6-sql qt6-network qt6-charts
```

#### Windows
1. **Visual Studio 2019/2022** with C++ workload, or **MinGW-w64**
2. **CMake**: Download from https://cmake.org/download/
3. **Qt6**: Download from https://www.qt.io/download or install via vcpkg

#### macOS
```bash
# Using Homebrew
brew install cmake
brew install qt6

# Or install Xcode Command Line Tools
xcode-select --install
```

## Quick Build

### Universal Build Script
The easiest way to build for your platform:

```bash
# Make the script executable
chmod +x build.sh

# Run the build
./build.sh
```

This script will:
1. Detect your operating system
2. Run the appropriate platform-specific build script
3. Generate packages in the `packages/` directory

### Platform-Specific Build Scripts

#### Linux
```bash
./scripts/build-linux.sh
```
**Outputs:**
- `.deb` package for Debian/Ubuntu systems
- `.AppImage` (if linuxdeploy is available)

#### Windows
```cmd
scripts\build-windows.bat
```
**Outputs:**
- `.exe` installer using NSIS
- `install.bat` for manual installation

#### macOS
```bash
./scripts/build-macos.sh
```
**Outputs:**
- `.dmg` package (if create-dmg is available)
- `.tar.gz` package as fallback

## Manual Build Process

### 1. Clone and Setup
```bash
git clone <repository-url>
cd smart-mavi-manager
```

### 2. Create Build Directory
```bash
mkdir build
cd build
```

### 3. Configure with CMake
```bash
# Linux/macOS
cmake .. -DCMAKE_BUILD_TYPE=Release

# Windows with Visual Studio
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

# Windows with MinGW
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
```

### 4. Build the Application
```bash
# Linux/macOS
make -j$(nproc)

# Windows with Visual Studio
cmake --build . --config Release

# Windows with MinGW
cmake --build . -j%NUMBER_OF_PROCESSORS%
```

### 5. Generate Packages
```bash
# Generate all configured packages
make package

# Or generate specific package types
cpack -G DEB    # Linux .deb
cpack -G NSIS   # Windows .exe
cpack -G TGZ    # Generic .tar.gz
```

## Package Types

### Linux Packages

#### .deb Package
- **Installation**: `sudo dpkg -i SmartMAVIManager_1.0.0_amd64.deb`
- **Dependencies**: Automatically resolved by package manager
- **Integration**: Appears in system menus, desktop integration

#### AppImage
- **Installation**: `chmod +x SmartMAVIManager-1.0.0-x86_64.AppImage && ./SmartMAVIManager-1.0.0-x86_64.AppImage`
- **Portable**: No installation required, runs from any location
- **Self-contained**: Includes all dependencies

### Windows Packages

#### .exe Installer
- **Installation**: Run as administrator
- **Features**: Automatic desktop shortcut, start menu entry, uninstaller
- **Dependencies**: Bundled with the installer

#### Manual Installation
- **Installation**: Run `install.bat`
- **Features**: Simple file copy to Program Files

### macOS Packages

#### .dmg Package
- **Installation**: Drag app to Applications folder
- **Features**: Standard macOS installation method
- **Code signing**: Recommended for distribution

#### .tar.gz Package
- **Installation**: Extract and copy to Applications
- **Features**: Simple archive format

## Development Build

For development and testing:

```bash
# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make

# Run from build directory
./bin/SmartMAVIManager
```

## Troubleshooting

### Common Issues

#### Qt6 Not Found
```bash
# Set Qt6 path manually
export CMAKE_PREFIX_PATH="/path/to/qt6:$CMAKE_PREFIX_PATH"
cmake ..
```

#### Compiler Not Found
```bash
# Linux: Install build tools
sudo apt install build-essential

# Windows: Install Visual Studio or MinGW
# macOS: Install Xcode Command Line Tools
xcode-select --install
```

#### CMake Version Too Old
```bash
# Linux: Update CMake
sudo apt install cmake  # or download from cmake.org

# Windows/macOS: Download from https://cmake.org/download/
```

#### Package Generation Fails
```bash
# Check CPack configuration in CMakeLists.txt
# Ensure all required files are installed
make install DESTDIR=./test-install
```

### Platform-Specific Issues

#### Linux
- **AppImage creation fails**: Install `linuxdeploy`
- **Missing libraries**: Install development packages
- **Permission issues**: Use `sudo` for system-wide installation

#### Windows
- **Visual Studio not found**: Install Visual Studio with C++ workload
- **Qt6 not in PATH**: Add Qt bin directory to PATH
- **NSIS not found**: Install NSIS or use portable version

#### macOS
- **Code signing issues**: Use valid developer certificate
- **DMG creation fails**: Install `create-dmg` via Homebrew
- **Architecture issues**: Ensure universal binary support

## Advanced Configuration

### Custom Installation Path
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/custom/path
```

### Enable/Disable Features
```bash
cmake .. -DBUILD_TESTS=ON -DBUILD_DOCS=OFF
```

### Cross-Compilation
```bash
# Set toolchain file
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake
```

## Distribution

### Linux Distribution
1. Test on target distributions
2. Ensure all dependencies are available
3. Consider using AppImage for maximum compatibility

### Windows Distribution
1. Test on clean Windows installations
2. Include Visual C++ Redistributable if needed
3. Consider code signing for better user experience

### macOS Distribution
1. Test on different macOS versions
2. Code sign the application
3. Consider notarization for Gatekeeper compatibility

## Support

For build issues:
1. Check the troubleshooting section
2. Verify all prerequisites are installed
3. Check CMake and compiler versions
4. Review build logs for specific error messages

## Version Information

- **Current Version**: 1.0.0
- **Build System**: CMake 3.16+
- **GUI Framework**: Qt6
- **Database**: SQLite3
- **C++ Standard**: C++17
