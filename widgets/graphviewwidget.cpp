#include "graphviewwidget.h"

graphViewWidget::graphViewWidget(QWidget *parent)
    : QWidget(parent)
{
    graphArray=NULL;
    xFactor=2;
    yFactor=1;
    resizeXFactor=2;
    xOffset=0;
    posY=0;
    maxValue=0;
    scrollBarPointer=nullptr;
    this->setMouseTracking(true);
}
//////////////////////////////////////////////////////////////////////////////////
void graphViewWidget::visualiseGraph(dayGraph *array){
    maxValue=array->minutesArray[0].value;
    for(int n=1;n!=1440;n++){
        if(maxValue<array->minutesArray[n].value){
            maxValue=array->minutesArray[n].value;
        }
    }
    graphArray=array;
    calcFactors();
}
///////////////////////////////////////////////////////////////////////////
void graphViewWidget::mouseMoveEvent(QMouseEvent *event){
    mousePosX=event->x();
    mousePosY=event->y();
    if(graphArray!=NULL){
        calculateRails((mousePosX+xOffset)/xFactor);//позиция в массиве зависит от позиции мыши на экране);
    }
    emit mouseMoveSignal(mousePosX,posY);
    update();
}
///////////////////////////////////////////////////////////////////////////
void graphViewWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        if(this->hasMouseTracking()){
            setMouseTracking(false);
            updateContent();
        }
        else{
            setMouseTracking(true);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////
void graphViewWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    QRect rect;
    rect.setX(0);
    rect.setY(0);
    rect.setWidth(this->width()-2);
    rect.setHeight(this->height()-2);
    painter.drawRect(rect);
    painter.setPen(QPen(Qt::black,2,Qt::SolidLine));

    if(graphArray!=NULL){
        for(int n=0;n!=1440;n++){
            minutePoint tmpPoint=graphArray->minutesArray[n];
            int graphValue=graphZero-tmpPoint.value*yFactor;
            switch(tmpPoint.event){
                case(EVENT_OK):{
                    painter.setPen(QPen(QColor(),2,Qt::SolidLine));
                    break;
                }
            }
            int xPos=xFactor+xOffset;
            if(n==0){
                painter.drawPoint(n*xFactor-xOffset,graphValue);
            }
            else{
                int prevValue=graphZero-graphArray->minutesArray[n-1].value*yFactor;
                painter.drawLine((n-1)*xFactor-xOffset,prevValue,n*xFactor-xOffset,graphValue);
            }
        }
        //направляющие
        painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
        painter.drawLine(0,posY,this->width(),posY);//горизонтальная
        painter.drawLine(mousePosX,0,mousePosX,this->height()-0);//вертикальная

        //для отладки
        painter.drawText(10,10,"xFactor="+QString::number(xFactor));
        painter.drawText(10,20,"mousePosX="+QString::number(mousePosX));
        painter.drawText(10,30,"xOffset="+QString::number(xOffset));
    }
}
//////////////////////////////////////////////////////////////////////////////////////
void graphViewWidget::calculateRails(int posInArray){
    if(graphArray!=NULL){
        visibleValue=QString::number(graphArray->minutesArray[posInArray].value);//отображаемое значение
        QTime time=QTime::fromMSecsSinceStartOfDay(posInArray*60000);
        visibleDateTime=graphArray->date.toString("dd_MM_yyyy ")+time.toString("hh:mm");
        switch(graphArray->minutesArray[posInArray].event){
            case(EVENT_OK):{
                visibleEvent=tr("ОК");
                break;
            }
            case(EVENT_NO_TYPE):{
                visibleEvent=tr("Неопределенное");
                break;
            }
            case(EVENT_NO_RESPONCE):{
                visibleEvent=tr("Нет ответа");
                break;
            }
            case(EVENT_NOT_READY):{
                visibleEvent=tr("Нет данных");
                break;
            }
            case(EVENT_CONTROLLER_FAULT):{
                visibleEvent=tr("Ошибка");
                break;
            }
        }

        posY=this->height()-graphArray->minutesArray[posInArray].value*yFactor-40;
    }
}
///////////////////////////////////////////////////////////////////////////
void graphViewWidget::wheelEvent(QWheelEvent *event){
    QPoint angle=event->angleDelta();
    if(angle.y()>0){
        xFactor+=1;
    }
    else{
        xFactor-=1;
    }
    if(xFactor>=resizeXFactor){
        scrollBarPointer->setVisible(true);
    }
    else{
        scrollBarPointer->setVisible(false);
        xFactor=resizeXFactor;
    }

    emit wheelSignal(xFactor);
    updateContent();
}
//////////////////////////////////////////////////////////////////////////////////////////
void graphViewWidget::resizeEvent(QResizeEvent *event){
    graphZero=this->height()-40;
    calcFactors();
}
//////////////////////////////////////////////////////////////////////////////////
void graphViewWidget::calcFactors(){
    float tmp=graphZero/4*3;//три четверти от размера виджета
    if(tmp!=0){//tmp может стать нулем, если все значения =0
        if(tmp>maxValue){
            yFactor=maxValue/tmp;//оставляем сверху четверть от максимального значения
        }
        else{
            yFactor=tmp/maxValue;
        }
    }
    else{
        yFactor=1;
    }

    //рассчитываем xFactor так, чтобы уместить сутки на графике
    resizeXFactor=this->width()/1440;
    if(resizeXFactor==0){
        resizeXFactor=1;
    }
    xFactor=resizeXFactor;
}
////////////////////////////////////////////////////////////////////////////////
void graphViewWidget::sliderMovedSlot(int value){
    xOffset=value;
    update();
}
///////////////////////////////////////////////////////////////////////////////
void graphViewWidget::updateContent(){
    if(!this->hasMouseTracking()){
        int posInArray=QTime::currentTime().msecsSinceStartOfDay()/60000;
        calculateRails(posInArray);
        mousePosX=posInArray*xFactor-xOffset;
        emit mouseMoveSignal(mousePosX,posY);
    }
    update();
}
//////////////////////////////////////////////////////////////////////
void graphViewWidget::setScrollBarPointer(QScrollBar *pointer){
    scrollBarPointer=pointer;
    connect(scrollBarPointer,SIGNAL(sliderMoved(int)),this,SLOT(sliderMovedSlot(int)));
}
/////////////////////////////////////////////////////////////////////////////////////////////////
QString graphViewWidget::getCurrentValue(){
    return visibleValue;
}
////////////////////////////////////////////////////////////////////////
QString graphViewWidget::getCurrentTime(){
    return visibleDateTime;
}
/////////////////////////////////////////////////////////////////////////
QString graphViewWidget::getCurrentEvent(){
    return visibleEvent;
}
///////////////////////////////////////////////////////////////////////////////
