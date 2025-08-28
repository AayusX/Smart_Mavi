#!/bin/bash

# Smart MA.VI Manager - macOS Build Script
# This script builds the application and creates .dmg package

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
BUILD_DIR="build-macos"
PACKAGE_DIR="packages"
DMG_FILE="${PROJECT_NAME}_${VERSION}_macos.dmg"
APP_NAME="${PROJECT_NAME}.app"

print_status "Starting macOS build process for $PROJECT_NAME v$VERSION"

# Check if we're on macOS
if [[ "$OSTYPE" != "darwin"* ]]; then
    print_error "This script is designed for macOS only."
    exit 1
fi

# Check dependencies
print_status "Checking dependencies..."

# Check for CMake
if ! command -v cmake &> /dev/null; then
    print_error "CMake is not installed. Please install it first."
    print_status "Using Homebrew: brew install cmake"
    print_status "Or download from: https://cmake.org/download/"
    exit 1
fi

# Check for Qt6
if ! pkg-config --exists Qt6Core; then
    print_error "Qt6 is not installed. Please install it first."
    print_status "Using Homebrew: brew install qt6"
    print_status "Or download from: https://www.qt.io/download"
    exit 1
fi

# Check for Xcode Command Line Tools
if ! command -v xcodebuild &> /dev/null; then
    print_error "Xcode Command Line Tools are not installed."
    print_status "Install with: xcode-select --install"
    exit 1
fi

# Check for create-dmg (optional, for creating DMG)
if ! command -v create-dmg &> /dev/null; then
    print_warning "create-dmg not found. DMG creation will be skipped."
    print_status "To create DMG, install create-dmg:"
    print_status "brew install create-dmg"
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
    -DCMAKE_INSTALL_PREFIX=/Applications \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 \
    -DCMAKE_OSX_ARCHITECTURES=x86_64\;arm64

# Build the application
print_status "Building the application..."
make -j$(sysctl -n hw.ncpu)

print_success "Application built successfully"

# Create packages directory
mkdir -p "../$PACKAGE_DIR"

# Create .app bundle
print_status "Creating .app bundle..."
DESTDIR="$(pwd)/appdir" make install

# Create DMG if create-dmg is available
if command -v create-dmg &> /dev/null; then
    print_status "Creating DMG package..."
    
    # Create DMG
    create-dmg \
        --volname "$PROJECT_NAME $VERSION" \
        --volicon "../resources/logo.icns" \
        --window-pos 200 120 \
        --window-size 800 400 \
        --icon-size 100 \
        --icon "$APP_NAME" 200 190 \
        --hide-extension "$APP_NAME" \
        --app-drop-link 600 185 \
        "../$PACKAGE_DIR/$DMG_FILE" \
        "appdir/Applications/"
    
    if [ -f "../$PACKAGE_DIR/$DMG_FILE" ]; then
        print_success "DMG package created: $PACKAGE_DIR/$DMG_FILE"
    else
        print_warning "DMG creation failed"
    fi
else
    print_warning "Skipping DMG creation (create-dmg not available)"
fi

# Create a simple .tar.gz package as fallback
print_status "Creating .tar.gz package..."
cd appdir
tar -czf "../$PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_macos.tar.gz" Applications/
cd ..

if [ -f "$PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_macos.tar.gz" ]; then
    print_success ".tar.gz package created: $PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_macos.tar.gz"
fi

# Clean up
cd ..
rm -rf "$BUILD_DIR"

print_success "macOS build completed!"
print_status "Packages created in $PACKAGE_DIR/:"
if [ -f "$PACKAGE_DIR/$DMG_FILE" ]; then
    print_status "  DMG package: $PACKAGE_DIR/$DMG_FILE"
fi
if [ -f "$PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_macos.tar.gz" ]; then
    print_status "  .tar.gz package: $PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_macos.tar.gz"
fi

print_status "Installation instructions:"
if [ -f "$PACKAGE_DIR/$DMG_FILE" ]; then
    print_status "  DMG: Open $PACKAGE_DIR/$DMG_FILE and drag the app to Applications"
fi
if [ -f "$PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_macos.tar.gz" ]; then
    print_status "  .tar.gz: Extract and copy the app to Applications folder"
fi
