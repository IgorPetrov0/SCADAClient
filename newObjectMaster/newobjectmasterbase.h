#ifndef NEWOBJECTMASTERBASE_H
#define NEWOBJECTMASTERBASE_H

#include <QDialog>
#include "newObjectMaster/newobjectmasterpage.h"
#include "newObjectMaster/newobjectmaster_1.h"
#include "newObjectMaster/newobjectmaster_2.h"
#include "object.h"

namespace Ui {
class newObjectMasterBase;
}

class newObjectMasterBase : public QDialog, public baseWidget
{
    Q_OBJECT

public:
    explicit newObjectMasterBase(QWidget *parent = 0);
    ~newObjectMasterBase();
    QByteArray getObjectData();
    void loadObject(object *existObject);
    virtual void setNetCorePointer(tcpClient *pointer);


protected:
    newObjectMasterPage *currentPage;
    object *currentObject;
    QByteArray objectData;
    bool createMode;//режим работы: false - редактирование true - создание

protected slots:
    void nextSlot();


private:
    Ui::newObjectMasterBase *ui;
};

#endif // NEWOBJECTMASTERBASE_H
