#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QString>
#include <QDate>
#include <QObject>

class Attendance
{

public:
    enum Status {
        Present = 0,
        Absent = 1,
        Leave = 2,
        Late = 3
    };
    
    explicit Attendance();
    Attendance(int id, int studentId, int classId, const QDate &date, 
               Status status, const QString &remarks = "");
    
    // Getters
    int getId() const { return m_id; }
    int getStudentId() const { return m_studentId; }
    int getClassId() const { return m_classId; }
    QDate getDate() const { return m_date; }
    Status getStatus() const { return m_status; }
    QString getRemarks() const { return m_remarks; }
    QDateTime getMarkedAt() const { return m_markedAt; }
    
    // Setters
    void setId(int id) { m_id = id; }
    void setStudentId(int studentId) { m_studentId = studentId; }
    void setClassId(int classId) { m_classId = classId; }
    void setDate(const QDate &date) { m_date = date; }
    void setStatus(Status status) { m_status = status; }
    void setRemarks(const QString &remarks) { m_remarks = remarks; }
    void setMarkedAt(const QDateTime &markedAt) { m_markedAt = markedAt; }
    
    // Utility methods
    QString toString() const;
    bool isValid() const;
    QString getStatusString() const;
    bool isPresent() const;
    bool isAbsent() const;
    bool isOnLeave() const;
    bool isLate() const;
    
    // Static methods
    static QString statusToString(Status status);
    static Status stringToStatus(const QString &statusStr);
    static QList<QString> getStatusList();
    static bool isValidStatus(Status status);
    static bool isValidDate(const QDate &date);

private:
    int m_id;
    int m_studentId;
    int m_classId;
    QDate m_date;
    Status m_status;
    QString m_remarks;
    QDateTime m_markedAt;
};

// For QVariant support
Q_DECLARE_METATYPE(Attendance)

#endif // ATTENDANCE_H
