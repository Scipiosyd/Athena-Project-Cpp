#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QList>
#include "suburb.h"

class SuburbsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SuburbsWindow(QWidget *parent = nullptr);

private slots:
    void addSuburb();
    void editSuburb();
    void saveToCSV();
    void tableDoubleClicked(int row, int /*column*/);

private:
    QList<Suburb> suburbList;
    QTableWidget *table;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *saveButton;
    Suburb showSuburbDialog(const Suburb *existing = nullptr, bool *ok = nullptr);

    void refreshTable();
    bool isDuplicate(const QString &name, int skipRow = -1);
};
