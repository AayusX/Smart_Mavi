#include "reports/advancedreports.h"
#include "database/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

AdvancedReports::AdvancedReports(QObject *parent)
    : QObject(parent)
{
}

AdvancedReports::~AdvancedReports()
{
}

ReportData AdvancedReports::generateAttendanceReport(const QDate &fromDate, const QDate &toDate,
                                                    const QString &grade, const QString &section)
{
    ReportData report;
    report.reportType = "Attendance Report";
    report.generatedDate = QDateTime::currentDateTime();
    report.dateRange = QString("%1 to %2").arg(fromDate.toString("dd/MM/yyyy"))
                                         .arg(toDate.toString("dd/MM/yyyy"));
    
    QSqlQuery query(Database::instance().database());
    
    QString queryStr = R"(
        SELECT es.roll_number, es.name, es.grade, es.section,
               COUNT(CASE WHEN aa.status = 'Present' THEN 1 END) as present_days,
               COUNT(CASE WHEN aa.status = 'Absent' THEN 1 END) as absent_days,
               COUNT(CASE WHEN aa.status = 'Late' THEN 1 END) as late_days,
               COUNT(CASE WHEN aa.status = 'Excused' THEN 1 END) as excused_days,
               COUNT(*) as total_days
        FROM enhanced_students es
        LEFT JOIN advanced_attendance aa ON es.roll_number = aa.student_roll
        AND aa.date BETWEEN ? AND ?
        WHERE 1=1
    )";
    
    if (!grade.isEmpty()) {
        queryStr += " AND es.grade = ?";
    }
    if (!section.isEmpty()) {
        queryStr += " AND es.section = ?";
    }
    
    queryStr += " GROUP BY es.roll_number, es.name, es.grade, es.section ORDER BY es.grade, es.section, es.name";
    
    query.prepare(queryStr);
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    if (!grade.isEmpty()) query.addBindValue(grade);
    if (!section.isEmpty()) query.addBindValue(section);
    
    QJsonArray studentsArray;
    int totalStudents = 0;
    double totalAttendancePercentage = 0.0;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject studentObj;
            studentObj["roll_number"] = query.value("roll_number").toString();
            studentObj["name"] = query.value("name").toString();
            studentObj["grade"] = query.value("grade").toString();
            studentObj["section"] = query.value("section").toString();
            
            int presentDays = query.value("present_days").toInt();
            int absentDays = query.value("absent_days").toInt();
            int lateDays = query.value("late_days").toInt();
            int excusedDays = query.value("excused_days").toInt();
            int totalDays = query.value("total_days").toInt();
            
            studentObj["present_days"] = presentDays;
            studentObj["absent_days"] = absentDays;
            studentObj["late_days"] = lateDays;
            studentObj["excused_days"] = excusedDays;
            studentObj["total_days"] = totalDays;
            
            double percentage = totalDays > 0 ? 
                (double)(presentDays + lateDays + excusedDays) / totalDays * 100 : 0.0;
            studentObj["attendance_percentage"] = percentage;
            
            studentsArray.append(studentObj);
            totalStudents++;
            totalAttendancePercentage += percentage;
        }
    }
    
    QJsonObject summaryObj;
    summaryObj["total_students"] = totalStudents;
    summaryObj["average_attendance"] = totalStudents > 0 ? totalAttendancePercentage / totalStudents : 0.0;
    
    QJsonObject reportObj;
    reportObj["summary"] = summaryObj;
    reportObj["students"] = studentsArray;
    
    report.jsonData = QJsonDocument(reportObj);
    
    return report;
}

ReportData AdvancedReports::generateAcademicReport(const QString &examName, const QString &grade,
                                                  const QString &section)
{
    ReportData report;
    report.reportType = "Academic Performance Report";
    report.generatedDate = QDateTime::currentDateTime();
    report.parameters = QString("Exam: %1, Grade: %2, Section: %3").arg(examName).arg(grade).arg(section);
    
    QSqlQuery query(Database::instance().database());
    
    QString queryStr = R"(
        SELECT es.roll_number, es.name, es.grade, es.section,
               er.subject, er.marks_obtained, er.total_marks, er.grade as exam_grade,
               (er.marks_obtained / er.total_marks * 100) as percentage
        FROM enhanced_students es
        LEFT JOIN exam_results er ON es.roll_number = er.student_roll
        WHERE er.exam_name = ?
    )";
    
    if (!grade.isEmpty()) {
        queryStr += " AND es.grade = ?";
    }
    if (!section.isEmpty()) {
        queryStr += " AND es.section = ?";
    }
    
    queryStr += " ORDER BY es.grade, es.section, es.name, er.subject";
    
    query.prepare(queryStr);
    query.addBindValue(examName);
    if (!grade.isEmpty()) query.addBindValue(grade);
    if (!section.isEmpty()) query.addBindValue(section);
    
    QJsonArray studentsArray;
    QMap<QString, QJsonObject> studentMap;
    
    if (query.exec()) {
        while (query.next()) {
            QString rollNumber = query.value("roll_number").toString();
            
            if (!studentMap.contains(rollNumber)) {
                QJsonObject studentObj;
                studentObj["roll_number"] = rollNumber;
                studentObj["name"] = query.value("name").toString();
                studentObj["grade"] = query.value("grade").toString();
                studentObj["section"] = query.value("section").toString();
                studentObj["subjects"] = QJsonArray();
                studentMap[rollNumber] = studentObj;
            }
            
            QJsonObject &studentObj = studentMap[rollNumber];
            QJsonArray subjectsArray = studentObj["subjects"].toArray();
            
            QJsonObject subjectObj;
            subjectObj["subject"] = query.value("subject").toString();
            subjectObj["marks_obtained"] = query.value("marks_obtained").toDouble();
            subjectObj["total_marks"] = query.value("total_marks").toDouble();
            subjectObj["percentage"] = query.value("percentage").toDouble();
            subjectObj["grade"] = query.value("exam_grade").toString();
            
            subjectsArray.append(subjectObj);
            studentObj["subjects"] = subjectsArray;
            studentMap[rollNumber] = studentObj;
        }
    }
    
    // Convert map to array
    for (auto it = studentMap.begin(); it != studentMap.end(); ++it) {
        studentsArray.append(it.value());
    }
    
    QJsonObject reportObj;
    reportObj["exam_name"] = examName;
    reportObj["students"] = studentsArray;
    
    report.jsonData = QJsonDocument(reportObj);
    
    return report;
}

ReportData AdvancedReports::generateFinancialReport(const QDate &fromDate, const QDate &toDate)
{
    ReportData report;
    report.reportType = "Financial Report";
    report.generatedDate = QDateTime::currentDateTime();
    report.dateRange = QString("%1 to %2").arg(fromDate.toString("dd/MM/yyyy"))
                                         .arg(toDate.toString("dd/MM/yyyy"));
    
    QSqlQuery query(Database::instance().database());
    
    // Get fee collection summary
    query.prepare(R"(
        SELECT fee_type, payment_method,
               COUNT(*) as transaction_count,
               SUM(amount) as total_amount
        FROM fee_transactions
        WHERE transaction_date BETWEEN ? AND ?
        GROUP BY fee_type, payment_method
        ORDER BY fee_type, payment_method
    )");
    
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    
    QJsonArray collectionsArray;
    double totalRevenue = 0.0;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject collectionObj;
            collectionObj["fee_type"] = query.value("fee_type").toString();
            collectionObj["payment_method"] = query.value("payment_method").toString();
            collectionObj["transaction_count"] = query.value("transaction_count").toInt();
            
            double amount = query.value("total_amount").toDouble();
            collectionObj["total_amount"] = amount;
            totalRevenue += amount;
            
            collectionsArray.append(collectionObj);
        }
    }
    
    // Get outstanding fees
    query.prepare(R"(
        SELECT es.grade, es.section, COUNT(*) as student_count,
               SUM(CASE WHEN ft.amount < 0 THEN ABS(ft.amount) ELSE 0 END) as outstanding_amount
        FROM enhanced_students es
        LEFT JOIN fee_transactions ft ON es.roll_number = ft.student_roll
        AND ft.fee_type LIKE '%Outstanding%'
        GROUP BY es.grade, es.section
        ORDER BY es.grade, es.section
    )");
    
    QJsonArray outstandingArray;
    double totalOutstanding = 0.0;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject outstandingObj;
            outstandingObj["grade"] = query.value("grade").toString();
            outstandingObj["section"] = query.value("section").toString();
            outstandingObj["student_count"] = query.value("student_count").toInt();
            
            double amount = query.value("outstanding_amount").toDouble();
            outstandingObj["outstanding_amount"] = amount;
            totalOutstanding += amount;
            
            outstandingArray.append(outstandingObj);
        }
    }
    
    QJsonObject summaryObj;
    summaryObj["total_revenue"] = totalRevenue;
    summaryObj["total_outstanding"] = totalOutstanding;
    summaryObj["net_revenue"] = totalRevenue - totalOutstanding;
    
    QJsonObject reportObj;
    reportObj["summary"] = summaryObj;
    reportObj["collections"] = collectionsArray;
    reportObj["outstanding"] = outstandingArray;
    
    report.jsonData = QJsonDocument(reportObj);
    
    return report;
}

ReportData AdvancedReports::generateCustomReport(const QString &reportName, const QMap<QString, QVariant> &parameters)
{
    ReportData report;
    report.reportType = reportName;
    report.generatedDate = QDateTime::currentDateTime();
    
    // Custom report logic based on reportName
    if (reportName == "Student Performance Summary") {
        return generateStudentPerformanceSummary(parameters);
    } else if (reportName == "Teacher Workload Analysis") {
        return generateTeacherWorkloadAnalysis(parameters);
    } else if (reportName == "Class Comparison") {
        return generateClassComparisonReport(parameters);
    } else if (reportName == "Trend Analysis") {
        return generateTrendAnalysisReport(parameters);
    }
    
    // Default empty report
    report.jsonData = QJsonDocument(QJsonObject());
    return report;
}

bool AdvancedReports::exportReportToPDF(const ReportData &report, const QString &filePath)
{
    // This would require QPrinter and more complex implementation
    // For now, we'll create a simplified text export
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << "=== " << report.reportType << " ===\\n\\n";
    out << "Generated: " << report.generatedDate.toString("dd/MM/yyyy hh:mm:ss") << "\\n";
    
    if (!report.dateRange.isEmpty()) {
        out << "Date Range: " << report.dateRange << "\\n";
    }
    
    if (!report.parameters.isEmpty()) {
        out << "Parameters: " << report.parameters << "\\n";
    }
    
    out << "\\n" << report.jsonData.toJson() << "\\n";
    
    file.close();
    return true;
}

bool AdvancedReports::exportReportToExcel(const ReportData &report, const QString &filePath)
{
    // This would require a library like QXlsx for proper Excel export
    // For now, we'll create a CSV export
    return exportReportToCSV(report, filePath);
}

bool AdvancedReports::exportReportToCSV(const ReportData &report, const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    
    // Parse JSON data and convert to CSV format
    QJsonObject rootObj = report.jsonData.object();
    
    if (report.reportType == "Attendance Report") {
        out << "Roll Number,Name,Grade,Section,Present Days,Absent Days,Late Days,Excused Days,Total Days,Attendance %\\n";
        
        QJsonArray students = rootObj["students"].toArray();
        for (const QJsonValue &studentVal : students) {
            QJsonObject student = studentVal.toObject();
            out << student["roll_number"].toString() << ","
                << student["name"].toString() << ","
                << student["grade"].toString() << ","
                << student["section"].toString() << ","
                << student["present_days"].toInt() << ","
                << student["absent_days"].toInt() << ","
                << student["late_days"].toInt() << ","
                << student["excused_days"].toInt() << ","
                << student["total_days"].toInt() << ","
                << student["attendance_percentage"].toDouble() << "\\n";
        }
    } else if (report.reportType == "Academic Performance Report") {
        out << "Roll Number,Name,Grade,Section,Subject,Marks Obtained,Total Marks,Percentage,Grade\\n";
        
        QJsonArray students = rootObj["students"].toArray();
        for (const QJsonValue &studentVal : students) {
            QJsonObject student = studentVal.toObject();
            QJsonArray subjects = student["subjects"].toArray();
            
            for (const QJsonValue &subjectVal : subjects) {
                QJsonObject subject = subjectVal.toObject();
                out << student["roll_number"].toString() << ","
                    << student["name"].toString() << ","
                    << student["grade"].toString() << ","
                    << student["section"].toString() << ","
                    << subject["subject"].toString() << ","
                    << subject["marks_obtained"].toDouble() << ","
                    << subject["total_marks"].toDouble() << ","
                    << subject["percentage"].toDouble() << ","
                    << subject["grade"].toString() << "\\n";
            }
        }
    }
    
    file.close();
    return true;
}

QList<ReportTemplate> AdvancedReports::getReportTemplates()
{
    QList<ReportTemplate> templates;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM report_templates ORDER BY category, name")) {
        while (query.next()) {
            ReportTemplate temp;
            temp.id = query.value("id").toInt();
            temp.name = query.value("name").toString();
            temp.description = query.value("description").toString();
            temp.category = query.value("category").toString();
            temp.parameters = query.value("parameters").toString().split(",");
            temp.sqlQuery = query.value("sql_query").toString();
            temp.outputFormat = query.value("output_format").toString();
            temp.createdBy = query.value("created_by").toString();
            temp.createdAt = query.value("created_at").toDateTime();
            templates.append(temp);
        }
    }
    
    return templates;
}

bool AdvancedReports::addReportTemplate(const ReportTemplate &temp)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO report_templates (name, description, category, "
                 "parameters, sql_query, output_format, created_by) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(temp.name);
    query.addBindValue(temp.description);
    query.addBindValue(temp.category);
    query.addBindValue(temp.parameters.join(","));
    query.addBindValue(temp.sqlQuery);
    query.addBindValue(temp.outputFormat);
    query.addBindValue(temp.createdBy);
    
    if (!query.exec()) {
        qDebug() << "Failed to add report template:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<ReportAnalytics> AdvancedReports::getReportAnalytics()
{
    QList<ReportAnalytics> analytics;
    QSqlQuery query(Database::instance().database());
    
    // Attendance trend analysis
    if (query.exec(R"(
        SELECT date, 
               COUNT(CASE WHEN status = 'Present' THEN 1 END) as present_count,
               COUNT(CASE WHEN status = 'Absent' THEN 1 END) as absent_count,
               COUNT(*) as total_count
        FROM advanced_attendance
        WHERE date >= date('now', '-30 days')
        GROUP BY date
        ORDER BY date
    )")) {
        ReportAnalytics attendanceAnalytics;
        attendanceAnalytics.analyticsType = "Attendance Trend";
        attendanceAnalytics.period = "Last 30 Days";
        
        QJsonArray dataArray;
        while (query.next()) {
            QJsonObject dayObj;
            dayObj["date"] = query.value("date").toString();
            dayObj["present"] = query.value("present_count").toInt();
            dayObj["absent"] = query.value("absent_count").toInt();
            dayObj["total"] = query.value("total_count").toInt();
            
            double attendanceRate = query.value("total_count").toInt() > 0 ?
                (double)query.value("present_count").toInt() / query.value("total_count").toInt() * 100 : 0.0;
            dayObj["attendance_rate"] = attendanceRate;
            
            dataArray.append(dayObj);
        }
        
        attendanceAnalytics.data = QJsonDocument(dataArray);
        analytics.append(attendanceAnalytics);
    }
    
    // Grade-wise performance analysis
    if (query.exec(R"(
        SELECT es.grade, 
               AVG(er.marks_obtained / er.total_marks * 100) as avg_percentage,
               COUNT(DISTINCT es.roll_number) as student_count,
               COUNT(er.id) as exam_count
        FROM enhanced_students es
        LEFT JOIN exam_results er ON es.roll_number = er.student_roll
        WHERE er.exam_date >= date('now', '-90 days')
        GROUP BY es.grade
        ORDER BY es.grade
    )")) {
        ReportAnalytics performanceAnalytics;
        performanceAnalytics.analyticsType = "Grade Performance";
        performanceAnalytics.period = "Last 90 Days";
        
        QJsonArray dataArray;
        while (query.next()) {
            QJsonObject gradeObj;
            gradeObj["grade"] = query.value("grade").toString();
            gradeObj["average_percentage"] = query.value("avg_percentage").toDouble();
            gradeObj["student_count"] = query.value("student_count").toInt();
            gradeObj["exam_count"] = query.value("exam_count").toInt();
            
            dataArray.append(gradeObj);
        }
        
        performanceAnalytics.data = QJsonDocument(dataArray);
        analytics.append(performanceAnalytics);
    }
    
    return analytics;
}

bool AdvancedReports::scheduleReport(const ScheduledReport &scheduledReport)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO scheduled_reports (report_name, report_type, "
                 "parameters, schedule_type, schedule_value, output_format, "
                 "email_recipients, next_run, active, created_by) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(scheduledReport.reportName);
    query.addBindValue(scheduledReport.reportType);
    query.addBindValue(scheduledReport.parameters);
    query.addBindValue(scheduledReport.scheduleType);
    query.addBindValue(scheduledReport.scheduleValue);
    query.addBindValue(scheduledReport.outputFormat);
    query.addBindValue(scheduledReport.emailRecipients.join(","));
    query.addBindValue(scheduledReport.nextRun);
    query.addBindValue(scheduledReport.active);
    query.addBindValue(scheduledReport.createdBy);
    
    if (!query.exec()) {
        qDebug() << "Failed to schedule report:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<ScheduledReport> AdvancedReports::getScheduledReports()
{
    QList<ScheduledReport> reports;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM scheduled_reports WHERE active = 1 ORDER BY next_run")) {
        while (query.next()) {
            ScheduledReport report;
            report.id = query.value("id").toInt();
            report.reportName = query.value("report_name").toString();
            report.reportType = query.value("report_type").toString();
            report.parameters = query.value("parameters").toString();
            report.scheduleType = query.value("schedule_type").toString();
            report.scheduleValue = query.value("schedule_value").toString();
            report.outputFormat = query.value("output_format").toString();
            report.emailRecipients = query.value("email_recipients").toString().split(",");
            report.nextRun = query.value("next_run").toDateTime();
            report.active = query.value("active").toBool();
            report.createdBy = query.value("created_by").toString();
            reports.append(report);
        }
    }
    
    return reports;
}

ReportData AdvancedReports::generateStudentPerformanceSummary(const QMap<QString, QVariant> &parameters)
{
    ReportData report;
    report.reportType = "Student Performance Summary";
    
    QString rollNumber = parameters.value("roll_number").toString();
    QDate fromDate = parameters.value("from_date").toDate();
    QDate toDate = parameters.value("to_date").toDate();
    
    QSqlQuery query(Database::instance().database());
    
    // Get student academic performance
    query.prepare(R"(
        SELECT er.exam_name, er.subject, er.marks_obtained, er.total_marks,
               er.grade, er.exam_date, er.remarks
        FROM exam_results er
        WHERE er.student_roll = ? AND er.exam_date BETWEEN ? AND ?
        ORDER BY er.exam_date DESC, er.subject
    )");
    
    query.addBindValue(rollNumber);
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    
    QJsonArray academicArray;
    if (query.exec()) {
        while (query.next()) {
            QJsonObject examObj;
            examObj["exam_name"] = query.value("exam_name").toString();
            examObj["subject"] = query.value("subject").toString();
            examObj["marks_obtained"] = query.value("marks_obtained").toDouble();
            examObj["total_marks"] = query.value("total_marks").toDouble();
            examObj["percentage"] = (query.value("marks_obtained").toDouble() / 
                                   query.value("total_marks").toDouble()) * 100;
            examObj["grade"] = query.value("grade").toString();
            examObj["exam_date"] = query.value("exam_date").toString();
            examObj["remarks"] = query.value("remarks").toString();
            academicArray.append(examObj);
        }
    }
    
    QJsonObject reportObj;
    reportObj["student_roll"] = rollNumber;
    reportObj["academic_performance"] = academicArray;
    
    report.jsonData = QJsonDocument(reportObj);
    return report;
}

ReportData AdvancedReports::generateTeacherWorkloadAnalysis(const QMap<QString, QVariant> &parameters)
{
    ReportData report;
    report.reportType = "Teacher Workload Analysis";
    
    QSqlQuery query(Database::instance().database());
    
    // Get teacher class assignments and workload
    if (query.exec(R"(
        SELECT t.name, t.subject, t.qualification,
               COUNT(DISTINCT c.grade) as grades_taught,
               COUNT(DISTINCT c.section) as sections_taught,
               COUNT(DISTINCT es.roll_number) as total_students
        FROM teachers t
        LEFT JOIN classes c ON t.id = c.teacher_id
        LEFT JOIN enhanced_students es ON c.grade = es.grade AND c.section = es.section
        GROUP BY t.id, t.name, t.subject, t.qualification
        ORDER BY t.name
    )")) {
        QJsonArray teachersArray;
        
        while (query.next()) {
            QJsonObject teacherObj;
            teacherObj["name"] = query.value("name").toString();
            teacherObj["subject"] = query.value("subject").toString();
            teacherObj["qualification"] = query.value("qualification").toString();
            teacherObj["grades_taught"] = query.value("grades_taught").toInt();
            teacherObj["sections_taught"] = query.value("sections_taught").toInt();
            teacherObj["total_students"] = query.value("total_students").toInt();
            
            // Calculate workload score (simple algorithm)
            int workloadScore = query.value("grades_taught").toInt() * 2 +
                              query.value("sections_taught").toInt() * 3 +
                              query.value("total_students").toInt();
            teacherObj["workload_score"] = workloadScore;
            
            teachersArray.append(teacherObj);
        }
        
        QJsonObject reportObj;
        reportObj["teachers"] = teachersArray;
        
        report.jsonData = QJsonDocument(reportObj);
    }
    
    return report;
}

ReportData AdvancedReports::generateClassComparisonReport(const QMap<QString, QVariant> &parameters)
{
    ReportData report;
    report.reportType = "Class Comparison Report";
    
    QString grade = parameters.value("grade").toString();
    QDate fromDate = parameters.value("from_date").toDate();
    QDate toDate = parameters.value("to_date").toDate();
    
    QSqlQuery query(Database::instance().database());
    
    // Compare sections within a grade
    query.prepare(R"(
        SELECT es.section,
               COUNT(DISTINCT es.roll_number) as student_count,
               AVG(CASE WHEN aa.status = 'Present' OR aa.status = 'Late' THEN 1.0 ELSE 0.0 END) * 100 as avg_attendance,
               AVG(er.marks_obtained / er.total_marks * 100) as avg_academic_performance
        FROM enhanced_students es
        LEFT JOIN advanced_attendance aa ON es.roll_number = aa.student_roll
        AND aa.date BETWEEN ? AND ?
        LEFT JOIN exam_results er ON es.roll_number = er.student_roll
        AND er.exam_date BETWEEN ? AND ?
        WHERE es.grade = ?
        GROUP BY es.section
        ORDER BY es.section
    )");
    
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    query.addBindValue(grade);
    
    QJsonArray sectionsArray;
    if (query.exec()) {
        while (query.next()) {
            QJsonObject sectionObj;
            sectionObj["section"] = query.value("section").toString();
            sectionObj["student_count"] = query.value("student_count").toInt();
            sectionObj["average_attendance"] = query.value("avg_attendance").toDouble();
            sectionObj["average_academic_performance"] = query.value("avg_academic_performance").toDouble();
            sectionsArray.append(sectionObj);
        }
    }
    
    QJsonObject reportObj;
    reportObj["grade"] = grade;
    reportObj["sections"] = sectionsArray;
    
    report.jsonData = QJsonDocument(reportObj);
    return report;
}

ReportData AdvancedReports::generateTrendAnalysisReport(const QMap<QString, QVariant> &parameters)
{
    ReportData report;
    report.reportType = "Trend Analysis Report";
    
    QSqlQuery query(Database::instance().database());
    
    // Analyze trends over the last 6 months
    if (query.exec(R"(
        SELECT DATE(aa.date, 'start of month') as month,
               COUNT(CASE WHEN aa.status = 'Present' OR aa.status = 'Late' THEN 1 END) as present_count,
               COUNT(*) as total_count,
               (COUNT(CASE WHEN aa.status = 'Present' OR aa.status = 'Late' THEN 1 END) * 100.0 / COUNT(*)) as attendance_rate
        FROM advanced_attendance aa
        WHERE aa.date >= date('now', '-6 months')
        GROUP BY DATE(aa.date, 'start of month')
        ORDER BY month
    )")) {
        QJsonArray trendsArray;
        
        while (query.next()) {
            QJsonObject monthObj;
            monthObj["month"] = query.value("month").toString();
            monthObj["present_count"] = query.value("present_count").toInt();
            monthObj["total_count"] = query.value("total_count").toInt();
            monthObj["attendance_rate"] = query.value("attendance_rate").toDouble();
            trendsArray.append(monthObj);
        }
        
        QJsonObject reportObj;
        reportObj["attendance_trends"] = trendsArray;
        
        report.jsonData = QJsonDocument(reportObj);
    }
    
    return report;
}

bool AdvancedReports::createDatabaseTables()
{
    QSqlQuery query(Database::instance().database());
    
    // Create report templates table
    QString createTemplatesTable = R"(
        CREATE TABLE IF NOT EXISTS report_templates (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            description TEXT,
            category TEXT,
            parameters TEXT,
            sql_query TEXT NOT NULL,
            output_format TEXT DEFAULT 'PDF',
            created_by TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createTemplatesTable)) {
        qDebug() << "Failed to create report_templates table:" << query.lastError().text();
        return false;
    }
    
    // Create scheduled reports table
    QString createScheduledTable = R"(
        CREATE TABLE IF NOT EXISTS scheduled_reports (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            report_name TEXT NOT NULL,
            report_type TEXT NOT NULL,
            parameters TEXT,
            schedule_type TEXT NOT NULL,
            schedule_value TEXT NOT NULL,
            output_format TEXT DEFAULT 'PDF',
            email_recipients TEXT,
            next_run TIMESTAMP NOT NULL,
            last_run TIMESTAMP,
            active BOOLEAN DEFAULT 1,
            created_by TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createScheduledTable)) {
        qDebug() << "Failed to create scheduled_reports table:" << query.lastError().text();
        return false;
    }
    
    // Create report history table
    QString createHistoryTable = R"(
        CREATE TABLE IF NOT EXISTS report_history (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            report_name TEXT NOT NULL,
            report_type TEXT NOT NULL,
            parameters TEXT,
            generated_date TIMESTAMP NOT NULL,
            file_path TEXT,
            file_size INTEGER,
            generated_by TEXT,
            status TEXT DEFAULT 'Generated'
        )
    )";
    
    if (!query.exec(createHistoryTable)) {
        qDebug() << "Failed to create report_history table:" << query.lastError().text();
        return false;
    }
    
    return true;
}
