#include "mashinetable.h"

mashineTable::mashineTable(QWidget *parent):
    QTableWidget(parent)
{
    QAction *shiftReport = new QAction(tr("Посменный отчет за период."));
    QAction *dayReport = new QAction(tr("Поcуточный отчет за период."));
    QAction *openEnotherDay = new QAction(tr("Открыть другой день"));
    contextMenu = new QMenu;
    contextMenu->addAction(openEnotherDay);
    contextMenu->addSeparator();
    contextMenu->addAction(shiftReport);
    contextMenu->addAction(dayReport);
    connect(shiftReport,SIGNAL(triggered(bool)),this,SLOT(shiftReportSlot()));
    connect(dayReport,SIGNAL(triggered(bool)),this,SLOT(dayReportSlot()));
    connect(openEnotherDay,SIGNAL(triggered(bool)),this,SLOT(enotherDaySlot()));
}
////////////////////////////////////////////////////////////////////////////////////////
mashineTable::~mashineTable()
{
    delete contextMenu;
}
/////////////////////////////////////////////////////////////////////////////////////////
void mashineTable::contextMenuEvent(QContextMenuEvent *event){
    QTableWidgetItem *item=currentItem();
    if(item!=NULL){
        contextMenu->popup(event->globalPos());
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void mashineTable::shiftReportSlot(){
    emit createReport(REPORT_SHIFT,currentItem()->data(Qt::UserRole).toUInt());
}
/////////////////////////////////////////////////////////////////////////////////////////
void mashineTable::dayReportSlot(){
    emit createReport(REPORT_DAY,currentItem()->data(Qt::UserRole).toUInt());
}
///////////////////////////////////////////////////////////////////////////////////////////
void mashineTable::enotherDaySlot(){
    emit enotherDaySignal(currentItem()->data(Qt::UserRole).toInt());
}
