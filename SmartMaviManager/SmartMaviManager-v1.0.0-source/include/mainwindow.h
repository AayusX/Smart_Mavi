#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QStackedWidget>
#include <QLabel>
#include <QProgressDialog>
#include <QTimer>
#include "surveydialog.h"
#include "scheduleview.h"
#include "schedulegenerator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void newSchedule();
    void openSchedule();
    void saveSchedule();
    void aboutApp();
    void showHelp();
    void onScheduleGenerated();
    void onRegenerateRequested();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void applyApplicationStyling();
    void showWelcomeScreen();
    void generateScheduleWithProgress();

    QStackedWidget *m_centralStack;
    QLabel *m_welcomeWidget;
    ScheduleView *m_scheduleView;
    
    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_exitAction;
    QAction *m_aboutAction;
    QAction *m_helpAction;
    
    ScheduleGenerator m_generator;
    ScheduleConfig m_currentConfig;
    Schedule m_currentSchedule;
    
    QLabel *m_statusLabel;
    QProgressDialog *m_progressDialog;
};

#endif // MAINWINDOW_H
