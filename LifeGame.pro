#-------------------------------------------------
#
# Project created by QtCreator 2017-07-30T15:03:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LifeGame
TEMPLATE = app


SOURCES += main.cpp\
        lifegamewidget.cpp \
    worldframe.cpp \
    cell.cpp

HEADERS  += \
    worldframe.hpp \
    lifegamewidget.hpp \
    cell.hpp

QMAKE_CXXFLAGS += -std=c++11
