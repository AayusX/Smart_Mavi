#ifndef ADVANCEDREPORTS_H
#define ADVANCEDREPORTS_H

#include <QObject>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

// Data structures for advanced reporting
struct ReportData {
    QString reportType;
    QDateTime generatedDate;
    QString dateRange;
    QString parameters;
    QJsonDocument jsonData;
};

struct ReportTemplate {
    int id = 0;
    QString name;
    QString description;
    QString category;
    QStringList parameters;
    QString sqlQuery;
    QString outputFormat;
    QString createdBy;
    QDateTime createdAt;
};

struct ReportAnalytics {
    QString analyticsType;
    QString period;
    QJsonDocument data;
};

struct ScheduledReport {
    int id = 0;
    QString reportName;
    QString reportType;
    QString parameters;
    QString scheduleType;
    QString scheduleValue;
    QString outputFormat;
    QStringList emailRecipients;
    QDateTime nextRun;
    bool active = true;
    QString createdBy;
};

class AdvancedReports : public QObject
{
    Q_OBJECT

public:
    explicit AdvancedReports(QObject *parent = nullptr);
    ~AdvancedReports();

    // Core report generation
    ReportData generateAttendanceReport(const QDate &fromDate, const QDate &toDate,
                                       const QString &grade = QString(), const QString &section = QString());
    ReportData generateAcademicReport(const QString &examName, const QString &grade = QString(),
                                     const QString &section = QString());
    ReportData generateFinancialReport(const QDate &fromDate, const QDate &toDate);
    ReportData generateCustomReport(const QString &reportName, const QMap<QString, QVariant> &parameters);

    // Export functions
    bool exportReportToPDF(const ReportData &report, const QString &filePath);
    bool exportReportToExcel(const ReportData &report, const QString &filePath);
    bool exportReportToCSV(const ReportData &report, const QString &filePath);

    // Template management
    QList<ReportTemplate> getReportTemplates();
    bool addReportTemplate(const ReportTemplate &temp);

    // Analytics
    QList<ReportAnalytics> getReportAnalytics();

    // Scheduling
    bool scheduleReport(const ScheduledReport &scheduledReport);
    QList<ScheduledReport> getScheduledReports();

    // Database management
    bool createDatabaseTables();

signals:
    void reportGenerated(const QString &reportType);
    void reportExported(const QString &filePath);

private:
    ReportData generateStudentPerformanceSummary(const QMap<QString, QVariant> &parameters);
    ReportData generateTeacherWorkloadAnalysis(const QMap<QString, QVariant> &parameters);
    ReportData generateClassComparisonReport(const QMap<QString, QVariant> &parameters);
    ReportData generateTrendAnalysisReport(const QMap<QString, QVariant> &parameters);
};

#endif // ADVANCEDREPORTS_H
