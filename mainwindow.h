#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include "defines.h"
#include "newObjectMaster/newobjectmasterbase.h"
#include "serviceClasses/deleteobjectdialog.h"
#include "serviceClasses/serialportsdialog.h"
#include "serviceClasses/kalendardialog.h"
#include "serviceClasses/reportdialog.h"
#include "serviceClasses/netdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initialise();
    ~MainWindow();

protected:
    tcpClient netCore;

    QString appPath;
    QTimer *updateTimer;
    void resizeEvent(QResizeEvent *event);
    void errorMessage(QString error);

protected slots:
    void createNewObjectSlot();
    void editObjectSlot(objectType type, int index);
    void deleteObjectSlot(objectType type, int index);
    void openGraphSlot(int index=-1);
    void serialPortsSlot();
    void createReport(reportType type,int index);
    void updateTimeSlot();
    void netSettingSlot();
    void netErrorSlot();
    void netConnectSlot();

private:
    Ui::MainWindow *ui;




};

#endif // MAINWINDOW_H
