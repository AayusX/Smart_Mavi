#include "reports/reports.h"
#include "database/database.h"
#include "models/teacher.h"
#include "models/student.h"
#include "models/class.h"
#include "models/attendance.h"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QStandardPaths>
#include <QApplication>
#include <cstdlib>

Reports::Reports(Database *database, QObject *parent)
    : QObject(parent)
    , m_database(database)
{
}

QString Reports::generateTeacherReport(const QDate &startDate, const QDate &endDate)
{
    QString report;
    QTextStream stream(&report);
    
    stream << formatReportHeader("Teacher Report", startDate, endDate);
    stream << "\n";
    
    // Get teacher data from database
    QList<Teacher> teachers = m_database->getAllTeachers();
    
    if (teachers.isEmpty()) {
        stream << "No teachers found in the system.\n";
    } else {
        stream << formatTeacherData(teachers);
        
        // Add statistics
        stream << "\n=== STATISTICS ===\n";
        stream << "Total Teachers: " << teachers.size() << "\n";
        stream << "Report Period: " << formatDate(startDate) << " to " << formatDate(endDate) << "\n";
    }
    
    stream << formatReportFooter();
    
    return report;
}

QString Reports::generateStudentReport(int classId, const QDate &startDate, const QDate &endDate)
{
    QString report;
    QTextStream stream(&report);
    
    stream << formatReportHeader("Student Report", startDate, endDate);
    stream << "\n";
    
    // Get student data from database
    QList<Student> students = m_database->getStudentsByClass(classId);
    
    if (students.isEmpty()) {
        stream << "No students found for the specified class.\n";
    } else {
        stream << formatStudentData(students);
        
        // Add attendance statistics
        double attendancePercentage = calculateAttendancePercentage(classId, startDate, endDate);
        
        stream << "\n=== STATISTICS ===\n";
        stream << "Total Students: " << students.size() << "\n";
        stream << "Average Attendance: " << QString::number(attendancePercentage, 'f', 2) << "%\n";
        stream << "Report Period: " << formatDate(startDate) << " to " << formatDate(endDate) << "\n";
    }
    
    stream << formatReportFooter();
    
    return report;
}

QString Reports::generateAttendanceReport(int classId, const QDate &date)
{
    QString report;
    QTextStream stream(&report);
    
    stream << formatReportHeader("Attendance Report", date, date);
    stream << "\n";
    
    // Get attendance data from database
    QList<Attendance> attendance = m_database->getAttendanceByClass(classId, date);
    
    if (attendance.isEmpty()) {
        stream << "No attendance records found for the specified class and date.\n";
    } else {
        stream << formatAttendanceData(attendance);
        
        // Calculate statistics
        int totalStudents = calculateTotalStudents(classId);
        int present = 0, absent = 0, leave = 0, late = 0;
        
        for (const Attendance &att : attendance) {
            switch (att.getStatus()) {
                case Attendance::Present: present++; break;
                case Attendance::Absent: absent++; break;
                case Attendance::Leave: leave++; break;
                case Attendance::Late: late++; break;
            }
        }
        
        stream << "\n=== STATISTICS ===\n";
        stream << "Date: " << formatDate(date) << "\n";
        stream << "Total Students: " << totalStudents << "\n";
        stream << "Present: " << present << "\n";
        stream << "Absent: " << absent << "\n";
        stream << "Leave: " << leave << "\n";
        stream << "Late: " << late << "\n";
        stream << "Attendance Rate: " << QString::number((double)present / totalStudents * 100, 'f', 2) << "%\n";
    }
    
    stream << formatReportFooter();
    
    return report;
}

QString Reports::generateClassReport(int classId, const QDate &startDate, const QDate &endDate)
{
    QString report;
    QTextStream stream(&report);
    
    stream << formatReportHeader("Class Report", startDate, endDate);
    stream << "\n";
    
    // Get class information
    QList<Class> classes = m_database->getAllClasses();
    Class targetClass;
    bool found = false;
    
    for (const Class &cls : classes) {
        if (cls.getId() == classId) {
            targetClass = cls;
            found = true;
            break;
        }
    }
    
    if (!found) {
        stream << "Class not found.\n";
    } else {
        stream << "=== CLASS INFORMATION ===\n";
        stream << "Grade: " << targetClass.getGrade() << "\n";
        stream << "Section: " << targetClass.getDescription() << "\n";
        stream << "Teacher: " << targetClass.getTeacherId() << "\n";
        stream << "Capacity: " << targetClass.getCapacity() << "\n";
        stream << "Room Number: " << targetClass.getRoomNumber() << "\n";
        stream << "\n";
        
        // Get students in this class
        QList<Student> students = m_database->getStudentsByClass(classId);
        stream << formatStudentData(students);
        
        // Add statistics
        double attendancePercentage = calculateAttendancePercentage(classId, startDate, endDate);
        
        stream << "\n=== STATISTICS ===\n";
        stream << "Total Students: " << students.size() << "\n";
        stream << "Average Attendance: " << QString::number(attendancePercentage, 'f', 2) << "%\n";
        stream << "Report Period: " << formatDate(startDate) << " to " << formatDate(endDate) << "\n";
    }
    
    stream << formatReportFooter();
    
    return report;
}

QString Reports::generateSummaryReport(const QDate &startDate, const QDate &endDate)
{
    QString report;
    QTextStream stream(&report);
    
    stream << formatReportHeader("Summary Report", startDate, endDate);
    stream << "\n";
    
    // Get overall statistics
    int totalTeachers = calculateTotalTeachers();
    int totalClasses = calculateTotalClasses();
    
    // Calculate total students across all classes
    int totalStudents = 0;
    QList<Class> classes = m_database->getAllClasses();
    for (const Class &cls : classes) {
        totalStudents += calculateTotalStudents(cls.getId());
    }
    
    stream << "=== SYSTEM OVERVIEW ===\n";
    stream << "Total Teachers: " << totalTeachers << "\n";
    stream << "Total Classes: " << totalClasses << "\n";
    stream << "Total Students: " << totalStudents << "\n";
    stream << "Report Period: " << formatDate(startDate) << " to " << formatDate(endDate) << "\n";
    stream << "\n";
    
    // Top performing classes
    QList<QPair<QString, double>> topClasses = getTopPerformingClasses(startDate, endDate);
    
    stream << "=== TOP PERFORMING CLASSES ===\n";
    for (const auto &pair : topClasses) {
        stream << pair.first << ": " << QString::number(pair.second, 'f', 2) << "%\n";
    }
    
    stream << formatReportFooter();
    
    return report;
}

bool Reports::exportToCSV(const QString &content, const QString &filename)
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = documentsPath + "/" + filename;
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    out << createCSVContent(content);
    file.close();
    
    return true;
}

bool Reports::exportToExcel(const QString &content, const QString &filename)
{
    // For now, export as CSV with .xlsx extension
    // Full Excel support would require additional libraries
    QString csvFilename = filename;
    csvFilename.replace(".xlsx", ".csv");
    return exportToCSV(content, csvFilename);
}

bool Reports::exportToHTML(const QString &content, const QString &filename)
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = documentsPath + "/" + filename;
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return false;
    }
    
    QTextStream out(&file);
    out << createHTMLTemplate(content);
    file.close();
    
    return true;
}

QChart* Reports::generateAttendanceChart(int classId, const QDate &startDate, const QDate &endDate)
{
    QChart *chart = new QChart();
    QBarSeries *series = createAttendanceBarSeries(classId, startDate, endDate);
    setupBarChart(chart, series, "Attendance Chart");
    return chart;
}

QChart* Reports::generateStudentPerformanceChart(int classId, const QDate &startDate, const QDate &endDate)
{
    QChart *chart = new QChart();
    QBarSeries *series = createStudentPerformanceBarSeries(classId, startDate, endDate);
    setupBarChart(chart, series, "Student Performance Chart");
    return chart;
}

QChart* Reports::generateTeacherWorkloadChart(const QDate &startDate, const QDate &endDate)
{
    QChart *chart = new QChart();
    QBarSeries *series = createTeacherWorkloadBarSeries(startDate, endDate);
    setupBarChart(chart, series, "Teacher Workload Chart");
    return chart;
}

QChart* Reports::generateClassComparisonChart(const QDate &date)
{
    QChart *chart = new QChart();
    QBarSeries *series = createClassComparisonBarSeries(date);
    setupBarChart(chart, series, "Class Comparison Chart");
    return chart;
}

QString Reports::formatReportHeader(const QString &title, const QDate &startDate, const QDate &endDate)
{
    QString header;
    QTextStream stream(&header);
    
    stream << "========================================\n";
    stream << "       SMART MA.VI MANAGER\n";
    stream << "        " << title << "\n";
    stream << "========================================\n";
    stream << "Generated on: " << formatDateTime(QDateTime::currentDateTime()) << "\n";
    if (startDate != endDate) {
        stream << "Period: " << formatDate(startDate) << " - " << formatDate(endDate) << "\n";
    } else {
        stream << "Date: " << formatDate(startDate) << "\n";
    }
    stream << "School: Shree MA.VI Imilya\n";
    stream << "========================================\n";
    
    return header;
}

QString Reports::formatReportFooter()
{
    QString footer;
    QTextStream stream(&footer);
    
    stream << "\n========================================\n";
    stream << "Report generated by Smart MA.VI Manager\n";
    stream << "© 2024 Tech07. All rights reserved.\n";
    stream << "========================================\n";
    
    return footer;
}

QString Reports::formatDate(const QDate &date)
{
    return date.toString("yyyy-MM-dd");
}

QString Reports::formatDateTime(const QDateTime &dateTime)
{
    return dateTime.toString("yyyy-MM-dd hh:mm:ss");
}

double Reports::calculateAttendancePercentage(int classId, const QDate &startDate, const QDate &endDate)
{
    // Simplified calculation - in real implementation, would iterate through date range
    int totalStudents = calculateTotalStudents(classId);
    if (totalStudents == 0) return 0.0;
    
    // Mock calculation - would need actual attendance data
    return 85.5; // Placeholder
}

int Reports::calculateTotalStudents(int classId)
{
    QList<Student> students = m_database->getStudentsByClass(classId);
    return students.size();
}

int Reports::calculateTotalTeachers()
{
    QList<Teacher> teachers = m_database->getAllTeachers();
    return teachers.size();
}

int Reports::calculateTotalClasses()
{
    QList<Class> classes = m_database->getAllClasses();
    return classes.size();
}

QList<QPair<QString, double>> Reports::getTopPerformingStudents(int classId, const QDate &startDate, const QDate &endDate)
{
    QList<QPair<QString, double>> result;
    QList<Student> students = m_database->getStudentsByClass(classId);
    
    // Mock data - in real implementation, calculate actual performance
    for (const Student &student : students) {
        double performance = 80.0 + (rand() % 20); // Mock performance 80-100%
        result.append(qMakePair(student.getName(), performance));
    }
    
    return result;
}

QList<QPair<QString, double>> Reports::getTopPerformingClasses(const QDate &startDate, const QDate &endDate)
{
    QList<QPair<QString, double>> result;
    QList<Class> classes = m_database->getAllClasses();
    
    // Mock data - in real implementation, calculate actual performance
    for (const Class &cls : classes) {
        double performance = 75.0 + (rand() % 25); // Mock performance 75-100%
        QString className = "Grade " + QString::number(cls.getGrade()) + " " + cls.getDescription();
        result.append(qMakePair(className, performance));
    }
    
    return result;
}

QString Reports::formatTeacherData(const QList<Teacher> &teachers)
{
    QString result;
    QTextStream stream(&result);
    
    stream << "=== TEACHER INFORMATION ===\n";
    stream << QString("%-5s %-20s %-15s %-15s %-10s\n").arg("ID", "Name", "Subject", "Contact", "Class");
    stream << QString("-").repeated(70) << "\n";
    
    for (const Teacher &teacher : teachers) {
        stream << QString("%-5s %-20s %-15s %-15s %-10s\n")
                  .arg(QString::number(teacher.getId()))
                  .arg(teacher.getName().left(19))
                  .arg(teacher.getSubject().left(14))
                  .arg(teacher.getContact().left(14))
                  .arg(QString::number(teacher.getAssignedClass()).left(9));
    }
    
    return result;
}

QString Reports::formatStudentData(const QList<Student> &students)
{
    QString result;
    QTextStream stream(&result);
    
    stream << "=== STUDENT INFORMATION ===\n";
    stream << QString("%-5s %-20s %-10s %-20s %-15s\n").arg("Roll", "Name", "Age", "Guardian", "Contact");
    stream << QString("-").repeated(75) << "\n";
    
    for (const Student &student : students) {
        stream << QString("%-5s %-20s %-10s %-20s %-15s\n")
                  .arg(student.getRollNo())
                  .arg(student.getName().left(19))
                  .arg(QString::number(student.getAge()))
                  .arg(student.getGuardianName().left(19))
                  .arg(student.getGuardianContact().left(14));
    }
    
    return result;
}

QString Reports::formatAttendanceData(const QList<Attendance> &attendance)
{
    QString result;
    QTextStream stream(&result);
    
    stream << "=== ATTENDANCE RECORDS ===\n";
    stream << QString("%-10s %-20s %-10s %-10s\n").arg("Student ID", "Name", "Status", "Time");
    stream << QString("-").repeated(55) << "\n";
    
    for (const Attendance &att : attendance) {
        QString statusStr;
        switch (att.getStatus()) {
            case Attendance::Present: statusStr = "Present"; break;
            case Attendance::Absent: statusStr = "Absent"; break;
            case Attendance::Leave: statusStr = "Leave"; break;
            case Attendance::Late: statusStr = "Late"; break;
        }
        
        stream << QString("%-10s %-20s %-10s %-10s\n")
                  .arg(QString::number(att.getStudentId()))
                  .arg("Student") // Would need to fetch student name
                  .arg(statusStr)
                  .arg(att.getDate().toString("hh:mm"));
    }
    
    return result;
}

QString Reports::formatClassData(const QList<Class> &classes)
{
    QString result;
    QTextStream stream(&result);
    
    stream << "=== CLASS INFORMATION ===\n";
    stream << QString("%-5s %-10s %-10s %-20s %-10s\n").arg("ID", "Grade", "Section", "Teacher", "Room");
    stream << QString("-").repeated(60) << "\n";
    
    for (const Class &cls : classes) {
        stream << QString("%-5s %-10s %-10s %-20s %-10s\n")
                  .arg(QString::number(cls.getId()))
                  .arg(QString::number(cls.getGrade()))
                  .arg(cls.getDescription().left(9))
                  .arg(QString::number(cls.getTeacherId()).left(19))
                  .arg(cls.getRoomNumber().left(9));
    }
    
    return result;
}

QString Reports::createHTMLTemplate(const QString &content)
{
    QString html = "<!DOCTYPE html>\n<html>\n<head>\n";
    html += "<meta charset='UTF-8'>\n";
    html += "<title>Smart MA.VI Manager Report</title>\n";
    html += "<style>\n";
    html += "body { font-family: Arial, sans-serif; margin: 20px; }\n";
    html += "pre { background-color: #f5f5f5; padding: 15px; border-radius: 5px; }\n";
    html += "h1 { color: #2c3e50; }\n";
    html += "</style>\n";
    html += "</head>\n<body>\n";
    html += "<h1>Smart MA.VI Manager Report</h1>\n";
    html += "<pre>" + content + "</pre>\n";
    html += "</body>\n</html>";
    return html;
}

QString Reports::createCSVContent(const QString &content)
{
    // Convert plain text to CSV format
    // This is a simplified conversion
    QString csv = content;
    csv.replace("\n", "\r\n"); // Proper line endings for CSV
    return csv;
}

QString Reports::createExcelContent(const QString &content)
{
    // For now, return CSV content
    // Full Excel support would require additional libraries
    return createCSVContent(content);
}

// Chart creation methods (simplified implementations)
QBarSeries* Reports::createAttendanceBarSeries(int classId, const QDate &startDate, const QDate &endDate)
{
    QBarSeries *series = new QBarSeries();
    
    QBarSet *presentSet = new QBarSet("Present");
    QBarSet *absentSet = new QBarSet("Absent");
    QBarSet *leaveSet = new QBarSet("Leave");
    QBarSet *lateSet = new QBarSet("Late");
    
    // Mock data - in real implementation, query actual data
    *presentSet << 25 << 22 << 28 << 30 << 27;
    *absentSet << 3 << 5 << 2 << 1 << 3;
    *leaveSet << 1 << 2 << 0 << 1 << 2;
    *lateSet << 1 << 1 << 0 << 0 << 1;
    
    series->append(presentSet);
    series->append(absentSet);
    series->append(leaveSet);
    series->append(lateSet);
    
    return series;
}

QPieSeries* Reports::createAttendancePieSeries(int classId, const QDate &date)
{
    QPieSeries *series = new QPieSeries();
    
    // Mock data
    series->append("Present", 25);
    series->append("Absent", 3);
    series->append("Leave", 1);
    series->append("Late", 1);
    
    return series;
}

QBarSeries* Reports::createStudentPerformanceBarSeries(int classId, const QDate &startDate, const QDate &endDate)
{
    QBarSeries *series = new QBarSeries();
    
    QBarSet *performanceSet = new QBarSet("Performance");
    
    // Mock data - in real implementation, calculate actual performance
    *performanceSet << 85 << 92 << 78 << 88 << 94;
    
    series->append(performanceSet);
    
    return series;
}

QBarSeries* Reports::createTeacherWorkloadBarSeries(const QDate &startDate, const QDate &endDate)
{
    QBarSeries *series = new QBarSeries();
    
    QBarSet *workloadSet = new QBarSet("Classes Taught");
    
    // Mock data
    *workloadSet << 5 << 4 << 6 << 3 << 5;
    
    series->append(workloadSet);
    
    return series;
}

QBarSeries* Reports::createClassComparisonBarSeries(const QDate &date)
{
    QBarSeries *series = new QBarSeries();
    
    QBarSet *attendanceSet = new QBarSet("Attendance Rate");
    
    // Mock data
    *attendanceSet << 85 << 90 << 88 << 92 << 87;
    
    series->append(attendanceSet);
    
    return series;
}

void Reports::setupChart(QChart *chart, const QString &title)
{
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);
}

void Reports::setupBarChart(QChart *chart, QBarSeries *series, const QString &title)
{
    setupChart(chart, title);
    chart->addSeries(series);
    chart->createDefaultAxes();
}

void Reports::setupPieChart(QChart *chart, QPieSeries *series, const QString &title)
{
    setupChart(chart, title);
    chart->addSeries(series);
}

QString Reports::getReportTemplate(ReportType type)
{
    switch (type) {
        case TeacherReport:
            return "Teacher Report Template";
        case StudentReport:
            return "Student Report Template";
        case AttendanceReport:
            return "Attendance Report Template";
        case ClassReport:
            return "Class Report Template";
        case SummaryReport:
            return "Summary Report Template";
        default:
            return "Generic Report Template";
    }
}
