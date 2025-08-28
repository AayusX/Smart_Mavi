#ifndef ENHANCEDSTUDENT_H
#define ENHANCEDSTUDENT_H

#include "models/student.h"
#include <QPixmap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include <QStringList>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QTime>

class Grade
{
public:
    Grade() : m_subject(""), m_marks(0), m_maxMarks(100), m_grade(""), m_date(QDate::currentDate()) {}
    Grade(const QString &subject, int marks, int maxMarks, const QString &grade, const QDate &date = QDate::currentDate())
        : m_subject(subject), m_marks(marks), m_maxMarks(maxMarks), m_grade(grade), m_date(date) {}
    
    QString getSubject() const { return m_subject; }
    int getMarks() const { return m_marks; }
    int getMaxMarks() const { return m_maxMarks; }
    QString getGrade() const { return m_grade; }
    QDate getDate() const { return m_date; }
    double getPercentage() const { return (double)m_marks / m_maxMarks * 100.0; }
    
    void setSubject(const QString &subject) { m_subject = subject; }
    void setMarks(int marks) { m_marks = marks; }
    void setMaxMarks(int maxMarks) { m_maxMarks = maxMarks; }
    void setGrade(const QString &grade) { m_grade = grade; }
    void setDate(const QDate &date) { m_date = date; }
    
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    QString m_subject;
    int m_marks;
    int m_maxMarks;
    QString m_grade;
    QDate m_date;
};

class AttendanceRecord
{
public:
    AttendanceRecord() : m_date(QDate::currentDate()), m_isPresent(false), m_arrivalTime(QTime()), m_remarks("") {}
    AttendanceRecord(const QDate &date, bool present, const QTime &arrivalTime = QTime(), const QString &remarks = "")
        : m_date(date), m_isPresent(present), m_arrivalTime(arrivalTime), m_remarks(remarks) {}
    
    QDate getDate() const { return m_date; }
    bool isPresent() const { return m_isPresent; }
    QTime getArrivalTime() const { return m_arrivalTime; }
    QString getRemarks() const { return m_remarks; }
    
    void setDate(const QDate &date) { m_date = date; }
    void setPresent(bool present) { m_isPresent = present; }
    void setArrivalTime(const QTime &time) { m_arrivalTime = time; }
    void setRemarks(const QString &remarks) { m_remarks = remarks; }
    
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    QDate m_date;
    bool m_isPresent;
    QTime m_arrivalTime;
    QString m_remarks;
};

class EnhancedStudent : public Student
{
public:
    enum Status {
        Active = 0,
        Inactive = 1,
        Graduated = 2,
        Transferred = 3,
        Suspended = 4
    };

    explicit EnhancedStudent();
    EnhancedStudent(const Student &student);
    
    // Photo management
    QPixmap getPhoto() const { return m_photo; }
    void setPhoto(const QPixmap &photo) { m_photo = photo; }
    bool hasPhoto() const { return !m_photo.isNull(); }
    QString getPhotoPath() const { return m_photoPath; }
    void setPhotoPath(const QString &path);
    
    // Academic information
    double getCurrentGPA() const;
    double getSubjectAverage(const QString &subject) const;
    QString getCurrentGrade() const;
    QStringList getSubjects() const;
    
    // Grades management
    void addGrade(const Grade &grade);
    void updateGrade(const QString &subject, const Grade &grade);
    void removeGrade(const QString &subject, const QDate &date);
    QList<Grade> getGrades() const { return m_grades; }
    QList<Grade> getGradesBySubject(const QString &subject) const;
    QList<Grade> getGradesByDateRange(const QDate &start, const QDate &end) const;
    
    // Attendance management
    void addAttendanceRecord(const AttendanceRecord &record);
    QList<AttendanceRecord> getAttendanceRecords() const { return m_attendanceRecords; }
    QList<AttendanceRecord> getAttendanceByDateRange(const QDate &start, const QDate &end) const;
    double getAttendancePercentage(const QDate &start, const QDate &end) const;
    int getTotalPresent(const QDate &start, const QDate &end) const;
    int getTotalAbsent(const QDate &start, const QDate &end) const;
    
    // Performance analytics
    double getPerformanceTrend(const QDate &start, const QDate &end) const;
    QStringList getWeakSubjects() const;
    QStringList getStrongSubjects() const;
    double getImprovementRate() const;
    
    // Status management
    Status getStatus() const { return m_status; }
    void setStatus(Status status) { m_status = status; }
    QString getStatusString() const;
    static QStringList getStatusList();
    
    // Additional information
    QString getBloodType() const { return m_bloodType; }
    void setBloodType(const QString &bloodType) { m_bloodType = bloodType; }
    
    QString getAllergies() const { return m_allergies; }
    void setAllergies(const QString &allergies) { m_allergies = allergies; }
    
    QString getMedicalNotes() const { return m_medicalNotes; }
    void setMedicalNotes(const QString &notes) { m_medicalNotes = notes; }
    
    QString getEmergencyContact() const { return m_emergencyContact; }
    void setEmergencyContact(const QString &contact) { m_emergencyContact = contact; }
    
    QString getTransportMode() const { return m_transportMode; }
    void setTransportMode(const QString &mode) { m_transportMode = mode; }
    
    QString getHobbies() const { return m_hobbies; }
    void setHobbies(const QString &hobbies) { m_hobbies = hobbies; }
    
    // Parent portal access
    QString getParentPortalUsername() const { return m_parentPortalUsername; }
    void setParentPortalUsername(const QString &username) { m_parentPortalUsername = username; }
    
    QString getParentPortalPassword() const { return m_parentPortalPassword; }
    void setParentPortalPassword(const QString &password) { m_parentPortalPassword = password; }
    
    // Communication preferences
    bool isEmailNotificationEnabled() const { return m_enableEmailNotifications; }
    void setEmailNotificationEnabled(bool enabled) { m_enableEmailNotifications = enabled; }
    
    bool isSMSNotificationEnabled() const { return m_enableSMSNotifications; }
    void setSMSNotificationEnabled(bool enabled) { m_enableSMSNotifications = enabled; }
    
    // Data export/import
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
    QString toCSV() const;
    void fromCSV(const QString &csvLine);
    
    // Validation
    bool isValidForPromotion() const;
    QStringList getValidationErrors() const;
    
    // Statistics
    struct Statistics {
        double averageGrade;
        double attendanceRate;
        int totalGrades;
        int totalPresent;
        int totalAbsent;
        QString topSubject;
        QString weakestSubject;
        double improvementRate;
        int rank; // Class rank
        QString lastActive;
    };
    
    Statistics getStatistics() const;

private:
    // Photo data
    QPixmap m_photo;
    QString m_photoPath;
    
    // Academic data
    QList<Grade> m_grades;
    QList<AttendanceRecord> m_attendanceRecords;
    Status m_status;
    
    // Medical and personal information
    QString m_bloodType;
    QString m_allergies;
    QString m_medicalNotes;
    QString m_emergencyContact;
    QString m_transportMode;
    QString m_hobbies;
    
    // Parent portal
    QString m_parentPortalUsername;
    QString m_parentPortalPassword;
    
    // Communication preferences
    bool m_enableEmailNotifications;
    bool m_enableSMSNotifications;
    
    // Helper methods
    void calculateCurrentGPA();
    QString calculateLetterGrade(double percentage) const;
    void updatePerformanceMetrics();
};

// Student Profile Widget for enhanced display
class StudentProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentProfileWidget(const EnhancedStudent &student, QWidget *parent = nullptr);
    
    void updateStudent(const EnhancedStudent &student);
    EnhancedStudent getStudent() const { return m_student; }

signals:
    void studentUpdated(const EnhancedStudent &student);
    void editRequested();
    void deleteRequested();
    void viewGradesRequested();
    void viewAttendanceRequested();

private slots:
    void onEditClicked();
    void onDeleteClicked();
    void onPhotoClicked();
    void onGradesClicked();
    void onAttendanceClicked();

private:
    void setupUI();
    void setupPhotoSection();
    void setupBasicInfoSection();
    void setupAcademicSection();
    void setupContactSection();
    void setupActionButtons();
    void updateDisplays();
    
    EnhancedStudent m_student;
    
    // UI Components
    QLabel *m_photoLabel;
    QLabel *m_nameLabel;
    QLabel *m_rollNoLabel;
    QLabel *m_classLabel;
    QLabel *m_statusLabel;
    QLabel *m_gpaLabel;
    QLabel *m_attendanceLabel;
    QLabel *m_guardianLabel;
    QLabel *m_contactLabel;
    QLabel *m_emailLabel;
    
    QPushButton *m_editBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_gradesBtn;
    QPushButton *m_attendanceBtn;
    QPushButton *m_photoBtn;
    
    QProgressBar *m_attendanceProgress;
    QProgressBar *m_performanceProgress;
};

#endif // ENHANCEDSTUDENT_H
