#include "teacher.h"

Teacher::Teacher() : m_id(-1)
{
}

Teacher::Teacher(const QString& name) : m_name(name), m_id(-1)
{
}

void Teacher::setName(const QString& name)
{
    m_name = name;
}

QString Teacher::getName() const
{
    return m_name;
}

void Teacher::setId(int id)
{
    m_id = id;
}

int Teacher::getId() const
{
    return m_id;
}

void Teacher::addSubject(const Subject& subject)
{
    if (!teachesSubject(subject)) {
        m_subjects.append(subject);
    }
}

void Teacher::removeSubject(const Subject& subject)
{
    m_subjects.removeAll(subject);
}

QVector<Subject> Teacher::getSubjects() const
{
    return m_subjects;
}

bool Teacher::teachesSubject(const Subject& subject) const
{
    return m_subjects.contains(subject);
}

bool Teacher::operator==(const Teacher& other) const
{
    return m_id == other.m_id && m_name == other.m_name;
}
