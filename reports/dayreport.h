#ifndef DAYREPORT_H
#define DAYREPORT_H

#include <QDate>
#include <QTime>

struct dayReportStructure{
    QDate date;
    int count;
    float performance;
    QTime stayTime;
    QTime stayWithoutReason;
    QTime noResponceTime;
    int overtimeCount;//продукции сверхурочно(вне рабочих смен)
};

class dayReport
{
public:
    dayReport();
};

#endif // DAYREPORT_H
