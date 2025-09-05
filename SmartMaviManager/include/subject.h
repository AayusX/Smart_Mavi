#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>

class Subject
{
public:
    Subject();
    Subject(const QString& name);
    
    void setName(const QString& name);
    QString getName() const;
    
    void setId(int id);
    int getId() const;
    
    bool operator==(const Subject& other) const;

private:
    QString m_name;
    int m_id;
};

#endif // SUBJECT_H
