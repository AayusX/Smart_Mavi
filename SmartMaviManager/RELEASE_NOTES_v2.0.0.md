# 🎉 Smart Mavi Manager v2.0.0 - Release Notes

**Professional Schedule Generator - Major Update**  
*Released: September 11, 2025*

## 🌟 What's New in v2.0.0

### 🕌 **Middle Eastern Schedule Format**
- **Week Structure**: Sunday to Friday (Saturday holiday)
- **Pre-Lunch**: 4 periods (08:00-11:00)
  - 08:00-08:45
  - 08:45-09:30  
  - 09:30-10:15
  - 10:15-11:00
- **Lunch Break**: 12:00-12:45
- **Post-Lunch**: 3 periods (13:00-15:15)
  - 13:00-13:45
  - 13:45-14:30
  - 14:30-15:15

### 📅 **Updated Copyright & Branding**
- Updated to 2025 copyright
- Enhanced professional branding
- Improved version information

### 📦 **Professional Distribution Packages**

#### 🐧 **Linux (.deb Package)**
- **File**: `smart-mavi-manager_2.0.0_amd64.deb` (1.0MB)
- **Installation**: `sudo dpkg -i smart-mavi-manager_2.0.0_amd64.deb`
- **Features**:
  - Automatic Qt5 dependency resolution
  - Desktop integration with menu entry
  - Application icon in system menu
  - Post-installation desktop database updates

#### 🪟 **Windows (.exe Installer)**
- **File**: `SmartMaviManager_v2.0.0_Setup.exe` (ready for build)
- **Features**:
  - Professional NSIS installer
  - Bundled Qt5 runtime libraries
  - Desktop and Start Menu shortcuts
  - Windows registry integration
  - Automatic uninstaller
  - Upgrade detection and handling

## 🔧 **Technical Improvements**

### **Enhanced Schedule Engine**
- Middle Eastern educational system compliance
- Improved lunch break handling
- Better time slot organization
- Saturday holiday recognition

### **Professional Packaging**
- Debian package with proper metadata
- Windows installer with dependency bundling
- Desktop integration for both platforms
- Professional licensing and branding

### **Code Quality**
- Updated Qt5 compatibility
- Improved error handling
- Enhanced PDF export with new schedule format
- Better user experience

## 🚀 **Installation Instructions**

### **Linux (Debian/Ubuntu)**
```bash
# Download the .deb package
wget https://releases.smartmavi.com/smart-mavi-manager_2.0.0_amd64.deb

# Install with dependencies
sudo dpkg -i smart-mavi-manager_2.0.0_amd64.deb
sudo apt-get install -f  # Fix any dependency issues

# Launch from Applications menu or terminal
smart-mavi-manager
```

### **Windows**
1. Download `SmartMaviManager_v2.0.0_Setup.exe`
2. Run as Administrator
3. Follow installation wizard
4. Launch from Desktop or Start Menu

## 🎯 **Key Features**

### **Multi-Interface Support**
- **GUI**: Beautiful Qt5 graphical interface
- **Console**: Professional terminal-based interface  
- **CLI**: Lightweight command-line tool

### **Schedule Generation**
- **Smart Randomization**: Conflict-free scheduling
- **Teacher Management**: Subject assignments and workload balancing
- **Class Organization**: Grade-based class management
- **PDF Export**: Professional document generation

### **Regional Compliance**
- **Middle Eastern Schedule**: Sunday-Friday academic week
- **Prayer Time Compatibility**: Proper break scheduling
- **Cultural Sensitivity**: Saturday holiday recognition

## 📊 **System Requirements**

### **Linux**
- Ubuntu 18.04+ or Debian 10+
- Qt5 libraries (auto-installed)
- 50MB disk space
- 512MB RAM

### **Windows**
- Windows 10/11
- 100MB disk space
- 1GB RAM
- Visual C++ Runtime (bundled)

## 🛠️ **For Developers**

### **Building from Source**
```bash
# Linux
qmake SimpleGUI.pro
make

# Cross-compile for Windows
x86_64-w64-mingw32-qmake-qt5 SimpleGUI.pro
make
```

### **Creating Packages**
```bash
# Build .deb package
dpkg-deb --build packaging/deb/smart-mavi-manager

# Build Windows installer (requires NSIS)
makensis packaging/windows/SmartMaviManager_Installer.nsi
```

## 🎊 **Migration from v1.0.0**

### **Automatic Updates**
- Linux: Package manager handles updates
- Windows: Installer detects and upgrades existing installation

### **Data Compatibility**
- All existing schedules remain compatible
- New time format automatically applied
- No data loss during upgrade

## 🆘 **Support & Documentation**

- **Installation Guide**: `README_GUI.md`
- **User Manual**: Built-in help system
- **Technical Support**: Available through package maintainer
- **Source Code**: Available for educational institutions

## 🏆 **Credits**

**Smart Mavi Manager v2.0.0**  
Professional Schedule Generator for Educational Institutions

*Developed with ❤️ for the global education community*  
*© 2025 Smart Mavi Solutions*

---

**🎓 Transform your school scheduling with Smart Mavi Manager v2.0.0!**  
*Professional • Reliable • Easy to Use*
