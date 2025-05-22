QT += core gui widgets

CONFIG += c++17

TARGET = gtfs_search
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    network.cpp

HEADERS += \
    mainwindow.h \
    network.h \
    types.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target