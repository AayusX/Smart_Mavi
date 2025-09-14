#ifndef SIMPLE_GUI_H
#define SIMPLE_GUI_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <vector>
#include <string>
#include <random>

class SmartMaviGUI : public QMainWindow
{
    Q_OBJECT

public:
    struct Teacher {
        std::string name;
        std::vector<std::string> subjects;
        int id;
    };
    
    struct Subject {
        std::string name;
        int id;
    };
    
    struct Class {
        std::string name;
        std::string grade;
        int id;
    };
    
    struct ScheduleEntry {
        std::string teacher;
        std::string subject;
        std::string className;
        std::string timeSlot;
        std::string day;
    };

    SmartMaviGUI(QWidget *parent = nullptr);

private slots:
    void addTeacher();
    void addSubject();
    void addClass();
    void generateSchedule();
    void exportToPDF();
    void showAbout();

private:
    void setupUI();
    void setupSetupTab();
    void setupScheduleTab();
    void updateTeachersList();
    void updateSubjectsList();
    void updateClassesList();
    void displaySchedule();

    std::vector<Teacher> teachers;
    std::vector<Subject> subjects;
    std::vector<Class> classes;
    std::vector<ScheduleEntry> schedule;
    std::vector<std::string> days;
    std::vector<std::string> timeSlots;
    
    QTabWidget *tabWidget;
    QWidget *setupTab;
    QWidget *scheduleTab;
    
    QLineEdit *teacherNameEdit;
    QLineEdit *subjectNameEdit;
    QLineEdit *classNameEdit;
    QLineEdit *classGradeEdit;
    QTextEdit *teachersListText;
    QTextEdit *subjectsListText;
    QTextEdit *classesListText;
    QTableWidget *scheduleTable;
    
    std::mt19937 rng;
};

#endif // SIMPLE_GUI_H
