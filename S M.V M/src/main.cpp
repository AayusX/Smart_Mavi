#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QMessageBox>
#include <QStandardPaths>
#include "mainwindow.h"
#include "database/database.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Smart MA.VI Manager");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Shree MA.VI Imilya");
    app.setOrganizationDomain("mavimanager.tech07.com");
    
    // Set application style
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // Create data directory if it doesn't exist
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);
    
    // Initialize database
    Database db;
    if (!db.initialize()) {
        QMessageBox::critical(nullptr, "Database Error", 
                            "Failed to initialize database. Please check permissions and try again.");
        return -1;
    }
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    return app.exec();
}
