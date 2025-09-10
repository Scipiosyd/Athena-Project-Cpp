#include "suburbswindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

SuburbsWindow::SuburbsWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Suburbs");
    resize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Add a suburb:", this);
    lineEdit = new QLineEdit(this);
    addButton = new QPushButton("Add", this);
    saveButton = new QPushButton("Save to CSV", this);
    listWidget = new QListWidget(this);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(lineEdit);
    inputLayout->addWidget(addButton);

    mainLayout->addWidget(label);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(saveButton);

    // Add suburb
    connect(addButton, &QPushButton::clicked, [this]() {
        if (!lineEdit->text().isEmpty()) {
            listWidget->addItem(lineEdit->text());
            lineEdit->clear();
        }
    });

    // Save list to CSV
    connect(saveButton, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Suburbs", "", "CSV Files (*.csv)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Cannot open file for writing");
            return;
        }

        QTextStream out(&file);
        for (int i = 0; i < listWidget->count(); ++i) {
            out << listWidget->item(i)->text() << "\n";
        }
        file.close();
        QMessageBox::information(this, "Saved", "Suburbs saved successfully!");
    });
}
