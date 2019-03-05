#include "reportdialog.h"
#include "ui_reportdialog.h"

reportDialog::reportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reportDialog)
{
    ui->setupUi(this);
}
///////////////////////////////////////////////////////////////////////////////////////
reportDialog::~reportDialog()
{
    if(currentReport!=NULL){
        switch(currentReport->getType()){
            case(REPORT_SHIFT):{
                shiftReport *newReport = static_cast<shiftReport*>(currentReport);
                delete newReport;
                break;
            }


            default:{
                delete currentReport;
                return;
            }
        }
    }
    delete ui;
}
//////////////////////////////////////////////////////////////////////////////////////
void reportDialog::showReport(reportClass *report){
    currentReport=report;
    switch(report->getType()){
        case(REPORT_SHIFT):{
            shiftReport *newReport = static_cast<shiftReport*>(report);
            this->setWindowTitle(tr("Отчет по сменам."));
            showReportShift(newReport);
            break;
        }
        default:{
            return;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////
void reportDialog::showReportShift(shiftReport *report){
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(report->count());
    QStringList headerList;
    headerList.append(tr("Номер смены"));
    headerList.append(tr("Начало"));
    headerList.append(tr("Окончание"));
    headerList.append(tr("Количество \n за смену"));
    headerList.append(tr("Средняя производительность \n в час"));
    headerList.append(tr("Время простоя \n всего"));
    headerList.append(tr("Время простоя \n без причины"));
    headerList.append(tr("Время отключенного \n состояния"));
    ui->tableWidget->setHorizontalHeaderLabels(headerList);
    for(int n=0;n!=8;n++){//подгоняем размеры столбцов под текс хидера
        //ui->tableWidget->setColumnWidth(n,);
    }
    for(int n=0;n!=report->count();n++){
        shiftReportStructure cStruct=report->getReportItem(n);
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(cStruct.shift+1));
        ui->tableWidget->setItem(n,0,item);
        item = new QTableWidgetItem(cStruct.startTime.toString("dd_MM_yyyy hh:mm"));
        ui->tableWidget->setItem(n,1,item);
        item = new QTableWidgetItem(cStruct.stopTime.toString("dd_MM_yyyy hh:mm"));
        ui->tableWidget->setItem(n,2,item);
        item = new QTableWidgetItem(QString::number(cStruct.count));
        ui->tableWidget->setItem(n,3,item);
        item = new QTableWidgetItem(QString::number(cStruct.performance));
        ui->tableWidget->setItem(n,4,item);
        item = new QTableWidgetItem(cStruct.stayTime.toString("hh:mm"));
        ui->tableWidget->setItem(n,5,item);
        item = new QTableWidgetItem(cStruct.stayWithoutReason.toString("hh:mm"));
        ui->tableWidget->setItem(n,6,item);
        item = new QTableWidgetItem(cStruct.noResponceTime.toString("hh:mm"));
        ui->tableWidget->setItem(n,7,item);
    }
    int size=report->fileNamesCount();
    ui->fileNamesTable->setColumnCount(1);
    ui->fileNamesTable->setRowCount(size);
    for(int n=0;n!=size;n++){
        QTableWidgetItem *item = new QTableWidgetItem(report->getFileName(n));
        ui->fileNamesTable->setItem(n,0,item);
    }
}
