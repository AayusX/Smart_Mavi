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
