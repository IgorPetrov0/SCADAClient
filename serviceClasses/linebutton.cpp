#include "linebutton.h"


lineButton::lineButton(QWidget *parent) :
    QPushButton(parent)
{
    color=QColor(Qt::black);
}
////////////////////////////////////////////////////////////////
void lineButton::setColor(QColor color){
    this->color=color;
}
///////////////////////////////////////////////////////////////
QColor lineButton::getColor(){
    return color;
}
//////////////////////////////////////////////////////////////
void lineButton::paintEvent(QPaintEvent *event){
    QPushButton::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(color, 4, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(5,this->geometry().height()/2,this->geometry().width()-10,this->geometry().height()/2);
}
