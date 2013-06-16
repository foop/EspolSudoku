#-------------------------------------------------
#
# Project created by QtCreator 2013-06-09T16:41:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app


SOURCES += main.cpp\
        sudoku.cpp \
    lib/libvalidate.cpp

HEADERS  += sudoku.h \
    lib/libvalidate.h

FORMS    += sudoku.ui
