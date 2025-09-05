#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QSplashScreen>
#include <QProgressDialog>
#include <QTimer>
#include <QDesktopWidget>
#include <QMenu>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_progressDialog(nullptr)
{
    setWindowTitle("Smart Mavi Manager 📚");
    setMinimumSize(1000, 700);
    
    // Set window icon (logo)
    QPixmap logoPixmap("logo.png");
    if (!logoPixmap.isNull()) {
        setWindowIcon(QIcon(logoPixmap));
    }
    
    setupUI();
    setupMenuBar();
    setupStatusBar();
    applyApplicationStyling();
    showWelcomeScreen();
    
    // Center the window
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void MainWindow::setupUI()
{
    m_centralStack = new QStackedWidget;
    setCentralWidget(m_centralStack);
    
    // Create welcome widget
    m_welcomeWidget = new QLabel;
    m_welcomeWidget->setAlignment(Qt::AlignCenter);
    m_welcomeWidget->setWordWrap(true);
    m_welcomeWidget->setObjectName("welcomeWidget");
    
    // Create schedule view
    m_scheduleView = new ScheduleView;
    
    // Add widgets to stack
    m_centralStack->addWidget(m_welcomeWidget);
    m_centralStack->addWidget(m_scheduleView);
    
    // Connect schedule view signals
    connect(m_scheduleView, &ScheduleView::regenerateRequested, 
            this, &MainWindow::onRegenerateRequested);
}

void MainWindow::setupMenuBar()
{
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("📁 &File");
    
    m_newAction = new QAction("🆕 &New Schedule", this);
    m_newAction->setShortcut(QKeySequence::New);
    m_newAction->setStatusTip("Create a new schedule");
    connect(m_newAction, &QAction::triggered, this, &MainWindow::newSchedule);
    
    m_openAction = new QAction("📂 &Open Schedule", this);
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setStatusTip("Open an existing schedule");
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openSchedule);
    
    m_saveAction = new QAction("💾 &Save Schedule", this);
    m_saveAction->setShortcut(QKeySequence::Save);
    m_saveAction->setStatusTip("Save the current schedule");
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::saveSchedule);
    
    m_exitAction = new QAction("🚪 E&xit", this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setStatusTip("Exit the application");
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    
    fileMenu->addAction(m_newAction);
    fileMenu->addAction(m_openAction);
    fileMenu->addAction(m_saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);
    
    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("❓ &Help");
    
    m_helpAction = new QAction("📖 &User Guide", this);
    m_helpAction->setStatusTip("Show user guide");
    connect(m_helpAction, &QAction::triggered, this, &MainWindow::showHelp);
    
    m_aboutAction = new QAction("ℹ️ &About", this);
    m_aboutAction->setStatusTip("About Smart Mavi Manager");
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::aboutApp);
    
    helpMenu->addAction(m_helpAction);
    helpMenu->addSeparator();
    helpMenu->addAction(m_aboutAction);
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Ready to create amazing schedules! 🚀");
    statusBar()->addWidget(m_statusLabel);
}

void MainWindow::showWelcomeScreen()
{
    QString welcomeHtml = QString(
        "<div style='text-align: center; font-family: Arial, sans-serif; padding: 50px;'>"
        "<h1 style='color: #2c3e50; font-size: 36px; margin-bottom: 20px;'>"
        "🎓 Smart Mavi Manager 🎓</h1>"
        
        "<div style='background: rgba(52, 152, 219, 0.1); border-radius: 15px; padding: 30px; margin: 30px;'>"
        "<h2 style='color: #34495e; font-size: 24px;'>Professional Schedule Generator</h2>"
        
        "<div style='font-size: 18px; color: #2c3e50; line-height: 1.8; margin: 25px 0;'>"
        "✨ <b>Intelligent Randomization</b> - Smart conflict resolution<br>"
        "👨‍🏫 <b>Teacher Management</b> - Subject assignments & workload balancing<br>"
        "🏫 <b>Class Scheduling</b> - Optimized time slot allocation<br>"
        "📊 <b>Professional Reports</b> - Beautiful printable schedules<br>"
        "🎯 <b>User-Friendly</b> - Fun and intuitive survey system<br>"
        "</div>"
        "</div>"
        
        "<div style='margin: 40px 0;'>"
        "<button onclick='' style='"
        "background: linear-gradient(45deg, #3498db, #2980b9); "
        "color: white; border: none; border-radius: 12px; "
        "padding: 15px 30px; font-size: 18px; font-weight: bold; "
        "cursor: pointer; margin: 10px;'>"
        "🚀 Start Creating Your Schedule!"
        "</button>"
        "</div>"
        
        "<div style='color: #7f8c8d; font-size: 14px; margin-top: 40px;'>"
        "<p>💡 <b>Pro Tip:</b> The more detailed your input, the better your schedule will be!</p>"
        "<p>🎲 Each generation creates a unique, optimized schedule</p>"
        "</div>"
        "</div>"
    );
    
    // Add logo if available
    QPixmap logoPixmap("logo.png");
    if (!logoPixmap.isNull()) {
        // Scale logo appropriately
        logoPixmap = logoPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        welcomeHtml = QString("<div style='text-align: center;'><img src='logo.png' width='100' height='100'></div>") + welcomeHtml;
    }
    
    m_welcomeWidget->setText(welcomeHtml);
    m_welcomeWidget->setTextFormat(Qt::RichText);
    
    m_centralStack->setCurrentWidget(m_welcomeWidget);
}

void MainWindow::newSchedule()
{
    SurveyDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        m_currentConfig = dialog.getScheduleConfig();
        generateScheduleWithProgress();
    }
}

void MainWindow::generateScheduleWithProgress()
{
    // Show progress dialog
    m_progressDialog = new QProgressDialog("🎲 Generating your awesome schedule...", "Cancel", 0, 100, this);
    m_progressDialog->setWindowModality(Qt::WindowModal);
    m_progressDialog->setAutoClose(true);
    m_progressDialog->setMinimumDuration(0);
    m_progressDialog->show();
    
    // Simulate progress with timer
    QTimer *progressTimer = new QTimer(this);
    int progress = 0;
    
    connect(progressTimer, &QTimer::timeout, [this, progressTimer, &progress]() {
        progress += 10;
        m_progressDialog->setValue(progress);
        
        if (progress >= 100) {
            progressTimer->stop();
            progressTimer->deleteLater();
            
            // Generate actual schedule
            m_generator.setConfig(m_currentConfig);
            m_currentSchedule = m_generator.generateSchedule();
            
            // Update UI
            m_scheduleView->setScheduleConfig(m_currentConfig);
            m_scheduleView->setSchedule(m_currentSchedule);
            m_centralStack->setCurrentWidget(m_scheduleView);
            
            m_statusLabel->setText(QString("✅ Schedule generated with %1 entries - Ready to print!")
                                 .arg(m_currentSchedule.size()));
            
            if (m_progressDialog) {
                m_progressDialog->close();
                m_progressDialog = nullptr;
            }
            
            // Show success message
            QMessageBox::information(this, "Success! 🎉", 
                "🎊 Your schedule has been generated successfully!\\n\\n"
                "📊 You can now view, print, or export your schedule.\\n"
                "🎲 Click 'Regenerate Schedule' for a different random arrangement!");
        }
    });
    
    progressTimer->start(200); // Update every 200ms
}

void MainWindow::onRegenerateRequested()
{
    generateScheduleWithProgress();
}

void MainWindow::openSchedule()
{
    // Placeholder for opening saved schedules
    QMessageBox::information(this, "Feature Coming Soon", 
                           "📂 Schedule loading feature will be available in the next update!");
}

void MainWindow::saveSchedule()
{
    if (m_currentSchedule.isEmpty()) {
        QMessageBox::warning(this, "No Schedule", "Please generate a schedule first!");
        return;
    }
    
    // Placeholder for saving schedules
    QMessageBox::information(this, "Feature Coming Soon", 
                           "💾 Schedule saving feature will be available in the next update!\\n\\n"
                           "💡 For now, you can export to PDF or CSV from the schedule view.");
}

void MainWindow::aboutApp()
{
    QMessageBox aboutBox(this);
    aboutBox.setWindowTitle("About Smart Mavi Manager");
    aboutBox.setIconPixmap(QPixmap("logo.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    
    aboutBox.setText(
        "<h2>🎓 Smart Mavi Manager</h2>"
        "<p><b>Version 1.0.0</b></p>"
    );
    
    aboutBox.setInformativeText(
        "<p>🚀 <b>Professional Schedule Generator</b></p>"
        "<p>Smart Mavi Manager is an intelligent scheduling application that creates "
        "optimized, randomized schedules for educational institutions.</p>"
        "<br>"
        "<p><b>✨ Key Features:</b></p>"
        "<ul>"
        "<li>🎲 Advanced randomization algorithms</li>"
        "<li>👨‍🏫 Smart conflict resolution</li>"
        "<li>📊 Professional reporting</li>"
        "<li>🎨 Beautiful, user-friendly interface</li>"
        "<li>📄 Multiple export formats</li>"
        "</ul>"
        "<br>"
        "<p style='color: #7f8c8d;'>"
        "Built with ❤️ using C++ and Qt5<br>"
        "© 2024 Smart Mavi Manager"
        "</p>"
    );
    
    aboutBox.setStandardButtons(QMessageBox::Ok);
    aboutBox.exec();
}

void MainWindow::showHelp()
{
    QMessageBox helpBox(this);
    helpBox.setWindowTitle("User Guide 📖");
    helpBox.setText("<h2>🔍 How to Use Smart Mavi Manager</h2>");
    
    helpBox.setInformativeText(
        "<p><b>🚀 Getting Started:</b></p>"
        "<ol>"
        "<li>📋 Click 'New Schedule' to start the setup wizard</li>"
        "<li>👨‍🏫 Add your teachers and their subjects</li>"
        "<li>🏫 Define your classes and grades</li>"
        "<li>⏰ Configure time settings and breaks</li>"
        "<li>🎯 Generate your randomized schedule!</li>"
        "</ol>"
        "<br>"
        "<p><b>📊 Viewing & Exporting:</b></p>"
        "<ul>"
        "<li>📅 Switch between Full Schedule, Class view, and Teacher view</li>"
        "<li>🖨️ Print or preview your schedule</li>"
        "<li>📄 Export to PDF for professional documents</li>"
        "<li>📊 Export to CSV for spreadsheet analysis</li>"
        "</ul>"
        "<br>"
        "<p><b>🎲 Pro Tips:</b></p>"
        "<ul>"
        "<li>✨ Each generation creates a unique schedule arrangement</li>"
        "<li>🔄 Use 'Regenerate' to try different random combinations</li>"
        "<li>⚖️ The system automatically balances teacher workloads</li>"
        "<li>🚫 Conflicts are automatically prevented</li>"
        "</ul>"
    );
    
    helpBox.setStandardButtons(QMessageBox::Ok);
    helpBox.exec();
}

void MainWindow::onScheduleGenerated()
{
    m_centralStack->setCurrentWidget(m_scheduleView);
    m_statusLabel->setText("✅ Schedule generated successfully!");
}

void MainWindow::applyApplicationStyling()
{
    setStyleSheet(
        "QMainWindow {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #f8f9fa, stop:1 #e9ecef);"
        "}"
        "QMenuBar {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #3498db, stop:1 #2980b9);"
        "    color: white;"
        "    border: none;"
        "    padding: 4px;"
        "    font-weight: bold;"
        "}"
        "QMenuBar::item {"
        "    background: transparent;"
        "    padding: 8px 12px;"
        "    border-radius: 4px;"
        "}"
        "QMenuBar::item:selected {"
        "    background: rgba(255, 255, 255, 0.2);"
        "}"
        "QMenu {"
        "    background: white;"
        "    border: 2px solid #3498db;"
        "    border-radius: 6px;"
        "    padding: 5px;"
        "}"
        "QMenu::item {"
        "    padding: 8px 20px;"
        "    border-radius: 4px;"
        "}"
        "QMenu::item:selected {"
        "    background: #3498db;"
        "    color: white;"
        "}"
        "QStatusBar {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #ecf0f1, stop:1 #d5dbdb);"
        "    border-top: 1px solid #bdc3c7;"
        "    color: #2c3e50;"
        "    font-weight: bold;"
        "}"
        "QLabel#welcomeWidget {"
        "    background: white;"
        "    border-radius: 15px;"
        "    margin: 20px;"
        "    padding: 30px;"
        "    font-size: 16px;"
        "    color: #2c3e50;"
        "}"
    );
}
