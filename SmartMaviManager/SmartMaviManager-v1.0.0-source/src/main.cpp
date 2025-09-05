#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>
#include <QFontDatabase>
#include <QDir>
#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Smart Mavi Manager");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Smart Mavi Solutions");
    app.setApplicationDisplayName("Smart Mavi Manager 📚");
    
    // Set application icon
    QPixmap logoPixmap("logo.png");
    if (!logoPixmap.isNull()) {
        app.setWindowIcon(QIcon(logoPixmap));
    }
    
    // Create and show splash screen
    QSplashScreen *splash = nullptr;
    if (!logoPixmap.isNull()) {
        // Scale logo for splash screen
        QPixmap splashPixmap = logoPixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        
        // Create a custom splash screen with gradient background
        QPixmap splashBg(400, 400);
        splashBg.fill(Qt::transparent);
        
        QPainter painter(&splashBg);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Draw gradient background
        QLinearGradient gradient(0, 0, 400, 400);
        gradient.setColorAt(0, QColor(52, 152, 219));
        gradient.setColorAt(1, QColor(41, 128, 185));
        
        painter.setBrush(QBrush(gradient));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(splashBg.rect(), 20, 20);
        
        // Draw logo
        int logoX = (400 - splashPixmap.width()) / 2;
        int logoY = (400 - splashPixmap.height()) / 2 - 50;
        painter.drawPixmap(logoX, logoY, splashPixmap);
        
        // Draw text
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(QRect(0, logoY + splashPixmap.height() + 20, 400, 50), 
                        Qt::AlignCenter, "Smart Mavi Manager");
        
        painter.setFont(QFont("Arial", 12));
        painter.drawText(QRect(0, logoY + splashPixmap.height() + 60, 400, 30), 
                        Qt::AlignCenter, "Professional Schedule Generator");
        
        painter.drawText(QRect(0, 350, 400, 30), 
                        Qt::AlignCenter, "Loading... 🚀");
        
        splash = new QSplashScreen(splashBg);
        splash->show();
        splash->showMessage("Initializing Smart Mavi Manager...", Qt::AlignBottom | Qt::AlignCenter, Qt::white);
        
        app.processEvents();
    }
    
    // Show splash for a brief moment
    if (splash) {
        QTimer::singleShot(2000, [splash]() {
            splash->finish(nullptr);
            delete splash;
        });
    }
    
    // Create and show main window
    MainWindow window;
    
    if (splash) {
        QTimer::singleShot(2000, [&window, splash]() {
            splash->finish(&window);
            window.show();
        });
    } else {
        window.show();
    }
    
    return app.exec();
}
