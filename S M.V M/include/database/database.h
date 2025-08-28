#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QList>
#include "models/teacher.h"
#include "models/student.h"
#include "models/class.h"
#include "models/attendance.h"
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
#include <QVariant>
#include <QDate>
#include <QDateTime>
#include <QSqlTableModel>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool initialize();
    bool createTables();
    bool isConnected() const;
    
    // Teacher operations
    bool addTeacher(const Teacher &teacher);
    bool updateTeacher(const Teacher &teacher);
    bool deleteTeacher(int teacherId);
    QList<Teacher> getAllTeachers();
    Teacher getTeacherById(int teacherId);
    Teacher getTeacherByName(const QString &name);
    
    // Student operations
    bool addStudent(const Student &student);
    bool updateStudent(const Student &student);
    bool deleteStudent(int studentId);
    QList<Student> getAllStudents();
    QList<Student> getStudentsByClass(int classId);
    Student getStudentById(int studentId);
    Student getStudentByRollNo(const QString &rollNo);
    
    // Class operations
    bool addClass(const Class &classObj);
    bool updateClass(const Class &classObj);
    bool deleteClass(int classId);
    QList<Class> getAllClasses();
    Class getClassById(int classId);
    Class getClassByName(const QString &name);
    
    // Attendance operations
    bool markAttendance(const Attendance &attendance);
    bool updateAttendance(const Attendance &attendance);
    bool deleteAttendance(int attendanceId);
    QList<Attendance> getAttendanceByDate(const QDate &date);
    QList<Attendance> getAttendanceByStudent(int studentId, const QDate &startDate, const QDate &endDate);
    QList<Attendance> getAttendanceByClass(int classId, const QDate &date);
    double getAttendancePercentage(int studentId, const QDate &startDate, const QDate &endDate);
    
    // Holiday and Event operations
    bool addHoliday(const QDate &date, const QString &description);
    bool deleteHoliday(const QDate &date);
    bool isHoliday(const QDate &date);
    QString getHolidayDescription(const QDate &date);
    QList<QDate> getHolidaysInRange(const QDate &startDate, const QDate &endDate);
    
    bool addEvent(const QDate &date, const QString &title, const QString &description);
    bool deleteEvent(int eventId);
    QList<QPair<QString, QString>> getEventsByDate(const QDate &date);
    
    // User authentication
    bool addUser(const QString &username, const QString &password, const QString &role);
    bool authenticateUser(const QString &username, const QString &password);
    QString getUserRole(const QString &username);
    bool changePassword(const QString &username, const QString &newPassword);
    
    // Backup and restore
    bool backupDatabase(const QString &backupPath);
    bool restoreDatabase(const QString &backupPath);
    
    // Utility functions
    QSqlTableModel* getTableModel(const QString &tableName);
    void closeConnection();

private:
    QSqlDatabase m_database;
    QString m_databasePath;
    
    bool createTeachersTable();
    bool createStudentsTable();
    bool createClassesTable();
    bool createAttendanceTable();
    bool createHolidaysTable();
    bool createEventsTable();
    bool createUsersTable();
    
    QString hashPassword(const QString &password);
    bool verifyPassword(const QString &password, const QString &hash);
};

#endif // DATABASE_H
