#include "schedule.h"

Schedule::Schedule()
{
    m_days << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";
}

void Schedule::addEntry(const ScheduleEntry& entry)
{
    if (!hasConflict(entry)) {
        m_entries.append(entry);
    }
}

void Schedule::removeEntry(const ScheduleEntry& entry)
{
    for (int i = 0; i < m_entries.size(); ++i) {
        const ScheduleEntry& existing = m_entries[i];
        if (existing.teacher == entry.teacher &&
            existing.subject == entry.subject &&
            existing.classInfo == entry.classInfo &&
            existing.timeSlot == entry.timeSlot) {
            m_entries.removeAt(i);
            break;
        }
    }
}

void Schedule::clear()
{
    m_entries.clear();
}

QVector<ScheduleEntry> Schedule::getEntries() const
{
    return m_entries;
}

QVector<ScheduleEntry> Schedule::getEntriesForClass(const ClassInfo& classInfo) const
{
    QVector<ScheduleEntry> result;
    for (const auto& entry : m_entries) {
        if (entry.classInfo == classInfo) {
            result.append(entry);
        }
    }
    return result;
}

QVector<ScheduleEntry> Schedule::getEntriesForTeacher(const Teacher& teacher) const
{
    QVector<ScheduleEntry> result;
    for (const auto& entry : m_entries) {
        if (entry.teacher == teacher) {
            result.append(entry);
        }
    }
    return result;
}

QVector<ScheduleEntry> Schedule::getEntriesForTimeSlot(const TimeSlot& timeSlot) const
{
    QVector<ScheduleEntry> result;
    for (const auto& entry : m_entries) {
        if (entry.timeSlot == timeSlot) {
            result.append(entry);
        }
    }
    return result;
}

bool Schedule::hasConflict(const ScheduleEntry& entry) const
{
    return !isTeacherAvailable(entry.teacher, entry.timeSlot) ||
           !isClassroomAvailable(entry.classInfo, entry.timeSlot);
}

bool Schedule::isTeacherAvailable(const Teacher& teacher, const TimeSlot& timeSlot) const
{
    for (const auto& entry : m_entries) {
        if (entry.teacher == teacher && 
            (entry.timeSlot == timeSlot || entry.timeSlot.overlaps(timeSlot))) {
            return false;
        }
    }
    return true;
}

bool Schedule::isClassroomAvailable(const ClassInfo& classInfo, const TimeSlot& timeSlot) const
{
    for (const auto& entry : m_entries) {
        if (entry.classInfo == classInfo && 
            (entry.timeSlot == timeSlot || entry.timeSlot.overlaps(timeSlot))) {
            return false;
        }
    }
    return true;
}

QStringList Schedule::getDays() const
{
    return m_days;
}

void Schedule::setDays(const QStringList& days)
{
    m_days = days;
}

bool Schedule::isEmpty() const
{
    return m_entries.isEmpty();
}

int Schedule::size() const
{
    return m_entries.size();
}
