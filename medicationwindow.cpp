#include "medicationwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QTimer>
#include <QInputDialog>
#include <QBrush>
#include <QShortcut>
#include <QKeyEvent>



MedicationWindow::MedicationWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Medication");
    resize(600, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // --- Search bar ---
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search medications or tests...");
    // no hide() anymore
    mainLayout->addWidget(searchBar);  // always visible





    QLabel *label = new QLabel("Medication List:", this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Medication" << "Tests");

    // --- Expand to fill available space in the VBox ---
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // --- Make columns initially equal width but manually adjustable ---
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    QTimer::singleShot(0, this, [this]() {
        int totalWidth = tableWidget->viewport()->width();
        tableWidget->setColumnWidth(0, totalWidth / 2);
        tableWidget->setColumnWidth(1, totalWidth / 2);
    });

    // Optional: set initial equal widths (half-half)
    int totalWidth = tableWidget->viewport()->width();
    tableWidget->setColumnWidth(0, totalWidth / 2);
    tableWidget->setColumnWidth(1, totalWidth / 2);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set selection to full row
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Allow only single row selection at a time (optional)
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Ensure the table accepts keyboard focus
    tableWidget->setFocusPolicy(Qt::StrongFocus);

    if (tableWidget->rowCount() > 0) {
        tableWidget->setCurrentCell(0, 0);
        tableWidget->setFocus();
    }



    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    saveButton = new QPushButton("Save to CSV", this);
    loadButton = new QPushButton("Load from CSV", this);
    addButton = new QPushButton("Add", this);
    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addWidget(label);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);


    // Connections
    connect(saveButton, &QPushButton::clicked, this, &MedicationWindow::saveToCSV);
    connect(loadButton, &QPushButton::clicked, this, &MedicationWindow::loadFromCSV);
    connect(addButton, &QPushButton::clicked, this, &MedicationWindow::addMedication);
    connect(editButton, &QPushButton::clicked, this, &MedicationWindow::editMedication);
    connect(deleteButton, &QPushButton::clicked, this, &MedicationWindow::deleteMedication);



    // --- Keyboard Shortcuts ---
    saveButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    loadButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    addButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    editButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    deleteButton->setShortcut(QKeySequence(Qt::Key_Delete));

    // --- Search filter as user types ---
    connect(searchBar, &QLineEdit::textChanged, this, [this](const QString &text) {

 if (text.trimmed().isEmpty()) {
        // Show all rows
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            tableWidget->setRowHidden(row, false);
        }
    } else {
        QStringList searchTerms = text.split(",", Qt::SkipEmptyParts);
        for (int i = 0; i < searchTerms.size(); ++i)
            searchTerms[i] = searchTerms[i].trimmed();

        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            bool match = false;

            for (const QString &term : searchTerms) {
                // Check each column for a match
                for (int col = 0; col < tableWidget->columnCount(); ++col) {
                    QTableWidgetItem *item = tableWidget->item(row, col);
                    if (item && item->text().contains(term, Qt::CaseInsensitive)) {
                        match = true;
                        break;
                    }
                }
                if (match) break; // no need to check further if one term matches
            }

            tableWidget->setRowHidden(row, !match);
            }
        }
    });


    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, [this](int row, int) {
        QString medName = tableWidget->item(row, 0)->text();
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Edit Medication",
            "Do you want to edit \"" + medName + "\"?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            tableWidget->setCurrentCell(row, 0);
            editMedication();
        }
    });


    this->installEventFilter(this);
    searchBar->installEventFilter(this);
    tableWidget->installEventFilter(this);




}

// --- Save ---
void MedicationWindow::saveToCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Medication", "", "CSV Files (*.csv)");
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
    QMessageBox::information(this, "Saved", "Medication saved successfully!");
}

// --- Load ---
void MedicationWindow::loadFromCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file for reading");
        return;
    }

    tableWidget->setRowCount(0);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 2) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(fields[0]));
            tableWidget->setItem(row, 1, new QTableWidgetItem(fields[1]));
        }
    }

    file.close();
}

// --- Add ---
void MedicationWindow::addMedication()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Add Medication");

    QFormLayout form(&dialog);
    QLineEdit *medicationEdit = new QLineEdit(&dialog);
    QLineEdit *testsEdit = new QLineEdit(&dialog);
    form.addRow("Medication:", medicationEdit);
    form.addRow("Tests:", testsEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(medicationEdit->text()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(testsEdit->text()));
    }
}

// --- Edit ---
void MedicationWindow::editMedication()
{
    int row = tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Warning", "Please select a row to edit.");
        return;
    }

    QString currentMed = tableWidget->item(row, 0)->text();
    QString currentTests = tableWidget->item(row, 1)->text();

    QDialog dialog(this);
    dialog.setWindowTitle("Edit Medication");

    QFormLayout form(&dialog);
    QLineEdit *medicationEdit = new QLineEdit(currentMed, &dialog);
    QLineEdit *testsEdit = new QLineEdit(currentTests, &dialog);
    form.addRow("Medication:", medicationEdit);
    form.addRow("Tests:", testsEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        tableWidget->setItem(row, 0, new QTableWidgetItem(medicationEdit->text()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(testsEdit->text()));
    }
}

// --- Delete ---
void MedicationWindow::deleteMedication()
{
    int row = tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Warning", "Please select a row to delete.");
        return;
    }

    QString medName = tableWidget->item(row, 0)->text();
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Delete",
        "Are you sure you want to delete \"" + medName + "\"?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        tableWidget->removeRow(row);
    }
}

void MedicationWindow::keyPressEvent(QKeyEvent *event)
{
    // Show/focus search bar on Enter or Ctrl+F
    if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) ||
        ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_F))
    {
        // searchBar->show();
        searchBar->setFocus();
        searchBar->selectAll(); // optional: select existing text
        return;
    }

    // Clear search on Esc or F11
    if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_F11) {
        searchBar->clear();
        searchBar->setFocus();

        for (int row = 0; row < tableWidget->rowCount(); ++row)
            tableWidget->setRowHidden(row, false);
        return;
    }

    // Default handling
    QWidget::keyPressEvent(event);
}



void MedicationWindow::searchMedication()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Search Medication",
                                         "Enter medication or test:", QLineEdit::Normal,
                                         "", &ok);
    if (!ok) return;

    text = text.trimmed();

    // If empty search, show all rows
    if (text.isEmpty()) {
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            tableWidget->setRowHidden(row, false);
        }
        return;
    }

    // Loop through all rows
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        tableWidget->setRowHidden(row, !match);
    }
}

bool MedicationWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        QString keyText = keyEvent->text();

        // --- Focus search bar if user types a printable character, space, or Enter ---
        if (!keyText.isEmpty() &&
            !(keyEvent->modifiers() & (Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier)) &&
            keyEvent->key() != Qt::Key_Escape &&
            keyEvent->key() != Qt::Key_Delete &&
            keyEvent->key() != Qt::Key_F11)
        {
            if (keyEvent->text().at(0).isPrint() ||
                keyEvent->key() == Qt::Key_Space ||
                keyEvent->key() == Qt::Key_Return ||
                keyEvent->key() == Qt::Key_Enter)
            {
                searchBar->setFocus();
                searchBar->insert(keyText);  // type the pressed key
                return true;  // event handled
            }
        }

        // --- Navigation when focus is on searchBar ---
        if (obj == searchBar) {
            if (keyEvent->key() == Qt::Key_Down) {
                for (int row = 0; row < tableWidget->rowCount(); ++row) {
                    if (!tableWidget->isRowHidden(row)) {
                        tableWidget->setCurrentCell(row, 0);
                        tableWidget->setFocus();
                        break;
                    }
                }
                return true;
            } else if (keyEvent->key() == Qt::Key_Up) {
                for (int row = tableWidget->rowCount() - 1; row >= 0; --row) {
                    if (!tableWidget->isRowHidden(row)) {
                        tableWidget->setCurrentCell(row, 0);
                        tableWidget->setFocus();
                        break;
                    }
                }
                return true;
            }
            return false;
        }



        // --- Navigation when focus is on tableWidget ---
        if (obj == tableWidget) {
            int currentRow = tableWidget->currentRow();

            if (keyEvent->key() == Qt::Key_Up) {
                for (int row = currentRow - 1; row >= 0; --row) {
                    if (!tableWidget->isRowHidden(row)) {
                        tableWidget->setCurrentCell(row, 0);
                        return true;
                    }
                }
                searchBar->setFocus();  // move to searchBar at top
                return true;
            }

            if (keyEvent->key() == Qt::Key_Down) {
                for (int row = currentRow + 1; row < tableWidget->rowCount(); ++row) {
                    if (!tableWidget->isRowHidden(row)) {
                        tableWidget->setCurrentCell(row, 0);
                        return true;
                    }
                }
                searchBar->setFocus();  // move to searchBar at bottom
                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, event);
}




