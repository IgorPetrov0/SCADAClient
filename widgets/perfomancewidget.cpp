#include "perfomancewidget.h"
#include "ui_perfomancewidget.h"

perfomanceWidget::perfomanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::perfomanceWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,300-20);
    ui->tableWidget->setColumnWidth(1,20);
    ui->tableWidget->setRowHeight(0,20);
    connect(ui->upButton,SIGNAL(clicked(bool)),this,SLOT(objectUpSlot()));
    connect(ui->downButton,SIGNAL(clicked(bool)),this,SLOT(objectDownSlot()));
    connect(ui->addButton,SIGNAL(clicked(bool)),this,SIGNAL(objectAddSignal()));
    connect(ui->editButton,SIGNAL(clicked(bool)),this,SLOT(objectEditSlot()));
    connect(ui->deleteButton,SIGNAL(clicked(bool)),this,SLOT(objectDeleteSlot()));
    connect(ui->tableWidget,SIGNAL(createReport(reportType,int)),this,SIGNAL(createReportSygnal(reportType,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(selectMashineSlot(int,int)));
    connect(ui->tableWidget,SIGNAL(enotherDaySignal(int)),this,SIGNAL(enotherDaySignal(int)));
}
//////////////////////////////////////////////////////////////////////
perfomanceWidget::~perfomanceWidget()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////////////
void perfomanceWidget::updateContent(){
    if(netCorePointer==NULL){
        qDebug("perfomanceWidget::updateContent() : netCorePointer is NULL");
        return;
    }
    int size=netCorePointer->getMashinsCount();
    int currentRow=ui->tableWidget->currentRow();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(size);
    for(int n=0;n!=size;n++){
        mashine *mashinePointer=netCorePointer->getMashine(n);
        QTableWidgetItem *item = new QTableWidgetItem(mashinePointer->getName());
        if(mashinePointer->isOnline()){
            item->setBackground(QBrush(QColor(32,234,43,100)));
        }
        else{
            item->setBackground(QBrush(QColor(28,54,239,100)));
        }
        item->setData(Qt::UserRole,n);//в ячейке хранится индекс объекта в массиве
        item->setToolTip(mashinePointer->getDescription());
        ui->tableWidget->setItem(n,0,item);
        ui->tableWidget->setRowHeight(n,20);
    }
    if(currentRow!=-1){
        if(currentRow<size){
            ui->tableWidget->selectRow(currentRow);
            selectMashineSlot(currentRow,0);
        }
        else{
            ui->tableWidget->selectRow(0);
            selectMashineSlot(0,0);
        }
    }
    else{
        ui->tableWidget->selectRow(0);
        selectMashineSlot(0,0);
    }
    ui->graphicWidget->updateContent();
}
///////////////////////////////////////////////////////////////////////////////////////
void perfomanceWidget::showGraph(dayGraph *array){
    ui->graphicWidget->visualizeGraphNewTab(array);
}
////////////////////////////////////////////////////////////////////////
void perfomanceWidget::resizeEvent(QResizeEvent *event){
    QRect widgetGeometry=this->geometry();
    int tabHeigth=widgetGeometry.height()-65;
    int tabWidth=300;
    QRect rect;
    rect.setX(5);
    rect.setY(5);
    rect.setWidth(tabWidth);
    rect.setHeight(tabHeigth);//-35(незнаю откуда) и -кнопка снизу (высота 20 + по 5 сверху и снизу
    ui->tableWidget->setGeometry(rect);
    int x1=ui->tableWidget->geometry().x()+ui->tableWidget->geometry().width()+40;//ширина кнопки 30 + по 5 с каждой стороны
    rect.setX(x1);
    rect.setY(5);
    rect.setWidth(this->width()-x1);
    rect.setHeight(widgetGeometry.height()-45);//график по высоте больше таблицы на высоту кнопок
    ui->graphicWidget->setGeometry(rect);

    //кнопки справа от таблицы
    //кнопка вверх
    rect.setX(x1-5-30);//х-координата графика - кнопка и расстояние слева и справа от кнопки
    rect.setY(tabHeigth/3);//треть высоты таблицы
    rect.setHeight(20);
    rect.setWidth(30);
    ui->upButton->setGeometry(rect);
    //кнопка вниз
    rect.setY((tabHeigth/3)*2);//две трети высоты таблицы
    rect.setHeight(20);
    ui->downButton->setGeometry(rect);

    //кнопки снизу таблицы
    //кнопка добавить
    rect.setX(ui->tableWidget->geometry().x());
    rect.setY(tabHeigth+10);
    rect.setHeight(20);
    rect.setWidth(30);
    ui->addButton->setGeometry(rect);
    //кнопка редактировать
    rect.setX((ui->tableWidget->geometry().x()+tabWidth/2)-15);
    rect.setY(tabHeigth+10);
    rect.setHeight(20);
    rect.setWidth(30);
    ui->editButton->setGeometry(rect);
    //кнопка удалить
    rect.setX(ui->tableWidget->geometry().x()+(tabWidth-30));
    rect.setY(tabHeigth+10);
    rect.setHeight(20);
    rect.setWidth(30);
    ui->deleteButton->setGeometry(rect);

    rect=ui->tableWidget->verticalHeader()->geometry();
    int w=ui->tableWidget->verticalHeader()->geometry().width();
    ui->tableWidget->setColumnWidth(0,300-40-w);
    ui->tableWidget->setColumnWidth(1,20);
    ui->tableWidget->setRowHeight(0,20);
}
//////////////////////////////////////////////////////////////////
void perfomanceWidget::objectUpSlot(){
    if(ui->tableWidget->currentColumn()==0){//если выбрана ячейка с именем машины
        QTableWidgetItem *curItem=ui->tableWidget->currentItem();
        if(curItem!=NULL){
            if(netCorePointer->mashineUp(curItem->data(Qt::UserRole).toInt())){
                updateContent();
            }
        }
    }
}
//////////////////////////////////////////////////////////////////
void perfomanceWidget::objectDownSlot(){
    if(ui->tableWidget->currentColumn()==0){//если выбрана ячейка с именем машины
        QTableWidgetItem *curItem=ui->tableWidget->currentItem();
        if(curItem!=NULL){
            if(netCorePointer->mashineDown(curItem->data(Qt::UserRole).toInt())){
                updateContent();
            }
        }
    }
}
//////////////////////////////////////////////////////////////////
void perfomanceWidget::objectEditSlot(){
    if(ui->tableWidget->currentColumn()==0){//если выбрана ячейка с именем машины
        QTableWidgetItem *curItem=ui->tableWidget->currentItem();
        if(curItem!=NULL){
            emit objectEditSignal(objectMashine, curItem->data(Qt::UserRole).toInt());
        }
    }
}
//////////////////////////////////////////////////////////////////
void perfomanceWidget::objectDeleteSlot(){
    if(ui->tableWidget->currentColumn()==0){//если выбрана ячейка с именем машины
        QTableWidgetItem *curItem=ui->tableWidget->currentItem();
        if(curItem!=NULL){
            emit objectDeleteSignal(objectMashine, curItem->data(Qt::UserRole).toInt());
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
void perfomanceWidget::selectMashineSlot(int row, int column){
    mashine *tmpMashine=netCorePointer->getMashine(row);
    if(tmpMashine!=NULL){
        dayGraph *graph=tmpMashine->getCurrentGraph();
        if(graph!=NULL){
            ui->graphicWidget->visualiseGraphFirstTab(graph);
        }
    }
}
