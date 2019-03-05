#include "kalendardialog.h"
#include "ui_kalendardialog.h"

kalendarDialog::kalendarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kalendarDialog)
{
    ui->setupUi(this);
    connect(ui->startCalendar,SIGNAL(selectionChanged()),this,SLOT(startDateSelectedSlot()));
    connect(ui->stopCalendar,SIGNAL(selectionChanged()),this,SLOT(stopDateSelectedSlot()));
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
    startDateSelectedSlot();
    stopDateSelectedSlot();
}
////////////////////////////////////////////////////////////////
kalendarDialog::~kalendarDialog()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////
void kalendarDialog::startDateSelectedSlot(){
    ui->startDataLabel->setText(ui->startCalendar->selectedDate().toString("dd MM yyyy"));
}
////////////////////////////////////////////////////////////////
void kalendarDialog::stopDateSelectedSlot(){
    ui->stopDataLabel->setText(ui->stopCalendar->selectedDate().toString("dd MM yyyy"));
}
/////////////////////////////////////////////////////////////////////////////////////////////
QDate kalendarDialog::getStartDate(){
    QDate startDate=ui->startCalendar->selectedDate();
    QDate stopDate=ui->stopCalendar->selectedDate();
    if(startDate<=stopDate){
        return startDate;
    }
    return stopDate;
}
//////////////////////////////////////////////////////////////////////////
QDate kalendarDialog::getStopDate(){
    QDate startDate=ui->startCalendar->selectedDate();
    QDate stopDate=ui->stopCalendar->selectedDate();
    if(startDate>=stopDate){
        return startDate;
    }
    return stopDate;
}
