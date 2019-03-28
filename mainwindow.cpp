#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateTimer = new QTimer(this);
    connect(ui->actionNewObject,SIGNAL(triggered(bool)),this,SLOT(createNewObjectSlot()));
    connect(ui->mainTab,SIGNAL(addObjectSignal()),this,SLOT(createNewObjectSlot()));
    connect(ui->mainTab,SIGNAL(editObjectSignal(objectType,int)),this,SLOT(editObjectSlot(objectType,int)));
    connect(ui->mainTab,SIGNAL(deleteObjectSignal(objectType,int)),this,SLOT(deleteObjectSlot(objectType,int)));
    connect(ui->openGraphAction,SIGNAL(triggered(bool)),this,SLOT(openGraphSlot(int)));
    connect(ui->actionSerialPorts,SIGNAL(triggered(bool)),this,SLOT(serialPortsSlot()));
    connect(ui->mainTab,SIGNAL(createReportSygnal(reportType,int)),this,SLOT(createReport(reportType,int)));
    connect(ui->mainTab,SIGNAL(enotherDaySignal(int)),this,SLOT(openGraphSlot(int)));
    connect(ui->actionNetSetting,SIGNAL(triggered(bool)),this,SLOT(netSettingSlot()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateTimeSlot()));
    connect(&netCore,SIGNAL(errorSignal()),this,SLOT(netErrorSlot()));
    connect(&netCore,SIGNAL(connectSignal()),this,SLOT(netConnectSlot()));
    connect(&netCore,SIGNAL(statisticUpdated()),this,SLOT(netUpdateStatistic()));
    appPath=QApplication::applicationDirPath();

    conIndicator = new connectionIndicator(tr("Соединение с сервером"));
    conIndicator->setMinimumSize(30,10);
    statusBar()->addPermanentWidget(conIndicator,0);
    statusBar()->setSizeGripEnabled(true);

    errorMessageBox=NULL;
}
////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{ 
    if(errorMessageBox!=NULL){
        delete errorMessageBox;
    }
    delete conIndicator;
    delete ui;
}
/////////////////////////////////////////////////////////////////
void MainWindow::resizeEvent(QResizeEvent *event){
    ui->mainTab->setGeometry(this->centralWidget()->geometry());
}
////////////////////////////////////////////////////////////////////////
void MainWindow::createNewObjectSlot(){
    newObjectMasterBase master;
    master.setNetCorePointer(&netCore);
    if(master.exec()==QDialog::Accepted){
        QByteArray arr=master.getObjectData();
        QDataStream str(&arr,QIODevice::ReadOnly);
        if(!netCore.createObject(&str)){
            errorMessage(netCore.getLastError());
        }
        ui->mainTab->updateContent();
    }
}
///////////////////////////////////////////////////////////////////////////////////
void MainWindow::editObjectSlot(objectType type, int index){
    newObjectMasterBase master;
    object *tmp=NULL;
    switch(type){
        case(objectMashine):{
            tmp=netCore.getMashine(index);
            break;
        }
        default:{
            qDebug("MainWindow::editObjectSlot : Unknow object type.");
            return;
        }
    }
    if(tmp==NULL){
        errorMessage(netCore.getLastError());
    }
    master.loadObject(tmp);
    master.setNetCorePointer(&netCore);
    if(master.exec()==QDialog::Accepted){
        ui->mainTab->updateContent();

    }
}
////////////////////////////////////////////////////////////////////////////////
void MainWindow::deleteObjectSlot(objectType type, int index){
    object *tmp=NULL;
    switch(type){
        case(objectMashine):{
            tmp=netCore.getMashine(index);
            break;
        }
        default:{
            qDebug("MainWindow::editObjectSlot : Unknow object type.");
            return;
        }
    }
    if(tmp!=NULL){
        deleteObjectDialog dialog(this,tmp);
        switch(dialog.exec()){
            case(DELETE_OBJECT_ONLY):{
                netCore.deleteObject(tmp,true);
                break;
            }
            case(DELETE_ALL):{
                netCore.deleteObject(tmp,false);
                break;
            }
            case(QDialog::Rejected):{
                return;
                break;
            }
        }
        ui->mainTab->updateContent();
    }
    else{
        qDebug("MainWindow::deleteObjectSlot : Object is NULL");
    }


}
///////////////////////////////////////////////////////////////////////////////
void MainWindow::openGraphSlot(int index){

    //!!!!!!!!!!!! Всместо стандартного файлового окна открывать свое!!!!!!!!!!!!!!!!!!
    //! Нечего клиенту копаться в файловой системе сервера!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!
    //!
    //!
    //!
//    QFileDialog dialog(this);
//    if(index==-1){
//        dialog.setDirectory(QApplication::applicationDirPath());
//    }
//    else{
//        mashine *tmpMashine=netCore.getMashine(index);
//        if(tmpMashine!=NULL){
//            dialog.setDirectory(tmpMashine->getPathForStatistics()+"/"+tmpMashine->getName());
//        }
//        else{
//            dialog.setDirectory(QApplication::applicationDirPath());
//        }
//    }
//    if(dialog.exec()==QDialog::Accepted){
//        QStringList list=dialog.selectedFiles();
//        dayGraph *dayStruct = netCore.readGraphFile(list.at(0));
//        if(dayStruct==NULL){
//            errorMessage(statCore.getLastError());
//            return;
//        }
//        ui->mainTab->showGraph(dayStruct);
//    }
}
///////////////////////////////////////////////////////////////////////////////////
void MainWindow::serialPortsSlot(){


}
////////////////////////////////////////////////////////////////////////////
void MainWindow::createReport(reportType type, int index){
    kalendarDialog dialog(this);
    dialog.setWindowTitle(tr("Выберите диапазон дат"));
    if(dialog.exec()==QDialog::Accepted){
        reportClass *report=netCore.createReport(type,dialog.getStartDate(),dialog.getStopDate(),index);
        if(report==NULL){
            errorMessage(netCore.getLastError());
            return;
        }
        reportDialog rDialog(this);
        rDialog.showReport(report);
        rDialog.exec();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::updateTimeSlot(){
    if(netCore.isConnected()){//если соединение установлено
        conIndicator->setState(true);
    }
    else if(!netCore.isConnecting()){//иначе, если соединение в данный момент не устанавливается <connectED|connecTING>
        netCore.connectToServer();
        conIndicator->setState(false);
    }
    netCore.updateState();
    ui->mainTab->updateContent();
}
///////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::netSettingSlot(){
    netDialog dialog;
    dialog.setIPAddress(netCore.getIPAddress());
    dialog.setPort(netCore.getPort());
    if(dialog.exec()==QDialog::Accepted){
        netCore.setIPAddress(dialog.getIPAddress());
        netCore.setPort(dialog.getPort());
        appPath=QApplication::applicationDirPath();
        if(!netCore.writeConfiguration(appPath)){
            errorMessage(netCore.getLastError());
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////
void MainWindow::netErrorSlot(){
    errorMessage(tr("Ошибка соединения с сервером: \n")+netCore.getLastError());
}
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::netConnectSlot(){

}
//////////////////////////////////////////////////////////////////////////////////////
void MainWindow::netUpdateStatistic(){
    ui->mainTab->updateContent();
}
//////////////////////////////////////////////////////////////////////////////////
void MainWindow::initialise(){
    QString appPath=QApplication::applicationDirPath();
    ui->mainTab->setNetCorePointer(&netCore);
    if(!netCore.readConfiguration(appPath)){
        errorMessage(netCore.getLastError());
        return;
    }
    netCore.connectToServer();
    updateTimer->start(10000);
}
///////////////////////////////////////////////////////////////////////////////////
void MainWindow::errorMessage(QString error){
    if(errorMessageBox==NULL){
        errorMessageBox = new QMessageBox(this);
        errorMessageBox->setDefaultButton(QMessageBox::Ok);
        errorMessageBox->setWindowTitle(tr("Ошибка"));
        errorMessageBox->setText(error);
        errorMessageBox->exec();
        delete errorMessageBox;
        errorMessageBox=NULL;
    }
}
///////////////////////////////////////////////////////////////////////////////////
