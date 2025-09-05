#include "subject.h"

Subject::Subject() : m_id(-1)
{
}

Subject::Subject(const QString& name) : m_name(name), m_id(-1)
{
}

void Subject::setName(const QString& name)
{
    m_name = name;
}

QString Subject::getName() const
{
    return m_name;
}

void Subject::setId(int id)
{
    m_id = id;
}

int Subject::getId() const
{
    return m_id;
}

bool Subject::operator==(const Subject& other) const
{
    return m_id == other.m_id && m_name == other.m_name;
}
