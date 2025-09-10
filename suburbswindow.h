#ifndef SUBURSWINDOW_H
#define SUBURSWINDOW_H

#include <QWidget>

class SuburbsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SuburbsWindow(QWidget *parent = nullptr);

private:
    class QLineEdit *lineEdit;
    class QPushButton *addButton;
    class QPushButton *saveButton;
    class QListWidget *listWidget;
};

#endif // SUBURSWINDOW_H
