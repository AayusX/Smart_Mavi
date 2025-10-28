#pragma once

// Qt Core
#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// Qt Widgets
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QStackedWidget>
#include <QFrame>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QComboBox>
#include <QHeaderView>
#include <QDialog>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QStyleFactory>
#include <QDate>

// Qt Charts
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

// Qt Effects
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

// Constants
namespace Constants {
    const QString APP_NAME = "Aayush-tech07 Dashboard";
    const QString APP_VERSION = "1.0.0";
    const QString STYLE_FILE = "assets/style.qss";
    const QString DATA_FILE = "assets/students.json";
    const QString USERS_FILE = "assets/users.json";
    
    // Colors
    const QString COLOR_BACKGROUND = "#101820";
    const QString COLOR_SIDEBAR = "#1f2a44";
    const QString COLOR_HOVER = "#394b75";
    const QString COLOR_TEXT = "#f0f0f0";
}

// Helper functions
namespace Helpers {
    inline QJsonArray readJsonFile(const QString& path) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            return QJsonArray();
        }
        
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        return doc.array();
    }
    
    inline bool writeJsonFile(const QString& path, const QJsonArray& array) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly)) {
            return false;
        }
        
        QJsonDocument doc(array);
        file.write(doc.toJson(QJsonDocument::Indented));
        return true;
    }

    inline bool verifyUser(const QString& username, const QString& password) {
        QJsonArray users = readJsonFile(Constants::USERS_FILE);
        for (const QJsonValue& value : users) {
            QJsonObject user = value.toObject();
            if (user["username"].toString() == username && 
                user["password"].toString() == password) {
                return true;
            }
        }
        return false;
    }

    inline bool addUser(const QString& username, const QString& password, const QString& role = "user") {
        QJsonArray users = readJsonFile(Constants::USERS_FILE);
        
        // Check if username already exists
        for (const QJsonValue& value : users) {
            if (value.toObject()["username"].toString() == username) {
                return false;
            }
        }
        
        QJsonObject newUser;
        newUser["username"] = username;
        newUser["password"] = password;
        newUser["role"] = role;
        
        users.append(newUser);
        return writeJsonFile(Constants::USERS_FILE, users);
    }

    inline QString getUserRole(const QString& username) {
        QJsonArray users = readJsonFile(Constants::USERS_FILE);
        for (const QJsonValue& value : users) {
            QJsonObject user = value.toObject();
            if (user["username"].toString() == username) {
                return user["role"].toString();
            }
        }
        return QString();
    }
}