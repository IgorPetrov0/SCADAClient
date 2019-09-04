#ifndef MASHINE_H
#define MASHINE_H

#include <QDataStream>
#include <QColor>
#include <QDateTime>
#include <QVector>
#include <cmath>
#include "object.h"


class mashine : public object
{
    Q_OBJECT

public:
    mashine();
    ~mashine();
    virtual void serialisation(QDataStream *str);
    virtual bool deserialisation(QDataStream *str);
    virtual bool deserialisationContinue(QDataStream *str);
    void netSerialise(QDataStream *str);//сериализация для передачи по сети
    bool netDeserialise(QDataStream *str);//десериализация для передачи по сети
    void serialiseDayGraph(QDataStream *str);
    mashine& operator=(const object& right);
    QColor getLineColor() const;
    int getShiftsCount();
    shift getShift(int number);
    void setLineColor(const QColor &value);
    QString getPathForStatistics() const;
    void setPathForStatistics(const QString &value);
    void addShift(shift newShift);
    void addTimePoint(minutePoint point, QTime time);
    dayGraph *getCurrentGraph();
    void setCurrentGraph(dayGraph *newCurrentGraph);
    void readPacket(unsigned char *array,QTime time);
    void memoryNotCleared();//вызывается, если небыло ответа на запрос стирания памяти

protected:
    QColor lineColor;
    QVector<shift> shiftsArray;
    QString pathForStatistics;
    dayGraph *currentDayGraph;
    QTime lastRequestTime;
    bool notCleared;
    void clearArray();

signals:
    void newDaySygnal(mashine *pointer);//сигнал срабатывает при заполнении последней минуты суток

};

#endif // MASHINE_H
