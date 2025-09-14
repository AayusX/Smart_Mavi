#!/bin/bash

# 🎓 Smart Mavi Manager - GUI Launcher
echo "🎓 Starting Smart Mavi Manager GUI..."
echo "📚 Professional Schedule Generator - GUI Edition"
echo ""

# Set working directory to script location
cd "$(dirname "$0")"

# Check if GUI executable exists
if [ ! -f "./SmartMaviGUI" ]; then
    echo "❌ SmartMaviGUI executable not found!"
    echo "Building the GUI application..."
    qmake SimpleGUI.pro && make
    if [ $? -ne 0 ]; then
        echo "❌ Failed to build the GUI application."
        echo "Please run: qmake SimpleGUI.pro && make"
        exit 1
    fi
fi

# Check if logo exists
if [ ! -f "./logo.png" ]; then
    echo "⚠️  Logo file not found, copying from resources..."
    if [ -f "./resources/logo.png" ]; then
        cp ./resources/logo.png ./
    else
        echo "⚠️  Logo file missing, but application will still work."
    fi
fi

echo "🚀 Launching Smart Mavi Manager GUI..."
./SmartMaviGUI

echo "👋 Thank you for using Smart Mavi Manager GUI!"
