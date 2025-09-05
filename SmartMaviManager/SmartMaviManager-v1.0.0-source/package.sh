#!/bin/bash

# Smart Mavi Manager Packaging Script
echo "📦 Creating Smart Mavi Manager package..."

# Create package directory
PACKAGE_DIR="SmartMaviManager-v1.0.0"
rm -rf "$PACKAGE_DIR"
mkdir -p "$PACKAGE_DIR"

# Copy executable
cp SmartMaviManager "$PACKAGE_DIR/"

# Copy logo
cp logo.png "$PACKAGE_DIR/"

# Copy documentation
cp README.md "$PACKAGE_DIR/"

# Copy run script
cp run.sh "$PACKAGE_DIR/"

# Create install script
cat > "$PACKAGE_DIR/install.sh" << 'EOF'
#!/bin/bash

echo "🎓 Smart Mavi Manager Installer"
echo "================================"

# Check for Qt5
if ! dpkg -l | grep -q qtbase5-dev; then
    echo "📋 Installing Qt5 dependencies..."
    sudo apt update
    sudo apt install qtbase5-dev qttools5-dev -y
fi

# Make executable
chmod +x SmartMaviManager
chmod +x run.sh

echo "✅ Installation complete!"
echo "🚀 Run './run.sh' to start Smart Mavi Manager"
EOF

chmod +x "$PACKAGE_DIR/install.sh"

# Create Linux binary package (tar.gz)
echo "🗜️ Creating binary package..."
tar -czf "SmartMaviManager-v1.0.0-linux.tar.gz" "$PACKAGE_DIR"

# Create source package with all source code
echo "📄 Creating source package..."
SOURCE_DIR="SmartMaviManager-v1.0.0-source"
rm -rf "$SOURCE_DIR"
mkdir -p "$SOURCE_DIR"

# Copy all source files
cp -r src include resources "$SOURCE_DIR/"
cp SmartMaviManager.pro CMakeLists.txt resources.qrc "$SOURCE_DIR/"
cp README.md run.sh package.sh "$SOURCE_DIR/"

tar -czf "SmartMaviManager-v1.0.0-source.tar.gz" "$SOURCE_DIR"

echo ""
echo "🎉 Packaging complete!"
echo "📦 Binary package: SmartMaviManager-v1.0.0-linux.tar.gz"
echo "📄 Source package: SmartMaviManager-v1.0.0-source.tar.gz"
echo ""
echo "📋 To distribute:"
echo "1. Send the binary package to end users"
echo "2. Users extract and run './install.sh'"
echo "3. Launch with './run.sh'"
