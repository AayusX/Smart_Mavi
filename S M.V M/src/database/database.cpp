#include "database/database.h"
#include "models/teacher.h"
#include "models/student.h"
#include "models/class.h"
#include "models/attendance.h"
#include "utils/passwordhash.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
#include <QVariant>
#include <QDate>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

Database::Database(QObject *parent)
    : QObject(parent)
    , m_database(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);
    m_databasePath = dataPath + "/school.db";
}

Database::~Database()
{
    closeConnection();
}

bool Database::initialize()
{
    m_database.setDatabaseName(m_databasePath);
    
    if (!m_database.open()) {
        qDebug() << "Failed to open database:" << m_database.lastError().text();
        return false;
    }
    
    if (!createTables()) {
        qDebug() << "Failed to create tables";
        return false;
    }
    
    return true;
}

bool Database::createTables()
{
    return createTeachersTable() &&
           createStudentsTable() &&
           createClassesTable() &&
           createAttendanceTable() &&
           createHolidaysTable() &&
           createEventsTable() &&
           createUsersTable();
}

bool Database::createTeachersTable()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS teachers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "subject TEXT NOT NULL,"
        "contact TEXT,"
        "email TEXT,"
        "address TEXT,"
        "assigned_class INTEGER,"
        "join_date DATE,"
        "is_active BOOLEAN DEFAULT 1"
        ")"
    );
}

bool Database::createStudentsTable()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "roll_no TEXT UNIQUE NOT NULL,"
        "name TEXT NOT NULL,"
        "class_id INTEGER,"
        "guardian_name TEXT,"
        "guardian_contact TEXT,"
        "guardian_email TEXT,"
        "address TEXT,"
        "date_of_birth DATE,"
        "gender TEXT,"
        "admission_date DATE,"
        "is_active BOOLEAN DEFAULT 1,"
        "FOREIGN KEY (class_id) REFERENCES classes (id)"
        ")"
    );
}

bool Database::createClassesTable()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS classes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "grade INTEGER,"
        "capacity INTEGER DEFAULT 40,"
        "room_number TEXT,"
        "teacher_id INTEGER,"
        "description TEXT,"
        "is_active BOOLEAN DEFAULT 1,"
        "FOREIGN KEY (teacher_id) REFERENCES teachers (id)"
        ")"
    );
}

bool Database::createAttendanceTable()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS attendance ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_id INTEGER NOT NULL,"
        "class_id INTEGER NOT NULL,"
        "date DATE NOT NULL,"
        "status INTEGER NOT NULL,"
        "remarks TEXT,"
        "marked_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "FOREIGN KEY (student_id) REFERENCES students (id),"
        "FOREIGN KEY (class_id) REFERENCES classes (id)"
        ")"
    );
}

bool Database::createHolidaysTable()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS holidays ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "date DATE UNIQUE NOT NULL,"
        "description TEXT"
        ")"
    );
}

bool Database::createEventsTable()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS events ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "date DATE NOT NULL,"
        "title TEXT NOT NULL,"
        "description TEXT"
        ")"
    );
}

bool Database::createUsersTable()
{
    QSqlQuery query;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash TEXT NOT NULL,"
        "role TEXT NOT NULL,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ")"
    );
}

bool Database::isConnected() const
{
    return m_database.isOpen();
}

// Teacher operations
bool Database::addTeacher(const Teacher &teacher)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO teachers (name, subject, contact, email, address, assigned_class, join_date, is_active) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(teacher.getName());
    query.addBindValue(teacher.getSubject());
    query.addBindValue(teacher.getContact());
    query.addBindValue(teacher.getEmail());
    query.addBindValue(teacher.getAddress());
    query.addBindValue(teacher.getAssignedClass());
    query.addBindValue(teacher.getJoinDate());
    query.addBindValue(teacher.isActive());
    
    return query.exec();
}

bool Database::updateTeacher(const Teacher &teacher)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE teachers SET name=?, subject=?, contact=?, email=?, address=?, "
        "assigned_class=?, join_date=?, is_active=? WHERE id=?"
    );
    query.addBindValue(teacher.getName());
    query.addBindValue(teacher.getSubject());
    query.addBindValue(teacher.getContact());
    query.addBindValue(teacher.getEmail());
    query.addBindValue(teacher.getAddress());
    query.addBindValue(teacher.getAssignedClass());
    query.addBindValue(teacher.getJoinDate());
    query.addBindValue(teacher.isActive());
    query.addBindValue(teacher.getId());
    
    return query.exec();
}

bool Database::deleteTeacher(int teacherId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM teachers WHERE id = ?");
    query.addBindValue(teacherId);
    return query.exec();
}

QList<Teacher> Database::getAllTeachers()
{
    QList<Teacher> teachers;
    QSqlQuery query("SELECT * FROM teachers WHERE is_active = 1 ORDER BY name");
    
    while (query.next()) {
        Teacher teacher(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("subject").toString(),
            query.value("contact").toString(),
            query.value("assigned_class").toInt(),
            query.value("email").toString(),
            query.value("address").toString(),
            query.value("join_date").toDate()
        );
        teacher.setActive(query.value("is_active").toBool());
        teachers.append(teacher);
    }
    
    return teachers;
}

Teacher Database::getTeacherById(int teacherId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM teachers WHERE id = ?");
    query.addBindValue(teacherId);
    
    if (query.exec() && query.next()) {
        return Teacher(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("subject").toString(),
            query.value("contact").toString(),
            query.value("assigned_class").toInt(),
            query.value("email").toString(),
            query.value("address").toString(),
            query.value("join_date").toDate()
        );
    }
    
    return Teacher();
}

Teacher Database::getTeacherByName(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM teachers WHERE name = ?");
    query.addBindValue(name);
    
    if (query.exec() && query.next()) {
        return Teacher(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("subject").toString(),
            query.value("contact").toString(),
            query.value("assigned_class").toInt(),
            query.value("email").toString(),
            query.value("address").toString(),
            query.value("join_date").toDate()
        );
    }
    
    return Teacher();
}

// Student operations
bool Database::addStudent(const Student &student)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO students (roll_no, name, class_id, guardian_name, guardian_contact, "
        "guardian_email, address, date_of_birth, gender, admission_date, is_active) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(student.getRollNo());
    query.addBindValue(student.getName());
    query.addBindValue(student.getClassId());
    query.addBindValue(student.getGuardianName());
    query.addBindValue(student.getGuardianContact());
    query.addBindValue(student.getGuardianEmail());
    query.addBindValue(student.getAddress());
    query.addBindValue(student.getDateOfBirth());
    query.addBindValue(student.getGender());
    query.addBindValue(student.getAdmissionDate());
    query.addBindValue(student.isActive());
    
    return query.exec();
}

bool Database::updateStudent(const Student &student)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE students SET roll_no=?, name=?, class_id=?, guardian_name=?, guardian_contact=?, "
        "guardian_email=?, address=?, date_of_birth=?, gender=?, admission_date=?, is_active=? WHERE id=?"
    );
    query.addBindValue(student.getRollNo());
    query.addBindValue(student.getName());
    query.addBindValue(student.getClassId());
    query.addBindValue(student.getGuardianName());
    query.addBindValue(student.getGuardianContact());
    query.addBindValue(student.getGuardianEmail());
    query.addBindValue(student.getAddress());
    query.addBindValue(student.getDateOfBirth());
    query.addBindValue(student.getGender());
    query.addBindValue(student.getAdmissionDate());
    query.addBindValue(student.isActive());
    query.addBindValue(student.getId());
    
    return query.exec();
}

bool Database::deleteStudent(int studentId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM students WHERE id = ?");
    query.addBindValue(studentId);
    return query.exec();
}

QList<Student> Database::getAllStudents()
{
    QList<Student> students;
    QSqlQuery query("SELECT * FROM students WHERE is_active = 1 ORDER BY name");
    
    while (query.next()) {
        Student student(
            query.value("id").toInt(),
            query.value("roll_no").toString(),
            query.value("name").toString(),
            query.value("class_id").toInt(),
            query.value("guardian_name").toString(),
            query.value("guardian_contact").toString(),
            query.value("guardian_email").toString(),
            query.value("address").toString(),
            query.value("date_of_birth").toDate(),
            query.value("gender").toString(),
            query.value("admission_date").toDate()
        );
        student.setActive(query.value("is_active").toBool());
        students.append(student);
    }
    
    return students;
}

QList<Student> Database::getStudentsByClass(int classId)
{
    QList<Student> students;
    QSqlQuery query;
    query.prepare("SELECT * FROM students WHERE class_id = ? AND is_active = 1 ORDER BY name");
    query.addBindValue(classId);
    
    while (query.exec() && query.next()) {
        Student student(
            query.value("id").toInt(),
            query.value("roll_no").toString(),
            query.value("name").toString(),
            query.value("class_id").toInt(),
            query.value("guardian_name").toString(),
            query.value("guardian_contact").toString(),
            query.value("guardian_email").toString(),
            query.value("address").toString(),
            query.value("date_of_birth").toDate(),
            query.value("gender").toString(),
            query.value("admission_date").toDate()
        );
        student.setActive(query.value("is_active").toBool());
        students.append(student);
    }
    
    return students;
}

Student Database::getStudentById(int studentId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM students WHERE id = ?");
    query.addBindValue(studentId);
    
    if (query.exec() && query.next()) {
        return Student(
            query.value("id").toInt(),
            query.value("roll_no").toString(),
            query.value("name").toString(),
            query.value("class_id").toInt(),
            query.value("guardian_name").toString(),
            query.value("guardian_contact").toString(),
            query.value("guardian_email").toString(),
            query.value("address").toString(),
            query.value("date_of_birth").toDate(),
            query.value("gender").toString(),
            query.value("admission_date").toDate()
        );
    }
    
    return Student();
}

Student Database::getStudentByRollNo(const QString &rollNo)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM students WHERE roll_no = ?");
    query.addBindValue(rollNo);
    
    if (query.exec() && query.next()) {
        return Student(
            query.value("id").toInt(),
            query.value("roll_no").toString(),
            query.value("name").toString(),
            query.value("class_id").toInt(),
            query.value("guardian_name").toString(),
            query.value("guardian_contact").toString(),
            query.value("guardian_email").toString(),
            query.value("address").toString(),
            query.value("date_of_birth").toDate(),
            query.value("gender").toString(),
            query.value("admission_date").toDate()
        );
    }
    
    return Student();
}

// Class operations
bool Database::addClass(const Class &classObj)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO classes (name, grade, capacity, room_number, teacher_id, description, is_active) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)"
    );
    query.addBindValue(classObj.getName());
    query.addBindValue(classObj.getGrade());
    query.addBindValue(classObj.getCapacity());
    query.addBindValue(classObj.getRoomNumber());
    query.addBindValue(classObj.getTeacherId());
    query.addBindValue(classObj.getDescription());
    query.addBindValue(classObj.isActive());
    
    return query.exec();
}

bool Database::updateClass(const Class &classObj)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE classes SET name=?, grade=?, capacity=?, room_number=?, teacher_id=?, description=?, is_active=? WHERE id=?"
    );
    query.addBindValue(classObj.getName());
    query.addBindValue(classObj.getGrade());
    query.addBindValue(classObj.getCapacity());
    query.addBindValue(classObj.getRoomNumber());
    query.addBindValue(classObj.getTeacherId());
    query.addBindValue(classObj.getDescription());
    query.addBindValue(classObj.isActive());
    query.addBindValue(classObj.getId());
    
    return query.exec();
}

bool Database::deleteClass(int classId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM classes WHERE id = ?");
    query.addBindValue(classId);
    return query.exec();
}

QList<Class> Database::getAllClasses()
{
    QList<Class> classes;
    QSqlQuery query("SELECT * FROM classes WHERE is_active = 1 ORDER BY grade, name");
    
    while (query.next()) {
        Class classObj(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("grade").toInt(),
            query.value("capacity").toInt(),
            query.value("room_number").toString(),
            query.value("teacher_id").toInt(),
            query.value("description").toString()
        );
        classObj.setActive(query.value("is_active").toBool());
        classes.append(classObj);
    }
    
    return classes;
}

Class Database::getClassById(int classId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM classes WHERE id = ?");
    query.addBindValue(classId);
    
    if (query.exec() && query.next()) {
        return Class(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("grade").toInt(),
            query.value("capacity").toInt(),
            query.value("room_number").toString(),
            query.value("teacher_id").toInt(),
            query.value("description").toString()
        );
    }
    
    return Class();
}

Class Database::getClassByName(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM classes WHERE name = ?");
    query.addBindValue(name);
    
    if (query.exec() && query.next()) {
        return Class(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("grade").toInt(),
            query.value("capacity").toInt(),
            query.value("room_number").toString(),
            query.value("teacher_id").toInt(),
            query.value("description").toString()
        );
    }
    
    return Class();
}

// Attendance operations
bool Database::markAttendance(const Attendance &attendance)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO attendance (student_id, class_id, date, status, remarks) "
        "VALUES (?, ?, ?, ?, ?)"
    );
    query.addBindValue(attendance.getStudentId());
    query.addBindValue(attendance.getClassId());
    query.addBindValue(attendance.getDate());
    query.addBindValue(static_cast<int>(attendance.getStatus()));
    query.addBindValue(attendance.getRemarks());
    
    return query.exec();
}

bool Database::updateAttendance(const Attendance &attendance)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE attendance SET student_id=?, class_id=?, date=?, status=?, remarks=? WHERE id=?"
    );
    query.addBindValue(attendance.getStudentId());
    query.addBindValue(attendance.getClassId());
    query.addBindValue(attendance.getDate());
    query.addBindValue(static_cast<int>(attendance.getStatus()));
    query.addBindValue(attendance.getRemarks());
    query.addBindValue(attendance.getId());
    
    return query.exec();
}

bool Database::deleteAttendance(int attendanceId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM attendance WHERE id = ?");
    query.addBindValue(attendanceId);
    return query.exec();
}

QList<Attendance> Database::getAttendanceByDate(const QDate &date)
{
    QList<Attendance> attendanceList;
    QSqlQuery query;
    query.prepare("SELECT * FROM attendance WHERE date = ? ORDER BY student_id");
    query.addBindValue(date);
    
    while (query.exec() && query.next()) {
        Attendance attendance(
            query.value("id").toInt(),
            query.value("student_id").toInt(),
            query.value("class_id").toInt(),
            query.value("date").toDate(),
            static_cast<Attendance::Status>(query.value("status").toInt()),
            query.value("remarks").toString()
        );
        attendance.setMarkedAt(query.value("marked_at").toDateTime());
        attendanceList.append(attendance);
    }
    
    return attendanceList;
}

QList<Attendance> Database::getAttendanceByStudent(int studentId, const QDate &startDate, const QDate &endDate)
{
    QList<Attendance> attendanceList;
    QSqlQuery query;
    query.prepare("SELECT * FROM attendance WHERE student_id = ? AND date BETWEEN ? AND ? ORDER BY date");
    query.addBindValue(studentId);
    query.addBindValue(startDate);
    query.addBindValue(endDate);
    
    while (query.exec() && query.next()) {
        Attendance attendance(
            query.value("id").toInt(),
            query.value("student_id").toInt(),
            query.value("class_id").toInt(),
            query.value("date").toDate(),
            static_cast<Attendance::Status>(query.value("status").toInt()),
            query.value("remarks").toString()
        );
        attendance.setMarkedAt(query.value("marked_at").toDateTime());
        attendanceList.append(attendance);
    }
    
    return attendanceList;
}

QList<Attendance> Database::getAttendanceByClass(int classId, const QDate &date)
{
    QList<Attendance> attendanceList;
    QSqlQuery query;
    query.prepare("SELECT * FROM attendance WHERE class_id = ? AND date = ? ORDER BY student_id");
    query.addBindValue(classId);
    query.addBindValue(date);
    
    while (query.exec() && query.next()) {
        Attendance attendance(
            query.value("id").toInt(),
            query.value("student_id").toInt(),
            query.value("class_id").toInt(),
            query.value("date").toDate(),
            static_cast<Attendance::Status>(query.value("status").toInt()),
            query.value("remarks").toString()
        );
        attendance.setMarkedAt(query.value("marked_at").toDateTime());
        attendanceList.append(attendance);
    }
    
    return attendanceList;
}

double Database::getAttendancePercentage(int studentId, const QDate &startDate, const QDate &endDate)
{
    QSqlQuery query;
    query.prepare(
        "SELECT COUNT(*) as total, "
        "SUM(CASE WHEN status = 0 THEN 1 ELSE 0 END) as present "
        "FROM attendance WHERE student_id = ? AND date BETWEEN ? AND ?"
    );
    query.addBindValue(studentId);
    query.addBindValue(startDate);
    query.addBindValue(endDate);
    
    if (query.exec() && query.next()) {
        int total = query.value("total").toInt();
        int present = query.value("present").toInt();
        return total > 0 ? (static_cast<double>(present) / total) * 100.0 : 0.0;
    }
    
    return 0.0;
}

// Holiday and Event operations
bool Database::addHoliday(const QDate &date, const QString &description)
{
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO holidays (date, description) VALUES (?, ?)");
    query.addBindValue(date);
    query.addBindValue(description);
    return query.exec();
}

bool Database::deleteHoliday(const QDate &date)
{
    QSqlQuery query;
    query.prepare("DELETE FROM holidays WHERE date = ?");
    query.addBindValue(date);
    return query.exec();
}

bool Database::isHoliday(const QDate &date)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM holidays WHERE date = ?");
    query.addBindValue(date);
    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

QString Database::getHolidayDescription(const QDate &date)
{
    QSqlQuery query;
    query.prepare("SELECT description FROM holidays WHERE date = ?");
    query.addBindValue(date);
    return query.exec() && query.next() ? query.value("description").toString() : QString();
}

QList<QDate> Database::getHolidaysInRange(const QDate &startDate, const QDate &endDate)
{
    QList<QDate> holidays;
    QSqlQuery query;
    query.prepare("SELECT date FROM holidays WHERE date BETWEEN ? AND ? ORDER BY date");
    query.addBindValue(startDate);
    query.addBindValue(endDate);
    
    while (query.exec() && query.next()) {
        holidays.append(query.value("date").toDate());
    }
    
    return holidays;
}

bool Database::addEvent(const QDate &date, const QString &title, const QString &description)
{
    QSqlQuery query;
    query.prepare("INSERT INTO events (date, title, description) VALUES (?, ?, ?)");
    query.addBindValue(date);
    query.addBindValue(title);
    query.addBindValue(description);
    return query.exec();
}

bool Database::deleteEvent(int eventId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM events WHERE id = ?");
    query.addBindValue(eventId);
    return query.exec();
}

QList<QPair<QString, QString>> Database::getEventsByDate(const QDate &date)
{
    QList<QPair<QString, QString>> events;
    QSqlQuery query;
    query.prepare("SELECT title, description FROM events WHERE date = ? ORDER BY title");
    query.addBindValue(date);
    
    while (query.exec() && query.next()) {
        events.append(qMakePair(
            query.value("title").toString(),
            query.value("description").toString()
        ));
    }
    
    return events;
}

// User authentication
bool Database::addUser(const QString &username, const QString &password, const QString &role)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash, role) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(hashPassword(password));
    query.addBindValue(role);
    return query.exec();
}

bool Database::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password_hash FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (query.exec() && query.next()) {
        QString storedHash = query.value("password_hash").toString();
        return verifyPassword(password, storedHash);
    }
    
    return false;
}

QString Database::getUserRole(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE username = ?");
    query.addBindValue(username);
    return query.exec() && query.next() ? query.value("role").toString() : QString();
}

bool Database::changePassword(const QString &username, const QString &newPassword)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET password_hash = ? WHERE username = ?");
    query.addBindValue(hashPassword(newPassword));
    query.addBindValue(username);
    return query.exec();
}

// Backup and restore
bool Database::backupDatabase(const QString &backupPath)
{
    QFile sourceFile(m_databasePath);
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

bool Database::restoreDatabase(const QString &backupPath)
{
    closeConnection();
    
    QFile sourceFile(backupPath);
    QFile targetFile(m_databasePath);
    
    if (!sourceFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    if (!targetFile.open(QIODevice::WriteOnly)) {
        sourceFile.close();
        return false;
    }
    
    QByteArray data = sourceFile.readAll();
    targetFile.write(data);
    
    sourceFile.close();
    targetFile.close();
    
    return initialize();
}

// Utility functions
QSqlTableModel* Database::getTableModel(const QString &tableName)
{
    return new QSqlTableModel(this, m_database);
}

void Database::closeConnection()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

QString Database::hashPassword(const QString &password)
{
    return PasswordHash::hashPassword(password);
}

bool Database::verifyPassword(const QString &password, const QString &hash)
{
    return PasswordHash::verifyPassword(password, hash);
}
