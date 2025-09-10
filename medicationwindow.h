#ifndef MEDICATIONWINDOW_H
#define MEDICATIONWINDOW_H

#include <QWidget>

class MedicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MedicationWindow(QWidget *parent = nullptr);

private:
    class QTableWidget *tableWidget;
    class QPushButton *saveButton;
};

#endif // MEDICATIONWINDOW_H
