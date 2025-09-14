#include "simple_gui.h"
#include <QApplication>
#include <QGridLayout>
#include <QSpinBox>
#include <QMessageBox>
#include <QScrollArea>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPixmap>
#include <QIcon>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QTextDocument>
#include <map>
#include <algorithm>

SmartMaviGUI::SmartMaviGUI(QWidget *parent) : QMainWindow(parent), rng(std::random_device{}())
{
    // Initialize days and timeSlots (Middle Eastern schedule: Sunday-Friday, Saturday holiday)
    days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    timeSlots = {
        "08:00-08:45", "08:45-09:30", "09:30-10:15", "10:15-11:00",  // 4 periods before lunch
        "12:00-12:45",  // Lunch break placeholder
        "13:00-13:45", "13:45-14:30", "14:30-15:15"  // 3 periods after lunch
    };
    
    setupUI();
    setWindowTitle("🎓 Smart Mavi Manager - Professional Schedule Generator");
    setMinimumSize(900, 600);
    resize(1100, 700);
        
        // Set window icon if logo exists
        QPixmap logo("logo.png");
        if (!logo.isNull()) {
            setWindowIcon(QIcon(logo));
        }
        
        // Apply modern styling
        setStyleSheet(
            "QMainWindow {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "                               stop:0 #f8f9fa, stop:1 #e9ecef);"
            "}"
            "QTabWidget::pane {"
            "    border: 2px solid #3498db;"
            "    border-radius: 8px;"
            "    background: white;"
            "}"
            "QTabBar::tab {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "                               stop:0 #ecf0f1, stop:1 #d5dbdb);"
            "    border: 2px solid #bdc3c7;"
            "    padding: 8px 16px;"
            "    margin-right: 2px;"
            "    border-top-left-radius: 8px;"
            "    border-top-right-radius: 8px;"
            "}"
            "QTabBar::tab:selected {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "                               stop:0 #3498db, stop:1 #2980b9);"
            "    color: white;"
            "    font-weight: bold;"
            "}"
            "QPushButton {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "                               stop:0 #3498db, stop:1 #2980b9);"
            "    color: white;"
            "    border: none;"
            "    padding: 8px 16px;"
            "    border-radius: 6px;"
            "    font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "                               stop:0 #5dade2, stop:1 #3498db);"
            "}"
            "QPushButton:pressed {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "                               stop:0 #2980b9, stop:1 #1f618d);"
            "}"
            "QLineEdit {"
            "    border: 2px solid #bdc3c7;"
            "    border-radius: 6px;"
            "    padding: 6px;"
            "    font-size: 14px;"
            "}"
            "QLineEdit:focus {"
            "    border-color: #3498db;"
            "}"
            "QTextEdit {"
            "    border: 2px solid #bdc3c7;"
            "    border-radius: 6px;"
            "    background: white;"
            "    font-family: 'Courier New', monospace;"
            "}"
            "QGroupBox {"
            "    font-weight: bold;"
            "    border: 2px solid #3498db;"
            "    border-radius: 8px;"
            "    margin-top: 10px;"
            "    padding-top: 10px;"
            "}"
            "QGroupBox::title {"
            "    color: #2c3e50;"
            "    subcontrol-origin: margin;"
            "    left: 10px;"
            "    padding: 0 5px 0 5px;"
            "}"
            "QTableWidget {"
            "    border: 2px solid #3498db;"
            "    border-radius: 8px;"
            "    background: white;"
            "    gridline-color: #bdc3c7;"
            "    alternate-background-color: #f8f9fa;"
            "}"
            "QTableWidget::item {"
            "    padding: 8px;"
            "    border-bottom: 1px solid #ecf0f1;"
            "}"
            "QTableWidget::item:selected {"
            "    background: #3498db;"
            "    color: white;"
            "}"
            "QHeaderView::section {"
            "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "                               stop:0 #3498db, stop:1 #2980b9);"
            "    color: white;"
            "    padding: 8px;"
            "    border: 1px solid #2980b9;"
            "    font-weight: bold;"
            "}"
        );
}

void SmartMaviGUI::addTeacher()
    {
        QString name = teacherNameEdit->text().trimmed();
        if (name.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a teacher name!");
            return;
        }
        
        Teacher teacher;
        teacher.name = name.toStdString();
        teacher.id = teachers.size() + 1;
        teachers.push_back(teacher);
        
        updateTeachersList();
        teacherNameEdit->clear();
        teacherNameEdit->setFocus();
        
        statusBar()->showMessage("✅ Teacher added: " + name, 2000);
    }

void SmartMaviGUI::addSubject()
    {
        QString name = subjectNameEdit->text().trimmed();
        if (name.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a subject name!");
            return;
        }
        
        Subject subject;
        subject.name = name.toStdString();
        subject.id = subjects.size() + 1;
        subjects.push_back(subject);
        
        updateSubjectsList();
        subjectNameEdit->clear();
        subjectNameEdit->setFocus();
        
        statusBar()->showMessage("✅ Subject added: " + name, 2000);
    }

void SmartMaviGUI::addClass()
    {
        QString name = classNameEdit->text().trimmed();
        QString grade = classGradeEdit->text().trimmed();
        if (name.isEmpty() || grade.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Please enter both class name and grade!");
            return;
        }
        
        Class cls;
        cls.name = name.toStdString();
        cls.grade = grade.toStdString();
        cls.id = classes.size() + 1;
        classes.push_back(cls);
        
        updateClassesList();
        classNameEdit->clear();
        classGradeEdit->clear();
        classNameEdit->setFocus();
        
        statusBar()->showMessage("✅ Class added: " + name + " (Grade " + grade + ")", 2000);
    }

void SmartMaviGUI::generateSchedule()
    {
        if (teachers.empty() || subjects.empty() || classes.empty()) {
            QMessageBox::warning(this, "Incomplete Data", 
                "Please add at least one teacher, subject, and class before generating a schedule!");
            return;
        }
        
        // Assign subjects to teachers randomly
        for (auto& teacher : teachers) {
            teacher.subjects.clear();
            int numSubjects = std::uniform_int_distribution<int>(1, std::min(3, (int)subjects.size()))(rng);
            
            std::vector<int> subjectIndices;
            for (int i = 0; i < subjects.size(); i++) {
                subjectIndices.push_back(i);
            }
            std::shuffle(subjectIndices.begin(), subjectIndices.end(), rng);
            
            for (int i = 0; i < numSubjects; i++) {
                teacher.subjects.push_back(subjects[subjectIndices[i]].name);
            }
        }
        
        // Generate schedule
        schedule.clear();
        
        for (const auto& day : days) {
            for (const auto& slot : timeSlots) {
                for (const auto& cls : classes) {
                    // Skip lunch break
                    if (slot == "12:00-12:45") continue;
                    
                    // Randomly select teacher and subject
                    if (!teachers.empty()) {
                        auto& teacher = teachers[std::uniform_int_distribution<int>(0, teachers.size()-1)(rng)];
                        if (!teacher.subjects.empty()) {
                            std::string subject = teacher.subjects[std::uniform_int_distribution<int>(0, teacher.subjects.size()-1)(rng)];
                            
                            ScheduleEntry entry;
                            entry.day = day;
                            entry.timeSlot = slot;
                            entry.teacher = teacher.name;
                            entry.subject = subject;
                            entry.className = cls.name + " (" + cls.grade + ")";
                            schedule.push_back(entry);
                        }
                    }
                }
            }
        }
        
        displaySchedule();
        tabWidget->setCurrentIndex(1); // Switch to schedule tab
        
        QMessageBox::information(this, "Success! 🎉", 
            QString("🎊 Your schedule has been generated successfully!\\n\\n"
                   "📊 Generated %1 schedule entries\\n"
                   "🎲 Click 'Generate New Schedule' for a different arrangement!")
                   .arg(schedule.size()));
    }

void SmartMaviGUI::exportToPDF()
    {
        if (schedule.empty()) {
            QMessageBox::warning(this, "No Schedule", "Please generate a schedule first!");
            return;
        }
        
        QString fileName = QFileDialog::getSaveFileName(this, 
            "Export Schedule to PDF", 
            "SmartMavi_Schedule.pdf", 
            "PDF Files (*.pdf)");
        
        if (fileName.isEmpty()) return;
        
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
        
        QTextDocument document;
        
        QString html = "<html><body>";
        html += "<h1 style='text-align: center; color: #3498db;'>🎓 Smart Mavi Manager - School Schedule</h1>";
        html += "<hr style='border: 2px solid #3498db;'>";
        
        // Create schedule by day
        for (const auto& day : days) {
            html += "<h2 style='color: #2c3e50; background: #ecf0f1; padding: 10px; border-radius: 5px;'>" + QString::fromStdString(day) + "</h2>";
            html += "<table border='1' style='border-collapse: collapse; width: 100%; margin-bottom: 20px;'>";
            html += "<tr style='background: #3498db; color: white;'><th>Time</th><th>Teacher</th><th>Subject</th><th>Class</th></tr>";
            
            for (const auto& slot : timeSlots) {
                if (slot == "12:00-12:45") {
                    html += "<tr style='background: #f39c12; color: white;'><td><strong>" + QString::fromStdString(slot) + "</strong></td><td colspan='3' style='text-align: center;'><strong>🍽️ LUNCH BREAK</strong></td></tr>";
                    continue;
                }
                
                for (const auto& entry : schedule) {
                    if (entry.day == day && entry.timeSlot == slot) {
                        html += "<tr>";
                        html += "<td>" + QString::fromStdString(entry.timeSlot) + "</td>";
                        html += "<td>" + QString::fromStdString(entry.teacher) + "</td>";
                        html += "<td>" + QString::fromStdString(entry.subject) + "</td>";
                        html += "<td>" + QString::fromStdString(entry.className) + "</td>";
                        html += "</tr>";
                        break;
                    }
                }
            }
            html += "</table>";
        }
        
        html += "<hr style='border: 1px solid #bdc3c7;'>";
        html += "<p style='text-align: center; color: #7f8c8d;'>";
        html += "Generated by Smart Mavi Manager v2.0.0 • Professional Schedule Generator<br>";
        html += "© 2025 Smart Mavi Solutions";
        html += "</p>";
        html += "</body></html>";
        
        document.setHtml(html);
        document.print(&printer);
        
        QMessageBox::information(this, "Export Complete", 
            "📄 Schedule exported to PDF successfully!\\n\\nFile: " + fileName);
    }

void SmartMaviGUI::showAbout()
    {
        QMessageBox aboutBox(this);
        aboutBox.setWindowTitle("About Smart Mavi Manager");
        
        // Set logo if available
        QPixmap logo("logo.png");
        if (!logo.isNull()) {
            aboutBox.setIconPixmap(logo.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        
        aboutBox.setText(
            "<h2>🎓 Smart Mavi Manager</h2>"
            "<p><b>Version 1.0.0 - GUI Edition</b></p>"
        );
        
        aboutBox.setInformativeText(
            "<p>🚀 <b>Professional Schedule Generator</b></p>"
            "<p>Smart Mavi Manager is an intelligent scheduling application that creates "
            "optimized, randomized schedules for educational institutions.</p>"
            "<br>"
            "<p><b>✨ Key Features:</b></p>"
            "<ul>"
            "<li>🎲 Advanced randomization algorithms</li>"
            "<li>👨‍🏫 Smart teacher and subject management</li>"
            "<li>🏫 Class scheduling with grade levels</li>"
            "<li>📄 Professional PDF export</li>"
            "<li>🎨 Beautiful, user-friendly interface</li>"
            "</ul>"
            "<br>"
            "<p style='color: #7f8c8d;'>"
            "Built with ❤️ using C++ and Qt5<br>"
            "© 2025 Smart Mavi Manager"
            "</p>"
        );
        
        aboutBox.setStandardButtons(QMessageBox::Ok);
        aboutBox.exec();
    }

void SmartMaviGUI::setupUI()
    {
        // Create central widget and tab widget
        QWidget *centralWidget = new QWidget;
        setCentralWidget(centralWidget);
        
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        
        // Add welcome header
        QLabel *headerLabel = new QLabel("🎓 <b>Smart Mavi Manager</b> - Professional Schedule Generator");
        headerLabel->setAlignment(Qt::AlignCenter);
        headerLabel->setStyleSheet("font-size: 18px; color: #2c3e50; padding: 10px; background: rgba(52, 152, 219, 0.1); border-radius: 8px; margin: 10px;");
        mainLayout->addWidget(headerLabel);
        
        tabWidget = new QTabWidget;
        mainLayout->addWidget(tabWidget);
        
        setupSetupTab();
        setupScheduleTab();
        
        // Create menu bar
        QMenuBar *menuBar = this->menuBar();
        QMenu *fileMenu = menuBar->addMenu("📁 File");
        QMenu *helpMenu = menuBar->addMenu("❓ Help");
        
        QAction *exportAction = fileMenu->addAction("📄 Export to PDF");
        connect(exportAction, &QAction::triggered, this, &SmartMaviGUI::exportToPDF);
        
        fileMenu->addSeparator();
        QAction *exitAction = fileMenu->addAction("🚪 Exit");
        connect(exitAction, &QAction::triggered, this, &QWidget::close);
        
        QAction *aboutAction = helpMenu->addAction("ℹ️ About");
        connect(aboutAction, &QAction::triggered, this, &SmartMaviGUI::showAbout);
        
        // Create status bar
        statusBar()->showMessage("Ready to create amazing schedules! 🚀");
    }

void SmartMaviGUI::setupSetupTab()
    {
        setupTab = new QWidget;
        tabWidget->addTab(setupTab, "🔧 Setup");
        
        QHBoxLayout *setupLayout = new QHBoxLayout(setupTab);
        
        // Left side - Input forms
        QWidget *inputWidget = new QWidget;
        QVBoxLayout *inputLayout = new QVBoxLayout(inputWidget);
        
        // Teachers section
        QGroupBox *teachersGroup = new QGroupBox("👥 Teachers");
        QVBoxLayout *teachersLayout = new QVBoxLayout(teachersGroup);
        
        QHBoxLayout *teacherInputLayout = new QHBoxLayout;
        teacherNameEdit = new QLineEdit;
        teacherNameEdit->setPlaceholderText("Enter teacher name (e.g., Mr. Smith)");
        QPushButton *addTeacherBtn = new QPushButton("➕ Add Teacher");
        connect(addTeacherBtn, &QPushButton::clicked, this, &SmartMaviGUI::addTeacher);
        connect(teacherNameEdit, &QLineEdit::returnPressed, this, &SmartMaviGUI::addTeacher);
        
        teacherInputLayout->addWidget(teacherNameEdit);
        teacherInputLayout->addWidget(addTeacherBtn);
        teachersLayout->addLayout(teacherInputLayout);
        
        // Subjects section
        QGroupBox *subjectsGroup = new QGroupBox("📚 Subjects");
        QVBoxLayout *subjectsLayout = new QVBoxLayout(subjectsGroup);
        
        QHBoxLayout *subjectInputLayout = new QHBoxLayout;
        subjectNameEdit = new QLineEdit;
        subjectNameEdit->setPlaceholderText("Enter subject name (e.g., Mathematics)");
        QPushButton *addSubjectBtn = new QPushButton("➕ Add Subject");
        connect(addSubjectBtn, &QPushButton::clicked, this, &SmartMaviGUI::addSubject);
        connect(subjectNameEdit, &QLineEdit::returnPressed, this, &SmartMaviGUI::addSubject);
        
        subjectInputLayout->addWidget(subjectNameEdit);
        subjectInputLayout->addWidget(addSubjectBtn);
        subjectsLayout->addLayout(subjectInputLayout);
        
        // Classes section
        QGroupBox *classesGroup = new QGroupBox("🏫 Classes");
        QVBoxLayout *classesLayout = new QVBoxLayout(classesGroup);
        
        QHBoxLayout *classInputLayout = new QHBoxLayout;
        classNameEdit = new QLineEdit;
        classNameEdit->setPlaceholderText("Class name (e.g., Class A)");
        classGradeEdit = new QLineEdit;
        classGradeEdit->setPlaceholderText("Grade (e.g., 5)");
        QPushButton *addClassBtn = new QPushButton("➕ Add Class");
        connect(addClassBtn, &QPushButton::clicked, this, &SmartMaviGUI::addClass);
        connect(classGradeEdit, &QLineEdit::returnPressed, this, &SmartMaviGUI::addClass);
        
        classInputLayout->addWidget(classNameEdit);
        classInputLayout->addWidget(classGradeEdit);
        classInputLayout->addWidget(addClassBtn);
        classesLayout->addLayout(classInputLayout);
        
        inputLayout->addWidget(teachersGroup);
        inputLayout->addWidget(subjectsGroup);
        inputLayout->addWidget(classesGroup);
        
        // Generate button
        QPushButton *generateBtn = new QPushButton("🎲 Generate Schedule");
        generateBtn->setStyleSheet("font-size: 16px; padding: 12px; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #27ae60, stop:1 #229954);");
        connect(generateBtn, &QPushButton::clicked, this, &SmartMaviGUI::generateSchedule);
        inputLayout->addWidget(generateBtn);
        
        inputLayout->addStretch();
        
        // Right side - Lists
        QWidget *listsWidget = new QWidget;
        QVBoxLayout *listsLayout = new QVBoxLayout(listsWidget);
        
        QGroupBox *teachersListGroup = new QGroupBox("👥 Current Teachers");
        QVBoxLayout *teachersListLayout = new QVBoxLayout(teachersListGroup);
        teachersListText = new QTextEdit;
        teachersListText->setReadOnly(true);
        teachersListText->setMaximumHeight(150);
        teachersListLayout->addWidget(teachersListText);
        
        QGroupBox *subjectsListGroup = new QGroupBox("📚 Current Subjects");
        QVBoxLayout *subjectsListLayout = new QVBoxLayout(subjectsListGroup);
        subjectsListText = new QTextEdit;
        subjectsListText->setReadOnly(true);
        subjectsListText->setMaximumHeight(150);
        subjectsListLayout->addWidget(subjectsListText);
        
        QGroupBox *classesListGroup = new QGroupBox("🏫 Current Classes");
        QVBoxLayout *classesListLayout = new QVBoxLayout(classesListGroup);
        classesListText = new QTextEdit;
        classesListText->setReadOnly(true);
        classesListText->setMaximumHeight(150);
        classesListLayout->addWidget(classesListText);
        
        listsLayout->addWidget(teachersListGroup);
        listsLayout->addWidget(subjectsListGroup);
        listsLayout->addWidget(classesListGroup);
        
        setupLayout->addWidget(inputWidget, 1);
        setupLayout->addWidget(listsWidget, 1);
    }

void SmartMaviGUI::setupScheduleTab()
    {
        scheduleTab = new QWidget;
        tabWidget->addTab(scheduleTab, "📅 Schedule");
        
        QVBoxLayout *scheduleLayout = new QVBoxLayout(scheduleTab);
        
        // Controls
        QHBoxLayout *controlsLayout = new QHBoxLayout;
        QPushButton *regenerateBtn = new QPushButton("🎲 Generate New Schedule");
        QPushButton *exportBtn = new QPushButton("📄 Export to PDF");
        
        connect(regenerateBtn, &QPushButton::clicked, this, &SmartMaviGUI::generateSchedule);
        connect(exportBtn, &QPushButton::clicked, this, &SmartMaviGUI::exportToPDF);
        
        controlsLayout->addWidget(regenerateBtn);
        controlsLayout->addWidget(exportBtn);
        controlsLayout->addStretch();
        
        scheduleLayout->addLayout(controlsLayout);
        
        // Schedule table
        scheduleTable = new QTableWidget;
        scheduleLayout->addWidget(scheduleTable);
    }

void SmartMaviGUI::updateTeachersList()
    {
        QString text = "";
        for (size_t i = 0; i < teachers.size(); ++i) {
            text += QString("• %1").arg(QString::fromStdString(teachers[i].name));
            if (!teachers[i].subjects.empty()) {
                text += " (Teaches: ";
                for (size_t j = 0; j < teachers[i].subjects.size(); ++j) {
                    text += QString::fromStdString(teachers[i].subjects[j]);
                    if (j < teachers[i].subjects.size() - 1) text += ", ";
                }
                text += ")";
            }
            text += "\\n";
        }
        teachersListText->setPlainText(text);
    }

void SmartMaviGUI::updateSubjectsList()
    {
        QString text = "";
        for (const auto& subject : subjects) {
            text += QString("• %1\\n").arg(QString::fromStdString(subject.name));
        }
        subjectsListText->setPlainText(text);
    }

void SmartMaviGUI::updateClassesList()
    {
        QString text = "";
        for (const auto& cls : classes) {
            text += QString("• %1 (Grade %2)\\n")
                    .arg(QString::fromStdString(cls.name))
                    .arg(QString::fromStdString(cls.grade));
        }
        classesListText->setPlainText(text);
    }

void SmartMaviGUI::displaySchedule()
    {
        scheduleTable->clear();
        scheduleTable->setRowCount(0);
        
        if (schedule.empty()) {
            scheduleTable->setColumnCount(1);
            scheduleTable->setHorizontalHeaderLabels({"No Schedule Generated"});
            return;
        }
        
        scheduleTable->setColumnCount(5);
        scheduleTable->setHorizontalHeaderLabels({"Day", "Time", "Teacher", "Subject", "Class"});
        
        scheduleTable->setRowCount(schedule.size());
        
        for (size_t i = 0; i < schedule.size(); ++i) {
            scheduleTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(schedule[i].day)));
            scheduleTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(schedule[i].timeSlot)));
            scheduleTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(schedule[i].teacher)));
            scheduleTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(schedule[i].subject)));
            scheduleTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(schedule[i].className)));
        }
        
        // Auto-resize columns
        scheduleTable->resizeColumnsToContents();
        scheduleTable->horizontalHeader()->setStretchLastSection(true);
    }

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Smart Mavi Manager");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Smart Mavi Solutions");
    app.setApplicationDisplayName("Smart Mavi Manager 📚");
    
    // Set application icon
    QPixmap logoPixmap("logo.png");
    if (!logoPixmap.isNull()) {
        app.setWindowIcon(QIcon(logoPixmap));
    }
    
    SmartMaviGUI window;
    window.show();
    
    return app.exec();
}

