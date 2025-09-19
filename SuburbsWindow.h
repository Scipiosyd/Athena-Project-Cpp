#ifndef SUBURBSWINDOW_H
#define SUBURBSWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProgressDialog>
#include <QTextEdit>
#include <QWebEnginePage>
#include <QProgressDialog>
#include <QProgressBar>



// ---------------- Suburb struct ----------------
struct Suburb {
    QString suburb;
    QString branchCode;
    QString speedDial;
    QString region;
    QString phone1;
    QString phone2;
    QString fax;
    QString email;
    QString manager;
    QString managerPhone;
    QString supervisor;
    QString supervisorPhone;
    QString supervisor2;
    QString supervisor2Phone;
    QString daysHomeVisit;
    QString hoursOpen;
    QString saturdayHoursOpen;
    QString dom1;
    QString dom2;
    QString dom3;
    QString dom4;

    Suburb() {}
};

class SuburbsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SuburbsWindow(QWidget *parent = nullptr);

private slots:
    void updateDetailsPanel(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void addSuburb();
    void editSuburb();
    void saveToCSV();
    void updateFromWeb();                    // NEW
    void handleNetworkReply(QNetworkReply*); // NEW
    void sendNextUpdate();
    void showProgressDialog();
    void handlePageLoad(bool ok);



public slots:
    void loadFromCSV(const QString &fileName);


protected:
    void closeEvent(QCloseEvent *event) override; // handle hide-on-close

private:
    // Table
    QTableWidget *table;

    // Details panel
    QFormLayout *detailsForm;
    QLabel *suburbLabel;
    QLabel *branchCodeLabel;
    QLabel *speedDialLabel;
    QLabel *regionLabel;
    QLabel *phone1Label;
    QLabel *phone2Label;
    QLabel *faxLabel;
    QLabel *emailLabel;
    QLabel *managerLabel;
    QLabel *managerPhoneLabel;
    QLabel *supervisorLabel;
    QLabel *supervisorPhoneLabel;
    QLabel *supervisor2Label;
    QLabel *supervisor2PhoneLabel;
    QLabel *daysHomeVisitLabel;
    QLabel *hoursOpenLabel;
    QLabel *saturdayHoursOpenLabel;
    QLabel *dom1Label;
    QLabel *dom2Label;
    QLabel *dom3Label;
    QLabel *dom4Label;

    // Buttons
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *updateButton; // NEW

    // Suburb list
    QVector<Suburb> suburbList;

    // Networking
    QNetworkAccessManager *networkManager; // NEW

    int currentUpdateIndex = 0;    // Tracks which suburb is being updated

    // Progress dialog members
    QProgressBar *progressBar = nullptr;
    QTextEdit *progressTextEdit = nullptr;
    QDialog *progressDialog = nullptr;
    QWebEnginePage *webPage = nullptr;

};

#endif // SUBURBSWINDOW_H
