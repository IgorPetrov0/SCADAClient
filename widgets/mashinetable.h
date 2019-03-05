#ifndef MASHINETABLE_H
#define MASHINETABLE_H

#include <QTableWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include "defines.h"



class mashineTable : public QTableWidget
{
    Q_OBJECT
public:
    mashineTable(QWidget *parent);
    ~mashineTable();

protected:
    QMenu *contextMenu;
    void contextMenuEvent(QContextMenuEvent *event);

protected slots:
    void shiftReportSlot();
    void dayReportSlot();
    void enotherDaySlot();

signals:
    void createReport(reportType type, int mashineIndex);
    void enotherDaySignal(int mashineIndex);



};

#endif // MASHINETABLE_H
