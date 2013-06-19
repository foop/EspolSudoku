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
    model/tablero.cpp \
    model/cuadricula.cpp \
    model/casillas.cpp \
    lib/inputdialog.cpp

HEADERS  += sudoku.h \
    lib/libvalidate.h \
    model/board.h \
    model/tablero.h \
    model/cuadricula.h \
    model/casilla.h \
    lib/inputdialog.h

FORMS    += sudoku.ui
