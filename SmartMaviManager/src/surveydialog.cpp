#include "surveydialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QSplitter>
#include <QPalette>
#include <QGraphicsDropShadowEffect>

SurveyDialog::SurveyDialog(QWidget *parent)
    : QDialog(parent), m_currentPage(0)
{
    setWindowTitle("Smart Mavi Manager - Setup Wizard 🎓");
    setFixedSize(800, 600);
    setupUI();
    applyModernStyling();
}

void SurveyDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title and progress bar
    m_pageTitle = new QLabel("Welcome to Smart Mavi Manager! 🚀");
    m_pageTitle->setAlignment(Qt::AlignCenter);
    m_pageTitle->setObjectName("pageTitle");
    
    m_progressBar = new QProgressBar;
    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(TOTAL_PAGES - 1);
    m_progressBar->setValue(0);
    m_progressBar->setTextVisible(true);
    m_progressBar->setFormat("Step %v of %m");
    
    // Stacked widget for pages
    m_stackedWidget = new QStackedWidget;
    
    // Setup all pages
    setupPage1();
    setupPage2();
    setupPage3();
    setupPage4();
    setupPage5();
    setupPage6();
    setupPage7();
    
    // Navigation buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_backButton = new QPushButton("⬅️ Back");
    m_nextButton = new QPushButton("Next ➡️");
    m_finishButton = new QPushButton("🎯 Generate Schedule!");
    
    m_backButton->setEnabled(false);
    m_finishButton->setVisible(false);
    
    buttonLayout->addWidget(m_backButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_nextButton);
    buttonLayout->addWidget(m_finishButton);
    
    // Add to main layout
    mainLayout->addWidget(m_pageTitle);
    mainLayout->addWidget(m_progressBar);
    mainLayout->addWidget(m_stackedWidget, 1);
    mainLayout->addLayout(buttonLayout);
    
    // Connect signals
    connect(m_nextButton, &QPushButton::clicked, this, &SurveyDialog::nextPage);
    connect(m_backButton, &QPushButton::clicked, this, &SurveyDialog::previousPage);
    connect(m_finishButton, &QPushButton::clicked, this, &SurveyDialog::finishSurvey);
    
    updateProgress();
}

void SurveyDialog::setupPage1()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QLabel *welcomeLabel = new QLabel(
        "🎉 Welcome to Smart Mavi Manager! 🎉\n\n"
        "Let's create an awesome schedule for your school! 📚\n"
        "This wizard will guide you through setting up:\n\n"
        "✨ Teachers and their subjects\n"
        "🏫 Classes and grades\n" 
        "⏰ Time periods and breaks\n"
        "🎲 Randomized schedule generation\n\n"
        "Let's start with some basic information:"
    );
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setWordWrap(true);
    welcomeLabel->setObjectName("welcomeText");
    
    QGroupBox *basicInfoGroup = new QGroupBox("📊 Basic Information");
    QGridLayout *gridLayout = new QGridLayout(basicInfoGroup);
    
    // Number of teachers
    gridLayout->addWidget(new QLabel("👨‍🏫 Number of Teachers:"), 0, 0);
    m_numTeachers = new QSpinBox;
    m_numTeachers->setRange(1, 50);
    m_numTeachers->setValue(5);
    m_numTeachers->setSuffix(" teachers");
    gridLayout->addWidget(m_numTeachers, 0, 1);
    
    // Number of subjects
    gridLayout->addWidget(new QLabel("📚 Number of Subjects:"), 1, 0);
    m_numSubjects = new QSpinBox;
    m_numSubjects->setRange(1, 20);
    m_numSubjects->setValue(6);
    m_numSubjects->setSuffix(" subjects");
    gridLayout->addWidget(m_numSubjects, 1, 1);
    
    // Number of classes
    gridLayout->addWidget(new QLabel("🏫 Number of Classes:"), 2, 0);
    m_numClasses = new QSpinBox;
    m_numClasses->setRange(1, 20);
    m_numClasses->setValue(4);
    m_numClasses->setSuffix(" classes");
    gridLayout->addWidget(m_numClasses, 2, 1);
    
    layout->addWidget(welcomeLabel);
    layout->addWidget(basicInfoGroup);
    layout->addStretch();
    
    m_stackedWidget->addWidget(page);
}

void SurveyDialog::setupPage2()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QLabel *titleLabel = new QLabel("👨‍🏫 Let's Meet Your Amazing Teachers!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageSubtitle");
    
    QGroupBox *teacherGroup = new QGroupBox("Add Teachers 🌟");
    QVBoxLayout *teacherLayout = new QVBoxLayout(teacherGroup);
    
    QHBoxLayout *inputLayout = new QHBoxLayout;
    m_teacherNameEdit = new QLineEdit;
    m_teacherNameEdit->setPlaceholderText("Enter teacher name (e.g., Mr. Smith, Ms. Johnson...)");
    QPushButton *addTeacherBtn = new QPushButton("➕ Add Teacher");
    QPushButton *removeTeacherBtn = new QPushButton("➖ Remove");
    
    inputLayout->addWidget(new QLabel("Teacher Name:"));
    inputLayout->addWidget(m_teacherNameEdit);
    inputLayout->addWidget(addTeacherBtn);
    inputLayout->addWidget(removeTeacherBtn);
    
    m_teachersList = new QListWidget;
    m_teachersList->setAlternatingRowColors(true);
    
    teacherLayout->addLayout(inputLayout);
    teacherLayout->addWidget(m_teachersList);
    
    layout->addWidget(titleLabel);
    layout->addWidget(teacherGroup);
    
    // Connect signals
    connect(addTeacherBtn, &QPushButton::clicked, this, &SurveyDialog::addTeacher);
    connect(removeTeacherBtn, &QPushButton::clicked, this, &SurveyDialog::removeSelectedTeacher);
    connect(m_teacherNameEdit, &QLineEdit::returnPressed, this, &SurveyDialog::addTeacher);
    
    m_stackedWidget->addWidget(page);
}

void SurveyDialog::setupPage3()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QLabel *titleLabel = new QLabel("📚 What Subjects Will You Teach?");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageSubtitle");
    
    QGroupBox *subjectGroup = new QGroupBox("Add Subjects 📖");
    QVBoxLayout *subjectLayout = new QVBoxLayout(subjectGroup);
    
    QHBoxLayout *inputLayout = new QHBoxLayout;
    m_subjectNameEdit = new QLineEdit;
    m_subjectNameEdit->setPlaceholderText("Enter subject (e.g., Mathematics, Science, History...)");
    QPushButton *addSubjectBtn = new QPushButton("➕ Add Subject");
    QPushButton *removeSubjectBtn = new QPushButton("➖ Remove");
    
    inputLayout->addWidget(new QLabel("Subject Name:"));
    inputLayout->addWidget(m_subjectNameEdit);
    inputLayout->addWidget(addSubjectBtn);
    inputLayout->addWidget(removeSubjectBtn);
    
    m_subjectsList = new QListWidget;
    m_subjectsList->setAlternatingRowColors(true);
    
    subjectLayout->addLayout(inputLayout);
    subjectLayout->addWidget(m_subjectsList);
    
    layout->addWidget(titleLabel);
    layout->addWidget(subjectGroup);
    
    // Connect signals
    connect(addSubjectBtn, &QPushButton::clicked, this, &SurveyDialog::addSubject);
    connect(removeSubjectBtn, &QPushButton::clicked, this, &SurveyDialog::removeSelectedSubject);
    connect(m_subjectNameEdit, &QLineEdit::returnPressed, this, &SurveyDialog::addSubject);
    
    m_stackedWidget->addWidget(page);
}

void SurveyDialog::setupPage4()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QLabel *titleLabel = new QLabel("🏫 Define Your Classes!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageSubtitle");
    
    QGroupBox *classGroup = new QGroupBox("Add Classes 🎒");
    QVBoxLayout *classLayout = new QVBoxLayout(classGroup);
    
    QHBoxLayout *inputLayout = new QHBoxLayout;
    m_classNameEdit = new QLineEdit;
    m_classNameEdit->setPlaceholderText("Enter class name (e.g., Class A, Grade 5B...)");
    
    m_gradeCombo = new QComboBox;
    m_gradeCombo->addItems({"Grade 1", "Grade 2", "Grade 3", "Grade 4", "Grade 5", 
                           "Grade 6", "Grade 7", "Grade 8", "Grade 9", "Grade 10",
                           "Grade 11", "Grade 12"});
    
    QPushButton *addClassBtn = new QPushButton("➕ Add Class");
    QPushButton *removeClassBtn = new QPushButton("➖ Remove");
    
    inputLayout->addWidget(new QLabel("Class Name:"));
    inputLayout->addWidget(m_classNameEdit);
    inputLayout->addWidget(new QLabel("Grade:"));
    inputLayout->addWidget(m_gradeCombo);
    inputLayout->addWidget(addClassBtn);
    inputLayout->addWidget(removeClassBtn);
    
    m_classesList = new QListWidget;
    m_classesList->setAlternatingRowColors(true);
    
    classLayout->addLayout(inputLayout);
    classLayout->addWidget(m_classesList);
    
    layout->addWidget(titleLabel);
    layout->addWidget(classGroup);
    
    // Connect signals
    connect(addClassBtn, &QPushButton::clicked, this, &SurveyDialog::addClass);
    connect(removeClassBtn, &QPushButton::clicked, this, &SurveyDialog::removeSelectedClass);
    connect(m_classNameEdit, &QLineEdit::returnPressed, this, &SurveyDialog::addClass);
    
    m_stackedWidget->addWidget(page);
}

void SurveyDialog::setupPage5()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QLabel *titleLabel = new QLabel("🔗 Match Teachers with Their Expertise!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageSubtitle");
    
    QGroupBox *assignmentGroup = new QGroupBox("Teacher-Subject Assignments 🎯");
    QVBoxLayout *assignmentLayout = new QVBoxLayout(assignmentGroup);
    
    // Teacher selection
    QHBoxLayout *teacherSelectLayout = new QHBoxLayout;
    teacherSelectLayout->addWidget(new QLabel("Select Teacher:"));
    m_teacherCombo = new QComboBox;
    teacherSelectLayout->addWidget(m_teacherCombo);
    
    // Subject assignment area
    QHBoxLayout *subjectAssignLayout = new QHBoxLayout;
    
    QGroupBox *availableGroup = new QGroupBox("📚 Available Subjects");
    QVBoxLayout *availableLayout = new QVBoxLayout(availableGroup);
    m_availableSubjects = new QListWidget;
    m_availableSubjects->setSelectionMode(QListWidget::MultiSelection);
    availableLayout->addWidget(m_availableSubjects);
    
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    QPushButton *assignBtn = new QPushButton("➡️ Assign");
    QPushButton *unassignBtn = new QPushButton("⬅️ Remove");
    buttonLayout->addStretch();
    buttonLayout->addWidget(assignBtn);
    buttonLayout->addWidget(unassignBtn);
    buttonLayout->addStretch();
    
    QGroupBox *assignedGroup = new QGroupBox("✅ Assigned Subjects");
    QVBoxLayout *assignedLayout = new QVBoxLayout(assignedGroup);
    m_assignedSubjects = new QListWidget;
    m_assignedSubjects->setSelectionMode(QListWidget::MultiSelection);
    assignedLayout->addWidget(m_assignedSubjects);
    
    subjectAssignLayout->addWidget(availableGroup);
    subjectAssignLayout->addLayout(buttonLayout);
    subjectAssignLayout->addWidget(assignedGroup);
    
    assignmentLayout->addLayout(teacherSelectLayout);
    assignmentLayout->addLayout(subjectAssignLayout);
    
    layout->addWidget(titleLabel);
    layout->addWidget(assignmentGroup);
    
    // Connect signals
    connect(m_teacherCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &SurveyDialog::onTeacherSelectionChanged);
    connect(assignBtn, &QPushButton::clicked, this, &SurveyDialog::addSubjectToTeacher);
    connect(unassignBtn, &QPushButton::clicked, this, &SurveyDialog::removeSubjectFromTeacher);
    
    m_stackedWidget->addWidget(page);
}

void SurveyDialog::setupPage6()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QLabel *titleLabel = new QLabel("⏰ Set Your School Schedule!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageSubtitle");
    
    QGroupBox *timeGroup = new QGroupBox("Time Configuration ⚙️");
    QGridLayout *timeLayout = new QGridLayout(timeGroup);
    
    // School timing
    timeLayout->addWidget(new QLabel("🌅 School Start Time:"), 0, 0);
    m_schoolStartTime = new QTimeEdit(QTime(8, 0));
    m_schoolStartTime->setDisplayFormat("hh:mm AP");
    timeLayout->addWidget(m_schoolStartTime, 0, 1);
    
    timeLayout->addWidget(new QLabel("🌇 School End Time:"), 1, 0);
    m_schoolEndTime = new QTimeEdit(QTime(15, 0));
    m_schoolEndTime->setDisplayFormat("hh:mm AP");
    timeLayout->addWidget(m_schoolEndTime, 1, 1);
    
    // Period settings
    timeLayout->addWidget(new QLabel("📖 Period Duration:"), 2, 0);
    m_periodDuration = new QSpinBox;
    m_periodDuration->setRange(30, 120);
    m_periodDuration->setValue(45);
    m_periodDuration->setSuffix(" minutes");
    timeLayout->addWidget(m_periodDuration, 2, 1);
    
    // Break settings
    timeLayout->addWidget(new QLabel("☕ Break Start Time:"), 3, 0);
    m_breakStartTime = new QTimeEdit(QTime(10, 30));
    m_breakStartTime->setDisplayFormat("hh:mm AP");
    timeLayout->addWidget(m_breakStartTime, 3, 1);
    
    timeLayout->addWidget(new QLabel("⏱️ Break Duration:"), 4, 0);
    m_breakDuration = new QSpinBox;
    m_breakDuration->setRange(10, 60);
    m_breakDuration->setValue(15);
    m_breakDuration->setSuffix(" minutes");
    timeLayout->addWidget(m_breakDuration, 4, 1);
    
    // Lunch settings
    timeLayout->addWidget(new QLabel("🍽️ Lunch Start Time:"), 5, 0);
    m_lunchStartTime = new QTimeEdit(QTime(12, 30));
    m_lunchStartTime->setDisplayFormat("hh:mm AP");
    timeLayout->addWidget(m_lunchStartTime, 5, 1);
    
    timeLayout->addWidget(new QLabel("🥪 Lunch Duration:"), 6, 0);
    m_lunchDuration = new QSpinBox;
    m_lunchDuration->setRange(20, 90);
    m_lunchDuration->setValue(30);
    m_lunchDuration->setSuffix(" minutes");
    timeLayout->addWidget(m_lunchDuration, 6, 1);
    
    // Workload limits
    timeLayout->addWidget(new QLabel("📅 Max Periods Per Day:"), 7, 0);
    m_maxPeriodsPerDay = new QSpinBox;
    m_maxPeriodsPerDay->setRange(4, 12);
    m_maxPeriodsPerDay->setValue(8);
    m_maxPeriodsPerDay->setSuffix(" periods");
    timeLayout->addWidget(m_maxPeriodsPerDay, 7, 1);
    
    timeLayout->addWidget(new QLabel("👨‍🏫 Max Periods Per Teacher Per Day:"), 8, 0);
    m_maxPeriodsPerTeacher = new QSpinBox;
    m_maxPeriodsPerTeacher->setRange(2, 10);
    m_maxPeriodsPerTeacher->setValue(6);
    m_maxPeriodsPerTeacher->setSuffix(" periods");
    timeLayout->addWidget(m_maxPeriodsPerTeacher, 8, 1);
    
    layout->addWidget(titleLabel);
    layout->addWidget(timeGroup);
    layout->addStretch();
    
    m_stackedWidget->addWidget(page);
}

void SurveyDialog::setupPage7()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);
    
    QLabel *titleLabel = new QLabel("🎊 Ready to Generate Your Schedule!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("pageSubtitle");
    
    QTextEdit *summaryText = new QTextEdit;
    summaryText->setReadOnly(true);
    summaryText->setMaximumHeight(200);
    summaryText->setHtml(
        "<h3>🎯 Configuration Summary:</h3>"
        "<p><b>👨‍🏫 Teachers:</b> Will be populated dynamically</p>"
        "<p><b>📚 Subjects:</b> Will be populated dynamically</p>"
        "<p><b>🏫 Classes:</b> Will be populated dynamically</p>"
        "<p><b>⏰ Schedule:</b> Fully randomized and optimized!</p>"
        "<br><p><i>✨ Your personalized schedule will be generated with smart conflict resolution!</i></p>"
    );
    
    QLabel *readyLabel = new QLabel(
        "🚀 Everything looks great! Click the button below to generate your awesome schedule.\n\n"
        "The Smart Mavi Manager will:\n"
        "• 🎲 Randomly assign teachers to time slots\n"
        "• 🔄 Ensure no conflicts between teachers\n"
        "• ⚖️ Balance workloads fairly\n"
        "• 📊 Create a beautiful printable schedule\n\n"
        "Ready to see the magic happen? ✨"
    );
    readyLabel->setAlignment(Qt::AlignCenter);
    readyLabel->setWordWrap(true);
    readyLabel->setObjectName("readyText");
    
    layout->addWidget(titleLabel);
    layout->addWidget(summaryText);
    layout->addWidget(readyLabel);
    layout->addStretch();
    
    m_stackedWidget->addWidget(page);
}

void SurveyDialog::nextPage()
{
    if (m_currentPage < TOTAL_PAGES - 1) {
        m_currentPage++;
        m_stackedWidget->setCurrentIndex(m_currentPage);
        updateProgress();
        animatePageTransition();
    }
}

void SurveyDialog::previousPage()
{
    if (m_currentPage > 0) {
        m_currentPage--;
        m_stackedWidget->setCurrentIndex(m_currentPage);
        updateProgress();
        animatePageTransition();
    }
}

void SurveyDialog::addTeacher()
{
    QString name = m_teacherNameEdit->text().trimmed();
    if (!name.isEmpty()) {
        Teacher teacher(name);
        teacher.setId(m_teachers.size());
        m_teachers.append(teacher);
        
        m_teachersList->addItem(QString("👨‍🏫 %1").arg(name));
        m_teacherNameEdit->clear();
        m_teacherNameEdit->setFocus();
    }
}

void SurveyDialog::addSubject()
{
    QString name = m_subjectNameEdit->text().trimmed();
    if (!name.isEmpty()) {
        Subject subject(name);
        subject.setId(m_subjects.size());
        m_subjects.append(subject);
        
        m_subjectsList->addItem(QString("📚 %1").arg(name));
        m_subjectNameEdit->clear();
        m_subjectNameEdit->setFocus();
    }
}

void SurveyDialog::addClass()
{
    QString name = m_classNameEdit->text().trimmed();
    QString grade = m_gradeCombo->currentText();
    if (!name.isEmpty()) {
        ClassInfo classInfo(name);
        classInfo.setId(m_classes.size());
        classInfo.setGrade(grade);
        m_classes.append(classInfo);
        
        m_classesList->addItem(QString("🏫 %1 (%2)").arg(name).arg(grade));
        m_classNameEdit->clear();
        m_classNameEdit->setFocus();
    }
}

void SurveyDialog::removeSelectedTeacher()
{
    int row = m_teachersList->currentRow();
    if (row >= 0 && row < m_teachers.size()) {
        m_teachers.removeAt(row);
        delete m_teachersList->takeItem(row);
    }
}

void SurveyDialog::removeSelectedSubject()
{
    int row = m_subjectsList->currentRow();
    if (row >= 0 && row < m_subjects.size()) {
        m_subjects.removeAt(row);
        delete m_subjectsList->takeItem(row);
    }
}

void SurveyDialog::removeSelectedClass()
{
    int row = m_classesList->currentRow();
    if (row >= 0 && row < m_classes.size()) {
        m_classes.removeAt(row);
        delete m_classesList->takeItem(row);
    }
}

void SurveyDialog::onTeacherSelectionChanged()
{
    // Update available and assigned subjects for selected teacher
    int teacherIndex = m_teacherCombo->currentIndex();
    if (teacherIndex >= 0 && teacherIndex < m_teachers.size()) {
        m_availableSubjects->clear();
        m_assignedSubjects->clear();
        
        Teacher& teacher = m_teachers[teacherIndex];
        
        for (const auto& subject : m_subjects) {
            if (teacher.teachesSubject(subject)) {
                m_assignedSubjects->addItem(subject.getName());
            } else {
                m_availableSubjects->addItem(subject.getName());
            }
        }
    }
}

void SurveyDialog::addSubjectToTeacher()
{
    int teacherIndex = m_teacherCombo->currentIndex();
    if (teacherIndex >= 0 && teacherIndex < m_teachers.size()) {
        QList<QListWidgetItem*> selectedItems = m_availableSubjects->selectedItems();
        
        for (QListWidgetItem* item : selectedItems) {
            QString subjectName = item->text();
            
            // Find subject by name
            for (const auto& subject : m_subjects) {
                if (subject.getName() == subjectName) {
                    m_teachers[teacherIndex].addSubject(subject);
                    break;
                }
            }
        }
        
        onTeacherSelectionChanged(); // Refresh lists
    }
}

void SurveyDialog::removeSubjectFromTeacher()
{
    int teacherIndex = m_teacherCombo->currentIndex();
    if (teacherIndex >= 0 && teacherIndex < m_teachers.size()) {
        QList<QListWidgetItem*> selectedItems = m_assignedSubjects->selectedItems();
        
        for (QListWidgetItem* item : selectedItems) {
            QString subjectName = item->text();
            
            // Find subject by name
            for (const auto& subject : m_subjects) {
                if (subject.getName() == subjectName) {
                    m_teachers[teacherIndex].removeSubject(subject);
                    break;
                }
            }
        }
        
        onTeacherSelectionChanged(); // Refresh lists
    }
}

void SurveyDialog::finishSurvey()
{
    // Validate data
    if (m_teachers.isEmpty() || m_subjects.isEmpty() || m_classes.isEmpty()) {
        QMessageBox::warning(this, "Incomplete Data", 
                           "Please make sure you have added teachers, subjects, and classes!");
        return;
    }
    
    // Check if all teachers have subjects assigned
    bool allTeachersHaveSubjects = true;
    for (const auto& teacher : m_teachers) {
        if (teacher.getSubjects().isEmpty()) {
            allTeachersHaveSubjects = false;
            break;
        }
    }
    
    if (!allTeachersHaveSubjects) {
        QMessageBox::warning(this, "Assignment Incomplete", 
                           "Please assign at least one subject to each teacher!");
        return;
    }
    
    showSuccessMessage();
    accept();
}

void SurveyDialog::updateProgress()
{
    m_progressBar->setValue(m_currentPage);
    
    // Update navigation buttons
    m_backButton->setEnabled(m_currentPage > 0);
    m_nextButton->setVisible(m_currentPage < TOTAL_PAGES - 1);
    m_finishButton->setVisible(m_currentPage == TOTAL_PAGES - 1);
    
    // Update page titles
    QStringList titles = {
        "Welcome to Smart Mavi Manager! 🚀",
        "👨‍🏫 Add Your Teachers",
        "📚 Add Your Subjects", 
        "🏫 Add Your Classes",
        "🔗 Assign Subjects to Teachers",
        "⏰ Configure Time Settings",
        "🎊 Ready to Generate!"
    };
    
    if (m_currentPage < titles.size()) {
        m_pageTitle->setText(titles[m_currentPage]);
    }
    
    // Update teacher combo on page 5
    if (m_currentPage == 4 && m_teacherCombo) { // Page 5 (0-indexed = 4)
        m_teacherCombo->clear();
        for (const auto& teacher : m_teachers) {
            m_teacherCombo->addItem(teacher.getName());
        }
        if (!m_teachers.isEmpty()) {
            onTeacherSelectionChanged();
        }
    }
}

void SurveyDialog::animatePageTransition()
{
    // Simple fade effect for page transitions
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
    m_stackedWidget->setGraphicsEffect(effect);
    
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(300);
    animation->setStartValue(0.3);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SurveyDialog::applyModernStyling()
{
    setStyleSheet(
        "QDialog {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #f0f8ff, stop:1 #e6f3ff);"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QLabel#pageTitle {"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    padding: 15px;"
        "    background: rgba(255, 255, 255, 0.8);"
        "    border-radius: 12px;"
        "    margin: 10px;"
        "}"
        "QLabel#pageSubtitle {"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    color: #34495e;"
        "    padding: 10px;"
        "}"
        "QLabel#welcomeText, QLabel#readyText {"
        "    font-size: 14px;"
        "    color: #2c3e50;"
        "    background: rgba(255, 255, 255, 0.9);"
        "    padding: 20px;"
        "    border-radius: 10px;"
        "    border: 2px solid #3498db;"
        "}"
        "QGroupBox {"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    border: 2px solid #3498db;"
        "    border-radius: 8px;"
        "    margin: 10px 0;"
        "    padding-top: 15px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 20px;"
        "    padding: 0 10px 0 10px;"
        "    background: rgba(255, 255, 255, 0.9);"
        "    border-radius: 4px;"
        "}"
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #3498db, stop:1 #2980b9);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 8px 16px;"
        "    font-weight: bold;"
        "    font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #5dade2, stop:1 #3498db);"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #2980b9, stop:1 #1f618d);"
        "}"
        "QSpinBox, QTimeEdit, QLineEdit, QComboBox {"
        "    padding: 8px;"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 4px;"
        "    font-size: 12px;"
        "    background: white;"
        "}"
        "QSpinBox:focus, QTimeEdit:focus, QLineEdit:focus, QComboBox:focus {"
        "    border-color: #3498db;"
        "}"
        "QListWidget {"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 4px;"
        "    background: white;"
        "    alternate-background-color: #ecf0f1;"
        "}"
        "QProgressBar {"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 8px;"
        "    text-align: center;"
        "    font-weight: bold;"
        "}"
        "QProgressBar::chunk {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "                               stop:0 #27ae60, stop:1 #2ecc71);"
        "    border-radius: 6px;"
        "}"
    );
}

void SurveyDialog::showSuccessMessage()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Success! 🎉");
    msgBox.setText("🎊 Survey Completed Successfully!");
    msgBox.setInformativeText("Your Smart Mavi Manager is now ready to generate an amazing schedule!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

ScheduleConfig SurveyDialog::getScheduleConfig() const
{
    ScheduleConfig config;
    config.teachers = m_teachers;
    config.subjects = m_subjects;
    config.classes = m_classes;
    config.schoolStartTime = m_schoolStartTime->time();
    config.schoolEndTime = m_schoolEndTime->time();
    config.periodDuration = m_periodDuration->value();
    config.breakStartTime = m_breakStartTime->time();
    config.breakDuration = m_breakDuration->value();
    config.lunchStartTime = m_lunchStartTime->time();
    config.lunchDuration = m_lunchDuration->value();
    config.maxPeriodsPerDay = m_maxPeriodsPerDay->value();
    config.maxPeriodsPerTeacherPerDay = m_maxPeriodsPerTeacher->value();
    
    return config;
}
