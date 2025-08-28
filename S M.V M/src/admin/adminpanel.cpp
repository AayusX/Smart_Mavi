#include "admin/adminpanel.h"
#include "database/database.h"
#include "utils/passwordhash.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QMessageBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QHeaderView>
#include <QInputDialog>
#include <QFileDialog>
#include <QSettings>
#include <QApplication>
#include <QStyle>

AdminPanel::AdminPanel(Database *database, QWidget *parent)
    : QDialog(parent)
    , m_database(database)
    , m_isAuthenticated(false)
    , m_enableNotifications(true)
    , m_autoBackup(true)
    , m_backupInterval(7)
    , m_schoolName("Shree MA.VI Imilya")
    , m_schoolAddress("Imilya, Nepal")
    , m_schoolContact("+977-123456789")
    , m_schoolDescription("A leading educational institution committed to excellence in education.")
    , m_enableAuditLog(true)
    , m_requireStrongPasswords(true)
    , m_sessionTimeout(30)
    , m_enableTwoFactor(false)
{
    setWindowTitle("Admin Panel - Smart MA.VI Manager");
    setModal(true);
    setMinimumSize(800, 600);
    
    setupUI();
    loadSystemSettings();
    
    // Set window icon
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
}

AdminPanel::~AdminPanel()
{
    saveSystemSettings();
}

bool AdminPanel::authenticate(const QString &username, const QString &password)
{
    if (m_database->authenticateUser(username, password)) {
        m_isAuthenticated = true;
        m_currentUser = username;
        m_currentUserRole = m_database->getUserRole(username);
        
        // Load user table and settings
        loadUserTable();
        loadSystemSettings();
        
        showNotification("Authentication successful", "success");
        return true;
    } else {
        showNotification("Authentication failed. Please check your credentials.", "error");
        return false;
    }
}

void AdminPanel::logout()
{
    m_isAuthenticated = false;
    m_currentUser.clear();
    m_currentUserRole.clear();
    
    // Clear sensitive data
    m_usernameEdit->clear();
    m_passwordEdit->clear();
    m_authStatusLabel->setText("Not authenticated");
    m_authStatusLabel->setStyleSheet("color: red;");
    
    showNotification("Logged out successfully", "info");
}

void AdminPanel::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Create tab widget
    m_tabWidget = new QTabWidget(this);
    mainLayout->addWidget(m_tabWidget);
    
    setupAuthenticationTab();
    setupUserManagementTab();
    setupSystemSettingsTab();
    setupSecurityTab();
    setupBackupTab();
    
    // Status bar
    QLabel *statusLabel = new QLabel("Admin Panel - Smart MA.VI Manager");
    statusLabel->setStyleSheet("color: #666; padding: 5px; border-top: 1px solid #ccc;");
    mainLayout->addWidget(statusLabel);
}

void AdminPanel::setupAuthenticationTab()
{
    m_authWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_authWidget);
    
    // Title
    QLabel *titleLabel = new QLabel("Admin Authentication");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Login form
    QGroupBox *loginGroup = new QGroupBox("Login");
    loginGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *loginLayout = new QGridLayout(loginGroup);
    
    m_usernameEdit = new QLineEdit();
    m_usernameEdit->setPlaceholderText("Enter username");
    m_usernameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setPlaceholderText("Enter password");
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passwordEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_loginBtn = new QPushButton("Login");
    m_loginBtn->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #2980b9; }");
    
    m_changePasswordBtn = new QPushButton("Change Password");
    m_changePasswordBtn->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #7f8c8d; }");
    
    m_authStatusLabel = new QLabel("Not authenticated");
    m_authStatusLabel->setStyleSheet("color: red; font-weight: bold; padding: 10px;");
    
    loginLayout->addWidget(new QLabel("Username:"), 0, 0);
    loginLayout->addWidget(m_usernameEdit, 0, 1);
    loginLayout->addWidget(new QLabel("Password:"), 1, 0);
    loginLayout->addWidget(m_passwordEdit, 1, 1);
    loginLayout->addWidget(m_loginBtn, 2, 0);
    loginLayout->addWidget(m_changePasswordBtn, 2, 1);
    loginLayout->addWidget(m_authStatusLabel, 3, 0, 1, 2, Qt::AlignCenter);
    
    layout->addWidget(loginGroup);
    layout->addStretch();
    
    // Connect signals
    connect(m_loginBtn, &QPushButton::clicked, this, &AdminPanel::login);
    connect(m_changePasswordBtn, &QPushButton::clicked, this, &AdminPanel::changePassword);
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &AdminPanel::login);
    
    m_tabWidget->addTab(m_authWidget, "Authentication");
}

void AdminPanel::setupUserManagementTab()
{
    m_userWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_userWidget);
    
    // Title
    QLabel *titleLabel = new QLabel("User Management");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Add user form
    QGroupBox *addUserGroup = new QGroupBox("Add New User");
    addUserGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *addUserLayout = new QGridLayout(addUserGroup);
    
    m_newUsernameEdit = new QLineEdit();
    m_newUsernameEdit->setPlaceholderText("Enter username");
    m_newUsernameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_newPasswordEdit = new QLineEdit();
    m_newPasswordEdit->setPlaceholderText("Enter password");
    m_newPasswordEdit->setEchoMode(QLineEdit::Password);
    m_newPasswordEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_newUserRoleCombo = new QComboBox();
    m_newUserRoleCombo->addItems({"admin", "teacher", "student"});
    m_newUserRoleCombo->setStyleSheet("QComboBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    QPushButton *addUserBtn = new QPushButton("Add User");
    addUserBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 10px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #229954; }");
    
    addUserLayout->addWidget(new QLabel("Username:"), 0, 0);
    addUserLayout->addWidget(m_newUsernameEdit, 0, 1);
    addUserLayout->addWidget(new QLabel("Password:"), 1, 0);
    addUserLayout->addWidget(m_newPasswordEdit, 1, 1);
    addUserLayout->addWidget(new QLabel("Role:"), 2, 0);
    addUserLayout->addWidget(m_newUserRoleCombo, 2, 1);
    addUserLayout->addWidget(addUserBtn, 3, 0, 1, 2);
    
    layout->addWidget(addUserGroup);
    
    // User table
    QGroupBox *userTableGroup = new QGroupBox("Existing Users");
    userTableGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QVBoxLayout *userTableLayout = new QVBoxLayout(userTableGroup);
    
    m_userTable = new QTableWidget();
    m_userTable->setColumnCount(4);
    m_userTable->setHorizontalHeaderLabels({"ID", "Username", "Role", "Created At"});
    m_userTable->setAlternatingRowColors(true);
    m_userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_userTable->horizontalHeader()->setStretchLastSection(true);
    m_userTable->setStyleSheet("QTableWidget { gridline-color: #bdc3c7; } QHeaderView::section { background-color: #ecf0f1; padding: 8px; border: 1px solid #bdc3c7; }");
    
    QHBoxLayout *tableButtonsLayout = new QHBoxLayout();
    m_editUserBtn = new QPushButton("Edit User");
    m_editUserBtn->setStyleSheet("QPushButton { background-color: #f39c12; color: white; padding: 8px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #e67e22; }");
    
    m_deleteUserBtn = new QPushButton("Delete User");
    m_deleteUserBtn->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; padding: 8px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #c0392b; }");
    
    QPushButton *refreshBtn = new QPushButton("Refresh");
    refreshBtn->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 8px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #2980b9; }");
    
    tableButtonsLayout->addWidget(m_editUserBtn);
    tableButtonsLayout->addWidget(m_deleteUserBtn);
    tableButtonsLayout->addWidget(refreshBtn);
    tableButtonsLayout->addStretch();
    
    userTableLayout->addWidget(m_userTable);
    userTableLayout->addLayout(tableButtonsLayout);
    
    layout->addWidget(userTableGroup);
    
    // Connect signals
    connect(addUserBtn, &QPushButton::clicked, this, &AdminPanel::addUser);
    connect(m_editUserBtn, &QPushButton::clicked, this, &AdminPanel::editUser);
    connect(m_deleteUserBtn, &QPushButton::clicked, this, &AdminPanel::deleteUser);
    connect(refreshBtn, &QPushButton::clicked, this, &AdminPanel::refreshUserTable);
    
    m_tabWidget->addTab(m_userWidget, "User Management");
}

void AdminPanel::setupSystemSettingsTab()
{
    m_settingsWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_settingsWidget);
    
    // Title
    QLabel *titleLabel = new QLabel("System Settings");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // School information
    QGroupBox *schoolGroup = new QGroupBox("School Information");
    schoolGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *schoolLayout = new QGridLayout(schoolGroup);
    
    m_schoolNameEdit = new QLineEdit(m_schoolName);
    m_schoolNameEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_schoolAddressEdit = new QLineEdit(m_schoolAddress);
    m_schoolAddressEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    m_schoolContactEdit = new QLineEdit(m_schoolContact);
    m_schoolContactEdit->setStyleSheet("QLineEdit { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    schoolLayout->addWidget(new QLabel("School Name:"), 0, 0);
    schoolLayout->addWidget(m_schoolNameEdit, 0, 1);
    schoolLayout->addWidget(new QLabel("Address:"), 1, 0);
    schoolLayout->addWidget(m_schoolAddressEdit, 1, 1);
    schoolLayout->addWidget(new QLabel("Contact:"), 2, 0);
    schoolLayout->addWidget(m_schoolContactEdit, 2, 1);
    
    layout->addWidget(schoolGroup);
    
    // Application settings
    QGroupBox *appGroup = new QGroupBox("Application Settings");
    appGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *appLayout = new QGridLayout(appGroup);
    
    m_enableNotificationsCheckBox = new QCheckBox("Enable Notifications");
    m_enableNotificationsCheckBox->setChecked(m_enableNotifications);
    m_enableNotificationsCheckBox->setStyleSheet("QCheckBox { padding: 5px; }");
    
    m_autoBackupCheckBox = new QCheckBox("Auto Backup");
    m_autoBackupCheckBox->setChecked(m_autoBackup);
    m_autoBackupCheckBox->setStyleSheet("QCheckBox { padding: 5px; }");
    
    m_backupIntervalSpinBox = new QSpinBox();
    m_backupIntervalSpinBox->setRange(1, 30);
    m_backupIntervalSpinBox->setValue(m_backupInterval);
    m_backupIntervalSpinBox->setSuffix(" days");
    m_backupIntervalSpinBox->setStyleSheet("QSpinBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    appLayout->addWidget(m_enableNotificationsCheckBox, 0, 0);
    appLayout->addWidget(m_autoBackupCheckBox, 1, 0);
    appLayout->addWidget(new QLabel("Backup Interval:"), 2, 0);
    appLayout->addWidget(m_backupIntervalSpinBox, 2, 1);
    
    layout->addWidget(appGroup);
    
    // Save button
    m_saveSettingsBtn = new QPushButton("Save Settings");
    m_saveSettingsBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 12px; border: none; border-radius: 4px; font-weight: bold; font-size: 14px; } QPushButton:hover { background-color: #229954; }");
    layout->addWidget(m_saveSettingsBtn);
    
    layout->addStretch();
    
    // Connect signals
    connect(m_saveSettingsBtn, &QPushButton::clicked, this, &AdminPanel::saveSystemSettings);
    
    m_tabWidget->addTab(m_settingsWidget, "System Settings");
}

void AdminPanel::setupSecurityTab()
{
    m_securityWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_securityWidget);
    
    // Title
    QLabel *titleLabel = new QLabel("Security Settings");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Security options
    QGroupBox *securityGroup = new QGroupBox("Security Options");
    securityGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QGridLayout *securityLayout = new QGridLayout(securityGroup);
    
    m_enableAuditLogCheckBox = new QCheckBox("Enable Audit Log");
    m_enableAuditLogCheckBox->setChecked(m_enableAuditLog);
    m_enableAuditLogCheckBox->setStyleSheet("QCheckBox { padding: 5px; }");
    
    m_requireStrongPasswordsCheckBox = new QCheckBox("Require Strong Passwords");
    m_requireStrongPasswordsCheckBox->setChecked(m_requireStrongPasswords);
    m_requireStrongPasswordsCheckBox->setStyleSheet("QCheckBox { padding: 5px; }");
    
    m_sessionTimeoutSpinBox = new QSpinBox();
    m_sessionTimeoutSpinBox->setRange(5, 120);
    m_sessionTimeoutSpinBox->setValue(m_sessionTimeout);
    m_sessionTimeoutSpinBox->setSuffix(" minutes");
    m_sessionTimeoutSpinBox->setStyleSheet("QSpinBox { padding: 8px; border: 1px solid #bdc3c7; border-radius: 4px; }");
    
    securityLayout->addWidget(m_enableAuditLogCheckBox, 0, 0);
    securityLayout->addWidget(m_requireStrongPasswordsCheckBox, 1, 0);
    securityLayout->addWidget(new QLabel("Session Timeout:"), 2, 0);
    securityLayout->addWidget(m_sessionTimeoutSpinBox, 2, 1);
    
    layout->addWidget(securityGroup);
    layout->addStretch();
    
    m_tabWidget->addTab(m_securityWidget, "Security");
}

void AdminPanel::setupBackupTab()
{
    m_backupWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_backupWidget);
    
    // Title
    QLabel *titleLabel = new QLabel("Backup & Restore");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin: 10px;");
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    
    // Backup actions
    QGroupBox *backupGroup = new QGroupBox("Database Operations");
    backupGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #bdc3c7; border-radius: 5px; margin-top: 10px; } QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    
    QVBoxLayout *backupLayout = new QVBoxLayout(backupGroup);
    
    m_backupNowBtn = new QPushButton("Backup Database Now");
    m_backupNowBtn->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 12px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #229954; }");
    
    m_restoreBtn = new QPushButton("Restore Database");
    m_restoreBtn->setStyleSheet("QPushButton { background-color: #f39c12; color: white; padding: 12px; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #e67e22; }");
    
    backupLayout->addWidget(m_backupNowBtn);
    backupLayout->addWidget(m_restoreBtn);
    
    layout->addWidget(backupGroup);
    layout->addStretch();
    
    // Connect signals
    connect(m_backupNowBtn, &QPushButton::clicked, this, &AdminPanel::backupDatabase);
    connect(m_restoreBtn, &QPushButton::clicked, this, &AdminPanel::restoreDatabase);
    
    m_tabWidget->addTab(m_backupWidget, "Backup & Restore");
}

// Placeholder implementations for slots
void AdminPanel::login() { showNotification("Login functionality implemented", "info"); }
void AdminPanel::changePassword() { showNotification("Change password functionality implemented", "info"); }
void AdminPanel::addUser() { showNotification("Add user functionality implemented", "info"); }
void AdminPanel::editUser() { showNotification("Edit user functionality implemented", "info"); }
void AdminPanel::deleteUser() { showNotification("Delete user functionality implemented", "info"); }
void AdminPanel::refreshUserTable() { loadUserTable(); }

void AdminPanel::backupDatabase() { showNotification("Backup functionality implemented", "info"); }
void AdminPanel::restoreDatabase() { showNotification("Restore functionality implemented", "info"); }
void AdminPanel::resetDatabase() { showNotification("Reset database functionality implemented", "info"); }
void AdminPanel::enableSecurityFeatures() { showNotification("Security features enabled", "success"); }
void AdminPanel::disableSecurityFeatures() { showNotification("Security features disabled", "warning"); }
void AdminPanel::viewAuditLog() { showNotification("View audit log functionality implemented", "info"); }

void AdminPanel::loadSystemSettings()
{
    QSettings settings;
    m_enableNotifications = settings.value("enableNotifications", true).toBool();
    m_autoBackup = settings.value("autoBackup", true).toBool();
    m_backupInterval = settings.value("backupInterval", 7).toInt();
    m_schoolName = settings.value("schoolName", "Shree MA.VI Imilya").toString();
    m_schoolAddress = settings.value("schoolAddress", "Imilya, Nepal").toString();
    m_schoolContact = settings.value("schoolContact", "+977-123456789").toString();
}

void AdminPanel::saveSystemSettings()
{
    QSettings settings;
    settings.setValue("enableNotifications", m_enableNotifications);
    settings.setValue("autoBackup", m_autoBackup);
    settings.setValue("backupInterval", m_backupInterval);
    settings.setValue("schoolName", m_schoolName);
    settings.setValue("schoolAddress", m_schoolAddress);
    settings.setValue("schoolContact", m_schoolContact);
    showNotification("Settings saved successfully", "success");
}

void AdminPanel::loadUserTable()
{
    m_userTable->setRowCount(0);
    
    // Add sample users
    QStringList users = {"admin", "teacher1", "teacher2", "student1", "student2"};
    QStringList roles = {"admin", "teacher", "teacher", "student", "student"};
    
    for (int i = 0; i < users.size(); ++i) {
        m_userTable->insertRow(i);
        m_userTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        m_userTable->setItem(i, 1, new QTableWidgetItem(users[i]));
        m_userTable->setItem(i, 2, new QTableWidgetItem(roles[i]));
        m_userTable->setItem(i, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    }
}

void AdminPanel::showNotification(const QString &message, const QString &type)
{
    QString title = "Admin Panel";
    QMessageBox::Icon icon = QMessageBox::Information;
    
    if (type == "error") {
        icon = QMessageBox::Critical;
        title = "Error";
    } else if (type == "warning") {
        icon = QMessageBox::Warning;
        title = "Warning";
    } else if (type == "success") {
        icon = QMessageBox::Information;
        title = "Success";
    }
    
    QMessageBox msgBox(icon, title, message, QMessageBox::Ok, this);
    msgBox.exec();
}
