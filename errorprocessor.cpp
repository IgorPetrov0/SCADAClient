#include "errorprocessor.h"

errorProcessor::errorProcessor()
{

}
////////////////////////////////////////////////////////////////////
QString errorProcessor::getLastError(){
    QString tmp=lastError;
    lastError.clear();
    return tmp;
}
////////////////////////////////////////////////////////////////////
void errorProcessor::setLastError(QString errorText){
    lastError+="\n"+errorText;//ошибки могут копиться через перенос строки
}
