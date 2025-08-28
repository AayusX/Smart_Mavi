#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QTableWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QTabWidget>

class Database;
class Teacher;
class Student;
class Class;

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(Database *database, QWidget *parent = nullptr);
    ~AdminPanel();

    bool authenticate(const QString &username, const QString &password);
    void logout();
    bool isAuthenticated() const { return m_isAuthenticated; }
    QString getCurrentUser() const { return m_currentUser; }
    QString getCurrentUserRole() const { return m_currentUserRole; }

private slots:
    // Authentication slots
    void login();
    void changePassword();
    
    // User management slots
    void addUser();
    void editUser();
    void deleteUser();
    void refreshUserTable();
    
    // System settings slots
    void saveSystemSettings();
    void backupDatabase();
    void restoreDatabase();
    void resetDatabase();
    
    // Security slots
    void enableSecurityFeatures();
    void disableSecurityFeatures();
    void viewAuditLog();

private:
    void setupUI();
    void setupAuthenticationTab();
    void setupUserManagementTab();
    void setupSystemSettingsTab();
    void setupSecurityTab();
    void setupBackupTab();
    
    void loadSystemSettings();
    void loadUserTable();
    void showNotification(const QString &message, const QString &type = "info");
    
    // UI Components
    QTabWidget *m_tabWidget;
    
    // Authentication tab
    QWidget *m_authWidget;
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_loginBtn;
    QPushButton *m_changePasswordBtn;
    QLabel *m_authStatusLabel;
    
    // User management tab
    QWidget *m_userWidget;
    QTableWidget *m_userTable;
    QPushButton *m_addUserBtn;
    QPushButton *m_editUserBtn;
    QPushButton *m_deleteUserBtn;
    QLineEdit *m_newUsernameEdit;
    QLineEdit *m_newPasswordEdit;
    QComboBox *m_newUserRoleCombo;
    
    // System settings tab
    QWidget *m_settingsWidget;
    QCheckBox *m_enableNotificationsCheckBox;
    QCheckBox *m_autoBackupCheckBox;
    QSpinBox *m_backupIntervalSpinBox;
    QLineEdit *m_schoolNameEdit;
    QLineEdit *m_schoolAddressEdit;
    QLineEdit *m_schoolContactEdit;
    QTextEdit *m_schoolDescriptionEdit;
    QPushButton *m_saveSettingsBtn;
    
    // Security tab
    QWidget *m_securityWidget;
    QCheckBox *m_enableAuditLogCheckBox;
    QCheckBox *m_requireStrongPasswordsCheckBox;
    QSpinBox *m_sessionTimeoutSpinBox;
    QCheckBox *m_enableTwoFactorCheckBox;
    QPushButton *m_enableSecurityBtn;
    QPushButton *m_disableSecurityBtn;
    QPushButton *m_viewAuditLogBtn;
    
    // Backup tab
    QWidget *m_backupWidget;
    QPushButton *m_backupNowBtn;
    QPushButton *m_restoreBtn;
    QPushButton *m_resetBtn;
    QTextEdit *m_backupLogEdit;
    QLabel *m_lastBackupLabel;
    
    // Data members
    Database *m_database;
    bool m_isAuthenticated;
    QString m_currentUser;
    QString m_currentUserRole;
    
    // Settings
    bool m_enableNotifications;
    bool m_autoBackup;
    int m_backupInterval;
    QString m_schoolName;
    QString m_schoolAddress;
    QString m_schoolContact;
    QString m_schoolDescription;
    bool m_enableAuditLog;
    bool m_requireStrongPasswords;
    int m_sessionTimeout;
    bool m_enableTwoFactor;
};

#endif // ADMINPANEL_H
