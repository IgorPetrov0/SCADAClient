#include "shiftreport.h"

shiftReport::shiftReport()
{
    type=REPORT_SHIFT;
}
////////////////////////////////////////////////////
int shiftReport::count(){
    return report.size();
}
///////////////////////////////////////////////////////////////
void shiftReport::createReport(QVector<dayGraph *> *dataArray, QVector<shift> *shiftArray, QVector<QString> *filesArray){
    int dataSize=dataArray->size();
    int shiftsCount = shiftArray->size();
    int dayCount=0;
    QDateTime startDateTime;
    QDateTime stopDateTime;
    minutePoint *currentShiftArray=NULL;
    while(dayCount!=dataSize){
        for(int n=0;n!=shiftsCount;n++){
            shift tmpShift=shiftArray->at(n);
            int shiftInMinutes=abs(tmpShift.startTime.msecsSinceStartOfDay()-tmpShift.stopTime.msecsSinceStartOfDay())/60000;
            currentShiftArray = new minutePoint[shiftInMinutes];
            int startTimeInMinutes=tmpShift.startTime.msecsSinceStartOfDay()/60000;
            //устанавливаем дату и время начала смены
            startDateTime.setDate(dataArray->at(dayCount)->date);
            startDateTime.setTime(tmpShift.startTime);

            for(int m=0;m!=shiftInMinutes;m++){
                int minCounter=startTimeInMinutes+m;
                if(minCounter>1440){
                    dayCount++;
                    minCounter=0;
                    if(dayCount==dataSize){//если смена переносится на день, которого нет в списке
                        delete currentShiftArray;//то эту смену не учитываем
                        currentShiftArray=NULL;
                        break;
                    }
                }
                if(currentShiftArray!=NULL){
                    currentShiftArray[m]=dataArray->at(dayCount)->minutesArray[minCounter];
                }
            }

            //устанавливаем дату и время окончания смены
            stopDateTime.setDate(dataArray->at(dayCount)->date);
            stopDateTime.setTime(tmpShift.stopTime);

            if(currentShiftArray!=NULL){//если массив не прибили в процессе, то
                //делаем анализ
                shiftReportStructure repStruct;
                repStruct.shift=n;
                repStruct.startTime=startDateTime;
                repStruct.stopTime=stopDateTime;
                repStruct.count=0;
                for(int nn=0;nn!=shiftInMinutes;nn++){
                    repStruct.count+=currentShiftArray[nn].value;
                }
                float f=repStruct.count/shiftInMinutes;
                repStruct.performance=f*60;
                //подсчитываем время простоя
                int swrCount=0;
                int nrCount=0;
                int stCount=0;
                for(int nn=0;nn!=shiftInMinutes;nn++){
                    minutePoint mPoint=currentShiftArray[nn];
                    if(mPoint.value==0){
                        stCount++;
                        if(mPoint.event==EVENT_NO_TYPE){
                            swrCount++;
                        }
                        if(mPoint.event==EVENT_NO_RESPONCE){
                            nrCount++;
                        }
                    }
                }
                repStruct.stayTime.fromMSecsSinceStartOfDay(stCount*60000);
                repStruct.stayWithoutReason.fromMSecsSinceStartOfDay(swrCount*60000);
                repStruct.noResponceTime.fromMSecsSinceStartOfDay(nrCount*60000);

                report.append(repStruct);

                delete[] currentShiftArray;
                currentShiftArray=NULL;
            }
        }
        dayCount++;//если в этот день больше нет смен
    }
    int size=filesArray->size();
    for(int n=0;n!=size;n++){
        filesNamesArray.append(filesArray->at(n));
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
shiftReportStructure shiftReport::getReportItem(int index){
    return report.at(index);
}
