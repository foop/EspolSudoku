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
    lib/libvalidate.cpp \
    model/board.cpp \
    model/field.cpp \
    model/group.cpp

HEADERS  += sudoku.h \
    lib/libvalidate.h \
    model/board.h \
    model/field.h \
    model/group.h

FORMS    += sudoku.ui
