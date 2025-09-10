#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "medicationwindow.h"
#include "oncallwindow.h"
#include "SuburbsWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Central widget
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setAlignment(Qt::AlignCenter); // center vertically and horizontally
    layout->setSpacing(20);                // space between buttons

    // Create buttons
    QPushButton *suburbsButton = new QPushButton("Suburbs", this);
    QPushButton *medicationButton = new QPushButton("Medication", this);
    QPushButton *onCallButton = new QPushButton("On Call Roster", this);

    suburbsButton->setFixedSize(200, 60);
    medicationButton->setFixedSize(200, 60);
    onCallButton->setFixedSize(200, 60);

    // Add buttons to layout
    layout->addWidget(suburbsButton);
    layout->addWidget(medicationButton);
    layout->addWidget(onCallButton);

    // Connect buttons to slots
    connect(suburbsButton, &QPushButton::clicked, this, &MainWindow::openSuburbs);
    connect(medicationButton, &QPushButton::clicked, this, &MainWindow::openMedication);
    connect(onCallButton, &QPushButton::clicked, this, &MainWindow::openOnCallRoster);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------- Slots (same as before) ----------------
void MainWindow::openSuburbs()
{
    if (!suburbsWindow) {
        suburbsWindow = new SuburbsWindow();
        suburbsWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(suburbsWindow, &QWidget::destroyed, [this]() { suburbsWindow = nullptr; });
    }
    suburbsWindow->show();
    suburbsWindow->raise();
    suburbsWindow->activateWindow();
}

void MainWindow::openMedication()
{
    if (!medicationWindow) {
        medicationWindow = new MedicationWindow();
        medicationWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(medicationWindow, &QWidget::destroyed, [this]() { medicationWindow = nullptr; });
    }
    medicationWindow->show();
    medicationWindow->raise();
    medicationWindow->activateWindow();
}

void MainWindow::openOnCallRoster()
{
    if (!onCallWindow) {
        onCallWindow = new OnCallWindow();
        onCallWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(onCallWindow, &QWidget::destroyed, [this]() { onCallWindow = nullptr; });
    }
    onCallWindow->show();
    onCallWindow->raise();
    onCallWindow->activateWindow();
}
