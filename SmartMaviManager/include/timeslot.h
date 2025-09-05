#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <QString>
#include <QTime>

class TimeSlot
{
public:
    TimeSlot();
    TimeSlot(const QTime& startTime, int durationMinutes);
    
    void setStartTime(const QTime& startTime);
    QTime getStartTime() const;
    
    void setDurationMinutes(int durationMinutes);
    int getDurationMinutes() const;
    
    QTime getEndTime() const;
    
    void setDay(const QString& day);
    QString getDay() const;
    
    void setPeriodNumber(int periodNumber);
    int getPeriodNumber() const;
    
    void setIsBreak(bool isBreak);
    bool getIsBreak() const;
    
    QString toString() const;
    
    bool operator==(const TimeSlot& other) const;
    bool overlaps(const TimeSlot& other) const;

private:
    QTime m_startTime;
    int m_durationMinutes;
    QString m_day;
    int m_periodNumber;
    bool m_isBreak;
};

#endif // TIMESLOT_H
