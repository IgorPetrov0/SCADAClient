#ifndef BASEGRAPHWIDGET_H
#define BASEGRAPHWIDGET_H

#include <QWidget>
#include "widgets/basewidget.h"
#include "widgets/graphwidget.h"

namespace Ui {
class baseGraphWidget;
}

class baseGraphWidget : public QWidget, baseWidget
{
    Q_OBJECT

public:
    explicit baseGraphWidget(QWidget *parent = 0);
    ~baseGraphWidget();
    void visualiseGraphFirstTab(dayGraph *array);
    void visualizeGraphNewTab(dayGraph *array);
    virtual void updateContent();

protected:
    void resizeEvent(QResizeEvent *event);
    QVector<graphWidget*>graphWidgetsArray;

protected slots:
    void tabCloseSlot(int index);

private:
    Ui::baseGraphWidget *ui;
};

#endif // BASEGRAPHWIDGET_H
