#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QCheckBox>
#include "models/student.h"

class StudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDialog(QWidget *parent = nullptr);
    explicit StudentDialog(const Student &student, QWidget *parent = nullptr);
    
    Student getStudent() const;
    bool isValid() const;

private slots:
    void accept() override;
    void validateInput();

private:
    void setupUI();
    void loadStudentData(const Student &student);
    void setupConnections();
    
    // UI Components
    QLineEdit *m_rollNoEdit;
    QLineEdit *m_nameEdit;
    QComboBox *m_classCombo;
    QLineEdit *m_guardianNameEdit;
    QLineEdit *m_guardianContactEdit;
    QLineEdit *m_guardianEmailEdit;
    QTextEdit *m_addressEdit;
    QDateEdit *m_dateOfBirthEdit;
    QComboBox *m_genderCombo;
    QDateEdit *m_admissionDateEdit;
    QCheckBox *m_activeCheckBox;
    
    QDialogButtonBox *m_buttonBox;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    
    // Data
    Student m_student;
    bool m_isEditMode;
    bool m_isValid;
    
    // Validation
    void updateValidationStatus();
    bool validateRollNo();
    bool validateName();
    bool validateGuardianContact();
    bool validateGuardianEmail();
    bool validateDateOfBirth();
    bool validateClass();
};

#endif // STUDENTDIALOG_H
