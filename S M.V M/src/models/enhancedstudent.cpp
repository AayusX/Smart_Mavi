#include "models/enhancedstudent.h"
#include "database/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

EnhancedStudent::EnhancedStudent(QObject *parent)
    : QObject(parent)
{
}

EnhancedStudent::~EnhancedStudent()
{
}

bool EnhancedStudent::addStudent(const StudentData &student)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO enhanced_students (roll_number, name, grade, section, "
                 "parent_name, parent_phone, parent_email, address, birth_date, "
                 "admission_date, blood_group, emergency_contact, medical_info, "
                 "transport_required, bus_route, fee_category, scholarship_percentage) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(student.rollNumber);
    query.addBindValue(student.name);
    query.addBindValue(student.grade);
    query.addBindValue(student.section);
    query.addBindValue(student.parentName);
    query.addBindValue(student.parentPhone);
    query.addBindValue(student.parentEmail);
    query.addBindValue(student.address);
    query.addBindValue(student.birthDate);
    query.addBindValue(student.admissionDate);
    query.addBindValue(student.bloodGroup);
    query.addBindValue(student.emergencyContact);
    query.addBindValue(student.medicalInfo);
    query.addBindValue(student.transportRequired);
    query.addBindValue(student.busRoute);
    query.addBindValue(student.feeCategory);
    query.addBindValue(student.scholarshipPercentage);
    
    if (!query.exec()) {
        qDebug() << "Failed to add student:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool EnhancedStudent::updateStudent(const StudentData &student)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("UPDATE enhanced_students SET name = ?, grade = ?, section = ?, "
                 "parent_name = ?, parent_phone = ?, parent_email = ?, address = ?, "
                 "birth_date = ?, admission_date = ?, blood_group = ?, emergency_contact = ?, "
                 "medical_info = ?, transport_required = ?, bus_route = ?, fee_category = ?, "
                 "scholarship_percentage = ? WHERE roll_number = ?");
    
    query.addBindValue(student.name);
    query.addBindValue(student.grade);
    query.addBindValue(student.section);
    query.addBindValue(student.parentName);
    query.addBindValue(student.parentPhone);
    query.addBindValue(student.parentEmail);
    query.addBindValue(student.address);
    query.addBindValue(student.birthDate);
    query.addBindValue(student.admissionDate);
    query.addBindValue(student.bloodGroup);
    query.addBindValue(student.emergencyContact);
    query.addBindValue(student.medicalInfo);
    query.addBindValue(student.transportRequired);
    query.addBindValue(student.busRoute);
    query.addBindValue(student.feeCategory);
    query.addBindValue(student.scholarshipPercentage);
    query.addBindValue(student.rollNumber);
    
    if (!query.exec()) {
        qDebug() << "Failed to update student:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool EnhancedStudent::deleteStudent(const QString &rollNumber)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("DELETE FROM enhanced_students WHERE roll_number = ?");
    query.addBindValue(rollNumber);
    
    if (!query.exec()) {
        qDebug() << "Failed to delete student:" << query.lastError().text();
        return false;
    }
    
    return true;
}

StudentData EnhancedStudent::getStudent(const QString &rollNumber)
{
    StudentData student;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM enhanced_students WHERE roll_number = ?");
    query.addBindValue(rollNumber);
    
    if (query.exec() && query.next()) {
        student.rollNumber = query.value("roll_number").toString();
        student.name = query.value("name").toString();
        student.grade = query.value("grade").toString();
        student.section = query.value("section").toString();
        student.parentName = query.value("parent_name").toString();
        student.parentPhone = query.value("parent_phone").toString();
        student.parentEmail = query.value("parent_email").toString();
        student.address = query.value("address").toString();
        student.birthDate = query.value("birth_date").toDate();
        student.admissionDate = query.value("admission_date").toDate();
        student.bloodGroup = query.value("blood_group").toString();
        student.emergencyContact = query.value("emergency_contact").toString();
        student.medicalInfo = query.value("medical_info").toString();
        student.transportRequired = query.value("transport_required").toBool();
        student.busRoute = query.value("bus_route").toString();
        student.feeCategory = query.value("fee_category").toString();
        student.scholarshipPercentage = query.value("scholarship_percentage").toDouble();
    } else {
        qDebug() << "Failed to get student:" << query.lastError().text();
    }
    
    return student;
}

QList<StudentData> EnhancedStudent::getAllStudents()
{
    QList<StudentData> students;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM enhanced_students ORDER BY grade, section, name")) {
        while (query.next()) {
            StudentData student;
            student.rollNumber = query.value("roll_number").toString();
            student.name = query.value("name").toString();
            student.grade = query.value("grade").toString();
            student.section = query.value("section").toString();
            student.parentName = query.value("parent_name").toString();
            student.parentPhone = query.value("parent_phone").toString();
            student.parentEmail = query.value("parent_email").toString();
            student.address = query.value("address").toString();
            student.birthDate = query.value("birth_date").toDate();
            student.admissionDate = query.value("admission_date").toDate();
            student.bloodGroup = query.value("blood_group").toString();
            student.emergencyContact = query.value("emergency_contact").toString();
            student.medicalInfo = query.value("medical_info").toString();
            student.transportRequired = query.value("transport_required").toBool();
            student.busRoute = query.value("bus_route").toString();
            student.feeCategory = query.value("fee_category").toString();
            student.scholarshipPercentage = query.value("scholarship_percentage").toDouble();
            students.append(student);
        }
    } else {
        qDebug() << "Failed to get all students:" << query.lastError().text();
    }
    
    return students;
}

QList<StudentData> EnhancedStudent::searchStudents(const QString &searchTerm)
{
    QList<StudentData> students;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM enhanced_students WHERE "
                 "roll_number LIKE ? OR name LIKE ? OR grade LIKE ? OR "
                 "section LIKE ? OR parent_name LIKE ? OR parent_phone LIKE ? "
                 "ORDER BY name");
    
    QString wildcardTerm = "%" + searchTerm + "%";
    for (int i = 0; i < 6; ++i) {
        query.addBindValue(wildcardTerm);
    }
    
    if (query.exec()) {
        while (query.next()) {
            StudentData student;
            student.rollNumber = query.value("roll_number").toString();
            student.name = query.value("name").toString();
            student.grade = query.value("grade").toString();
            student.section = query.value("section").toString();
            student.parentName = query.value("parent_name").toString();
            student.parentPhone = query.value("parent_phone").toString();
            student.parentEmail = query.value("parent_email").toString();
            student.address = query.value("address").toString();
            student.birthDate = query.value("birth_date").toDate();
            student.admissionDate = query.value("admission_date").toDate();
            student.bloodGroup = query.value("blood_group").toString();
            student.emergencyContact = query.value("emergency_contact").toString();
            student.medicalInfo = query.value("medical_info").toString();
            student.transportRequired = query.value("transport_required").toBool();
            student.busRoute = query.value("bus_route").toString();
            student.feeCategory = query.value("fee_category").toString();
            student.scholarshipPercentage = query.value("scholarship_percentage").toDouble();
            students.append(student);
        }
    } else {
        qDebug() << "Failed to search students:" << query.lastError().text();
    }
    
    return students;
}

QList<StudentData> EnhancedStudent::getStudentsByGrade(const QString &grade)
{
    QList<StudentData> students;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM enhanced_students WHERE grade = ? ORDER BY section, name");
    query.addBindValue(grade);
    
    if (query.exec()) {
        while (query.next()) {
            StudentData student;
            student.rollNumber = query.value("roll_number").toString();
            student.name = query.value("name").toString();
            student.grade = query.value("grade").toString();
            student.section = query.value("section").toString();
            student.parentName = query.value("parent_name").toString();
            student.parentPhone = query.value("parent_phone").toString();
            student.parentEmail = query.value("parent_email").toString();
            student.address = query.value("address").toString();
            student.birthDate = query.value("birth_date").toDate();
            student.admissionDate = query.value("admission_date").toDate();
            student.bloodGroup = query.value("blood_group").toString();
            student.emergencyContact = query.value("emergency_contact").toString();
            student.medicalInfo = query.value("medical_info").toString();
            student.transportRequired = query.value("transport_required").toBool();
            student.busRoute = query.value("bus_route").toString();
            student.feeCategory = query.value("fee_category").toString();
            student.scholarshipPercentage = query.value("scholarship_percentage").toDouble();
            students.append(student);
        }
    } else {
        qDebug() << "Failed to get students by grade:" << query.lastError().text();
    }
    
    return students;
}

QStringList EnhancedStudent::getAllGrades()
{
    QStringList grades;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT DISTINCT grade FROM enhanced_students ORDER BY grade")) {
        while (query.next()) {
            grades.append(query.value("grade").toString());
        }
    }
    
    return grades;
}

QStringList EnhancedStudent::getSectionsByGrade(const QString &grade)
{
    QStringList sections;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT DISTINCT section FROM enhanced_students WHERE grade = ? ORDER BY section");
    query.addBindValue(grade);
    
    if (query.exec()) {
        while (query.next()) {
            sections.append(query.value("section").toString());
        }
    }
    
    return sections;
}

int EnhancedStudent::getStudentCount()
{
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT COUNT(*) FROM enhanced_students")) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    }
    
    return 0;
}

QMap<QString, int> EnhancedStudent::getGradeWiseCount()
{
    QMap<QString, int> counts;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT grade, COUNT(*) FROM enhanced_students GROUP BY grade ORDER BY grade")) {
        while (query.next()) {
            counts[query.value(0).toString()] = query.value(1).toInt();
        }
    }
    
    return counts;
}

bool EnhancedStudent::addFeeTransaction(const FeeTransaction &transaction)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO fee_transactions (student_roll, amount, fee_type, "
                 "transaction_date, payment_method, receipt_number, remarks) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(transaction.studentRoll);
    query.addBindValue(transaction.amount);
    query.addBindValue(transaction.feeType);
    query.addBindValue(transaction.transactionDate);
    query.addBindValue(transaction.paymentMethod);
    query.addBindValue(transaction.receiptNumber);
    query.addBindValue(transaction.remarks);
    
    if (!query.exec()) {
        qDebug() << "Failed to add fee transaction:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<FeeTransaction> EnhancedStudent::getFeeTransactions(const QString &rollNumber)
{
    QList<FeeTransaction> transactions;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM fee_transactions WHERE student_roll = ? "
                 "ORDER BY transaction_date DESC");
    query.addBindValue(rollNumber);
    
    if (query.exec()) {
        while (query.next()) {
            FeeTransaction transaction;
            transaction.id = query.value("id").toInt();
            transaction.studentRoll = query.value("student_roll").toString();
            transaction.amount = query.value("amount").toDouble();
            transaction.feeType = query.value("fee_type").toString();
            transaction.transactionDate = query.value("transaction_date").toDate();
            transaction.paymentMethod = query.value("payment_method").toString();
            transaction.receiptNumber = query.value("receipt_number").toString();
            transaction.remarks = query.value("remarks").toString();
            transactions.append(transaction);
        }
    }
    
    return transactions;
}

bool EnhancedStudent::addExamResult(const ExamResult &result)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO exam_results (student_roll, exam_name, subject, "
                 "marks_obtained, total_marks, exam_date, grade, remarks) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(result.studentRoll);
    query.addBindValue(result.examName);
    query.addBindValue(result.subject);
    query.addBindValue(result.marksObtained);
    query.addBindValue(result.totalMarks);
    query.addBindValue(result.examDate);
    query.addBindValue(result.grade);
    query.addBindValue(result.remarks);
    
    if (!query.exec()) {
        qDebug() << "Failed to add exam result:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<ExamResult> EnhancedStudent::getExamResults(const QString &rollNumber)
{
    QList<ExamResult> results;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM exam_results WHERE student_roll = ? "
                 "ORDER BY exam_date DESC");
    query.addBindValue(rollNumber);
    
    if (query.exec()) {
        while (query.next()) {
            ExamResult result;
            result.id = query.value("id").toInt();
            result.studentRoll = query.value("student_roll").toString();
            result.examName = query.value("exam_name").toString();
            result.subject = query.value("subject").toString();
            result.marksObtained = query.value("marks_obtained").toDouble();
            result.totalMarks = query.value("total_marks").toDouble();
            result.examDate = query.value("exam_date").toDate();
            result.grade = query.value("grade").toString();
            result.remarks = query.value("remarks").toString();
            results.append(result);
        }
    }
    
    return results;
}

bool EnhancedStudent::addDisciplinaryRecord(const DisciplinaryRecord &record)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO disciplinary_records (student_roll, incident_type, "
                 "description, incident_date, action_taken, severity, resolved) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(record.studentRoll);
    query.addBindValue(record.incidentType);
    query.addBindValue(record.description);
    query.addBindValue(record.incidentDate);
    query.addBindValue(record.actionTaken);
    query.addBindValue(record.severity);
    query.addBindValue(record.resolved);
    
    if (!query.exec()) {
        qDebug() << "Failed to add disciplinary record:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<DisciplinaryRecord> EnhancedStudent::getDisciplinaryRecords(const QString &rollNumber)
{
    QList<DisciplinaryRecord> records;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM disciplinary_records WHERE student_roll = ? "
                 "ORDER BY incident_date DESC");
    query.addBindValue(rollNumber);
    
    if (query.exec()) {
        while (query.next()) {
            DisciplinaryRecord record;
            record.id = query.value("id").toInt();
            record.studentRoll = query.value("student_roll").toString();
            record.incidentType = query.value("incident_type").toString();
            record.description = query.value("description").toString();
            record.incidentDate = query.value("incident_date").toDate();
            record.actionTaken = query.value("action_taken").toString();
            record.severity = query.value("severity").toString();
            record.resolved = query.value("resolved").toBool();
            records.append(record);
        }
    }
    
    return records;
}

bool EnhancedStudent::addParentMeeting(const ParentMeeting &meeting)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO parent_meetings (student_roll, meeting_date, "
                 "meeting_type, purpose, attendees, discussion_points, "
                 "action_items, follow_up_date) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(meeting.studentRoll);
    query.addBindValue(meeting.meetingDate);
    query.addBindValue(meeting.meetingType);
    query.addBindValue(meeting.purpose);
    query.addBindValue(meeting.attendees);
    query.addBindValue(meeting.discussionPoints);
    query.addBindValue(meeting.actionItems);
    query.addBindValue(meeting.followUpDate);
    
    if (!query.exec()) {
        qDebug() << "Failed to add parent meeting:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<ParentMeeting> EnhancedStudent::getParentMeetings(const QString &rollNumber)
{
    QList<ParentMeeting> meetings;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM parent_meetings WHERE student_roll = ? "
                 "ORDER BY meeting_date DESC");
    query.addBindValue(rollNumber);
    
    if (query.exec()) {
        while (query.next()) {
            ParentMeeting meeting;
            meeting.id = query.value("id").toInt();
            meeting.studentRoll = query.value("student_roll").toString();
            meeting.meetingDate = query.value("meeting_date").toDateTime();
            meeting.meetingType = query.value("meeting_type").toString();
            meeting.purpose = query.value("purpose").toString();
            meeting.attendees = query.value("attendees").toString();
            meeting.discussionPoints = query.value("discussion_points").toString();
            meeting.actionItems = query.value("action_items").toString();
            meeting.followUpDate = query.value("follow_up_date").toDate();
            meetings.append(meeting);
        }
    }
    
    return meetings;
}

QList<StudentData> EnhancedStudent::getUpcomingBirthdays(int days)
{
    QList<StudentData> students;
    QSqlQuery query(Database::instance().database());
    
    // Get students with birthdays in the next 'days' days
    QString queryStr = QString("SELECT * FROM enhanced_students WHERE "
                              "strftime('%%j', birth_date) BETWEEN "
                              "strftime('%%j', 'now') AND "
                              "strftime('%%j', 'now', '+%1 days') "
                              "ORDER BY birth_date").arg(days);
    
    if (query.exec(queryStr)) {
        while (query.next()) {
            StudentData student;
            student.rollNumber = query.value("roll_number").toString();
            student.name = query.value("name").toString();
            student.grade = query.value("grade").toString();
            student.section = query.value("section").toString();
            student.birthDate = query.value("birth_date").toDate();
            students.append(student);
        }
    }
    
    return students;
}

double EnhancedStudent::getOutstandingFees(const QString &rollNumber)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT COALESCE(SUM(amount), 0) FROM fee_transactions "
                 "WHERE student_roll = ? AND fee_type LIKE '%Outstanding%'");
    query.addBindValue(rollNumber);
    
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    
    return 0.0;
}

bool EnhancedStudent::createDatabaseTables()
{
    QSqlQuery query(Database::instance().database());
    
    // Create enhanced students table
    QString createStudentsTable = R"(
        CREATE TABLE IF NOT EXISTS enhanced_students (
            roll_number TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            grade TEXT NOT NULL,
            section TEXT,
            parent_name TEXT,
            parent_phone TEXT,
            parent_email TEXT,
            address TEXT,
            birth_date DATE,
            admission_date DATE,
            blood_group TEXT,
            emergency_contact TEXT,
            medical_info TEXT,
            transport_required BOOLEAN DEFAULT 0,
            bus_route TEXT,
            fee_category TEXT,
            scholarship_percentage REAL DEFAULT 0.0,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createStudentsTable)) {
        qDebug() << "Failed to create enhanced_students table:" << query.lastError().text();
        return false;
    }
    
    // Create fee transactions table
    QString createFeeTable = R"(
        CREATE TABLE IF NOT EXISTS fee_transactions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT NOT NULL,
            amount REAL NOT NULL,
            fee_type TEXT NOT NULL,
            transaction_date DATE NOT NULL,
            payment_method TEXT,
            receipt_number TEXT UNIQUE,
            remarks TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createFeeTable)) {
        qDebug() << "Failed to create fee_transactions table:" << query.lastError().text();
        return false;
    }
    
    // Create exam results table
    QString createExamTable = R"(
        CREATE TABLE IF NOT EXISTS exam_results (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT NOT NULL,
            exam_name TEXT NOT NULL,
            subject TEXT NOT NULL,
            marks_obtained REAL NOT NULL,
            total_marks REAL NOT NULL,
            exam_date DATE NOT NULL,
            grade TEXT,
            remarks TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createExamTable)) {
        qDebug() << "Failed to create exam_results table:" << query.lastError().text();
        return false;
    }
    
    // Create disciplinary records table
    QString createDisciplinaryTable = R"(
        CREATE TABLE IF NOT EXISTS disciplinary_records (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT NOT NULL,
            incident_type TEXT NOT NULL,
            description TEXT NOT NULL,
            incident_date DATE NOT NULL,
            action_taken TEXT,
            severity TEXT DEFAULT 'Low',
            resolved BOOLEAN DEFAULT 0,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createDisciplinaryTable)) {
        qDebug() << "Failed to create disciplinary_records table:" << query.lastError().text();
        return false;
    }
    
    // Create parent meetings table
    QString createMeetingsTable = R"(
        CREATE TABLE IF NOT EXISTS parent_meetings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT NOT NULL,
            meeting_date TIMESTAMP NOT NULL,
            meeting_type TEXT NOT NULL,
            purpose TEXT NOT NULL,
            attendees TEXT,
            discussion_points TEXT,
            action_items TEXT,
            follow_up_date DATE,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createMeetingsTable)) {
        qDebug() << "Failed to create parent_meetings table:" << query.lastError().text();
        return false;
    }
    
    return true;
}
