#include "dialogs/studentdialog.h"
#include <QApplication>
#include <QStyle>

StudentDialog::StudentDialog(QWidget *parent)
    : QDialog(parent)
    , m_isEditMode(false)
    , m_isValid(false)
{
    setWindowTitle("Add New Student");
    setModal(true);
    setMinimumSize(600, 700);
    
    setupUI();
    setupConnections();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

StudentDialog::StudentDialog(const Student &student, QWidget *parent)
    : QDialog(parent)
    , m_student(student)
    , m_isEditMode(true)
    , m_isValid(false)
{
    setWindowTitle("Edit Student");
    setModal(true);
    setMinimumSize(600, 700);
    
    setupUI();
    loadStudentData(student);
    setupConnections();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

Student StudentDialog::getStudent() const
{
    return m_student;
}

bool StudentDialog::isValid() const
{
    return m_isValid;
}

void StudentDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel(m_isEditMode ? "Edit Student Information" : "Add New Student");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Student Information Group
    QGroupBox *studentGroup = new QGroupBox("Student Information");
    studentGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *studentLayout = new QGridLayout(studentGroup);
    
    m_rollNoEdit = new QLineEdit();
    m_rollNoEdit->setPlaceholderText("Enter roll number (e.g., ST001)");
    m_rollNoEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_nameEdit = new QLineEdit();
    m_nameEdit->setPlaceholderText("Enter student's full name");
    m_nameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_classCombo = new QComboBox();
    m_classCombo->addItem("Select Class", 0);
    for (int i = 1; i <= 12; ++i) {
        m_classCombo->addItem(QString("Grade %1").arg(i), i);
    }
    m_classCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_genderCombo = new QComboBox();
    m_genderCombo->addItems(Student::getGenderList());
    m_genderCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_dateOfBirthEdit = new QDateEdit();
    m_dateOfBirthEdit->setDate(QDate::currentDate().addYears(-5));
    m_dateOfBirthEdit->setCalendarPopup(true);
    m_dateOfBirthEdit->setStyleSheet("QDateEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_admissionDateEdit = new QDateEdit();
    m_admissionDateEdit->setDate(QDate::currentDate());
    m_admissionDateEdit->setCalendarPopup(true);
    m_admissionDateEdit->setStyleSheet("QDateEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    studentLayout->addWidget(new QLabel("Roll Number:"), 0, 0);
    studentLayout->addWidget(m_rollNoEdit, 0, 1);
    studentLayout->addWidget(new QLabel("Full Name:"), 1, 0);
    studentLayout->addWidget(m_nameEdit, 1, 1);
    studentLayout->addWidget(new QLabel("Class:"), 2, 0);
    studentLayout->addWidget(m_classCombo, 2, 1);
    studentLayout->addWidget(new QLabel("Gender:"), 3, 0);
    studentLayout->addWidget(m_genderCombo, 3, 1);
    studentLayout->addWidget(new QLabel("Date of Birth:"), 4, 0);
    studentLayout->addWidget(m_dateOfBirthEdit, 4, 1);
    studentLayout->addWidget(new QLabel("Admission Date:"), 5, 0);
    studentLayout->addWidget(m_admissionDateEdit, 5, 1);
    
    mainLayout->addWidget(studentGroup);
    
    // Guardian Information Group
    QGroupBox *guardianGroup = new QGroupBox("Guardian Information");
    guardianGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *guardianLayout = new QGridLayout(guardianGroup);
    
    m_guardianNameEdit = new QLineEdit();
    m_guardianNameEdit->setPlaceholderText("Enter guardian's full name");
    m_guardianNameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_guardianContactEdit = new QLineEdit();
    m_guardianContactEdit->setPlaceholderText("Enter guardian's contact number");
    m_guardianContactEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_guardianEmailEdit = new QLineEdit();
    m_guardianEmailEdit->setPlaceholderText("Enter guardian's email address");
    m_guardianEmailEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_addressEdit = new QTextEdit();
    m_addressEdit->setPlaceholderText("Enter student's address");
    m_addressEdit->setMaximumHeight(80);
    m_addressEdit->setStyleSheet("QTextEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    guardianLayout->addWidget(new QLabel("Guardian Name:"), 0, 0);
    guardianLayout->addWidget(m_guardianNameEdit, 0, 1);
    guardianLayout->addWidget(new QLabel("Guardian Contact:"), 1, 0);
    guardianLayout->addWidget(m_guardianContactEdit, 1, 1);
    guardianLayout->addWidget(new QLabel("Guardian Email:"), 2, 0);
    guardianLayout->addWidget(m_guardianEmailEdit, 2, 1);
    guardianLayout->addWidget(new QLabel("Address:"), 3, 0);
    guardianLayout->addWidget(m_addressEdit, 3, 1);
    
    mainLayout->addWidget(guardianGroup);
    
    // Status Group
    QGroupBox *statusGroup = new QGroupBox("Status");
    statusGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QHBoxLayout *statusLayout = new QHBoxLayout(statusGroup);
    
    m_activeCheckBox = new QCheckBox("Active Student");
    m_activeCheckBox->setChecked(true);
    m_activeCheckBox->setStyleSheet("QCheckBox { padding: 5px; }");
    
    statusLayout->addWidget(m_activeCheckBox);
    statusLayout->addStretch();
    
    mainLayout->addWidget(statusGroup);
    
    // Buttons
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    m_saveButton = m_buttonBox->button(QDialogButtonBox::Save);
    m_cancelButton = m_buttonBox->button(QDialogButtonBox::Cancel);
    
    m_saveButton->setText("Save Student");
    m_saveButton->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #229954; } QPushButton:disabled { background-color: #bdc3c7; }");
    m_cancelButton->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #c0392b; }");
    
    mainLayout->addWidget(m_buttonBox);
    
    // Initially disable save button until validation passes
    m_saveButton->setEnabled(false);
}

void StudentDialog::loadStudentData(const Student &student)
{
    m_rollNoEdit->setText(student.getRollNo());
    m_nameEdit->setText(student.getName());
    m_classCombo->setCurrentIndex(student.getClassId());
    m_guardianNameEdit->setText(student.getGuardianName());
    m_guardianContactEdit->setText(student.getGuardianContact());
    m_guardianEmailEdit->setText(student.getGuardianEmail());
    m_addressEdit->setPlainText(student.getAddress());
    m_dateOfBirthEdit->setDate(student.getDateOfBirth());
    m_genderCombo->setCurrentText(student.getGender());
    m_admissionDateEdit->setDate(student.getAdmissionDate());
    m_activeCheckBox->setChecked(student.isActive());
}

void StudentDialog::setupConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &StudentDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    // Connect validation signals
    connect(m_rollNoEdit, &QLineEdit::textChanged, this, &StudentDialog::validateInput);
    connect(m_nameEdit, &QLineEdit::textChanged, this, &StudentDialog::validateInput);
    connect(m_classCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &StudentDialog::validateInput);
    connect(m_guardianContactEdit, &QLineEdit::textChanged, this, &StudentDialog::validateInput);
    connect(m_guardianEmailEdit, &QLineEdit::textChanged, this, &StudentDialog::validateInput);
    connect(m_dateOfBirthEdit, &QDateEdit::dateChanged, this, &StudentDialog::validateInput);
}

void StudentDialog::accept()
{
    // Create student object from form data
    m_student = Student(
        0, // ID will be set by database
        m_rollNoEdit->text().trimmed(),
        m_nameEdit->text().trimmed(),
        m_classCombo->currentData().toInt(),
        m_guardianNameEdit->text().trimmed(),
        m_guardianContactEdit->text().trimmed(),
        m_guardianEmailEdit->text().trimmed(),
        m_addressEdit->toPlainText().trimmed(),
        m_dateOfBirthEdit->date(),
        m_genderCombo->currentText(),
        m_admissionDateEdit->date()
    );
    
    if (m_student.isValid()) {
        QDialog::accept();
    } else {
        QMessageBox::warning(this, "Validation Error", "Please check the input fields and try again.");
    }
}

void StudentDialog::validateInput()
{
    updateValidationStatus();
    m_saveButton->setEnabled(m_isValid);
}

void StudentDialog::updateValidationStatus()
{
    m_isValid = validateRollNo() && 
                validateName() && 
                validateClass() &&
                validateDateOfBirth() &&
                validateGuardianContact() && 
                validateGuardianEmail();
}

bool StudentDialog::validateRollNo()
{
    QString rollNo = m_rollNoEdit->text().trimmed();
    bool isValid = Student::isValidRollNo(rollNo);
    
    if (isValid) {
        m_rollNoEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_rollNoEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid;
}

bool StudentDialog::validateName()
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

bool StudentDialog::validateClass()
{
    int classId = m_classCombo->currentData().toInt();
    bool isValid = classId > 0;
    
    if (isValid) {
        m_classCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_classCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid;
}

bool StudentDialog::validateDateOfBirth()
{
    QDate dob = m_dateOfBirthEdit->date();
    bool isValid = Student::isValidDateOfBirth(dob);
    
    if (isValid) {
        m_dateOfBirthEdit->setStyleSheet("QDateEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_dateOfBirthEdit->setStyleSheet("QDateEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid;
}

bool StudentDialog::validateGuardianContact()
{
    QString contact = m_guardianContactEdit->text().trimmed();
    bool isValid = Student::isValidContact(contact);
    
    if (isValid || contact.isEmpty()) {
        m_guardianContactEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_guardianContactEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid || contact.isEmpty();
}

bool StudentDialog::validateGuardianEmail()
{
    QString email = m_guardianEmailEdit->text().trimmed();
    bool isValid = Student::isValidEmail(email);
    
    if (isValid || email.isEmpty()) {
        m_guardianEmailEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_guardianEmailEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid || email.isEmpty();
}
