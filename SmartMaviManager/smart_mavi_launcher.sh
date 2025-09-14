#!/bin/bash

# 🎓 Smart Mavi Manager - Universal Launcher
clear

echo "🎓 =================================="
echo "    SMART MAVI MANAGER v1.0.0"
echo "    Professional Schedule Generator"
echo "🎓 =================================="
echo ""
echo "Choose your preferred interface:"
echo ""
echo "🖥️  [1] GUI Version (Graphical Interface)"
echo "💼 [2] Professional Console"
echo "📱 [3] Interactive CLI"
echo "❌ [4] Exit"
echo ""
echo -n "Enter your choice (1-4): "

read choice

case $choice in
    1)
        echo ""
        echo "🚀 Launching GUI version..."
        ./launch_gui.sh
        ;;
    2)
        echo ""
        echo "💼 Launching Professional Console version..."
        ./professional_app
        ;;
    3)
        echo ""
        echo "📱 Launching Interactive CLI version..."
        ./interactive_cli
        ;;
    4)
        echo ""
        echo "👋 Thank you for using Smart Mavi Manager!"
        exit 0
        ;;
    *)
        echo ""
        echo "❌ Invalid choice. Please select 1-4."
        echo "Defaulting to GUI version..."
        echo ""
        ./launch_gui.sh
        ;;
esac
