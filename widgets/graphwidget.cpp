#include "graphwidget.h"
#include "ui_graphwidget.h"

graphWidget::graphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphWidget)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    graphArray=NULL;
    posY=0;
    xFactor=2;
    yFactor=1;
    contextMenu = createContextMenu();
}
/////////////////////////////////////////////////////////////////////////////////////
graphWidget::~graphWidget()
{
    delete contextMenu;
    delete ui;
}
///////////////////////////////////////////////////////////////////////////////////////
void graphWidget::visualiseGraph(dayGraph *array){
    int maxValue=0;
    maxValue=array->minutesArray[0].value;
    for(int n=1;n!=1440;n++){
        if(maxValue<array->minutesArray[n].value){
            maxValue=array->minutesArray[n].value;
        }
    }
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
    xFactor=((float)this->width()-30)/1440;
    graphArray=array;
}
///////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::updateContent(){
    if(!this->hasMouseTracking()){
        int posInArray=QTime::currentTime().msecsSinceStartOfDay()/60000;
        calculateRails(posInArray);
        mousePosX=posInArray*xFactor+30;
    }
    update();
}
/////////////////////////////////////////////////////////////////////////////////
void graphWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    QRect rect;
    rect.setX(0);
    rect.setY(0);
    rect.setWidth(this->width());
    rect.setHeight(this->height());
    painter.drawRect(rect);

    //прямоугольник окна и координатные линии
    painter.setPen(QPen(Qt::black,2,Qt::SolidLine));
    painter.drawRect(0,0,this->width()-1,this->height()-1);
    painter.drawLine(30,0,30,this->height()-30);
    painter.drawLine(30,this->height()-30,this->width(),this->height()-30);

    if(graphArray!=NULL){
        for(int n=0;n!=1440;n++){
            minutePoint tmpPoint=graphArray->minutesArray[n];
            int graphValue=graphZero-tmpPoint.value*yFactor;
            //не готовые точки не отрисовываем
            if(tmpPoint.event!=EVENT_NOT_READY){
                if(n==0){
                    painter.drawPoint(n*xFactor+30,graphValue);
                }
                else{
                    int prevValue=graphZero-graphArray->minutesArray[n-1].value*yFactor;
                    painter.drawLine((n-1)*xFactor+30,prevValue,n*xFactor+30,graphValue);
                }
            }
        }
        //направляющие
        painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
        painter.drawLine(28,posY,this->width(),posY);
        painter.drawLine(mousePosX,0,mousePosX,this->height()-28);

        painter.drawText(10,posY,visibleValue);//по горизонтали
        painter.drawText(mousePosX,this->height()-15,visibleDateTime);//по вертикали
    }
}
///////////////////////////////////////////////////////////////////////////////
void graphWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->x()<30){
        mousePosX=30;
    }
    else{
        mousePosX=event->x();
    }
    mousePosY=event->y();
    if(graphArray!=NULL){
        calculateRails((mousePosX-30)/xFactor);//позиция в массиве зависит от позиции мыши на экране);
    }
    update();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::wheelEvent(QWheelEvent *event){
    QPoint angle=event->angleDelta();
    if(angle.y()>0){
        xFactor+=0.1f;
    }
    else{
        xFactor-=0.1f;
    }
    updateContent();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::contextMenuEvent(QContextMenuEvent *event){
    contextMenu->popup(event->globalPos());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::resizeEvent(QResizeEvent *event){
    graphZero=this->height()-40;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::mousePressEvent(QMouseEvent *event){
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
//////////////////////////////////////////////////////////////////////////////////////////////////////
QMenu *graphWidget::createContextMenu(){
    QMenu *menu = new QMenu;
    QAction *calculateAll = new QAction(tr("Отчет за сутки"));
    menu->addAction(calculateAll);
    return menu;
}
////////////////////////////////////////////////////////////////////////
void graphWidget::calculateRails(int posInArray){
    visibleValue=QString::number(graphArray->minutesArray[posInArray].value);//отображаемое значение
    QTime time=QTime::fromMSecsSinceStartOfDay(posInArray*60000);
    visibleDateTime=graphArray->date.toString("dd_MM_yyyy ")+time.toString("hh:mm");
    posY=this->height()-graphArray->minutesArray[posInArray].value*yFactor-40;
}
//////////////////////////////////////////////////////////////////
void graphWidget::slotCalcAll(){

}


