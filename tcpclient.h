#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QFile>
#include "mashine.h"
#include "errorprocessor.h"
#include "reports/reportclass.h"

class tcpClient : public QObject, public errorProcessor
{
    Q_OBJECT

public:
    tcpClient(QObject *parent=nullptr);
    ~tcpClient();
    mashine *getMashine(int index);
    bool createObject(QByteArray array);
    bool deleteObject(object *ob, bool objectOnly=false);
    bool writeConfiguration(QString workingDir);
    dayGraph *readGraphFile(QString fullPath);//при использовании не забывать удалять полученные данные
    //строит отчет по заданным датам
    reportClass *createReport(reportType type, QDate startDate, QDate stopDate, int mashineIndex);//за удаление отчета отвечает вызывающий
    bool readConfiguration(QString workingDir);
    bool isNameExist(QString name,object *ob=nullptr);//если ob задан, то проверяется все, кроме данного объекта
    object *getObjectForAddress(int address, object *ob=nullptr);
    object *getObjectForName(QString name);
    int getMashinsCount();
    //перемещение машины в списке
    bool mashineUp(int index);
    bool mashineDown(int index);
    void connectToServer();
    void setIPAddress(QHostAddress address);
    void setPort(quint16 port);
    QHostAddress getIPAddress();
    quint16 getPort();
    bool isConnected();
    bool isConnecting();
    void sendCommand();
    void updateState();
    bool editObject(object *editedObject);



protected:
    QTcpSocket *socket;
    QHostAddress IPAddress;
    quint16 port;
    QTimer *waitTimer;
    serverCommand currentState;
    QVector<mashine*> mashinesArray;
    QByteArray incomingBuffer;
    void decodeStatistic(QDataStream *str);
    void decodeAnswer(QDataStream *str);
    void decodeError(QDataStream *str);
    void decErrorOrAnswer(QDataStream *str);


signals:
    void connectSignal();
    void errorSignal();
    void statisticUpdatedSignal();
    void serverAnswerSignal(QString answer);


protected slots:
    void connectSlot();
    void disconnectSlot();
    void readyReadSlot();
    void errorSlot(QAbstractSocket::SocketError error);
    void waitTimeSlot();


};

#endif // TCPCLIENT_H
