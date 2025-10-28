#pragma once
#include "common.h"

class StudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit StudentDialog(QWidget* parent = nullptr);
    void setStudent(const QString& name, const QString& className, int marks, int year, const QString& date);
    QString getStudentName() const;
    QString getStudentClass() const;
    int getStudentMarks() const;
    int getStudentYear() const;
    QString getEnrollmentDate() const;

private:
    QLineEdit* nameEdit;
    QComboBox* classCombo;
    QComboBox* yearCombo;
    QSpinBox* marksSpin;
    QDateEdit* enrollmentDate;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QLabel* statusLabel;

    void setupUI();
    void setupConnections();
    void validateInput();
};