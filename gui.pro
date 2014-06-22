#-------------------------------------------------
#
# Project created by QtCreator 2014-05-18T17:56:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
		mainwindow.cpp \
	mwidget.cpp \
	algo.cpp

HEADERS  += mainwindow.h \
	mwidget.h \
	algo.h \
	network.h

FORMS    += mainwindow.ui

OTHER_FILES += images/room.png gui.pro.user

LIBS += -lcurl -ljsoncpp
