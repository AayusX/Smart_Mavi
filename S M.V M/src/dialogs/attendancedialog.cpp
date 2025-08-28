#include "dialogs/attendancedialog.h"
#include <QApplication>
#include <QStyle>

AttendanceDialog::AttendanceDialog(int classId, const QDate &date, QWidget *parent)
    : QDialog(parent)
    , m_classId(classId)
    , m_date(date)
    , m_hasChanges(false)
{
    setWindowTitle("Mark Attendance");
    setModal(true);
    setMinimumSize(800, 600);
    
    setupUI();
    loadStudents();
    setupConnections();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

QList<Attendance> AttendanceDialog::getAttendanceList() const
{
    return m_attendanceList;
}

bool AttendanceDialog::hasChanges() const
{
    return m_hasChanges;
}

void AttendanceDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("Mark Student Attendance");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Header Information
    QGroupBox *headerGroup = new QGroupBox("Attendance Information");
    headerGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *headerLayout = new QGridLayout(headerGroup);
    
    m_classLabel = new QLabel("Class: Grade 1");
    m_classLabel->setStyleSheet("font-weight: bold; color: #2c3e50;");
    
    m_dateLabel = new QLabel("Date: " + m_date.toString("dddd, MMMM dd, yyyy"));
    m_dateLabel->setStyleSheet("font-weight: bold; color: #2c3e50;");
    
    m_totalStudentsLabel = new QLabel("Total Students: 0");
    m_totalStudentsLabel->setStyleSheet("font-weight: bold; color: #3498db;");
    
    headerLayout->addWidget(m_classLabel, 0, 0);
    headerLayout->addWidget(m_dateLabel, 0, 1);
    headerLayout->addWidget(m_totalStudentsLabel, 0, 2);
    
    mainLayout->addWidget(headerGroup);
    
    // Attendance Statistics
    QGroupBox *statsGroup = new QGroupBox("Attendance Statistics");
    statsGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QHBoxLayout *statsLayout = new QHBoxLayout(statsGroup);
    
    m_presentLabel = new QLabel("Present: 0");
    m_presentLabel->setStyleSheet("font-weight: bold; color: #27ae60; padding: 5px; background-color: #d5f4e6; border-radius: 4px;");
    
    m_absentLabel = new QLabel("Absent: 0");
    m_absentLabel->setStyleSheet("font-weight: bold; color: #e74c3c; padding: 5px; background-color: #fadbd8; border-radius: 4px;");
    
    m_leaveLabel = new QLabel("Leave: 0");
    m_leaveLabel->setStyleSheet("font-weight: bold; color: #f39c12; padding: 5px; background-color: #fdeaa7; border-radius: 4px;");
    
    m_lateLabel = new QLabel("Late: 0");
    m_lateLabel->setStyleSheet("font-weight: bold; color: #9b59b6; padding: 5px; background-color: #e8d5f2; border-radius: 4px;");
    
    statsLayout->addWidget(m_presentLabel);
    statsLayout->addWidget(m_absentLabel);
    statsLayout->addWidget(m_leaveLabel);
    statsLayout->addWidget(m_lateLabel);
    statsLayout->addStretch();
    
    mainLayout->addWidget(statsGroup);
    
    // Bulk Actions
    QGroupBox *actionsGroup = new QGroupBox("Bulk Actions");
    actionsGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QHBoxLayout *actionsLayout = new QHBoxLayout(actionsGroup);
    
    m_markAllPresentBtn = new QPushButton("Mark All Present");
    m_markAllPresentBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 8px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #229954; }");
    
    m_markAllAbsentBtn = new QPushButton("Mark All Absent");
    m_markAllAbsentBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 8px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #c0392b; }");
    
    m_markAllLeaveBtn = new QPushButton("Mark All Leave");
    m_markAllLeaveBtn->setStyleSheet("QPushButton { background-color: #f39c12; color: white; padding: 8px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #e67e22; }");
    
    actionsLayout->addWidget(m_markAllPresentBtn);
    actionsLayout->addWidget(m_markAllAbsentBtn);
    actionsLayout->addWidget(m_markAllLeaveBtn);
    actionsLayout->addStretch();
    
    mainLayout->addWidget(actionsGroup);
    
    // Student Table
    QGroupBox *tableGroup = new QGroupBox("Student List");
    tableGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);
    
    m_studentTable = new QTableWidget();
    m_studentTable->setColumnCount(4);
    m_studentTable->setHorizontalHeaderLabels({"Roll No", "Name", "Status", "Remarks"});
    m_studentTable->setAlternatingRowColors(true);
    m_studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_studentTable->horizontalHeader()->setStretchLastSection(true);
    m_studentTable->setStyleSheet("QTableWidget { gridline-color: #bdc3c7; } QHeaderView::section { background-color: #ecf0f1; padding: 8px; border: 1px solid #bdc3c7; font-weight: bold; }");
    
    tableLayout->addWidget(m_studentTable);
    
    mainLayout->addWidget(tableGroup);
    
    // Remarks
    QGroupBox *remarksGroup = new QGroupBox("General Remarks");
    remarksGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QVBoxLayout *remarksLayout = new QVBoxLayout(remarksGroup);
    
    m_remarksEdit = new QTextEdit();
    m_remarksEdit->setPlaceholderText("Enter any general remarks for today's attendance...");
    m_remarksEdit->setMaximumHeight(80);
    m_remarksEdit->setStyleSheet("QTextEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    remarksLayout->addWidget(m_remarksEdit);
    
    mainLayout->addWidget(remarksGroup);
    
    // Buttons
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    m_saveButton = m_buttonBox->button(QDialogButtonBox::Save);
    m_cancelButton = m_buttonBox->button(QDialogButtonBox::Cancel);
    
    m_saveButton->setText("Save Attendance");
    m_saveButton->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #229954; }");
    m_cancelButton->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #c0392b; }");
    
    mainLayout->addWidget(m_buttonBox);
}

void AttendanceDialog::loadStudents()
{
    // In a real implementation, this would load students from the database
    // For now, we'll add some sample students
    m_students.clear();
    m_students.append(Student(1, "ST001", "Aarav Sharma", m_classId, "Rajesh Sharma", "+977111111111", "rajesh@email.com", "Kathmandu", QDate(2017, 5, 15), "Male", QDate(2024, 1, 1)));
    m_students.append(Student(2, "ST002", "Zara Khan", m_classId, "Ahmed Khan", "+977222222222", "ahmed@email.com", "Lalitpur", QDate(2017, 8, 20), "Female", QDate(2024, 1, 1)));
    m_students.append(Student(3, "ST003", "Arjun Patel", m_classId, "Vikram Patel", "+977333333333", "vikram@email.com", "Bhaktapur", QDate(2017, 3, 10), "Male", QDate(2024, 1, 1)));
    
    // Populate table
    m_studentTable->setRowCount(m_students.size());
    
    for (int i = 0; i < m_students.size(); ++i) {
        const Student &student = m_students.at(i);
        
        // Roll No
        QTableWidgetItem *rollNoItem = new QTableWidgetItem(student.getRollNo());
        rollNoItem->setFlags(rollNoItem->flags() & ~Qt::ItemIsEditable);
        m_studentTable->setItem(i, 0, rollNoItem);
        
        // Name
        QTableWidgetItem *nameItem = new QTableWidgetItem(student.getName());
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        m_studentTable->setItem(i, 1, nameItem);
        
        // Status Combo Box
        QComboBox *statusCombo = new QComboBox();
        statusCombo->addItems({"Present", "Absent", "Leave", "Late"});
        statusCombo->setCurrentText("Present");
        statusCombo->setStyleSheet("QComboBox { padding: 5px; border: 1px solid #bdc3c7; border-radius: 3px; }");
        m_studentTable->setCellWidget(i, 2, statusCombo);
        
        // Remarks
        QTableWidgetItem *remarksItem = new QTableWidgetItem("");
        m_studentTable->setItem(i, 3, remarksItem);
        
        // Connect status change signal
        connect(statusCombo, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
                [this, i](const QString &text) {
                    onStudentStatusChanged(i, 2);
                });
    }
    
    m_totalStudentsLabel->setText(QString("Total Students: %1").arg(m_students.size()));
    updateAttendanceCount();
}

void AttendanceDialog::setupConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &AttendanceDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    connect(m_markAllPresentBtn, &QPushButton::clicked, this, &AttendanceDialog::markAllPresent);
    connect(m_markAllAbsentBtn, &QPushButton::clicked, this, &AttendanceDialog::markAllAbsent);
    connect(m_markAllLeaveBtn, &QPushButton::clicked, this, &AttendanceDialog::markAllLeave);
}

void AttendanceDialog::accept()
{
    saveAttendance();
    QDialog::accept();
}

void AttendanceDialog::markAllPresent()
{
    for (int i = 0; i < m_studentTable->rowCount(); ++i) {
        QComboBox *statusCombo = qobject_cast<QComboBox*>(m_studentTable->cellWidget(i, 2));
        if (statusCombo) {
            statusCombo->setCurrentText("Present");
        }
    }
    m_hasChanges = true;
    updateAttendanceCount();
}

void AttendanceDialog::markAllAbsent()
{
    for (int i = 0; i < m_studentTable->rowCount(); ++i) {
        QComboBox *statusCombo = qobject_cast<QComboBox*>(m_studentTable->cellWidget(i, 2));
        if (statusCombo) {
            statusCombo->setCurrentText("Absent");
        }
    }
    m_hasChanges = true;
    updateAttendanceCount();
}

void AttendanceDialog::markAllLeave()
{
    for (int i = 0; i < m_studentTable->rowCount(); ++i) {
        QComboBox *statusCombo = qobject_cast<QComboBox*>(m_studentTable->cellWidget(i, 2));
        if (statusCombo) {
            statusCombo->setCurrentText("Leave");
        }
    }
    m_hasChanges = true;
    updateAttendanceCount();
}

void AttendanceDialog::onStudentStatusChanged(int row, int column)
{
    Q_UNUSED(column)
    
    if (row >= 0 && row < m_studentTable->rowCount()) {
        m_hasChanges = true;
        updateAttendanceCount();
    }
}

void AttendanceDialog::saveAttendance()
{
    m_attendanceList.clear();
    
    for (int i = 0; i < m_studentTable->rowCount(); ++i) {
        const Student &student = m_students.at(i);
        QComboBox *statusCombo = qobject_cast<QComboBox*>(m_studentTable->cellWidget(i, 2));
        QTableWidgetItem *remarksItem = m_studentTable->item(i, 3);
        
        if (statusCombo) {
            QString statusText = statusCombo->currentText();
            Attendance::Status status = Attendance::Present;
            
            if (statusText == "Absent") status = Attendance::Absent;
            else if (statusText == "Leave") status = Attendance::Leave;
            else if (statusText == "Late") status = Attendance::Late;
            
            QString remarks = remarksItem ? remarksItem->text() : "";
            
            Attendance attendance(
                0, // ID will be set by database
                student.getId(),
                m_classId,
                m_date,
                status,
                remarks
            );
            
            m_attendanceList.append(attendance);
        }
    }
}

void AttendanceDialog::updateAttendanceCount()
{
    int present = 0, absent = 0, leave = 0, late = 0;
    
    for (int i = 0; i < m_studentTable->rowCount(); ++i) {
        QComboBox *statusCombo = qobject_cast<QComboBox*>(m_studentTable->cellWidget(i, 2));
        if (statusCombo) {
            QString status = statusCombo->currentText();
            if (status == "Present") present++;
            else if (status == "Absent") absent++;
            else if (status == "Leave") leave++;
            else if (status == "Late") late++;
        }
    }
    
    m_presentLabel->setText(QString("Present: %1").arg(present));
    m_absentLabel->setText(QString("Absent: %1").arg(absent));
    m_leaveLabel->setText(QString("Leave: %1").arg(leave));
    m_lateLabel->setText(QString("Late: %1").arg(late));
}

QString AttendanceDialog::getStatusString(Attendance::Status status)
{
    switch (status) {
        case Attendance::Present: return "Present";
        case Attendance::Absent: return "Absent";
        case Attendance::Leave: return "Leave";
        case Attendance::Late: return "Late";
        default: return "Unknown";
    }
}

QColor AttendanceDialog::getStatusColor(Attendance::Status status)
{
    switch (status) {
        case Attendance::Present: return QColor("#27ae60");
        case Attendance::Absent: return QColor("#e74c3c");
        case Attendance::Leave: return QColor("#f39c12");
        case Attendance::Late: return QColor("#9b59b6");
        default: return QColor("#7f8c8d");
    }
}
