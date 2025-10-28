#pragma once
#include "common.h"
#include "student_dialog.h"

class DashboardWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = nullptr);
    ~DashboardWindow() override;

private slots:
    void setupUI();
    void loadStudents();
    void refreshStudentsList();
    void addStudent();
    void editStudent();
    void deleteStudent();
    void searchStudents(const QString& text);
    void exportToCSV();
    void exportToPDF();
    void updatePerformanceChart();
    void filterStudents(const QString& criteria);
    void sortStudents(int column);

private:
    // UI Components
    QTableWidget* studentsTable;
    QLineEdit* searchBox;
    QComboBox* filterBox;
    QComboBox* yearFilterBox;
    QPushButton* addButton;
    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* exportCSVButton;
    QPushButton* exportPDFButton;
    QChartView* performanceChart;
    QBarSeries* performanceSeries;
    
    // Layouts
    QVBoxLayout* mainLayout;
    QHBoxLayout* toolbarLayout;
    QWidget* centralWidget;
    
    // Helper methods
    void createToolbar();
    void createStudentsTable();
    void createPerformanceChart();
    void setupConnections();
    void styleComponents();
    
    // Data management
    struct Student {
        QString name;
        QString className;
        int marks;
        int year;
        QString enrollmentDate;
        
        bool isValid() const {
            return !name.isEmpty() && !className.isEmpty() && 
                   marks >= 0 && marks <= 100 && year >= 1 && year <= 4 &&
                   !enrollmentDate.isEmpty();
        }
    };
    
    QList<Student> students;
    void saveStudents();
    void loadFromJson();
    bool validateStudent(const Student& student);
};