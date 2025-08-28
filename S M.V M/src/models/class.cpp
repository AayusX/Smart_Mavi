#include "models/class.h"
#include <QRegularExpression>

Class::Class()
    : m_id(0)
    , m_grade(0)
    , m_capacity(40)
    , m_teacherId(0)
    , m_isActive(true)
{
}

Class::Class(int id, const QString &name, int grade, int capacity,
             const QString &roomNumber, int teacherId,
             const QString &description)
    : m_id(id)
    , m_name(name)
    , m_grade(grade)
    , m_capacity(capacity)
    , m_roomNumber(roomNumber)
    , m_teacherId(teacherId)
    , m_description(description)
    , m_isActive(true)
{
}

QString Class::toString() const
{
    return QString("Class{id=%1, name='%2', grade=%3, capacity=%4}")
           .arg(m_id)
           .arg(m_name)
           .arg(m_grade)
           .arg(m_capacity);
}

bool Class::isValid() const
{
    return !m_name.isEmpty() && isValidGrade(m_grade) && isValidCapacity(m_capacity);
}

QString Class::getDisplayName() const
{
    return QString("Grade %1 - %2").arg(m_grade).arg(m_name);
}

bool Class::isFull() const
{
    // This would need to be implemented with actual student count from database
    return false;
}

int Class::getAvailableSeats() const
{
    // This would need to be implemented with actual student count from database
    return m_capacity;
}

QList<QString> Class::getGradeList()
{
    QList<QString> grades;
    for (int i = 1; i <= 12; ++i) {
        grades.append(QString::number(i));
    }
    return grades;
}

QString Class::getGradeName(int grade)
{
    switch (grade) {
        case 1: return "Grade 1";
        case 2: return "Grade 2";
        case 3: return "Grade 3";
        case 4: return "Grade 4";
        case 5: return "Grade 5";
        case 6: return "Grade 6";
        case 7: return "Grade 7";
        case 8: return "Grade 8";
        case 9: return "Grade 9";
        case 10: return "Grade 10";
        case 11: return "Grade 11";
        case 12: return "Grade 12";
        default: return QString("Grade %1").arg(grade);
    }
}

bool Class::isValidGrade(int grade)
{
    return grade >= 1 && grade <= 12;
}

bool Class::isValidCapacity(int capacity)
{
    return capacity > 0 && capacity <= 100; // Reasonable class size limit
}

bool Class::isValidRoomNumber(const QString &roomNumber)
{
    if (roomNumber.isEmpty()) return true; // Room number is optional
    
    // Room number should be alphanumeric and 2-10 characters long
    QRegularExpression roomRegex("^[A-Za-z0-9-]{2,10}$");
    return roomRegex.match(roomNumber).hasMatch();
}
