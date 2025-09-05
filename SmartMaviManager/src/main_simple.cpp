#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QWidget window;
    window.setWindowTitle("Smart Mavi Manager Test");
    window.resize(400, 300);
    
    QVBoxLayout *layout = new QVBoxLayout(&window);
    
    QLabel *titleLabel = new QLabel("🎓 Smart Mavi Manager");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50; padding: 20px;");
    
    QPushButton *testButton = new QPushButton("🎯 Test Application");
    testButton->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3498db, stop:1 #2980b9);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 12px 24px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #5dade2, stop:1 #3498db);"
        "}"
    );
    
    QObject::connect(testButton, &QPushButton::clicked, [&]() {
        QMessageBox::information(&window, "Success! 🎉", 
            "🎊 Smart Mavi Manager is working correctly!\n\n"
            "✅ Qt5 GUI is functional\n"
            "✅ Event handling works\n"
            "✅ Styling is applied\n\n"
            "The core application framework is ready!");
    });
    
    layout->addWidget(titleLabel);
    layout->addWidget(testButton);
    layout->addStretch();
    
    window.show();
    
    return app.exec();
}
