#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QWidget>
#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLocale>
#include <QTranslator>
#include <QDialog>
#include <QTabWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QProgressBar>
#include <QLineEdit>
#include <QGroupBox>
#include <QSlider>
#include <QTableWidget>
#include <QGridLayout>
#include <QPixmap>
#include <QColor>
#include <QSize>
#include <QPoint>
#include <QTime>
#include <QTimer>
#include <QFileInfoList>

class Database;

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager();

    // Theme management
    void setTheme(const QString &themeName);
    QString getCurrentTheme() const { return m_currentTheme; }
    QStringList getAvailableThemes() const;
    void createCustomTheme(const QString &name, const QString &cssContent);
    void deleteCustomTheme(const QString &name);
    bool isCustomTheme(const QString &name) const;

    // Language support
    void setLanguage(const QString &languageCode);
    QString getCurrentLanguage() const { return m_currentLanguage; }
    QStringList getAvailableLanguages() const;
    void loadTranslations();
    QString translate(const QString &key, const QString &context = "") const;

    // School branding
    void setSchoolLogo(const QPixmap &logo);
    QPixmap getSchoolLogo() const { return m_schoolLogo; }
    void setSchoolColors(const QColor &primary, const QColor &secondary);
    QColor getPrimaryColor() const { return m_primaryColor; }
    QColor getSecondaryColor() const { return m_secondaryColor; }
    void setSchoolName(const QString &name);
    QString getSchoolName() const { return m_schoolName; }

    // UI preferences
    void setWindowSize(const QSize &size);
    QSize getWindowSize() const { return m_windowSize; }
    void setWindowPosition(const QPoint &position);
    QPoint getWindowPosition() const { return m_windowPosition; }
    void setMaximized(bool maximized) { m_isMaximized = maximized; }
    bool isMaximized() const { return m_isMaximized; }

    // Application preferences
    void setAutoSave(bool enabled) { m_autoSave = enabled; }
    bool isAutoSaveEnabled() const { return m_autoSave; }
    void setAutoSaveInterval(int minutes) { m_autoSaveInterval = minutes; }
    int getAutoSaveInterval() const { return m_autoSaveInterval; }

    void setStartupScreen(const QString &screen) { m_startupScreen = screen; }
    QString getStartupScreen() const { return m_startupScreen; }

    void setAnimationsEnabled(bool enabled) { m_animationsEnabled = enabled; }
    bool areAnimationsEnabled() const { return m_animationsEnabled; }

    void setSoundEnabled(bool enabled) { m_soundEnabled = enabled; }
    bool isSoundEnabled() const { return m_soundEnabled; }

    // Data preferences
    void setDateFormat(const QString &format) { m_dateFormat = format; }
    QString getDateFormat() const { return m_dateFormat; }
    void setTimeFormat(const QString &format) { m_timeFormat = format; }
    QString getTimeFormat() const { return m_timeFormat; }
    void setNumberFormat(const QString &format) { m_numberFormat = format; }
    QString getNumberFormat() const { return m_numberFormat; }

    // Backup settings
    void setAutoBackup(bool enabled) { m_autoBackup = enabled; }
    bool isAutoBackupEnabled() const { return m_autoBackup; }
    void setBackupInterval(int days) { m_backupInterval = days; }
    int getBackupInterval() const { return m_backupInterval; }
    void setBackupLocation(const QString &path) { m_backupLocation = path; }
    QString getBackupLocation() const { return m_backupLocation; }
    void setBackupCompression(bool enabled) { m_backupCompression = enabled; }
    bool isBackupCompressionEnabled() const { return m_backupCompression; }

    // Security settings
    void setSessionTimeout(int minutes) { m_sessionTimeout = minutes; }
    int getSessionTimeout() const { return m_sessionTimeout; }
    void setPasswordPolicy(const QJsonObject &policy) { m_passwordPolicy = policy; }
    QJsonObject getPasswordPolicy() const { return m_passwordPolicy; }
    void setTwoFactorEnabled(bool enabled) { m_twoFactorEnabled = enabled; }
    bool isTwoFactorEnabled() const { return m_twoFactorEnabled; }

    // Notification settings
    void setDesktopNotifications(bool enabled) { m_desktopNotifications = enabled; }
    bool areDesktopNotificationsEnabled() const { return m_desktopNotifications; }
    void setEmailNotifications(bool enabled) { m_emailNotifications = enabled; }
    bool areEmailNotificationsEnabled() const { return m_emailNotifications; }
    void setSMSNotifications(bool enabled) { m_smsNotifications = enabled; }
    bool areSMSNotificationsEnabled() const { return m_smsNotifications; }

    // System monitoring
    void setSystemMonitoring(bool enabled) { m_systemMonitoring = enabled; }
    bool isSystemMonitoringEnabled() const { return m_systemMonitoring; }
    void setPerformanceLogging(bool enabled) { m_performanceLogging = enabled; }
    bool isPerformanceLoggingEnabled() const { return m_performanceLogging; }

    // Data management
    void exportSettings(const QString &filename);
    void importSettings(const QString &filename);
    void resetToDefaults();
    void validateSettings();

    // Apply settings
    void applyTheme();
    void applyLanguage();
    void applyBranding();
    void applyAllSettings();

public slots:
    void saveSettings();
    void loadSettings();
    void reloadSettings();

signals:
    void themeChanged(const QString &theme);
    void languageChanged(const QString &language);
    void brandingChanged();
    void settingsChanged();
    void settingsReset();

private:
    void initializeDefaults();
    void createDefaultThemes();
    void createLanguageFiles();
    void setupDirectories();
    
    QSettings *m_settings;
    QTranslator *m_translator;
    
    // Theme system
    QString m_currentTheme;
    QMap<QString, QString> m_themes; // name -> css file path
    QString m_customThemeDir;
    
    // Language system
    QString m_currentLanguage;
    QMap<QString, QString> m_languages; // code -> name
    QString m_translationDir;
    
    // Branding
    QPixmap m_schoolLogo;
    QColor m_primaryColor;
    QColor m_secondaryColor;
    QString m_schoolName;
    
    // Window state
    QSize m_windowSize;
    QPoint m_windowPosition;
    bool m_isMaximized;
    
    // Application preferences
    bool m_autoSave;
    int m_autoSaveInterval;
    QString m_startupScreen;
    bool m_animationsEnabled;
    bool m_soundEnabled;
    
    // Format settings
    QString m_dateFormat;
    QString m_timeFormat;
    QString m_numberFormat;
    
    // Backup settings
    bool m_autoBackup;
    int m_backupInterval;
    QString m_backupLocation;
    bool m_backupCompression;
    
    // Security settings
    int m_sessionTimeout;
    QJsonObject m_passwordPolicy;
    bool m_twoFactorEnabled;
    
    // Notification settings
    bool m_desktopNotifications;
    bool m_emailNotifications;
    bool m_smsNotifications;
    
    // System monitoring
    bool m_systemMonitoring;
    bool m_performanceLogging;
};

// Settings Dialog
class SettingsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDialog(SettingsManager *manager, QWidget *parent = nullptr);

private slots:
    void saveAllSettings();
    void resetAllSettings();
    void applySettings();
    void importSettings();
    void exportSettings();
    
    // Theme settings
    void onThemeChanged();
    void createCustomTheme();
    void editCustomTheme();
    void deleteCustomTheme();
    void previewTheme();
    
    // Language settings
    void onLanguageChanged();
    void downloadLanguagePack();
    
    // Branding settings
    void selectSchoolLogo();
    void selectPrimaryColor();
    void selectSecondaryColor();
    void resetBranding();
    void previewBranding();
    
    // Advanced settings
    void configureBackup();
    void configureSecurity();
    void configureNotifications();
    void configureSystem();

private:
    void setupUI();
    void setupGeneralTab();
    void setupThemeTab();
    void setupLanguageTab();
    void setupBrandingTab();
    void setupDataTab();
    void setupSecurityTab();
    void setupNotificationTab();
    void setupAdvancedTab();
    
    void loadCurrentSettings();
    void updatePreview();
    void validateInput();
    
    SettingsManager *m_manager;
    
    QTabWidget *m_tabWidget;
    
    // General settings
    QWidget *m_generalTab;
    QCheckBox *m_autoSaveCheck;
    QSpinBox *m_autoSaveIntervalSpin;
    QComboBox *m_startupScreenCombo;
    QCheckBox *m_animationsCheck;
    QCheckBox *m_soundCheck;
    QComboBox *m_dateFormatCombo;
    QComboBox *m_timeFormatCombo;
    
    // Theme settings
    QWidget *m_themeTab;
    QComboBox *m_themeCombo;
    QListWidget *m_customThemesList;
    QPushButton *m_createThemeBtn;
    QPushButton *m_editThemeBtn;
    QPushButton *m_deleteThemeBtn;
    QTextEdit *m_themePreview;
    QPushButton *m_previewThemeBtn;
    
    // Language settings
    QWidget *m_languageTab;
    QComboBox *m_languageCombo;
    QListWidget *m_installedLanguages;
    QPushButton *m_downloadLanguageBtn;
    QProgressBar *m_languageProgress;
    
    // Branding settings
    QWidget *m_brandingTab;
    QLabel *m_logoPreview;
    QPushButton *m_selectLogoBtn;
    QPushButton *m_primaryColorBtn;
    QPushButton *m_secondaryColorBtn;
    QLineEdit *m_schoolNameEdit;
    QPushButton *m_resetBrandingBtn;
    QPushButton *m_previewBrandingBtn;
    
    // Data settings
    QWidget *m_dataTab;
    QCheckBox *m_autoBackupCheck;
    QSpinBox *m_backupIntervalSpin;
    QLineEdit *m_backupLocationEdit;
    QPushButton *m_selectBackupDirBtn;
    QCheckBox *m_backupCompressionCheck;
    QPushButton *m_backupNowBtn;
    QPushButton *m_restoreBtn;
    
    // Security settings
    QWidget *m_securityTab;
    QSpinBox *m_sessionTimeoutSpin;
    QCheckBox *m_twoFactorCheck;
    QGroupBox *m_passwordPolicyGroup;
    QSpinBox *m_minPasswordLengthSpin;
    QCheckBox *m_requireUppercaseCheck;
    QCheckBox *m_requireNumbersCheck;
    QCheckBox *m_requireSymbolsCheck;
    
    // Notification settings
    QWidget *m_notificationTab;
    QCheckBox *m_desktopNotificationsCheck;
    QCheckBox *m_emailNotificationsCheck;
    QCheckBox *m_smsNotificationsCheck;
    QComboBox *m_notificationSoundCombo;
    QSlider *m_notificationVolumeSlider;
    
    // Advanced settings
    QWidget *m_advancedTab;
    QCheckBox *m_systemMonitoringCheck;
    QCheckBox *m_performanceLoggingCheck;
    QCheckBox *m_debugModeCheck;
    QComboBox *m_logLevelCombo;
    QLineEdit *m_logFileLocationEdit;
    QPushButton *m_clearLogsBtn;
    QPushButton *m_exportLogsBtn;
};

// Theme Editor
class ThemeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeEditor(const QString &themeName = "", QWidget *parent = nullptr);

    QString getThemeName() const { return m_themeName; }
    QString getThemeContent() const;
    void setThemeContent(const QString &content);

signals:
    void themeCreated(const QString &name, const QString &content);
    void themeUpdated(const QString &name, const QString &content);

private slots:
    void saveTheme();
    void previewTheme();
    void resetTheme();
    void importTheme();
    void exportTheme();
    void loadPreset();

private:
    void setupUI();
    void setupEditor();
    void setupPreview();
    void setupActions();
    void setupColorPalette();
    void setupFontSelector();
    
    void updatePreview();
    void applyThemeToPreview();
    
    QString m_themeName;
    
    QTabWidget *m_tabWidget;
    QTextEdit *m_cssEditor;
    QWidget *m_previewWidget;
    
    // Color palette
    QGridLayout *m_colorPaletteLayout;
    QList<QPushButton*> m_colorButtons;
    QMap<QString, QColor> m_themeColors;
    
    // Font settings
    QComboBox *m_fontFamilyCombo;
    QSpinBox *m_fontSizeSpin;
    QCheckBox *m_fontBoldCheck;
    QCheckBox *m_fontItalicCheck;
    
    // Preview components
    QLabel *m_previewLabel;
    QPushButton *m_previewButton;
    QLineEdit *m_previewLineEdit;
    QTableWidget *m_previewTable;
    QTabWidget *m_previewTabs;
    
    // Actions
    QPushButton *m_saveBtn;
    QPushButton *m_previewBtn;
    QPushButton *m_resetBtn;
    QPushButton *m_importBtn;
    QPushButton *m_exportBtn;
    QComboBox *m_presetCombo;
    QPushButton *m_loadPresetBtn;
};

// Language Manager
class LanguageManager : public QObject
{
    Q_OBJECT

public:
    explicit LanguageManager(QObject *parent = nullptr);

    void addLanguage(const QString &code, const QString &name, const QString &translationFile);
    void removeLanguage(const QString &code);
    QStringList getAvailableLanguages() const;
    QString getLanguageName(const QString &code) const;
    
    bool loadTranslation(const QString &code);
    QString translate(const QString &key, const QString &context = "") const;
    
    void setFallbackLanguage(const QString &code) { m_fallbackLanguage = code; }
    QString getFallbackLanguage() const { return m_fallbackLanguage; }

signals:
    void languageChanged(const QString &code);
    void translationLoaded(const QString &code);

private:
    void initializeLanguages();
    void loadLanguageFile(const QString &filename);
    
    QMap<QString, QString> m_languages; // code -> name
    QMap<QString, QString> m_translationFiles; // code -> file path
    QMap<QString, QMap<QString, QString>> m_translations; // code -> (key -> translation)
    
    QString m_currentLanguage;
    QString m_fallbackLanguage;
    QTranslator *m_translator;
};

// Backup Manager
class BackupManager : public QObject
{
    Q_OBJECT

public:
    explicit BackupManager(Database *database, QObject *parent = nullptr);

    // Backup operations
    bool createBackup(const QString &filename = "", bool compress = true);
    bool restoreBackup(const QString &filename);
    bool verifyBackup(const QString &filename);
    
    // Scheduled backups
    void enableAutoBackup(bool enabled);
    void setBackupSchedule(int intervalDays, const QTime &time);
    void setBackupLocation(const QString &path);
    void setBackupRetention(int days); // Keep backups for X days
    
    // Backup management
    QStringList getAvailableBackups();
    QFileInfoList getBackupFiles();
    void deleteOldBackups();
    void cleanupBackups();
    
    qint64 getBackupSize(const QString &filename);
    QString getBackupInfo(const QString &filename);

signals:
    void backupCreated(const QString &filename, bool success);
    void backupRestored(bool success);
    void autoBackupCompleted(bool success);
    void backupProgress(int percentage);

private slots:
    void performScheduledBackup();
    void cleanupOldBackups();

private:
    void initializeBackupSystem();
    void setupScheduleTimer();
    QString generateBackupFilename();
    bool compressBackup(const QString &source, const QString &destination);
    bool extractBackup(const QString &source, const QString &destination);
    
    Database *m_database;
    QTimer *m_backupTimer;
    QTimer *m_cleanupTimer;
    
    bool m_autoBackupEnabled;
    int m_backupIntervalDays;
    QTime m_backupTime;
    QString m_backupLocation;
    int m_retentionDays;
    bool m_compressionEnabled;
};

// System Monitor
class SystemMonitor : public QObject
{
    Q_OBJECT

public:
    explicit SystemMonitor(QObject *parent = nullptr);

    void startMonitoring();
    void stopMonitoring();
    bool isMonitoring() const { return m_isMonitoring; }

    // Performance metrics
    double getCPUUsage() const { return m_cpuUsage; }
    double getMemoryUsage() const { return m_memoryUsage; }
    double getDiskUsage() const { return m_diskUsage; }
    int getDatabaseSize() const { return m_databaseSize; }
    int getActiveConnections() const { return m_activeConnections; }

    // System info
    QString getSystemInfo() const;
    QString getDatabaseInfo() const;
    QString getApplicationInfo() const;

signals:
    void performanceUpdated(double cpu, double memory, double disk);
    void highCPUUsage(double usage);
    void highMemoryUsage(double usage);
    void lowDiskSpace(double available);
    void databaseGrowth(int sizeMB);

private slots:
    void updatePerformanceMetrics();
    void checkSystemHealth();

private:
    void initializeMonitoring();
    double calculateCPUUsage();
    double calculateMemoryUsage();
    double calculateDiskUsage();
    void updateSystemMetrics();
    
    bool m_isMonitoring;
    QTimer *m_monitorTimer;
    
    // Performance data
    double m_cpuUsage;
    double m_memoryUsage;
    double m_diskUsage;
    int m_databaseSize;
    int m_activeConnections;
    
    // Thresholds
    double m_cpuThreshold;
    double m_memoryThreshold;
    double m_diskThreshold;
    
    // History for trend analysis
    QList<QPair<QDateTime, double>> m_cpuHistory;
    QList<QPair<QDateTime, double>> m_memoryHistory;
    QList<QPair<QDateTime, double>> m_diskHistory;
};

// About Dialog with System Information
class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(SettingsManager *manager, QWidget *parent = nullptr);

private slots:
    void showSystemInfo();
    void showLicense();
    void checkUpdates();
    void openWebsite();
    void sendFeedback();

private:
    void setupUI();
    void setupAboutTab();
    void setupSystemTab();
    void setupLicenseTab();
    void setupCreditsTab();
    
    SettingsManager *m_manager;
    QTabWidget *m_tabWidget;
    
    // About information
    QLabel *m_logoLabel;
    QLabel *m_nameLabel;
    QLabel *m_versionLabel;
    QLabel *m_descriptionLabel;
    QLabel *m_copyrightLabel;
    
    // System information
    QTextEdit *m_systemInfoEdit;
    QPushButton *m_updateSystemInfoBtn;
    
    // License
    QTextEdit *m_licenseEdit;
    
    // Credits
    QTextEdit *m_creditsEdit;
    
    // Actions
    QPushButton *m_checkUpdatesBtn;
    QPushButton *m_websiteBtn;
    QPushButton *m_feedbackBtn;
    QPushButton *m_closeBtn;
};

#endif // SETTINGSMANAGER_H
