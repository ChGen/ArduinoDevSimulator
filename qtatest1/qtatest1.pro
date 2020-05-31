QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtatest1
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    arcode.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

CONFIG += c++11
