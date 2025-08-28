#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTimer>
#include <QQueue>
#include <QSettings>
#include <QDateTime>
#include <QDialog>
#include <QWidget>
#include <QTabWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QDateEdit>
#include <QTimeEdit>
#include <QStringList>
#include <QMap>
#include <QTime>

class Database;

struct EmailMessage {
    QString to;
    QString cc;
    QString bcc;
    QString subject;
    QString body;
    QString htmlBody;
    QStringList attachments;
    int priority; // 1=high, 2=normal, 3=low
    QDateTime scheduledTime;
    bool isScheduled;
    QString messageId;
    
    EmailMessage() : priority(2), isScheduled(false), scheduledTime(QDateTime::currentDateTime()) {}
};

struct SMSMessage {
    QString phoneNumber;
    QString message;
    QDateTime scheduledTime;
    bool isScheduled;
    QString messageId;
    
    SMSMessage() : isScheduled(false), scheduledTime(QDateTime::currentDateTime()) {}
};

struct NotificationMessage {
    QString title;
    QString message;
    QString type; // info, success, warning, error
    QString recipient; // user, admin, teacher, parent, student
    QDateTime timestamp;
    bool isRead;
    QString actionUrl;
    QString messageId;
    
    NotificationMessage() : timestamp(QDateTime::currentDateTime()), isRead(false) {}
};

class CommunicationManager : public QObject
{
    Q_OBJECT

public:
    explicit CommunicationManager(QObject *parent = nullptr);
    ~CommunicationManager();

    // Email functionality
    bool setupEmailServer(const QString &smtpServer, int port, const QString &username, 
                         const QString &password, bool useSSL = true);
    bool sendEmail(const EmailMessage &message);
    bool scheduleEmail(const EmailMessage &message, const QDateTime &sendTime);
    void sendBulkEmails(const QList<EmailMessage> &messages);
    
    // SMS functionality
    bool setupSMSProvider(const QString &provider, const QString &apiKey, const QString &senderId);
    bool sendSMS(const SMSMessage &message);
    bool scheduleSMS(const SMSMessage &message, const QDateTime &sendTime);
    void sendBulkSMS(const QList<SMSMessage> &messages);
    
    // Push notifications (in-app)
    void sendNotification(const NotificationMessage &notification);
    void broadcastNotification(const QString &message, const QString &type = "info");
    void sendToRole(const QString &role, const QString &title, const QString &message, const QString &type = "info");
    QList<NotificationMessage> getUnreadNotifications(const QString &recipient);
    void markNotificationAsRead(const QString &messageId);
    
    // Template management
    void saveEmailTemplate(const QString &name, const QString &subject, const QString &body);
    QString getEmailTemplate(const QString &name);
    QStringList getEmailTemplateNames();
    void deleteEmailTemplate(const QString &name);
    
    void saveSMSTemplate(const QString &name, const QString &message);
    QString getSMSTemplate(const QString &name);
    QStringList getSMSTemplateNames();
    void deleteSMSTemplate(const QString &name);
    
    // Automated notifications
    void enableAutomaticNotifications(bool enabled);
    void setAttendanceNotificationTime(const QTime &time);
    void setWeeklyReportDay(int dayOfWeek); // 1=Monday, 7=Sunday
    void setMonthlyReportDay(int day);
    
    // Communication history
    QList<EmailMessage> getEmailHistory(const QDate &startDate = QDate(), const QDate &endDate = QDate());
    QList<SMSMessage> getSMSHistory(const QDate &startDate = QDate(), const QDate &endDate = QDate());
    QList<NotificationMessage> getNotificationHistory(const QString &recipient = "", 
                                                     const QDate &startDate = QDate(), 
                                                     const QDate &endDate = QDate());
    
    // Statistics
    struct CommunicationStats {
        int totalEmailsSent;
        int totalSMSSent;
        int totalNotifications;
        int failedEmails;
        int failedSMS;
        double deliveryRate;
        QDateTime lastEmailSent;
        QDateTime lastSMSSent;
        QStringList topRecipients;
    };
    
    CommunicationStats getStatistics(const QDate &startDate = QDate(), const QDate &endDate = QDate());
    
    // Settings management
    void loadSettings();
    void saveSettings();
    bool isEmailConfigured() const { return m_emailConfigured; }
    bool isSMSConfigured() const { return m_smsConfigured; }

public slots:
    void processScheduledMessages();
    void sendDailyAttendanceReport();
    void sendWeeklyReport();
    void sendMonthlyReport();
    void sendLowAttendanceAlert(int studentId, double attendanceRate);
    void sendGradeAlert(int studentId, const QString &subject, double grade);
    void sendParentAlert(int studentId, const QString &message, const QString &type = "info");

signals:
    void emailSent(const QString &messageId, bool success);
    void smsSent(const QString &messageId, bool success);
    void notificationSent(const QString &messageId);
    void messageQueueUpdated(int pendingCount);
    void configurationChanged();

private slots:
    void onNetworkReply();
    void processMessageQueue();
    void onScheduledMessageTimer();

private:
    void initializeTemplates();
    void setupAutomaticNotifications();
    void loadMessageHistory();
    void saveMessageHistory();
    
    QString generateMessageId();
    QString formatEmailBody(const QString &templateStr, const QJsonObject &variables);
    QString formatSMSMessage(const QString &templateStr, const QJsonObject &variables);
    
    // Email sending
    bool sendEmailViaAPI(const EmailMessage &message);
    bool sendEmailViaSMTP(const EmailMessage &message);
    
    // SMS sending
    bool sendSMSViaAPI(const SMSMessage &message);
    
    // Notification system
    void storeNotification(const NotificationMessage &notification);
    void removeOldNotifications();
    
    Database *m_database;
    QNetworkAccessManager *m_networkManager;
    
    // Configuration
    struct EmailConfig {
        QString smtpServer;
        int port;
        QString username;
        QString password;
        bool useSSL;
        QString fromAddress;
        QString fromName;
    } m_emailConfig;
    
    struct SMSConfig {
        QString provider; // twilio, nexmo, etc.
        QString apiKey;
        QString senderId;
        QString apiUrl;
        QString authToken;
    } m_smsConfig;
    
    bool m_emailConfigured;
    bool m_smsConfigured;
    bool m_automaticNotificationsEnabled;
    
    // Message queues
    QQueue<EmailMessage> m_emailQueue;
    QQueue<SMSMessage> m_smsQueue;
    QList<NotificationMessage> m_notifications;
    
    // Timers
    QTimer *m_queueProcessTimer;
    QTimer *m_scheduledMessageTimer;
    QTimer *m_dailyReportTimer;
    QTimer *m_weeklyReportTimer;
    QTimer *m_monthlyReportTimer;
    
    // Settings
    QSettings *m_settings;
    
    // Message history
    QList<EmailMessage> m_emailHistory;
    QList<SMSMessage> m_smsHistory;
    
    // Templates
    QMap<QString, QString> m_emailTemplates;
    QMap<QString, QString> m_smsTemplates;
    
    // Rate limiting
    QDateTime m_lastEmailSent;
    QDateTime m_lastSMSSent;
    int m_emailRateLimit; // emails per minute
    int m_smsRateLimit; // SMS per minute
    
    // Retry mechanism
    struct RetryInfo {
        QString messageId;
        int attempts;
        QDateTime nextRetry;
        QString type; // email or sms
    };
    
    QList<RetryInfo> m_retryQueue;
    QTimer *m_retryTimer;
};

// Communication Settings Dialog
class CommunicationSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommunicationSettingsDialog(CommunicationManager *manager, QWidget *parent = nullptr);

private slots:
    void saveEmailSettings();
    void saveSMSSettings();
    void testEmailConnection();
    void testSMSConnection();
    void loadTemplate();
    void saveTemplate();
    void deleteTemplate();

private:
    void setupUI();
    void setupEmailTab();
    void setupSMSTab();
    void setupTemplatesTab();
    void setupNotificationTab();
    void loadCurrentSettings();
    
    CommunicationManager *m_manager;
    QTabWidget *m_tabWidget;
    
    // Email settings
    QLineEdit *m_smtpServerEdit;
    QSpinBox *m_smtpPortSpin;
    QLineEdit *m_emailUserEdit;
    QLineEdit *m_emailPassEdit;
    QCheckBox *m_emailSSLCheck;
    QLineEdit *m_fromAddressEdit;
    QLineEdit *m_fromNameEdit;
    
    // SMS settings
    QComboBox *m_smsProviderCombo;
    QLineEdit *m_smsApiKeyEdit;
    QLineEdit *m_smsSenderIdEdit;
    QLineEdit *m_smsApiUrlEdit;
    
    // Template management
    QComboBox *m_templateTypeCombo;
    QListWidget *m_templateList;
    QLineEdit *m_templateNameEdit;
    QTextEdit *m_templateContentEdit;
    
    // Notification settings
    QCheckBox *m_enableAutoNotifications;
    QTimeEdit *m_attendanceReportTime;
    QComboBox *m_weeklyReportDay;
    QSpinBox *m_monthlyReportDay;
};

// Parent Portal Communication Interface
class ParentPortal : public QWidget
{
    Q_OBJECT

public:
    explicit ParentPortal(Database *database, CommunicationManager *commManager, QWidget *parent = nullptr);

public slots:
    void loginParent(const QString &username, const QString &password);
    void logoutParent();

signals:
    void loginSuccessful(int studentId);
    void loginFailed();
    void messageReceived(const QString &message);

private slots:
    void sendMessageToTeacher();
    void requestMeeting();
    void viewStudentGrades();
    void viewStudentAttendance();
    void updateContactInfo();

private:
    void setupUI();
    void setupStudentInfo();
    void setupCommunication();
    void setupRequests();
    void loadStudentData();
    
    Database *m_database;
    CommunicationManager *m_commManager;
    int m_currentStudentId;
    bool m_isLoggedIn;
    
    // UI components
    QTabWidget *m_tabWidget;
    QWidget *m_studentInfoTab;
    QWidget *m_communicationTab;
    QWidget *m_requestsTab;
    
    // Student info display
    QLabel *m_studentNameLabel;
    QLabel *m_classLabel;
    QLabel *m_rollNoLabel;
    QLabel *m_attendanceLabel;
    QLabel *m_gpaLabel;
    
    // Communication
    QTextEdit *m_messageEdit;
    QComboBox *m_recipientCombo;
    QPushButton *m_sendMessageBtn;
    QListWidget *m_messageHistory;
    
    // Meeting requests
    QDateEdit *m_meetingDateEdit;
    QTimeEdit *m_meetingTimeEdit;
    QTextEdit *m_meetingPurposeEdit;
    QPushButton *m_requestMeetingBtn;
};

#endif // COMMUNICATIONMANAGER_H
