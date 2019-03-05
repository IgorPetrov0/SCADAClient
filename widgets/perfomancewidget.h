#ifndef PERFOMANCEWIDGET_H
#define PERFOMANCEWIDGET_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class perfomanceWidget;
}

class perfomanceWidget : public QWidget, public baseWidget
{
    Q_OBJECT

public:
    explicit perfomanceWidget(QWidget *parent = 0);
    ~perfomanceWidget();
    virtual void updateContent();
    void showGraph(dayGraph *array);

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void objectUpSlot();
    void objectDownSlot();
    void objectEditSlot();
    void objectDeleteSlot();
    void selectMashineSlot(int row, int column);

signals:
    void objectAddSignal();
    void objectEditSignal(objectType type, int index);
    void objectDeleteSignal(objectType type, int index);
    void createReportSygnal(reportType type, int index);
    void enotherDaySignal(int index);

private:
    Ui::perfomanceWidget *ui;
};

#endif // PERFOMANCEWIDGET_H
