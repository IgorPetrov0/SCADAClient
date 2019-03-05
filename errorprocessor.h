#ifndef ERRORPROCESSOR_H
#define ERRORPROCESSOR_H

#include <QString>

class errorProcessor
{

public:
    explicit errorProcessor();
    QString getLastError();

protected:
    void setLastError(QString errorText);

private:
    QString lastError;


};

#endif // ERRORPROCESSOR_H
