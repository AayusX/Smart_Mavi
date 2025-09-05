# 🎓 Smart Mavi Manager

**Professional Schedule Generator for Educational Institutions**

## 🌟 Features

✨ **Intelligent Randomization** - Advanced algorithms for optimal schedule generation  
👨‍🏫 **Teacher Management** - Assign subjects to teachers with workload balancing  
🏫 **Class Scheduling** - Smart time slot allocation with conflict prevention  
📊 **Professional Reports** - Beautiful, printable schedules with multiple views  
🎯 **User-Friendly Interface** - Fun, interactive survey system  
📄 **Multiple Export Formats** - PDF, CSV export with professional formatting  
⏰ **Flexible Timing** - Customizable periods, breaks, and lunch times  
🎲 **True Randomization** - Each generation creates unique schedule arrangements  

## 🚀 Getting Started

### Prerequisites
- Qt5 development libraries
- C++17 compatible compiler
- Linux/Unix environment

### Installation & Building

1. **Clone or extract the project**
   ```bash
   cd SmartMaviManager
   ```

2. **Build the application**
   ```bash
   qmake SmartMaviManager.pro
   make
   ```

3. **Run the application**
   ```bash
   ./run.sh
   ```
   Or directly:
   ```bash
   ./SmartMaviManager
   ```

## 📋 How to Use

### 1. 🏁 Start the Setup Wizard
- Click "File > New Schedule" or use Ctrl+N
- The fun, animated survey will guide you through setup

### 2. 📊 Provide Basic Information
- Enter number of teachers, subjects, and classes
- All fields have helpful hints and emojis!

### 3. 👨‍🏫 Add Your Teachers
- Enter teacher names one by one
- Use fun, descriptive names like "Mr. Smith" or "Ms. Johnson"

### 4. 📚 Define Subjects
- Add all subjects taught in your school
- Examples: Mathematics, Science, History, Art, etc.

### 5. 🏫 Create Classes
- Define class names and grade levels
- Examples: "Class A (Grade 5)", "Class B (Grade 10)"

### 6. 🔗 Assign Subjects to Teachers
- Match teachers with their expertise
- Each teacher can teach multiple subjects
- Visual drag-and-drop style interface

### 7. ⏰ Configure Time Settings
- Set school hours (start/end times)
- Define period duration
- Schedule break and lunch times
- Set workload limits

### 8. 🎊 Generate Your Schedule!
- Watch the magic happen with progress animation
- Get a fully randomized, conflict-free schedule

## 🎯 Advanced Features

### 📅 Multiple View Types
- **Full Schedule**: Complete overview of all classes and teachers
- **By Class**: Individual class schedules with assigned teachers
- **By Teacher**: Teacher schedules showing their class assignments

### 🖨️ Professional Printing
- **Print Preview**: See exactly how your schedule will look
- **Direct Printing**: Send to any connected printer
- **PDF Export**: Professional PDF documents for sharing
- **CSV Export**: Spreadsheet-compatible data export

### 🎲 Smart Randomization
- **Conflict Prevention**: No teacher double-booking
- **Workload Balancing**: Fair distribution of periods per teacher
- **Multiple Generations**: Click regenerate for different arrangements
- **Quality Optimization**: Algorithm ensures optimal schedule quality

## 🛠️ Technical Details

### Built With
- **C++17**: Modern C++ with Qt5 framework
- **Qt5 Widgets**: Professional cross-platform GUI
- **Qt5 PrintSupport**: Advanced printing and PDF export
- **Custom Algorithm**: Proprietary randomized scheduling engine

### Architecture
```
SmartMaviManager/
├── src/                 # Source code
├── include/             # Header files  
├── resources/           # Logo and assets
├── SmartMaviManager     # Compiled executable
├── run.sh              # Launch script
└── README.md           # This file
```

### Core Components
- **SurveyDialog**: Interactive setup wizard with animations
- **ScheduleGenerator**: Randomized algorithm with constraint solving
- **ScheduleView**: Professional table display with export options
- **MainWindow**: Central application hub with modern styling

## 🎨 Design Philosophy

Smart Mavi Manager combines professional functionality with delightful user experience:

- **Fun & Engaging**: Emoji-rich interface makes data entry enjoyable
- **Professional Output**: Clean, printable schedules suitable for any institution
- **Intelligent**: Advanced algorithms prevent conflicts automatically  
- **Flexible**: Highly customizable to fit any school's needs
- **Reliable**: Robust error handling and validation

## 🔧 Troubleshooting

### Common Issues

**Application won't start**
- Ensure Qt5 libraries are installed: `sudo apt install qtbase5-dev`
- Check logo.png exists in the application directory

**Schedule generation fails**
- Verify all teachers have assigned subjects
- Ensure realistic time constraints (enough periods for all subjects)
- Try reducing number of classes or subjects if schedule is too complex

**Printing issues**
- Ensure printer drivers are installed
- Try PDF export as alternative
- Check system print services are running

## 📈 Future Enhancements

- 💾 Save/Load schedule configurations
- 🌐 Multi-language support
- 📱 Mobile companion app
- 🔄 Import from existing systems
- 🎯 Advanced constraint customization
- 📊 Schedule analytics and optimization metrics

## 🏆 Version History

**v1.0.0** - Initial Release
- Complete schedule generation system
- Interactive survey with 7-step wizard
- Professional table views and printing
- PDF and CSV export functionality
- Modern, animated user interface
- Comprehensive conflict resolution

## 📞 Support

For support, feedback, or feature requests, the Smart Mavi Manager provides:
- Built-in help system (Help > User Guide)
- Comprehensive tooltips and hints
- Error messages with clear guidance
- Professional documentation

## 📜 License

Smart Mavi Manager - Professional Schedule Generator  
© 2024 Smart Mavi Solutions

---

**🎊 Congratulations! You now have a professional, randomized schedule generator that's both powerful and fun to use!**

**🚀 Ready to revolutionize your school's scheduling? Launch Smart Mavi Manager and experience the magic!**
