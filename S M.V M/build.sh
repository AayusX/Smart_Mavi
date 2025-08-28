#!/bin/bash

# Smart MA.VI Manager - Universal Build Script
# This script detects the platform and runs the appropriate build script

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

print_header() {
    echo -e "${GREEN}"
    echo "╔══════════════════════════════════════════════════════════════╗"
    echo "║                Smart MA.VI Manager Build Script              ║"
    echo "║                     School Management System                 ║"
    echo "╚══════════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
}

print_header

# Check if we're in the right directory
if [ ! -f "CMakeLists.txt" ]; then
    print_error "CMakeLists.txt not found. Please run this script from the project root directory."
    exit 1
fi

# Detect operating system
print_status "Detecting operating system..."

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
    BUILD_SCRIPT="scripts/build-linux.sh"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
    BUILD_SCRIPT="scripts/build-macos.sh"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    OS="Windows"
    BUILD_SCRIPT="scripts/build-windows.bat"
    print_warning "Windows detected. Please run scripts/build-windows.bat directly."
    print_status "Or install WSL (Windows Subsystem for Linux) for better compatibility."
    exit 1
else
    print_error "Unsupported operating system: $OSTYPE"
    exit 1
fi

print_success "Detected OS: $OS"

# Check if the appropriate build script exists
if [ ! -f "$BUILD_SCRIPT" ]; then
    print_error "Build script not found: $BUILD_SCRIPT"
    exit 1
fi

# Check if build script is executable (for Unix-like systems)
if [[ "$OS" != "Windows" ]] && [ ! -x "$BUILD_SCRIPT" ]; then
    print_status "Making build script executable..."
    chmod +x "$BUILD_SCRIPT"
fi

# Create packages directory
mkdir -p packages

# Run the appropriate build script
print_status "Starting build process for $OS..."
print_status "Build script: $BUILD_SCRIPT"

if [[ "$OS" == "Windows" ]]; then
    # For Windows, we need to run the batch file
    print_warning "Please run the Windows build script manually:"
    print_status "  scripts/build-windows.bat"
    exit 1
else
    # For Unix-like systems, run the shell script
    ./"$BUILD_SCRIPT"
fi

print_success "Build process completed!"
print_status "Check the packages/ directory for generated packages."
