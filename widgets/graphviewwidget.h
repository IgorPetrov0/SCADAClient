#ifndef GRAPHVIEWWIDGET_H
#define GRAPHVIEWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include "defines.h"

class graphViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit graphViewWidget(QWidget *parent = nullptr);
    void visualiseGraph(dayGraph *array);
    void updateContent();
    void setScrollBarPointer(QScrollBar *pointer);
    QString getCurrentValue();
    QString getCurrentTime();
    QString getCurrentEvent();

protected:
    dayGraph *graphArray;
    int graphZero;
    int mousePosX,mousePosY;
    int posY;
    float yFactor;
    int xFactor;//меняется при whileEvent и ипользуется дл отрисовки
    int resizeXFactor;//меняется при resizeEvent
    int xOffset;//смещение слайдером по горизонтали
    QString visibleValue;
    QString visibleDateTime;
    QString visibleEvent;
    QScrollBar *scrollBarPointer;
    int maxValue;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void calculateRails(int posInArray);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);
    void calcFactors();

signals:
    void mouseMoveSignal(int x,int y);
    void wheelSignal(int xFactor);


public slots:
    void sliderMovedSlot(int value);

};

#endif // GRAPHVIEWWIDGET_H
