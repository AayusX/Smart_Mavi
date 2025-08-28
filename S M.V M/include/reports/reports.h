#ifndef REPORTS_H
#define REPORTS_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QList>
#include <QPair>
#include <QTextDocument>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>

class Database;
class Teacher;
class Student;
class Class;
class Attendance;

class Reports : public QObject
{
    Q_OBJECT

public:
    enum ReportType {
        TeacherReport = 0,
        StudentReport = 1,
        AttendanceReport = 2,
        ClassReport = 3,
        SummaryReport = 4
    };
    
    enum ExportFormat {
        CSV = 0,
        Excel = 1,
        HTML = 2
    };
    
    explicit Reports(Database *database, QObject *parent = nullptr);
    
    // Report generation
    QString generateTeacherReport(const QDate &startDate, const QDate &endDate);
    QString generateStudentReport(int classId, const QDate &startDate, const QDate &endDate);
    QString generateAttendanceReport(int classId, const QDate &date);
    QString generateClassReport(int classId, const QDate &startDate, const QDate &endDate);
    QString generateSummaryReport(const QDate &startDate, const QDate &endDate);
    
    // Export functions
    bool exportToCSV(const QString &content, const QString &filename);
    bool exportToExcel(const QString &content, const QString &filename);
    bool exportToHTML(const QString &content, const QString &filename);
    
    // Chart generation
    QChart* generateAttendanceChart(int classId, const QDate &startDate, const QDate &endDate);
    QChart* generateStudentPerformanceChart(int classId, const QDate &startDate, const QDate &endDate);
    QChart* generateTeacherWorkloadChart(const QDate &startDate, const QDate &endDate);
    QChart* generateClassComparisonChart(const QDate &date);
    
    // Utility functions
    QString formatReportHeader(const QString &title, const QDate &startDate, const QDate &endDate);
    QString formatReportFooter();
    QString getReportTemplate(ReportType type);
    QString formatDate(const QDate &date);
    QString formatDateTime(const QDateTime &dateTime);
    
    // Statistics
    double calculateAttendancePercentage(int classId, const QDate &startDate, const QDate &endDate);
    int calculateTotalStudents(int classId);
    int calculateTotalTeachers();
    int calculateTotalClasses();
    QList<QPair<QString, double>> getTopPerformingStudents(int classId, const QDate &startDate, const QDate &endDate);
    QList<QPair<QString, double>> getTopPerformingClasses(const QDate &startDate, const QDate &endDate);

private:
    Database *m_database;
    
    // Helper methods
    QString formatTeacherData(const QList<Teacher> &teachers);
    QString formatStudentData(const QList<Student> &students);
    QString formatAttendanceData(const QList<Attendance> &attendance);
    QString formatClassData(const QList<Class> &classes);
    
    QString createHTMLTemplate(const QString &content);
    QString createCSVContent(const QString &content);
    QString createExcelContent(const QString &content);
    
    QBarSeries* createAttendanceBarSeries(int classId, const QDate &startDate, const QDate &endDate);
    QPieSeries* createAttendancePieSeries(int classId, const QDate &date);
    QBarSeries* createStudentPerformanceBarSeries(int classId, const QDate &startDate, const QDate &endDate);
    QBarSeries* createTeacherWorkloadBarSeries(const QDate &startDate, const QDate &endDate);
    QBarSeries* createClassComparisonBarSeries(const QDate &date);
    
    void setupChart(QChart *chart, const QString &title);
    void setupBarChart(QChart *chart, QBarSeries *series, const QString &title);
    void setupPieChart(QChart *chart, QPieSeries *series, const QString &title);
};

// For QVariant support
Q_DECLARE_METATYPE(Reports)

#endif // REPORTS_H
