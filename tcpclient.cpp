#include "tcpclient.h"

tcpClient::tcpClient(QObject *parent):
    QObject(parent)
{
    waitTimer = new QTimer(this);
    waitTimer->setSingleShot(true);
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));
    socket->abort();
    currentState=SERVERCOMMAND_NO_COMMAND;
}
/////////////////////////////////////////////////
tcpClient::~tcpClient(){
    delete waitTimer;
}
//////////////////////////////////////////////////////////
mashine *tcpClient::getMashine(int index){
    if((index>=mashinesArray.size())||(index<0)){
        qDebug("netCore::getMashine : index out of range");
        return NULL;
    }
    return mashinesArray.at(index);
}
///////////////////////////////////////////////////////////
bool tcpClient::createObject(QDataStream *str){

}
//////////////////////////////////////////////////////////////////////
void tcpClient::deleteObject(object *ob, bool objectOnly){

}
///////////////////////////////////////////////////////////////////////
bool tcpClient::writeConfiguration(QString workingDir){
    QFile file(workingDir+"/"+CONFIG_FILE_NAME);
    if(!file.open(QIODevice::WriteOnly)){
        setLastError(tr("Невозможно открыть файл конфигурации."));
        return false;
    }
    QDataStream str(&file);
    str<<QString(SIGNATURE);
    str<<(float)CUR_VERSION;
    QString ipAddress=IPAddress.toString();
    str<<ipAddress;
    str<<port;

    file.close();
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
reportClass *tcpClient::createReport(reportType type, QDate startDate, QDate stopDate, int mashineIndex){

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool tcpClient::readConfiguration(QString workingDir){
    QFile file(workingDir+"/"+CONFIG_FILE_NAME);
    if(!file.open(QIODevice::ReadOnly)){
        setLastError(tr("Невозможно открыть файл конфигурации."));
        return false;
    }
    QDataStream str(&file);
    QString sig;
    str>>sig;
    if(sig!=SIGNATURE){
        setLastError(tr("Ошибка чтения сигнатуры конфигурационного файла"));
        file.close();
        return false;
    }
    float v;
    str>>v;//получаем версию
    if(v>CUR_VERSION){
        setLastError(tr("Конфигурационный файл создан в болеее новой версии программы."));
        file.close();
        return false;
    }
    QString ipAddress;
    str>>ipAddress;
    IPAddress.setAddress(ipAddress);
    str>>port;

    file.close();
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////
bool tcpClient::isNameExist(QString name, object *ob){

}
/////////////////////////////////////////////////////////////////////////////////////////////
object *tcpClient::getObjectForAddress(int address, object *ob){

}
////////////////////////////////////////////////////////////////////////
int tcpClient::getMashinsCount(){
    return mashinesArray.size();
}
///////////////////////////////////////////////////////////////////////
bool tcpClient::mashineUp(int index){

}
/////////////////////////////////////////////////////////////////////////
bool tcpClient::mashineDown(int index){

}
/////////////////////////////////////////////////////////////////
void tcpClient::connectToServer(){
    if((!IPAddress.isNull()) && (port!=0)){
        socket->connectToHost(IPAddress,port);
    }
}
/////////////////////////////////////////////////////////////////////////
void tcpClient::setIPAddress(QHostAddress address){
    IPAddress=address;
}
///////////////////////////////////////////////////////////////////////
void tcpClient::setPort(quint16 port){
    this->port=port;
}
//////////////////////////////////////////////////////////////////////////
QHostAddress tcpClient::getIPAddress(){
    return IPAddress;
}
//////////////////////////////////////////////////////////////////////////
quint16 tcpClient::getPort(){
    return port;
}
//////////////////////////////////////////////////////////////////////////////
bool tcpClient::isConnected(){
    if(socket->state()==QAbstractSocket::ConnectedState){
        return true;
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////
bool tcpClient::isConnecting(){
    if(socket->state()==QAbstractSocket::ConnectingState){
        return true;
    }
    return false;
}
///////////////////////////////////////////////////////////////////////////
void tcpClient::sendCommand(){

}
////////////////////////////////////////////////////////////////////////////
void tcpClient::updateState(){
    if(socket->state()==QAbstractSocket::ConnectedState){
        currentState=SERVERCOMMAND_GET_STATISTIC;
        QByteArray array;
        QDataStream str(&array,QIODevice::WriteOnly);
        str<<qint64(sizeof(qint64)+2);
        str<<(uchar)TCP_PACKET_COMMAND;
        str<<(uchar)currentState;
        socket->write(array);
        socket->flush();
    }
}
/////////////////////////////////////////////////////////////////////////////
void tcpClient::decodeStatistic(QDataStream *str){
    int size=mashinesArray.size();
    QVector<mashine*>tmpVector;
    *str>>size;
    for(int n=0;n!=size;n++){
        mashine *tmpMashine = new mashine;
        tmpMashine->netDeserialise(str);
        tmpVector.append(tmpMashine);
    }
    //ищем и переписываем одноименные машины т.к. порядок машин у клиента и сервера может отличаться
    int arraySize=mashinesArray.size();
    for(int n=0;n!=size;n++){
        int m=0;
        for(;m!=arraySize;m++){
            mashine *tmpMashine=mashinesArray.at(m);
            if(tmpVector.at(n)->getName()==tmpMashine->getName()){
                delete tmpMashine;
                mashinesArray[m]=tmpVector.at(n);
                break;
            }
        }
        if(m==arraySize){//если машина не найдена,
            mashinesArray.append(tmpVector.at(n));
        }
    }



}
////////////////////////////////////////////////////////////////////////
void tcpClient::connectSlot(){

}
///////////////////////////////////////////////////////////////////////////
void tcpClient::disconnectSlot(){

}
///////////////////////////////////////////////////////////////////////////
void tcpClient::readyReadSlot(){
    qint64 packetSize=0;
    incomingBuffer.append(socket->readAll());
    QDataStream str(incomingBuffer);

    str>>packetSize;
    if(packetSize==incomingBuffer.size()){
        switch(currentState){
            case(SERVERCOMMAND_GET_STATISTIC):{//если ждем статистику от сервера
                uchar type;
                str>>type;
                if(type==TCP_PACKET_STATISTIC){
                    decodeStatistic(&str);
                }
                else{
                    setLastError(tr("Неверный формат пакета от сервера"));
                    emit errorSignal();
                }
                break;
            }
        }
        incomingBuffer.clear();
    }
    else if(packetSize<incomingBuffer.size()){
        setLastError(tr("Неверный формат пакета от сервера"));
        emit errorSignal();
        incomingBuffer.clear();
    }
}
//////////////////////////////////////////////////////////////////////////////
void tcpClient::errorSlot(QAbstractSocket::SocketError error){
    setLastError(socket->errorString());
    emit errorSignal();
}
////////////////////////////////////////////////////////////////////////////
void tcpClient::waitTimeSlot(){

}
