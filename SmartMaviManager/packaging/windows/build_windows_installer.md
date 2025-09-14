# Windows .exe Installer Build Instructions

## Prerequisites
1. **Windows Development Environment**
2. **Qt5 for Windows** (with MinGW or MSVC compiler)
3. **NSIS** (Nullsoft Scriptable Install System)

## Build Steps

### 1. Cross-compile for Windows (on Linux)
```bash
# Install MinGW cross-compiler
sudo apt install mingw-w64 g++-mingw-w64

# Install Qt5 for MinGW
sudo apt install qt5-qmake-mingw-w64

# Cross-compile the application
x86_64-w64-mingw32-qmake-qt5 SimpleGUI.pro
make
```

### 2. Gather Qt5 Runtime DLLs
Copy these files from Qt5 installation:
```
Qt5Core.dll
Qt5Gui.dll
Qt5Widgets.dll
Qt5PrintSupport.dll
platforms/qwindows.dll
```

### 3. Bundle Visual C++ Runtime (if needed)
```
msvcp140.dll
vcruntime140.dll
```

### 4. Build Windows Installer
```bash
# Install NSIS
# On Windows: Download from https://nsis.sourceforge.io/
# On Linux: sudo apt install nsis

# Compile installer
makensis SmartMaviManager_Installer.nsi
```

## Output
- `SmartMaviManager_v2.0.0_Setup.exe` - Windows installer

## Features
- ✅ Automatic Qt5 dependency installation
- ✅ Desktop and Start Menu shortcuts
- ✅ Windows registry integration
- ✅ Uninstaller included
- ✅ Upgrade detection
- ✅ Professional installer UI

## Installation for Users
1. Download `SmartMaviManager_v2.0.0_Setup.exe`
2. Run as Administrator
3. Follow installation wizard
4. Launch from Desktop or Start Menu

The installer will handle all dependencies automatically!
