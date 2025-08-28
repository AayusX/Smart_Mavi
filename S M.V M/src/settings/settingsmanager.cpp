#include "settings/settingsmanager.h"
#include "database/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QCryptographicHash>

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
    , m_settings(new QSettings("Tech07", "SmartMAVIManager", this))
{
    loadSettings();
}

SettingsManager::~SettingsManager()
{
    saveSettings();
}

void SettingsManager::loadSettings()
{
    // Load general settings
    m_generalSettings.schoolName = m_settings->value("general/school_name", "Shree MA.VI Imilya").toString();
    m_generalSettings.schoolAddress = m_settings->value("general/school_address", "").toString();
    m_generalSettings.schoolPhone = m_settings->value("general/school_phone", "").toString();
    m_generalSettings.schoolEmail = m_settings->value("general/school_email", "").toString();
    m_generalSettings.academicYear = m_settings->value("general/academic_year", "2024-2025").toString();
    m_generalSettings.schoolCode = m_settings->value("general/school_code", "MAVI001").toString();
    m_generalSettings.principalName = m_settings->value("general/principal_name", "").toString();
    m_generalSettings.establishedYear = m_settings->value("general/established_year", 2020).toInt();
    
    // Load UI settings
    m_uiSettings.theme = m_settings->value("ui/theme", "modern").toString();
    m_uiSettings.language = m_settings->value("ui/language", "en").toString();
    m_uiSettings.fontSize = m_settings->value("ui/font_size", 10).toInt();
    m_uiSettings.showAnimations = m_settings->value("ui/show_animations", true).toBool();
    m_uiSettings.autoSave = m_settings->value("ui/auto_save", true).toBool();
    m_uiSettings.confirmDeletion = m_settings->value("ui/confirm_deletion", true).toBool();
    m_uiSettings.showWelcomeScreen = m_settings->value("ui/show_welcome_screen", true).toBool();
    
    // Load database settings
    m_dbSettings.dbPath = m_settings->value("database/db_path", "").toString();
    m_dbSettings.autoBackup = m_settings->value("database/auto_backup", true).toBool();
    m_dbSettings.backupInterval = m_settings->value("database/backup_interval", 24).toInt();
    m_dbSettings.maxBackups = m_settings->value("database/max_backups", 10).toInt();
    m_dbSettings.backupLocation = m_settings->value("database/backup_location", "").toString();
    m_dbSettings.encryptBackups = m_settings->value("database/encrypt_backups", false).toBool();
    m_dbSettings.compressionLevel = m_settings->value("database/compression_level", 6).toInt();
    
    // Load security settings
    m_securitySettings.passwordPolicy = m_settings->value("security/password_policy", "medium").toString();
    m_securitySettings.sessionTimeout = m_settings->value("security/session_timeout", 30).toInt();
    m_securitySettings.maxLoginAttempts = m_settings->value("security/max_login_attempts", 3).toInt();
    m_securitySettings.enableTwoFactor = m_settings->value("security/enable_two_factor", false).toBool();
    m_securitySettings.auditLogging = m_settings->value("security/audit_logging", true).toBool();
    m_securitySettings.encryptSensitiveData = m_settings->value("security/encrypt_sensitive_data", false).toBool();
    
    // Load notification settings
    m_notificationSettings.enableEmailNotifications = m_settings->value("notifications/enable_email", true).toBool();
    m_notificationSettings.enableSmsNotifications = m_settings->value("notifications/enable_sms", false).toBool();
    m_notificationSettings.attendanceAlerts = m_settings->value("notifications/attendance_alerts", true).toBool();
    m_notificationSettings.feeReminders = m_settings->value("notifications/fee_reminders", true).toBool();
    m_notificationSettings.examNotifications = m_settings->value("notifications/exam_notifications", true).toBool();
    m_notificationSettings.emergencyAlerts = m_settings->value("notifications/emergency_alerts", true).toBool();
    m_notificationSettings.parentPortalNotifications = m_settings->value("notifications/parent_portal", false).toBool();
    
    // Load system settings
    m_systemSettings.maxConcurrentUsers = m_settings->value("system/max_concurrent_users", 50).toInt();
    m_systemSettings.cacheSize = m_settings->value("system/cache_size", 100).toInt();
    m_systemSettings.logLevel = m_settings->value("system/log_level", "Info").toString();
    m_systemSettings.enableDebugMode = m_settings->value("system/enable_debug", false).toBool();
    m_systemSettings.autoUpdate = m_settings->value("system/auto_update", false).toBool();
    m_systemSettings.updateCheckInterval = m_settings->value("system/update_check_interval", 7).toInt();
    m_systemSettings.enableCrashReporting = m_settings->value("system/enable_crash_reporting", true).toBool();
}

void SettingsManager::saveSettings()
{
    // Save general settings
    m_settings->setValue("general/school_name", m_generalSettings.schoolName);
    m_settings->setValue("general/school_address", m_generalSettings.schoolAddress);
    m_settings->setValue("general/school_phone", m_generalSettings.schoolPhone);
    m_settings->setValue("general/school_email", m_generalSettings.schoolEmail);
    m_settings->setValue("general/academic_year", m_generalSettings.academicYear);
    m_settings->setValue("general/school_code", m_generalSettings.schoolCode);
    m_settings->setValue("general/principal_name", m_generalSettings.principalName);
    m_settings->setValue("general/established_year", m_generalSettings.establishedYear);
    
    // Save UI settings
    m_settings->setValue("ui/theme", m_uiSettings.theme);
    m_settings->setValue("ui/language", m_uiSettings.language);
    m_settings->setValue("ui/font_size", m_uiSettings.fontSize);
    m_settings->setValue("ui/show_animations", m_uiSettings.showAnimations);
    m_settings->setValue("ui/auto_save", m_uiSettings.autoSave);
    m_settings->setValue("ui/confirm_deletion", m_uiSettings.confirmDeletion);
    m_settings->setValue("ui/show_welcome_screen", m_uiSettings.showWelcomeScreen);
    
    // Save database settings
    m_settings->setValue("database/db_path", m_dbSettings.dbPath);
    m_settings->setValue("database/auto_backup", m_dbSettings.autoBackup);
    m_settings->setValue("database/backup_interval", m_dbSettings.backupInterval);
    m_settings->setValue("database/max_backups", m_dbSettings.maxBackups);
    m_settings->setValue("database/backup_location", m_dbSettings.backupLocation);
    m_settings->setValue("database/encrypt_backups", m_dbSettings.encryptBackups);
    m_settings->setValue("database/compression_level", m_dbSettings.compressionLevel);
    
    // Save security settings
    m_settings->setValue("security/password_policy", m_securitySettings.passwordPolicy);
    m_settings->setValue("security/session_timeout", m_securitySettings.sessionTimeout);
    m_settings->setValue("security/max_login_attempts", m_securitySettings.maxLoginAttempts);
    m_settings->setValue("security/enable_two_factor", m_securitySettings.enableTwoFactor);
    m_settings->setValue("security/audit_logging", m_securitySettings.auditLogging);
    m_settings->setValue("security/encrypt_sensitive_data", m_securitySettings.encryptSensitiveData);
    
    // Save notification settings
    m_settings->setValue("notifications/enable_email", m_notificationSettings.enableEmailNotifications);
    m_settings->setValue("notifications/enable_sms", m_notificationSettings.enableSmsNotifications);
    m_settings->setValue("notifications/attendance_alerts", m_notificationSettings.attendanceAlerts);
    m_settings->setValue("notifications/fee_reminders", m_notificationSettings.feeReminders);
    m_settings->setValue("notifications/exam_notifications", m_notificationSettings.examNotifications);
    m_settings->setValue("notifications/emergency_alerts", m_notificationSettings.emergencyAlerts);
    m_settings->setValue("notifications/parent_portal", m_notificationSettings.parentPortalNotifications);
    
    // Save system settings
    m_settings->setValue("system/max_concurrent_users", m_systemSettings.maxConcurrentUsers);
    m_settings->setValue("system/cache_size", m_systemSettings.cacheSize);
    m_settings->setValue("system/log_level", m_systemSettings.logLevel);
    m_settings->setValue("system/enable_debug", m_systemSettings.enableDebugMode);
    m_settings->setValue("system/auto_update", m_systemSettings.autoUpdate);
    m_settings->setValue("system/update_check_interval", m_systemSettings.updateCheckInterval);
    m_settings->setValue("system/enable_crash_reporting", m_systemSettings.enableCrashReporting);
    
    m_settings->sync();
}

GeneralSettings SettingsManager::getGeneralSettings() const
{
    return m_generalSettings;
}

void SettingsManager::setGeneralSettings(const GeneralSettings &settings)
{
    m_generalSettings = settings;
    saveSettings();
    emit settingsChanged("general");
}

UISettings SettingsManager::getUISettings() const
{
    return m_uiSettings;
}

void SettingsManager::setUISettings(const UISettings &settings)
{
    m_uiSettings = settings;
    saveSettings();
    emit settingsChanged("ui");
    emit themeChanged(settings.theme);
}

DatabaseSettings SettingsManager::getDatabaseSettings() const
{
    return m_dbSettings;
}

void SettingsManager::setDatabaseSettings(const DatabaseSettings &settings)
{
    m_dbSettings = settings;
    saveSettings();
    emit settingsChanged("database");
}

SecuritySettings SettingsManager::getSecuritySettings() const
{
    return m_securitySettings;
}

void SettingsManager::setSecuritySettings(const SecuritySettings &settings)
{
    m_securitySettings = settings;
    saveSettings();
    emit settingsChanged("security");
}

NotificationSettings SettingsManager::getNotificationSettings() const
{
    return m_notificationSettings;
}

void SettingsManager::setNotificationSettings(const NotificationSettings &settings)
{
    m_notificationSettings = settings;
    saveSettings();
    emit settingsChanged("notifications");
}

SystemSettings SettingsManager::getSystemSettings() const
{
    return m_systemSettings;
}

void SettingsManager::setSystemSettings(const SystemSettings &settings)
{
    m_systemSettings = settings;
    saveSettings();
    emit settingsChanged("system");
}

bool SettingsManager::exportSettings(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QJsonObject exportObj;
    
    // Export general settings
    QJsonObject generalObj;
    generalObj["school_name"] = m_generalSettings.schoolName;
    generalObj["school_address"] = m_generalSettings.schoolAddress;
    generalObj["school_phone"] = m_generalSettings.schoolPhone;
    generalObj["school_email"] = m_generalSettings.schoolEmail;
    generalObj["academic_year"] = m_generalSettings.academicYear;
    generalObj["school_code"] = m_generalSettings.schoolCode;
    generalObj["principal_name"] = m_generalSettings.principalName;
    generalObj["established_year"] = m_generalSettings.establishedYear;
    exportObj["general"] = generalObj;
    
    // Export UI settings
    QJsonObject uiObj;
    uiObj["theme"] = m_uiSettings.theme;
    uiObj["language"] = m_uiSettings.language;
    uiObj["font_size"] = m_uiSettings.fontSize;
    uiObj["show_animations"] = m_uiSettings.showAnimations;
    uiObj["auto_save"] = m_uiSettings.autoSave;
    uiObj["confirm_deletion"] = m_uiSettings.confirmDeletion;
    uiObj["show_welcome_screen"] = m_uiSettings.showWelcomeScreen;
    exportObj["ui"] = uiObj;
    
    // Export notification settings
    QJsonObject notifObj;
    notifObj["enable_email"] = m_notificationSettings.enableEmailNotifications;
    notifObj["enable_sms"] = m_notificationSettings.enableSmsNotifications;
    notifObj["attendance_alerts"] = m_notificationSettings.attendanceAlerts;
    notifObj["fee_reminders"] = m_notificationSettings.feeReminders;
    notifObj["exam_notifications"] = m_notificationSettings.examNotifications;
    notifObj["emergency_alerts"] = m_notificationSettings.emergencyAlerts;
    notifObj["parent_portal"] = m_notificationSettings.parentPortalNotifications;
    exportObj["notifications"] = notifObj;
    
    QJsonDocument doc(exportObj);
    QTextStream out(&file);
    out << doc.toJson();
    file.close();
    
    return true;
}

bool SettingsManager::importSettings(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        return false;
    }
    
    QJsonObject importObj = doc.object();
    
    // Import general settings
    if (importObj.contains("general")) {
        QJsonObject generalObj = importObj["general"].toObject();
        m_generalSettings.schoolName = generalObj["school_name"].toString();
        m_generalSettings.schoolAddress = generalObj["school_address"].toString();
        m_generalSettings.schoolPhone = generalObj["school_phone"].toString();
        m_generalSettings.schoolEmail = generalObj["school_email"].toString();
        m_generalSettings.academicYear = generalObj["academic_year"].toString();
        m_generalSettings.schoolCode = generalObj["school_code"].toString();
        m_generalSettings.principalName = generalObj["principal_name"].toString();
        m_generalSettings.establishedYear = generalObj["established_year"].toInt();
    }
    
    // Import UI settings
    if (importObj.contains("ui")) {
        QJsonObject uiObj = importObj["ui"].toObject();
        m_uiSettings.theme = uiObj["theme"].toString();
        m_uiSettings.language = uiObj["language"].toString();
        m_uiSettings.fontSize = uiObj["font_size"].toInt();
        m_uiSettings.showAnimations = uiObj["show_animations"].toBool();
        m_uiSettings.autoSave = uiObj["auto_save"].toBool();
        m_uiSettings.confirmDeletion = uiObj["confirm_deletion"].toBool();
        m_uiSettings.showWelcomeScreen = uiObj["show_welcome_screen"].toBool();
    }
    
    // Import notification settings
    if (importObj.contains("notifications")) {
        QJsonObject notifObj = importObj["notifications"].toObject();
        m_notificationSettings.enableEmailNotifications = notifObj["enable_email"].toBool();
        m_notificationSettings.enableSmsNotifications = notifObj["enable_sms"].toBool();
        m_notificationSettings.attendanceAlerts = notifObj["attendance_alerts"].toBool();
        m_notificationSettings.feeReminders = notifObj["fee_reminders"].toBool();
        m_notificationSettings.examNotifications = notifObj["exam_notifications"].toBool();
        m_notificationSettings.emergencyAlerts = notifObj["emergency_alerts"].toBool();
        m_notificationSettings.parentPortalNotifications = notifObj["parent_portal"].toBool();
    }
    
    saveSettings();
    emit settingsChanged("all");
    return true;
}

bool SettingsManager::resetToDefaults()
{
    m_settings->clear();
    
    // Reset to default values
    m_generalSettings = GeneralSettings();
    m_generalSettings.schoolName = "Shree MA.VI Imilya";
    m_generalSettings.academicYear = "2024-2025";
    m_generalSettings.schoolCode = "MAVI001";
    m_generalSettings.establishedYear = 2020;
    
    m_uiSettings = UISettings();
    m_uiSettings.theme = "modern";
    m_uiSettings.language = "en";
    m_uiSettings.fontSize = 10;
    m_uiSettings.showAnimations = true;
    m_uiSettings.autoSave = true;
    m_uiSettings.confirmDeletion = true;
    m_uiSettings.showWelcomeScreen = true;
    
    m_dbSettings = DatabaseSettings();
    m_dbSettings.autoBackup = true;
    m_dbSettings.backupInterval = 24;
    m_dbSettings.maxBackups = 10;
    m_dbSettings.compressionLevel = 6;
    
    m_securitySettings = SecuritySettings();
    m_securitySettings.passwordPolicy = "medium";
    m_securitySettings.sessionTimeout = 30;
    m_securitySettings.maxLoginAttempts = 3;
    m_securitySettings.auditLogging = true;
    
    m_notificationSettings = NotificationSettings();
    m_notificationSettings.enableEmailNotifications = true;
    m_notificationSettings.attendanceAlerts = true;
    m_notificationSettings.feeReminders = true;
    m_notificationSettings.examNotifications = true;
    m_notificationSettings.emergencyAlerts = true;
    
    m_systemSettings = SystemSettings();
    m_systemSettings.maxConcurrentUsers = 50;
    m_systemSettings.cacheSize = 100;
    m_systemSettings.logLevel = "Info";
    m_systemSettings.updateCheckInterval = 7;
    m_systemSettings.enableCrashReporting = true;
    
    saveSettings();
    emit settingsChanged("all");
    return true;
}

bool SettingsManager::backupDatabase()
{
    if (m_dbSettings.backupLocation.isEmpty()) {
        QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        m_dbSettings.backupLocation = QDir(documentsPath).filePath("SmartMAVIManager/Backups");
    }
    
    QDir backupDir(m_dbSettings.backupLocation);
    if (!backupDir.exists()) {
        backupDir.mkpath(".");
    }
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString backupFileName = QString("backup_%1.db").arg(timestamp);
    QString backupPath = backupDir.filePath(backupFileName);
    
    // Copy database file
    QFile::copy(Database::instance().databasePath(), backupPath);
    
    // Clean old backups if needed
    cleanOldBackups();
    
    // Log backup
    QSqlQuery query(Database::instance().database());
    query.prepare("INSERT INTO system_backups (backup_name, backup_path, backup_size, "
                 "backup_date, backup_type, status) VALUES (?, ?, ?, ?, ?, ?)");
    
    QFileInfo backupInfo(backupPath);
    query.addBindValue(backupFileName);
    query.addBindValue(backupPath);
    query.addBindValue(backupInfo.size());
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue("Auto");
    query.addBindValue("Completed");
    
    if (!query.exec()) {
        qDebug() << "Failed to log backup:" << query.lastError().text();
    }
    
    emit backupCompleted(backupPath);
    return true;
}

bool SettingsManager::restoreDatabase(const QString &backupPath)
{
    if (!QFile::exists(backupPath)) {
        return false;
    }
    
    // Close current database connection
    Database::instance().closeDatabase();
    
    // Replace current database with backup
    QString currentDbPath = Database::instance().databasePath();
    QFile::remove(currentDbPath + ".backup");
    QFile::copy(currentDbPath, currentDbPath + ".backup"); // Create safety backup
    QFile::remove(currentDbPath);
    
    bool success = QFile::copy(backupPath, currentDbPath);
    
    // Reopen database
    Database::instance().initialize();
    
    if (success) {
        emit databaseRestored(backupPath);
    }
    
    return success;
}

QList<BackupInfo> SettingsManager::getAvailableBackups()
{
    QList<BackupInfo> backups;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM system_backups WHERE status = 'Completed' "
                  "ORDER BY backup_date DESC")) {
        while (query.next()) {
            BackupInfo backup;
            backup.id = query.value("id").toInt();
            backup.backupName = query.value("backup_name").toString();
            backup.backupPath = query.value("backup_path").toString();
            backup.backupSize = query.value("backup_size").toLongLong();
            backup.backupDate = query.value("backup_date").toDateTime();
            backup.backupType = query.value("backup_type").toString();
            backup.status = query.value("status").toString();
            backups.append(backup);
        }
    }
    
    return backups;
}

bool SettingsManager::addUserPreference(const QString &key, const QVariant &value, const QString &userId)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT OR REPLACE INTO user_preferences (user_id, preference_key, "
                 "preference_value, updated_date) VALUES (?, ?, ?, ?)");
    
    query.addBindValue(userId);
    query.addBindValue(key);
    query.addBindValue(value.toString());
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Failed to add user preference:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QVariant SettingsManager::getUserPreference(const QString &key, const QString &userId, const QVariant &defaultValue)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT preference_value FROM user_preferences "
                 "WHERE user_id = ? AND preference_key = ?");
    
    query.addBindValue(userId);
    query.addBindValue(key);
    
    if (query.exec() && query.next()) {
        return query.value("preference_value");
    }
    
    return defaultValue;
}

bool SettingsManager::validatePassword(const QString &password)
{
    if (m_securitySettings.passwordPolicy == "weak") {
        return password.length() >= 4;
    } else if (m_securitySettings.passwordPolicy == "medium") {
        return password.length() >= 8 && 
               password.contains(QRegularExpression("[a-z]")) &&
               password.contains(QRegularExpression("[A-Z]")) &&
               password.contains(QRegularExpression("[0-9]"));
    } else if (m_securitySettings.passwordPolicy == "strong") {
        return password.length() >= 12 && 
               password.contains(QRegularExpression("[a-z]")) &&
               password.contains(QRegularExpression("[A-Z]")) &&
               password.contains(QRegularExpression("[0-9]")) &&
               password.contains(QRegularExpression("[!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>\\/?]"));
    }
    
    return false;
}

QString SettingsManager::hashPassword(const QString &password)
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(password.toUtf8());
    return hash.result().toHex();
}

bool SettingsManager::logAuditEvent(const QString &event, const QString &details, const QString &userId)
{
    if (!m_securitySettings.auditLogging) {
        return true; // Audit logging is disabled
    }
    
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO audit_logs (user_id, event_type, event_details, "
                 "event_timestamp, ip_address) VALUES (?, ?, ?, ?, ?)");
    
    query.addBindValue(userId);
    query.addBindValue(event);
    query.addBindValue(details);
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue("127.0.0.1"); // Local IP for desktop app
    
    if (!query.exec()) {
        qDebug() << "Failed to log audit event:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<AuditLog> SettingsManager::getAuditLogs(int limit)
{
    QList<AuditLog> logs;
    QSqlQuery query(Database::instance().database());
    
    QString queryStr = "SELECT * FROM audit_logs ORDER BY event_timestamp DESC";
    if (limit > 0) {
        queryStr += QString(" LIMIT %1").arg(limit);
    }
    
    if (query.exec(queryStr)) {
        while (query.next()) {
            AuditLog log;
            log.id = query.value("id").toInt();
            log.userId = query.value("user_id").toString();
            log.eventType = query.value("event_type").toString();
            log.eventDetails = query.value("event_details").toString();
            log.eventTimestamp = query.value("event_timestamp").toDateTime();
            log.ipAddress = query.value("ip_address").toString();
            logs.append(log);
        }
    }
    
    return logs;
}

bool SettingsManager::updateSystemConfiguration(const QString &key, const QVariant &value)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT OR REPLACE INTO system_config (config_key, config_value, "
                 "updated_date, updated_by) VALUES (?, ?, ?, ?)");
    
    query.addBindValue(key);
    query.addBindValue(value.toString());
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue("admin"); // Default admin user
    
    if (!query.exec()) {
        qDebug() << "Failed to update system configuration:" << query.lastError().text();
        return false;
    }
    
    emit configurationChanged(key, value);
    return true;
}

QVariant SettingsManager::getSystemConfiguration(const QString &key, const QVariant &defaultValue)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT config_value FROM system_config WHERE config_key = ?");
    query.addBindValue(key);
    
    if (query.exec() && query.next()) {
        return query.value("config_value");
    }
    
    return defaultValue;
}

void SettingsManager::cleanOldBackups()
{
    QDir backupDir(m_dbSettings.backupLocation);
    QStringList backupFiles = backupDir.entryList(QStringList() << "backup_*.db", 
                                                 QDir::Files, QDir::Time);
    
    // Remove old backups if we exceed the maximum
    if (backupFiles.size() > m_dbSettings.maxBackups) {
        for (int i = m_dbSettings.maxBackups; i < backupFiles.size(); ++i) {
            QString filePath = backupDir.filePath(backupFiles[i]);
            QFile::remove(filePath);
            
            // Remove from database log
            QSqlQuery query(Database::instance().database());
            query.prepare("DELETE FROM system_backups WHERE backup_name = ?");
            query.addBindValue(backupFiles[i]);
            query.exec();
        }
    }
}

bool SettingsManager::createDatabaseTables()
{
    QSqlQuery query(Database::instance().database());
    
    // Create system backups table
    QString createBackupsTable = R"(
        CREATE TABLE IF NOT EXISTS system_backups (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            backup_name TEXT NOT NULL,
            backup_path TEXT NOT NULL,
            backup_size INTEGER,
            backup_date TIMESTAMP NOT NULL,
            backup_type TEXT DEFAULT 'Manual',
            status TEXT DEFAULT 'Pending',
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createBackupsTable)) {
        qDebug() << "Failed to create system_backups table:" << query.lastError().text();
        return false;
    }
    
    // Create user preferences table
    QString createPreferencesTable = R"(
        CREATE TABLE IF NOT EXISTS user_preferences (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id TEXT NOT NULL,
            preference_key TEXT NOT NULL,
            preference_value TEXT,
            updated_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            UNIQUE(user_id, preference_key)
        )
    )";
    
    if (!query.exec(createPreferencesTable)) {
        qDebug() << "Failed to create user_preferences table:" << query.lastError().text();
        return false;
    }
    
    // Create audit logs table
    QString createAuditTable = R"(
        CREATE TABLE IF NOT EXISTS audit_logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id TEXT,
            event_type TEXT NOT NULL,
            event_details TEXT,
            event_timestamp TIMESTAMP NOT NULL,
            ip_address TEXT,
            session_id TEXT
        )
    )";
    
    if (!query.exec(createAuditTable)) {
        qDebug() << "Failed to create audit_logs table:" << query.lastError().text();
        return false;
    }
    
    // Create system config table
    QString createConfigTable = R"(
        CREATE TABLE IF NOT EXISTS system_config (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            config_key TEXT UNIQUE NOT NULL,
            config_value TEXT,
            config_type TEXT DEFAULT 'string',
            description TEXT,
            updated_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            updated_by TEXT
        )
    )";
    
    if (!query.exec(createConfigTable)) {
        qDebug() << "Failed to create system_config table:" << query.lastError().text();
        return false;
    }
    
    // Create user sessions table
    QString createSessionsTable = R"(
        CREATE TABLE IF NOT EXISTS user_sessions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id TEXT NOT NULL,
            session_id TEXT UNIQUE NOT NULL,
            login_time TIMESTAMP NOT NULL,
            last_activity TIMESTAMP NOT NULL,
            ip_address TEXT,
            user_agent TEXT,
            status TEXT DEFAULT 'Active'
        )
    )";
    
    if (!query.exec(createSessionsTable)) {
        qDebug() << "Failed to create user_sessions table:" << query.lastError().text();
        return false;
    }
    
    return true;
}
