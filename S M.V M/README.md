# Smart MA.VI Manager

A comprehensive School Management System for Shree MA.VI Imilya, powered by Tech07.

## 🎯 Project Overview

Smart MA.VI Manager is a full-featured desktop application built with C++ and Qt that provides complete school management functionality including teacher management, student management, class management, attendance tracking, and comprehensive reporting.

## ✨ Features

### 👨‍🏫 Teacher Management
- Add, edit, delete teacher profiles
- Store teacher information (ID, Name, Subject, Contact, Assigned Class)
- Teacher attendance tracking
- Attendance history and reports

### 🏫 Class Management
- Create, edit, delete classes (Grade 1-12 or custom)
- Assign teachers to classes
- Link students to classes
- Class capacity management

### 👩‍🎓 Student Management
- Add, edit, delete students
- Store comprehensive student information (Roll No, Name, Guardian Info, Class)
- Mark student attendance (Present/Absent/Leave/Late)
- Bulk import/export via CSV/Excel

### 🗓️ Nepali Calendar Integration
- Built-in BS ↔ AD conversion
- Nepali + English calendar widget in GUI
- Mark holidays, events, exam schedules
- Attendance tied with Nepali Calendar

### 📊 Reports & Analytics
- Generate reports for teachers & students
- Export reports to CSV, Excel, or PDF
- Attendance percentage calculator
- Graphical dashboards for trends & performance

### ⚡ Admin Panel
- Secure admin login (username + password)
- Role-based access control:
  - Admin → Full access
  - Teacher → Attendance for their class only
  - Student/Guardian → View only
- Only admins can add/edit/delete data

### 🎨 Modern GUI
- Dashboard showing total students, teachers, classes, attendance summary
- Tabbed interface: Teachers, Students, Classes, Attendance, Reports, Calendar, Settings
- Modern design with light/dark mode support
- Search and filter functionality
- Notification system

## 🛠️ Technical Requirements

- **Language**: C++17 or later
- **GUI Framework**: Qt 6.x
- **Database**: SQLite (Qt SQL module)
- **Authentication**: Secure login with hashed passwords
- **Build System**: CMake 3.16+

## 📦 Dependencies

### Required Qt Modules
- Qt6::Core
- Qt6::Widgets
- Qt6::Sql
- Qt6::Network
- Qt6::Charts (for reports and analytics)

### System Requirements
- Linux (tested on Ubuntu 20.04+)
- Windows 10+ (with Qt 6.x)
- macOS 10.15+ (with Qt 6.x)

## 🚀 Building the Project

### Prerequisites
1. Install Qt 6.x development packages
2. Install CMake 3.16 or later
3. Install a C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

### Build Instructions

#### Linux
```bash
# Install dependencies
sudo apt update
sudo apt install qt6-base-dev qt6-charts-dev cmake build-essential

# Clone and build
git clone <repository-url>
cd SmartMAVIManager
mkdir build && cd build
cmake ..
make -j$(nproc)
```

#### Windows
```bash
# Using Qt Creator
1. Open Qt Creator
2. Open the CMakeLists.txt file
3. Configure the project with Qt 6.x
4. Build and run

# Using Command Line (with Qt 6.x installed)
mkdir build && cd build
cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build . --config Release
```

#### macOS
```bash
# Install dependencies
brew install qt6 cmake

# Build
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

## 🏃‍♂️ Running the Application

### First Run
1. The application will create a SQLite database automatically
2. Default admin credentials:
   - Username: `admin`
   - Password: `admin123`
3. **Important**: Change the default password after first login

### Normal Operation
```bash
# From build directory
./bin/SmartMAVIManager

# Or install and run from system
sudo make install
SmartMAVIManager
```

## 📁 Project Structure

```
SmartMAVIManager/
├── CMakeLists.txt              # Main build configuration
├── src/                        # Source files
│   ├── main.cpp               # Application entry point
│   ├── mainwindow.cpp         # Main window implementation
│   ├── models/                # Data models
│   │   ├── teacher.cpp
│   │   ├── student.cpp
│   │   ├── class.cpp
│   │   ├── attendance.cpp
│   │   └── nepalicalendar.cpp
│   ├── database/              # Database operations
│   │   └── database.cpp
│   ├── admin/                 # Admin functionality
│   │   └── adminpanel.cpp
│   ├── reports/               # Reporting system
│   │   └── reports.cpp
│   └── utils/                 # Utility classes
│       ├── csvhandler.cpp
│       └── passwordhash.cpp
├── include/                   # Header files
│   ├── mainwindow.h
│   ├── models/
│   ├── database/
│   ├── admin/
│   ├── reports/
│   └── utils/
├── ui/                        # UI files (Qt Designer)
├── resources/                 # Application resources
│   ├── icons/
│   ├── styles/
│   └── data/
└── data/                      # Database and data files
```

## 🔧 Configuration

### Database Configuration
- Database file: `~/.local/share/SmartMAVIManager/school.db`
- Automatic backup location: `~/.local/share/SmartMAVIManager/backup/`

### Settings
- Application settings: `~/.config/SmartMAVIManager/`
- Theme preferences, language settings, etc.

## 📊 Data Import/Export

### CSV Import
1. Use the provided CSV templates
2. Import students, teachers, classes, and attendance data
3. Validation ensures data integrity

### Export Options
- CSV format for spreadsheet applications
- PDF reports for printing
- Excel format (requires additional libraries)

## 🔐 Security Features

- Password hashing using SHA-256 with salt
- Role-based access control
- Session management
- Audit logging (admin panel)
- Secure database storage

## 🗓️ Nepali Calendar Features

- Complete BS to AD conversion (2000-2090 BS)
- Nepali month and day names
- Academic year management
- Holiday and event tracking
- Attendance integration

## 📈 Reporting System

### Available Reports
- Teacher attendance reports
- Student attendance reports
- Class performance reports
- Summary reports
- Custom date range reports

### Export Formats
- PDF (printable reports)
- CSV (spreadsheet analysis)
- HTML (web viewing)

## 🎨 User Interface

### Themes
- Light mode (default)
- Dark mode
- Customizable color schemes

### Responsive Design
- Adapts to different screen sizes
- Touch-friendly interface
- Keyboard shortcuts

## 🐛 Troubleshooting

### Common Issues

#### Build Errors
```bash
# Qt not found
export CMAKE_PREFIX_PATH=/path/to/qt6

# Missing dependencies
sudo apt install qt6-base-dev qt6-charts-dev
```

#### Runtime Errors
```bash
# Database permission issues
chmod 755 ~/.local/share/SmartMAVIManager/

# Missing Qt libraries
export LD_LIBRARY_PATH=/path/to/qt6/lib:$LD_LIBRARY_PATH
```

#### Performance Issues
- Ensure sufficient RAM (minimum 2GB)
- Close other applications during bulk operations
- Regular database maintenance

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## 📝 License

© 2024 Smart MA.VI Manager. All rights reserved.
Powered by Tech07.

## 📞 Support

For technical support or feature requests:
- Email: support@tech07.com
- Documentation: [Project Wiki]
- Issues: [GitHub Issues]

## 🔄 Version History

### v1.0.0 (Current)
- Initial release
- Complete school management functionality
- Nepali calendar integration
- Admin panel with role-based access
- Comprehensive reporting system
- Modern Qt-based GUI

---

**Note**: This is a comprehensive school management system designed specifically for Shree MA.VI Imilya. The system includes all requested features and is ready for production use.
