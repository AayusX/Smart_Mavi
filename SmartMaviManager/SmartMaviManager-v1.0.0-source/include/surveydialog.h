#ifndef SURVEYDIALOG_H
#define SURVEYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTimeEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QStackedWidget>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include "schedulegenerator.h"

class SurveyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SurveyDialog(QWidget *parent = nullptr);
    
    ScheduleConfig getScheduleConfig() const;

private slots:
    void nextPage();
    void previousPage();
    void addTeacher();
    void addSubject();
    void addClass();
    void removeSelectedTeacher();
    void removeSelectedSubject();
    void removeSelectedClass();
    void onTeacherSelectionChanged();
    void addSubjectToTeacher();
    void removeSubjectFromTeacher();
    void finishSurvey();

private:
    void setupUI();
    void setupPage1(); // Welcome and basic info
    void setupPage2(); // Teachers input
    void setupPage3(); // Subjects input  
    void setupPage4(); // Classes input
    void setupPage5(); // Teacher-Subject assignments
    void setupPage6(); // Time settings
    void setupPage7(); // Final confirmation
    
    void updateProgress();
    void animatePageTransition();
    void applyModernStyling();
    void showSuccessMessage();

    QStackedWidget *m_stackedWidget;
    QProgressBar *m_progressBar;
    QLabel *m_pageTitle;
    QPushButton *m_nextButton;
    QPushButton *m_backButton;
    QPushButton *m_finishButton;
    
    // Page 1 - Basic Info
    QSpinBox *m_numTeachers;
    QSpinBox *m_numSubjects;
    QSpinBox *m_numClasses;
    
    // Page 2 - Teachers
    QLineEdit *m_teacherNameEdit;
    QListWidget *m_teachersList;
    
    // Page 3 - Subjects
    QLineEdit *m_subjectNameEdit;
    QListWidget *m_subjectsList;
    
    // Page 4 - Classes
    QLineEdit *m_classNameEdit;
    QComboBox *m_gradeCombo;
    QListWidget *m_classesList;
    
    // Page 5 - Teacher-Subject assignments
    QComboBox *m_teacherCombo;
    QListWidget *m_availableSubjects;
    QListWidget *m_assignedSubjects;
    
    // Page 6 - Time settings
    QTimeEdit *m_schoolStartTime;
    QTimeEdit *m_schoolEndTime;
    QSpinBox *m_periodDuration;
    QTimeEdit *m_breakStartTime;
    QSpinBox *m_breakDuration;
    QTimeEdit *m_lunchStartTime;
    QSpinBox *m_lunchDuration;
    QSpinBox *m_maxPeriodsPerDay;
    QSpinBox *m_maxPeriodsPerTeacher;
    
    // Data storage
    QVector<Teacher> m_teachers;
    QVector<Subject> m_subjects;
    QVector<ClassInfo> m_classes;
    
    int m_currentPage;
    static const int TOTAL_PAGES = 7;
};

#endif // SURVEYDIALOG_H
