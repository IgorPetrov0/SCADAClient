#ifndef LINEBUTTON_H
#define LINEBUTTON_H

#include <QPushButton>
#include <QPainter>

class lineButton: public QPushButton
{
public:
    lineButton(QWidget *parent);
    void setColor(QColor color);
    QColor getColor();

protected:
    void paintEvent(QPaintEvent *event);
    QColor color;
};

#endif // LINEBUTTON_H
