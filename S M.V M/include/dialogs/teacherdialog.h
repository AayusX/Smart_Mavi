#ifndef TEACHERDIALOG_H
#define TEACHERDIALOG_H

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
#include "models/teacher.h"

class TeacherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherDialog(QWidget *parent = nullptr);
    explicit TeacherDialog(const Teacher &teacher, QWidget *parent = nullptr);
    
    Teacher getTeacher() const;
    bool isValid() const;

private slots:
    void accept() override;
    void validateInput();

private:
    void setupUI();
    void loadTeacherData(const Teacher &teacher);
    void setupConnections();
    
    // UI Components
    QLineEdit *m_nameEdit;
    QComboBox *m_subjectCombo;
    QLineEdit *m_contactEdit;
    QLineEdit *m_emailEdit;
    QTextEdit *m_addressEdit;
    QComboBox *m_assignedClassCombo;
    QDateEdit *m_joinDateEdit;
    QCheckBox *m_activeCheckBox;
    
    QDialogButtonBox *m_buttonBox;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    
    // Data
    Teacher m_teacher;
    bool m_isEditMode;
    bool m_isValid;
    
    // Validation
    void updateValidationStatus();
    bool validateName();
    bool validateContact();
    bool validateEmail();
    bool validateSubject();
};

#endif // TEACHERDIALOG_H
