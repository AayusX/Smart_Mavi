#ifndef ATTENDANCEDIALOG_H
#define ATTENDANCEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QTableWidget>
#include <QHeaderView>
#include "models/attendance.h"
#include "models/student.h"

class AttendanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AttendanceDialog(int classId, const QDate &date, QWidget *parent = nullptr);
    
    QList<Attendance> getAttendanceList() const;
    bool hasChanges() const;

private slots:
    void accept() override;
    void markAllPresent();
    void markAllAbsent();
    void markAllLeave();
    void onStudentStatusChanged(int row, int column);
    void saveAttendance();

private:
    void setupUI();
    void loadStudents();
    void setupConnections();
    void updateAttendanceCount();
    
    // UI Components
    QLabel *m_classLabel;
    QLabel *m_dateLabel;
    QLabel *m_totalStudentsLabel;
    QLabel *m_presentLabel;
    QLabel *m_absentLabel;
    QLabel *m_leaveLabel;
    QLabel *m_lateLabel;
    
    QTableWidget *m_studentTable;
    QTextEdit *m_remarksEdit;
    
    QPushButton *m_markAllPresentBtn;
    QPushButton *m_markAllAbsentBtn;
    QPushButton *m_markAllLeaveBtn;
    
    QDialogButtonBox *m_buttonBox;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    
    // Data
    int m_classId;
    QDate m_date;
    QList<Student> m_students;
    QList<Attendance> m_attendanceList;
    bool m_hasChanges;
    
    // Helper methods
    void updateStudentStatus(int row, Attendance::Status status);
    QString getStatusString(Attendance::Status status);
    QColor getStatusColor(Attendance::Status status);
};

#endif // ATTENDANCEDIALOG_H
