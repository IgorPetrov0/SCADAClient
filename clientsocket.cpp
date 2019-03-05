#include "clientsocket.h"

clientSocket::clientSocket(QObject *parent):
    QTcpSocket(parent)
{
    connect(this,SIGNAL(disconnected()),this,SLOT(disconnectedSlot()));
    connect(this,SIGNAL(readyRead()),this,SLOT(readClient()));
}
////////////////////////////////////////////////////////////////////////////////
void clientSocket::setIndex(int index){
    socketIndex=index;
}
///////////////////////////////////////////////////////////////////////////////
void clientSocket::disconnectedSlot(){
    emit socketDisconnected(socketIndex);
}
////////////////////////////////////////////////////////////////////////////
void clientSocket::readClient(){

}
