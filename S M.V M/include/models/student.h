#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QDate>
#include <QObject>

class Student
{

public:
    explicit Student();
    Student(int id, const QString &rollNo, const QString &name, int classId,
            const QString &guardianName = "", const QString &guardianContact = "",
            const QString &guardianEmail = "", const QString &address = "",
            const QDate &dob = QDate(), const QString &gender = "",
            const QDate &admissionDate = QDate::currentDate());
    
    // Getters
    int getId() const { return m_id; }
    QString getRollNo() const { return m_rollNo; }
    QString getName() const { return m_name; }
    int getClassId() const { return m_classId; }
    QString getGuardianName() const { return m_guardianName; }
    QString getGuardianContact() const { return m_guardianContact; }
    QString getGuardianEmail() const { return m_guardianEmail; }
    QString getAddress() const { return m_address; }
    QDate getDateOfBirth() const { return m_dob; }
    QString getGender() const { return m_gender; }
    QDate getAdmissionDate() const { return m_admissionDate; }
    bool isActive() const { return m_isActive; }
    
    // Setters
    void setId(int id) { m_id = id; }
    void setRollNo(const QString &rollNo) { m_rollNo = rollNo; }
    void setName(const QString &name) { m_name = name; }
    void setClassId(int classId) { m_classId = classId; }
    void setGuardianName(const QString &guardianName) { m_guardianName = guardianName; }
    void setGuardianContact(const QString &guardianContact) { m_guardianContact = guardianContact; }
    void setGuardianEmail(const QString &guardianEmail) { m_guardianEmail = guardianEmail; }
    void setAddress(const QString &address) { m_address = address; }
    void setDateOfBirth(const QDate &dob) { m_dob = dob; }
    void setGender(const QString &gender) { m_gender = gender; }
    void setAdmissionDate(const QDate &admissionDate) { m_admissionDate = admissionDate; }
    void setActive(bool active) { m_isActive = active; }
    
    // Utility methods
    QString toString() const;
    bool isValid() const;
    int getAge() const;
    QString getFullAddress() const;
    QString getGuardianInfo() const;
    
    // Static methods
    static QList<QString> getGenderList();
    static bool isValidRollNo(const QString &rollNo);
    static bool isValidContact(const QString &contact);
    static bool isValidEmail(const QString &email);
    static bool isValidDateOfBirth(const QDate &dob);

private:
    int m_id;
    QString m_rollNo;
    QString m_name;
    int m_classId;
    QString m_guardianName;
    QString m_guardianContact;
    QString m_guardianEmail;
    QString m_address;
    QDate m_dob;
    QString m_gender;
    QDate m_admissionDate;
    bool m_isActive;
};

// For QVariant support
Q_DECLARE_METATYPE(Student)

#endif // STUDENT_H
