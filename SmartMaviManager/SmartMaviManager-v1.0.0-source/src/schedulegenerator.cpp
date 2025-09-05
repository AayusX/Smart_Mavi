#include "schedulegenerator.h"
#include <QDebug>
#include <algorithm>

ScheduleGenerator::ScheduleGenerator()
{
    m_random.seed(QTime::currentTime().msecsSinceStartOfDay());
    m_config.days << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";
}

void ScheduleGenerator::setConfig(const ScheduleConfig& config)
{
    m_config = config;
}

ScheduleConfig ScheduleGenerator::getConfig() const
{
    return m_config;
}

void ScheduleGenerator::setSeed(unsigned int seed)
{
    m_random.seed(seed);
}

Schedule ScheduleGenerator::generateSchedule()
{
    Schedule schedule;
    schedule.setDays(m_config.days);
    
    // Generate time slots for each day
    QVector<TimeSlot> allTimeSlots = generateTimeSlots();
    
    // Create all possible class-subject combinations
    QVector<QPair<ClassInfo, Subject>> assignments;
    
    for (const auto& classInfo : m_config.classes) {
        for (const auto& subject : m_config.subjects) {
            // Add multiple periods per week for each subject
            int periodsPerWeek = 2 + (m_random.bounded(3)); // 2-4 periods per week
            for (int i = 0; i < periodsPerWeek; ++i) {
                assignments.append({classInfo, subject});
            }
        }
    }
    
    // Shuffle assignments for randomization
    shuffleAssignments(assignments);
    
    // Try to assign each combination to a time slot
    for (const auto& assignment : assignments) {
        const ClassInfo& classInfo = assignment.first;
        const Subject& subject = assignment.second;
        
        // Shuffle time slots for randomization
        QVector<TimeSlot> availableSlots = allTimeSlots;
        std::shuffle(availableSlots.begin(), availableSlots.end(), m_random);
        
        for (const auto& timeSlot : availableSlots) {
            if (timeSlot.getIsBreak()) continue;
            
            // Get available teachers for this subject
            QVector<Teacher> availableTeachers = getAvailableTeachers(subject, timeSlot, schedule);
            
            if (!availableTeachers.isEmpty()) {
                // Randomly select a teacher
                int teacherIndex = m_random.bounded(availableTeachers.size());
                Teacher selectedTeacher = availableTeachers[teacherIndex];
                
                // Check if class is available
                if (schedule.isClassroomAvailable(classInfo, timeSlot)) {
                    ScheduleEntry entry(selectedTeacher, subject, classInfo, timeSlot);
                    schedule.addEntry(entry);
                    break; // Move to next assignment
                }
            }
        }
    }
    
    return schedule;
}

QVector<TimeSlot> ScheduleGenerator::generateTimeSlots() const
{
    QVector<TimeSlot> timeSlots;
    
    for (const QString& day : m_config.days) {
        QTime currentTime = m_config.schoolStartTime;
        int periodNumber = 1;
        
        while (currentTime < m_config.schoolEndTime) {
            // Check if it's break time
            if (currentTime == m_config.breakStartTime) {
                TimeSlot breakSlot(currentTime, m_config.breakDuration);
                breakSlot.setDay(day);
                breakSlot.setIsBreak(true);
                breakSlot.setPeriodNumber(periodNumber);
                timeSlots.append(breakSlot);
                currentTime = currentTime.addSecs(m_config.breakDuration * 60);
                periodNumber++;
                continue;
            }
            
            // Check if it's lunch time
            if (currentTime == m_config.lunchStartTime) {
                TimeSlot lunchSlot(currentTime, m_config.lunchDuration);
                lunchSlot.setDay(day);
                lunchSlot.setIsBreak(true);
                lunchSlot.setPeriodNumber(periodNumber);
                timeSlots.append(lunchSlot);
                currentTime = currentTime.addSecs(m_config.lunchDuration * 60);
                periodNumber++;
                continue;
            }
            
            // Regular class period
            TimeSlot slot(currentTime, m_config.periodDuration);
            slot.setDay(day);
            slot.setPeriodNumber(periodNumber);
            slot.setIsBreak(false);
            timeSlots.append(slot);
            
            currentTime = currentTime.addSecs(m_config.periodDuration * 60);
            periodNumber++;
            
            // Don't exceed max periods per day
            if (periodNumber > m_config.maxPeriodsPerDay) {
                break;
            }
        }
    }
    
    return timeSlots;
}

bool ScheduleGenerator::canAssignTeacher(const Teacher& teacher, const Subject& subject, 
                                       const ClassInfo& classInfo, const TimeSlot& timeSlot, 
                                       const Schedule& currentSchedule) const
{
    // Check if teacher teaches this subject
    if (!teacher.teachesSubject(subject)) {
        return false;
    }
    
    // Check if teacher is available at this time
    if (!currentSchedule.isTeacherAvailable(teacher, timeSlot)) {
        return false;
    }
    
    // Check if classroom is available
    if (!currentSchedule.isClassroomAvailable(classInfo, timeSlot)) {
        return false;
    }
    
    // Check daily workload limit for teacher
    QVector<ScheduleEntry> teacherEntries = currentSchedule.getEntriesForTeacher(teacher);
    int periodsToday = 0;
    for (const auto& entry : teacherEntries) {
        if (entry.timeSlot.getDay() == timeSlot.getDay() && !entry.timeSlot.getIsBreak()) {
            periodsToday++;
        }
    }
    
    return periodsToday < m_config.maxPeriodsPerTeacherPerDay;
}

QVector<Teacher> ScheduleGenerator::getAvailableTeachers(const Subject& subject, 
                                                       const TimeSlot& timeSlot, 
                                                       const Schedule& currentSchedule) const
{
    QVector<Teacher> availableTeachers;
    
    for (const auto& teacher : m_config.teachers) {
        if (teacher.teachesSubject(subject) && 
            currentSchedule.isTeacherAvailable(teacher, timeSlot)) {
            
            // Check daily workload
            QVector<ScheduleEntry> teacherEntries = currentSchedule.getEntriesForTeacher(teacher);
            int periodsToday = 0;
            for (const auto& entry : teacherEntries) {
                if (entry.timeSlot.getDay() == timeSlot.getDay() && !entry.timeSlot.getIsBreak()) {
                    periodsToday++;
                }
            }
            
            if (periodsToday < m_config.maxPeriodsPerTeacherPerDay) {
                availableTeachers.append(teacher);
            }
        }
    }
    
    return availableTeachers;
}

void ScheduleGenerator::shuffleAssignments(QVector<QPair<ClassInfo, Subject>>& assignments)
{
    std::shuffle(assignments.begin(), assignments.end(), m_random);
}

int ScheduleGenerator::calculateScheduleQuality(const Schedule& schedule) const
{
    int quality = 0;
    
    // Higher score for more filled time slots
    quality += schedule.size() * 10;
    
    // Bonus for balanced teacher workloads
    for (const auto& teacher : m_config.teachers) {
        QVector<ScheduleEntry> teacherEntries = schedule.getEntriesForTeacher(teacher);
        if (!teacherEntries.isEmpty()) {
            quality += 5; // Bonus for utilized teachers
        }
    }
    
    // Penalty for gaps in class schedules
    for (const auto& classInfo : m_config.classes) {
        QVector<ScheduleEntry> classEntries = schedule.getEntriesForClass(classInfo);
        // Sort by day and time... (simplified for now)
        quality += classEntries.size();
    }
    
    return quality;
}
