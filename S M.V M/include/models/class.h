#ifndef CLASS_H
#define CLASS_H

#include <QString>
#include <QObject>
#include <QList>

class Class
{

public:
    explicit Class();
    Class(int id, const QString &name, int grade, int capacity = 40,
          const QString &roomNumber = "", int teacherId = 0,
          const QString &description = "");
    
    // Getters
    int getId() const { return m_id; }
    QString getName() const { return m_name; }
    int getGrade() const { return m_grade; }
    int getCapacity() const { return m_capacity; }
    QString getRoomNumber() const { return m_roomNumber; }
    int getTeacherId() const { return m_teacherId; }
    QString getDescription() const { return m_description; }
    bool isActive() const { return m_isActive; }
    
    // Setters
    void setId(int id) { m_id = id; }
    void setName(const QString &name) { m_name = name; }
    void setGrade(int grade) { m_grade = grade; }
    void setCapacity(int capacity) { m_capacity = capacity; }
    void setRoomNumber(const QString &roomNumber) { m_roomNumber = roomNumber; }
    void setTeacherId(int teacherId) { m_teacherId = teacherId; }
    void setDescription(const QString &description) { m_description = description; }
    void setActive(bool active) { m_isActive = active; }
    
    // Utility methods
    QString toString() const;
    bool isValid() const;
    QString getDisplayName() const;
    bool isFull() const;
    int getAvailableSeats() const;
    
    // Static methods
    static QList<QString> getGradeList();
    static QString getGradeName(int grade);
    static bool isValidGrade(int grade);
    static bool isValidCapacity(int capacity);
    static bool isValidRoomNumber(const QString &roomNumber);

private:
    int m_id;
    QString m_name;
    int m_grade;
    int m_capacity;
    QString m_roomNumber;
    int m_teacherId;
    QString m_description;
    bool m_isActive;
};

// For QVariant support
Q_DECLARE_METATYPE(Class)

#endif // CLASS_H
