#!/bin/bash

# Smart MA.VI Manager - Package Creation Script
# This script creates .deb and .AppImage packages

set -e

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
BUILD_DIR="build-packages"
PACKAGE_DIR="packages"

print_status "Starting package creation for $PROJECT_NAME v$VERSION"

# Create directories
mkdir -p $BUILD_DIR
mkdir -p $PACKAGE_DIR

# Build the application
print_status "Building the application..."
cd $BUILD_DIR
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cd ..

# Create .deb package
print_status "Creating .deb package..."
cd $BUILD_DIR
cpack -G DEB
cd ..

# Move .deb package to packages directory
if [ -f "$BUILD_DIR/$PROJECT_NAME-$VERSION-Linux.deb" ]; then
    mv "$BUILD_DIR/$PROJECT_NAME-$VERSION-Linux.deb" "$PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_amd64.deb"
    print_success ".deb package created: $PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_amd64.deb"
else
    print_error ".deb package not found"
fi

# Create AppImage (if linuxdeploy is available)
if command -v linuxdeploy &> /dev/null; then
    print_status "Creating AppImage..."
    cd $BUILD_DIR
    
    # Install to appdir
    make install DESTDIR=appdir
    
    # Create AppImage
    linuxdeploy --appdir appdir --output appimage
    
    cd ..
    
    # Move AppImage to packages directory
    if [ -f "$BUILD_DIR/$PROJECT_NAME-$VERSION-x86_64.AppImage" ]; then
        mv "$BUILD_DIR/$PROJECT_NAME-$VERSION-x86_64.AppImage" "$PACKAGE_DIR/"
        print_success "AppImage created: $PACKAGE_DIR/$PROJECT_NAME-$VERSION-x86_64.AppImage"
    else
        print_warning "AppImage not created"
    fi
else
    print_warning "linuxdeploy not found. Skipping AppImage creation."
    print_status "To create AppImage, install linuxdeploy:"
    print_status "wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage"
    print_status "chmod +x linuxdeploy-x86_64.AppImage"
    print_status "sudo mv linuxdeploy-x86_64.AppImage /usr/local/bin/linuxdeploy"
fi

print_success "Package creation completed!"
print_status "Packages created in $PACKAGE_DIR/:"
ls -la $PACKAGE_DIR/

print_status "Installation instructions:"
print_status "  .deb package: sudo dpkg -i $PACKAGE_DIR/${PROJECT_NAME}_${VERSION}_amd64.deb"
if [ -f "$PACKAGE_DIR/$PROJECT_NAME-$VERSION-x86_64.AppImage" ]; then
    print_status "  AppImage: chmod +x $PACKAGE_DIR/$PROJECT_NAME-$VERSION-x86_64.AppImage && ./$PACKAGE_DIR/$PROJECT_NAME-$VERSION-x86_64.AppImage"
fi

