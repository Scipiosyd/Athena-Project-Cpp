#include "suburbdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QMessageBox>

SuburbDialog::SuburbDialog(QWidget *parent, const QList<Suburb> &existing, const Suburb *editSuburb)
    : QDialog(parent), existingSuburbs(existing)
{
    setWindowTitle(editSuburb ? "Edit Suburb" : "Add Suburb");
    QGridLayout *grid = new QGridLayout(this);

    // Create all fields
    suburbField = new QLineEdit(this);
    branchCodeField = new QLineEdit(this);
    regionField = new QLineEdit(this);
    speedDialField = new QLineEdit(this);
    phone1Field = new QLineEdit(this);
    phone2Field = new QLineEdit(this);
    faxField = new QLineEdit(this);
    emailField = new QLineEdit(this);
    managerField = new QLineEdit(this);
    managerPhoneField = new QLineEdit(this);
    supervisorField = new QLineEdit(this);
    supervisorPhoneField = new QLineEdit(this);
    supervisor2Field = new QLineEdit(this);
    supervisor2PhoneField = new QLineEdit(this);
    daysHomeVisitField = new QLineEdit(this);
    hoursOpenField = new QLineEdit(this);
    saturdayHoursOpenField = new QLineEdit(this);
    dom1Field = new QLineEdit(this);
    dom2Field = new QLineEdit(this);
    dom3Field = new QLineEdit(this);
    dom4Field = new QLineEdit(this);

    QStringList labels = {"Suburb","Branch Code","Region","Speed Dial","Phone 1","Phone 2","Fax","Email",
                          "Manager","Manager Phone","Supervisor","Supervisor Phone","Supervisor 2","Supervisor 2 Phone",
                          "Days Home Visit","Hours Open","Saturday Hours Open","DOM 1 MOB","DOM 2 MOB","DOM 3 MOB","DOM 4 MOB"};

    QList<QLineEdit*> fields = {suburbField, branchCodeField, regionField, speedDialField, phone1Field, phone2Field,
                                 faxField, emailField, managerField, managerPhoneField, supervisorField, supervisorPhoneField,
                                 supervisor2Field, supervisor2PhoneField, daysHomeVisitField, hoursOpenField, saturdayHoursOpenField,
                                 dom1Field, dom2Field, dom3Field, dom4Field};

    for (int i = 0; i < labels.size(); ++i) {
        grid->addWidget(new QLabel(labels[i] + ":"), i, 0);
        grid->addWidget(fields[i], i, 1);
    }

    // Fill fields if editing
    if (editSuburb) {
        suburbField->setText(editSuburb->suburb);
        branchCodeField->setText(editSuburb->branchCode);
        regionField->setText(editSuburb->region);
        speedDialField->setText(editSuburb->speedDial);
        phone1Field->setText(editSuburb->phone1);
        phone2Field->setText(editSuburb->phone2);
        faxField->setText(editSuburb->fax);
        emailField->setText(editSuburb->email);
        managerField->setText(editSuburb->manager);
        managerPhoneField->setText(editSuburb->managerPhone);
        supervisorField->setText(editSuburb->supervisor);
        supervisorPhoneField->setText(editSuburb->supervisorPhone);
        supervisor2Field->setText(editSuburb->supervisor2);
        supervisor2PhoneField->setText(editSuburb->supervisor2Phone);
        daysHomeVisitField->setText(editSuburb->daysHomeVisit);
        hoursOpenField->setText(editSuburb->hoursOpen);
        saturdayHoursOpenField->setText(editSuburb->saturdayHoursOpen);
        dom1Field->setText(editSuburb->dom1);
        dom2Field->setText(editSuburb->dom2);
        dom3Field->setText(editSuburb->dom3);
        dom4Field->setText(editSuburb->dom4);

    }

    // Buttons
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SuburbDialog::onSaveClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SuburbDialog::reject);

    grid->addWidget(buttonBox, labels.size(), 0, 1, 2);
}

void SuburbDialog::onSaveClicked() {
    QString name = suburbField->text();
    for (const Suburb &s : existingSuburbs) {
        if (s.suburb.compare(name, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Duplicate Suburb", "The suburb name you entered already exists.");
            return;
        }
    }
    accept();
}

Suburb SuburbDialog::getSuburb() const {
    return Suburb(suburbField->text(), branchCodeField->text(), regionField->text(), speedDialField->text(),
                  phone1Field->text(), phone2Field->text(), faxField->text(), emailField->text(),
                  managerField->text(), managerPhoneField->text(), supervisorField->text(), supervisorPhoneField->text(),
                  supervisor2Field->text(), supervisor2PhoneField->text(), daysHomeVisitField->text(),
                  hoursOpenField->text(), saturdayHoursOpenField->text(), dom1Field->text(),
                  dom2Field->text(), dom3Field->text(), dom4Field->text());
}
