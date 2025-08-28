#!/bin/bash

# Smart MA.VI Manager - Linux Build Script
# This script builds the application and creates .deb and .AppImage packages

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored status messages
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Configuration
PROJECT_NAME="SmartMAVIManager"
VERSION="1.0.0"
BUILD_DIR="build-linux"
PACKAGE_DIR="packages"
DEB_FILE="${PROJECT_NAME}_${VERSION}_amd64.deb"
APPIMAGE_FILE="${PROJECT_NAME}-${VERSION}-x86_64.AppImage"

print_status "Starting Linux build process for $PROJECT_NAME v$VERSION"

# Check dependencies
print_status "Checking dependencies..."

# Check for CMake
if ! command -v cmake &> /dev/null; then
    print_error "CMake is not installed. Please install it first."
    print_status "Ubuntu/Debian: sudo apt install cmake"
    print_status "Fedora: sudo dnf install cmake"
    exit 1
fi

# Check for Qt6
if ! pkg-config --exists Qt6Core; then
    print_error "Qt6 is not installed. Please install it first."
    print_status "Ubuntu/Debian: sudo apt install qt6-base-dev qt6-sql-dev qt6-network-dev qt6-charts-dev"
    print_status "Fedora: sudo dnf install qt6-qtbase-devel qt6-qtsql-devel qt6-qtnetwork-devel qt6-qtcharts-devel"
    exit 1
fi

# Check for build tools
if ! command -v make &> /dev/null; then
    print_error "Make is not installed. Please install build-essential."
    print_status "Ubuntu/Debian: sudo apt install build-essential"
    exit 1
fi

print_success "All dependencies are available"

# Create build directory
print_status "Creating build directory..."
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
print_status "Configuring with CMake..."
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DCMAKE_INSTALL_LIBDIR=lib \
    -DCMAKE_INSTALL_DATADIR=share \
    -DCMAKE_INSTALL_DOCDIR=share/doc \
    -DCMAKE_INSTALL_MANDIR=share/man

# Build the application
print_status "Building the application..."
make -j$(nproc)

print_success "Application built successfully"

# Create packages directory
mkdir -p "../$PACKAGE_DIR"

# Generate .deb package
print_status "Generating .deb package..."
make package

# Move .deb to packages directory
if [ -f "$DEB_FILE" ]; then
    mv "$DEB_FILE" "../$PACKAGE_DIR/"
    print_success ".deb package created: $PACKAGE_DIR/$DEB_FILE"
else
    print_warning ".deb package not found"
fi

# Generate AppImage
print_status "Generating AppImage..."

# Install to a temporary directory
DESTDIR="$(pwd)/appdir" make install

# Create AppImage using linuxdeploy
if command -v linuxdeploy &> /dev/null; then
    linuxdeploy --appdir appdir --output appimage
    if [ -f "*.AppImage" ]; then
        mv *.AppImage "../$PACKAGE_DIR/$APPIMAGE_FILE"
        print_success "AppImage created: $PACKAGE_DIR/$APPIMAGE_FILE"
    fi
else
    print_warning "linuxdeploy not found. Skipping AppImage creation."
    print_status "To create AppImage, install linuxdeploy:"
    print_status "wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage"
    print_status "chmod +x linuxdeploy-x86_64.AppImage"
    print_status "sudo mv linuxdeploy-x86_64.AppImage /usr/local/bin/linuxdeploy"
fi

# Clean up
cd ..
rm -rf "$BUILD_DIR"

print_success "Linux build completed!"
print_status "Packages created in $PACKAGE_DIR/:"
if [ -f "$PACKAGE_DIR/$DEB_FILE" ]; then
    print_status "  .deb package: $PACKAGE_DIR/$DEB_FILE"
fi
if [ -f "$PACKAGE_DIR/$APPIMAGE_FILE" ]; then
    print_status "  AppImage: $PACKAGE_DIR/$APPIMAGE_FILE"
fi

print_status "Installation instructions:"
print_status "  .deb package: sudo dpkg -i $PACKAGE_DIR/$DEB_FILE"
print_status "  AppImage: chmod +x $PACKAGE_DIR/$APPIMAGE_FILE && ./$PACKAGE_DIR/$APPIMAGE_FILE"

