#include "suburbswindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFormLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>

// ---------------- SuburbDialog ----------------
class SuburbDialog : public QDialog {
    Q_OBJECT
public:
    SuburbDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Suburb Details");
        setMinimumWidth(400);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        form = new QFormLayout();
        mainLayout->addLayout(form);

        suburbField = new QLineEdit(); form->addRow("Suburb:", suburbField);
        branchCodeField = new QLineEdit(); form->addRow("Branch Code:", branchCodeField);
        speedDialField = new QLineEdit(); form->addRow("Speed Dial:", speedDialField);
        regionField = new QLineEdit(); form->addRow("Region:", regionField);

        phone1Field = new QLineEdit(); form->addRow("Phone 1:", phone1Field);
        phone2Field = new QLineEdit(); form->addRow("Phone 2:", phone2Field);
        faxField = new QLineEdit(); form->addRow("Fax:", faxField);
        emailField = new QLineEdit(); form->addRow("Email:", emailField);
        managerField = new QLineEdit(); form->addRow("Manager:", managerField);
        managerPhoneField = new QLineEdit(); form->addRow("Manager Phone:", managerPhoneField);
        supervisorField = new QLineEdit(); form->addRow("Supervisor:", supervisorField);
        supervisorPhoneField = new QLineEdit(); form->addRow("Supervisor Phone:", supervisorPhoneField);
        supervisor2Field = new QLineEdit(); form->addRow("Supervisor 2:", supervisor2Field);
        supervisor2PhoneField = new QLineEdit(); form->addRow("Supervisor 2 Phone:", supervisor2PhoneField);
        daysHomeVisitField = new QLineEdit(); form->addRow("Days Home Visit:", daysHomeVisitField);
        hoursOpenField = new QLineEdit(); form->addRow("Hours Open:", hoursOpenField);
        saturdayHoursOpenField = new QLineEdit(); form->addRow("Saturday Hours Open:", saturdayHoursOpenField);
        dom1Field = new QLineEdit(); form->addRow("DOM1:", dom1Field);
        dom2Field = new QLineEdit(); form->addRow("DOM2:", dom2Field);
        dom3Field = new QLineEdit(); form->addRow("DOM3:", dom3Field);
        dom4Field = new QLineEdit(); form->addRow("DOM4:", dom4Field);

        QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        mainLayout->addWidget(buttons);

        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    void setSuburb(const Suburb &s) {
        suburbField->setText(s.suburb);
        branchCodeField->setText(s.branchCode);
        speedDialField->setText(s.speedDial);
        regionField->setText(s.region);
        phone1Field->setText(s.phone1);
        phone2Field->setText(s.phone2);
        faxField->setText(s.fax);
        emailField->setText(s.email);
        managerField->setText(s.manager);
        managerPhoneField->setText(s.managerPhone);
        supervisorField->setText(s.supervisor);
        supervisorPhoneField->setText(s.supervisorPhone);
        supervisor2Field->setText(s.supervisor2);
        supervisor2PhoneField->setText(s.supervisor2Phone);
        daysHomeVisitField->setText(s.daysHomeVisit);
        hoursOpenField->setText(s.hoursOpen);
        saturdayHoursOpenField->setText(s.saturdayHoursOpen);
        dom1Field->setText(s.dom1);
        dom2Field->setText(s.dom2);
        dom3Field->setText(s.dom3);
        dom4Field->setText(s.dom4);
    }

    Suburb getSuburb() const {
        Suburb s;
        s.suburb = suburbField->text();
        s.branchCode = branchCodeField->text();
        s.speedDial = speedDialField->text();
        s.region = regionField->text();
        s.phone1 = phone1Field->text();
        s.phone2 = phone2Field->text();
        s.fax = faxField->text();
        s.email = emailField->text();
        s.manager = managerField->text();
        s.managerPhone = managerPhoneField->text();
        s.supervisor = supervisorField->text();
        s.supervisorPhone = supervisorPhoneField->text();
        s.supervisor2 = supervisor2Field->text();
        s.supervisor2Phone = supervisor2PhoneField->text();
        s.daysHomeVisit = daysHomeVisitField->text();
        s.hoursOpen = hoursOpenField->text();
        s.saturdayHoursOpen = saturdayHoursOpenField->text();
        s.dom1 = dom1Field->text();
        s.dom2 = dom2Field->text();
        s.dom3 = dom3Field->text();
        s.dom4 = dom4Field->text();
        return s;
    }

private:
    QFormLayout *form;
    QLineEdit *suburbField, *branchCodeField, *speedDialField, *regionField;
    QLineEdit *phone1Field, *phone2Field, *faxField, *emailField;
    QLineEdit *managerField, *managerPhoneField;
    QLineEdit *supervisorField, *supervisorPhoneField;
    QLineEdit *supervisor2Field, *supervisor2PhoneField;
    QLineEdit *daysHomeVisitField, *hoursOpenField, *saturdayHoursOpenField;
    QLineEdit *dom1Field, *dom2Field, *dom3Field, *dom4Field;
};

// ---------------- SuburbsWindow ----------------
SuburbsWindow::SuburbsWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Suburbs");
    resize(1200, 600);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // Table setup
    table = new QTableWidget(this);
    table->setColumnCount(4);
    QStringList headers = {"Suburb","Branch Code","Speed Dial","Region"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setAlternatingRowColors(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers); // read-only

    table->setStyleSheet(
        "QTableWidget { gridline-color: #CCCCCC; font-size: 14px; }"
        "QHeaderView::section { background-color: #007ACC; color: white; font-weight: bold; padding: 4px; }"
        "QTableWidget::item:selected { background-color: #80C0FF; }"
        );

    mainLayout->addWidget(table, 2);

    // Details panel
    QWidget *detailsPanel = new QWidget(this);
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsPanel);

    QLabel *title = new QLabel("Details", detailsPanel);
    title->setStyleSheet("font-weight: bold; font-size: 16px; margin-bottom: 10px;");
    detailsLayout->addWidget(title);

    detailsForm = new QFormLayout();
    detailsLayout->addLayout(detailsForm);

    // Labels
    suburbLabel = new QLabel(); branchCodeLabel = new QLabel();
    regionLabel = new QLabel(); speedDialLabel = new QLabel();
    phone1Label = new QLabel(); phone2Label = new QLabel();
    faxLabel = new QLabel(); emailLabel = new QLabel();
    managerLabel = new QLabel(); managerPhoneLabel = new QLabel();
    supervisorLabel = new QLabel(); supervisorPhoneLabel = new QLabel();
    supervisor2Label = new QLabel(); supervisor2PhoneLabel = new QLabel();
    daysHomeVisitLabel = new QLabel(); hoursOpenLabel = new QLabel();
    saturdayHoursOpenLabel = new QLabel();
    dom1Label = new QLabel(); dom2Label = new QLabel();
    dom3Label = new QLabel(); dom4Label = new QLabel();

    detailsForm->addRow("Suburb:", suburbLabel);
    detailsForm->addRow("Branch Code:", branchCodeLabel);
    detailsForm->addRow("Region:", regionLabel);
    detailsForm->addRow("Speed Dial:", speedDialLabel);
    detailsForm->addRow("Phone 1:", phone1Label);
    detailsForm->addRow("Phone 2:", phone2Label);
    detailsForm->addRow("Fax:", faxLabel);
    detailsForm->addRow("Email:", emailLabel);
    detailsForm->addRow("Manager:", managerLabel);
    detailsForm->addRow("Manager Phone:", managerPhoneLabel);
    detailsForm->addRow("Supervisor:", supervisorLabel);
    detailsForm->addRow("Supervisor Phone:", supervisorPhoneLabel);
    detailsForm->addRow("Supervisor 2:", supervisor2Label);
    detailsForm->addRow("Supervisor 2 Phone:", supervisor2PhoneLabel);
    detailsForm->addRow("Days Home Visit:", daysHomeVisitLabel);
    detailsForm->addRow("Hours Open:", hoursOpenLabel);
    detailsForm->addRow("Saturday Hours Open:", saturdayHoursOpenLabel);
    detailsForm->addRow("DOM1:", dom1Label);
    detailsForm->addRow("DOM2:", dom2Label);
    detailsForm->addRow("DOM3:", dom3Label);
    detailsForm->addRow("DOM4:", dom4Label);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add Suburb"); buttonLayout->addWidget(addButton);
    editButton = new QPushButton("Edit Selected"); buttonLayout->addWidget(editButton);
    saveButton = new QPushButton("Save to CSV"); buttonLayout->addWidget(saveButton);

    detailsLayout->addSpacing(15);
    detailsLayout->addLayout(buttonLayout);

    mainLayout->addWidget(detailsPanel, 1);

    // Connections
    connect(table, &QTableWidget::currentCellChanged, this, &SuburbsWindow::updateDetailsPanel);
    connect(addButton, &QPushButton::clicked, this, &SuburbsWindow::addSuburb);
    connect(editButton, &QPushButton::clicked, this, &SuburbsWindow::editSuburb);
    connect(saveButton, &QPushButton::clicked, this, &SuburbsWindow::saveToCSV);
}

// ---------------- Details update ----------------
void SuburbsWindow::updateDetailsPanel(int row, int, int, int) {
    if (row < 0 || row >= suburbList.size()) return;
    const Suburb &s = suburbList[row];

    suburbLabel->setText(s.suburb);
    branchCodeLabel->setText(s.branchCode);
    regionLabel->setText(s.region);
    speedDialLabel->setText(s.speedDial);
    phone1Label->setText(s.phone1);
    phone2Label->setText(s.phone2);
    faxLabel->setText(s.fax);
    emailLabel->setText(s.email);
    managerLabel->setText(s.manager);
    managerPhoneLabel->setText(s.managerPhone);
    supervisorLabel->setText(s.supervisor);
    supervisorPhoneLabel->setText(s.supervisorPhone);
    supervisor2Label->setText(s.supervisor2);
    supervisor2PhoneLabel->setText(s.supervisor2Phone);
    daysHomeVisitLabel->setText(s.daysHomeVisit);
    hoursOpenLabel->setText(s.hoursOpen);
    saturdayHoursOpenLabel->setText(s.saturdayHoursOpen);
    dom1Label->setText(s.dom1);
    dom2Label->setText(s.dom2);
    dom3Label->setText(s.dom3);
    dom4Label->setText(s.dom4);
}

// ---------------- Add/Edit ----------------
void SuburbsWindow::addSuburb() {
    SuburbDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Suburb s = dlg.getSuburb();
        suburbList.append(s);
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(s.suburb));
        table->setItem(row, 1, new QTableWidgetItem(s.branchCode));
        table->setItem(row, 2, new QTableWidgetItem(s.speedDial));
        table->setItem(row, 3, new QTableWidgetItem(s.region));
        table->selectRow(row);
    }
}

void SuburbsWindow::editSuburb() {
    int row = table->currentRow();
    if (row < 0 || row >= suburbList.size()) {
        QMessageBox::warning(this, "Edit Suburb", "Please select a suburb to edit.");
        return;
    }

    SuburbDialog dlg(this);
    dlg.setSuburb(suburbList[row]);
    if (dlg.exec() == QDialog::Accepted) {
        Suburb s = dlg.getSuburb();
        suburbList[row] = s;
        table->setItem(row, 0, new QTableWidgetItem(s.suburb));
        table->setItem(row, 1, new QTableWidgetItem(s.branchCode));
        table->setItem(row, 2, new QTableWidgetItem(s.speedDial));
        table->setItem(row, 3, new QTableWidgetItem(s.region));
        updateDetailsPanel(row, 0, 0, 0);
    }
}

// ---------------- Save CSV ----------------
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
            << s.supervisor2 << "," << s.supervisor2Phone << "," << s.daysHomeVisit << ","
            << s.hoursOpen << "," << s.saturdayHoursOpen << "," << s.dom1 << "," << s.dom2 << ","
            << s.dom3 << "," << s.dom4 << "\n";
    }
    file.close();
    QMessageBox::information(this, "Saved", "Suburbs saved successfully!");
}

#include "suburbswindow.moc"
