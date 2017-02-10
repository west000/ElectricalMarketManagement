#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T08:04:01
#
#-------------------------------------------------

QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ElectricalMarket
TEMPLATE = app

INCLUDEPATH += "C:\Program Files\MySQL\MySQL Server 5.7\include"
LIBS += "C:\Program Files\MySQL\MySQL Server 5.7\lib\libmysql.lib"

SOURCES += main.cpp\
        mainwindow.cpp \
    device.cpp \
    devicewidget.cpp \
    utility.cpp \
    supplier.cpp \
    supplierwidget.cpp \
    store.cpp \
    storewidget.cpp \
    purchase.cpp \
    purchasewidget.cpp \
    sales.cpp \
    saleswidget.cpp

HEADERS  += mainwindow.h \
    device.h \
    devicewidget.h \
    utility.h \
    supplier.h \
    supplierwidget.h \
    store.h \
    storewidget.h \
    purchase.h \
    purchasewidget.h \
    sales.h \
    saleswidget.h

FORMS    += mainwindow.ui
