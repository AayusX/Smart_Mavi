#include "student_dialog.h"

StudentDialog::StudentDialog(QWidget* parent)
    : QDialog(parent)
{
    setupUI();
    setupConnections();
}

void StudentDialog::setupUI()
{
    setWindowTitle("Student Details");
    setModal(true);
    setMinimumWidth(400);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout;
    
    // Create a header
    auto* headerLabel = new QLabel("Student Information", this);
    headerLabel->setStyleSheet("font-size: 16px; font-weight: bold; padding: 10px;");
    headerLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(headerLabel);

    // Create form widgets with modern styling
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter student name");
    nameEdit->setMinimumHeight(30);
    
    classCombo = new QComboBox(this);
    classCombo->addItems({"Class A", "Class B", "Class C"});
    classCombo->setMinimumHeight(30);
    
    yearCombo = new QComboBox(this);
    yearCombo->addItems({"Year 1", "Year 2", "Year 3", "Year 4"});
    yearCombo->setMinimumHeight(30);
    
    marksSpin = new QSpinBox(this);
    marksSpin->setRange(0, 100);
    marksSpin->setSuffix(" %");
    marksSpin->setSpecialValueText("Not graded");
    marksSpin->setMinimumHeight(30);
    
    enrollmentDate = new QDateEdit(QDate::currentDate(), this);
    enrollmentDate->setCalendarPopup(true);
    enrollmentDate->setMinimumHeight(30);
    enrollmentDate->setDisplayFormat("dd/MM/yyyy");

    // Status label for validation feedback
    statusLabel = new QLabel(this);
    statusLabel->setStyleSheet("color: red;");
    statusLabel->hide();

    // Add widgets to form layout with proper spacing
    formLayout->setSpacing(10);
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Class:", classCombo);
    formLayout->addRow("Year:", yearCombo);
    formLayout->addRow("Marks:", marksSpin);
    formLayout->addRow("Enrollment Date:", enrollmentDate);
    
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(statusLabel);
    
    // Create styled buttons
    auto* buttonBox = new QHBoxLayout;
    okButton = new QPushButton("Save", this);
    cancelButton = new QPushButton("Cancel", this);
    
    okButton->setMinimumHeight(35);
    cancelButton->setMinimumHeight(35);
    okButton->setEnabled(false);
    
    // Style buttons
    okButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border-radius: 4px; } "
                           "QPushButton:disabled { background-color: #cccccc; }");
    cancelButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; border-radius: 4px; }");
    
    buttonBox->addWidget(okButton);
    buttonBox->addWidget(cancelButton);
    
    mainLayout->addSpacing(15);
    mainLayout->addLayout(buttonBox);
}

void StudentDialog::setupConnections()
{
    connect(nameEdit, &QLineEdit::textChanged, this, &StudentDialog::validateInput);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void StudentDialog::validateInput()
{
    okButton->setEnabled(!nameEdit->text().trimmed().isEmpty());
}

void StudentDialog::setStudent(const QString& name, const QString& className, int marks, int year, const QString& date)
{
    nameEdit->setText(name);
    classCombo->setCurrentText(className);
    yearCombo->setCurrentIndex(year - 1);
    marksSpin->setValue(marks);
    enrollmentDate->setDate(QDate::fromString(date, "dd/MM/yyyy"));
}

QString StudentDialog::getStudentName() const
{
    return nameEdit->text().trimmed();
}

QString StudentDialog::getStudentClass() const
{
    return classCombo->currentText();
}

int StudentDialog::getStudentMarks() const
{
    return marksSpin->value();
}

int StudentDialog::getStudentYear() const
{
    return yearCombo->currentIndex() + 1;
}

QString StudentDialog::getEnrollmentDate() const
{
    return enrollmentDate->date().toString("dd/MM/yyyy");
}