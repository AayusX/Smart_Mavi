#include "dashboard.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QBarSet>

DashboardWindow::DashboardWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    loadStudents();
    updatePerformanceChart();
}

DashboardWindow::~DashboardWindow() = default;

void DashboardWindow::setupUI()
{
    setWindowTitle("Smart Mavi Dashboard");
    setMinimumSize(800, 600);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    createToolbar();
    createStudentsTable();
    createPerformanceChart();
    setupConnections();
    styleComponents();
}

void DashboardWindow::createToolbar()
{
    toolbarLayout = new QHBoxLayout();
    toolbarLayout->setSpacing(10);
    
    // Create a search box with icon
    auto* searchContainer = new QWidget(this);
    auto* searchLayout = new QHBoxLayout(searchContainer);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    
    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("Search students...");
    searchBox->setMinimumHeight(30);
    searchBox->setStyleSheet(
        "QLineEdit { border: 1px solid #ccc; border-radius: 4px; padding: 5px; }"
        "QLineEdit:focus { border-color: #2196F3; }"
    );
    
    // Create filter boxes container
    auto* filterContainer = new QWidget(this);
    auto* filterLayout = new QHBoxLayout(filterContainer);
    filterLayout->setContentsMargins(0, 0, 0, 0);
    filterLayout->setSpacing(5);
    
    filterBox = new QComboBox(this);
    filterBox->addItems({"All Classes", "Class A", "Class B", "Class C"});
    filterBox->setMinimumHeight(30);
    
    yearFilterBox = new QComboBox(this);
    yearFilterBox->addItems({"All Years", "Year 1", "Year 2", "Year 3", "Year 4"});
    yearFilterBox->setMinimumHeight(30);
    
    // Style combo boxes
    QString comboStyle = 
        "QComboBox { border: 1px solid #ccc; border-radius: 4px; padding: 5px; background: white; }"
        "QComboBox::drop-down { border: none; }"
        "QComboBox::down-arrow { image: url(:/icons/down-arrow.png); }";
    
    filterBox->setStyleSheet(comboStyle);
    yearFilterBox->setStyleSheet(comboStyle);
    
    filterLayout->addWidget(filterBox);
    filterLayout->addWidget(yearFilterBox);
    
    // Create action buttons with modern styling
    addButton = new QPushButton("Add Student", this);
    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);
    exportCSVButton = new QPushButton("Export CSV", this);
    exportPDFButton = new QPushButton("Export PDF", this);
    
    // Style buttons
    QString buttonStyle = 
        "QPushButton { padding: 8px 15px; border-radius: 4px; color: white; }"
        "QPushButton:hover { opacity: 0.9; }";
    
    addButton->setStyleSheet(buttonStyle + "background-color: #4CAF50;");
    editButton->setStyleSheet(buttonStyle + "background-color: #2196F3;");
    deleteButton->setStyleSheet(buttonStyle + "background-color: #f44336;");
    exportCSVButton->setStyleSheet(buttonStyle + "background-color: #FF9800;");
    exportPDFButton->setStyleSheet(buttonStyle + "background-color: #9C27B0;");
    
    // Add widgets to toolbar
    toolbarLayout->addWidget(searchContainer, 2);  // Search takes more space
    toolbarLayout->addWidget(filterContainer, 2);  // Filters take more space
    toolbarLayout->addWidget(addButton);
    toolbarLayout->addWidget(editButton);
    toolbarLayout->addWidget(deleteButton);
    toolbarLayout->addWidget(exportCSVButton);
    toolbarLayout->addWidget(exportPDFButton);
    
    mainLayout->addLayout(toolbarLayout);
}

void DashboardWindow::createStudentsTable()
{
    studentsTable = new QTableWidget(this);
    studentsTable->setColumnCount(5);
    studentsTable->setHorizontalHeaderLabels({"Name", "Class", "Marks", "Year", "Enrollment Date"});
    studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Style the table
    studentsTable->setStyleSheet(
        "QTableWidget { border: 1px solid #ddd; gridline-color: #ddd; }"
        "QTableWidget::item { padding: 5px; }"
        "QTableWidget::item:selected { background-color: #e3f2fd; color: black; }"
        "QHeaderView::section { background-color: #f5f5f5; padding: 5px; border: 1px solid #ddd; }"
    );
    
    // Set column widths
    studentsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);  // Name
    studentsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);    // Class
    studentsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);    // Marks
    studentsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);    // Year
    studentsTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);    // Date
    
    studentsTable->setColumnWidth(1, 100);  // Class
    studentsTable->setColumnWidth(2, 80);   // Marks
    studentsTable->setColumnWidth(3, 80);   // Year
    studentsTable->setColumnWidth(4, 120);  // Date
    
    // Enable sorting
    studentsTable->setSortingEnabled(true);
    
    mainLayout->addWidget(studentsTable);
}

void DashboardWindow::createPerformanceChart()
{
    performanceSeries = new QBarSeries();
    QChart* chart = new QChart();
    chart->addSeries(performanceSeries);
    chart->setTitle("Student Performance Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append({"0-20", "21-40", "41-60", "61-80", "81-100"});
    chart->addAxis(axisX, Qt::AlignBottom);
    
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, 10);
    chart->addAxis(axisY, Qt::AlignLeft);
    
    performanceChart = new QChartView(chart);
    performanceChart->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(performanceChart);
}

void DashboardWindow::setupConnections()
{
    connect(searchBox, &QLineEdit::textChanged, this, &DashboardWindow::searchStudents);
    connect(filterBox, &QComboBox::currentTextChanged, this, &DashboardWindow::filterStudents);
    connect(addButton, &QPushButton::clicked, this, &DashboardWindow::addStudent);
    connect(editButton, &QPushButton::clicked, this, &DashboardWindow::editStudent);
    connect(deleteButton, &QPushButton::clicked, this, &DashboardWindow::deleteStudent);
    connect(exportCSVButton, &QPushButton::clicked, this, &DashboardWindow::exportToCSV);
    connect(exportPDFButton, &QPushButton::clicked, this, &DashboardWindow::exportToPDF);
    connect(studentsTable->horizontalHeader(), &QHeaderView::sectionClicked, this, &DashboardWindow::sortStudents);
}

void DashboardWindow::styleComponents()
{
    QFile styleFile(":/assets/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        setStyleSheet(styleSheet);
        styleFile.close();
    }
}

void DashboardWindow::loadStudents()
{
    loadFromJson();
    refreshStudentsList();
}

void DashboardWindow::loadFromJson()
{
    QFile file("assets/students.json");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open students.json");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    students.clear();
    if (doc.isArray()) {
        QJsonArray array = doc.array();
        for (const QJsonValue& value : array) {
            QJsonObject obj = value.toObject();
            Student student{
                obj["name"].toString(),
                obj["class"].toString(),
                obj["marks"].toInt()
            };
            if (student.isValid()) {
                students.append(student);
            }
        }
    }
}

void DashboardWindow::saveStudents()
{
    QJsonArray array;
    for (const Student& student : students) {
        QJsonObject obj;
        obj["name"] = student.name;
        obj["class"] = student.className;
        obj["marks"] = student.marks;
        array.append(obj);
    }

    QFile file("assets/students.json");
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Could not save students.json");
        return;
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();
}

void DashboardWindow::refreshStudentsList()
{
    studentsTable->setSortingEnabled(false);  // Disable sorting while updating
    studentsTable->setRowCount(students.size());
    
    for (int i = 0; i < students.size(); ++i) {
        const Student& student = students[i];
        
        auto* nameItem = new QTableWidgetItem(student.name);
        auto* classItem = new QTableWidgetItem(student.className);
        auto* marksItem = new QTableWidgetItem;
        auto* yearItem = new QTableWidgetItem(QString("Year %1").arg(student.year));
        auto* dateItem = new QTableWidgetItem(student.enrollmentDate);
        
        // Set marks with proper alignment
        marksItem->setData(Qt::DisplayRole, student.marks);  // For proper sorting
        marksItem->setTextAlignment(Qt::AlignCenter);
        
        // Add tooltips
        nameItem->setToolTip(student.name);
        classItem->setToolTip(QString("Class: %1").arg(student.className));
        marksItem->setToolTip(QString("Marks: %1%").arg(student.marks));
        yearItem->setToolTip(QString("Study Year: %1").arg(student.year));
        dateItem->setToolTip(QString("Enrolled: %1").arg(student.enrollmentDate));
        
        studentsTable->setItem(i, 0, nameItem);
        studentsTable->setItem(i, 1, classItem);
        studentsTable->setItem(i, 2, marksItem);
        studentsTable->setItem(i, 3, yearItem);
        studentsTable->setItem(i, 4, dateItem);
    }
    
    studentsTable->setSortingEnabled(true);  // Re-enable sorting
    updatePerformanceChart();
}

void DashboardWindow::addStudent()
{
    StudentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Student newStudent{
            dialog.getStudentName(),
            dialog.getStudentClass(),
            dialog.getStudentMarks(),
            dialog.getStudentYear(),
            dialog.getEnrollmentDate()
        };
        
        if (newStudent.isValid()) {
            students.append(newStudent);
            saveStudents();
            refreshStudentsList();
        } else {
            QMessageBox::warning(this, "Error", "Invalid student data");
        }
    }
}

void DashboardWindow::editStudent()
{
    int row = studentsTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a student to edit");
        return;
    }

    StudentDialog dialog(this);
    const Student& student = students[row];
    dialog.setStudent(student.name, student.className, student.marks, student.year, student.enrollmentDate);

    if (dialog.exec() == QDialog::Accepted) {
        Student updatedStudent{
            dialog.getStudentName(),
            dialog.getStudentClass(),
            dialog.getStudentMarks(),
            dialog.getStudentYear(),
            dialog.getEnrollmentDate()
        };
        
        if (updatedStudent.isValid()) {
            students[row] = updatedStudent;
            saveStudents();
            refreshStudentsList();
        } else {
            QMessageBox::warning(this, "Error", "Invalid student data");
        }
    }
}

void DashboardWindow::deleteStudent()
{
    int row = studentsTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a student to delete");
        return;
    }

    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this student?") 
        == QMessageBox::Yes) {
        students.removeAt(row);
        saveStudents();
        refreshStudentsList();
    }
}

void DashboardWindow::searchStudents(const QString& text)
{
    for (int row = 0; row < studentsTable->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < studentsTable->columnCount(); ++col) {
            QTableWidgetItem* item = studentsTable->item(row, col);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        studentsTable->setRowHidden(row, !match);
    }
}

void DashboardWindow::exportToCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file for writing");
        return;
    }

    QTextStream stream(&file);
    stream << "Name,Class,Marks\n";
    for (const Student& student : students) {
        stream << QString("%1,%2,%3\n")
                     .arg(student.name)
                     .arg(student.className)
                     .arg(student.marks);
    }
    file.close();
}

void DashboardWindow::exportToPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QPainter painter(&printer);
    painter.begin(&printer);

    // Draw the table
    int y = 100;
    painter.drawText(100, y, "Student Records");
    y += 50;

    for (const Student& student : students) {
        painter.drawText(100, y, student.name);
        painter.drawText(300, y, student.className);
        painter.drawText(500, y, QString::number(student.marks));
        y += 30;
    }

    // Draw the chart
    QRect chartRect(100, y + 50, 600, 400);
    performanceChart->grab().scaled(chartRect.size()).save(fileName + "_chart.png");
    painter.drawImage(chartRect, QImage(fileName + "_chart.png"));

    painter.end();
}

void DashboardWindow::updatePerformanceChart()
{
    QVector<int> distribution(5, 0);  // 0-20, 21-40, 41-60, 61-80, 81-100
    for (const Student& student : students) {
        int index = student.marks / 20;
        if (index == 5) index = 4;  // Handle mark = 100
        distribution[index]++;
    }

    performanceSeries->clear();
    QBarSet* set = new QBarSet("Students");
    for (int count : distribution) {
        *set << count;
    }
    performanceSeries->append(set);
}

void DashboardWindow::filterStudents(const QString& criteria)
{
    QString classFilter = filterBox->currentText();
    QString yearFilter = yearFilterBox->currentText();
    
    for (int row = 0; row < studentsTable->rowCount(); ++row) {
        QTableWidgetItem* classItem = studentsTable->item(row, 1);
        QTableWidgetItem* yearItem = studentsTable->item(row, 3);  // Year column
        if (!classItem || !yearItem) continue;
        
        bool matchesClass = classFilter == "All Classes" || classItem->text() == classFilter;
        bool matchesYear = yearFilter == "All Years" || yearItem->text() == yearFilter;
        bool matchesSearch = criteria.isEmpty();
        
        if (!criteria.isEmpty()) {
            for (int col = 0; col < studentsTable->columnCount(); ++col) {
                QTableWidgetItem* item = studentsTable->item(row, col);
                if (item && item->text().contains(criteria, Qt::CaseInsensitive)) {
                    matchesSearch = true;
                    break;
                }
            }
        }
        
        studentsTable->setRowHidden(row, !(matchesClass && matchesYear && matchesSearch));
    }
}

void DashboardWindow::sortStudents(int column)
{
    studentsTable->sortItems(column, Qt::AscendingOrder);
}

bool DashboardWindow::validateStudent(const Student& student)
{
    return student.isValid();
}
