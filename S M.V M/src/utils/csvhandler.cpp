#include "utils/csvhandler.h"
#include "models/teacher.h"
#include "models/student.h"
#include "models/class.h"
#include "models/attendance.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

CSVHandler::CSVHandler(QObject *parent)
    : QObject(parent)
{
}

QList<Teacher> CSVHandler::importTeachers(const QString &filename)
{
    QList<Teacher> teachers;
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showImportError(filename, "Could not open file");
        return teachers;
    }
    
    QTextStream in(&file);
    bool firstLine = true;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        QStringList data = parseCSVLine(line);
        if (validateTeacherData(data)) {
            Teacher teacher = parseTeacherData(data);
            teachers.append(teacher);
        }
    }
    
    file.close();
    return teachers;
}

QList<Student> CSVHandler::importStudents(const QString &filename)
{
    QList<Student> students;
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showImportError(filename, "Could not open file");
        return students;
    }
    
    QTextStream in(&file);
    bool firstLine = true;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        QStringList data = parseCSVLine(line);
        if (validateStudentData(data)) {
            Student student = parseStudentData(data);
            students.append(student);
        }
    }
    
    file.close();
    return students;
}

QList<Class> CSVHandler::importClasses(const QString &filename)
{
    QList<Class> classes;
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showImportError(filename, "Could not open file");
        return classes;
    }
    
    QTextStream in(&file);
    bool firstLine = true;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        QStringList data = parseCSVLine(line);
        if (validateClassData(data)) {
            Class classObj = parseClassData(data);
            classes.append(classObj);
        }
    }
    
    file.close();
    return classes;
}

QList<Attendance> CSVHandler::importAttendance(const QString &filename)
{
    QList<Attendance> attendanceList;
    QFile file(filename);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showImportError(filename, "Could not open file");
        return attendanceList;
    }
    
    QTextStream in(&file);
    bool firstLine = true;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        QStringList data = parseCSVLine(line);
        if (validateAttendanceData(data)) {
            Attendance attendance = parseAttendanceData(data);
            attendanceList.append(attendance);
        }
    }
    
    file.close();
    return attendanceList;
}

bool CSVHandler::exportTeachers(const QList<Teacher> &teachers, const QString &filename)
{
    if (!writeHeaders(filename, getTeacherHeaders())) {
        return false;
    }
    
    QList<QStringList> data;
    for (const Teacher &teacher : teachers) {
        data.append(formatTeacherData(teacher));
    }
    
    return writeData(filename, data);
}

bool CSVHandler::exportStudents(const QList<Student> &students, const QString &filename)
{
    if (!writeHeaders(filename, getStudentHeaders())) {
        return false;
    }
    
    QList<QStringList> data;
    for (const Student &student : students) {
        data.append(formatStudentData(student));
    }
    
    return writeData(filename, data);
}

bool CSVHandler::exportClasses(const QList<Class> &classes, const QString &filename)
{
    if (!writeHeaders(filename, getClassHeaders())) {
        return false;
    }
    
    QList<QStringList> data;
    for (const Class &classObj : classes) {
        data.append(formatClassData(classObj));
    }
    
    return writeData(filename, data);
}

bool CSVHandler::exportAttendance(const QList<Attendance> &attendance, const QString &filename)
{
    if (!writeHeaders(filename, getAttendanceHeaders())) {
        return false;
    }
    
    QList<QStringList> data;
    for (const Attendance &att : attendance) {
        data.append(formatAttendanceData(att));
    }
    
    return writeData(filename, data);
}

bool CSVHandler::bulkImportStudents(const QString &filename)
{
    QList<Student> students = importStudents(filename);
    if (students.isEmpty()) {
        showImportError(filename, "No valid students found in file");
        return false;
    }
    
    // Here you would typically add the students to the database
    // For now, we'll just log the count
    qDebug() << "Imported" << students.size() << "students from" << filename;
    return true;
}

bool CSVHandler::bulkExportStudents(const QList<Student> &students, const QString &filename)
{
    return exportStudents(students, filename);
}

bool CSVHandler::bulkImportAttendance(const QString &filename)
{
    QList<Attendance> attendance = importAttendance(filename);
    if (attendance.isEmpty()) {
        showImportError(filename, "No valid attendance records found in file");
        return false;
    }
    
    // Here you would typically add the attendance records to the database
    qDebug() << "Imported" << attendance.size() << "attendance records from" << filename;
    return true;
}

bool CSVHandler::bulkExportAttendance(const QList<Attendance> &attendance, const QString &filename)
{
    return exportAttendance(attendance, filename);
}

bool CSVHandler::generateStudentTemplate(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << getStudentHeaders() << "\n";
    out << "ST001,John Doe,1,Parent Name,+977123456789,parent@email.com,Address,2005-01-01,Male,2024-01-01\n";
    out << "ST002,Jane Smith,1,Guardian Name,+977987654321,guardian@email.com,Address,2005-06-15,Female,2024-01-01\n";
    
    file.close();
    return true;
}

bool CSVHandler::generateTeacherTemplate(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << getTeacherHeaders() << "\n";
    out << "1,Mr. Teacher,Mathematics,+977123456789,teacher@email.com,Address,1,2024-01-01\n";
    out << "2,Mrs. Teacher,English,+977987654321,teacher2@email.com,Address,2,2024-01-01\n";
    
    file.close();
    return true;
}

bool CSVHandler::generateClassTemplate(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << getClassHeaders() << "\n";
    out << "1,Class A,1,40,Room 101,1,Description\n";
    out << "2,Class B,2,35,Room 102,2,Description\n";
    
    file.close();
    return true;
}

bool CSVHandler::generateAttendanceTemplate(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << getAttendanceHeaders() << "\n";
    out << "1,1,2024-01-01,0,Present\n";
    out << "2,1,2024-01-01,1,Absent\n";
    
    file.close();
    return true;
}

bool CSVHandler::validateStudentData(const QStringList &data)
{
    if (data.size() < 11) return false;
    
    // Validate roll number
    if (!Student::isValidRollNo(data[0])) return false;
    
    // Validate name
    if (data[1].isEmpty()) return false;
    
    // Validate class ID
    bool ok;
    data[2].toInt(&ok);
    if (!ok) return false;
    
    // Validate date of birth
    QDate dob = QDate::fromString(data[7], "yyyy-MM-dd");
    if (!Student::isValidDateOfBirth(dob)) return false;
    
    // Validate gender
    QStringList validGenders = Student::getGenderList();
    if (!validGenders.contains(data[8])) return false;
    
    return true;
}

bool CSVHandler::validateTeacherData(const QStringList &data)
{
    if (data.size() < 8) return false;
    
    // Validate name
    if (data[0].isEmpty()) return false;
    
    // Validate subject
    if (data[1].isEmpty()) return false;
    
    // Validate contact
    if (!Teacher::isValidContact(data[2])) return false;
    
    // Validate email
    if (!Teacher::isValidEmail(data[4])) return false;
    
    return true;
}

bool CSVHandler::validateClassData(const QStringList &data)
{
    if (data.size() < 7) return false;
    
    // Validate name
    if (data[0].isEmpty()) return false;
    
    // Validate grade
    bool ok;
    int grade = data[1].toInt(&ok);
    if (!ok || !Class::isValidGrade(grade)) return false;
    
    // Validate capacity
    int capacity = data[2].toInt(&ok);
    if (!ok || !Class::isValidCapacity(capacity)) return false;
    
    return true;
}

bool CSVHandler::validateAttendanceData(const QStringList &data)
{
    if (data.size() < 5) return false;
    
    // Validate student ID
    bool ok;
    data[0].toInt(&ok);
    if (!ok) return false;
    
    // Validate class ID
    data[1].toInt(&ok);
    if (!ok) return false;
    
    // Validate date
    QDate date = QDate::fromString(data[2], "yyyy-MM-dd");
    if (!Attendance::isValidDate(date)) return false;
    
    // Validate status
    int status = data[3].toInt(&ok);
    if (!ok || !Attendance::isValidStatus(static_cast<Attendance::Status>(status))) return false;
    
    return true;
}

QStringList CSVHandler::parseCSVLine(const QString &line)
{
    QStringList result;
    QString current;
    bool inQuotes = false;
    
    for (int i = 0; i < line.length(); ++i) {
        QChar ch = line.at(i);
        
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            result.append(current.trimmed());
            current.clear();
        } else {
            current += ch;
        }
    }
    
    result.append(current.trimmed());
    return result;
}

QString CSVHandler::escapeCSVField(const QString &field)
{
    if (field.contains(',') || field.contains('"') || field.contains('\n')) {
        QString escaped = field;
        escaped.replace("\"", "\"\"");
        return "\"" + escaped + "\"";
    }
    return field;
}

QString CSVHandler::unescapeCSVField(const QString &field)
{
    if (field.startsWith('"') && field.endsWith('"')) {
        QString unescaped = field.mid(1, field.length() - 2);
        unescaped.replace("\"\"", "\"");
        return unescaped;
    }
    return field;
}

bool CSVHandler::isValidCSVFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream in(&file);
    QString firstLine = in.readLine();
    file.close();
    
    return !firstLine.isEmpty() && firstLine.contains(',');
}

QString CSVHandler::getDefaultExportPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/SmartMAVIManager/";
}

Teacher CSVHandler::parseTeacherData(const QStringList &data)
{
    return Teacher(
        0, // ID will be set by database
        data[0], // name
        data[1], // subject
        data[2], // contact
        data[3].toInt(), // assigned class
        data[4], // email
        data[5], // address
        QDate::fromString(data[6], "yyyy-MM-dd") // join date
    );
}

Student CSVHandler::parseStudentData(const QStringList &data)
{
    return Student(
        0, // ID will be set by database
        data[0], // roll no
        data[1], // name
        data[2].toInt(), // class id
        data[3], // guardian name
        data[4], // guardian contact
        data[5], // guardian email
        data[6], // address
        QDate::fromString(data[7], "yyyy-MM-dd"), // date of birth
        data[8], // gender
        QDate::fromString(data[9], "yyyy-MM-dd") // admission date
    );
}

Class CSVHandler::parseClassData(const QStringList &data)
{
    return Class(
        0, // ID will be set by database
        data[0], // name
        data[1].toInt(), // grade
        data[2].toInt(), // capacity
        data[3], // room number
        data[4].toInt(), // teacher id
        data[5] // description
    );
}

Attendance CSVHandler::parseAttendanceData(const QStringList &data)
{
    return Attendance(
        0, // ID will be set by database
        data[0].toInt(), // student id
        data[1].toInt(), // class id
        QDate::fromString(data[2], "yyyy-MM-dd"), // date
        static_cast<Attendance::Status>(data[3].toInt()), // status
        data[4] // remarks
    );
}

QStringList CSVHandler::formatTeacherData(const Teacher &teacher)
{
    return {
        teacher.getName(),
        teacher.getSubject(),
        teacher.getContact(),
        QString::number(teacher.getAssignedClass()),
        teacher.getEmail(),
        teacher.getAddress(),
        teacher.getJoinDate().toString("yyyy-MM-dd")
    };
}

QStringList CSVHandler::formatStudentData(const Student &student)
{
    return {
        student.getRollNo(),
        student.getName(),
        QString::number(student.getClassId()),
        student.getGuardianName(),
        student.getGuardianContact(),
        student.getGuardianEmail(),
        student.getAddress(),
        student.getDateOfBirth().toString("yyyy-MM-dd"),
        student.getGender(),
        student.getAdmissionDate().toString("yyyy-MM-dd")
    };
}

QStringList CSVHandler::formatClassData(const Class &classObj)
{
    return {
        classObj.getName(),
        QString::number(classObj.getGrade()),
        QString::number(classObj.getCapacity()),
        classObj.getRoomNumber(),
        QString::number(classObj.getTeacherId()),
        classObj.getDescription()
    };
}

QStringList CSVHandler::formatAttendanceData(const Attendance &attendance)
{
    return {
        QString::number(attendance.getStudentId()),
        QString::number(attendance.getClassId()),
        attendance.getDate().toString("yyyy-MM-dd"),
        QString::number(static_cast<int>(attendance.getStatus())),
        attendance.getRemarks()
    };
}

QString CSVHandler::getTeacherHeaders()
{
    return "Name,Subject,Contact,AssignedClass,Email,Address,JoinDate";
}

QString CSVHandler::getStudentHeaders()
{
    return "RollNo,Name,ClassId,GuardianName,GuardianContact,GuardianEmail,Address,DateOfBirth,Gender,AdmissionDate";
}

QString CSVHandler::getClassHeaders()
{
    return "Name,Grade,Capacity,RoomNumber,TeacherId,Description";
}

QString CSVHandler::getAttendanceHeaders()
{
    return "StudentId,ClassId,Date,Status,Remarks";
}

bool CSVHandler::writeHeaders(const QString &filename, const QString &headers)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << headers << "\n";
    file.close();
    return true;
}

bool CSVHandler::writeData(const QString &filename, const QList<QStringList> &data)
{
    QFile file(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    for (const QStringList &row : data) {
        QStringList escapedRow;
        for (const QString &field : row) {
            escapedRow.append(escapeCSVField(field));
        }
        out << escapedRow.join(",") << "\n";
    }
    
    file.close();
    return true;
}

void CSVHandler::logError(const QString &error)
{
    qDebug() << "CSVHandler Error:" << error;
}

void CSVHandler::showImportError(const QString &filename, const QString &error)
{
    QMessageBox::warning(nullptr, "Import Error", 
                        QString("Failed to import from %1: %2").arg(filename, error));
}

void CSVHandler::showExportError(const QString &filename, const QString &error)
{
    QMessageBox::warning(nullptr, "Export Error", 
                        QString("Failed to export to %1: %2").arg(filename, error));
}

bool CSVHandler::createBackup(const QString &filename)
{
    QString backupPath = getBackupPath(filename);
    QFile sourceFile(filename);
    QFile backupFile(backupPath);
    
    if (!sourceFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    if (!backupFile.open(QIODevice::WriteOnly)) {
        sourceFile.close();
        return false;
    }
    
    QByteArray data = sourceFile.readAll();
    backupFile.write(data);
    
    sourceFile.close();
    backupFile.close();
    
    return true;
}

bool CSVHandler::restoreBackup(const QString &filename)
{
    QString backupPath = getBackupPath(filename);
    QFile backupFile(backupPath);
    QFile targetFile(filename);
    
    if (!backupFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    if (!targetFile.open(QIODevice::WriteOnly)) {
        backupFile.close();
        return false;
    }
    
    QByteArray data = backupFile.readAll();
    targetFile.write(data);
    
    backupFile.close();
    targetFile.close();
    
    return true;
}

QString CSVHandler::getBackupPath(const QString &filename)
{
    QFileInfo fileInfo(filename);
    QString backupDir = fileInfo.absolutePath() + "/backup/";
    QDir().mkpath(backupDir);
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    return backupDir + fileInfo.baseName() + "_backup_" + timestamp + "." + fileInfo.suffix();
}
