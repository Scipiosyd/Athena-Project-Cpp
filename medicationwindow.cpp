#include "medicationwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QVBoxLayout>

MedicationWindow::MedicationWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Medication");
    resize(500, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Medication List:", this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Medication" << "Dose");

    // Example data
    tableWidget->insertRow(0);
    tableWidget->setItem(0, 0, new QTableWidgetItem("Paracetamol"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("500mg"));

    tableWidget->insertRow(1);
    tableWidget->setItem(1, 0, new QTableWidgetItem("Ibuprofen"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("200mg"));

    saveButton = new QPushButton("Save to CSV", this);

    mainLayout->addWidget(label);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(saveButton);

    // Save table to CSV
    connect(saveButton, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Save Medication",
                                                        "",
                                                        "CSV Files (*.csv)");
        if (fileName.isEmpty())
            return;

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
        QMessageBox::information(this, "Saved", "Medication saved successfully!");
    });
}
