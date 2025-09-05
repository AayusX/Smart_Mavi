#ifndef SCHEDULEGENERATOR_H
#define SCHEDULEGENERATOR_H

#include <QVector>
#include <QTime>
#include <QRandomGenerator>
#include <QPair>
#include "schedule.h"
#include "teacher.h"
#include "subject.h"
#include "classinfo.h"
#include "timeslot.h"

struct ScheduleConfig
{
    QVector<Teacher> teachers;
    QVector<Subject> subjects;
    QVector<ClassInfo> classes;
    QStringList days;
    QTime schoolStartTime = QTime(8, 0);
    QTime schoolEndTime = QTime(15, 0);
    int periodDuration = 45; // minutes
    QTime breakStartTime = QTime(10, 30);
    int breakDuration = 15; // minutes
    QTime lunchStartTime = QTime(12, 30);
    int lunchDuration = 30; // minutes
    int maxPeriodsPerDay = 8;
    int maxPeriodsPerTeacherPerDay = 6;
};

class ScheduleGenerator
{
public:
    ScheduleGenerator();
    
    void setConfig(const ScheduleConfig& config);
    ScheduleConfig getConfig() const;
    
    Schedule generateSchedule();
    
    void setSeed(unsigned int seed);
    
private:
    ScheduleConfig m_config;
    QRandomGenerator m_random;
    
    QVector<TimeSlot> generateTimeSlots() const;
    bool canAssignTeacher(const Teacher& teacher, const Subject& subject, 
                         const ClassInfo& classInfo, const TimeSlot& timeSlot, 
                         const Schedule& currentSchedule) const;
    
    QVector<Teacher> getAvailableTeachers(const Subject& subject, 
                                        const TimeSlot& timeSlot, 
                                        const Schedule& currentSchedule) const;
    
    void shuffleAssignments(QVector<QPair<ClassInfo, Subject>>& assignments);
    int calculateScheduleQuality(const Schedule& schedule) const;
};

#endif // SCHEDULEGENERATOR_H
