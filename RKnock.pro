# -------------------------------------------------
# Project created by QtCreator 2009-09-06T06:01:35
# -------------------------------------------------
QT += network \
    xml
TARGET = RKnock
TEMPLATE = app
SOURCES += main.cpp \
    basewindow.cpp \
    serverrecord.cpp \
    knockdialog.cpp \
    knockerthread.cpp
HEADERS += basewindow.h \
    serverrecord.h \
    knockdialog.h \
    knockerthread.h
FORMS += basewindow.ui \
    knockdialog.ui
RESOURCES += core.qrc
