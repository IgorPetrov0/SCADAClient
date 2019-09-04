#include "object.h"

object::object(QObject *parent) : QObject(parent)
{
    name.clear();
    address=0;
    description.clear();
    type=objectUnknow;
    requestEnable=true;
    online=false;
    currentState=OBJECT_STATE_OFF;
}
//////////////////////////////////////////////////////////
object::~object(){
    int size=ports.size();
    for(int n=0;n!=size;n++){
        delete ports.at(n);
    }
}
//////////////////////////////////////////////////////////
int object::getAddress() const{
    return address;
}
//////////////////////////////////////////////////////////
void object::setAddress(unsigned int value){
    address = value;
}
////////////////////////////////////////////////////////////
QString object::getName() const{
    return name;
}
//////////////////////////////////////////////////////////////
void object::setName(const QString &value){
    name = value;
}
///////////////////////////////////////////////////////////////////////
QString object::getDescription() const{
    return description;
}
////////////////////////////////////////////////////////////////////////
void object::setDescription(const QString &value){
    description = value;
}
///////////////////////////////////////////////////////////
void object::serialisation(QDataStream *str){
    *str<<name;
    *str<<(int)type;
    *str<<address;
    *str<<description;
    *str<<requestEnable;
    int size=ports.size();
    *str<<size;
    for(int n=0;n!=size;n++){
        ports.at(n)->serialisation(str);
    }
}
///////////////////////////////////////////////////////////////////
bool object::deserialisation(QDataStream *str){
    *str>>name;
    if(name.isEmpty()||(name.size()>MAX_OBJECT_NAME_SIZE)){
        return false;
    }
    int tmp=0;
    *str>>tmp;
    if((tmp<objectMashine)||(tmp>objectUnknow)){
        return false;
    }
    type=(objectType)tmp;
    *str>>address;
    if(address>MAX_RS_ADDRESES){
        return false;
    }
    *str>>description;
    if(description.size()>MAX_OBJECT_DESCRIPTION_SYMBOLS){
        return false;
    }
    *str>>requestEnable;
    int size=0;
    *str>>size;
    if((size<0)||(size>MAX_OBJECT_PORTS)){
        return false;
    }
    for(int n=0;n!=size;n++){
        objectPort *tmpPort = new objectPort();
        if(!tmpPort->deserialisation(str)){
            return false;
        }
        ports.append(tmpPort);
    }
    return true;
}
////////////////////////////////////////////////////////////////////////
bool object::deserialisationContinue(QDataStream *str){
    *str>>name;
    if(name.isEmpty()||(name.size()>MAX_OBJECT_NAME_SIZE)){
        return false;
    }
    int tmp=0;
    *str>>tmp;
    if((tmp<objectMashine)||(tmp>objectUnknow)){
        return false;
    }
    type=(objectType)tmp;
    *str>>address;
    if(address>MAX_RS_ADDRESES){
        return false;
    }
    *str>>description;
    if(description.size()>MAX_OBJECT_DESCRIPTION_SYMBOLS){
        return false;
    }
    int size=0;
    *str>>size;
    if((size<0)||(size>MAX_OBJECT_PORTS)){
        return false;
    }
    for(int n=0;n!=size;n++){
        objectPort *tmpPort = new objectPort();
        if(!tmpPort->deserialisation(str)){
            return false;
        }
        ports.append(tmpPort);
    }
    return true;
}
////////////////////////////////////////////////////////////////
objectState object::getCurrentState() const{
    return currentState;
}
//////////////////////////////////////////////////////////////////////////
void object::setCurrentState(const objectState &value){
    stateSetTime=QTime::currentTime();
    currentState = value;
}
///////////////////////////////////////////////////////////////////////
QString object::getCurrentStateString(){
    switch(currentState){
        case(OBJECT_STATE_OFF):{
            return tr("Выключен");
        }
        case(OBJECT_STATE_ON):{
            return tr("Включен");
        }
        case(OBJECT_STATE_WORK):{
            return tr("Работает");
        }
    }
}
//////////////////////////////////////////////////////////////////////////
QTime object::getStateSetTime() const{
    return stateSetTime;
}
//////////////////////////////////////////////////////////////////////////
int object::getPortIndex(int portNumber){
    int count=ports.size();
    for(int n=0;n!=count;n++){
        if(portNumber==ports.at(n)->getNumber()){
            return n;
        }
    }
    return -1;
}
///////////////////////////////////////////////////////////////////////////
objectType object::getType() const{
    return type;
}
//////////////////////////////////////////////////////////////////////////
void object::setType(const objectType &value){
    type = value;
}
////////////////////////////////////////////////////////////////////////////
QString object::getTypeString(){
    switch(type){
        case(objectMashine):{
            return tr("Машина");
        }
        default:{
            return QString();
        }
    }
}
//////////////////////////////////////////////////////////////////
bool object::isOnline(){
    return online;
}
///////////////////////////////////////////////////////////////////
void object::setOnline(bool value){
    online=value;
}
////////////////////////////////////////////////////////////////////
bool object::isRequestEnable(){
    return requestEnable;
}
///////////////////////////////////////////////////////////////////
void object::setRequestEnable(bool enable){
    requestEnable=enable;
}
///////////////////////////////////////////////////////////////////
int object::getPortsCount() const{
    return ports.size();
}
//////////////////////////////////////////////////////////////////////
bool object::isPortExist(int number, objectPort *port){
    int size=ports.size();
    for(int n=0;n!=size;n++){
        objectPort *tmpPort=ports.at(n);
        if(tmpPort!=port){
            if(tmpPort->getNumber()==number){
                return true;
            }
        }
    }
    return false;
}
//////////////////////////////////////////////////////////////////
objectPort *object::getPort(int index) const{
    if((index>=0)&&(index<ports.size())){
        return ports.at(index);
    }
    return nullptr;
}
///////////////////////////////////////////////////////////////////
objectPort *object::getPortByNumber(int number) const{
    int count=ports.size();
    for(int n=0;n!=count;n++){
        objectPort *tmpPort=ports.at(n);
        if(tmpPort->getNumber()==number){
            return tmpPort;
        }
    }
    return nullptr;
}
/////////////////////////////////////////////////////////////////
void object::addPort(objectPort *port){
    if(port!=nullptr){
        ports.append(port);
    }
    else{
        qDebug("object::addPort port is NULL");
    }
}
/////////////////////////////////////////////////////////////////////
void object::removePort(int index){
    if((index>=0)||(index<ports.size())){
        delete ports.at(index);
        ports.remove(index);
    }
}
///////////////////////////////////////////////////////////
object& object::operator=(const object& right){
    if (this == &right) {
        return *this;
    }
    address=right.getAddress();
    name=right.getName();
    description=right.getDescription();
    type=right.getType();
    int size=right.getPortsCount();
    for(int n=0;n!=size;n++){
        objectPort *tmpPort = new objectPort;
        *tmpPort=*right.getPort(n);
        ports.append(tmpPort);
    }
    return *this;
}
