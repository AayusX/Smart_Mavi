#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QTextDocument>
#include <QGroupBox>
#include "schedule.h"
#include "schedulegenerator.h"

class ScheduleView : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleView(QWidget *parent = nullptr);
    
    void setSchedule(const Schedule& schedule);
    void setScheduleConfig(const ScheduleConfig& config);

private slots:
    void printSchedule();
    void printPreview();
    void exportToPdf();
    void exportToCsv();
    void onViewTypeChanged();
    void regenerateSchedule();

signals:
    void regenerateRequested();

private:
    void setupUI();
    void updateTable();
    void populateClassSchedule(const ClassInfo& classInfo);
    void populateTeacherSchedule(const Teacher& teacher);
    void populateFullSchedule();
    void applyTableStyling();
    void setupPrintDocument(QTextDocument* doc, const QString& title);

    QTableWidget *m_scheduleTable;
    QComboBox *m_viewTypeCombo;
    QComboBox *m_classTeacherCombo;
    QPushButton *m_printButton;
    QPushButton *m_previewButton;
    QPushButton *m_exportPdfButton;
    QPushButton *m_exportCsvButton;
    QPushButton *m_regenerateButton;
    QLabel *m_statusLabel;
    
    Schedule m_schedule;
    ScheduleConfig m_config;
    QStringList m_timeSlots;
    QStringList m_days;
};

#endif // SCHEDULEVIEW_H
