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
    tcpClient(QObject *parent=0);
    ~tcpClient();
    mashine *getMashine(int index);
    bool createObject(QDataStream *str);
    void deleteObject(object *ob, bool objectOnly=false);
    bool writeConfiguration(QString workingDir);
    dayGraph *readGraphFile(QString fullPath);//при использовании не забывать удалять полученные данные
    //строит отчет по заданным датам
    reportClass *createReport(reportType type, QDate startDate, QDate stopDate, int mashineIndex);//за удаление отчета отвечает вызывающий
    bool readConfiguration(QString workingDir);
    bool isNameExist(QString name,object *ob=NULL);//если ob задан, то проверяется все, кроме данного объекта
    object *getObjectForAddress(int address, object *ob=NULL);
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

signals:
    void connectSignal();
    void errorSignal();

protected:
    QTcpSocket *socket;
    QHostAddress IPAddress;
    quint16 port;
    QTimer *waitTimer;

protected slots:
    void connectSlot();
    void disconnectSlot();
    void readyReadSlot();
    void errorSlot(QAbstractSocket::SocketError error);


};

#endif // TCPCLIENT_H
