#ifndef NEWOBJECTMASTERPAGE_H
#define NEWOBJECTMASTERPAGE_H

#include <QWidget>
#include "object.h"
#include "widgets/basewidget.h"


class newObjectMasterPage : public QWidget, public baseWidget
{
    Q_OBJECT
public:
    newObjectMasterPage(QWidget *parent);
    int getStage() const;
    virtual void setObject(object **newObject);
    virtual void loadObject(object *existObject);
    virtual QByteArray getData();
    virtual bool next();


protected:
    int stage;
    object *currentObject;
    QByteArray objectData;
    bool createMode;//режим работы: false - редактирование true - создание



};

#endif // NEWOBJECTMASTERPAGE_H
