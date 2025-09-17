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
#include <QTimer>

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

    //Status Label

    statusLabelpositive = new QLabel(this);
    statusLabelpositive->setStyleSheet("color: green; font-weight: bold; background-color: rgba(255,255,255,200); padding: 5px;");
    statusLabelpositive->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    statusLabelpositive->setVisible(false);
    statusLabelpositive->setGeometry(this->width() - 220, this->height() - 40, 200, 30);

    statusLabelerror = new QLabel(this);
    statusLabelerror->setStyleSheet("color: red; font-weight: bold; background-color: rgba(255,255,255,200); padding: 5px;");
    statusLabelerror->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    statusLabelerror->setVisible(false);
    statusLabelerror->setGeometry(this->width() - 220, this->height() - 40, 200, 30);




    // Connect buttons to slots
    connect(suburbsButton, &QPushButton::clicked, this, &MainWindow::openSuburbs);
    connect(medicationButton, &QPushButton::clicked, this, &MainWindow::openMedication);
    connect(onCallButton, &QPushButton::clicked, this, &MainWindow::openOnCallRoster);


    // Create suburbs window once
    suburbsWindow = new SuburbsWindow();


    // Laod CSV File Automatically
    QString defaultFile = "C:/Users/dhmdxc6/Desktop/QtcreatorProjects/APv2/Domiciliary_Book_for_App.csv";
    QFile f(defaultFile);
    if(f.exists()) {
        suburbsWindow->loadFromCSV(defaultFile);



        // Show status label
        statusLabelpositive->setText("Suburbs loaded successfully!");
        statusLabelpositive->setVisible(true);
        statusLabelpositive->raise();
        QTimer::singleShot(750, this, [this]() {
            statusLabelpositive->move(width() - statusLabelpositive->width() - 20, height() - statusLabelpositive->height() - 20);

        QTimer::singleShot(10000, statusLabelpositive, &QLabel::hide);
            });
    }

    else if(!f.exists()){
        statusLabelerror->setText("Suburbs file not found!");
        statusLabelerror->setVisible(true);
        statusLabelerror->raise();
        QTimer::singleShot(750, this, [this]() {
            statusLabelerror->move(width() - statusLabelerror->width() - 20, height() - statusLabelerror->height() - 20);

            QTimer::singleShot(10000, statusLabelerror, &QLabel::hide);
        });

    }

}




MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------- Slots (same as before) ----------------
void MainWindow::openSuburbs()
{
    if (!suburbsWindow) {
        return;
    }

    suburbsWindow->show();          // Just show the existing window
    suburbsWindow->raise();         // Bring it to front
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

void MainWindow::loadFromCSV(const QString &fileName) {
    if (!suburbsWindow) {
        suburbsWindow = new SuburbsWindow();
        //connect(suburbsWindow, &QWidget::destroyed, [this]() { suburbsWindow = nullptr; });
    }

    suburbsWindow->loadFromCSV(fileName); // Call the public function in SuburbsWindow
}



void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    if (statusLabelpositive && statusLabelpositive->isVisible()) {
        statusLabelpositive->move(width() - statusLabelpositive->width() - 20, height() - statusLabelpositive->height() - 20);
    }

    else if(statusLabelerror && statusLabelerror->isVisible()) {
        statusLabelerror->move(width() - statusLabelerror->width() - 20, height() - statusLabelerror->height() - 20);
    }

}
