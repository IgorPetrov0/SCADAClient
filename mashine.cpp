#include "mashine.h"

mashine::mashine(){
    type=objectMashine;
    lineColor=QColor(Qt::black);
    currentDayGraph = new dayGraph;
    currentDayGraph->name=name;
    currentDayGraph->date=QDate::currentDate();
    currentDayGraph->minutesArray = new minutePoint[1440];
    for(int n=0;n!=1440;n++){
        minutePoint point;
        point.event=EVENT_NOT_READY;
        point.value=0;
        currentDayGraph->minutesArray[n]=point;
    }
}
////////////////////////////////////////////////////////////////////
mashine::~mashine(){
    delete[] currentDayGraph->minutesArray;
    delete currentDayGraph;
}
/////////////////////////////////////////////////////////////////////////
void mashine::serialisation(QDataStream *str){
    object::serialisation(str);
    *str<<lineColor;
    *str<<pathForStatistics;
    int size=shiftsArray.size();
    *str<<size;
    for(int n=0;n!=size;n++){
        *str<<shiftsArray.at(n).startTime;
        *str<<shiftsArray.at(n).stopTime;
    }

}
////////////////////////////////////////////////////////////////////
void mashine::deserialisation(QDataStream *str){
    object::deserialisation(str);
    deserialisationContinue(str);
}
///////////////////////////////////////////////////////////////////////
void mashine::deserialisationContinue(QDataStream *str){
    *str>>lineColor;
    *str>>pathForStatistics;
    int size;
    *str>>size;
    currentDayGraph->name=name;
    for(int n=0;n!=size;n++){
        shift s;
        *str>>s.startTime;
        *str>>s.stopTime;
        shiftsArray.append(s);
    }
}
////////////////////////////////////////////////////////////////////
mashine &mashine::operator=(const object &right){
    if (this == &right) {
        return *this;
    }
    address=right.getAddress();
    name=right.getName();
    description=right.getDescription();
    type=right.getType();
    return *this;
}
////////////////////////////////////////////////////////////
QColor mashine::getLineColor() const{
    return lineColor;
}
///////////////////////////////////////////////////////////////////////
int mashine::getShiftsCount(){
    return shiftsArray.size();
}
///////////////////////////////////////////////////////////////////////////
shift mashine::getShift(int number){
    if((number>=0) & (number<shiftsArray.size())){
        return shiftsArray.at(number);
    }
    else{
        qDebug("mashine::getShift : Number is out of range");
        shift s;
        s.startTime=QTime(0,0);
        s.stopTime=QTime(0,0);
        return s;
    }
}
///////////////////////////////////////////////////////////////////////
void mashine::setLineColor(const QColor &value){
    lineColor = value;
}
//////////////////////////////////////////////////////////////////////////
QString mashine::getPathForStatistics() const{
    return pathForStatistics;
}
//////////////////////////////////////////////////////////////////////////
void mashine::setPathForStatistics(const QString &value){
    pathForStatistics = value;
}
//////////////////////////////////////////////////////////////////////////
void mashine::addShift(shift newShift){
    shiftsArray.append(newShift);
}
///////////////////////////////////////////////////////////////////////////
void mashine::addTimePoint(minutePoint point, QTime time){
    int pos=time.msecsSinceStartOfDay()/60000;
    currentDayGraph->minutesArray[pos]=point;
    //проверяем предыдущие точки
    //все NOT_READY делаем NOT_RESPONCE
    while(pos>0){
        pos--;
        minutePoint *tmpPoint=&currentDayGraph->minutesArray[pos];
        if(tmpPoint->event==EVENT_NOT_READY){
            tmpPoint->event=EVENT_NO_RESPONCE;
        }
        else{//предполагается, что ранее уже все точки изменены
            break;// и при первой же готовой точке останавливаемся
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////
dayGraph *mashine::getCurrentGraph(){
    return currentDayGraph;
}
/////////////////////////////////////////////////////////////////////////////////
void mashine::readPacket(unsigned char *array, QTime time){
    int lastTimeInMinutes=lastRequestTime.msecsSinceStartOfDay()/60000;
    int currentTimeInMinutes=time.msecsSinceStartOfDay()/60000;
    int period=(currentTimeInMinutes-lastTimeInMinutes);//период со времени последнего запроса в минутах
    int packetSize=array[0]+(array[1]<<8);//размер пакета в байтах
    int packetSizeInMinutes=packetSize/4;

    minutePoint tmpPoint;

    if(packetSizeInMinutes*4!=packetSize-2){//если размер в байтах не соответствует размеру в минутах, то ошибка контроллера
        //и все данные в пакете недостоверны
        //отправляя пакет контроллер уже удалил свои данные и повторный запрос бесполезен
        for(int n=0;n!=period;n++){
            tmpPoint.event=EVENT_CONTROLLER_FAULT;
            tmpPoint.value=0;
            currentDayGraph->minutesArray[lastTimeInMinutes]=tmpPoint;
        }
        return;
    }
    for(int n=1;n!=period;n++){
        tmpPoint.value=array[packetSize-n-2]+(array[packetSize-n-1]<<8);
        tmpPoint.event=array[packetSize-n];
        currentDayGraph->minutesArray[currentTimeInMinutes-n]=tmpPoint;
    }
    lastRequestTime=time;
}
//////////////////////////////////////////////////////////////////////////////////



