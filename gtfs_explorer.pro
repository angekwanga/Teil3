QT += core gui widgets
CONFIG += c++17
TARGET = gtfs_explorer
SOURCES += main.cpp mainwindow.cpp CSVReader.cpp \
    network.cpp
HEADERS += mainwindow.h types.h CSVReader.h \
    network.h