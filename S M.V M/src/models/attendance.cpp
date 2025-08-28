#include "models/attendance.h"
#include <QDateTime>

Attendance::Attendance()
    : m_id(0)
    , m_studentId(0)
    , m_classId(0)
    , m_date(QDate::currentDate())
    , m_status(Present)
    , m_markedAt(QDateTime::currentDateTime())
{
}

Attendance::Attendance(int id, int studentId, int classId, const QDate &date, 
                       Status status, const QString &remarks)
    : m_id(id)
    , m_studentId(studentId)
    , m_classId(classId)
    , m_date(date)
    , m_status(status)
    , m_remarks(remarks)
    , m_markedAt(QDateTime::currentDateTime())
{
}

QString Attendance::toString() const
{
    return QString("Attendance{id=%1, studentId=%2, classId=%3, date=%4, status=%5}")
           .arg(m_id)
           .arg(m_studentId)
           .arg(m_classId)
           .arg(m_date.toString("yyyy-MM-dd"))
           .arg(statusToString(m_status));
}

bool Attendance::isValid() const
{
    return m_studentId > 0 && m_classId > 0 && m_date.isValid() && isValidStatus(m_status);
}

QString Attendance::getStatusString() const
{
    return statusToString(m_status);
}

bool Attendance::isPresent() const
{
    return m_status == Present;
}

bool Attendance::isAbsent() const
{
    return m_status == Absent;
}

bool Attendance::isOnLeave() const
{
    return m_status == Leave;
}

bool Attendance::isLate() const
{
    return m_status == Late;
}

QString Attendance::statusToString(Status status)
{
    switch (status) {
        case Present: return "Present";
        case Absent: return "Absent";
        case Leave: return "Leave";
        case Late: return "Late";
        default: return "Unknown";
    }
}

Attendance::Status Attendance::stringToStatus(const QString &statusStr)
{
    if (statusStr.toLower() == "present") return Present;
    if (statusStr.toLower() == "absent") return Absent;
    if (statusStr.toLower() == "leave") return Leave;
    if (statusStr.toLower() == "late") return Late;
    return Present; // Default to present
}

QList<QString> Attendance::getStatusList()
{
    return {"Present", "Absent", "Leave", "Late"};
}

bool Attendance::isValidStatus(Status status)
{
    return status >= Present && status <= Late;
}

bool Attendance::isValidDate(const QDate &date)
{
    if (!date.isValid()) return false;
    
    QDate currentDate = QDate::currentDate();
    QDate minDate = currentDate.addYears(-1); // Allow attendance for past year
    QDate maxDate = currentDate.addDays(1);   // Allow attendance for today and tomorrow
    
    return date >= minDate && date <= maxDate;
}


