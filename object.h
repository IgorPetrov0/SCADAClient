#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QDataStream>
#include <QVector>
#include "defines.h"
#include "logic/objectport.h"


class object : public QObject
{
    Q_OBJECT
public:
    explicit object(QObject *parent = nullptr);
    ~object();
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
    bool isRequestEnable();
    void setRequestEnable(bool enable);
    int getPortsCount() const;
    bool isPortExist(int number,objectPort *port=nullptr);
    objectPort *getPort(int index) const;
    objectPort *getPortByNumber(int number) const;
    void addPort(objectPort *port);
    void removePort(int index);
    objectState getCurrentState() const;
    void setCurrentState(const objectState &value);
    QString getCurrentStateString();
    QTime getStateSetTime() const;
    int getPortIndex(int portNumber);

    object& operator=(const object& right);

    virtual void serialisation(QDataStream *str);
    virtual bool deserialisation(QDataStream *str);//полная десериализация
    virtual bool deserialisationContinue(QDataStream *str);//частичная. только для своих данных без данных родителя

protected:
    unsigned int address;//сетевой адрес в сети RS485
    QString name;
    QString description;
    objectType type;
    bool requestEnable;
    bool online;
    QVector<objectPort*>ports;
    objectState currentState;
    QTime stateSetTime;

signals:

public slots:
};

#endif // OBJECT_H
