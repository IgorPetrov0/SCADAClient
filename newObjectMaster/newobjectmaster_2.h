#ifndef NEWOBJECTMASTER_2_H
#define NEWOBJECTMASTER_2_H

#include <QWidget>
#include <QMessageBox>
#include "newObjectMaster/newobjectmasterpage.h"
#include "mashine.h"
#include "defines.h"

namespace Ui {
class newObjectMaster_2;
}

class newObjectMaster_2 : public newObjectMasterPage
{
    Q_OBJECT

public:
    explicit newObjectMaster_2(QWidget *parent = 0);
    ~newObjectMaster_2();
    virtual bool next();
    virtual void setObject(object **newObject);
    virtual QByteArray getData();
    virtual void loadObject(object *existObject);

protected slots:
    void shiftCheckSlot_2(bool checked);
    void shiftCheckSlot_3(bool checked);

private:
    Ui::newObjectMaster_2 *ui;
};

#endif // NEWOBJECTMASTER_2_H
