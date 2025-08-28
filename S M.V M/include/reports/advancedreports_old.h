#ifndef ADVANCEDREPORTS_H
#define ADVANCEDREPORTS_H

#include <QObject>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class CommunicationManager;

class AdvancedReports : public Reports
{
    Q_OBJECT

public:
    enum ReportFormat {
        PDF = 0,
        Excel = 1,
        Word = 2,
        PowerPoint = 3,
        CSV = 4,
        HTML = 5,
        JSON = 6
    };

    enum ReportTemplate {
        Standard = 0,
        Detailed = 1,
        Summary = 2,
        Executive = 3,
        Academic = 4,
        Administrative = 5,
        Custom = 6
    };

    explicit AdvancedReports(Database *database, QObject *parent = nullptr);
    ~AdvancedReports();

    // Enhanced report generation
    QString generateAdvancedTeacherReport(const QDate &startDate, const QDate &endDate, 
                                        ReportTemplate template = Standard);
    QString generateAdvancedStudentReport(int classId, const QDate &startDate, const QDate &endDate,
                                        ReportTemplate template = Standard);
    QString generateAdvancedAttendanceReport(int classId, const QDate &date, 
                                           ReportTemplate template = Standard);
    QString generateAdvancedClassReport(int classId, const QDate &startDate, const QDate &endDate,
                                      ReportTemplate template = Standard);
    QString generateAdvancedSummaryReport(const QDate &startDate, const QDate &endDate,
                                        ReportTemplate template = Executive);

    // Specialized reports
    QString generatePerformanceReport(int classId, const QDate &startDate, const QDate &endDate);
    QString generateParentReport(int studentId, const QDate &startDate, const QDate &endDate);
    QString generateTeacherWorkloadReport(int teacherId, const QDate &startDate, const QDate &endDate);
    QString generateFinancialReport(const QDate &startDate, const QDate &endDate);
    QString generateComplianceReport(const QDate &startDate, const QDate &endDate);
    QString generateCustomReport(const QJsonObject &parameters);

    // Advanced export functions
    bool exportToPDF(const QString &content, const QString &filename, ReportTemplate template = Standard);
    bool exportToWord(const QString &content, const QString &filename);
    bool exportToPowerPoint(const QString &content, const QString &filename);
    bool exportToExcelAdvanced(const QString &content, const QString &filename);
    bool exportToJSON(const QJsonObject &data, const QString &filename);

    // Email reports
    bool emailReport(const QString &content, const QString &recipient, const QString &subject,
                    ReportFormat format = PDF, const QString &template = "");
    bool scheduleReport(const QString &reportType, const QJsonObject &parameters, 
                       const QDateTime &scheduleTime, const QString &recipient = "");

    // Custom report builder
    void addReportSection(const QString &sectionName, const QString &content);
    void addChart(const QString &chartName, QChart *chart);
    void addTable(const QString &tableName, const QJsonArray &data);
    void addImage(const QString &imageName, const QPixmap &image);
    QString buildCustomReport(const QString &templateName = "");

    // Report analytics
    struct ReportMetrics {
        QDateTime generationTime;
        int pageCount;
        int chartCount;
        int tableCount;
        int imageCount;
        QString format;
        QString recipient;
        bool emailSent;
        QDateTime emailSentTime;
    };

    QList<ReportMetrics> getReportHistory();
    void trackReportGeneration(const ReportMetrics &metrics);

    // Template management
    void saveReportTemplate(const QString &name, const QString &htmlTemplate, const QJsonObject &settings);
    QString getReportTemplate(const QString &name);
    QStringList getReportTemplateNames();
    void deleteReportTemplate(const QString &name);

    // Batch processing
    void generateBatchReports(const QJsonArray &reportRequests);
    void scheduleBatchReports(const QJsonArray &reportRequests, const QDateTime &scheduleTime);

signals:
    void reportGenerated(const QString &filename, bool success);
    void batchReportCompleted(int successful, int failed);
    void reportEmailSent(const QString &recipient, bool success);
    void reportScheduled(const QString &reportId);

private slots:
    void onReportGenerationProgress(int percentage);
    void onBatchReportTimer();

private:
    void initializeTemplates();
    void setupReportEngine();
    QString generateHTMLReport(const QString &content, ReportTemplate template);
    QString applyReportTemplate(const QString &content, const QString &templateName);
    
    // PDF generation
    bool generatePDFFromHTML(const QString &html, const QString &filename);
    void configurePDFPrinter(QPrinter *printer, ReportTemplate template);
    
    // Chart to image conversion
    QPixmap chartToPixmap(QChart *chart, const QSize &size = QSize(800, 600));
    QString chartToBase64(QChart *chart, const QSize &size = QSize(800, 600));
    
    // Template processing
    QString processTemplate(const QString &template, const QJsonObject &variables);
    QJsonObject getReportVariables(const QString &reportType, const QJsonObject &parameters);
    
    CommunicationManager *m_commManager;
    
    // Report building
    QMap<QString, QString> m_reportSections;
    QMap<QString, QChart*> m_reportCharts;
    QMap<QString, QJsonArray> m_reportTables;
    QMap<QString, QPixmap> m_reportImages;
    
    // Templates
    QMap<QString, QString> m_reportTemplates;
    QMap<QString, QJsonObject> m_templateSettings;
    
    // Batch processing
    QTimer *m_batchTimer;
    QQueue<QJsonObject> m_reportQueue;
    QList<ReportMetrics> m_reportHistory;
    
    // Progress tracking
    QProgressBar *m_progressBar;
    int m_currentProgress;
};

// Report Builder Widget
class ReportBuilder : public QWidget
{
    Q_OBJECT

public:
    explicit ReportBuilder(AdvancedReports *reports, Database *database, QWidget *parent = nullptr);

signals:
    void reportGenerated(const QString &filename);

private slots:
    void selectReportType();
    void configureParameters();
    void selectTemplate();
    void previewReport();
    void generateReport();
    void saveTemplate();
    void loadTemplate();
    void exportReport();
    void emailReport();
    void scheduleReport();

private:
    void setupUI();
    void setupReportTypePanel();
    void setupParameterPanel();
    void setupTemplatePanel();
    void setupPreviewPanel();
    void setupActionPanel();
    
    void updateParameterPanel();
    void updatePreview();
    void loadReportParameters();
    void saveReportParameters();
    
    AdvancedReports *m_reports;
    Database *m_database;
    
    // UI Components
    QSplitter *m_splitter;
    QTabWidget *m_leftPanel;
    QTabWidget *m_rightPanel;
    
    // Report type selection
    QComboBox *m_reportTypeCombo;
    QListWidget *m_reportSubtypeList;
    QTextEdit *m_reportDescEdit;
    
    // Parameters
    QWidget *m_parameterWidget;
    QScrollArea *m_parameterScroll;
    QFormLayout *m_parameterLayout;
    QDateEdit *m_startDateEdit;
    QDateEdit *m_endDateEdit;
    QComboBox *m_classFilterCombo;
    QComboBox *m_teacherFilterCombo;
    QComboBox *m_statusFilterCombo;
    QCheckBox *m_includeChartsCheck;
    QCheckBox *m_includeImagesCheck;
    QSpinBox *m_chartWidthSpin;
    QSpinBox *m_chartHeightSpin;
    
    // Template selection
    QComboBox *m_templateCombo;
    QTextEdit *m_templatePreview;
    QPushButton *m_saveTemplateBtn;
    QPushButton *m_loadTemplateBtn;
    QPushButton *m_deleteTemplateBtn;
    
    // Preview
    QWebEngineView *m_previewWebView;
    QTextEdit *m_previewTextEdit;
    QTabWidget *m_previewTabs;
    
    // Actions
    QComboBox *m_formatCombo;
    QLineEdit *m_filenameEdit;
    QPushButton *m_generateBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_emailBtn;
    QPushButton *m_scheduleBtn;
    QProgressBar *m_progressBar;
    
    // Current configuration
    QJsonObject m_currentConfig;
    QString m_currentReportType;
    QString m_currentTemplate;
    QString m_generatedContent;
};

// Report Scheduler
class ReportScheduler : public QWidget
{
    Q_OBJECT

public:
    explicit ReportScheduler(AdvancedReports *reports, QWidget *parent = nullptr);

private slots:
    void addScheduledReport();
    void editScheduledReport();
    void deleteScheduledReport();
    void enableScheduledReport();
    void disableScheduledReport();
    void testScheduledReport();
    void viewReportHistory();

private:
    void setupUI();
    void setupScheduleTable();
    void setupActionButtons();
    void loadScheduledReports();
    void saveScheduledReports();
    
    AdvancedReports *m_reports;
    
    QTableWidget *m_scheduleTable;
    QPushButton *m_addBtn;
    QPushButton *m_editBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_enableBtn;
    QPushButton *m_disableBtn;
    QPushButton *m_testBtn;
    QPushButton *m_historyBtn;
    
    struct ScheduledReport {
        QString id;
        QString name;
        QString reportType;
        QJsonObject parameters;
        QString schedule; // cron-like expression
        QString recipient;
        AdvancedReports::ReportFormat format;
        bool enabled;
        QDateTime lastRun;
        QDateTime nextRun;
    };
    
    QList<ScheduledReport> m_scheduledReports;
};

// Report Dashboard
class ReportDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit ReportDashboard(AdvancedReports *reports, Database *database, QWidget *parent = nullptr);

private slots:
    void generateQuickReport();
    void openReportBuilder();
    void openReportScheduler();
    void viewReportHistory();
    void manageTemplates();

private:
    void setupUI();
    void setupQuickReports();
    void setupRecentReports();
    void setupStatistics();
    void loadRecentReports();
    
    AdvancedReports *m_reports;
    Database *m_database;
    
    // Quick reports
    QGridLayout *m_quickReportsLayout;
    QList<QPushButton*> m_quickReportButtons;
    
    // Recent reports
    QTableWidget *m_recentReportsTable;
    
    // Statistics
    QLabel *m_totalReportsLabel;
    QLabel *m_reportsThisMonthLabel;
    QLabel *m_mostPopularTypeLabel;
    QChart *m_reportStatsChart;
    QChartView *m_reportStatsView;
    
    // Actions
    QPushButton *m_builderBtn;
    QPushButton *m_schedulerBtn;
    QPushButton *m_historyBtn;
    QPushButton *m_templatesBtn;
};

#endif // ADVANCEDREPORTS_H
