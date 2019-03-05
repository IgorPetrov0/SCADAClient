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
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QMenu *createContextMenu();
    void calculateRails(int posInArray);
    int mousePosX,mousePosY;
    dayGraph *graphArray;
    float yFactor;
    float xFactor;
    int graphZero;
    int posY;
    QString visibleValue;
    QString visibleDateTime;
    QMenu *contextMenu;

protected slots:
    void slotCalcAll();





private:
    Ui::graphWidget *ui;
};

#endif // GRAPHWIDGET_H
