#include "models/nepalicalendar.h"
#include <QDate>
#include <QDebug>

NepaliCalendar::NepaliCalendar(QObject *parent)
    : QObject(parent)
{
}

// Nepali calendar data (2000-2090 BS) - days in each month
const int NepaliCalendar::nepaliCalendarData[91][13] = {
    // Year, Baisakh, Jestha, Asar, Shrawan, Bhadra, Ashoj, Kartik, Mangsir, Poush, Magh, Falgun, Chaitra
    {2000, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 30},
    {2001, 31, 31, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2002, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 29, 31},
    {2003, 30, 31, 32, 32, 31, 30, 29, 30, 29, 30, 29, 30},
    {2004, 30, 30, 32, 32, 31, 30, 29, 30, 29, 30, 29, 30},
    {2005, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2006, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2007, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2008, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2009, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2010, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2011, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2012, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2013, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2014, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2015, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2016, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2017, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2018, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2019, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2020, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2021, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2022, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2023, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2024, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2025, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2026, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2027, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2028, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2029, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2030, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2031, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2032, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2033, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2034, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2035, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2036, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2037, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2038, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2039, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2040, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2041, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2042, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2043, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2044, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2045, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2046, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2047, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2048, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2049, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2050, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2051, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2052, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2053, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2054, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2055, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2056, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2057, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2058, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2059, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2060, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2061, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2062, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2063, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2064, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2065, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2066, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2067, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2068, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2069, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2070, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2071, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2072, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2073, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2074, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2075, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2076, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2077, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2078, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2079, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2080, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2081, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2082, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2083, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2084, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2085, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
    {2086, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2087, 30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
    {2088, 31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
    {2089, 31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
    {2090, 31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30}
};

QDate NepaliCalendar::bsToAd(int bsYear, int bsMonth, int bsDay)
{
    if (!isValidNepaliDate(bsYear, bsMonth, bsDay)) {
        return QDate();
    }
    
    // Base date: 1 Baisakh 2000 BS = 13 April 1943 AD
    QDate baseDate(1943, 4, 13);
    int totalDays = 0;
    
    // Calculate days from base date to the given BS date
    for (int year = 2000; year < bsYear; ++year) {
        totalDays += getTotalDaysInNepaliYear(year);
    }
    
    // Add days for the current year
    for (int month = 1; month < bsMonth; ++month) {
        totalDays += getDaysInNepaliMonth(bsYear, month);
    }
    
    totalDays += bsDay - 1; // Subtract 1 because we start from day 1
    
    return baseDate.addDays(totalDays);
}

QDate NepaliCalendar::adToBs(int adYear, int adMonth, int adDay)
{
    QDate adDate(adYear, adMonth, adDay);
    if (!adDate.isValid()) {
        return QDate();
    }
    
    // Base date: 13 April 1943 AD = 1 Baisakh 2000 BS
    QDate baseDate(1943, 4, 13);
    int totalDays = baseDate.daysTo(adDate);
    
    if (totalDays < 0) {
        return QDate(); // Date before BS calendar
    }
    
    int bsYear = 2000;
    int bsMonth = 1;
    int bsDay = 1;
    
    // Find the BS year
    while (totalDays >= getTotalDaysInNepaliYear(bsYear)) {
        totalDays -= getTotalDaysInNepaliYear(bsYear);
        bsYear++;
    }
    
    // Find the BS month
    while (totalDays >= getDaysInNepaliMonth(bsYear, bsMonth)) {
        totalDays -= getDaysInNepaliMonth(bsYear, bsMonth);
        bsMonth++;
    }
    
    // Calculate the BS day
    bsDay = totalDays + 1;
    
    return QDate(bsYear, bsMonth, bsDay);
}

QDate NepaliCalendar::getCurrentNepaliDate()
{
    QDate currentAdDate = QDate::currentDate();
    return adToBs(currentAdDate.year(), currentAdDate.month(), currentAdDate.day());
}

int NepaliCalendar::getNepaliYear(const QDate &adDate)
{
    QDate bsDate = adToBs(adDate.year(), adDate.month(), adDate.day());
    return bsDate.isValid() ? bsDate.year() : 0;
}

int NepaliCalendar::getNepaliMonth(const QDate &adDate)
{
    QDate bsDate = adToBs(adDate.year(), adDate.month(), adDate.day());
    return bsDate.isValid() ? bsDate.month() : 0;
}

int NepaliCalendar::getNepaliDay(const QDate &adDate)
{
    QDate bsDate = adToBs(adDate.year(), adDate.month(), adDate.day());
    return bsDate.isValid() ? bsDate.day() : 0;
}

QString NepaliCalendar::getNepaliDateString(const QDate &adDate)
{
    QDate bsDate = adToBs(adDate.year(), adDate.month(), adDate.day());
    if (!bsDate.isValid()) return QString();
    
    return QString("%1 %2 %3")
           .arg(getNepaliDayName(bsDate.dayOfWeek()))
           .arg(getNepaliMonthName(bsDate.month()))
           .arg(bsDate.year());
}

QString NepaliCalendar::getNepaliDateString(int bsYear, int bsMonth, int bsDay)
{
    QDate bsDate(bsYear, bsMonth, bsDay);
    if (!bsDate.isValid()) return QString();
    
    return QString("%1 %2 %3")
           .arg(getNepaliDayName(bsDate.dayOfWeek()))
           .arg(getNepaliMonthName(bsMonth))
           .arg(bsYear);
}

QString NepaliCalendar::getNepaliMonthName(int month)
{
    switch (month) {
        case 1: return "बैशाख";
        case 2: return "जेठ";
        case 3: return "असार";
        case 4: return "श्रावण";
        case 5: return "भदौ";
        case 6: return "असोज";
        case 7: return "कार्तिक";
        case 8: return "मंसिर";
        case 9: return "पुष";
        case 10: return "माघ";
        case 11: return "फाल्गुन";
        case 12: return "चैत";
        default: return QString();
    }
}

QString NepaliCalendar::getNepaliMonthNameShort(int month)
{
    switch (month) {
        case 1: return "बै";
        case 2: return "जे";
        case 3: return "अ";
        case 4: return "श्रा";
        case 5: return "भ";
        case 6: return "अ";
        case 7: return "का";
        case 8: return "मं";
        case 9: return "पु";
        case 10: return "मा";
        case 11: return "फा";
        case 12: return "चै";
        default: return QString();
    }
}

QList<QString> NepaliCalendar::getNepaliMonthNames()
{
    return {
        "बैशाख", "जेठ", "असार", "श्रावण", "भदौ", "असोज",
        "कार्तिक", "मंसिर", "पुष", "माघ", "फाल्गुन", "चैत"
    };
}

QString NepaliCalendar::getNepaliDayName(int dayOfWeek)
{
    switch (dayOfWeek) {
        case 1: return "आइतबार";
        case 2: return "सोमबार";
        case 3: return "मंगलबार";
        case 4: return "बुधबार";
        case 5: return "बिहिबार";
        case 6: return "शुक्रबार";
        case 7: return "शनिबार";
        default: return QString();
    }
}

QString NepaliCalendar::getNepaliDayNameShort(int dayOfWeek)
{
    switch (dayOfWeek) {
        case 1: return "आइत";
        case 2: return "सोम";
        case 3: return "मंगल";
        case 4: return "बुध";
        case 5: return "बिहि";
        case 6: return "शुक्र";
        case 7: return "शनि";
        default: return QString();
    }
}

QList<QString> NepaliCalendar::getNepaliDayNames()
{
    return {
        "आइतबार", "सोमबार", "मंगलबार", "बुधबार", 
        "बिहिबार", "शुक्रबार", "शनिबार"
    };
}

QString NepaliCalendar::getNepaliYearName(int year)
{
    // Convert year to Nepali numerals (simplified)
    QString yearStr = QString::number(year);
    QString nepaliYear;
    
    for (QChar ch : yearStr) {
        switch (ch.unicode()) {
            case '0': nepaliYear += "०"; break;
            case '1': nepaliYear += "१"; break;
            case '2': nepaliYear += "२"; break;
            case '3': nepaliYear += "३"; break;
            case '4': nepaliYear += "४"; break;
            case '5': nepaliYear += "५"; break;
            case '6': nepaliYear += "६"; break;
            case '7': nepaliYear += "७"; break;
            case '8': nepaliYear += "८"; break;
            case '9': nepaliYear += "९"; break;
            default: nepaliYear += ch; break;
        }
    }
    
    return nepaliYear;
}

QList<QString> NepaliCalendar::getNepaliYearNames()
{
    QList<QString> years;
    for (int year = 2000; year <= 2090; ++year) {
        years.append(getNepaliYearName(year));
    }
    return years;
}

int NepaliCalendar::getDaysInNepaliMonth(int year, int month)
{
    if (!isValidNepaliYear(year) || !isValidNepaliMonth(month)) {
        return 0;
    }
    
    int yearIndex = year - 2000;
    if (yearIndex < 0 || yearIndex >= 91) {
        return 0;
    }
    
    return nepaliCalendarData[yearIndex][month];
}

bool NepaliCalendar::isNepaliLeapYear(int year)
{
    // Simplified leap year calculation for Nepali calendar
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

QDate NepaliCalendar::getNepaliNewYear(int adYear)
{
    // Nepali New Year typically falls in April
    return QDate(adYear, 4, 13);
}

QDate NepaliCalendar::getNepaliNewYearDate(int bsYear)
{
    return bsToAd(bsYear, 1, 1);
}

bool NepaliCalendar::isValidNepaliDate(int year, int month, int day)
{
    if (!isValidNepaliYear(year) || !isValidNepaliMonth(month) || !isValidNepaliDay(day)) {
        return false;
    }
    
    return day <= getDaysInNepaliMonth(year, month);
}

bool NepaliCalendar::isValidNepaliYear(int year)
{
    return year >= 2000 && year <= 2090;
}

bool NepaliCalendar::isValidNepaliMonth(int month)
{
    return month >= 1 && month <= 12;
}

bool NepaliCalendar::isValidNepaliDay(int day)
{
    return day >= 1 && day <= 32; // Maximum days in a Nepali month
}

QString NepaliCalendar::formatNepaliDate(const QDate &adDate, const QString &format)
{
    QDate bsDate = adToBs(adDate.year(), adDate.month(), adDate.day());
    if (!bsDate.isValid()) return QString();
    
    return formatNepaliDate(bsDate.year(), bsDate.month(), bsDate.day(), format);
}

QString NepaliCalendar::formatNepaliDate(int bsYear, int bsMonth, int bsDay, const QString &format)
{
    QString result = format;
    
    result.replace("yyyy", QString::number(bsYear));
    result.replace("yy", QString::number(bsYear).right(2));
    result.replace("mm", QString("%1").arg(bsMonth, 2, 10, QChar('0')));
    result.replace("dd", QString("%1").arg(bsDay, 2, 10, QChar('0')));
    result.replace("MMMM", getNepaliMonthName(bsMonth));
    result.replace("MMM", getNepaliMonthNameShort(bsMonth));
    result.replace("MM", QString("%1").arg(bsMonth, 2, 10, QChar('0')));
    result.replace("M", QString::number(bsMonth));
    result.replace("DD", QString("%1").arg(bsDay, 2, 10, QChar('0')));
    result.replace("D", QString::number(bsDay));
    
    return result;
}

bool NepaliCalendar::isNepaliHoliday(const QDate &adDate)
{
    // This would need to be implemented with actual holiday data
    // For now, return false
    return false;
}

QString NepaliCalendar::getNepaliHolidayName(const QDate &adDate)
{
    // This would need to be implemented with actual holiday data
    return QString();
}

QList<QPair<QDate, QString>> NepaliCalendar::getNepaliHolidays(int bsYear)
{
    // This would need to be implemented with actual holiday data
    return QList<QPair<QDate, QString>>();
}

QDate NepaliCalendar::getAcademicYearStart(int bsYear)
{
    // Academic year typically starts in Baisakh (April)
    return bsToAd(bsYear, 1, 1);
}

QDate NepaliCalendar::getAcademicYearEnd(int bsYear)
{
    // Academic year typically ends in Chaitra (March)
    return bsToAd(bsYear, 12, 30);
}

bool NepaliCalendar::isAcademicYear(const QDate &adDate, int bsYear)
{
    QDate startDate = getAcademicYearStart(bsYear);
    QDate endDate = getAcademicYearEnd(bsYear);
    
    return adDate >= startDate && adDate <= endDate;
}

int NepaliCalendar::getCurrentAcademicYear()
{
    QDate currentDate = QDate::currentDate();
    QDate currentBsDate = adToBs(currentDate.year(), currentDate.month(), currentDate.day());
    
    if (!currentBsDate.isValid()) return 0;
    
    // If current date is before Chaitra (month 12), it's the previous academic year
    if (currentBsDate.month() < 12) {
        return currentBsDate.year() - 1;
    }
    
    return currentBsDate.year();
}

int NepaliCalendar::getTotalDaysInNepaliMonth(int year, int month)
{
    return getDaysInNepaliMonth(year, month);
}

int NepaliCalendar::getTotalDaysInNepaliYear(int year)
{
    if (!isValidNepaliYear(year)) return 0;
    
    int totalDays = 0;
    for (int month = 1; month <= 12; ++month) {
        totalDays += getDaysInNepaliMonth(year, month);
    }
    
    return totalDays;
}

int NepaliCalendar::getDayOfWeek(int bsYear, int bsMonth, int bsDay)
{
    QDate adDate = bsToAd(bsYear, bsMonth, bsDay);
    return adDate.isValid() ? adDate.dayOfWeek() : 0;
}

bool NepaliCalendar::isDateInRange(int year, int month, int day)
{
    return isValidNepaliDate(year, month, day);
}
