#include "netdialog.h"
#include "ui_netdialog.h"

netDialog::netDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::netDialog)
{
    ui->setupUi(this);
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
/////////////////////////////////////////////////////////////////
netDialog::~netDialog()
{
    delete ui;
}
///////////////////////////////////////////////////////////////////////////////////////////
void netDialog::setPort(qint16 port){
    QString str=QString::number(port);
    if(!str.isEmpty()){
        ui->portLineEdit->setText(str);
    }
}
//////////////////////////////////////////////////////////////////////////////
qint16 netDialog::getPort(){
    QString str=ui->portLineEdit->text();
    if(!str.isEmpty()){
        return str.toInt();
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
void netDialog::setIPAddress(QHostAddress address){
    QString str=address.toString();
    if(!str.isEmpty()){
        ui->IPLineEdit->setText(str);
    }
}
/////////////////////////////////////////////////////////////
QHostAddress netDialog::getIPAddress(){
    QHostAddress address;
    address.setAddress(ui->IPLineEdit->text());
    return address;

}
