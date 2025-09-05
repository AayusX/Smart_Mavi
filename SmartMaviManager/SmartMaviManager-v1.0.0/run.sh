#!/bin/bash

# Smart Mavi Manager Launch Script
echo "🎓 Starting Smart Mavi Manager..."
echo "📚 Professional Schedule Generator"
echo ""

# Set working directory to script location
cd "$(dirname "$0")"

# Check if executable exists
if [ ! -f "./SmartMaviManager" ]; then
    echo "❌ SmartMaviManager executable not found!"
    echo "Please run 'qmake SmartMaviManager.pro && make' to build the application."
    exit 1
fi

# Check if logo exists
if [ ! -f "./logo.png" ]; then
    echo "⚠️  Logo file not found, copying from resources..."
    if [ -f "./resources/logo.png" ]; then
        cp ./resources/logo.png ./
    else
        echo "❌ Logo file missing! Please ensure logo.png is in the resources folder."
    fi
fi

echo "🚀 Launching Smart Mavi Manager..."
./SmartMaviManager

echo "👋 Thank you for using Smart Mavi Manager!"
