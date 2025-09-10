#include "suburbswindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>

SuburbsWindow::SuburbsWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Suburbs");
    resize(1000, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // ---------------- Table Setup ----------------
    table = new QTableWidget(this);
    table->setColumnCount(21);
    QStringList headers = {"Suburb","Branch Code","Region","Speed Dial","Phone 1","Phone 2","Fax","Email",
                           "Manager","Manager Phone","Supervisor","Supervisor Phone","Supervisor 2","Supervisor 2 Phone",
                           "Days Home Visit","Hours Open","Saturday Hours Open","DOM1","DOM2","DOM3","DOM4"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setAlternatingRowColors(true);
    table->setStyleSheet(
        "QTableWidget {"
        "  gridline-color: #CCCCCC;"
        "  font-size: 14px;"
        "}"
        "QHeaderView::section {"
        "  background-color: #007ACC;"
        "  color: white;"
        "  font-weight: bold;"
        "  padding: 4px;"
        "}"
        "QTableWidget::item:selected {"
        "  background-color: #80C0FF;"
        "}"
        );
    mainLayout->addWidget(table);

    // ---------------- Buttons ----------------
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add Suburb", this);
    editButton = new QPushButton("Edit Selected", this);
    saveButton = new QPushButton("Save to CSV", this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(saveButton);
    mainLayout->addLayout(buttonLayout);

    connect(addButton, &QPushButton::clicked, this, &SuburbsWindow::addSuburb);
    connect(editButton, &QPushButton::clicked, this, &SuburbsWindow::editSuburb);
    connect(saveButton, &QPushButton::clicked, this, &SuburbsWindow::saveToCSV);
}

// ---------------- Slots ----------------
void SuburbsWindow::addSuburb() {
    bool ok;
    Suburb s = showSuburbDialog(nullptr, &ok);
    if (ok) {
        suburbList.append(s);
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(s.suburb));
        table->setItem(row, 1, new QTableWidgetItem(s.branchCode));
        table->setItem(row, 2, new QTableWidgetItem(s.region));
        table->setItem(row, 3, new QTableWidgetItem(s.speedDial));
        table->setItem(row, 4, new QTableWidgetItem(s.phone1));
        table->setItem(row, 5, new QTableWidgetItem(s.phone2));
        table->setItem(row, 6, new QTableWidgetItem(s.fax));
        table->setItem(row, 7, new QTableWidgetItem(s.email));
        table->setItem(row, 8, new QTableWidgetItem(s.manager));
        table->setItem(row, 9, new QTableWidgetItem(s.managerPhone));
        table->setItem(row, 10, new QTableWidgetItem(s.supervisor));
        table->setItem(row, 11, new QTableWidgetItem(s.supervisorPhone));
        table->setItem(row, 12, new QTableWidgetItem(s.supervisor2));
        table->setItem(row, 13, new QTableWidgetItem(s.supervisor2Phone));
        table->setItem(row, 14, new QTableWidgetItem(s.daysHomeVisit));
        table->setItem(row, 15, new QTableWidgetItem(s.hoursOpen));
        table->setItem(row, 16, new QTableWidgetItem(s.saturdayHoursOpen));
        table->setItem(row, 17, new QTableWidgetItem(s.dom1));
        table->setItem(row, 18, new QTableWidgetItem(s.dom2));
        table->setItem(row, 19, new QTableWidgetItem(s.dom3));
        table->setItem(row, 20, new QTableWidgetItem(s.dom4));
    }
}

void SuburbsWindow::editSuburb() {
    int row = table->currentRow();
    if (row < 0) return;

    bool ok;
    Suburb edited = showSuburbDialog(&suburbList[row], &ok);
    if (ok) {
        suburbList[row] = edited;
        for (int col = 0; col < 21; ++col) {
            QString value;
            switch(col) {
            case 0: value = edited.suburb; break;
            case 1: value = edited.branchCode; break;
            case 2: value = edited.region; break;
            case 3: value = edited.speedDial; break;
            case 4: value = edited.phone1; break;
            case 5: value = edited.phone2; break;
            case 6: value = edited.fax; break;
            case 7: value = edited.email; break;
            case 8: value = edited.manager; break;
            case 9: value = edited.managerPhone; break;
            case 10: value = edited.supervisor; break;
            case 11: value = edited.supervisorPhone; break;
            case 12: value = edited.supervisor2; break;
            case 13: value = edited.supervisor2Phone; break;
            case 14: value = edited.daysHomeVisit; break;
            case 15: value = edited.hoursOpen; break;
            case 16: value = edited.saturdayHoursOpen; break;
            case 17: value = edited.dom1; break;
            case 18: value = edited.dom2; break;
            case 19: value = edited.dom3; break;
            case 20: value = edited.dom4; break;
            }
            table->setItem(row, col, new QTableWidgetItem(value));
        }
    }
}

void SuburbsWindow::tableDoubleClicked(int row, int /*column*/) {
    table->selectRow(row); // make sure row is selected
    editSuburb();          // open edit dialog
}

void SuburbsWindow::saveToCSV() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file for writing");
        return;
    }

    QTextStream out(&file);
    for (const Suburb &s : suburbList) {
        out << s.suburb << "," << s.branchCode << "," << s.region << "," << s.speedDial << ","
            << s.phone1 << "," << s.phone2 << "," << s.fax << "," << s.email << ","
            << s.manager << "," << s.managerPhone << "," << s.supervisor << "," << s.supervisorPhone << ","
            << s.supervisor2 << "," << s.supervisor2Phone << "," << s.daysHomeVisit << "," << s.hoursOpen << ","
            << s.saturdayHoursOpen << "," << s.dom1 << "," << s.dom2 << "," << s.dom3 << "," << s.dom4 << "\n";
    }
    file.close();
    QMessageBox::information(this, "Saved", "Suburbs saved successfully!");
}

// ---------------- Inline Add/Edit Dialog ----------------
Suburb SuburbsWindow::showSuburbDialog(const Suburb *existing, bool *ok) {
    QDialog dialog(this);
    dialog.setWindowTitle(existing ? "Edit Suburb" : "Add Suburb");

    QFormLayout *form = new QFormLayout(&dialog);

    QLineEdit *suburbField = new QLineEdit(&dialog);
    QLineEdit *branchCodeField = new QLineEdit(&dialog);
    QLineEdit *regionField = new QLineEdit(&dialog);
    QLineEdit *speedDialField = new QLineEdit(&dialog);
    QLineEdit *phone1Field = new QLineEdit(&dialog);
    QLineEdit *phone2Field = new QLineEdit(&dialog);
    QLineEdit *faxField = new QLineEdit(&dialog);
    QLineEdit *emailField = new QLineEdit(&dialog);
    QLineEdit *managerField = new QLineEdit(&dialog);
    QLineEdit *managerPhoneField = new QLineEdit(&dialog);
    QLineEdit *supervisorField = new QLineEdit(&dialog);
    QLineEdit *supervisorPhoneField = new QLineEdit(&dialog);
    QLineEdit *supervisor2Field = new QLineEdit(&dialog);
    QLineEdit *supervisor2PhoneField = new QLineEdit(&dialog);
    QLineEdit *daysHomeVisitField = new QLineEdit(&dialog);
    QLineEdit *hoursOpenField = new QLineEdit(&dialog);
    QLineEdit *saturdayHoursOpenField = new QLineEdit(&dialog);
    QLineEdit *dom1Field = new QLineEdit(&dialog);
    QLineEdit *dom2Field = new QLineEdit(&dialog);
    QLineEdit *dom3Field = new QLineEdit(&dialog);
    QLineEdit *dom4Field = new QLineEdit(&dialog);

    if (existing) {
        suburbField->setText(existing->suburb);
        branchCodeField->setText(existing->branchCode);
        regionField->setText(existing->region);
        speedDialField->setText(existing->speedDial);
        phone1Field->setText(existing->phone1);
        phone2Field->setText(existing->phone2);
        faxField->setText(existing->fax);
        emailField->setText(existing->email);
        managerField->setText(existing->manager);
        managerPhoneField->setText(existing->managerPhone);
        supervisorField->setText(existing->supervisor);
        supervisorPhoneField->setText(existing->supervisorPhone);
        supervisor2Field->setText(existing->supervisor2);
        supervisor2PhoneField->setText(existing->supervisor2Phone);
        daysHomeVisitField->setText(existing->daysHomeVisit);
        hoursOpenField->setText(existing->hoursOpen);
        saturdayHoursOpenField->setText(existing->saturdayHoursOpen);
        dom1Field->setText(existing->dom1);
        dom2Field->setText(existing->dom2);
        dom3Field->setText(existing->dom3);
        dom4Field->setText(existing->dom4);
    }

    form->addRow("Suburb:", suburbField);
    form->addRow("Branch Code:", branchCodeField);
    form->addRow("Region:", regionField);
    form->addRow("Speed Dial:", speedDialField);
    form->addRow("Phone 1:", phone1Field);
    form->addRow("Phone 2:", phone2Field);
    form->addRow("Fax:", faxField);
    form->addRow("Email:", emailField);
    form->addRow("Manager:", managerField);
    form->addRow("Manager Phone:", managerPhoneField);
    form->addRow("Supervisor:", supervisorField);
    form->addRow("Supervisor Phone:", supervisorPhoneField);
    form->addRow("Supervisor 2:", supervisor2Field);
    form->addRow("Supervisor 2 Phone:", supervisor2PhoneField);
    form->addRow("Days Home Visit:", daysHomeVisitField);
    form->addRow("Hours Open:", hoursOpenField);
    form->addRow("Saturday Hours Open:", saturdayHoursOpenField);
    form->addRow("DOM1:", dom1Field);
    form->addRow("DOM2:", dom2Field);
    form->addRow("DOM3:", dom3Field);
    form->addRow("DOM4:", dom4Field);

    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    form->addWidget(&buttons);
    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        if (ok) *ok = true;
        return Suburb(suburbField->text(), branchCodeField->text(), regionField->text(), speedDialField->text(),
                      phone1Field->text(), phone2Field->text(), faxField->text(), emailField->text(),
                      managerField->text(), managerPhoneField->text(), supervisorField->text(), supervisorPhoneField->text(),
                      supervisor2Field->text(), supervisor2PhoneField->text(), daysHomeVisitField->text(), hoursOpenField->text(),
                      saturdayHoursOpenField->text(), dom1Field->text(), dom2Field->text(), dom3Field->text(), dom4Field->text());
    } else {
        if (ok) *ok = false;
        return existing ? *existing : Suburb("", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
    }
}

