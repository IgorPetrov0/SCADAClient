#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include "basewidget.h"

namespace Ui {
class graphWidget;
}


class graphWidget : public QWidget, baseWidget
{
    Q_OBJECT

public:
    explicit graphWidget(QWidget *parent = 0);
    ~graphWidget();
    void visualiseGraph(dayGraph *array);
    virtual void updateContent();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void resizeEvent(QResizeEvent *event);
    QMenu *createContextMenu();
    QMenu *contextMenu;
    int viewWidgetBottom;
    int bottomPos;
    int viewWidgetLeft;
    int leftPos;

protected slots:
    void slotCalcAll();
    void mouseMoveSlot(int x, int y);
    void wheelSlot(int xFactor);


private:
    Ui::graphWidget *ui;
};



#endif // GRAPHWIDGET_H
