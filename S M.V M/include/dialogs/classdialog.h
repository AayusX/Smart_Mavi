#ifndef CLASSDIALOG_H
#define CLASSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QCheckBox>
#include "models/class.h"

class ClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClassDialog(QWidget *parent = nullptr);
    explicit ClassDialog(const Class &classObj, QWidget *parent = nullptr);
    
    Class getClass() const;
    bool isValid() const;

private slots:
    void accept() override;
    void validateInput();

private:
    void setupUI();
    void loadClassData(const Class &classObj);
    void setupConnections();
    
    // UI Components
    QLineEdit *m_nameEdit;
    QComboBox *m_gradeCombo;
    QSpinBox *m_capacitySpinBox;
    QLineEdit *m_roomNumberEdit;
    QComboBox *m_teacherCombo;
    QTextEdit *m_descriptionEdit;
    QCheckBox *m_activeCheckBox;
    
    QDialogButtonBox *m_buttonBox;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
    
    // Data
    Class m_class;
    bool m_isEditMode;
    bool m_isValid;
    
    // Validation
    void updateValidationStatus();
    bool validateName();
    bool validateGrade();
    bool validateCapacity();
    bool validateRoomNumber();
};

#endif // CLASSDIALOG_H
