#ifndef TEACHER_H
#define TEACHER_H

#include <QString>
#include <QDate>
#include <QList>
#include <QObject>

class Teacher
{

public:
    explicit Teacher();
    Teacher(int id, const QString &name, const QString &subject, const QString &contact, 
            int assignedClass, const QString &email = "", const QString &address = "", 
            const QDate &joinDate = QDate::currentDate());
    
    // Getters
    int getId() const { return m_id; }
    QString getName() const { return m_name; }
    QString getSubject() const { return m_subject; }
    QString getContact() const { return m_contact; }
    QString getEmail() const { return m_email; }
    QString getAddress() const { return m_address; }
    int getAssignedClass() const { return m_assignedClass; }
    QDate getJoinDate() const { return m_joinDate; }
    bool isActive() const { return m_isActive; }
    
    // Setters
    void setId(int id) { m_id = id; }
    void setName(const QString &name) { m_name = name; }
    void setSubject(const QString &subject) { m_subject = subject; }
    void setContact(const QString &contact) { m_contact = contact; }
    void setEmail(const QString &email) { m_email = email; }
    void setAddress(const QString &address) { m_address = address; }
    void setAssignedClass(int assignedClass) { m_assignedClass = assignedClass; }
    void setJoinDate(const QDate &joinDate) { m_joinDate = joinDate; }
    void setActive(bool active) { m_isActive = active; }
    
    // Utility methods
    QString toString() const;
    bool isValid() const;
    int getExperienceYears() const;
    
    // Static methods
    static QList<QString> getSubjectList();
    static bool isValidContact(const QString &contact);
    static bool isValidEmail(const QString &email);

private:
    int m_id;
    QString m_name;
    QString m_subject;
    QString m_contact;
    QString m_email;
    QString m_address;
    int m_assignedClass;
    QDate m_joinDate;
    bool m_isActive;
};

// For QVariant support
Q_DECLARE_METATYPE(Teacher)

#endif // TEACHER_H
