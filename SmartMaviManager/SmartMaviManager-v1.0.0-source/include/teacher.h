#ifndef TEACHER_H
#define TEACHER_H

#include <QString>
#include <QVector>
#include "subject.h"

class Teacher
{
public:
    Teacher();
    Teacher(const QString& name);
    
    void setName(const QString& name);
    QString getName() const;
    
    void setId(int id);
    int getId() const;
    
    void addSubject(const Subject& subject);
    void removeSubject(const Subject& subject);
    QVector<Subject> getSubjects() const;
    bool teachesSubject(const Subject& subject) const;
    
    bool operator==(const Teacher& other) const;

private:
    QString m_name;
    int m_id;
    QVector<Subject> m_subjects;
};

#endif // TEACHER_H
