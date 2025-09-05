#include "classinfo.h"

ClassInfo::ClassInfo() : m_id(-1)
{
}

ClassInfo::ClassInfo(const QString& name) : m_name(name), m_id(-1)
{
}

void ClassInfo::setName(const QString& name)
{
    m_name = name;
}

QString ClassInfo::getName() const
{
    return m_name;
}

void ClassInfo::setId(int id)
{
    m_id = id;
}

int ClassInfo::getId() const
{
    return m_id;
}

void ClassInfo::setGrade(const QString& grade)
{
    m_grade = grade;
}

QString ClassInfo::getGrade() const
{
    return m_grade;
}

bool ClassInfo::operator==(const ClassInfo& other) const
{
    return m_id == other.m_id && m_name == other.m_name;
}
