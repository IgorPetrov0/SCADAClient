#include "tcpclient.h"

tcpClient::tcpClient(QObject *parent):
    QObject(parent)
{
    waitTimer = new QTimer(this);
    waitTimer->setSingleShot(true);
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(errorSlot(QAbstractSocket::SocketError)));
    socket->abort();
}
/////////////////////////////////////////////////
tcpClient::~tcpClient(){
    delete waitTimer;
}
//////////////////////////////////////////////////////////
mashine *tcpClient::getMashine(int index){

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
        QAbstractSocket::SocketState state=socket->state();
        socket->connectToHost(IPAddress,port);
        state=socket->state();
        QString name=socket->peerName();
        int t=0;
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
    QAbstractSocket::SocketState state=socket->state();
    if(socket->state()==QAbstractSocket::UnconnectedState){
        return false;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////
void tcpClient::connectSlot(){

}
///////////////////////////////////////////////////////////////////////////
void tcpClient::disconnectSlot(){

}
///////////////////////////////////////////////////////////////////////////
void tcpClient::readyReadSlot(){

}
//////////////////////////////////////////////////////////////////////////////
void tcpClient::errorSlot(QAbstractSocket::SocketError error){
    setLastError(socket->errorString());
    emit errorSignal();
}
