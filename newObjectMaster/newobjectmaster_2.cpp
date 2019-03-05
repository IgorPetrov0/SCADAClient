#include "newobjectmaster_2.h"
#include "ui_newobjectmaster_2.h"

newObjectMaster_2::newObjectMaster_2(QWidget *parent) :
    newObjectMasterPage(parent),
    ui(new Ui::newObjectMaster_2)
{
    ui->setupUi(this);
    stage=1;
    connect(ui->shiftCheckBox_2,SIGNAL(clicked(bool)),this,SLOT(shiftCheckSlot_2(bool)));
    connect(ui->shiftCheckBox_3,SIGNAL(clicked(bool)),this,SLOT(shiftCheckSlot_3(bool)));
    ui->shiftCheckBox_2->setChecked(false);
    ui->shiftCheckBox_3->setChecked(false);
    ui->startTimeEdit_2->setEnabled(false);
    ui->stopTimeEdit_2->setEnabled(false);
    ui->startTimeEdit_3->setEnabled(false);
    ui->stopTimeEdit_3->setEnabled(false);
    ui->startTimeEdit_1->setTime(QTime(8,0));
    ui->stopTimeEdit_1->setTime(QTime(17,0));
    ui->shiftCheckBox_3->setEnabled(false);
}
//////////////////////////////////////////////////////////////
newObjectMaster_2::~newObjectMaster_2(){
    delete ui;
}
///////////////////////////////////////////////////////////////
bool newObjectMaster_2::next(){
    mashine *mObject= static_cast<mashine*>(currentObject);
    //проверяем на пересечение времени смен
    bool error=false;
    if(ui->shiftCheckBox_2->isChecked()){
        int start1=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        int stop1=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        int start2=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        int stop2=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        if((start2>start1) && (start2<stop1)){
           error=true;
        }
        if((stop2>start1) && (stop2<stop1)){
           error=true;
        }
    }
    if(ui->shiftCheckBox_3->isChecked()){
        int start2=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        int stop2=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        int start3=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        int stop3=ui->startTimeEdit_1->time().msecsSinceStartOfDay();
        if((start3>start2) && (start3<stop2)){
           error=true;
        }
        if((stop3>start2) && (stop3<stop2)){
           error=true;
        }
    }
    if(error){
        QMessageBox box(this);
        box.setWindowTitle(tr("Ошибка"));
        box.setDefaultButton(QMessageBox::Ok);
        box.setText("Смены не должны пересекаться по времени");
        box.exec();
        return false;
    }

    mObject->setLineColor(ui->pushButton->getColor());
    mObject->setPathForStatistics(QApplication::applicationDirPath()+STAT_PATH);
    //формируем смены
    shift tmpShift;
    //первая и обязательная
    tmpShift.startTime=ui->startTimeEdit_1->time();
    tmpShift.stopTime=ui->stopTimeEdit_1->time();
    mObject->addShift(tmpShift);

    //вторая, если задана
    if(ui->shiftCheckBox_2->isChecked()){
        tmpShift.startTime=ui->startTimeEdit_2->time();
        tmpShift.stopTime=ui->stopTimeEdit_2->time();
        mObject->addShift(tmpShift);

        //третья, если задана
        if(ui->shiftCheckBox_3->isChecked()){
            tmpShift.startTime=ui->startTimeEdit_3->time();
            tmpShift.stopTime=ui->stopTimeEdit_3->time();
            mObject->addShift(tmpShift);
        }
    }

    QDataStream str(&objectData,QIODevice::WriteOnly);
    mObject->serialisation(&str);
    return true;
}
/////////////////////////////////////////////////////////////
void newObjectMaster_2::setObject(object **newObject){
    if(*newObject!=NULL){
        mashine *mObject = new mashine;
        *mObject=**newObject;
        delete *newObject;
        *newObject = mObject;
        currentObject=mObject;
    }
    else{
        qDebug("newObjectMaster_2::setObject : newObject is NULL");
    }
}
////////////////////////////////////////////////////////////////
QByteArray newObjectMaster_2::getData(){
    return objectData;
}
////////////////////////////////////////////////////////////////////////////////
void newObjectMaster_2::loadObject(object *existObject){
    if(existObject!=NULL){
        newObjectMasterPage::loadObject(existObject);
        mashine *mObject = static_cast<mashine*>(existObject);
        ui->pushButton->setColor(mObject->getLineColor());
        int count=mObject->getShiftsCount();
        if(count!=0){
            shift s=mObject->getShift(0);
            ui->startTimeEdit_1->setTime(s.startTime);
            ui->stopTimeEdit_1->setTime(s.stopTime);
            count--;
            if(count!=0){
                shift s=mObject->getShift(1);
                ui->startTimeEdit_2->setTime(s.startTime);
                ui->stopTimeEdit_2->setTime(s.stopTime);
                count--;
                if(count!=0){
                    shift s=mObject->getShift(2);
                    ui->startTimeEdit_3->setTime(s.startTime);
                    ui->stopTimeEdit_3->setTime(s.stopTime);
                }
            }
        }
    }
    else{
        qDebug("newObjectMaster_2::loadObject : existObject is NULL");
    }
}
//////////////////////////////////////////////////////////////////////////////////
void newObjectMaster_2::shiftCheckSlot_2(bool checked){
    if(checked){
        ui->startTimeEdit_2->setEnabled(true);
        ui->stopTimeEdit_2->setEnabled(true);
        ui->startTimeEdit_2->setTime(ui->stopTimeEdit_1->time());
        ui->shiftCheckBox_3->setEnabled(true);
    }
    else{
        ui->startTimeEdit_2->setEnabled(false);
        ui->stopTimeEdit_2->setEnabled(false);
        ui->startTimeEdit_2->setTime(QTime(0,0));
        ui->startTimeEdit_3->setEnabled(false);
        ui->stopTimeEdit_3->setEnabled(false);
        ui->startTimeEdit_3->setTime(QTime(0,0));
        ui->shiftCheckBox_3->setEnabled(false);
    }
}
//////////////////////////////////////////////////////////////////////////////////
void newObjectMaster_2::shiftCheckSlot_3(bool checked){
    if(checked){
        ui->startTimeEdit_3->setEnabled(true);
        ui->stopTimeEdit_3->setEnabled(true);
        ui->startTimeEdit_3->setTime(ui->stopTimeEdit_2->time());
    }
    else{
        ui->startTimeEdit_3->setEnabled(false);
        ui->stopTimeEdit_3->setEnabled(false);
        ui->startTimeEdit_3->setTime(QTime(0,0));
    }
}
