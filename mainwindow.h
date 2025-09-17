#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QTableWidget>
#include <QLabel>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SuburbsWindow;
class MedicationWindow;
class OnCallWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSuburbs();
    void openMedication();
    void openOnCallRoster();
    void loadFromCSV(const QString &fileName);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    QPointer<SuburbsWindow> suburbsWindow;
    QPointer<MedicationWindow> medicationWindow;
    QPointer<OnCallWindow> onCallWindow;

    //Status Label
    QLabel *statusLabelpositive;
    QLabel *statusLabelerror;

};



#endif // MAINWINDOW_H
