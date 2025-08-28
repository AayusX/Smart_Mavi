#include "communication/communicationmanager.h"
#include "database/database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

CommunicationManager::CommunicationManager(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &CommunicationManager::handleNetworkResponse);
}

CommunicationManager::~CommunicationManager()
{
}

bool CommunicationManager::sendSMS(const QString &phoneNumber, const QString &message)
{
    // Store SMS in database for tracking
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO communications (recipient, type, subject, content, "
                 "sent_date, status, delivery_method) "
                 "VALUES (?, 'SMS', 'SMS Message', ?, ?, 'Pending', 'SMS')");
    
    query.addBindValue(phoneNumber);
    query.addBindValue(message);
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Failed to log SMS:" << query.lastError().text();
        return false;
    }
    
    // In a real implementation, you would integrate with an SMS gateway
    // For now, we'll simulate sending
    qDebug() << "SMS sent to" << phoneNumber << ":" << message;
    
    // Update status to sent
    query.prepare("UPDATE communications SET status = 'Sent' WHERE recipient = ? "
                 "AND type = 'SMS' AND content = ? AND status = 'Pending'");
    query.addBindValue(phoneNumber);
    query.addBindValue(message);
    query.exec();
    
    emit smsStatusChanged(phoneNumber, "Sent");
    return true;
}

bool CommunicationManager::sendEmail(const QString &email, const QString &subject, const QString &content)
{
    // Store email in database for tracking
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO communications (recipient, type, subject, content, "
                 "sent_date, status, delivery_method) "
                 "VALUES (?, 'Email', ?, ?, ?, 'Pending', 'Email')");
    
    query.addBindValue(email);
    query.addBindValue(subject);
    query.addBindValue(content);
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Failed to log email:" << query.lastError().text();
        return false;
    }
    
    // In a real implementation, you would integrate with an email service
    // For now, we'll simulate sending
    qDebug() << "Email sent to" << email << "Subject:" << subject;
    
    // Update status to sent
    query.prepare("UPDATE communications SET status = 'Sent' WHERE recipient = ? "
                 "AND type = 'Email' AND subject = ? AND content = ? AND status = 'Pending'");
    query.addBindValue(email);
    query.addBindValue(subject);
    query.addBindValue(content);
    query.exec();
    
    emit emailStatusChanged(email, "Sent");
    return true;
}

bool CommunicationManager::sendBulkSMS(const QStringList &phoneNumbers, const QString &message)
{
    bool allSent = true;
    
    for (const QString &phone : phoneNumbers) {
        if (!sendSMS(phone, message)) {
            allSent = false;
        }
    }
    
    return allSent;
}

bool CommunicationManager::sendBulkEmail(const QStringList &emails, const QString &subject, const QString &content)
{
    bool allSent = true;
    
    for (const QString &email : emails) {
        if (!sendEmail(email, subject, content)) {
            allSent = false;
        }
    }
    
    return allSent;
}

bool CommunicationManager::addAnnouncement(const Announcement &announcement)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO announcements (title, content, target_audience, "
                 "priority, start_date, end_date, created_by, category) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(announcement.title);
    query.addBindValue(announcement.content);
    query.addBindValue(announcement.targetAudience);
    query.addBindValue(announcement.priority);
    query.addBindValue(announcement.startDate);
    query.addBindValue(announcement.endDate);
    query.addBindValue(announcement.createdBy);
    query.addBindValue(announcement.category);
    
    if (!query.exec()) {
        qDebug() << "Failed to add announcement:" << query.lastError().text();
        return false;
    }
    
    emit announcementAdded(announcement.title);
    return true;
}

QList<Announcement> CommunicationManager::getActiveAnnouncements()
{
    QList<Announcement> announcements;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM announcements WHERE "
                 "start_date <= ? AND (end_date IS NULL OR end_date >= ?) "
                 "ORDER BY priority DESC, created_at DESC");
    
    QDate today = QDate::currentDate();
    query.addBindValue(today);
    query.addBindValue(today);
    
    if (query.exec()) {
        while (query.next()) {
            Announcement announcement;
            announcement.id = query.value("id").toInt();
            announcement.title = query.value("title").toString();
            announcement.content = query.value("content").toString();
            announcement.targetAudience = query.value("target_audience").toString();
            announcement.priority = query.value("priority").toString();
            announcement.startDate = query.value("start_date").toDate();
            announcement.endDate = query.value("end_date").toDate();
            announcement.createdBy = query.value("created_by").toString();
            announcement.category = query.value("category").toString();
            announcement.createdAt = query.value("created_at").toDateTime();
            announcements.append(announcement);
        }
    }
    
    return announcements;
}

bool CommunicationManager::addNotificationTemplate(const NotificationTemplate &temp)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO notification_templates (name, subject, content, "
                 "type, variables, category) VALUES (?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(temp.name);
    query.addBindValue(temp.subject);
    query.addBindValue(temp.content);
    query.addBindValue(temp.type);
    query.addBindValue(temp.variables.join(","));
    query.addBindValue(temp.category);
    
    if (!query.exec()) {
        qDebug() << "Failed to add template:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<NotificationTemplate> CommunicationManager::getNotificationTemplates()
{
    QList<NotificationTemplate> templates;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM notification_templates ORDER BY category, name")) {
        while (query.next()) {
            NotificationTemplate temp;
            temp.id = query.value("id").toInt();
            temp.name = query.value("name").toString();
            temp.subject = query.value("subject").toString();
            temp.content = query.value("content").toString();
            temp.type = query.value("type").toString();
            temp.variables = query.value("variables").toString().split(",");
            temp.category = query.value("category").toString();
            templates.append(temp);
        }
    }
    
    return templates;
}

QString CommunicationManager::processTemplate(const QString &templateContent, const QMap<QString, QString> &variables)
{
    QString processedContent = templateContent;
    
    for (auto it = variables.begin(); it != variables.end(); ++it) {
        QString placeholder = "{{" + it.key() + "}}";
        processedContent.replace(placeholder, it.value());
    }
    
    return processedContent;
}

bool CommunicationManager::scheduleMessage(const ScheduledMessage &message)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO scheduled_messages (recipient, type, subject, content, "
                 "scheduled_time, created_by, status) VALUES (?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(message.recipient);
    query.addBindValue(message.type);
    query.addBindValue(message.subject);
    query.addBindValue(message.content);
    query.addBindValue(message.scheduledTime);
    query.addBindValue(message.createdBy);
    query.addBindValue("Scheduled");
    
    if (!query.exec()) {
        qDebug() << "Failed to schedule message:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<ScheduledMessage> CommunicationManager::getPendingScheduledMessages()
{
    QList<ScheduledMessage> messages;
    QSqlQuery query(Database::instance().database());
    
    query.prepare("SELECT * FROM scheduled_messages WHERE "
                 "scheduled_time <= ? AND status = 'Scheduled' "
                 "ORDER BY scheduled_time");
    
    query.addBindValue(QDateTime::currentDateTime());
    
    if (query.exec()) {
        while (query.next()) {
            ScheduledMessage message;
            message.id = query.value("id").toInt();
            message.recipient = query.value("recipient").toString();
            message.type = query.value("type").toString();
            message.subject = query.value("subject").toString();
            message.content = query.value("content").toString();
            message.scheduledTime = query.value("scheduled_time").toDateTime();
            message.createdBy = query.value("created_by").toString();
            message.status = query.value("status").toString();
            messages.append(message);
        }
    }
    
    return messages;
}

bool CommunicationManager::addEmergencyContact(const EmergencyContact &contact)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO emergency_contacts (name, phone, email, role, "
                 "priority, active) VALUES (?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(contact.name);
    query.addBindValue(contact.phone);
    query.addBindValue(contact.email);
    query.addBindValue(contact.role);
    query.addBindValue(contact.priority);
    query.addBindValue(contact.active);
    
    if (!query.exec()) {
        qDebug() << "Failed to add emergency contact:" << query.lastError().text();
        return false;
    }
    
    return true;
}

QList<EmergencyContact> CommunicationManager::getEmergencyContacts()
{
    QList<EmergencyContact> contacts;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM emergency_contacts WHERE active = 1 ORDER BY priority")) {
        while (query.next()) {
            EmergencyContact contact;
            contact.id = query.value("id").toInt();
            contact.name = query.value("name").toString();
            contact.phone = query.value("phone").toString();
            contact.email = query.value("email").toString();
            contact.role = query.value("role").toString();
            contact.priority = query.value("priority").toInt();
            contact.active = query.value("active").toBool();
            contacts.append(contact);
        }
    }
    
    return contacts;
}

bool CommunicationManager::sendEmergencyAlert(const QString &message)
{
    QList<EmergencyContact> contacts = getEmergencyContacts();
    bool allSent = true;
    
    for (const EmergencyContact &contact : contacts) {
        // Send SMS
        if (!contact.phone.isEmpty()) {
            if (!sendSMS(contact.phone, "EMERGENCY ALERT: " + message)) {
                allSent = false;
            }
        }
        
        // Send Email
        if (!contact.email.isEmpty()) {
            if (!sendEmail(contact.email, "EMERGENCY ALERT - Shree MA.VI Imilya", 
                          "EMERGENCY ALERT\n\n" + message + 
                          "\n\nThis is an automated emergency notification from Shree MA.VI Imilya School Management System.")) {
                allSent = false;
            }
        }
    }
    
    // Log emergency alert
    QSqlQuery query(Database::instance().database());
    query.prepare("INSERT INTO communications (recipient, type, subject, content, "
                 "sent_date, status, delivery_method) "
                 "VALUES ('Emergency Contacts', 'Emergency', 'Emergency Alert', ?, ?, 'Sent', 'Multiple')");
    query.addBindValue(message);
    query.addBindValue(QDateTime::currentDateTime());
    query.exec();
    
    emit emergencyAlertSent(message);
    return allSent;
}

QList<CommunicationLog> CommunicationManager::getCommunicationHistory(int limit)
{
    QList<CommunicationLog> logs;
    QSqlQuery query(Database::instance().database());
    
    QString queryStr = "SELECT * FROM communications ORDER BY sent_date DESC";
    if (limit > 0) {
        queryStr += QString(" LIMIT %1").arg(limit);
    }
    
    if (query.exec(queryStr)) {
        while (query.next()) {
            CommunicationLog log;
            log.id = query.value("id").toInt();
            log.recipient = query.value("recipient").toString();
            log.type = query.value("type").toString();
            log.subject = query.value("subject").toString();
            log.content = query.value("content").toString();
            log.sentDate = query.value("sent_date").toDateTime();
            log.status = query.value("status").toString();
            log.deliveryMethod = query.value("delivery_method").toString();
            logs.append(log);
        }
    }
    
    return logs;
}

bool CommunicationManager::addFeedback(const ParentFeedback &feedback)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("INSERT INTO parent_feedback (student_roll, parent_name, "
                 "feedback_type, rating, comments, feedback_date, category, "
                 "response_required, responded) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(feedback.studentRoll);
    query.addBindValue(feedback.parentName);
    query.addBindValue(feedback.feedbackType);
    query.addBindValue(feedback.rating);
    query.addBindValue(feedback.comments);
    query.addBindValue(feedback.feedbackDate);
    query.addBindValue(feedback.category);
    query.addBindValue(feedback.responseRequired);
    query.addBindValue(feedback.responded);
    
    if (!query.exec()) {
        qDebug() << "Failed to add feedback:" << query.lastError().text();
        return false;
    }
    
    emit feedbackReceived(feedback.studentRoll, feedback.parentName);
    return true;
}

QList<ParentFeedback> CommunicationManager::getPendingFeedback()
{
    QList<ParentFeedback> feedbacks;
    QSqlQuery query(Database::instance().database());
    
    if (query.exec("SELECT * FROM parent_feedback WHERE response_required = 1 "
                  "AND responded = 0 ORDER BY feedback_date DESC")) {
        while (query.next()) {
            ParentFeedback feedback;
            feedback.id = query.value("id").toInt();
            feedback.studentRoll = query.value("student_roll").toString();
            feedback.parentName = query.value("parent_name").toString();
            feedback.feedbackType = query.value("feedback_type").toString();
            feedback.rating = query.value("rating").toInt();
            feedback.comments = query.value("comments").toString();
            feedback.feedbackDate = query.value("feedback_date").toDateTime();
            feedback.category = query.value("category").toString();
            feedback.responseRequired = query.value("response_required").toBool();
            feedback.responded = query.value("responded").toBool();
            feedbacks.append(feedback);
        }
    }
    
    return feedbacks;
}

bool CommunicationManager::markFeedbackResponded(int feedbackId)
{
    QSqlQuery query(Database::instance().database());
    
    query.prepare("UPDATE parent_feedback SET responded = 1, response_date = ? WHERE id = ?");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(feedbackId);
    
    if (!query.exec()) {
        qDebug() << "Failed to mark feedback as responded:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool CommunicationManager::sendAttendanceAlert(const QString &studentRoll, const QString &parentPhone)
{
    QString message = QString("Alert: Your child (Roll: %1) was marked absent today. "
                             "Please contact school if this is incorrect.").arg(studentRoll);
    
    return sendSMS(parentPhone, message);
}

bool CommunicationManager::sendFeeReminder(const QString &studentRoll, const QString &parentPhone, 
                                          double amount, const QDate &dueDate)
{
    QString message = QString("Fee Reminder: Outstanding fee of Rs. %.2f for student (Roll: %1) "
                             "is due on %2. Please make payment at the earliest.")
                             .arg(amount).arg(studentRoll).arg(dueDate.toString("dd/MM/yyyy"));
    
    return sendSMS(parentPhone, message);
}

bool CommunicationManager::sendExamNotification(const QString &examName, const QDate &examDate, 
                                               const QString &grade)
{
    // Get all students in the grade
    QSqlQuery query(Database::instance().database());
    query.prepare("SELECT parent_phone FROM enhanced_students WHERE grade = ? AND parent_phone IS NOT NULL");
    query.addBindValue(grade);
    
    QStringList phoneNumbers;
    if (query.exec()) {
        while (query.next()) {
            QString phone = query.value("parent_phone").toString();
            if (!phone.isEmpty()) {
                phoneNumbers.append(phone);
            }
        }
    }
    
    QString message = QString("Exam Notification: %1 for Grade %2 is scheduled on %3. "
                             "Please ensure your child is well prepared.")
                             .arg(examName).arg(grade).arg(examDate.toString("dd/MM/yyyy"));
    
    return sendBulkSMS(phoneNumbers, message);
}

void CommunicationManager::processScheduledMessages()
{
    QList<ScheduledMessage> pendingMessages = getPendingScheduledMessages();
    
    for (const ScheduledMessage &message : pendingMessages) {
        bool sent = false;
        
        if (message.type == "SMS") {
            sent = sendSMS(message.recipient, message.content);
        } else if (message.type == "Email") {
            sent = sendEmail(message.recipient, message.subject, message.content);
        }
        
        if (sent) {
            // Update scheduled message status
            QSqlQuery query(Database::instance().database());
            query.prepare("UPDATE scheduled_messages SET status = 'Sent', "
                         "actual_sent_time = ? WHERE id = ?");
            query.addBindValue(QDateTime::currentDateTime());
            query.addBindValue(message.id);
            query.exec();
        }
    }
}

void CommunicationManager::handleNetworkResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        qDebug() << "Network response:" << data;
    } else {
        qDebug() << "Network error:" << reply->errorString();
    }
    
    reply->deleteLater();
}

bool CommunicationManager::createDatabaseTables()
{
    QSqlQuery query(Database::instance().database());
    
    // Create communications table
    QString createCommTable = R"(
        CREATE TABLE IF NOT EXISTS communications (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            recipient TEXT NOT NULL,
            type TEXT NOT NULL,
            subject TEXT,
            content TEXT NOT NULL,
            sent_date TIMESTAMP NOT NULL,
            status TEXT DEFAULT 'Pending',
            delivery_method TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createCommTable)) {
        qDebug() << "Failed to create communications table:" << query.lastError().text();
        return false;
    }
    
    // Create announcements table
    QString createAnnTable = R"(
        CREATE TABLE IF NOT EXISTS announcements (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            content TEXT NOT NULL,
            target_audience TEXT,
            priority TEXT DEFAULT 'Medium',
            start_date DATE,
            end_date DATE,
            created_by TEXT,
            category TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createAnnTable)) {
        qDebug() << "Failed to create announcements table:" << query.lastError().text();
        return false;
    }
    
    // Create notification templates table
    QString createTemplatesTable = R"(
        CREATE TABLE IF NOT EXISTS notification_templates (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            subject TEXT,
            content TEXT NOT NULL,
            type TEXT NOT NULL,
            variables TEXT,
            category TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createTemplatesTable)) {
        qDebug() << "Failed to create notification_templates table:" << query.lastError().text();
        return false;
    }
    
    // Create scheduled messages table
    QString createScheduledTable = R"(
        CREATE TABLE IF NOT EXISTS scheduled_messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            recipient TEXT NOT NULL,
            type TEXT NOT NULL,
            subject TEXT,
            content TEXT NOT NULL,
            scheduled_time TIMESTAMP NOT NULL,
            created_by TEXT,
            status TEXT DEFAULT 'Scheduled',
            actual_sent_time TIMESTAMP,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createScheduledTable)) {
        qDebug() << "Failed to create scheduled_messages table:" << query.lastError().text();
        return false;
    }
    
    // Create emergency contacts table
    QString createEmergencyTable = R"(
        CREATE TABLE IF NOT EXISTS emergency_contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            phone TEXT,
            email TEXT,
            role TEXT,
            priority INTEGER DEFAULT 1,
            active BOOLEAN DEFAULT 1,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    )";
    
    if (!query.exec(createEmergencyTable)) {
        qDebug() << "Failed to create emergency_contacts table:" << query.lastError().text();
        return false;
    }
    
    // Create parent feedback table
    QString createFeedbackTable = R"(
        CREATE TABLE IF NOT EXISTS parent_feedback (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_roll TEXT NOT NULL,
            parent_name TEXT,
            feedback_type TEXT NOT NULL,
            rating INTEGER,
            comments TEXT,
            feedback_date TIMESTAMP NOT NULL,
            category TEXT,
            response_required BOOLEAN DEFAULT 0,
            responded BOOLEAN DEFAULT 0,
            response_date TIMESTAMP,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (student_roll) REFERENCES enhanced_students(roll_number)
        )
    )";
    
    if (!query.exec(createFeedbackTable)) {
        qDebug() << "Failed to create parent_feedback table:" << query.lastError().text();
        return false;
    }
    
    return true;
}
