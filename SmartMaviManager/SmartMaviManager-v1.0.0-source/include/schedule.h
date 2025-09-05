#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QMap>
#include <QPair>
#include <QVector>
#include "teacher.h"
#include "subject.h"
#include "classinfo.h"
#include "timeslot.h"

struct ScheduleEntry
{
    Teacher teacher;
    Subject subject;
    ClassInfo classInfo;
    TimeSlot timeSlot;
    
    ScheduleEntry() = default;
    ScheduleEntry(const Teacher& t, const Subject& s, const ClassInfo& c, const TimeSlot& ts)
        : teacher(t), subject(s), classInfo(c), timeSlot(ts) {}
};

class Schedule
{
public:
    Schedule();
    
    void addEntry(const ScheduleEntry& entry);
    void removeEntry(const ScheduleEntry& entry);
    void clear();
    
    QVector<ScheduleEntry> getEntries() const;
    QVector<ScheduleEntry> getEntriesForClass(const ClassInfo& classInfo) const;
    QVector<ScheduleEntry> getEntriesForTeacher(const Teacher& teacher) const;
    QVector<ScheduleEntry> getEntriesForTimeSlot(const TimeSlot& timeSlot) const;
    
    bool hasConflict(const ScheduleEntry& entry) const;
    bool isTeacherAvailable(const Teacher& teacher, const TimeSlot& timeSlot) const;
    bool isClassroomAvailable(const ClassInfo& classInfo, const TimeSlot& timeSlot) const;
    
    QStringList getDays() const;
    void setDays(const QStringList& days);
    
    bool isEmpty() const;
    int size() const;

private:
    QVector<ScheduleEntry> m_entries;
    QStringList m_days;
};

#endif // SCHEDULE_H
