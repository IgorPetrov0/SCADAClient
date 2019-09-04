#include "mashine.h"

mashine::mashine(){
    type=objectMashine;
    lineColor=QColor(Qt::black);
    currentDayGraph = new dayGraph;
    currentDayGraph->name=name;
    currentDayGraph->date=QDate::currentDate();
    currentDayGraph->minutesArray = new minutePoint[1440];
    notCleared=false;
    clearArray();
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
bool mashine::deserialisation(QDataStream *str){
    if(!object::deserialisation(str)){
        return false;
    }
    return deserialisationContinue(str);
}
///////////////////////////////////////////////////////////////////////
bool mashine::deserialisationContinue(QDataStream *str){
    *str>>lineColor;
    *str>>pathForStatistics;
    if(pathForStatistics>MAX_PATH_LEIGTH){
        return false;
    }
    int size;
    *str>>size;
    if((size<0)||(size>MAX_MASHINES_SHIFTS)){
        return false;
    }
    currentDayGraph->name=name;
    for(int n=0;n!=size;n++){
        shift s;
        *str>>s.startTime;
        *str>>s.stopTime;
        shiftsArray.append(s);
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////
void mashine::netSerialise(QDataStream *str){
    object::serialisation(str);
    *str<<lineColor;
    int size=shiftsArray.size();
    *str<<size;
    for(int n=0;n!=size;n++){
        *str<<shiftsArray.at(n).startTime;
        *str<<shiftsArray.at(n).stopTime;
    }
    serialiseDayGraph(str);
}
////////////////////////////////////////////////////////////////////////////////
bool mashine::netDeserialise(QDataStream *str){
    if(!object::deserialisation(str)){
        return false;
    }
    *str>>lineColor;
    int size;
    *str>>size;
    currentDayGraph->name=name;
    for(int n=0;n!=size;n++){
        shift s;
        *str>>s.startTime;
        *str>>s.stopTime;
        shiftsArray.append(s);
    }
    *str>>currentDayGraph->name;
    *str>>currentDayGraph->date;
    for(int n=0;n!=1440;n++){
        *str>>currentDayGraph->minutesArray[n].value;
        *str>>currentDayGraph->minutesArray[n].event;
    }
    return true;
}
/////////////////////////////////////////////////////////////////////
void mashine::serialiseDayGraph(QDataStream *str){
    *str<<currentDayGraph->name;
    *str<<currentDayGraph->date;
    for(int n=0;n!=1440;n++){
        *str<<currentDayGraph->minutesArray[n].value;
        *str<<currentDayGraph->minutesArray[n].event;
        *str<<currentDayGraph->minutesArray[n].objectState;
    }
}
////////////////////////////////////////////////////////////////////
mashine &mashine::operator=(const object &right){
    if (this == &right) {
        return *this;
    }
    object::operator =(right);
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
    pathForStatistics = value+"/"+name;
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
////////////////////////////////////////////////////////////////////////////
void mashine::setCurrentGraph(dayGraph *newCurrentGraph){
    delete[] currentDayGraph->minutesArray;
    delete currentDayGraph;
    currentDayGraph=newCurrentGraph;
}
/////////////////////////////////////////////////////////////////////////////////
void mashine::readPacket(unsigned char *array, QTime time){
    int lastTimeInMinutes=lastRequestTime.msecsSinceStartOfDay()/60000;
    int currentTimeInMinutes=time.msecsSinceStartOfDay()/60000;
    if(lastTimeInMinutes>currentTimeInMinutes){//если перешли на следующие сутки
        lastTimeInMinutes=0;
        emit newDaySygnal(this);
        clearArray();
    }
    int period=(currentTimeInMinutes-lastTimeInMinutes);//период со времени последнего запроса в минутах
    int packetSize=(int)array[0];//размер пакета в байтах
    int seconds=time.second();
    switch(array[2]){
        case(ANSWER_OK):{
            int packetSizeInMinutes=(int)array[3];//кол-во минут в пакете
            minutePoint tmpPoint;
            if((packetSizeInMinutes*2!=packetSize-5) || notCleared){//если размер в байтах не соответствует размеру
                //в минутах, или контроллер не ответил на запрос стирания памяти то ошибка контроллера
                //и все данные в пакете недостоверны
                //контроллер уже удалил свои данные и повторный запрос бесполезен
                for(int n=0;n!=period;n++){
                    tmpPoint.event=EVENT_CONTROLLER_FAULT;
                    tmpPoint.value=0;
                    tmpPoint.objectState=OBJECT_STATE_OFF;
                    this->setCurrentState(OBJECT_STATE_OFF);
                    currentDayGraph->minutesArray[lastTimeInMinutes]=tmpPoint;
                }
                notCleared=false;
                return;
            }
            int minutesOffset=currentTimeInMinutes-packetSizeInMinutes+1;
            for(int n=0;n!=packetSizeInMinutes;n++){
                int offset=4+n*2;
                int t=array[offset+1]<<8;//старший байт значения
                int value=(int)array[offset]+t;//младший байт значения
                int index=minutesOffset+n;
                if(index<0){//индек может быть <0 в начале суток
                    break;//тогда просто отбрасываем все, что <0
                }
                //делим значение между текущей минутой и предыдущей
                double tmp=(double)value/60*(double)seconds;
                int currentMinuteValue=round(tmp);
                int prevMinuteValue=value-currentMinuteValue;
                tmpPoint.value=currentMinuteValue;
                //tmpPoint.event=array[offset+2];
                if(currentMinuteValue==0){
                    tmpPoint.objectState=OBJECT_STATE_ON;
                    this->setCurrentState(OBJECT_STATE_ON);
                }
                else{
                    tmpPoint.objectState=OBJECT_STATE_WORK;
                    this->setCurrentState(OBJECT_STATE_WORK);
                }
                currentDayGraph->minutesArray[index]=tmpPoint;
                int prevIndex=index-1;
                if(prevIndex<0){
                    break;
                }
                currentDayGraph->minutesArray[prevIndex].value=currentDayGraph->minutesArray[prevIndex].value+prevMinuteValue;
            }
            break;
        }
        case(ANSWER_CLEARED):{
            lastRequestTime=time;
            break;
        }
        default:{
            int t=0;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////
void mashine::memoryNotCleared(){
    notCleared=true;
}
////////////////////////////////////////////////////////////////////////
void mashine::clearArray(){
    for(int n=0;n!=1440;n++){
        minutePoint point;
        point.event=EVENT_NOT_READY;
        point.value=0;
        point.objectState=OBJECT_STATE_OFF;
        currentDayGraph->minutesArray[n]=point;
    }
}
//////////////////////////////////////////////////////////////////////////////////



