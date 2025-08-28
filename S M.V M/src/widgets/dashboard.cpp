#include "widgets/dashboard.h"
#include "database/database.h"
#include "reports/reports.h"
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QFont>
#include <QFontMetrics>
#include <QPixmap>
#include <QIcon>
#include <QDateTime>
#include <QScrollArea>
#include <QSplitter>
#include <QRandomGenerator>
#include <cmath>

// StatCard Implementation
StatCard::StatCard(const QString &title, const QString &subtitle, 
                  const QString &iconPath, const QColor &color, QWidget *parent)
    : QFrame(parent)
    , m_title(title)
    , m_subtitle(subtitle)
    , m_iconPath(iconPath)
    , m_color(color)
    , m_value(0)
    , m_trendValue(0.0)
{
    setObjectName("StatCard");
    setProperty("class", "dashboard-card");
    setFixedSize(280, 160);
    setCursor(Qt::PointingHandCursor);
    
    setupUI();
    
    // Setup animation
    m_animation = new QPropertyAnimation(this, "value");
    m_animation->setDuration(800);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    
    // Setup opacity effect for hover
    m_opacityEffect = new QGraphicsOpacityEffect(this);
    m_opacityEffect->setOpacity(1.0);
    setGraphicsEffect(m_opacityEffect);
}

void StatCard::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(20, 16, 20, 16);
    
    // Header with icon and trend
    QHBoxLayout *headerLayout = new QHBoxLayout();
    
    // Icon frame
    m_iconFrame = new QFrame();
    m_iconFrame->setFixedSize(48, 48);
    m_iconFrame->setStyleSheet(QString(
        "background: %1; border-radius: 24px; border: 2px solid %2;")
        .arg(m_color.lighter(150).name())
        .arg(m_color.name()));
    
    m_iconLabel = new QLabel(m_iconFrame);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setFixedSize(44, 44);
    m_iconLabel->setStyleSheet(QString("color: %1; font-size: 24px; font-weight: bold;")
                              .arg(m_color.name()));
    m_iconLabel->setText("📊"); // Default icon, will be replaced with actual icons
    
    m_trendLabel = new QLabel();
    m_trendLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    m_trendLabel->setStyleSheet("color: #28a745; font-size: 12px; font-weight: 600;");
    
    headerLayout->addWidget(m_iconFrame);
    headerLayout->addStretch();
    headerLayout->addWidget(m_trendLabel);
    
    // Value display
    m_valueLabel = new QLabel("0");
    m_valueLabel->setAlignment(Qt::AlignLeft);
    m_valueLabel->setStyleSheet("font-size: 36px; font-weight: 700; color: #2c3e50; margin: 8px 0;");
    
    // Title
    m_titleLabel = new QLabel(m_title);
    m_titleLabel->setStyleSheet("font-size: 16px; font-weight: 600; color: #495057;");
    
    // Subtitle
    m_subtitleLabel = new QLabel(m_subtitle);
    m_subtitleLabel->setStyleSheet("font-size: 12px; color: #6c757d; margin-top: 4px;");
    m_subtitleLabel->setWordWrap(true);
    
    layout->addLayout(headerLayout);
    layout->addWidget(m_valueLabel);
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_subtitleLabel);
    layout->addStretch();
}

void StatCard::setValue(int value)
{
    if (m_value != value) {
        m_value = value;
        m_valueLabel->setText(QString::number(value));
        emit valueChanged(value);
    }
}

void StatCard::setTrendValue(double trend)
{
    m_trendValue = trend;
    updateTrendDisplay();
}

void StatCard::updateData(int newValue, double trend)
{
    setTrendValue(trend);
    
    // Animate value change
    m_animation->setStartValue(m_value);
    m_animation->setEndValue(newValue);
    m_animation->start();
}

void StatCard::updateTrendDisplay()
{
    QString trendText;
    QString trendColor;
    
    if (m_trendValue > 0) {
        trendText = QString("↗ +%1%").arg(QString::number(m_trendValue, 'f', 1));
        trendColor = "#28a745";
    } else if (m_trendValue < 0) {
        trendText = QString("↘ %1%").arg(QString::number(m_trendValue, 'f', 1));
        trendColor = "#dc3545";
    } else {
        trendText = "→ 0%";
        trendColor = "#6c757d";
    }
    
    m_trendLabel->setText(trendText);
    m_trendLabel->setStyleSheet(QString("color: %1; font-size: 12px; font-weight: 600;").arg(trendColor));
}

void StatCard::animateUpdate()
{
    // Pulse effect
    QPropertyAnimation *pulseAnimation = new QPropertyAnimation(m_opacityEffect, "opacity");
    pulseAnimation->setDuration(300);
    pulseAnimation->setStartValue(1.0);
    pulseAnimation->setEndValue(0.7);
    pulseAnimation->setDirection(QAbstractAnimation::Forward);
    pulseAnimation->setLoopCount(2);
    pulseAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void StatCard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        animateUpdate();
        emit clicked();
    }
    QFrame::mousePressEvent(event);
}

void StatCard::enterEvent(QEnterEvent *event)
{
    setStyleSheet(property("class").toString() + " { transform: scale(1.02); }");
    QFrame::enterEvent(event);
}

void StatCard::leaveEvent(QEvent *event)
{
    setStyleSheet("");
    QFrame::leaveEvent(event);
}

// QuickActionCard Implementation
QuickActionCard::QuickActionCard(const QString &title, const QString &description,
                                const QString &iconPath, QWidget *parent)
    : QFrame(parent)
    , m_title(title)
    , m_description(description)
    , m_iconPath(iconPath)
{
    setObjectName("QuickActionCard");
    setProperty("class", "card");
    setFixedSize(200, 120);
    setCursor(Qt::PointingHandCursor);
    
    setupUI();
    
    m_animation = new QPropertyAnimation(this, "pos");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
}

void QuickActionCard::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(16, 16, 16, 16);
    
    m_iconLabel = new QLabel();
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 32px; color: #007bff; margin-bottom: 8px;");
    m_iconLabel->setText("⚡"); // Default icon
    
    m_titleLabel = new QLabel(m_title);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 14px; font-weight: 600; color: #2c3e50; margin: 4px 0;");
    
    m_descLabel = new QLabel(m_description);
    m_descLabel->setAlignment(Qt::AlignCenter);
    m_descLabel->setStyleSheet("font-size: 11px; color: #6c757d; margin: 0;");
    m_descLabel->setWordWrap(true);
    
    layout->addWidget(m_iconLabel);
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_descLabel);
    layout->addStretch();
}

void QuickActionCard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit actionTriggered();
    }
    QFrame::mousePressEvent(event);
}

void QuickActionCard::enterEvent(QEnterEvent *event)
{
    setStyleSheet("QFrame { border: 2px solid #007bff; background: #f8f9ff; }");
    QFrame::enterEvent(event);
}

void QuickActionCard::leaveEvent(QEvent *event)
{
    setStyleSheet("");
    QFrame::leaveEvent(event);
}

// NotificationWidget Implementation
NotificationWidget::NotificationWidget(const QString &message, Type type, QWidget *parent)
    : QFrame(parent)
    , m_message(message)
    , m_type(type)
{
    setObjectName("NotificationWidget");
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedHeight(60);
    
    setupUI();
    
    // Auto-hide timer
    m_autoHideTimer = new QTimer(this);
    m_autoHideTimer->setSingleShot(true);
    m_autoHideTimer->setInterval(5000); // 5 seconds
    connect(m_autoHideTimer, &QTimer::timeout, this, &NotificationWidget::autoHide);
    
    // Setup animation
    m_opacityEffect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(m_opacityEffect);
    
    m_animation = new QPropertyAnimation(m_opacityEffect, "opacity");
    m_animation->setDuration(300);
}

void NotificationWidget::setupUI()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 12, 16, 12);
    layout->setSpacing(12);
    
    // Icon
    m_iconLabel = new QLabel();
    m_iconLabel->setFixedSize(24, 24);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 18px;");
    m_iconLabel->setText(getTypeIcon());
    
    // Message
    m_messageLabel = new QLabel(m_message);
    m_messageLabel->setWordWrap(true);
    m_messageLabel->setStyleSheet("font-size: 14px; font-weight: 500;");
    
    // Close button
    m_closeButton = new QPushButton("×");
    m_closeButton->setFixedSize(24, 24);
    m_closeButton->setStyleSheet("QPushButton { border: none; background: transparent; "
                                "font-size: 18px; font-weight: bold; color: #666; }"
                                "QPushButton:hover { background: rgba(0,0,0,0.1); border-radius: 12px; }");
    connect(m_closeButton, &QPushButton::clicked, this, &NotificationWidget::hide);
    
    layout->addWidget(m_iconLabel);
    layout->addWidget(m_messageLabel, 1);
    layout->addWidget(m_closeButton);
    
    // Set background color based on type
    setStyleSheet(QString("QFrame { background: %1; border-radius: 8px; border: 1px solid %2; }")
                 .arg(getTypeColor())
                 .arg(getTypeColor()));
}

QString NotificationWidget::getTypeIcon() const
{
    switch (m_type) {
        case Success: return "✅";
        case Warning: return "⚠️";
        case Error: return "❌";
        case Info:
        default: return "ℹ️";
    }
}

QString NotificationWidget::getTypeColor() const
{
    switch (m_type) {
        case Success: return "#d4edda";
        case Warning: return "#fff3cd";
        case Error: return "#f8d7da";
        case Info:
        default: return "#cce5ff";
    }
}

void NotificationWidget::show()
{
    m_animation->setStartValue(0.0);
    m_animation->setEndValue(1.0);
    m_animation->start();
    m_autoHideTimer->start();
    QWidget::show();
}

void NotificationWidget::hide()
{
    m_animation->setStartValue(1.0);
    m_animation->setEndValue(0.0);
    connect(m_animation, &QPropertyAnimation::finished, this, &QWidget::close);
    m_animation->start();
}

void NotificationWidget::autoHide()
{
    hide();
}

// Dashboard Implementation
Dashboard::Dashboard(Database *database, QWidget *parent)
    : QWidget(parent)
    , m_database(database)
    , m_isMobileLayout(false)
    , m_currentTheme("light")
    , m_isDarkTheme(false)
{
    setObjectName("Dashboard");
    
    // Initialize reports system
    m_reports = new Reports(database, this);
    
    // Setup refresh timer
    m_refreshTimer = new QTimer(this);
    m_refreshTimer->setInterval(30000); // Refresh every 30 seconds
    connect(m_refreshTimer, &QTimer::timeout, this, &Dashboard::refreshStatistics);
    m_refreshTimer->start();
    
    setupUI();
    refreshData();
    
    // Initial animation
    QTimer::singleShot(100, this, &Dashboard::animateStatCards);
}

Dashboard::~Dashboard()
{
    if (m_refreshTimer) {
        m_refreshTimer->stop();
    }
}

void Dashboard::setupUI()
{
    m_mainLayout = new QGridLayout(this);
    m_mainLayout->setSpacing(16);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    
    setupStatCards();
    setupQuickActions();
    setupCharts();
    setupNotificationArea();
    setupResponsiveLayout();
}

void Dashboard::setupStatCards()
{
    // Create stat cards
    m_studentsCard = new StatCard("Total Students", "Enrolled in all classes", 
                                 ":/icons/students.png", QColor("#007bff"), this);
    m_teachersCard = new StatCard("Total Teachers", "Active faculty members", 
                                 ":/icons/teachers.png", QColor("#28a745"), this);
    m_classesCard = new StatCard("Active Classes", "Currently running", 
                                ":/icons/classes.png", QColor("#ffc107"), this);
    m_attendanceCard = new StatCard("Today's Attendance", "Present students", 
                                   ":/icons/attendance.png", QColor("#17a2b8"), this);
    
    // Connect signals
    connect(m_studentsCard, &StatCard::clicked, this, &Dashboard::addStudentRequested);
    connect(m_teachersCard, &StatCard::clicked, this, &Dashboard::addTeacherRequested);
    connect(m_classesCard, &StatCard::clicked, this, &Dashboard::addClassRequested);
    connect(m_attendanceCard, &StatCard::clicked, this, &Dashboard::markAttendanceRequested);
    
    // Add to layout
    m_statLayout = new QHBoxLayout();
    m_statLayout->addWidget(m_studentsCard);
    m_statLayout->addWidget(m_teachersCard);
    m_statLayout->addWidget(m_classesCard);
    m_statLayout->addWidget(m_attendanceCard);
    
    m_mainLayout->addLayout(m_statLayout, 0, 0, 1, 2);
}

void Dashboard::setupQuickActions()
{
    QGroupBox *quickActionGroup = new QGroupBox("Quick Actions");
    quickActionGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: 600; }");
    
    m_quickActionLayout = new QGridLayout(quickActionGroup);
    m_quickActionLayout->setSpacing(12);
    
    // Create quick action cards
    QStringList actionTitles = {"Add Student", "Add Teacher", "Mark Attendance", "View Reports", "Settings", "Backup Data"};
    QStringList actionDescs = {"Register new student", "Add faculty member", "Take today's attendance", 
                              "Generate reports", "System configuration", "Backup database"};
    QStringList actionIcons = {"👨‍🎓", "👩‍🏫", "📝", "📊", "⚙️", "💾"};
    
    for (int i = 0; i < actionTitles.size(); ++i) {
        QuickActionCard *card = new QuickActionCard(actionTitles[i], actionDescs[i], actionIcons[i], this);
        m_quickActionCards.append(card);
        
        // Connect to appropriate signals
        connect(card, &QuickActionCard::actionTriggered, this, &Dashboard::onQuickActionTriggered);
        
        int row = i / 3;
        int col = i % 3;
        m_quickActionLayout->addWidget(card, row, col);
    }
    
    m_mainLayout->addWidget(quickActionGroup, 1, 0);
}

void Dashboard::setupCharts()
{
    // Create chart container
    QGroupBox *chartGroup = new QGroupBox("Analytics & Reports");
    chartGroup->setStyleSheet("QGroupBox { font-size: 16px; font-weight: 600; }");
    
    m_chartLayout = new QVBoxLayout(chartGroup);
    
    // Chart tabs
    QTabWidget *chartTabs = new QTabWidget();
    
    createAttendanceChart();
    createPerformanceChart();
    createTrendChart();
    createSystemOverviewChart();
    
    chartTabs->addTab(m_attendanceChartView, "📊 Attendance");
    chartTabs->addTab(m_performanceChartView, "📈 Performance");
    chartTabs->addTab(m_trendChartView, "📉 Trends");
    chartTabs->addTab(m_overviewChartView, "🎯 Overview");
    
    m_chartLayout->addWidget(chartTabs);
    
    m_mainLayout->addWidget(chartGroup, 1, 1);
}

void Dashboard::setupNotificationArea()
{
    m_notificationArea = new QWidget();
    m_notificationLayout = new QVBoxLayout(m_notificationArea);
    m_notificationLayout->setSpacing(8);
    m_notificationLayout->setContentsMargins(0, 0, 0, 0);
    
    // Add notification area to main layout
    m_mainLayout->addWidget(m_notificationArea, 2, 0, 1, 2);
}

void Dashboard::setupResponsiveLayout()
{
    // Get screen size
    QScreen *screen = QApplication::primaryScreen();
    QSize screenSize = screen->size();
    m_currentScreenWidth = screenSize.width();
    m_currentScreenHeight = screenSize.height();
    
    adjustLayoutForScreenSize();
}

void Dashboard::createAttendanceChart()
{
    m_attendanceChart = new QChart();
    m_attendanceChart->setTitle("Weekly Attendance Overview");
    m_attendanceChart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create bar series for attendance data
    QBarSeries *series = new QBarSeries();
    
    QBarSet *presentSet = new QBarSet("Present");
    QBarSet *absentSet = new QBarSet("Absent");
    QBarSet *lateSet = new QBarSet("Late");
    
    // Sample data for the week
    *presentSet << 120 << 115 << 125 << 130 << 118;
    *absentSet << 8 << 12 << 5 << 3 << 10;
    *lateSet << 2 << 3 << 0 << 1 << 2;
    
    presentSet->setColor(QColor("#28a745"));
    absentSet->setColor(QColor("#dc3545"));
    lateSet->setColor(QColor("#ffc107"));
    
    series->append(presentSet);
    series->append(absentSet);
    series->append(lateSet);
    
    m_attendanceChart->addSeries(series);
    
    // Create axes
    QStringList categories = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    m_attendanceChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 150);
    axisY->setTitleText("Number of Students");
    m_attendanceChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    // Style the chart
    m_attendanceChart->legend()->setVisible(true);
    m_attendanceChart->legend()->setAlignment(Qt::AlignBottom);
    
    m_attendanceChartView = new QChartView(m_attendanceChart);
    m_attendanceChartView->setRenderHint(QPainter::Antialiasing);
    m_attendanceChartView->setMinimumHeight(300);
}

void Dashboard::createPerformanceChart()
{
    m_performanceChart = new QChart();
    m_performanceChart->setTitle("Class Performance Comparison");
    m_performanceChart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create pie series for performance data
    QPieSeries *series = new QPieSeries();
    
    // Sample performance data
    series->append("Excellent (90-100%)", 25);
    series->append("Good (80-89%)", 35);
    series->append("Average (70-79%)", 25);
    series->append("Below Average (<70%)", 15);
    
    // Color the slices
    QList<QColor> colors = {QColor("#28a745"), QColor("#007bff"), QColor("#ffc107"), QColor("#dc3545")};
    for (int i = 0; i < series->slices().size(); ++i) {
        series->slices().at(i)->setBrush(colors[i]);
        series->slices().at(i)->setLabelVisible(true);
    }
    
    m_performanceChart->addSeries(series);
    m_performanceChart->legend()->setVisible(true);
    m_performanceChart->legend()->setAlignment(Qt::AlignRight);
    
    m_performanceChartView = new QChartView(m_performanceChart);
    m_performanceChartView->setRenderHint(QPainter::Antialiasing);
    m_performanceChartView->setMinimumHeight(300);
}

void Dashboard::createTrendChart()
{
    m_trendChart = new QChart();
    m_trendChart->setTitle("Monthly Attendance Trends");
    m_trendChart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create line series for trends
    QSplineSeries *series = new QSplineSeries();
    series->setName("Attendance Rate %");
    series->setColor(QColor("#007bff"));
    
    // Sample trend data for past 6 months
    QDateTime currentDate = QDateTime::currentDateTime();
    for (int i = -6; i <= 0; ++i) {
        QDateTime date = currentDate.addMonths(i);
        double attendance = 85 + (QRandomGenerator::global()->bounded(15)); // 85-100%
        series->append(date.toMSecsSinceEpoch(), attendance);
    }
    
    m_trendChart->addSeries(series);
    
    // Create axes
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("MMM");
    axisX->setTitleText("Month");
    m_trendChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%.0f%%");
    axisY->setTitleText("Attendance Rate");
    axisY->setRange(0, 100);
    m_trendChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    m_trendChartView = new QChartView(m_trendChart);
    m_trendChartView->setRenderHint(QPainter::Antialiasing);
    m_trendChartView->setMinimumHeight(300);
}

void Dashboard::createSystemOverviewChart()
{
    m_overviewChart = new QChart();
    m_overviewChart->setTitle("System Overview - Current Month");
    m_overviewChart->setAnimationOptions(QChart::SeriesAnimations);
    
    // Create area series for overview
    QAreaSeries *series = new QAreaSeries();
    series->setName("Daily Activity");
    
    QLineSeries *upperSeries = new QLineSeries();
    QLineSeries *lowerSeries = new QLineSeries();
    
    // Sample data for the current month (daily activity)
    QDate today = QDate::currentDate();
    for (int i = 1; i <= today.day(); ++i) {
        QDate date(today.year(), today.month(), i);
        double activity = 50 + (QRandomGenerator::global()->bounded(50)); // 50-100
        upperSeries->append(i, activity);
        lowerSeries->append(i, 20); // Base level
    }
    
    series->setUpperSeries(upperSeries);
    series->setLowerSeries(lowerSeries);
    series->setColor(QColor("#007bff"));
    
    m_overviewChart->addSeries(series);
    
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Day of Month");
    axisX->setRange(1, 31);
    m_overviewChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Activity Level");
    axisY->setRange(0, 100);
    m_overviewChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    m_overviewChartView = new QChartView(m_overviewChart);
    m_overviewChartView->setRenderHint(QPainter::Antialiasing);
    m_overviewChartView->setMinimumHeight(300);
}

void Dashboard::refreshData()
{
    updateStatistics();
    updateAttendanceChart();
    updatePerformanceChart();
    updateTrendChart();
}

void Dashboard::updateStatistics()
{
    if (!m_database) return;
    
    // Get real data from database
    m_stats.totalStudents = m_database->getAllStudents().size();
    m_stats.totalTeachers = m_database->getAllTeachers().size();
    m_stats.totalClasses = m_database->getAllClasses().size();
    
    // Calculate today's attendance (mock data for now)
    m_stats.presentToday = static_cast<int>(m_stats.totalStudents * 0.92); // 92% attendance
    m_stats.absentToday = m_stats.totalStudents - m_stats.presentToday;
    m_stats.attendanceRate = (double)m_stats.presentToday / m_stats.totalStudents * 100.0;
    
    // Update stat cards with animation
    m_studentsCard->updateData(m_stats.totalStudents, 5.2); // 5.2% increase
    m_teachersCard->updateData(m_stats.totalTeachers, 0.0); // No change
    m_classesCard->updateData(m_stats.totalClasses, 8.3); // 8.3% increase
    m_attendanceCard->updateData(m_stats.presentToday, 2.1); // 2.1% increase
    
    // Show notification for low attendance
    if (m_stats.attendanceRate < 85.0) {
        showNotification(QString("Attendance below 85%: %1%").arg(QString::number(m_stats.attendanceRate, 'f', 1)), 
                        NotificationWidget::Warning);
    }
}

void Dashboard::refreshStatistics()
{
    updateStatistics();
    
    // Add a subtle notification
    showNotification("Dashboard refreshed", NotificationWidget::Info);
}

void Dashboard::onQuickActionTriggered()
{
    QuickActionCard *card = qobject_cast<QuickActionCard*>(sender());
    if (!card) return;
    
    // Emit appropriate signal based on the card
    if (card == m_quickActionCards[0]) {
        emit addStudentRequested();
    } else if (card == m_quickActionCards[1]) {
        emit addTeacherRequested();
    } else if (card == m_quickActionCards[2]) {
        emit markAttendanceRequested();
    } else if (card == m_quickActionCards[3]) {
        emit viewReportsRequested();
    } else if (card == m_quickActionCards[4]) {
        emit openSettingsRequested();
    }
    
    showNotification("Action triggered: " + card->property("title").toString(), NotificationWidget::Success);
}

void Dashboard::showAttendanceChart()
{
    // Switch to attendance chart tab and highlight it
    updateAttendanceChart();
    animateStatCards();
}

void Dashboard::showPerformanceChart()
{
    updatePerformanceChart();
}

void Dashboard::showTrendChart()
{
    updateTrendChart();
}

void Dashboard::updateAttendanceChart()
{
    // Update with fresh data
    // This would typically fetch real data from database
}

void Dashboard::updatePerformanceChart()
{
    // Update performance chart with current data
}

void Dashboard::updateTrendChart()
{
    // Update trend chart with latest trends
}

void Dashboard::showNotification(const QString &message, NotificationWidget::Type type)
{
    NotificationWidget *notification = new NotificationWidget(message, type, m_notificationArea);
    m_notifications.append(notification);
    
    // Position notification
    int yPos = m_notifications.size() * 70;
    notification->move(0, yPos);
    notification->show();
    
    // Remove old notifications if too many
    if (m_notifications.size() > 5) {
        NotificationWidget *oldNotification = m_notifications.takeFirst();
        oldNotification->hide();
    }
}

void Dashboard::animateStatCards()
{
    // Animate stat cards with staggered timing
    QList<StatCard*> cards = {m_studentsCard, m_teachersCard, m_classesCard, m_attendanceCard};
    
    for (int i = 0; i < cards.size(); ++i) {
        QTimer::singleShot(i * 100, cards[i], &StatCard::animateUpdate);
    }
}

void Dashboard::adjustLayoutForScreenSize()
{
    // Adjust layout based on screen size
    if (m_currentScreenWidth < 1024) {
        // Mobile/tablet layout
        m_isMobileLayout = true;
        
        // Stack stat cards vertically on small screens
        for (int i = 0; i < 4; ++i) {
            m_statLayout->removeWidget(m_statLayout->itemAt(0)->widget());
        }
        
        // Reorganize in 2x2 grid
        QGridLayout *mobileStatLayout = new QGridLayout();
        mobileStatLayout->addWidget(m_studentsCard, 0, 0);
        mobileStatLayout->addWidget(m_teachersCard, 0, 1);
        mobileStatLayout->addWidget(m_classesCard, 1, 0);
        mobileStatLayout->addWidget(m_attendanceCard, 1, 1);
        
    } else {
        // Desktop layout (already set up)
        m_isMobileLayout = false;
    }
}

void Dashboard::onThemeChanged(const QString &theme)
{
    m_currentTheme = theme;
    m_isDarkTheme = (theme == "dark");
    
    // Update all components for new theme
    QString cardClass = m_isDarkTheme ? "dashboard-card-dark" : "dashboard-card";
    
    m_studentsCard->setProperty("class", cardClass);
    m_teachersCard->setProperty("class", cardClass);
    m_classesCard->setProperty("class", cardClass);
    m_attendanceCard->setProperty("class", cardClass);
    
    // Update chart themes
    QChart::ChartTheme chartTheme = m_isDarkTheme ? QChart::ChartThemeDark : QChart::ChartThemeLight;
    m_attendanceChart->setTheme(chartTheme);
    m_performanceChart->setTheme(chartTheme);
    m_trendChart->setTheme(chartTheme);
    m_overviewChart->setTheme(chartTheme);
    
    // Force style update
    style()->polish(this);
    update();
}

void Dashboard::onWindowResized(const QSize &size)
{
    m_currentScreenWidth = size.width();
    m_currentScreenHeight = size.height();
    adjustLayoutForScreenSize();
}

// DashboardAnimator Implementation
DashboardAnimator::DashboardAnimator(QObject *parent)
    : QObject(parent)
{
}

void DashboardAnimator::fadeIn(QWidget *widget, int duration)
{
    QGraphicsOpacityEffect *effect = createOpacityEffect(widget);
    
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    
    connect(animation, &QPropertyAnimation::finished, this, &DashboardAnimator::onAnimationFinished);
    m_activeAnimations.append(animation);
    
    animation->start();
}

void DashboardAnimator::fadeOut(QWidget *widget, int duration)
{
    QGraphicsOpacityEffect *effect = createOpacityEffect(widget);
    
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::InCubic);
    
    connect(animation, &QPropertyAnimation::finished, this, &DashboardAnimator::onAnimationFinished);
    m_activeAnimations.append(animation);
    
    animation->start();
}

void DashboardAnimator::slideIn(QWidget *widget, const QPoint &start, const QPoint &end, int duration)
{
    QPropertyAnimation *animation = new QPropertyAnimation(widget, "pos");
    animation->setDuration(duration);
    animation->setStartValue(start);
    animation->setEndValue(end);
    animation->setEasingCurve(QEasingCurve::OutBack);
    
    connect(animation, &QPropertyAnimation::finished, this, &DashboardAnimator::onAnimationFinished);
    m_activeAnimations.append(animation);
    
    animation->start();
}

void DashboardAnimator::bounceIn(QWidget *widget, int duration)
{
    QPropertyAnimation *animation = new QPropertyAnimation(widget, "geometry");
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    
    QRect originalGeometry = widget->geometry();
    QRect startGeometry = originalGeometry;
    startGeometry.setSize(QSize(0, 0));
    startGeometry.moveCenter(originalGeometry.center());
    
    animation->setStartValue(startGeometry);
    animation->setEndValue(originalGeometry);
    
    connect(animation, &QPropertyAnimation::finished, this, &DashboardAnimator::onAnimationFinished);
    m_activeAnimations.append(animation);
    
    animation->start();
}

void DashboardAnimator::pulseEffect(QWidget *widget, int duration)
{
    QGraphicsOpacityEffect *effect = createOpacityEffect(widget);
    
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setKeyValueAt(0.5, 0.7);
    animation->setEndValue(1.0);
    animation->setLoopCount(-1); // Infinite loop
    animation->setEasingCurve(QEasingCurve::InOutSine);
    
    m_activeAnimations.append(animation);
    animation->start();
}

void DashboardAnimator::onAnimationFinished()
{
    QPropertyAnimation *animation = qobject_cast<QPropertyAnimation*>(sender());
    if (animation) {
        m_activeAnimations.removeAll(animation);
        animation->deleteLater();
    }
}

QGraphicsOpacityEffect* DashboardAnimator::createOpacityEffect(QWidget *widget)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    widget->setGraphicsEffect(effect);
    return effect;
}

