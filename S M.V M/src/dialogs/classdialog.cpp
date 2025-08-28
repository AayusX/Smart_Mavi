#include "dialogs/classdialog.h"
#include <QApplication>
#include <QStyle>

ClassDialog::ClassDialog(QWidget *parent)
    : QDialog(parent)
    , m_isEditMode(false)
    , m_isValid(false)
{
    setWindowTitle("Add New Class");
    setModal(true);
    setMinimumSize(500, 500);
    
    setupUI();
    setupConnections();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

ClassDialog::ClassDialog(const Class &classObj, QWidget *parent)
    : QDialog(parent)
    , m_class(classObj)
    , m_isEditMode(true)
    , m_isValid(false)
{
    setWindowTitle("Edit Class");
    setModal(true);
    setMinimumSize(500, 500);
    
    setupUI();
    loadClassData(classObj);
    setupConnections();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

Class ClassDialog::getClass() const
{
    return m_class;
}

bool ClassDialog::isValid() const
{
    return m_isValid;
}

void ClassDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel(m_isEditMode ? "Edit Class Information" : "Add New Class");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Class Information Group
    QGroupBox *classGroup = new QGroupBox("Class Information");
    classGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *classLayout = new QGridLayout(classGroup);
    
    m_nameEdit = new QLineEdit();
    m_nameEdit->setPlaceholderText("Enter class name (e.g., Class A, Section A)");
    m_nameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_gradeCombo = new QComboBox();
    m_gradeCombo->addItem("Select Grade", 0);
    for (int i = 1; i <= 12; ++i) {
        m_gradeCombo->addItem(QString("Grade %1").arg(i), i);
    }
    m_gradeCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_capacitySpinBox = new QSpinBox();
    m_capacitySpinBox->setRange(1, 100);
    m_capacitySpinBox->setValue(40);
    m_capacitySpinBox->setSuffix(" students");
    m_capacitySpinBox->setStyleSheet("QSpinBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_roomNumberEdit = new QLineEdit();
    m_roomNumberEdit->setPlaceholderText("Enter room number (e.g., Room 101)");
    m_roomNumberEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_teacherCombo = new QComboBox();
    m_teacherCombo->addItem("No Teacher Assigned", 0);
    // In a real implementation, this would be populated with actual teachers
    m_teacherCombo->addItem("Mr. Ram Bahadur", 1);
    m_teacherCombo->addItem("Mrs. Sita Devi", 2);
    m_teacherCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_descriptionEdit = new QTextEdit();
    m_descriptionEdit->setPlaceholderText("Enter class description (optional)");
    m_descriptionEdit->setMaximumHeight(80);
    m_descriptionEdit->setStyleSheet("QTextEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    classLayout->addWidget(new QLabel("Class Name:"), 0, 0);
    classLayout->addWidget(m_nameEdit, 0, 1);
    classLayout->addWidget(new QLabel("Grade:"), 1, 0);
    classLayout->addWidget(m_gradeCombo, 1, 1);
    classLayout->addWidget(new QLabel("Capacity:"), 2, 0);
    classLayout->addWidget(m_capacitySpinBox, 2, 1);
    classLayout->addWidget(new QLabel("Room Number:"), 3, 0);
    classLayout->addWidget(m_roomNumberEdit, 3, 1);
    classLayout->addWidget(new QLabel("Assigned Teacher:"), 4, 0);
    classLayout->addWidget(m_teacherCombo, 4, 1);
    classLayout->addWidget(new QLabel("Description:"), 5, 0);
    classLayout->addWidget(m_descriptionEdit, 5, 1);
    
    mainLayout->addWidget(classGroup);
    
    // Status Group
    QGroupBox *statusGroup = new QGroupBox("Status");
    statusGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QHBoxLayout *statusLayout = new QHBoxLayout(statusGroup);
    
    m_activeCheckBox = new QCheckBox("Active Class");
    m_activeCheckBox->setChecked(true);
    m_activeCheckBox->setStyleSheet("QCheckBox { padding: 5px; }");
    
    statusLayout->addWidget(m_activeCheckBox);
    statusLayout->addStretch();
    
    mainLayout->addWidget(statusGroup);
    
    // Buttons
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    m_saveButton = m_buttonBox->button(QDialogButtonBox::Save);
    m_cancelButton = m_buttonBox->button(QDialogButtonBox::Cancel);
    
    m_saveButton->setText("Save Class");
    m_saveButton->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #229954; } QPushButton:disabled { background-color: #bdc3c7; }");
    m_cancelButton->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #c0392b; }");
    
    mainLayout->addWidget(m_buttonBox);
    
    // Initially disable save button until validation passes
    m_saveButton->setEnabled(false);
}

void ClassDialog::loadClassData(const Class &classObj)
{
    m_nameEdit->setText(classObj.getName());
    m_gradeCombo->setCurrentIndex(classObj.getGrade());
    m_capacitySpinBox->setValue(classObj.getCapacity());
    m_roomNumberEdit->setText(classObj.getRoomNumber());
    m_teacherCombo->setCurrentIndex(classObj.getTeacherId());
    m_descriptionEdit->setPlainText(classObj.getDescription());
    m_activeCheckBox->setChecked(classObj.isActive());
}

void ClassDialog::setupConnections()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &ClassDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    // Connect validation signals
    connect(m_nameEdit, &QLineEdit::textChanged, this, &ClassDialog::validateInput);
    connect(m_gradeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ClassDialog::validateInput);
    connect(m_capacitySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ClassDialog::validateInput);
    connect(m_roomNumberEdit, &QLineEdit::textChanged, this, &ClassDialog::validateInput);
}

void ClassDialog::accept()
{
    // Create class object from form data
    m_class = Class(
        0, // ID will be set by database
        m_nameEdit->text().trimmed(),
        m_gradeCombo->currentData().toInt(),
        m_capacitySpinBox->value(),
        m_roomNumberEdit->text().trimmed(),
        m_teacherCombo->currentData().toInt(),
        m_descriptionEdit->toPlainText().trimmed()
    );
    
    if (m_class.isValid()) {
        QDialog::accept();
    } else {
        QMessageBox::warning(this, "Validation Error", "Please check the input fields and try again.");
    }
}

void ClassDialog::validateInput()
{
    updateValidationStatus();
    m_saveButton->setEnabled(m_isValid);
}

void ClassDialog::updateValidationStatus()
{
    m_isValid = validateName() && 
                validateGrade() && 
                validateCapacity() &&
                validateRoomNumber();
}

bool ClassDialog::validateName()
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

bool ClassDialog::validateGrade()
{
    int grade = m_gradeCombo->currentData().toInt();
    bool isValid = Class::isValidGrade(grade);
    
    if (isValid) {
        m_gradeCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_gradeCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid;
}

bool ClassDialog::validateCapacity()
{
    int capacity = m_capacitySpinBox->value();
    bool isValid = Class::isValidCapacity(capacity);
    
    if (isValid) {
        m_capacitySpinBox->setStyleSheet("QSpinBox { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_capacitySpinBox->setStyleSheet("QSpinBox { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid;
}

bool ClassDialog::validateRoomNumber()
{
    QString roomNumber = m_roomNumberEdit->text().trimmed();
    bool isValid = Class::isValidRoomNumber(roomNumber);
    
    if (isValid || roomNumber.isEmpty()) {
        m_roomNumberEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #27ae60; border-radius: 4px; }");
    } else {
        m_roomNumberEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #e74c3c; border-radius: 4px; }");
    }
    
    return isValid || roomNumber.isEmpty();
}
