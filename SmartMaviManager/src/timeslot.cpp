#include "timeslot.h"

TimeSlot::TimeSlot() : m_durationMinutes(45), m_periodNumber(0), m_isBreak(false)
{
}

TimeSlot::TimeSlot(const QTime& startTime, int durationMinutes)
    : m_startTime(startTime), m_durationMinutes(durationMinutes), m_periodNumber(0), m_isBreak(false)
{
}

void TimeSlot::setStartTime(const QTime& startTime)
{
    m_startTime = startTime;
}

QTime TimeSlot::getStartTime() const
{
    return m_startTime;
}

void TimeSlot::setDurationMinutes(int durationMinutes)
{
    m_durationMinutes = durationMinutes;
}

int TimeSlot::getDurationMinutes() const
{
    return m_durationMinutes;
}

QTime TimeSlot::getEndTime() const
{
    return m_startTime.addSecs(m_durationMinutes * 60);
}

void TimeSlot::setDay(const QString& day)
{
    m_day = day;
}

QString TimeSlot::getDay() const
{
    return m_day;
}

void TimeSlot::setPeriodNumber(int periodNumber)
{
    m_periodNumber = periodNumber;
}

int TimeSlot::getPeriodNumber() const
{
    return m_periodNumber;
}

void TimeSlot::setIsBreak(bool isBreak)
{
    m_isBreak = isBreak;
}

bool TimeSlot::getIsBreak() const
{
    return m_isBreak;
}

QString TimeSlot::toString() const
{
    return QString("%1 %2 - %3")
        .arg(m_day)
        .arg(m_startTime.toString("hh:mm"))
        .arg(getEndTime().toString("hh:mm"));
}

bool TimeSlot::operator==(const TimeSlot& other) const
{
    return m_startTime == other.m_startTime && 
           m_durationMinutes == other.m_durationMinutes &&
           m_day == other.m_day;
}

bool TimeSlot::overlaps(const TimeSlot& other) const
{
    if (m_day != other.m_day) {
        return false;
    }
    
    QTime thisEnd = getEndTime();
    QTime otherEnd = other.getEndTime();
    
    return !(thisEnd <= other.m_startTime || m_startTime >= otherEnd);
}
