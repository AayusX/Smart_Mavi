#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <QString>

class ClassInfo
{
public:
    ClassInfo();
    ClassInfo(const QString& name);
    
    void setName(const QString& name);
    QString getName() const;
    
    void setId(int id);
    int getId() const;
    
    void setGrade(const QString& grade);
    QString getGrade() const;
    
    bool operator==(const ClassInfo& other) const;

private:
    QString m_name;
    QString m_grade;
    int m_id;
};

#endif // CLASSINFO_H
