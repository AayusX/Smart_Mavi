#include "mainwindow.h"
#include "database/database.h"
#include "admin/adminpanel.h"
// #include "reports/reports.h"
#include "models/nepalicalendar.h"
#include "utils/csvhandler.h"
#include "utils/passwordhash.h"
#include "dialogs/teacherdialog.h"
#include "dialogs/studentdialog.h"
#include "dialogs/classdialog.h"
#include "dialogs/attendancedialog.h"
#include <QApplication>
#include <QStyle>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_database(new Database(this))
    , m_adminPanel(new AdminPanel(m_database, this))
    , m_reports(nullptr)
    , m_nepaliCalendar(new NepaliCalendar(this))
    , m_isAdmin(false)
    , m_darkMode(false)
    , m_useNepaliCalendar(true)
{
    setupUI();
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    loadSettings();
    loadData();
    updateDashboard();
}

MainWindow::~MainWindow()
{
    saveSettings();
}

void MainWindow::setupUI()
{
    setWindowTitle("Smart MA.VI Manager - School Management System");
    setMinimumSize(1200, 800);
    
    // Set window icon and logo
    setWindowIcon(QIcon(":/logo.png"));
    
    // Load style sheet
    loadStyleSheet();
    
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);
    
    setupDashboard();
    setupTeacherTab();
    setupStudentTab();
    setupClassTab();
    setupAttendanceTab();
    setupCalendarTab();
    setupReportsTab();
    setupSettingsTab();
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    
    // File menu
    QMenu *fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction("&Import Students", this, &MainWindow::importStudents, QKeySequence::Open);
    fileMenu->addAction("&Export Students", this, &MainWindow::exportStudents, QKeySequence::Save);
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &QWidget::close, QKeySequence::Quit);
    
    // Admin menu
    QMenu *adminMenu = menuBar->addMenu("&Admin");
    adminMenu->addAction("&Admin Panel", this, &MainWindow::showAdminPanel, QKeySequence("Ctrl+A"));
    adminMenu->addAction("&Logout", this, &MainWindow::logout, QKeySequence("Ctrl+L"));
    
    // Reports menu
    QMenu *reportsMenu = menuBar->addMenu("&Reports");
    reportsMenu->addAction("&Teacher Report", this, &MainWindow::generateTeacherReport);
    reportsMenu->addAction("&Student Report", this, &MainWindow::generateStudentReport);
    reportsMenu->addAction("&Attendance Report", this, &MainWindow::generateAttendanceReport);
    
    // Help menu
    QMenu *helpMenu = menuBar->addMenu("&Help");
    helpMenu->addAction("&About", [this]() {
        QMessageBox::about(this, "About Smart MA.VI Manager",
                          "Smart MA.VI Manager v1.0.0\n"
                          "School Management System for Shree MA.VI Imilya\n"
                          "Powered by Tech07\n\n"
                          "© 2024 All rights reserved.");
    });
}

void MainWindow::setupToolBar()
{
    QToolBar *toolBar = addToolBar("Main Toolbar");
    toolBar->setMovable(false);
    
    toolBar->addAction("Dashboard", this, [this]() { m_tabWidget->setCurrentIndex(0); });
    toolBar->addAction("Teachers", this, [this]() { m_tabWidget->setCurrentIndex(1); });
    toolBar->addAction("Students", this, [this]() { m_tabWidget->setCurrentIndex(2); });
    toolBar->addAction("Classes", this, [this]() { m_tabWidget->setCurrentIndex(3); });
    toolBar->addAction("Attendance", this, [this]() { m_tabWidget->setCurrentIndex(4); });
    toolBar->addAction("Calendar", this, [this]() { m_tabWidget->setCurrentIndex(5); });
    toolBar->addAction("Reports", this, [this]() { m_tabWidget->setCurrentIndex(6); });
    toolBar->addAction("Settings", this, [this]() { m_tabWidget->setCurrentIndex(7); });
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("Ready");
}

void MainWindow::setupDashboard()
{
    m_dashboardWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_dashboardWidget);
    
    // Header with logo and title
    QHBoxLayout *headerLayout = new QHBoxLayout();
    
    QLabel *logoLabel = new QLabel();
    QPixmap logoPixmap(":/logo.png");
    logoLabel->setPixmap(logoPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);
    
    QVBoxLayout *titleLayout = new QVBoxLayout();
    QLabel *welcomeLabel = new QLabel("Welcome to Smart MA.VI Manager");
    welcomeLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #2c3e50; margin: 5px;");
    
    QLabel *subtitleLabel = new QLabel("School Management System for Shree MA.VI Imilya");
    subtitleLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; margin: 5px;");
    
    titleLayout->addWidget(welcomeLabel);
    titleLayout->addWidget(subtitleLabel);
    
    headerLayout->addWidget(logoLabel);
    headerLayout->addLayout(titleLayout);
    headerLayout->addStretch();
    
    layout->addLayout(headerLayout);
    
    // Statistics cards
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    // Student stats card
    QGroupBox *studentCard = new QGroupBox("Students");
    studentCard->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #3498db; border-radius: 10px; margin: 10px; background-color: #ecf0f1; } QGroupBox::title { subcontrol-origin: margin; left: 15px; padding: 0 10px 0 10px; color: #2c3e50; }");
    QVBoxLayout *studentLayout = new QVBoxLayout(studentCard);
    m_totalStudentsLabel = new QLabel("0");
    m_totalStudentsLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #3498db;");
    m_totalStudentsLabel->setAlignment(Qt::AlignCenter);
    studentLayout->addWidget(m_totalStudentsLabel);
    studentLayout->addWidget(new QLabel("Total Students"));
    statsLayout->addWidget(studentCard);
    
    // Teacher stats card
    QGroupBox *teacherCard = new QGroupBox("Teachers");
    teacherCard->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #e74c3c; border-radius: 10px; margin: 10px; background-color: #ecf0f1; } QGroupBox::title { subcontrol-origin: margin; left: 15px; padding: 0 10px 0 10px; color: #2c3e50; }");
    QVBoxLayout *teacherLayout = new QVBoxLayout(teacherCard);
    m_totalTeachersLabel = new QLabel("0");
    m_totalTeachersLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #e74c3c;");
    m_totalTeachersLabel->setAlignment(Qt::AlignCenter);
    teacherLayout->addWidget(m_totalTeachersLabel);
    teacherLayout->addWidget(new QLabel("Total Teachers"));
    statsLayout->addWidget(teacherCard);
    
    // Class stats card
    QGroupBox *classCard = new QGroupBox("Classes");
    classCard->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #27ae60; border-radius: 10px; margin: 10px; background-color: #ecf0f1; } QGroupBox::title { subcontrol-origin: margin; left: 15px; padding: 0 10px 0 10px; color: #2c3e50; }");
    QVBoxLayout *classLayout = new QVBoxLayout(classCard);
    m_totalClassesLabel = new QLabel("0");
    m_totalClassesLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #27ae60;");
    m_totalClassesLabel->setAlignment(Qt::AlignCenter);
    classLayout->addWidget(m_totalClassesLabel);
    classLayout->addWidget(new QLabel("Total Classes"));
    statsLayout->addWidget(classCard);
    
    // Attendance stats card
    QGroupBox *attendanceCard = new QGroupBox("Today's Attendance");
    attendanceCard->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #f39c12; border-radius: 10px; margin: 10px; background-color: #ecf0f1; } QGroupBox::title { subcontrol-origin: margin; left: 15px; padding: 0 10px 0 10px; color: #2c3e50; }");
    QVBoxLayout *attendanceLayout = new QVBoxLayout(attendanceCard);
    m_todayAttendanceLabel = new QLabel("0%");
    m_todayAttendanceLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #f39c12;");
    m_todayAttendanceLabel->setAlignment(Qt::AlignCenter);
    attendanceLayout->addWidget(m_todayAttendanceLabel);
    attendanceLayout->addWidget(new QLabel("Attendance Rate"));
    statsLayout->addWidget(attendanceCard);
    
    layout->addLayout(statsLayout);
    
    // Quick actions
    QGroupBox *quickActionsGroup = new QGroupBox("Quick Actions");
    quickActionsGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #9b59b6; border-radius: 10px; margin: 10px; background-color: #ecf0f1; } QGroupBox::title { subcontrol-origin: margin; left: 15px; padding: 0 10px 0 10px; color: #2c3e50; }");
    
    QHBoxLayout *actionsLayout = new QHBoxLayout(quickActionsGroup);
    
    QPushButton *addStudentBtn = new QPushButton("Add Student");
    addStudentBtn->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 15px; border: none; border-radius: 8px; font-weight: bold; font-size: 14px; } QPushButton:hover { background-color: #2980b9; }");
    
    QPushButton *addTeacherBtn = new QPushButton("Add Teacher");
    addTeacherBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 15px; border: none; border-radius: 8px; font-weight: bold; font-size: 14px; } QPushButton:hover { background-color: #c0392b; }");
    
    QPushButton *markAttendanceBtn = new QPushButton("Mark Attendance");
    markAttendanceBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 15px; border: none; border-radius: 8px; font-weight: bold; font-size: 14px; } QPushButton:hover { background-color: #229954; }");
    
    QPushButton *generateReportBtn = new QPushButton("Generate Report");
    generateReportBtn->setStyleSheet("QPushButton { background-color: #f39c12; color: white; padding: 15px; border: none; border-radius: 8px; font-weight: bold; font-size: 14px; } QPushButton:hover { background-color: #e67e22; }");
    
    actionsLayout->addWidget(addStudentBtn);
    actionsLayout->addWidget(addTeacherBtn);
    actionsLayout->addWidget(markAttendanceBtn);
    actionsLayout->addWidget(generateReportBtn);
    
    layout->addWidget(quickActionsGroup);
    
    // Connect quick action buttons
    connect(addStudentBtn, &QPushButton::clicked, this, [this]() { m_tabWidget->setCurrentIndex(2); });
    connect(addTeacherBtn, &QPushButton::clicked, this, [this]() { m_tabWidget->setCurrentIndex(1); });
    connect(markAttendanceBtn, &QPushButton::clicked, this, [this]() { m_tabWidget->setCurrentIndex(4); });
    connect(generateReportBtn, &QPushButton::clicked, this, [this]() { m_tabWidget->setCurrentIndex(6); });
    
    layout->addStretch();
    
    m_tabWidget->addTab(m_dashboardWidget, "Dashboard");
}

void MainWindow::setupTeacherTab()
{
    m_teacherWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_teacherWidget);
    
    // Search and controls
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    m_teacherSearchEdit = new QLineEdit();
    m_teacherSearchEdit->setPlaceholderText("Search teachers...");
    m_addTeacherBtn = new QPushButton("Add Teacher");
    m_editTeacherBtn = new QPushButton("Edit Teacher");
    m_deleteTeacherBtn = new QPushButton("Delete Teacher");
    
    controlsLayout->addWidget(m_teacherSearchEdit);
    controlsLayout->addWidget(m_addTeacherBtn);
    controlsLayout->addWidget(m_editTeacherBtn);
    controlsLayout->addWidget(m_deleteTeacherBtn);
    
    layout->addLayout(controlsLayout);
    
    // Teacher table
    m_teacherTable = new QTableWidget();
    m_teacherTable->setColumnCount(6);
    m_teacherTable->setHorizontalHeaderLabels({"ID", "Name", "Subject", "Contact", "Class", "Status"});
    layout->addWidget(m_teacherTable);
    
    // Connect signals
    connect(m_addTeacherBtn, &QPushButton::clicked, this, &MainWindow::addTeacher);
    connect(m_editTeacherBtn, &QPushButton::clicked, this, &MainWindow::editTeacher);
    connect(m_deleteTeacherBtn, &QPushButton::clicked, this, &MainWindow::deleteTeacher);
    connect(m_teacherSearchEdit, &QLineEdit::textChanged, this, &MainWindow::searchTeachers);
    
    m_tabWidget->addTab(m_teacherWidget, "Teachers");
}

void MainWindow::setupStudentTab()
{
    m_studentWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_studentWidget);
    
    // Search and controls
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    m_studentSearchEdit = new QLineEdit();
    m_studentSearchEdit->setPlaceholderText("Search students...");
    m_studentClassFilter = new QComboBox();
    m_studentClassFilter->addItem("All Classes");
    m_addStudentBtn = new QPushButton("Add Student");
    m_editStudentBtn = new QPushButton("Edit Student");
    m_deleteStudentBtn = new QPushButton("Delete Student");
    m_importStudentBtn = new QPushButton("Import");
    m_exportStudentBtn = new QPushButton("Export");
    
    controlsLayout->addWidget(m_studentSearchEdit);
    controlsLayout->addWidget(m_studentClassFilter);
    controlsLayout->addWidget(m_addStudentBtn);
    controlsLayout->addWidget(m_editStudentBtn);
    controlsLayout->addWidget(m_deleteStudentBtn);
    controlsLayout->addWidget(m_importStudentBtn);
    controlsLayout->addWidget(m_exportStudentBtn);
    
    layout->addLayout(controlsLayout);
    
    // Student table
    m_studentTable = new QTableWidget();
    m_studentTable->setColumnCount(7);
    m_studentTable->setHorizontalHeaderLabels({"Roll No", "Name", "Class", "Guardian", "Contact", "Address", "Status"});
    layout->addWidget(m_studentTable);
    
    // Connect signals
    connect(m_addStudentBtn, &QPushButton::clicked, this, &MainWindow::addStudent);
    connect(m_editStudentBtn, &QPushButton::clicked, this, &MainWindow::editStudent);
    connect(m_deleteStudentBtn, &QPushButton::clicked, this, &MainWindow::deleteStudent);
    connect(m_importStudentBtn, &QPushButton::clicked, this, &MainWindow::importStudents);
    connect(m_exportStudentBtn, &QPushButton::clicked, this, &MainWindow::exportStudents);
    connect(m_studentSearchEdit, &QLineEdit::textChanged, this, &MainWindow::searchStudents);
    
    m_tabWidget->addTab(m_studentWidget, "Students");
}

void MainWindow::setupClassTab()
{
    m_classWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_classWidget);
    
    // Controls
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    m_addClassBtn = new QPushButton("Add Class");
    m_editClassBtn = new QPushButton("Edit Class");
    m_deleteClassBtn = new QPushButton("Delete Class");
    
    controlsLayout->addWidget(m_addClassBtn);
    controlsLayout->addWidget(m_editClassBtn);
    controlsLayout->addWidget(m_deleteClassBtn);
    controlsLayout->addStretch();
    
    layout->addLayout(controlsLayout);
    
    // Class table
    m_classTable = new QTableWidget();
    m_classTable->setColumnCount(6);
    m_classTable->setHorizontalHeaderLabels({"ID", "Name", "Grade", "Capacity", "Teacher", "Status"});
    layout->addWidget(m_classTable);
    
    // Connect signals
    connect(m_addClassBtn, &QPushButton::clicked, this, &MainWindow::addClass);
    connect(m_editClassBtn, &QPushButton::clicked, this, &MainWindow::editClass);
    connect(m_deleteClassBtn, &QPushButton::clicked, this, &MainWindow::deleteClass);
    
    m_tabWidget->addTab(m_classWidget, "Classes");
}

void MainWindow::setupAttendanceTab()
{
    m_attendanceWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_attendanceWidget);
    
    // Controls
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    m_attendanceDateEdit = new QDateEdit();
    m_attendanceDateEdit->setDate(QDate::currentDate());
    m_attendanceClassFilter = new QComboBox();
    m_attendanceClassFilter->addItem("All Classes");
    m_markAttendanceBtn = new QPushButton("Mark Attendance");
    m_viewAttendanceBtn = new QPushButton("View Attendance");
    m_exportAttendanceBtn = new QPushButton("Export");
    
    controlsLayout->addWidget(new QLabel("Date:"));
    controlsLayout->addWidget(m_attendanceDateEdit);
    controlsLayout->addWidget(new QLabel("Class:"));
    controlsLayout->addWidget(m_attendanceClassFilter);
    controlsLayout->addWidget(m_markAttendanceBtn);
    controlsLayout->addWidget(m_viewAttendanceBtn);
    controlsLayout->addWidget(m_exportAttendanceBtn);
    
    layout->addLayout(controlsLayout);
    
    // Attendance table
    m_attendanceTable = new QTableWidget();
    m_attendanceTable->setColumnCount(5);
    m_attendanceTable->setHorizontalHeaderLabels({"Student", "Class", "Date", "Status", "Remarks"});
    layout->addWidget(m_attendanceTable);
    
    // Connect signals
    connect(m_markAttendanceBtn, &QPushButton::clicked, this, &MainWindow::markAttendance);
    connect(m_viewAttendanceBtn, &QPushButton::clicked, this, &MainWindow::viewAttendance);
    connect(m_exportAttendanceBtn, &QPushButton::clicked, this, &MainWindow::exportAttendance);
    
    m_tabWidget->addTab(m_attendanceWidget, "Attendance");
}

void MainWindow::setupCalendarTab()
{
    m_calendarWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(m_calendarWidget);
    
    // Calendar
    QVBoxLayout *calendarLayout = new QVBoxLayout();
    m_calendar = new QCalendarWidget();
    m_nepaliDateLabel = new QLabel();
    m_addHolidayBtn = new QPushButton("Add Holiday");
    m_addEventBtn = new QPushButton("Add Event");
    
    calendarLayout->addWidget(m_calendar);
    calendarLayout->addWidget(m_nepaliDateLabel);
    calendarLayout->addWidget(m_addHolidayBtn);
    calendarLayout->addWidget(m_addEventBtn);
    
    // Events table
    QVBoxLayout *eventsLayout = new QVBoxLayout();
    eventsLayout->addWidget(new QLabel("Events:"));
    m_eventsTable = new QTableWidget();
    m_eventsTable->setColumnCount(3);
    m_eventsTable->setHorizontalHeaderLabels({"Date", "Title", "Description"});
    eventsLayout->addWidget(m_eventsTable);
    
    layout->addLayout(calendarLayout);
    layout->addLayout(eventsLayout);
    
    // Connect signals
    connect(m_calendar, &QCalendarWidget::clicked, this, &MainWindow::onDateSelected);
    connect(m_addHolidayBtn, &QPushButton::clicked, this, &MainWindow::addHoliday);
    connect(m_addEventBtn, &QPushButton::clicked, this, &MainWindow::addEvent);
    
    m_tabWidget->addTab(m_calendarWidget, "Calendar");
}

void MainWindow::setupReportsTab()
{
    m_reportsWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_reportsWidget);
    
    // Controls
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    m_reportTypeCombo = new QComboBox();
    m_reportTypeCombo->addItems({"Teacher Report", "Student Report", "Attendance Report", "Class Report", "Summary Report"});
    m_reportStartDate = new QDateEdit();
    m_reportStartDate->setDate(QDate::currentDate().addDays(-30));
    m_reportEndDate = new QDateEdit();
    m_reportEndDate->setDate(QDate::currentDate());
    m_generateReportBtn = new QPushButton("Generate Report");
    m_exportReportBtn = new QPushButton("Export Report");
    
    controlsLayout->addWidget(new QLabel("Report Type:"));
    controlsLayout->addWidget(m_reportTypeCombo);
    controlsLayout->addWidget(new QLabel("Start Date:"));
    controlsLayout->addWidget(m_reportStartDate);
    controlsLayout->addWidget(new QLabel("End Date:"));
    controlsLayout->addWidget(m_reportEndDate);
    controlsLayout->addWidget(m_generateReportBtn);
    controlsLayout->addWidget(m_exportReportBtn);
    
    layout->addLayout(controlsLayout);
    
    // Report preview
    m_reportPreview = new QTextEdit();
    m_reportPreview->setReadOnly(true);
    layout->addWidget(m_reportPreview);
    
    // Connect signals
    connect(m_generateReportBtn, &QPushButton::clicked, this, &MainWindow::generateTeacherReport);
    connect(m_exportReportBtn, &QPushButton::clicked, this, &MainWindow::exportReport);
    
    m_tabWidget->addTab(m_reportsWidget, "Reports");
}

void MainWindow::setupSettingsTab()
{
    m_settingsWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_settingsWidget);
    
    // Settings
    m_darkModeCheckBox = new QCheckBox("Dark Mode");
    m_nepaliCalendarCheckBox = new QCheckBox("Use Nepali Calendar");
    m_backupDataBtn = new QPushButton("Backup Data");
    m_restoreDataBtn = new QPushButton("Restore Data");
    
    layout->addWidget(m_darkModeCheckBox);
    layout->addWidget(m_nepaliCalendarCheckBox);
    layout->addWidget(m_backupDataBtn);
    layout->addWidget(m_restoreDataBtn);
    layout->addStretch();
    
    // Connect signals
    connect(m_darkModeCheckBox, &QCheckBox::toggled, this, &MainWindow::toggleTheme);
    connect(m_backupDataBtn, &QPushButton::clicked, this, [this]() {
        QString filename = QFileDialog::getSaveFileName(this, "Backup Database", "", "Database Files (*.db)");
        if (!filename.isEmpty()) {
            m_database->backupDatabase(filename);
            showNotification("Database backed up successfully", "success");
        }
    });
    connect(m_restoreDataBtn, &QPushButton::clicked, this, [this]() {
        QString filename = QFileDialog::getOpenFileName(this, "Restore Database", "", "Database Files (*.db)");
        if (!filename.isEmpty()) {
            m_database->restoreDatabase(filename);
            showNotification("Database restored successfully", "success");
        }
    });
    
    m_tabWidget->addTab(m_settingsWidget, "Settings");
}

void MainWindow::loadData()
{
    refreshTeacherTable();
    refreshStudentTable();
    refreshClassTable();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("darkMode", m_darkMode);
    settings.setValue("useNepaliCalendar", m_useNepaliCalendar);
    settings.setValue("language", m_language);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    m_darkMode = settings.value("darkMode", false).toBool();
    m_useNepaliCalendar = settings.value("useNepaliCalendar", true).toBool();
    m_language = settings.value("language", "en").toString();
    
    m_darkModeCheckBox->setChecked(m_darkMode);
    m_nepaliCalendarCheckBox->setChecked(m_useNepaliCalendar);
}

void MainWindow::showNotification(const QString &message, const QString &type)
{
    statusBar()->showMessage(message, 3000);
}

// Placeholder implementations for slots
void MainWindow::updateDashboard() {
    // Update dashboard statistics
    m_totalStudentsLabel->setText("25");
    m_totalTeachersLabel->setText("8");
    m_totalClassesLabel->setText("12");
    m_todayAttendanceLabel->setText("92%");
}

void MainWindow::showTodayAttendance() {
    showNotification("Today's attendance: 92% (23/25 students present)", "info");
}

void MainWindow::addTeacher() {
    TeacherDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Teacher teacher = dialog.getTeacher();
        showNotification("Teacher added successfully: " + teacher.getName(), "success");
        refreshTeacherTable();
    }
}

void MainWindow::editTeacher() {
    // In a real implementation, you would get the selected teacher
    Teacher sampleTeacher(1, "Mr. Ram Bahadur", "Mathematics", "+977123456789", 1, "ram@school.edu.np", "Kathmandu", QDate(2024, 1, 1));
    
    TeacherDialog dialog(sampleTeacher, this);
    if (dialog.exec() == QDialog::Accepted) {
        Teacher teacher = dialog.getTeacher();
        showNotification("Teacher updated successfully: " + teacher.getName(), "success");
        refreshTeacherTable();
    }
}

void MainWindow::deleteTeacher() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete", 
                                                            "Are you sure you want to delete this teacher?",
                                                            QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        showNotification("Teacher deleted successfully", "success");
        refreshTeacherTable();
    }
}

void MainWindow::refreshTeacherTable() {
    // In a real implementation, this would load teachers from database
    m_teacherTable->setRowCount(3);
    
    QStringList teachers = {"Mr. Ram Bahadur", "Mrs. Sita Devi", "Mr. Krishna Kumar"};
    QStringList subjects = {"Mathematics", "English", "Science"};
    QStringList contacts = {"+977123456789", "+977987654321", "+977555555555"};
    
    for (int i = 0; i < 3; ++i) {
        m_teacherTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        m_teacherTable->setItem(i, 1, new QTableWidgetItem(teachers[i]));
        m_teacherTable->setItem(i, 2, new QTableWidgetItem(subjects[i]));
        m_teacherTable->setItem(i, 3, new QTableWidgetItem(contacts[i]));
        m_teacherTable->setItem(i, 4, new QTableWidgetItem("Grade " + QString::number(i + 1)));
        m_teacherTable->setItem(i, 5, new QTableWidgetItem("Active"));
    }
}

void MainWindow::searchTeachers() {
    QString searchText = m_teacherSearchEdit->text().toLower();
    showNotification("Searching for: " + searchText, "info");
}

void MainWindow::addStudent() {
    StudentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Student student = dialog.getStudent();
        showNotification("Student added successfully: " + student.getName(), "success");
        refreshStudentTable();
    }
}

void MainWindow::editStudent() {
    // In a real implementation, you would get the selected student
    Student sampleStudent(1, "ST001", "Aarav Sharma", 1, "Rajesh Sharma", "+977111111111", "rajesh@email.com", "Kathmandu", QDate(2017, 5, 15), "Male", QDate(2024, 1, 1));
    
    StudentDialog dialog(sampleStudent, this);
    if (dialog.exec() == QDialog::Accepted) {
        Student student = dialog.getStudent();
        showNotification("Student updated successfully: " + student.getName(), "success");
        refreshStudentTable();
    }
}

void MainWindow::deleteStudent() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete", 
                                                            "Are you sure you want to delete this student?",
                                                            QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        showNotification("Student deleted successfully", "success");
        refreshStudentTable();
    }
}

void MainWindow::refreshStudentTable() {
    // In a real implementation, this would load students from database
    m_studentTable->setRowCount(5);
    
    QStringList students = {"Aarav Sharma", "Zara Khan", "Arjun Patel", "Myra Kapoor", "Rohan Singh"};
    QStringList rollNos = {"ST001", "ST002", "ST003", "ST004", "ST005"};
    QStringList classes = {"Grade 1", "Grade 1", "Grade 2", "Grade 2", "Grade 3"};
    
    for (int i = 0; i < 5; ++i) {
        m_studentTable->setItem(i, 0, new QTableWidgetItem(rollNos[i]));
        m_studentTable->setItem(i, 1, new QTableWidgetItem(students[i]));
        m_studentTable->setItem(i, 2, new QTableWidgetItem(classes[i]));
        m_studentTable->setItem(i, 3, new QTableWidgetItem("Active"));
    }
}

void MainWindow::searchStudents() {
    QString searchText = m_studentSearchEdit->text().toLower();
    showNotification("Searching for: " + searchText, "info");
}

void MainWindow::importStudents() {
    QString filename = QFileDialog::getOpenFileName(this, "Import Students", "", "CSV Files (*.csv)");
    if (!filename.isEmpty()) {
        showNotification("Students imported successfully from: " + filename, "success");
        refreshStudentTable();
    }
}

void MainWindow::exportStudents() {
    QString filename = QFileDialog::getSaveFileName(this, "Export Students", "", "CSV Files (*.csv)");
    if (!filename.isEmpty()) {
        showNotification("Students exported successfully to: " + filename, "success");
    }
}

void MainWindow::addClass() {
    ClassDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Class classObj = dialog.getClass();
        showNotification("Class added successfully: " + classObj.getName(), "success");
        refreshClassTable();
    }
}

void MainWindow::editClass() {
    // In a real implementation, you would get the selected class
    Class sampleClass(1, "Class A", 1, 40, "Room 101", 1, "Grade 1 Class A");
    
    ClassDialog dialog(sampleClass, this);
    if (dialog.exec() == QDialog::Accepted) {
        Class classObj = dialog.getClass();
        showNotification("Class updated successfully: " + classObj.getName(), "success");
        refreshClassTable();
    }
}

void MainWindow::deleteClass() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete", 
                                                            "Are you sure you want to delete this class?",
                                                            QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        showNotification("Class deleted successfully", "success");
        refreshClassTable();
    }
}

void MainWindow::refreshClassTable() {
    // In a real implementation, this would load classes from database
    m_classTable->setRowCount(4);
    
    QStringList classes = {"Class A", "Class B", "Class C", "Class D"};
    QStringList grades = {"Grade 1", "Grade 1", "Grade 2", "Grade 2"};
    QStringList capacities = {"40", "35", "38", "42"};
    QStringList rooms = {"Room 101", "Room 102", "Room 201", "Room 202"};
    
    for (int i = 0; i < 4; ++i) {
        m_classTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        m_classTable->setItem(i, 1, new QTableWidgetItem(classes[i]));
        m_classTable->setItem(i, 2, new QTableWidgetItem(grades[i]));
        m_classTable->setItem(i, 3, new QTableWidgetItem(capacities[i]));
        m_classTable->setItem(i, 4, new QTableWidgetItem(rooms[i]));
        m_classTable->setItem(i, 5, new QTableWidgetItem("Active"));
    }
}

void MainWindow::markAttendance() {
    AttendanceDialog dialog(1, QDate::currentDate(), this);
    if (dialog.exec() == QDialog::Accepted) {
        QList<Attendance> attendanceList = dialog.getAttendanceList();
        showNotification("Attendance marked successfully for " + QString::number(attendanceList.size()) + " students", "success");
    }
}

void MainWindow::viewAttendance() {
    showNotification("Viewing attendance records", "info");
}

void MainWindow::exportAttendance() {
    QString filename = QFileDialog::getSaveFileName(this, "Export Attendance", "", "CSV Files (*.csv)");
    if (!filename.isEmpty()) {
        showNotification("Attendance exported successfully to: " + filename, "success");
    }
}

void MainWindow::onDateSelected(const QDate &date) {
    showNotification("Date selected: " + date.toString("dddd, MMMM dd, yyyy"), "info");
}

void MainWindow::addHoliday() {
    showNotification("Add holiday functionality", "info");
}

void MainWindow::addEvent() {
    showNotification("Add event functionality", "info");
}

void MainWindow::generateTeacherReport() {
    showNotification("Generating teacher report...", "info");
}

void MainWindow::generateStudentReport() {
    showNotification("Generating student report...", "info");
}
void MainWindow::generateAttendanceReport() {}
void MainWindow::exportReport() {}
void MainWindow::showAdminPanel() {}
void MainWindow::logout() {}
void MainWindow::showSettings() {}
void MainWindow::toggleTheme() {}

void MainWindow::loadStyleSheet()
{
    QFile file(":/styles/light.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = file.readAll();
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}
