#include "scheduleview.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QDateTime>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QIODevice>

ScheduleView::ScheduleView(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    m_days << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";
}

void ScheduleView::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Control panel
    QGroupBox *controlGroup = new QGroupBox("📊 Schedule Controls");
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);
    
    // View type selection
    controlLayout->addWidget(new QLabel("View Type:"));
    m_viewTypeCombo = new QComboBox;
    m_viewTypeCombo->addItems({"📅 Full Schedule", "🏫 By Class", "👨‍🏫 By Teacher"});
    controlLayout->addWidget(m_viewTypeCombo);
    
    // Class/Teacher selection
    controlLayout->addWidget(new QLabel("Select:"));
    m_classTeacherCombo = new QComboBox;
    controlLayout->addWidget(m_classTeacherCombo);
    
    controlLayout->addStretch();
    
    // Action buttons
    m_regenerateButton = new QPushButton("🎲 Regenerate Schedule");
    m_previewButton = new QPushButton("👀 Print Preview");
    m_printButton = new QPushButton("🖨️ Print");
    m_exportPdfButton = new QPushButton("📄 Export PDF");
    m_exportCsvButton = new QPushButton("📊 Export CSV");
    
    controlLayout->addWidget(m_regenerateButton);
    controlLayout->addWidget(m_previewButton);
    controlLayout->addWidget(m_printButton);
    controlLayout->addWidget(m_exportPdfButton);
    controlLayout->addWidget(m_exportCsvButton);
    
    // Schedule table
    m_scheduleTable = new QTableWidget;
    m_scheduleTable->setAlternatingRowColors(true);
    m_scheduleTable->setSelectionBehavior(QAbstractItemView::SelectItems);
    m_scheduleTable->horizontalHeader()->setStretchLastSection(true);
    m_scheduleTable->verticalHeader()->setVisible(true);
    
    // Status label
    m_statusLabel = new QLabel("📋 Schedule ready for viewing");
    m_statusLabel->setAlignment(Qt::AlignCenter);
    
    // Add to main layout
    mainLayout->addWidget(controlGroup);
    mainLayout->addWidget(m_scheduleTable, 1);
    mainLayout->addWidget(m_statusLabel);
    
    // Connect signals
    connect(m_viewTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &ScheduleView::onViewTypeChanged);
    connect(m_classTeacherCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &ScheduleView::updateTable);
    connect(m_printButton, &QPushButton::clicked, this, &ScheduleView::printSchedule);
    connect(m_previewButton, &QPushButton::clicked, this, &ScheduleView::printPreview);
    connect(m_exportPdfButton, &QPushButton::clicked, this, &ScheduleView::exportToPdf);
    connect(m_exportCsvButton, &QPushButton::clicked, this, &ScheduleView::exportToCsv);
    connect(m_regenerateButton, &QPushButton::clicked, this, &ScheduleView::regenerateSchedule);
    
    applyTableStyling();
}

void ScheduleView::setSchedule(const Schedule& schedule)
{
    m_schedule = schedule;
    updateTable();
    m_statusLabel->setText(QString("✅ Schedule loaded with %1 entries").arg(schedule.size()));
}

void ScheduleView::setScheduleConfig(const ScheduleConfig& config)
{
    m_config = config;
    m_days = config.days;
    
    // Update combo boxes
    onViewTypeChanged();
}

void ScheduleView::updateTable()
{
    int viewType = m_viewTypeCombo->currentIndex();
    
    switch (viewType) {
        case 0: // Full Schedule
            populateFullSchedule();
            break;
        case 1: // By Class
            {
                int classIndex = m_classTeacherCombo->currentIndex();
                if (classIndex >= 0 && classIndex < m_config.classes.size()) {
                    populateClassSchedule(m_config.classes[classIndex]);
                }
            }
            break;
        case 2: // By Teacher
            {
                int teacherIndex = m_classTeacherCombo->currentIndex();
                if (teacherIndex >= 0 && teacherIndex < m_config.teachers.size()) {
                    populateTeacherSchedule(m_config.teachers[teacherIndex]);
                }
            }
            break;
    }
}

void ScheduleView::populateFullSchedule()
{
    // Create time slots for display
    QVector<TimeSlot> allTimeSlots;
    for (const QString& day : m_days) {
        QTime currentTime = m_config.schoolStartTime;
        int periodNumber = 1;
        
        while (currentTime < m_config.schoolEndTime && periodNumber <= m_config.maxPeriodsPerDay) {
            TimeSlot slot(currentTime, m_config.periodDuration);
            slot.setDay(day);
            slot.setPeriodNumber(periodNumber);
            
            // Check for breaks
            if (currentTime == m_config.breakStartTime) {
                slot.setDurationMinutes(m_config.breakDuration);
                slot.setIsBreak(true);
            } else if (currentTime == m_config.lunchStartTime) {
                slot.setDurationMinutes(m_config.lunchDuration);
                slot.setIsBreak(true);
            }
            
            allTimeSlots.append(slot);
            currentTime = slot.getEndTime();
            periodNumber++;
        }
    }
    
    // Set up table structure
    int periods = allTimeSlots.size() / m_days.size();
    m_scheduleTable->setRowCount(periods);
    m_scheduleTable->setColumnCount(m_days.size());
    
    // Set headers
    m_scheduleTable->setHorizontalHeaderLabels(m_days);
    
    QStringList verticalHeaders;
    for (int i = 0; i < periods; i++) {
        if (i < allTimeSlots.size()) {
            TimeSlot slot = allTimeSlots[i];
            if (slot.getIsBreak()) {
                verticalHeaders.append(QString("Break\\n%1-%2")
                    .arg(slot.getStartTime().toString("hh:mm"))
                    .arg(slot.getEndTime().toString("hh:mm")));
            } else {
                verticalHeaders.append(QString("Period %1\\n%2-%3")
                    .arg(slot.getPeriodNumber())
                    .arg(slot.getStartTime().toString("hh:mm"))
                    .arg(slot.getEndTime().toString("hh:mm")));
            }
        }
    }
    m_scheduleTable->setVerticalHeaderLabels(verticalHeaders);
    
    // Clear table
    m_scheduleTable->clearContents();
    
    // Populate table with schedule entries
    for (const auto& entry : m_schedule.getEntries()) {
        int dayIndex = m_days.indexOf(entry.timeSlot.getDay());
        int periodIndex = entry.timeSlot.getPeriodNumber() - 1;
        
        if (dayIndex >= 0 && periodIndex >= 0 && 
            dayIndex < m_scheduleTable->columnCount() && 
            periodIndex < m_scheduleTable->rowCount()) {
            
            QString cellText = QString("%1\\n%2\\n%3")
                .arg(entry.classInfo.getName())
                .arg(entry.subject.getName())
                .arg(entry.teacher.getName());
            
            QTableWidgetItem *item = new QTableWidgetItem(cellText);
            item->setTextAlignment(Qt::AlignCenter);
            
            // Color coding
            if (entry.timeSlot.getIsBreak()) {
                item->setBackground(QColor(255, 235, 59)); // Yellow for breaks
            } else {
                // Random color based on subject
                int colorIndex = entry.subject.getId() % 6;
                QColor colors[] = {
                    QColor(169, 223, 191), // Light green
                    QColor(174, 198, 235), // Light blue
                    QColor(255, 182, 193), // Light pink
                    QColor(221, 160, 221), // Light purple
                    QColor(255, 218, 185), // Light orange
                    QColor(211, 211, 211)  // Light gray
                };
                item->setBackground(colors[colorIndex]);
            }
            
            m_scheduleTable->setItem(periodIndex, dayIndex, item);
        }
    }
    
    // Adjust column and row sizes
    m_scheduleTable->resizeColumnsToContents();
    m_scheduleTable->resizeRowsToContents();
}

void ScheduleView::populateClassSchedule(const ClassInfo& classInfo)
{
    QVector<ScheduleEntry> classEntries = m_schedule.getEntriesForClass(classInfo);
    
    // Create simplified view for single class
    int maxPeriods = m_config.maxPeriodsPerDay;
    m_scheduleTable->setRowCount(maxPeriods);
    m_scheduleTable->setColumnCount(m_days.size());
    
    m_scheduleTable->setHorizontalHeaderLabels(m_days);
    
    QStringList verticalHeaders;
    for (int i = 1; i <= maxPeriods; i++) {
        verticalHeaders.append(QString("Period %1").arg(i));
    }
    m_scheduleTable->setVerticalHeaderLabels(verticalHeaders);
    
    m_scheduleTable->clearContents();
    
    for (const auto& entry : classEntries) {
        int dayIndex = m_days.indexOf(entry.timeSlot.getDay());
        int periodIndex = entry.timeSlot.getPeriodNumber() - 1;
        
        if (dayIndex >= 0 && periodIndex >= 0 && 
            dayIndex < m_scheduleTable->columnCount() && 
            periodIndex < m_scheduleTable->rowCount()) {
            
            QString cellText;
            if (entry.timeSlot.getIsBreak()) {
                cellText = "🍽️ Break";
            } else {
                cellText = QString("%1\\n👨‍🏫 %2")
                    .arg(entry.subject.getName())
                    .arg(entry.teacher.getName());
            }
            
            QTableWidgetItem *item = new QTableWidgetItem(cellText);
            item->setTextAlignment(Qt::AlignCenter);
            
            // Color coding same as full schedule
            if (entry.timeSlot.getIsBreak()) {
                item->setBackground(QColor(255, 235, 59));
            } else {
                int colorIndex = entry.subject.getId() % 6;
                QColor colors[] = {
                    QColor(169, 223, 191), QColor(174, 198, 235), QColor(255, 182, 193),
                    QColor(221, 160, 221), QColor(255, 218, 185), QColor(211, 211, 211)
                };
                item->setBackground(colors[colorIndex]);
            }
            
            m_scheduleTable->setItem(periodIndex, dayIndex, item);
        }
    }
    
    m_scheduleTable->resizeColumnsToContents();
    m_scheduleTable->resizeRowsToContents();
}

void ScheduleView::populateTeacherSchedule(const Teacher& teacher)
{
    QVector<ScheduleEntry> teacherEntries = m_schedule.getEntriesForTeacher(teacher);
    
    // Similar to class schedule but showing classes instead of teachers
    int maxPeriods = m_config.maxPeriodsPerDay;
    m_scheduleTable->setRowCount(maxPeriods);
    m_scheduleTable->setColumnCount(m_days.size());
    
    m_scheduleTable->setHorizontalHeaderLabels(m_days);
    
    QStringList verticalHeaders;
    for (int i = 1; i <= maxPeriods; i++) {
        verticalHeaders.append(QString("Period %1").arg(i));
    }
    m_scheduleTable->setVerticalHeaderLabels(verticalHeaders);
    
    m_scheduleTable->clearContents();
    
    for (const auto& entry : teacherEntries) {
        int dayIndex = m_days.indexOf(entry.timeSlot.getDay());
        int periodIndex = entry.timeSlot.getPeriodNumber() - 1;
        
        if (dayIndex >= 0 && periodIndex >= 0 && 
            dayIndex < m_scheduleTable->columnCount() && 
            periodIndex < m_scheduleTable->rowCount()) {
            
            QString cellText = QString("%1\\n🏫 %2")
                .arg(entry.subject.getName())
                .arg(entry.classInfo.getName());
            
            QTableWidgetItem *item = new QTableWidgetItem(cellText);
            item->setTextAlignment(Qt::AlignCenter);
            
            int colorIndex = entry.classInfo.getId() % 6;
            QColor colors[] = {
                QColor(169, 223, 191), QColor(174, 198, 235), QColor(255, 182, 193),
                QColor(221, 160, 221), QColor(255, 218, 185), QColor(211, 211, 211)
            };
            item->setBackground(colors[colorIndex]);
            
            m_scheduleTable->setItem(periodIndex, dayIndex, item);
        }
    }
    
    m_scheduleTable->resizeColumnsToContents();
    m_scheduleTable->resizeRowsToContents();
}

void ScheduleView::onViewTypeChanged()
{
    m_classTeacherCombo->clear();
    
    int viewType = m_viewTypeCombo->currentIndex();
    
    switch (viewType) {
        case 0: // Full Schedule
            m_classTeacherCombo->setEnabled(false);
            break;
        case 1: // By Class
            m_classTeacherCombo->setEnabled(true);
            for (const auto& classInfo : m_config.classes) {
                m_classTeacherCombo->addItem(QString("🏫 %1").arg(classInfo.getName()));
            }
            break;
        case 2: // By Teacher
            m_classTeacherCombo->setEnabled(true);
            for (const auto& teacher : m_config.teachers) {
                m_classTeacherCombo->addItem(QString("👨‍🏫 %1").arg(teacher.getName()));
            }
            break;
    }
    
    updateTable();
}

void ScheduleView::printPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    
    connect(&preview, &QPrintPreviewDialog::paintRequested, [this](QPrinter *printer) {
        QTextDocument doc;
        QString title = "Smart Mavi Manager Schedule";
        
        int viewType = m_viewTypeCombo->currentIndex();
        if (viewType == 1 && m_classTeacherCombo->currentIndex() >= 0) {
            title += QString(" - %1").arg(m_config.classes[m_classTeacherCombo->currentIndex()].getName());
        } else if (viewType == 2 && m_classTeacherCombo->currentIndex() >= 0) {
            title += QString(" - %1").arg(m_config.teachers[m_classTeacherCombo->currentIndex()].getName());
        }
        
        setupPrintDocument(&doc, title);
        doc.print(printer);
    });
    
    preview.exec();
}

void ScheduleView::printSchedule()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    
    if (dialog.exec() == QDialog::Accepted) {
        QTextDocument doc;
        QString title = "Smart Mavi Manager Schedule";
        setupPrintDocument(&doc, title);
        doc.print(&printer);
        
        QMessageBox::information(this, "Print Complete", "📄 Schedule printed successfully!");
    }
}

void ScheduleView::exportToPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Schedule to PDF", 
                       QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/schedule.pdf",
                       "PDF Files (*.pdf)");
    
    if (!fileName.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        
        QTextDocument doc;
        QString title = "Smart Mavi Manager Schedule";
        setupPrintDocument(&doc, title);
        doc.print(&printer);
        
        QMessageBox::information(this, "Export Complete", 
                                QString("📄 Schedule exported to: %1").arg(fileName));
        
        // Open the PDF
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
}

void ScheduleView::exportToCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Schedule to CSV", 
                       QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/schedule.csv",
                       "CSV Files (*.csv)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            
            // Write headers
            stream << "Day,Period,Time,Class,Subject,Teacher\\n";
            
            // Write schedule data
            for (const auto& entry : m_schedule.getEntries()) {
                if (!entry.timeSlot.getIsBreak()) {
                    stream << entry.timeSlot.getDay() << ","
                           << entry.timeSlot.getPeriodNumber() << ","
                           << entry.timeSlot.toString() << ","
                           << entry.classInfo.getName() << ","
                           << entry.subject.getName() << ","
                           << entry.teacher.getName() << "\\n";
                }
            }
            
            file.close();
            QMessageBox::information(this, "Export Complete", 
                                    QString("📊 Schedule exported to: %1").arg(fileName));
        }
    }
}

void ScheduleView::regenerateSchedule()
{
    emit regenerateRequested();
}

void ScheduleView::applyTableStyling()
{
    setStyleSheet(
        "QTableWidget {"
        "    background-color: white;"
        "    gridline-color: #bdc3c7;"
        "    selection-background-color: #3498db;"
        "    font-size: 11px;"
        "}"
        "QHeaderView::section {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #3498db, stop:1 #2980b9);"
        "    color: white;"
        "    padding: 8px;"
        "    border: 1px solid #2980b9;"
        "    font-weight: bold;"
        "}"
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #3498db;"
        "    border-radius: 8px;"
        "    margin: 5px 0;"
        "    padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 15px;"
        "    padding: 0 8px 0 8px;"
        "    background: white;"
        "    border-radius: 4px;"
        "}"
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #3498db, stop:1 #2980b9);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 8px 12px;"
        "    font-weight: bold;"
        "    margin: 2px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "                               stop:0 #5dade2, stop:1 #3498db);"
        "}"
        "QComboBox {"
        "    padding: 6px;"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 4px;"
        "    background: white;"
        "    min-width: 150px;"
        "}"
        "QLabel {"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "}"
    );
}

void ScheduleView::setupPrintDocument(QTextDocument* doc, const QString& title)
{
    QString html = QString(
        "<html><head>"
        "<style>"
        "body { font-family: Arial, sans-serif; margin: 20px; }"
        "h1 { color: #2c3e50; text-align: center; border-bottom: 3px solid #3498db; padding-bottom: 10px; }"
        "h2 { color: #34495e; margin-top: 25px; }"
        "table { width: 100%; border-collapse: collapse; margin: 20px 0; }"
        "th, td { border: 1px solid #bdc3c7; padding: 8px; text-align: center; vertical-align: middle; }"
        "th { background-color: #3498db; color: white; font-weight: bold; }"
        "tr:nth-child(even) { background-color: #ecf0f1; }"
        ".break { background-color: #f1c40f !important; font-weight: bold; }"
        ".footer { margin-top: 30px; text-align: center; color: #7f8c8d; font-size: 12px; }"
        "</style>"
        "</head><body>"
    );
    
    html += QString("<h1>%1</h1>").arg(title);
    html += QString("<p style='text-align: center; color: #7f8c8d;'>Generated on %1</p>")
            .arg(QDateTime::currentDateTime().toString("dddd, MMMM d, yyyy at hh:mm"));
    
    // Add table
    html += "<table>";
    
    // Header row
    html += "<tr><th>Time</th>";
    for (const QString& day : m_days) {
        html += QString("<th>%1</th>").arg(day);
    }
    html += "</tr>";
    
    // Table rows
    for (int row = 0; row < m_scheduleTable->rowCount(); ++row) {
        html += "<tr>";
        
        // Time column
        QString timeHeader = m_scheduleTable->verticalHeaderItem(row) ? 
                           m_scheduleTable->verticalHeaderItem(row)->text() : "";
        html += QString("<td><strong>%1</strong></td>").arg(timeHeader.replace("\\n", "<br>"));
        
        // Day columns
        for (int col = 0; col < m_scheduleTable->columnCount(); ++col) {
            QTableWidgetItem* item = m_scheduleTable->item(row, col);
            QString cellText = item ? item->text() : "";
            QString cssClass = "";
            
            if (timeHeader.contains("Break")) {
                cssClass = " class='break'";
            }
            
            html += QString("<td%1>%2</td>").arg(cssClass).arg(cellText.replace("\\n", "<br>"));
        }
        html += "</tr>";
    }
    
    html += "</table>";
    
    // Footer
    html += "<div class='footer'>";
    html += "<p>📚 Smart Mavi Manager - Professional Schedule Generator</p>";
    html += "<p>✨ Randomized schedule with conflict resolution</p>";
    html += "</div>";
    
    html += "</body></html>";
    
    doc->setHtml(html);
}
