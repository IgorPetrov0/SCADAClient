#ifndef SERIALPORTSDIALOG_H
#define SERIALPORTSDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSerialPort>

namespace Ui {
class serialPortsDialog;
}

class serialPortsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit serialPortsDialog(QWidget *parent);
    ~serialPortsDialog();
    QString getPortName(int port);
    void setPort(QString name, int number);


protected:
    QList<QSerialPortInfo> list;
    void fillComboBoxes();

protected slots:
    void port1ChangeSlot(int index);
    void port2ChangeSlot(int index);
    void saveSlot();


private:
    Ui::serialPortsDialog *ui;
};

#endif // SERIALPORTSDIALOG_H
