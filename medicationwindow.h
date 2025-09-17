#ifndef MEDICATIONWINDOW_H
#define MEDICATIONWINDOW_H

#include <QWidget>
#include <QLineEdit>

class QTableWidget;
class QPushButton;

class MedicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MedicationWindow(QWidget *parent = nullptr);

private slots:
    void saveToCSV();
    void loadFromCSV();
    void addMedication();
    void editMedication();
    void deleteMedication();
    void searchMedication();
    void keyPressEvent(QKeyEvent *event) override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QTableWidget *tableWidget;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QLineEdit *searchBar;

};

#endif // MEDICATIONWINDOW_H
