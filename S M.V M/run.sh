#!/bin/bash

# Smart MA.VI Manager Launcher Script
# This script launches the Smart MA.VI Manager application

set -e

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_header() {
    echo -e "${GREEN}"
    echo "╔══════════════════════════════════════════════════════════════╗"
    echo "║                Smart MA.VI Manager                           ║"
    echo "║                School Management System                      ║"
    echo "║                   Shree MA.VI Imilya                        ║"
    echo "╚══════════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
}

print_header

# Check if application exists
APP_PATH="./build/bin/SmartMAVIManager"
if [ ! -f "$APP_PATH" ]; then
    print_status "Application not found. Building..."
    if [ ! -f "build.sh" ]; then
        print_status "Creating build directory..."
        mkdir -p build && cd build
        cmake ..
        make -j$(nproc)
        cd ..
    else
        chmod +x build.sh
        ./build.sh
    fi
fi

print_success "Application found: $APP_PATH"

# Check for display
if [ -z "$DISPLAY" ]; then
    print_warning "No display detected. The application is a GUI application and requires a display."
    print_status "Options:"
    echo "  1. Run with X11 forwarding (if using SSH): ssh -X username@hostname"
    echo "  2. Use VNC or similar remote desktop solution"
    echo "  3. Run on a local machine with desktop environment"
    echo ""
    print_status "Running in offscreen mode for testing..."
    export QT_QPA_PLATFORM=offscreen
fi

# Default admin credentials reminder
print_status "Default admin credentials:"
echo "  Username: admin"
echo "  Password: admin123"
echo "  IMPORTANT: Change these credentials after first login!"
echo ""

# Launch application
print_status "Launching Smart MA.VI Manager..."
exec "$APP_PATH" "$@"
