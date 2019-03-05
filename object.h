#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QDataStream>
#include "defines.h"

enum objectType:int{
    objectMashine,
    objectUnknow
};



class object : public QObject
{
    Q_OBJECT
public:
    explicit object(QObject *parent = nullptr);

    int getAddress() const;
    void setAddress(unsigned int value);
    QString getName() const;
    void setName(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);
    objectType getType() const;
    void setType(const objectType &value);
    QString getTypeString();
    bool isOnline();
    void setOnline(bool value);

    object& operator=(const object& right);

    virtual void serialisation(QDataStream *str);
    virtual void deserialisation(QDataStream *str);//полная десериализация
    virtual void deserialisationContinue(QDataStream *str);//частичная. только для своих данных без данных родителя



protected:
    unsigned int address;//сетевой адрес в сети RS485
    QString name;
    QString description;
    objectType type;
    bool requestEnable;
    bool online;

signals:

public slots:
};

#endif // OBJECT_H
