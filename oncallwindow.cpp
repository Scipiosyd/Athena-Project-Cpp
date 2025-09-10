#include "oncallwindow.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

OnCallWindow::OnCallWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("On Call Roster");
    resize(500, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("On Call Roster:", this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Date" << "Shift");

    // Example data
    tableWidget->insertRow(0);
    tableWidget->setItem(0, 0, new QTableWidgetItem("Dr. Smith"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("05/09/2025"));
    tableWidget->setItem(0, 2, new QTableWidgetItem("Morning"));

    tableWidget->insertRow(1);
    tableWidget->setItem(1, 0, new QTableWidgetItem("Dr. Jones"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("05/09/2025"));
    tableWidget->setItem(1, 2, new QTableWidgetItem("Night"));

    saveButton = new QPushButton("Save to CSV", this);

    mainLayout->addWidget(label);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(saveButton);

    // Save table to CSV
    connect(saveButton, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save On Call Roster", "", "CSV Files (*.csv)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Cannot open file for writing");
            return;
        }

        QTextStream out(&file);
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            QStringList rowData;
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget->item(row, col);
                rowData << (item ? item->text() : "");
            }
            out << rowData.join(",") << "\n";
        }
        file.close();
        QMessageBox::information(this, "Saved", "On Call Roster saved successfully!");
    });
}
