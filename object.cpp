#include "object.h"

object::object(QObject *parent) : QObject(parent)
{
    name.clear();
    address=0;
    description.clear();
    type=objectUnknow;
    requestEnable=false;
    online=false;
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
}
///////////////////////////////////////////////////////////////////
void object::deserialisation(QDataStream *str){
    *str>>name;
    int tmp;
    *str>>tmp;
    type=(objectType)tmp;
    *str>>address;
    *str>>description;
    *str>>requestEnable;
}
////////////////////////////////////////////////////////////////////////
void object::deserialisationContinue(QDataStream *str){
    *str>>name;
    int tmp;
    *str>>tmp;
    type=(objectType)tmp;
    *str>>address;
    *str>>description;
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
///////////////////////////////////////////////////////////
object& object::operator=(const object& right){
    if (this == &right) {
        return *this;
    }
    address=right.getAddress();
    name=right.getName();
    description=right.getDescription();
    type=right.getType();
    return *this;
}
