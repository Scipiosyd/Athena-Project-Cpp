#ifndef ONCALLWINDOW_H
#define ONCALLWINDOW_H

#include <QWidget>

class OnCallWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OnCallWindow(QWidget *parent = nullptr);

private:
    class QTableWidget *tableWidget;
    class QPushButton *saveButton;
};

#endif // ONCALLWINDOW_H
