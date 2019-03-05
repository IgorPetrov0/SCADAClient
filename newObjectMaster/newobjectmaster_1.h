#ifndef NEWOBJECTMASTER_1_H
#define NEWOBJECTMASTER_1_H

#include <QMessageBox>
#include "newObjectMaster/newobjectmasterpage.h"
#include "object.h"

namespace Ui {
class newObjectMaster_1;
}

class newObjectMaster_1 : public newObjectMasterPage
{
    Q_OBJECT

public:
    explicit newObjectMaster_1(QWidget *parent);
    ~newObjectMaster_1();
    virtual bool next();
    virtual void setObject(object **newObject);
    virtual void loadObject(object *existObject);

private:
    Ui::newObjectMaster_1 *ui;
};

#endif // NEWOBJECTMASTER_1_H
