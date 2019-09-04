#ifndef DEFINES_H
#define DEFINES_H

#include <QTime>

#define STAT_PATH "/statistics"
#define CONFIG_FILE_NAME "config.cfg"
#define SP_CONFIG_FILE_NAME "spConfig.cfg"
#define NET_CONFIG_FILE_NAME "netConfig.cfg"
#define SIGNATURE "phConfig"
#define SPSIGNATURE "spConfig"
#define CUR_VERSION 0.0f
#define MAX_TCP_CONNECTIONS 3
#define DATA_STREAM_VERSION QDataStream::Qt_4_0
#define ON true
#define OFF false
#define MAX_OBJECT_PORTS 20 //максимальное количество портов у обного объекта
#define MAX_RS_ADDRESES 255 //максимальное количество адресов в сети RS485
#define MAX_OBJECT_DESCRIPTION_SYMBOLS 100 //максимальное количество символов в описании объекта
#define MAX_PATH_LEIGTH 32767 //максимальная длина пути
#define MAX_MASHINES_SHIFTS 5 //максимальное количество смен для машины
#define MAX_CONDITIONS 10 //максимальное количество состояний для порта
#define MAX_OBJECT_NAME_SIZE 255 //максимальный размер имен объектов



//запросы
enum requestType{
    REQUEST_EMPTY=0,
    REQUEST_GET_DATA,
    REQUEST_CLEAR,
    REQUEST_CONFIG_PORTS
};
//ответы
enum answerType{
    ANSWER_OK=0,
    ANSWER_ERROR,
    ANSWER_NO_DATA,
    ANSWER_CLEARED,
    ANSWER_PORTS_STATE
};

enum portTypes:int{//todo все следующие перечисления писать между PORT_INPUT и PORT_OUTPUT
    PORT_INPUT,
    PORT_OUTPUT
};

//enum portState:int{
//    PORT_ON,
//    PORT_OFF
//};

enum objectType:int{
    objectMashine,//todo все следующие перечисления писать между  objectMashine и objectUnknow
    objectUnknow
};

struct minutePoint{
    int value;
    int event;//событие, определяемое контроллером
    int objectState;//состояние объекта в момент запроса для отображения на графике
};

struct dayGraph{
    QString name;
    QDate date;
    minutePoint *minutesArray;
};

struct shift{
    QTime startTime;
    QTime stopTime;
};

enum serverCommand{
    SERVERCOMMAND_NO_COMMAND=0,
    SERVERCOMMAND_GET_STATISTIC,
    SERVERCOMMAND_EDIT_OBJECT,
    SERVERCOMMAND_CREATE_OBJECT,
    SERVERCOMMAND_DELETE_OBJECT
};

enum tcpPacketType{
    TCP_PACKET_COMMAND=0,
    TCP_PACKET_STATISTIC,
    TCP_PACKET_ANSWER,
    TCP_PACKET_ERROR
};

enum reportType{
    REPORT_DAY,
    REPORT_SHIFT,
    REPORT_ALL_MASHINES
};

enum eventType{
    EVENT_CONTROLLER_FAULT=0,
    EVENT_NO_TYPE,
    EVENT_NOT_READY,
    EVENT_NO_RESPONCE,
    EVENT_OK
};




enum logicType:int{
    LOGIC_OR,
    LOGIC_AND,
    LOGIC_NO
};

enum objectState:int{//todo все следующие перечисления писать между  OBJECT_STATE_ON и OBJECT_STATE_ANY
    OBJECT_STATE_ON,    //включен - когда отвечает, но не производит продукцию
    OBJECT_STATE_OFF,   //выключен - когда не отвечает
    OBJECT_STATE_WORK,   //работает - когда производит продукцию
    OBJECT_STATE_ANY    //состояние не имеет значения
};

enum tableType:int{
    TABLE_PORTS=0,
    TABLE_ON_CONDITIONS,
    TABLE_OFF_CONDITIONS
};

#endif // DEFINES_H
