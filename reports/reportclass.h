#ifndef REPORTCLASS_H
#define REPORTCLASS_H

#include "defines.h"
#include <QSTring>
#include <QVector>




class reportClass
{
public:
    reportClass();

    reportType getType() const;
    virtual int count();
    int fileNamesCount();
    QString getFileName(int index);

protected:
    reportType type;
    QVector<QString>filesNamesArray;


};

#endif // REPORTCLASS_H
