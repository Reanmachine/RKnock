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
    knockerthread.cpp \
    aboutdialog.cpp
HEADERS += basewindow.h \
    serverrecord.h \
    knockdialog.h \
    knockerthread.h \
    aboutdialog.h \
    core.h
FORMS += basewindow.ui \
    knockdialog.ui \
    aboutdialog.ui
RESOURCES += core.qrc
OTHER_FILES += RKnock.rc
RC_FILE = RKnock.rc
