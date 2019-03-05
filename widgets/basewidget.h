#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include "tcpclient.h"

class baseWidget
{
public:
    baseWidget();
    virtual void setNetCorePointer(tcpClient *pointer);
    virtual void updateContent();


protected:
    tcpClient *netCorePointer;

};

#endif // BASEWIDGET_H
