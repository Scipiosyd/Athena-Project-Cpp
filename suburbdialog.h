#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QList>
#include "suburb.h"

class SuburbDialog : public QDialog {
    Q_OBJECT
public:
    SuburbDialog(QWidget *parent,
                 const QList<Suburb> &existingSuburbs,
                 const Suburb *editSuburb = nullptr);

    Suburb getSuburb() const;

private slots:
    void onSaveClicked();

private:
    const QList<Suburb> &existingSuburbs;
    Suburb editSuburbData;

    QLineEdit *suburbField;
    QLineEdit *branchCodeField;
    QLineEdit *regionField;
    QLineEdit *speedDialField;
    QLineEdit *phone1Field;
    QLineEdit *phone2Field;
    QLineEdit *faxField;
    QLineEdit *emailField;
    QLineEdit *managerField;
    QLineEdit *managerPhoneField;
    QLineEdit *supervisorField;
    QLineEdit *supervisorPhoneField;
    QLineEdit *supervisor2Field;
    QLineEdit *supervisor2PhoneField;
    QLineEdit *daysHomeVisitField;
    QLineEdit *hoursOpenField;
    QLineEdit *saturdayHoursOpenField;
    QLineEdit *dom1Field;
    QLineEdit *dom2Field;
    QLineEdit *dom3Field;
    QLineEdit *dom4Field;
};
