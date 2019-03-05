#include "maintabwidget.h"
#include "ui_maintabwidget.h"

mainTabWidget::mainTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::mainTabWidget)
{
    ui->setupUi(this);
    connect(ui->perfWidget,SIGNAL(objectAddSignal()),this,SIGNAL(addObjectSignal()));
    connect(ui->perfWidget,SIGNAL(objectEditSignal(objectType,int)),this,SIGNAL(editObjectSignal(objectType,int)));
    connect(ui->perfWidget,SIGNAL(objectDeleteSignal(objectType,int)),this,SIGNAL(deleteObjectSignal(objectType,int)));
    connect(ui->perfWidget,SIGNAL(createReportSygnal(reportType,int)),this,SIGNAL(createReportSygnal(reportType,int)));
    connect(ui->perfWidget,SIGNAL(enotherDaySignal(int)),this,SIGNAL(enotherDaySignal(int)));
}
/////////////////////////////////////////////////////////////
mainTabWidget::~mainTabWidget()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////////////
void mainTabWidget::updateContent(){
    ui->perfWidget->updateContent();
}
//////////////////////////////////////////////////////////////////////////
void mainTabWidget::showGraph(dayGraph *array){
    ui->perfWidget->showGraph(array);
}
//////////////////////////////////////////////////////////////////
void mainTabWidget::setNetCorePointer(tcpClient *pointer){
    baseWidget::setNetCorePointer(pointer);
    ui->perfWidget->setNetCorePointer(pointer);
}
/////////////////////////////////////////////////////////////
void mainTabWidget::resizeEvent(QResizeEvent *event){
    QRect rect=this->geometry();
    rect.setX(0);
    rect.setY(0);
    rect.setHeight(this->geometry().height());
    ui->tabWidget->setGeometry(rect);
    ui->perfWidget->setGeometry(ui->tabWidget->currentWidget()->geometry());
}
