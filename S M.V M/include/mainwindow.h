#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QProgressBar>
#include <QTextEdit>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QSplitter>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QResizeEvent>

// Forward declarations
class Teacher;
class Student;
class Class;
class Attendance;
class NepaliCalendar;
class Database;
class AdminPanel;
class Reports;
class Dashboard;
class CommunicationManager;
class AdvancedAttendanceManager;
class AdvancedReports;
class SettingsManager;
class BackupManager;
class SystemMonitor;
class EnhancedStudent;
class StudentProfileWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Dashboard slots
    void updateDashboard();
    void showTodayAttendance();
    
    // Teacher management slots
    void addTeacher();
    void editTeacher();
    void deleteTeacher();
    void refreshTeacherTable();
    void searchTeachers();
    
    // Student management slots
    void addStudent();
    void editStudent();
    void deleteStudent();
    void refreshStudentTable();
    void searchStudents();
    void importStudents();
    void exportStudents();
    
    // Class management slots
    void addClass();
    void editClass();
    void deleteClass();
    void refreshClassTable();
    
    // Attendance slots
    void markAttendance();
    void viewAttendance();
    void exportAttendance();
    
    // Calendar slots
    void onDateSelected(const QDate &date);
    void addHoliday();
    void addEvent();
    
    // Reports slots
    void generateTeacherReport();
    void generateStudentReport();
    void generateAttendanceReport();
    void exportReport();
    
    // Admin slots
    void showAdminPanel();
    void logout();
    
    // Settings slots
    void showSettings();
    void toggleTheme();
    void loadStyleSheet();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupDashboard();
    void setupTeacherTab();
    void setupStudentTab();
    void setupClassTab();
    void setupAttendanceTab();
    void setupCalendarTab();
    void setupReportsTab();
    void setupSettingsTab();
    
    void loadData();
    void saveSettings();
    void loadSettings();
    void showNotification(const QString &message, const QString &type = "info");
    
    // UI Components
    QTabWidget *m_tabWidget;
    
    // Dashboard
    QWidget *m_dashboardWidget;
    QLabel *m_totalStudentsLabel;
    QLabel *m_totalTeachersLabel;
    QLabel *m_totalClassesLabel;
    QLabel *m_todayAttendanceLabel;
    QProgressBar *m_attendanceProgressBar;
    QChartView *m_attendanceChartView;
    
    // Teacher management
    QWidget *m_teacherWidget;
    QTableWidget *m_teacherTable;
    QPushButton *m_addTeacherBtn;
    QPushButton *m_editTeacherBtn;
    QPushButton *m_deleteTeacherBtn;
    QLineEdit *m_teacherSearchEdit;
    
    // Student management
    QWidget *m_studentWidget;
    QTableWidget *m_studentTable;
    QPushButton *m_addStudentBtn;
    QPushButton *m_editStudentBtn;
    QPushButton *m_deleteStudentBtn;
    QPushButton *m_importStudentBtn;
    QPushButton *m_exportStudentBtn;
    QLineEdit *m_studentSearchEdit;
    QComboBox *m_studentClassFilter;
    
    // Class management
    QWidget *m_classWidget;
    QTableWidget *m_classTable;
    QPushButton *m_addClassBtn;
    QPushButton *m_editClassBtn;
    QPushButton *m_deleteClassBtn;
    
    // Attendance
    QWidget *m_attendanceWidget;
    QTableWidget *m_attendanceTable;
    QPushButton *m_markAttendanceBtn;
    QPushButton *m_viewAttendanceBtn;
    QPushButton *m_exportAttendanceBtn;
    QDateEdit *m_attendanceDateEdit;
    QComboBox *m_attendanceClassFilter;
    
    // Calendar
    QWidget *m_calendarWidget;
    QCalendarWidget *m_calendar;
    QTableWidget *m_eventsTable;
    QPushButton *m_addHolidayBtn;
    QPushButton *m_addEventBtn;
    QLabel *m_nepaliDateLabel;
    
    // Reports
    QWidget *m_reportsWidget;
    QComboBox *m_reportTypeCombo;
    QDateEdit *m_reportStartDate;
    QDateEdit *m_reportEndDate;
    QPushButton *m_generateReportBtn;
    QPushButton *m_exportReportBtn;
    QTextEdit *m_reportPreview;
    
    // Settings
    QWidget *m_settingsWidget;
    QCheckBox *m_darkModeCheckBox;
    QCheckBox *m_nepaliCalendarCheckBox;
    QPushButton *m_backupDataBtn;
    QPushButton *m_restoreDataBtn;
    
    // Data members
    Database *m_database;
    AdminPanel *m_adminPanel;
    void *m_reports;  // Temporarily void* until Reports class is implemented
    NepaliCalendar *m_nepaliCalendar;
    
    bool m_isAdmin;
    QString m_currentUser;
    
    // Settings
    bool m_darkMode;
    bool m_useNepaliCalendar;
    QString m_language;
};

#endif // MAINWINDOW_H
