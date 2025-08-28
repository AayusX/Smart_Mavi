#ifndef ADVANCEDATTENDANCE_H
#define ADVANCEDATTENDANCE_H

#include "models/attendance.h"
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QNetworkAccessManager>

class Database;
class CommunicationManager;

// Enhanced Attendance with additional features
class EnhancedAttendance : public Attendance
{
public:
    enum Method {
        Manual = 0,
        Biometric = 1,
        CardScan = 2,
        QRCode = 3,
        FaceRecognition = 4,
        Bulk = 5
    };

    enum DetailedStatus {
        Present = 0,
        Absent = 1,
        Late = 2,
        Leave = 3,
        Sick = 4,
        Excused = 5,
        Suspended = 6,
        EarlyDismissal = 7
    };

    explicit EnhancedAttendance();
    EnhancedAttendance(const Attendance &attendance);
    
    // Enhanced properties
    Method getMethod() const { return m_method; }
    void setMethod(Method method) { m_method = method; }
    
    DetailedStatus getDetailedStatus() const { return m_detailedStatus; }
    void setDetailedStatus(DetailedStatus status) { m_detailedStatus = status; }
    
    QTime getCheckInTime() const { return m_checkInTime; }
    void setCheckInTime(const QTime &time) { m_checkInTime = time; }
    
    QTime getCheckOutTime() const { return m_checkOutTime; }
    void setCheckOutTime(const QTime &time) { m_checkOutTime = time; }
    
    QString getRemarks() const { return m_remarks; }
    void setRemarks(const QString &remarks) { m_remarks = remarks; }
    
    QString getLocationId() const { return m_locationId; }
    void setLocationId(const QString &id) { m_locationId = id; }
    
    QString getDeviceId() const { return m_deviceId; }
    void setDeviceId(const QString &id) { m_deviceId = id; }
    
    QString getVerifiedBy() const { return m_verifiedBy; }
    void setVerifiedBy(const QString &verifier) { m_verifiedBy = verifier; }
    
    QPixmap getPhoto() const { return m_photo; }
    void setPhoto(const QPixmap &photo) { m_photo = photo; }
    
    // Validation and business logic
    bool isLate() const;
    bool isEarlyDismissal() const;
    int getHoursPresent() const;
    bool requiresApproval() const;
    QString getStatusDescription() const;
    
    // Data serialization
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    Method m_method;
    DetailedStatus m_detailedStatus;
    QTime m_checkInTime;
    QTime m_checkOutTime;
    QString m_remarks;
    QString m_locationId;
    QString m_deviceId;
    QString m_verifiedBy;
    QPixmap m_photo; // For photo verification
};

// Biometric Attendance Simulator
class BiometricSimulator : public QObject
{
    Q_OBJECT

public:
    explicit BiometricSimulator(QObject *parent = nullptr);
    
    void startScanning();
    void stopScanning();
    bool isScanning() const { return m_isScanning; }
    
    void setSimulationMode(bool enabled) { m_simulationMode = enabled; }
    bool isSimulationMode() const { return m_simulationMode; }

signals:
    void fingerprintDetected(const QString &fingerprintId);
    void faceDetected(const QString &faceId, const QPixmap &photo);
    void cardScanned(const QString &cardId);
    void qrCodeScanned(const QString &qrData);
    void scanningError(const QString &error);
    void scanningStarted();
    void scanningStopped();

private slots:
    void simulateFingerprint();
    void simulateFaceRecognition();
    void simulateCardScan();

private:
    void initializeDevices();
    
    bool m_isScanning;
    bool m_simulationMode;
    QTimer *m_simulationTimer;
    QStringList m_simulatedFingerprints;
    QStringList m_simulatedFaces;
    QStringList m_simulatedCards;
};

// Bulk Attendance Widget
class BulkAttendanceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BulkAttendanceWidget(Database *database, QWidget *parent = nullptr);

signals:
    void attendanceMarked(const QList<EnhancedAttendance> &records);
    void bulkOperationCompleted(int successful, int failed);

private slots:
    void loadStudentList();
    void selectAllStudents();
    void deselectAllStudents();
    void markSelectedPresent();
    void markSelectedAbsent();
    void markSelectedLate();
    void markCustomStatus();
    void importFromCSV();
    void exportToCSV();
    void saveAttendance();

private:
    void setupUI();
    void setupStudentTable();
    void setupActionButtons();
    void updateSelectedCount();
    void validateAttendanceData();
    
    Database *m_database;
    QTableWidget *m_studentTable;
    QLabel *m_selectedCountLabel;
    QComboBox *m_classFilter;
    QDateEdit *m_dateEdit;
    QComboBox *m_statusCombo;
    QTextEdit *m_remarksEdit;
    
    QPushButton *m_selectAllBtn;
    QPushButton *m_deselectAllBtn;
    QPushButton *m_markPresentBtn;
    QPushButton *m_markAbsentBtn;
    QPushButton *m_markLateBtn;
    QPushButton *m_markCustomBtn;
    QPushButton *m_importBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_saveBtn;
    
    QList<int> m_selectedStudents;
    QDate m_currentDate;
};

// Advanced Attendance Manager
class AdvancedAttendanceManager : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedAttendanceManager(Database *database, CommunicationManager *commManager, QWidget *parent = nullptr);
    ~AdvancedAttendanceManager();

    void setCurrentClass(int classId);
    void setCurrentDate(const QDate &date);
    void refreshAttendanceData();

signals:
    void attendanceUpdated();
    void studentMarked(int studentId, EnhancedAttendance::DetailedStatus status);
    void bulkOperationCompleted();

private slots:
    void onBiometricDetected();
    void onManualAttendance();
    void onBulkAttendance();
    void onAttendanceAnalytics();
    void onExportAttendance();
    void onImportAttendance();
    void onGenerateReports();
    
    // Biometric handlers
    void onFingerprintDetected(const QString &fingerprintId);
    void onFaceDetected(const QString &faceId, const QPixmap &photo);
    void onCardScanned(const QString &cardId);
    void onQRCodeScanned(const QString &qrData);
    
    // Auto-notifications
    void sendLateArrivalNotification(int studentId);
    void sendAbsentNotification(int studentId);
    void sendAttendanceReport();

private:
    void setupUI();
    void setupBiometricPanel();
    void setupAttendanceTable();
    void setupAnalyticsPanel();
    void setupControlPanel();
    
    void updateAttendanceTable();
    void updateAnalytics();
    void processAttendanceRecord(const EnhancedAttendance &record);
    
    Database *m_database;
    CommunicationManager *m_commManager;
    BiometricSimulator *m_biometricSimulator;
    BulkAttendanceWidget *m_bulkWidget;
    
    // UI Components
    QTabWidget *m_tabWidget;
    QWidget *m_attendanceTab;
    QWidget *m_biometricTab;
    QWidget *m_bulkTab;
    QWidget *m_analyticsTab;
    
    // Attendance table
    QTableWidget *m_attendanceTable;
    QComboBox *m_classCombo;
    QDateEdit *m_dateEdit;
    QPushButton *m_refreshBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_reportBtn;
    
    // Biometric panel
    QLabel *m_biometricStatusLabel;
    QPushButton *m_startBiometricBtn;
    QPushButton *m_stopBiometricBtn;
    QLabel *m_lastScannedLabel;
    QProgressBar *m_scanProgress;
    
    // Analytics
    QLabel *m_totalPresentLabel;
    QLabel *m_totalAbsentLabel;
    QLabel *m_totalLateLabel;
    QLabel *m_attendanceRateLabel;
    QProgressBar *m_attendanceProgress;
    
    QChartView *m_attendanceChartView;
    QChartView *m_trendChartView;
    
    // Control panel
    QLineEdit *m_searchEdit;
    QComboBox *m_statusFilter;
    QPushButton *m_markPresentBtn;
    QPushButton *m_markAbsentBtn;
    QPushButton *m_markLateBtn;
    QPushButton *m_bulkOperationsBtn;
    
    // Data
    int m_currentClassId;
    QDate m_currentDate;
    QList<EnhancedAttendance> m_currentAttendance;
    
    // Settings
    bool m_autoNotificationsEnabled;
    bool m_biometricEnabled;
    bool m_photoVerificationEnabled;
    QTime m_lateThreshold;
    QTime m_earlyDismissalThreshold;
};

// Attendance Analytics Widget
class AttendanceAnalytics : public QWidget
{
    Q_OBJECT

public:
    explicit AttendanceAnalytics(Database *database, QWidget *parent = nullptr);

public slots:
    void refreshAnalytics();
    void setDateRange(const QDate &start, const QDate &end);
    void setClassFilter(int classId);

private slots:
    void generateDetailedReport();
    void exportAnalytics();
    void showTrendAnalysis();
    void showComparison();

private:
    void setupUI();
    void setupFilterPanel();
    void setupChartPanel();
    void setupStatisticsPanel();
    void setupReportPanel();
    
    void updateCharts();
    void updateStatistics();
    void createAttendanceTrendChart();
    void createClassComparisonChart();
    void createStatusDistributionChart();
    void createTimeAnalysisChart();
    
    Database *m_database;
    
    // Filters
    QDateEdit *m_startDateEdit;
    QDateEdit *m_endDateEdit;
    QComboBox *m_classFilterCombo;
    QComboBox *m_statusFilterCombo;
    QPushButton *m_applyFiltersBtn;
    QPushButton *m_resetFiltersBtn;
    
    // Charts
    QTabWidget *m_chartTabs;
    QChartView *m_trendChartView;
    QChartView *m_comparisonChartView;
    QChartView *m_distributionChartView;
    QChartView *m_timeChartView;
    
    // Statistics
    QLabel *m_totalDaysLabel;
    QLabel *m_avgAttendanceLabel;
    QLabel *m_bestClassLabel;
    QLabel *m_worstClassLabel;
    QLabel *m_trendLabel;
    QProgressBar *m_overallProgress;
    
    // Report generation
    QPushButton *m_generateReportBtn;
    QPushButton *m_exportBtn;
    QPushButton *m_emailReportBtn;
    QTextEdit *m_reportPreview;
    
    // Current data
    QDate m_startDate;
    QDate m_endDate;
    int m_filteredClassId;
    QList<EnhancedAttendance> m_filteredRecords;
};

// Real-time Attendance Monitor
class AttendanceMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit AttendanceMonitor(Database *database, CommunicationManager *commManager, QWidget *parent = nullptr);

public slots:
    void startMonitoring();
    void stopMonitoring();
    void pauseMonitoring();
    void resumeMonitoring();

signals:
    void lateStudentDetected(int studentId, const QTime &arrivalTime);
    void absentStudentDetected(int studentId);
    void attendanceThresholdReached(int classId, double percentage);
    void emergencyContactNeeded(int studentId, const QString &reason);

private slots:
    void checkLateArrivals();
    void checkAbsentees();
    void updateLiveStats();
    void sendAutomaticNotifications();

private:
    void setupUI();
    void setupLiveDisplay();
    void setupAlertSystem();
    void setupNotificationSettings();
    
    void processLiveAttendance();
    void updateLiveChart();
    void triggerAlert(const QString &type, const QString &message);
    
    Database *m_database;
    CommunicationManager *m_commManager;
    
    // Live monitoring
    QTimer *m_monitorTimer;
    QTimer *m_alertTimer;
    bool m_isMonitoring;
    bool m_isPaused;
    
    // UI Components
    QLabel *m_statusLabel;
    QLabel *m_liveCountLabel;
    QLabel *m_lateCountLabel;
    QLabel *m_absentCountLabel;
    QProgressBar *m_liveProgress;
    
    QTableWidget *m_liveTable;
    QListWidget *m_alertsList;
    
    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;
    QPushButton *m_pauseBtn;
    
    QChartView *m_liveChartView;
    QChart *m_liveChart;
    
    // Settings
    QTime m_lateThreshold;
    double m_attendanceThreshold;
    bool m_autoNotificationsEnabled;
    bool m_emergencyAlertsEnabled;
    
    // Current monitoring data
    QDate m_monitoringDate;
    QList<int> m_monitoredClasses;
    QMap<int, EnhancedAttendance> m_liveAttendance;
};

// QR Code Attendance System
class QRAttendanceSystem : public QWidget
{
    Q_OBJECT

public:
    explicit QRAttendanceSystem(Database *database, QWidget *parent = nullptr);

    void generateStudentQRCode(int studentId);
    void generateClassQRCode(int classId, const QDate &date);

signals:
    void qrCodeScanned(const QString &data);
    void attendanceMarked(int studentId, const QDateTime &timestamp);

private slots:
    void startQRScanner();
    void stopQRScanner();
    void onQRCodeDetected(const QString &data);
    void generateQRCodes();
    void printQRCodes();

private:
    void setupUI();
    void setupScannerPanel();
    void setupGeneratorPanel();
    void setupQRDisplay();
    
    void processQRData(const QString &data);
    QPixmap generateQRCodePixmap(const QString &data);
    QString encryptQRData(const QString &data);
    QString decryptQRData(const QString &encryptedData);
    
    Database *m_database;
    
    // QR Scanner simulation
    QTimer *m_scannerTimer;
    bool m_isScanning;
    
    // UI Components
    QTabWidget *m_tabWidget;
    QWidget *m_scannerTab;
    QWidget *m_generatorTab;
    
    QLabel *m_scannerStatus;
    QLabel *m_qrDisplay;
    QPushButton *m_startScanBtn;
    QPushButton *m_stopScanBtn;
    
    QComboBox *m_classCombo;
    QDateEdit *m_dateEdit;
    QPushButton *m_generateBtn;
    QPushButton *m_printBtn;
    
    QListWidget *m_recentScans;
    QLabel *m_lastScannedLabel;
};

#endif // ADVANCEDATTENDANCE_H
