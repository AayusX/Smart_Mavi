#include "attendance/advancedattendance.h"
#include "database/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QTextStream>

AdvancedAttendance::AdvancedAttendance(QObject *parent)
    : QObject(parent)
    , m_autoMarkTimer(new QTimer(this))
{
    connect(m_autoMarkTimer, &QTimer::timeout, this, &AdvancedAttendance::processAutoAttendance);
    
    // Check for auto attendance every minute
    m_autoMarkTimer->start(60000);
}

AdvancedAttendance::~AdvancedAttendance()
{
}

bool AdvancedAttendance::markAttendance(const AttendanceEntry &entry)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT OR REPLACE INTO advanced_attendance "
                 "(student_roll, date, time_in, time_out, status, method, "
                 "location, notes, marked_by) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(entry.studentRoll);
    query.addBindValue(entry.date);
    query.addBindValue(entry.timeIn);
    query.addBindValue(entry.timeOut);
    query.addBindValue(entry.status);
    query.addBindValue(entry.method);
    query.addBindValue(entry.location);
    query.addBindValue(entry.notes);
    query.addBindValue(entry.markedBy);
    
    if (!query.exec()) {
        qDebug() << "Failed to mark attendance:" << query.lastError().text();
        return false;
    }
    
    emit attendanceMarked(entry.studentRoll, entry.status);
    return true;
}

bool AdvancedAttendance::markTimeOut(const QString &studentRoll, const QTime &timeOut)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("UPDATE advanced_attendance SET time_out = ? "
                 "WHERE student_roll = ? AND date = ? AND time_out IS NULL");
    
    query.addBindValue(timeOut);
    query.addBindValue(studentRoll);
    query.addBindValue(QDate::currentDate());
    
    if (!query.exec()) {
        qDebug() << "Failed to mark time out:" << query.lastError().text();
        return false;
    }
    
    emit timeOutMarked(studentRoll, timeOut);
    return true;
}

QList<AttendanceEntry> AdvancedAttendance::getAttendance(const QDate &date, const QString &grade, const QString &section)
{
    QList<AttendanceEntry> entries;
    QSqlQuery query(Database::instance().database());
    
    QString queryStr = "SELECT aa.*, es.name, es.grade, es.section FROM advanced_attendance aa "
                      "JOIN enhanced_students es ON aa.student_roll = es.roll_number "
                      "WHERE aa.date = ?";
    
    QStringList params;
    params.append(date.toString(Qt::ISODate));
    
    if (!grade.isEmpty()) {
        queryStr += " AND es.grade = ?";
        params.append(grade);
    }
    
    if (!section.isEmpty()) {
        queryStr += " AND es.section = ?";
        params.append(section);
    }
    
    queryStr += " ORDER BY es.grade, es.section, es.name";
    
    query.prepare(queryStr);
    for (const QString &param : params) {
        query.addBindValue(param);
    }
    
    if (query.exec()) {
        while (query.next()) {
            AttendanceEntry entry;
            entry.id = query.value("id").toInt();
            entry.studentRoll = query.value("student_roll").toString();
            entry.studentName = query.value("name").toString();
            entry.grade = query.value("grade").toString();
            entry.section = query.value("section").toString();
            entry.date = query.value("date").toDate();
            entry.timeIn = query.value("time_in").toTime();
            entry.timeOut = query.value("time_out").toTime();
            entry.status = query.value("status").toString();
            entry.method = query.value("method").toString();
            entry.location = query.value("location").toString();
            entry.notes = query.value("notes").toString();
            entry.markedBy = query.value("marked_by").toString();
            entries.append(entry);
        }
    }
    
    return entries;
}

AttendanceStats AdvancedAttendance::getAttendanceStats(const QString &studentRoll, const QDate &fromDate, const QDate &toDate)
{
    AttendanceStats stats;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT status, COUNT(*) as count FROM advanced_attendance "
                 "WHERE student_roll = ? AND date BETWEEN ? AND ? "
                 "GROUP BY status");
    
    query.addBindValue(studentRoll);
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    
    if (query.exec()) {
        while (query.next()) {
            QString status = query.value("status").toString();
            int count = query.value("count").toInt();
            
            if (status == "Present") {
                stats.presentDays = count;
            } else if (status == "Absent") {
                stats.absentDays = count;
            } else if (status == "Late") {
                stats.lateDays = count;
            } else if (status == "Excused") {
                stats.excusedDays = count;
            }
        }
    }
    
    stats.totalDays = stats.presentDays + stats.absentDays + stats.lateDays + stats.excusedDays;
    stats.attendancePercentage = stats.totalDays > 0 ? 
        (double)(stats.presentDays + stats.lateDays + stats.excusedDays) / stats.totalDays * 100 : 0.0;
    
    return stats;
}

QMap<QString, AttendanceStats> AdvancedAttendance::getClassAttendanceStats(const QString &grade, 
                                                                          const QString &section, 
                                                                          const QDate &fromDate, 
                                                                          const QDate &toDate)
{
    QMap<QString, AttendanceStats> classStats;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT es.roll_number, aa.status, COUNT(*) as count "
                 "FROM enhanced_students es "
                 "LEFT JOIN advanced_attendance aa ON es.roll_number = aa.student_roll "
                 "AND aa.date BETWEEN ? AND ? "
                 "WHERE es.grade = ? AND es.section = ? "
                 "GROUP BY es.roll_number, aa.status");
    
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    query.addBindValue(grade);
    query.addBindValue(section);
    
    if (query.exec()) {
        while (query.next()) {
            QString rollNumber = query.value("roll_number").toString();
            QString status = query.value("status").toString();
            int count = query.value("count").toInt();
            
            if (!classStats.contains(rollNumber)) {
                classStats[rollNumber] = AttendanceStats();
            }
            
            AttendanceStats &stats = classStats[rollNumber];
            
            if (status == "Present") {
                stats.presentDays = count;
            } else if (status == "Absent") {
                stats.absentDays = count;
            } else if (status == "Late") {
                stats.lateDays = count;
            } else if (status == "Excused") {
                stats.excusedDays = count;
            }
        }
    }
    
    // Calculate totals and percentages
    for (auto &stats : classStats) {
        stats.totalDays = stats.presentDays + stats.absentDays + stats.lateDays + stats.excusedDays;
        stats.attendancePercentage = stats.totalDays > 0 ? 
            (double)(stats.presentDays + stats.lateDays + stats.excusedDays) / stats.totalDays * 100 : 0.0;
    }
    
    return classStats;
}

bool AdvancedAttendance::setBiometricData(const QString &studentRoll, const BiometricData &data)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT OR REPLACE INTO biometric_data "
                 "(student_roll, fingerprint_hash, face_encoding, rfid_code, "
                 "active, created_date) VALUES (?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(studentRoll);
    query.addBindValue(data.fingerprintHash);
    query.addBindValue(data.faceEncoding);
    query.addBindValue(data.rfidCode);
    query.addBindValue(data.active);
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Failed to set biometric data:" << query.lastError().text();
        return false;
    }
    
    return true;
}

BiometricData AdvancedAttendance::getBiometricData(const QString &studentRoll)
{
    BiometricData data;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM biometric_data WHERE student_roll = ? AND active = 1");
    query.addBindValue(studentRoll);
    
    if (query.exec() && query.next()) {
        data.studentRoll = query.value("student_roll").toString();
        data.fingerprintHash = query.value("fingerprint_hash").toString();
        data.faceEncoding = query.value("face_encoding").toString();
        data.rfidCode = query.value("rfid_code").toString();
        data.active = query.value("active").toBool();
        data.createdDate = query.value("created_date").toDateTime();
    }
    
    return data;
}

bool AdvancedAttendance::verifyBiometric(const QString &biometricHash, const QString &method)
{
    QSqlQuery query(Database::instance().database());
    
    if (method == "Fingerprint") {
        query.prepare("SELECT student_roll FROM biometric_data WHERE fingerprint_hash = ? AND active = 1");
    } else if (method == "Face") {
        query.prepare("SELECT student_roll FROM biometric_data WHERE face_encoding = ? AND active = 1");
    } else if (method == "RFID") {
        query.prepare("SELECT student_roll FROM biometric_data WHERE rfid_code = ? AND active = 1");
    } else {
        return false;
    }
    
    query.addBindValue(biometricHash);
    
    if (query.exec() && query.next()) {
        QString studentRoll = query.value("student_roll").toString();
        
        // Auto-mark attendance
        AttendanceEntry entry;
        entry.studentRoll = studentRoll;
        entry.date = QDate::currentDate();
        entry.timeIn = QTime::currentTime();
        entry.status = "Present";
        entry.method = method;
        entry.location = "Main Entrance";
        entry.markedBy = "Auto-Biometric";
        
        return markAttendance(entry);
    }
    
    return false;
}

bool AdvancedAttendance::addAttendanceRule(const AttendanceRule &rule)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO attendance_rules (rule_name, rule_type, conditions, "
                 "actions, priority, active, grade, section) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(rule.ruleName);
    query.addBindValue(rule.ruleType);
    query.addBindValue(rule.conditions);
    query.addBindValue(rule.actions);
    query.addBindValue(rule.priority);
    query.addBindValue(rule.active);
    query.addBindValue(rule.grade);
    query.addBindValue(rule.section);
    
    if (!query.exec()) {
        qDebug() << "Failed to add attendance rule:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<AttendanceRule> AdvancedAttendance::getAttendanceRules()
{
    QList<AttendanceRule> rules;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM attendance_rules WHERE active = 1 ORDER BY priority")) {
        while (query.next()) {
            AttendanceRule rule;
            rule.id = query.value("id").toInt();
            rule.ruleName = query.value("rule_name").toString();
            rule.ruleType = query.value("rule_type").toString();
            rule.conditions = query.value("conditions").toString();
            rule.actions = query.value("actions").toString();
            rule.priority = query.value("priority").toInt();
            rule.active = query.value("active").toBool();
            rule.grade = query.value("grade").toString();
            rule.section = query.value("section").toString();
            rules.append(rule);
        }
    }
    
    return rules;
}

void AdvancedAttendance::processAutoAttendance()
{
    // Auto-mark students as late if they haven't arrived by a certain time
    QTime cutoffTime = QTime(9, 0); // 9:00 AM cutoff
    QTime currentTime = QTime::currentTime();
    QDate currentDate = QDate::currentDate();
    
    if (currentTime >= cutoffTime) {
        QSqlQuery query(Database::instance().database());
        
        // Find students who haven't been marked present today
        query.prepare("SELECT es.roll_number FROM enhanced_students es "
                     "LEFT JOIN advanced_attendance aa ON es.roll_number = aa.student_roll "
                     "AND aa.date = ? "
                     "WHERE aa.student_roll IS NULL");
        
        query.addBindValue(currentDate);
        
        if (query.exec()) {
            while (query.next()) {
                QString studentRoll = query.value("roll_number").toString();
                
                AttendanceEntry entry;
                entry.studentRoll = studentRoll;
                entry.date = currentDate;
                entry.status = "Absent";
                entry.method = "Auto-System";
                entry.location = "Auto-Generated";
                entry.markedBy = "System";
                entry.notes = "Auto-marked absent - no check-in recorded";
                
                markAttendance(entry);
            }
        }
    }
}

bool AdvancedAttendance::generateAttendanceReport(const QString &grade, const QString &section,
                                                 const QDate &fromDate, const QDate &toDate)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO attendance_reports (grade, section, from_date, to_date, "
                 "generated_date, report_type, status) "
                 "VALUES (?, ?, ?, ?, ?, 'Detailed', 'Generated')");
    
    query.addBindValue(grade);
    query.addBindValue(section);
    query.addBindValue(fromDate);
    query.addBindValue(toDate);
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Failed to generate attendance report:" << query.lastError().text();
        return false;
    }
    
    emit reportGenerated(grade, section);
    return true;
}

QList<AttendanceAlert> AdvancedAttendance::getAttendanceAlerts()
{
    QList<AttendanceAlert> alerts;
    QSqlQuery query(Database::instance().database());
    
    // Get students with low attendance (less than 75%)
    QString queryStr = R"(
        SELECT es.roll_number, es.name, es.grade, es.section, es.parent_phone,
               COUNT(CASE WHEN aa.status = 'Present' OR aa.status = 'Late' THEN 1 END) as present_count,
               COUNT(*) as total_count,
               (COUNT(CASE WHEN aa.status = 'Present' OR aa.status = 'Late' THEN 1 END) * 100.0 / COUNT(*)) as percentage
        FROM enhanced_students es
        LEFT JOIN advanced_attendance aa ON es.roll_number = aa.student_roll
        WHERE aa.date >= date('now', '-30 days')
        GROUP BY es.roll_number, es.name, es.grade, es.section, es.parent_phone
        HAVING percentage < 75
        ORDER BY percentage ASC
    )";
    
    if (query.exec(queryStr)) {
        while (query.next()) {
            AttendanceAlert alert;
            alert.studentRoll = query.value("roll_number").toString();
            alert.studentName = query.value("name").toString();
            alert.grade = query.value("grade").toString();
            alert.section = query.value("section").toString();
            alert.alertType = "Low Attendance";
            alert.message = QString("Student %1 (Roll: %2) has attendance of %.1f%% in the last 30 days")
                           .arg(query.value("name").toString())
                           .arg(query.value("roll_number").toString())
                           .arg(query.value("percentage").toDouble());
            alert.severity = "Medium";
            alert.parentPhone = query.value("parent_phone").toString();
            alert.alertDate = QDateTime::currentDateTime();
            alerts.append(alert);
        }
    }
    
    // Get students absent for consecutive days
    QString consecutiveAbsentQuery = R"(
        WITH consecutive_absents AS (
            SELECT student_roll, COUNT(*) as consecutive_days
            FROM (
                SELECT student_roll, date,
                       ROW_NUMBER() OVER (PARTITION BY student_roll ORDER BY date) -
                       ROW_NUMBER() OVER (PARTITION BY student_roll, status ORDER BY date) as grp
                FROM advanced_attendance
                WHERE status = 'Absent' AND date >= date('now', '-7 days')
            )
            GROUP BY student_roll, grp
            HAVING consecutive_days >= 3
        )
        SELECT es.roll_number, es.name, es.grade, es.section, es.parent_phone, ca.consecutive_days
        FROM consecutive_absents ca
        JOIN enhanced_students es ON ca.student_roll = es.roll_number
    )";
    
    if (query.exec(consecutiveAbsentQuery)) {
        while (query.next()) {
            AttendanceAlert alert;
            alert.studentRoll = query.value("roll_number").toString();
            alert.studentName = query.value("name").toString();
            alert.grade = query.value("grade").toString();
            alert.section = query.value("section").toString();
            alert.alertType = "Consecutive Absence";
            alert.message = QString("Student %1 (Roll: %2) has been absent for %3 consecutive days")
                           .arg(query.value("name").toString())
                           .arg(query.value("roll_number").toString())
                           .arg(query.value("consecutive_days").toInt());
            alert.severity = "High";
            alert.parentPhone = query.value("parent_phone").toString();
            alert.alertDate = QDateTime::currentDateTime();
            alerts.append(alert);
        }
    }
    
    return alerts;
}

bool AdvancedAttendance::addLeaveRequest(const LeaveRequest &request)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO leave_requests (student_roll, from_date, to_date, "
                 "reason, request_type, submitted_by, status, submitted_date) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(request.studentRoll);
    query.addBindValue(request.fromDate);
    query.addBindValue(request.toDate);
    query.addBindValue(request.reason);
    query.addBindValue(request.requestType);
    query.addBindValue(request.submittedBy);
    query.addBindValue("Pending");
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Failed to add leave request:" << query.lastError().text();
        return false;
    }
    
    emit leaveRequestSubmitted(request.studentRoll);
    return true;
}

QList<LeaveRequest> AdvancedAttendance::getPendingLeaveRequests()
{
    QList<LeaveRequest> requests;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT lr.*, es.name FROM leave_requests lr "
                  "JOIN enhanced_students es ON lr.student_roll = es.roll_number "
                  "WHERE lr.status = 'Pending' ORDER BY lr.submitted_date DESC")) {
        while (query.next()) {
            LeaveRequest request;
            request.id = query.value("id").toInt();
            request.studentRoll = query.value("student_roll").toString();
            request.studentName = query.value("name").toString();
            request.fromDate = query.value("from_date").toDate();
            request.toDate = query.value("to_date").toDate();
            request.reason = query.value("reason").toString();
            request.requestType = query.value("request_type").toString();
            request.submittedBy = query.value("submitted_by").toString();
            request.status = query.value("status").toString();
            request.submittedDate = query.value("submitted_date").toDateTime();
            requests.append(request);
        }
    }
    
    return requests;
}

bool AdvancedAttendance::approveLeaveRequest(int requestId, const QString &approvedBy)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("UPDATE leave_requests SET status = 'Approved', "
                 "approved_by = ?, approved_date = ? WHERE id = ?");
    
    query.addBindValue(approvedBy);
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(requestId);
    
    if (!query.exec()) {
        qDebug() << "Failed to approve leave request:" << query.lastError().text();
        return false;
    }
    
    // Get request details for marking excused attendance
    query.prepare("SELECT student_roll, from_date, to_date FROM leave_requests WHERE id = ?");
    query.addBindValue(requestId);
    
    if (query.exec() && query.next()) {
        QString studentRoll = query.value("student_roll").toString();
        QDate fromDate = query.value("from_date").toDate();
        QDate toDate = query.value("to_date").toDate();
        
        // Mark all days in range as excused
        for (QDate date = fromDate; date <= toDate; date = date.addDays(1)) {
            AttendanceEntry entry;
            entry.studentRoll = studentRoll;
            entry.date = date;
            entry.status = "Excused";
            entry.method = "Leave Request";
            entry.location = "N/A";
            entry.markedBy = approvedBy;
            entry.notes = "Approved leave request";
            
            markAttendance(entry);
        }
    }
    
    emit leaveRequestApproved(requestId);
    return true;
}

bool AdvancedAttendance::exportAttendanceData(const QString &filePath, const QString &format,
                                             const QDate &fromDate, const QDate &toDate,
                                             const QString &grade, const QString &section)
{
    Q_UNUSED(format) // Currently only supporting CSV
    
    QSqlQuery query(Database::instance().database());
    
    QString queryStr = "SELECT aa.*, es.name, es.grade, es.section "
                      "FROM advanced_attendance aa "
                      "JOIN enhanced_students es ON aa.student_roll = es.roll_number "
                      "WHERE aa.date BETWEEN ? AND ?";
    
    QStringList params;
    params << fromDate.toString(Qt::ISODate) << toDate.toString(Qt::ISODate);
    
    if (!grade.isEmpty()) {
        queryStr += " AND es.grade = ?";
        params << grade;
    }
    
    if (!section.isEmpty()) {
        queryStr += " AND es.section = ?";
        params << section;
    }
    
    queryStr += " ORDER BY aa.date, es.grade, es.section, es.name";
    
    query.prepare(queryStr);
    for (const QString &param : params) {
        query.addBindValue(param);
    }
    
    if (!query.exec()) {
        qDebug() << "Failed to export attendance data:" << query.lastError().text();
        return false;
    }
    
    // Write to CSV file (simplified implementation)
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << "Date,Roll Number,Student Name,Grade,Section,Time In,Time Out,Status,Method,Location,Marked By,Notes\n";
    
    while (query.next()) {
        out << query.value("date").toString() << ","
            << query.value("student_roll").toString() << ","
            << query.value("name").toString() << ","
            << query.value("grade").toString() << ","
            << query.value("section").toString() << ","
            << query.value("time_in").toString() << ","
            << query.value("time_out").toString() << ","
            << query.value("status").toString() << ","
            << query.value("method").toString() << ","
            << query.value("location").toString() << ","
            << query.value("marked_by").toString() << ","
            << query.value("notes").toString() << "\n";
    }
    
    file.close();
    return true;
}

QList<QString> AdvancedAttendance::getDefaultStudents(const QDate &date)
{
    QStringList absentStudents;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT es.roll_number FROM enhanced_students es "
                 "LEFT JOIN advanced_attendance aa ON es.roll_number = aa.student_roll "
                 "AND aa.date = ? "
                 "WHERE aa.student_roll IS NULL");
    
    query.addBindValue(date);
    
    if (query.exec()) {
        while (query.next()) {
            absentStudents.append(query.value("roll_number").toString());
        }
    }
    
    return absentStudents;
}

bool AdvancedAttendance::createDatabaseTables()
{
    QSqlQuery query(Database::instance().database());
    
    // Create advanced attendance table
    QString createAttendanceTable = R"(
        CREATE TABLE IF NOT EXISTS advanced_attendance (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT NOT NULL,
            date DATE NOT NULL,
            time_in TIME,
            time_out TIME,
            status TEXT NOT NULL DEFAULT 'Present',
            method TEXT DEFAULT 'Manual',
            location TEXT,
            notes TEXT,
            marked_by TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            UNIQUE(student_roll, date),
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createAttendanceTable)) {
        qDebug() << "Failed to create advanced_attendance table:" << query.lastError().text();
        return false;
    }
    
    // Create biometric data table
    QString createBiometricTable = R"(
        CREATE TABLE IF NOT EXISTS biometric_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT UNIQUE NOT NULL,
            fingerprint_hash TEXT,
            face_encoding TEXT,
            rfid_code TEXT UNIQUE,
            active BOOLEAN DEFAULT 1,
            created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createBiometricTable)) {
        qDebug() << "Failed to create biometric_data table:" << query.lastError().text();
        return false;
    }
    
    // Create attendance rules table
    QString createRulesTable = R"(
        CREATE TABLE IF NOT EXISTS attendance_rules (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            rule_name TEXT UNIQUE NOT NULL,
            rule_type TEXT NOT NULL,
            conditions TEXT NOT NULL,
            actions TEXT NOT NULL,
            priority INTEGER DEFAULT 1,
            active BOOLEAN DEFAULT 1,
            grade TEXT,
            section TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createRulesTable)) {
        qDebug() << "Failed to create attendance_rules table:" << query.lastError().text();
        return false;
    }
    
    // Create leave requests table
    QString createLeaveTable = R"(
        CREATE TABLE IF NOT EXISTS leave_requests (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT NOT NULL,
            from_date DATE NOT NULL,
            to_date DATE NOT NULL,
            reason TEXT NOT NULL,
            request_type TEXT DEFAULT 'Medical',
            submitted_by TEXT,
            status TEXT DEFAULT 'Pending',
            submitted_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            approved_by TEXT,
            approved_date TIMESTAMP,
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createLeaveTable)) {
        qDebug() << "Failed to create leave_requests table:" << query.lastError().text();
        return false;
    }
    
    // Create attendance reports table
    QString createReportsTable = R"(
        CREATE TABLE IF NOT EXISTS attendance_reports (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            grade TEXT,
            section TEXT,
            from_date DATE NOT NULL,
            to_date DATE NOT NULL,
            generated_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            report_type TEXT DEFAULT 'Summary',
            status TEXT DEFAULT 'Generated',
            file_path TEXT
        )
    )";
    
    if (!query.exec(createReportsTable)) {
        qDebug() << "Failed to create attendance_reports table:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool AdvancedAttendance::bulkMarkAttendance(const QList<AttendanceEntry> &entries)
{
    Database::instance().database().transaction();
    
    bool allSuccessful = true;
    for (const AttendanceEntry &entry : entries) {
        if (!markAttendance(entry)) {
            allSuccessful = false;
            break;
        }
    }
    
    if (allSuccessful) {
        Database::instance().database().commit();
    } else {
        Database::instance().database().rollback();
    }
    
    return allSuccessful;
}
