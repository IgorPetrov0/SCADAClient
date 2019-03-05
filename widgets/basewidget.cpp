#include "basewidget.h"

baseWidget::baseWidget()
{
    netCorePointer=NULL;
}
///////////////////////////////////////////////////////////////////
void baseWidget::setNetCorePointer(tcpClient *pointer){
    netCorePointer=pointer;
}
///////////////////////////////////////////////////////////////////
void baseWidget::updateContent(){

}
