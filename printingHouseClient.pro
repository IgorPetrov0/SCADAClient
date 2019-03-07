#-------------------------------------------------
#
# Project created by QtCreator 2019-02-20T06:03:48
#
#-------------------------------------------------

QT       += core gui\
            serialport \
            network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = printingHouseClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    clientsocket.cpp \
    errorprocessor.cpp \
    mashine.cpp \
    object.cpp \
    newObjectMaster/newobjectmaster_1.cpp \
    newObjectMaster/newobjectmaster_2.cpp \
    newObjectMaster/newobjectmasterbase.cpp \
    newObjectMaster/newobjectmasterpage.cpp \
    reports/dayreport.cpp \
    reports/reportclass.cpp \
    reports/shiftreport.cpp \
    serviceClasses/deleteobjectdialog.cpp \
    serviceClasses/kalendardialog.cpp \
    serviceClasses/linebutton.cpp \
    serviceClasses/netdialog.cpp \
    serviceClasses/reportdialog.cpp \
    serviceClasses/serialportsdialog.cpp \
    widgets/basegraphwidget.cpp \
    widgets/basewidget.cpp \
    widgets/graphwidget.cpp \
    widgets/maintabwidget.cpp \
    widgets/mashinetable.cpp \
    widgets/perfomancewidget.cpp \
    tcpclient.cpp \
    serviceClasses/connectionindicator.cpp

HEADERS += \
        mainwindow.h \
    clientsocket.h \
    defines.h \
    errorprocessor.h \
    mashine.h \
    object.h \
    newObjectMaster/newobjectmaster_1.h \
    newObjectMaster/newobjectmaster_2.h \
    newObjectMaster/newobjectmasterbase.h \
    newObjectMaster/newobjectmasterpage.h \
    reports/dayreport.h \
    reports/reportclass.h \
    reports/shiftreport.h \
    serviceClasses/deleteobjectdialog.h \
    serviceClasses/kalendardialog.h \
    serviceClasses/linebutton.h \
    serviceClasses/netdialog.h \
    serviceClasses/reportdialog.h \
    serviceClasses/serialportsdialog.h \
    widgets/basegraphwidget.h \
    widgets/basewidget.h \
    widgets/graphwidget.h \
    widgets/maintabwidget.h \
    widgets/mashinetable.h \
    widgets/perfomancewidget.h \
    tcpclient.h \
    serviceClasses/connectionindicator.h

FORMS += \
        mainwindow.ui \
    reportdialog.ui \
    newObjectMaster/form.ui \
    newObjectMaster/newobjectmaster_1.ui \
    newObjectMaster/newobjectmaster_2.ui \
    newObjectMaster/newobjectmasterbase.ui \
    serviceClasses/deleteobjectdialog.ui \
    serviceClasses/kalendardialog.ui \
    serviceClasses/netdialog.ui \
    serviceClasses/reportdialog.ui \
    serviceClasses/serialportsdialog.ui \
    widgets/basegraphwidget.ui \
    widgets/graphwidget.ui \
    widgets/maintabwidget.ui \
    widgets/perfomancewidget.ui
