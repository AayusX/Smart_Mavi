#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>

class Teacher;
class Student;
class Class;
class Attendance;

class CSVHandler : public QObject
{
    Q_OBJECT

public:
    explicit CSVHandler(QObject *parent = nullptr);
    
    // Import functions
    QList<Teacher> importTeachers(const QString &filename);
    QList<Student> importStudents(const QString &filename);
    QList<Class> importClasses(const QString &filename);
    QList<Attendance> importAttendance(const QString &filename);
    
    // Export functions
    bool exportTeachers(const QList<Teacher> &teachers, const QString &filename);
    bool exportStudents(const QList<Student> &students, const QString &filename);
    bool exportClasses(const QList<Class> &classes, const QString &filename);
    bool exportAttendance(const QList<Attendance> &attendance, const QString &filename);
    
    // Bulk operations
    bool bulkImportStudents(const QString &filename);
    bool bulkExportStudents(const QList<Student> &students, const QString &filename);
    bool bulkImportAttendance(const QString &filename);
    bool bulkExportAttendance(const QList<Attendance> &attendance, const QString &filename);
    
    // Template generation
    bool generateStudentTemplate(const QString &filename);
    bool generateTeacherTemplate(const QString &filename);
    bool generateClassTemplate(const QString &filename);
    bool generateAttendanceTemplate(const QString &filename);
    
    // Validation
    bool validateStudentData(const QStringList &data);
    bool validateTeacherData(const QStringList &data);
    bool validateClassData(const QStringList &data);
    bool validateAttendanceData(const QStringList &data);
    
    // Utility functions
    QStringList parseCSVLine(const QString &line);
    QString escapeCSVField(const QString &field);
    QString unescapeCSVField(const QString &field);
    bool isValidCSVFile(const QString &filename);
    QString getDefaultExportPath();

private:
    // Helper methods
    Teacher parseTeacherData(const QStringList &data);
    Student parseStudentData(const QStringList &data);
    Class parseClassData(const QStringList &data);
    Attendance parseAttendanceData(const QStringList &data);
    
    QStringList formatTeacherData(const Teacher &teacher);
    QStringList formatStudentData(const Student &student);
    QStringList formatClassData(const Class &classObj);
    QStringList formatAttendanceData(const Attendance &attendance);
    
    QString getTeacherHeaders();
    QString getStudentHeaders();
    QString getClassHeaders();
    QString getAttendanceHeaders();
    
    bool writeHeaders(const QString &filename, const QString &headers);
    bool writeData(const QString &filename, const QList<QStringList> &data);
    
    // Error handling
    void logError(const QString &error);
    void showImportError(const QString &filename, const QString &error);
    void showExportError(const QString &filename, const QString &error);
    
    // File operations
    bool createBackup(const QString &filename);
    bool restoreBackup(const QString &filename);
    QString getBackupPath(const QString &filename);
};

// For QVariant support
Q_DECLARE_METATYPE(CSVHandler)

#endif // CSVHANDLER_H
