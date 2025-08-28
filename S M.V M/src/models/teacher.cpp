#include "models/teacher.h"
#include <QRegularExpression>
#include <QDate>

Teacher::Teacher()
    : m_id(0)
    , m_assignedClass(0)
    , m_joinDate(QDate::currentDate())
    , m_isActive(true)
{
}

Teacher::Teacher(int id, const QString &name, const QString &subject, const QString &contact, 
                 int assignedClass, const QString &email, const QString &address, 
                 const QDate &joinDate)
    : m_id(id)
    , m_name(name)
    , m_subject(subject)
    , m_contact(contact)
    , m_email(email)
    , m_address(address)
    , m_assignedClass(assignedClass)
    , m_joinDate(joinDate)
    , m_isActive(true)
{
}

QString Teacher::toString() const
{
    return QString("Teacher{id=%1, name='%2', subject='%3', contact='%4', class=%5}")
           .arg(m_id)
           .arg(m_name)
           .arg(m_subject)
           .arg(m_contact)
           .arg(m_assignedClass);
}

bool Teacher::isValid() const
{
    return !m_name.isEmpty() && !m_subject.isEmpty() && isValidContact(m_contact);
}

int Teacher::getExperienceYears() const
{
    QDate currentDate = QDate::currentDate();
    return m_joinDate.daysTo(currentDate) / 365;
}

QList<QString> Teacher::getSubjectList()
{
    return {
        "Mathematics", "Science", "English", "Nepali", "Social Studies",
        "Computer Science", "Physical Education", "Art", "Music", "Health",
        "Economics", "Business Studies", "Accountancy", "Physics", "Chemistry",
        "Biology", "History", "Geography", "Civics", "Literature"
    };
}

bool Teacher::isValidContact(const QString &contact)
{
    if (contact.isEmpty()) return true; // Contact is optional
    
    QRegularExpression phoneRegex("^[+]?[0-9]{7,15}$");
    return phoneRegex.match(contact).hasMatch();
}

bool Teacher::isValidEmail(const QString &email)
{
    if (email.isEmpty()) return true; // Email is optional
    
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return emailRegex.match(email).hasMatch();
}
