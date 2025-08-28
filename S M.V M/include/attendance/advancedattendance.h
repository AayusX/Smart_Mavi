#ifndef ADVANCEDATTENDANCE_H
#define ADVANCEDATTENDANCE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QJsonObject>
#include <QFile>
#include <QRegularExpression>

class QNetworkAccessManager;

// Data structures for advanced attendance
struct AttendanceEntry {
    int id = 0;
    QString studentRoll;
    QString studentName;
    QString grade;
    QString section;
    QDate date;
    QTime timeIn;
    QTime timeOut;
    QString status = "Present";  // Present, Absent, Late, Excused
    QString method = "Manual";   // Manual, Biometric, RFID, Auto
    QString location;
    QString notes;
    QString markedBy;
};

struct AttendanceStats {
    int presentDays = 0;
    int absentDays = 0;
    int lateDays = 0;
    int excusedDays = 0;
    int totalDays = 0;
    double attendancePercentage = 0.0;
};

struct BiometricData {
    QString studentRoll;
    QString fingerprintHash;
    QString faceEncoding;
    QString rfidCode;
    bool active = true;
    QDateTime createdDate;
};

struct AttendanceRule {
    int id = 0;
    QString ruleName;
    QString ruleType;
    QString conditions;
    QString actions;
    int priority = 1;
    bool active = true;
    QString grade;
    QString section;
};

struct AttendanceAlert {
    QString studentRoll;
    QString studentName;
    QString grade;
    QString section;
    QString alertType;
    QString message;
    QString severity;
    QString parentPhone;
    QDateTime alertDate;
};

struct LeaveRequest {
    int id = 0;
    QString studentRoll;
    QString studentName;
    QDate fromDate;
    QDate toDate;
    QString reason;
    QString requestType;
    QString submittedBy;
    QString status = "Pending";
    QDateTime submittedDate;
};

class AdvancedAttendance : public QObject
{
    Q_OBJECT

public:
    explicit AdvancedAttendance(QObject *parent = nullptr);
    ~AdvancedAttendance();

    // Core attendance functions
    bool markAttendance(const AttendanceEntry &entry);
    bool markTimeOut(const QString &studentRoll, const QTime &timeOut);
    QList<AttendanceEntry> getAttendance(const QDate &date, const QString &grade = QString(), 
                                        const QString &section = QString());
    
    // Statistics and analytics
    AttendanceStats getAttendanceStats(const QString &studentRoll, const QDate &fromDate, const QDate &toDate);
    QMap<QString, AttendanceStats> getClassAttendanceStats(const QString &grade, const QString &section,
                                                          const QDate &fromDate, const QDate &toDate);
    
    // Biometric and advanced features
    bool setBiometricData(const QString &studentRoll, const BiometricData &data);
    BiometricData getBiometricData(const QString &studentRoll);
    bool verifyBiometric(const QString &biometricHash, const QString &method);
    
    // Rules and automation
    bool addAttendanceRule(const AttendanceRule &rule);
    QList<AttendanceRule> getAttendanceRules();
    void processAutoAttendance();
    
    // Reporting and export
    bool generateAttendanceReport(const QString &grade, const QString &section,
                                 const QDate &fromDate, const QDate &toDate);
    bool exportAttendanceData(const QString &filePath, const QString &format,
                             const QDate &fromDate, const QDate &toDate,
                             const QString &grade = QString(), const QString &section = QString());
    
    // Alerts and notifications
    QList<AttendanceAlert> getAttendanceAlerts();
    
    // Leave management
    bool addLeaveRequest(const LeaveRequest &request);
    QList<LeaveRequest> getPendingLeaveRequests();
    bool approveLeaveRequest(int requestId, const QString &approvedBy);
    
    // Utility functions
    QList<QString> getDefaultStudents(const QDate &date);
    bool bulkMarkAttendance(const QList<AttendanceEntry> &entries);
    
    // Database management
    bool createDatabaseTables();

signals:
    void attendanceMarked(const QString &studentRoll, const QString &status);
    void timeOutMarked(const QString &studentRoll, const QTime &timeOut);
    void reportGenerated(const QString &grade, const QString &section);
    void leaveRequestSubmitted(const QString &studentRoll);
    void leaveRequestApproved(int requestId);

private:
    QTimer *m_autoMarkTimer;
};

#endif // ADVANCEDATTENDANCE_H
