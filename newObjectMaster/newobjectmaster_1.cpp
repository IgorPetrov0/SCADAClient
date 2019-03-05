#include "newobjectmaster_1.h"
#include "ui_newobjectmaster_1.h"

newObjectMaster_1::newObjectMaster_1(QWidget *parent) :
    newObjectMasterPage(parent),
    ui(new Ui::newObjectMaster_1)
{
    ui->setupUi(this);
    ui->typeComboBox->addItem(tr("Машина"),objectMashine);
    stage=0;
}
/////////////////////////////////////////////////////////////////
newObjectMaster_1::~newObjectMaster_1()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////
bool newObjectMaster_1::next(){
    QString name=ui->nameLineEdit->text();
    if(name.isEmpty()){
        QMessageBox box(this);
        box.setDefaultButton(QMessageBox::Ok);
        box.setWindowTitle(tr("Ошибка"));
        box.setText(tr("Имя объекта не должно быть пустым."));
        box.exec();
        return false;
    }
    if(netCorePointer->isNameExist(name,currentObject)){//проверяем все объекты кроме текущего
        QMessageBox box(this);
        box.setDefaultButton(QMessageBox::Ok);
        box.setText(tr("Объект с именем ")+name+tr(" уже существует.\n Выберите другое имя объекта."));
        box.exec();
        return false;
    }
    int address=ui->addressSpinBox->value();
    object *tmp=netCorePointer->getObjectForAddress(ui->addressSpinBox->value(),currentObject);
    if(tmp!=NULL){
        QString existObjectName=tmp->getName();
        QMessageBox box(this);
        box.setDefaultButton(QMessageBox::Ok);
        box.setText(tr("В базе уже есть объект с адресом ")+QString::number(address)+tr("\n по имени ")+
                    existObjectName+tr(" .\nЗадайте другой адрес."));
        box.exec();
        return false;
    }

    currentObject->setName(name);
    currentObject->setDescription(ui->textEdit->document()->toPlainText());
    currentObject->setAddress(address);
    currentObject->setType((objectType)ui->typeComboBox->currentData().toInt());
    return true;
}
///////////////////////////////////////////////////////////////////////////
void newObjectMaster_1::setObject(object **newObject){

    if(newObject!=NULL){
        currentObject=*newObject;
        ui->addressSpinBox->setValue(currentObject->getAddress());
        ui->nameLineEdit->setText(currentObject->getName());
        ui->textEdit->setText(currentObject->getDescription());
        int size=ui->typeComboBox->count();//выставляем тип в комбо-боксе
        for(int n=0;n!=size;n++){
            int m=ui->typeComboBox->itemData(n).toInt();
            if(m==currentObject->getType()){
                ui->typeComboBox->setCurrentIndex(m);
            }
        }
    }
    else{
        qDebug("newObjectMaster::setObject(object *newObject) : New bject is NULL!!");
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void newObjectMaster_1::loadObject(object *existObject){

    if(existObject!=NULL){
        newObjectMasterPage::loadObject(existObject);
        ui->addressSpinBox->setValue(currentObject->getAddress());
        ui->nameLineEdit->setText(currentObject->getName());
        ui->textEdit->setText(currentObject->getDescription());
        ui->nameLineEdit->setEnabled(false);//запрещаем редактировать имя т.к. оно должно быть уникально
        ui->typeComboBox->setEnabled(false);//запрещаем редактировать тип
        int size=ui->typeComboBox->count();//выставляем тип в комбо-боксе
        for(int n=0;n!=size;n++){
            int m=ui->typeComboBox->itemData(n).toInt();
            if(m==currentObject->getType()){
                ui->typeComboBox->setCurrentIndex(m);
            }
        }
    }
    else{
        qDebug("newObjectMaster::setObject(object *newObject) : Exist object is NULL!!");
    }
}
