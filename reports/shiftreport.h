#ifndef SHIFTREPORT_H
#define SHIFTREPORT_H

#include <QDateTime>
#include <QVector>
#include "reports/reportclass.h"

struct shiftReportStructure{
    int shift;
    QDateTime startTime;
    QDateTime stopTime;
    int count;
    float performance;
    QTime stayTime;
    QTime stayWithoutReason;
    QTime noResponceTime;
};

class shiftReport : public reportClass
{
public:
    shiftReport();
    virtual int count();
    void createReport(QVector<dayGraph*> *dataArray, QVector<shift> *shiftArray, QVector<QString> *filesArray);
    shiftReportStructure getReportItem(int index);

protected:
    QVector<shiftReportStructure> report;


};

#endif // SHIFTREPORT_H
