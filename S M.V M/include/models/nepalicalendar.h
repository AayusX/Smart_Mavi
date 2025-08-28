#ifndef NEPALICALENDAR_H
#define NEPALICALENDAR_H

#include <QObject>
#include <QDate>
#include <QString>
#include <QList>

class NepaliCalendar : public QObject
{
    Q_OBJECT

public:
    explicit NepaliCalendar(QObject *parent = nullptr);
    
    // BS to AD conversion
    static QDate bsToAd(int bsYear, int bsMonth, int bsDay);
    static QDate adToBs(int adYear, int adMonth, int adDay);
    
    // Get current Nepali date
    static QDate getCurrentNepaliDate();
    
    // Get Nepali date components
    static int getNepaliYear(const QDate &adDate);
    static int getNepaliMonth(const QDate &adDate);
    static int getNepaliDay(const QDate &adDate);
    
    // Get Nepali date string
    static QString getNepaliDateString(const QDate &adDate);
    static QString getNepaliDateString(int bsYear, int bsMonth, int bsDay);
    
    // Get Nepali month names
    static QString getNepaliMonthName(int month);
    static QString getNepaliMonthNameShort(int month);
    static QList<QString> getNepaliMonthNames();
    
    // Get Nepali day names
    static QString getNepaliDayName(int dayOfWeek);
    static QString getNepaliDayNameShort(int dayOfWeek);
    static QList<QString> getNepaliDayNames();
    
    // Get Nepali year names
    static QString getNepaliYearName(int year);
    static QList<QString> getNepaliYearNames();
    
    // Calendar utilities
    static int getDaysInNepaliMonth(int year, int month);
    static bool isNepaliLeapYear(int year);
    static QDate getNepaliNewYear(int adYear);
    static QDate getNepaliNewYearDate(int bsYear);
    
    // Validation
    static bool isValidNepaliDate(int year, int month, int day);
    static bool isValidNepaliYear(int year);
    static bool isValidNepaliMonth(int month);
    static bool isValidNepaliDay(int day);
    
    // Formatting
    static QString formatNepaliDate(const QDate &adDate, const QString &format = "dd/mm/yyyy");
    static QString formatNepaliDate(int bsYear, int bsMonth, int bsDay, const QString &format = "dd/mm/yyyy");
    
    // Holidays and events
    static bool isNepaliHoliday(const QDate &adDate);
    static QString getNepaliHolidayName(const QDate &adDate);
    static QList<QPair<QDate, QString>> getNepaliHolidays(int bsYear);
    
    // Academic calendar
    static QDate getAcademicYearStart(int bsYear);
    static QDate getAcademicYearEnd(int bsYear);
    static bool isAcademicYear(const QDate &adDate, int bsYear);
    static int getCurrentAcademicYear();

private:
    // Nepali calendar data (2000-2090 BS)
    static const int nepaliCalendarData[91][13];
    
    // Helper methods
    static int getTotalDaysInNepaliMonth(int year, int month);
    static int getTotalDaysInNepaliYear(int year);
    static int getDayOfWeek(int bsYear, int bsMonth, int bsDay);
    static bool isDateInRange(int year, int month, int day);
};

// For QVariant support
Q_DECLARE_METATYPE(NepaliCalendar)

#endif // NEPALICALENDAR_H
