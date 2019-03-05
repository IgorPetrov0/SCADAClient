#include "newobjectmasterbase.h"
#include "ui_newobjectmasterbase.h"

newObjectMasterBase::newObjectMasterBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newObjectMasterBase)
{
    ui->setupUi(this);
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(nextSlot()));
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
    currentPage = new newObjectMaster_1(this);
    QRect g=currentPage->geometry();
    g.setX(0);
    g.setY(0);
    currentPage->setGeometry(g);
    currentObject = new object;
    currentPage->setObject(&currentObject);
    this->setWindowTitle(tr("Новый объект"));
    createMode=true;
}
/////////////////////////////////////////////////////////////////////
newObjectMasterBase::~newObjectMasterBase()
{
    delete ui;
}
////////////////////////////////////////////////////////////////////////////
QByteArray newObjectMasterBase::getObjectData(){
    return objectData;
}
////////////////////////////////////////////////////////////////////////////////
void newObjectMasterBase::loadObject(object *existObject){
    createMode=false;
    currentObject=existObject;
    currentPage->loadObject(existObject);
}
//////////////////////////////////////////////////////////////////////////////
void newObjectMasterBase::setNetCorePointer(tcpClient *pointer){
    baseWidget::setNetCorePointer(pointer);
    currentPage->setNetCorePointer(pointer);
}
//////////////////////////////////////////////////////////////////////////
void newObjectMasterBase::nextSlot(){
    if(!currentPage->next()){//если на странице ошибка, то ничего не делаем
        return;
    }
    switch(currentPage->getStage()){
        case(0):{//если стадия 0
            switch(currentObject->getType()){
                case(objectMashine):{//если тип "машина"
                    delete currentPage;
                    currentPage=new newObjectMaster_2(this);
                    currentPage->setNetCorePointer(netCorePointer);
                    break;
                }
            }
            break;
        }
        case(1):{//если стадия 1
            switch(currentObject->getType()){
                case(objectMashine):{//если тип "машина"
                    objectData=currentPage->getData();//
                    delete currentPage;
                    accept();
                    return;
                }
            }
            break;
        }
    }
    QRect g=currentPage->geometry();
    g.setX(0);
    g.setY(0);
    currentPage->setGeometry(g);
    if(createMode){
        currentPage->setObject(&currentObject);
    }
    else{
        currentPage->loadObject(currentObject);
    }
    currentPage->show();
}
