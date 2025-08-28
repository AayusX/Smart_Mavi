#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QGroupBox>
#include <QTabWidget>
#include <QStyle>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QtCharts>
#include <QGraphicsOpacityEffect>
#include <QChartView>
#include <QChart>
#include <QBarSeries>
#include <QPieSeries>
#include <QLineSeries>
#include <QSplineSeries>
#include <QAreaSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QLegend>

class Database;
class Reports;

class StatCard : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit StatCard(const QString &title, const QString &subtitle, 
                     const QString &iconPath, const QColor &color, QWidget *parent = nullptr);
    
    int value() const { return m_value; }
    void setValue(int value);
    
    void setTrendValue(double trend);
    void updateData(int newValue, double trend = 0.0);
    void animateUpdate();

signals:
    void valueChanged(int value);
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void setupUI();
    void updateTrendDisplay();
    
    QString m_title;
    QString m_subtitle;
    QString m_iconPath;
    QColor m_color;
    
    QLabel *m_titleLabel;
    QLabel *m_valueLabel;
    QLabel *m_subtitleLabel;
    QLabel *m_iconLabel;
    QLabel *m_trendLabel;
    QFrame *m_iconFrame;
    
    int m_value;
    double m_trendValue;
    
    QPropertyAnimation *m_animation;
    QGraphicsOpacityEffect *m_opacityEffect;
};

class QuickActionCard : public QFrame
{
    Q_OBJECT

public:
    explicit QuickActionCard(const QString &title, const QString &description,
                           const QString &iconPath, QWidget *parent = nullptr);

signals:
    void actionTriggered();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void setupUI();
    
    QString m_title;
    QString m_description;
    QString m_iconPath;
    
    QLabel *m_titleLabel;
    QLabel *m_descLabel;
    QLabel *m_iconLabel;
    
    QPropertyAnimation *m_animation;
};

class NotificationWidget : public QFrame
{
    Q_OBJECT

public:
    enum Type {
        Info,
        Success,
        Warning,
        Error
    };

    explicit NotificationWidget(const QString &message, Type type = Info, QWidget *parent = nullptr);
    
    void show();
    void hide();

private slots:
    void autoHide();

private:
    void setupUI();
    QString getTypeColor() const;
    QString getTypeIcon() const;
    
    QString m_message;
    Type m_type;
    QTimer *m_autoHideTimer;
    QPropertyAnimation *m_animation;
    QGraphicsOpacityEffect *m_opacityEffect;
    
    QLabel *m_messageLabel;
    QLabel *m_iconLabel;
    QPushButton *m_closeButton;
};

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(Database *database, QWidget *parent = nullptr);
    ~Dashboard();

    void refreshData();
    void updateStatistics();

public slots:
    void onThemeChanged(const QString &theme);
    void onWindowResized(const QSize &size);

signals:
    void addTeacherRequested();
    void addStudentRequested();
    void addClassRequested();
    void markAttendanceRequested();
    void viewReportsRequested();
    void openSettingsRequested();

private slots:
    void refreshStatistics();
    void onQuickActionTriggered();
    void showAttendanceChart();
    void showPerformanceChart();
    void showTrendChart();

private:
    void setupUI();
    void setupStatCards();
    void setupQuickActions();
    void setupCharts();
    void setupNotificationArea();
    void setupResponsiveLayout();
    
    void createAttendanceChart();
    void createPerformanceChart();
    void createTrendChart();
    void createSystemOverviewChart();
    
    void updateAttendanceChart();
    void updatePerformanceChart();
    void updateTrendChart();
    
    void showNotification(const QString &message, NotificationWidget::Type type = NotificationWidget::Info);
    void animateStatCards();
    void adjustLayoutForScreenSize();
    
    Database *m_database;
    Reports *m_reports;
    
    // Layout components
    QGridLayout *m_mainLayout;
    QHBoxLayout *m_statLayout;
    QGridLayout *m_quickActionLayout;
    QVBoxLayout *m_chartLayout;
    QVBoxLayout *m_notificationLayout;
    
    // Stat cards
    StatCard *m_studentsCard;
    StatCard *m_teachersCard;
    StatCard *m_classesCard;
    StatCard *m_attendanceCard;
    
    // Quick action cards
    QList<QuickActionCard*> m_quickActionCards;
    
    // Charts
    QChartView *m_attendanceChartView;
    QChartView *m_performanceChartView;
    QChartView *m_trendChartView;
    QChartView *m_overviewChartView;
    
    QChart *m_attendanceChart;
    QChart *m_performanceChart;
    QChart *m_trendChart;
    QChart *m_overviewChart;
    
    // Notification system
    QWidget *m_notificationArea;
    QList<NotificationWidget*> m_notifications;
    
    // Data refresh timer
    QTimer *m_refreshTimer;
    
    // Animation system
    QPropertyAnimation *m_fadeAnimation;
    QGraphicsOpacityEffect *m_fadeEffect;
    
    // Responsive design
    bool m_isMobileLayout;
    int m_currentScreenWidth;
    int m_currentScreenHeight;
    
    // Theme support
    QString m_currentTheme;
    bool m_isDarkTheme;
    
    // Statistics data
    struct Statistics {
        int totalStudents;
        int totalTeachers;
        int totalClasses;
        int presentToday;
        int absentToday;
        double attendanceRate;
        double performanceAverage;
        int newStudentsThisMonth;
        int newTeachersThisMonth;
        QList<QPair<QString, int>> monthlyAttendance;
        QList<QPair<QString, double>> classPerformance;
        QList<QPair<QString, int>> weeklyTrends;
    } m_stats;
};

// Animation helper class
class DashboardAnimator : public QObject
{
    Q_OBJECT

public:
    explicit DashboardAnimator(QObject *parent = nullptr);
    
    void fadeIn(QWidget *widget, int duration = 300);
    void fadeOut(QWidget *widget, int duration = 300);
    void slideIn(QWidget *widget, const QPoint &start, const QPoint &end, int duration = 500);
    void bounceIn(QWidget *widget, int duration = 600);
    void pulseEffect(QWidget *widget, int duration = 1000);
    
private slots:
    void onAnimationFinished();
    
private:
    QList<QPropertyAnimation*> m_activeAnimations;
    QGraphicsOpacityEffect* createOpacityEffect(QWidget *widget);
};

#endif // DASHBOARD_H
