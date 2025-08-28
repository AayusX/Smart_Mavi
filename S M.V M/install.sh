#!/bin/bash

# Smart MA.VI Manager Installation Script
# This script installs the Smart MA.VI Manager application system-wide

set -e

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
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

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_header() {
    echo -e "${GREEN}"
    echo "╔══════════════════════════════════════════════════════════════╗"
    echo "║           Smart MA.VI Manager Installation                   ║"
    echo "║                School Management System                      ║"
    echo "╚══════════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
}

print_header

# Check if running as root for system-wide installation
if [ "$EUID" -ne 0 ]; then
    print_warning "Not running as root. Installing to user directory..."
    INSTALL_PREFIX="$HOME/.local"
    BIN_DIR="$INSTALL_PREFIX/bin"
    SHARE_DIR="$INSTALL_PREFIX/share"
    APPLICATIONS_DIR="$SHARE_DIR/applications"
    ICONS_DIR="$SHARE_DIR/icons/hicolor/256x256/apps"
else
    print_status "Installing system-wide..."
    INSTALL_PREFIX="/usr/local"
    BIN_DIR="$INSTALL_PREFIX/bin"
    SHARE_DIR="$INSTALL_PREFIX/share"
    APPLICATIONS_DIR="$SHARE_DIR/applications"
    ICONS_DIR="$SHARE_DIR/icons/hicolor/256x256/apps"
fi

# Check if application is built
if [ ! -f "build/bin/SmartMAVIManager" ]; then
    print_error "Application not built. Please run: ./build.sh"
    exit 1
fi

# Create directories
print_status "Creating installation directories..."
mkdir -p "$BIN_DIR"
mkdir -p "$APPLICATIONS_DIR"
mkdir -p "$ICONS_DIR"
mkdir -p "$SHARE_DIR/smart-mavi-manager"

# Install executable
print_status "Installing executable..."
cp "build/bin/SmartMAVIManager" "$BIN_DIR/"
chmod +x "$BIN_DIR/SmartMAVIManager"

# Install desktop file
print_status "Installing desktop file..."
cp "packaging/smart-mavi-manager.desktop" "$APPLICATIONS_DIR/"

# Install icon
print_status "Installing icon..."
cp "resources/logo.png" "$ICONS_DIR/smart-mavi-manager.png"

# Install data files
print_status "Installing data files..."
cp -r data/* "$SHARE_DIR/smart-mavi-manager/"

# Update desktop database (if available)
if command -v update-desktop-database >/dev/null 2>&1; then
    print_status "Updating desktop database..."
    if [ "$EUID" -eq 0 ]; then
        update-desktop-database "$APPLICATIONS_DIR"
    else
        update-desktop-database "$APPLICATIONS_DIR" 2>/dev/null || true
    fi
fi

# Update icon cache (if available)
if command -v gtk-update-icon-cache >/dev/null 2>&1; then
    print_status "Updating icon cache..."
    if [ "$EUID" -eq 0 ]; then
        gtk-update-icon-cache -t "$SHARE_DIR/icons/hicolor" 2>/dev/null || true
    else
        gtk-update-icon-cache -t "$HOME/.local/share/icons/hicolor" 2>/dev/null || true
    fi
fi

print_success "Installation completed!"
print_status "Installation details:"
echo "  Executable: $BIN_DIR/SmartMAVIManager"
echo "  Desktop file: $APPLICATIONS_DIR/smart-mavi-manager.desktop"
echo "  Icon: $ICONS_DIR/smart-mavi-manager.png"
echo "  Data files: $SHARE_DIR/smart-mavi-manager/"
echo ""
print_status "To run the application:"
echo "  Command line: SmartMAVIManager"
echo "  Desktop: Look for 'Smart MA.VI Manager' in your application menu"
echo ""
print_status "Default login credentials:"
echo "  Username: admin"
echo "  Password: admin123"
print_warning "IMPORTANT: Change the default password after first login!"
