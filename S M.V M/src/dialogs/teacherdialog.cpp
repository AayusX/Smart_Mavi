#include "dialogs/teacherdialog.h"
#include <QApplication>
#include <QStyle>

TeacherDialog::TeacherDialog(QWidget *parent)
    : QDialog(parent)
    , m_isEditMode(false)
    , m_isValid(false)
{
    setWindowTitle("Add New Teacher");
    setModal(true);
    setMinimumSize(500, 600);
    
    setupUI();
    setupConnections();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

TeacherDialog::TeacherDialog(const Teacher &teacher, QWidget *parent)
    : QDialog(parent)
    , m_teacher(teacher)
    , m_isEditMode(true)
    , m_isValid(false)
{
    setWindowTitle("Edit Teacher");
    setModal(true);
    setMinimumSize(500, 600);
    
    setupUI();
    loadTeacherData(teacher);
    setupConnections();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

Teacher TeacherDialog::getTeacher() const
{
    return m_teacher;
}

bool TeacherDialog::isValid() const
{
    return m_isValid;
}

void TeacherDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel(m_isEditMode ? "Edit Teacher Information" : "Add New Teacher");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Personal Information Group
    QGroupBox *personalGroup = new QGroupBox("Personal Information");
    personalGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *personalLayout = new QGridLayout(personalGroup);
    
    m_nameEdit = new QLineEdit();
    m_nameEdit->setPlaceholderText("Enter teacher's full name");
    m_nameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_contactEdit = new QLineEdit();
    m_contactEdit->setPlaceholderText("Enter contact number");
    m_contactEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_emailEdit = new QLineEdit();
    m_emailEdit->setPlaceholderText("Enter email address");
    m_emailEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_addressEdit = new QTextEdit();
    m_addressEdit->setPlaceholderText("Enter address");
    m_addressEdit->setMaximumHeight(80);
    m_addressEdit->setStyleSheet("QTextEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    personalLayout->addWidget(new QLabel("Full Name:"), 0, 0);
    personalLayout->addWidget(m_nameEdit, 0, 1);
    personalLayout->addWidget(new QLabel("Contact:"), 1, 0);
    personalLayout->addWidget(m_contactEdit, 1, 1);
    personalLayout->addWidget(new QLabel("Email:"), 2, 0);
    personalLayout->addWidget(m_emailEdit, 2, 1);
    personalLayout->addWidget(new QLabel("Address:"), 3, 0);
    personalLayout->addWidget(m_addressEdit, 3, 1);
    
    mainLayout->addWidget(personalGroup);
    
    // Professional Information Group
    QGroupBox *professionalGroup = new QGroupBox("Professional Information");
    professionalGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *professionalLayout = new QGridLayout(professionalGroup);
    
    m_subjectCombo = new QComboBox();
    m_subjectCombo->addItems(Teacher::getSubjectList());
    m_subjectCombo->setEditable(true);
    m_subjectCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_assignedClassCombo = new QComboBox();
    m_assignedClassCombo->addItem("Not Assigned", 0);
    for (int i = 1; i <= 12; ++i) {
        m_assignedClassCombo->addItem(QString("Grade %1").arg(i), i);
    }
    m_assignedClassCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_joinDateEdit = new QDateEdit();
    m_joinDateEdit->setDate(QDate::currentDate());
    m_joinDateEdit->setCalendarPopup(true);
    m_joinDateEdit->setStyleSheet("QDateEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_activeCheckBox = new QCheckBox("Active");
    m_activeCheckBox->setChecked(true);
    m_activeCheckBox->setStyleSheet("QCheckBox { padding: 5px; }");
    
    professionalLayout->addWidget(new QLabel("Subject:"), 0, 0);
    professionalLayout->addWidget(m_subjectCombo, 0, 1);
    professionalLayout->addWidget(new QLabel("Assigned Class:"), 1, 0);
    professionalLayout->addWidget(m_assignedClassCombo, 1, 1);
    professionalLayout->addWidget(new QLabel("Join Date:"), 2, 0);
    professionalLayout->addWidget(m_joinDateEdit, 2, 1);
    professionalLayout->addWidget(m_activeCheckBox, 3, 0, 1, 2);
    
    mainLayout->addWidget(professionalGroup);
    
    // Buttons
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    m_saveButton = m_buttonBox->button(QDialogButtonBox::Save);
    m_cancelButton = m_buttonBox->button(QDialogButtonBox::Cancel);
    
    m_saveButton->setText("Save Teacher");
    m_saveButton->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #229954; } QPushButton:disabled { background-color: #bdc3c7; }");
    m_cancelButton->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #c0392b; }");
    
    mainLayout->addWidget(m_buttonBox);
    
    // Initially disable save button until validation passes
    m_saveButton->setEnabled(false);
}

void TeacherDialog::loadTeacherData(const Teacher &teacher)
{
    m_nameEdit->setText(teacher.getName());
    m_subjectCombo->setCurrentText(teacher.getSubject());
    m_contactEdit->setText(teacher.getContact());
    m_emailEdit->setText(teacher.getEmail());
    m_addressEdit->setPlainText(teacher.getAddress());
    m_assignedClassCombo->setCurrentIndex(teacher.getAssignedClass());
    m_joinDateEdit->setDate(teacher.getJoinDate());
    m_activeCheckBox->setChecked(teacher.isActive());
}

void TeacherDialog::setupConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &TeacherDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    // Connect validation signals
    connect(m_nameEdit, &QLineEdit::textChanged, this, &TeacherDialog::validateInput);
    connect(m_subjectCombo, &QComboBox::currentTextChanged, this, &TeacherDialog::validateInput);
    connect(m_contactEdit, &QLineEdit::textChanged, this, &TeacherDialog::validateInput);
    connect(m_emailEdit, &QLineEdit::textChanged, this, &TeacherDialog::validateInput);
}

void TeacherDialog::accept()
{
    // Create teacher object from form data
    m_teacher = Teacher(
        0, // ID will be set by database
        m_nameEdit->text().trimmed(),
        m_subjectCombo->currentText(),
        m_contactEdit->text().trimmed(),
        m_assignedClassCombo->currentData().toInt(),
        m_emailEdit->text().trimmed(),
        m_addressEdit->toPlainText().trimmed(),
        m_joinDateEdit->date()
    );
    
    if (m_teacher.isValid()) {
        QDialog::accept();
    } else {
        QMessageBox::warning(this, "Validation Error", "Please check the input fields and try again.");
    }
}

void TeacherDialog::validateInput()
{
    updateValidationStatus();
    m_saveButton->setEnabled(m_isValid);
}

void TeacherDialog::updateValidationStatus()
{
    m_isValid = validateName() && 
                validateSubject() && 
                validateContact() && 
                validateEmail();
}

bool TeacherDialog::validateName()
{
    QString name = m_nameEdit->text().trimmed();
    bool isValid = !name.isEmpty() && name.length() >= 2;
    
    if (isValid) {
        m_nameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_nameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid;
}

bool TeacherDialog::validateContact()
{
    QString contact = m_contactEdit->text().trimmed();
    bool isValid = Teacher::isValidContact(contact);
    
    if (isValid || contact.isEmpty()) {
        m_contactEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_contactEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid || contact.isEmpty();
}

bool TeacherDialog::validateEmail()
{
    QString email = m_emailEdit->text().trimmed();
    bool isValid = Teacher::isValidEmail(email);
    
    if (isValid || email.isEmpty()) {
        m_emailEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_emailEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid || email.isEmpty();
}

bool TeacherDialog::validateSubject()
{
    QString subject = m_subjectCombo->currentText().trimmed();
    bool isValid = !subject.isEmpty();
    
    if (isValid) {
        m_subjectCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_subjectCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid;
}
