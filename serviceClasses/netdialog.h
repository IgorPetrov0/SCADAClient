#ifndef NETDIALOG_H
#define NETDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class netDialog;
}

class netDialog : public QDialog
{
    Q_OBJECT

public:
    explicit netDialog(QWidget *parent = 0);
    ~netDialog();
    void setPort(qint16 port);
    qint16 getPort();
    void setIPAddress(QHostAddress address);
    QHostAddress getIPAddress();

protected:
    QString oldText;


protected slots:

private:
    Ui::netDialog *ui;
};

#endif // NETDIALOG_H
