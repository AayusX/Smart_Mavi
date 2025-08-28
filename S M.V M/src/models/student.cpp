#include "models/student.h"
#include <QRegularExpression>
#include <QDate>

Student::Student()
    : m_id(0)
    , m_classId(0)
    , m_dob(QDate())
    , m_admissionDate(QDate::currentDate())
    , m_isActive(true)
{
}

Student::Student(int id, const QString &rollNo, const QString &name, int classId,
                 const QString &guardianName, const QString &guardianContact,
                 const QString &guardianEmail, const QString &address,
                 const QDate &dob, const QString &gender,
                 const QDate &admissionDate)
    : m_id(id)
    , m_rollNo(rollNo)
    , m_name(name)
    , m_classId(classId)
    , m_guardianName(guardianName)
    , m_guardianContact(guardianContact)
    , m_guardianEmail(guardianEmail)
    , m_address(address)
    , m_dob(dob)
    , m_gender(gender)
    , m_admissionDate(admissionDate)
    , m_isActive(true)
{
}

QString Student::toString() const
{
    return QString("Student{id=%1, rollNo='%2', name='%3', classId=%4}")
           .arg(m_id)
           .arg(m_rollNo)
           .arg(m_name)
           .arg(m_classId);
}

bool Student::isValid() const
{
    return !m_rollNo.isEmpty() && !m_name.isEmpty() && isValidRollNo(m_rollNo) &&
           isValidContact(m_guardianContact) && isValidEmail(m_guardianEmail) &&
           isValidDateOfBirth(m_dob);
}

int Student::getAge() const
{
    if (!m_dob.isValid()) return 0;
    
    QDate currentDate = QDate::currentDate();
    int age = currentDate.year() - m_dob.year();
    
    if (currentDate.month() < m_dob.month() || 
        (currentDate.month() == m_dob.month() && currentDate.day() < m_dob.day())) {
        age--;
    }
    
    return age;
}

QString Student::getFullAddress() const
{
    return m_address;
}

QString Student::getGuardianInfo() const
{
    QString info = m_guardianName;
    if (!m_guardianContact.isEmpty()) {
        info += QString(" (%1)").arg(m_guardianContact);
    }
    return info;
}

QList<QString> Student::getGenderList()
{
    return {"Male", "Female", "Other"};
}

bool Student::isValidRollNo(const QString &rollNo)
{
    if (rollNo.isEmpty()) return false;
    
    // Roll number should be alphanumeric and 3-10 characters long
    QRegularExpression rollNoRegex("^[A-Za-z0-9]{3,10}$");
    return rollNoRegex.match(rollNo).hasMatch();
}

bool Student::isValidContact(const QString &contact)
{
    if (contact.isEmpty()) return true; // Contact is optional
    
    QRegularExpression phoneRegex("^[+]?[0-9]{7,15}$");
    return phoneRegex.match(contact).hasMatch();
}

bool Student::isValidEmail(const QString &email)
{
    if (email.isEmpty()) return true; // Email is optional
    
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return emailRegex.match(email).hasMatch();
}

bool Student::isValidDateOfBirth(const QDate &dob)
{
    if (!dob.isValid()) return false;
    
    QDate currentDate = QDate::currentDate();
    QDate minDate = currentDate.addYears(-100); // Reasonable minimum age
    QDate maxDate = currentDate.addYears(-3);   // Reasonable maximum age for school
    
    return dob >= minDate && dob <= maxDate;
}
