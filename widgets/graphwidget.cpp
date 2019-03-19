#include "graphwidget.h"
#include "ui_graphwidget.h"

graphWidget::graphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphWidget)
{
    ui->setupUi(this);
    contextMenu = createContextMenu();
    ui->viewWidget->setScrollBarPointer(ui->horizontalScrollBar);
    viewWidgetBottom=0;
    bottomPos=0;
    viewWidgetLeft=0;
    leftPos=0;

    connect(ui->viewWidget,SIGNAL(mouseMoveSignal(int,int)),this,SLOT(mouseMoveSlot(int,int)));
    connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),ui->viewWidget,SLOT(sliderMovedSlot(int)));
}
/////////////////////////////////////////////////////////////////////////////////////
graphWidget::~graphWidget()
{
    delete contextMenu;
    delete ui;
}
///////////////////////////////////////////////////////////////////////////////////////
void graphWidget::visualiseGraph(dayGraph *array){
    ui->viewWidget->visualiseGraph(array);
}
///////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::updateContent(){
    ui->viewWidget->updateContent();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::contextMenuEvent(QContextMenuEvent *event){
    contextMenu->popup(event->globalPos());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void graphWidget::resizeEvent(QResizeEvent *event){
    int valueLabelWidth=50;
    int timeLabelWidth=100;
    QRect rect;
    rect.setX(0);
    rect.setY(this->height()-20);
    rect.setWidth(this->width());
    rect.setHeight(20);
    ui->horizontalScrollBar->setGeometry(rect);
    //видовой виджет
    rect.setX(valueLabelWidth+5);
    rect.setY(0);
    rect.setWidth(this->width()-(valueLabelWidth+5));
    rect.setHeight(this->height()-ui->horizontalScrollBar->height()-40);
    ui->viewWidget->setGeometry(rect);
    //поле значения
    rect.setX(0);
    rect.setY(0);
    rect.setWidth(valueLabelWidth);
    rect.setHeight(16);
    ui->valueLabel->setGeometry(rect);
    //поле времени
    rect.setX(0);
    rect.setY(ui->viewWidget->height());
    rect.setWidth(timeLabelWidth);
    rect.setHeight(16);
    ui->timeLabel->setGeometry(rect);
    //поле события
    rect.setX(0);
    rect.setY(ui->viewWidget->height()+ui->timeLabel->height());
    rect.setWidth(timeLabelWidth);
    rect.setHeight(16);
    ui->eventLabel->setGeometry(rect);


    viewWidgetBottom=ui->viewWidget->geometry().y()+ui->viewWidget->geometry().height();
    bottomPos=viewWidgetBottom-rect.height();
    viewWidgetLeft=ui->viewWidget->width()-ui->viewWidget->geometry().y();
    leftPos=viewWidgetLeft-ui->timeLabel->width();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
QMenu *graphWidget::createContextMenu(){
    QMenu *menu = new QMenu;
    QAction *calculateAll = new QAction(tr("Отчет за сутки"));
    menu->addAction(calculateAll);
    return menu;
}
//////////////////////////////////////////////////////////////////
void graphWidget::slotCalcAll(){

}
///////////////////////////////////////////////////////////////
void graphWidget::mouseMoveSlot(int x, int y){
    x=x+ui->viewWidget->x();
    QRect rect=ui->valueLabel->geometry();

    if(y>bottomPos){
        rect.setY(bottomPos);
    }
    else{
        rect.setY(y);
    }
    rect.setHeight(ui->valueLabel->height());
    ui->valueLabel->setGeometry(rect);

    rect=ui->timeLabel->geometry();
    if(x>leftPos){
        rect.setX(leftPos);
    }
    else{
        rect.setX(x);
    }
    rect.setWidth(ui->timeLabel->width());
    ui->timeLabel->setGeometry(rect);

    rect=ui->eventLabel->geometry();
    if(x>leftPos){
        rect.setX(leftPos);
    }
    else{
        rect.setX(x);
    }
    rect.setWidth(ui->eventLabel->width());
    ui->eventLabel->setGeometry(rect);

    ui->valueLabel->setText(ui->viewWidget->getCurrentValue());
    ui->timeLabel->setText(ui->viewWidget->getCurrentTime());
    ui->eventLabel->setText(ui->viewWidget->getCurrentEvent());
}


