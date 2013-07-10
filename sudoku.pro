#-------------------------------------------------
#
# Project created by QtCreator 2013-06-09T16:41:45
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app


SOURCES += main.cpp\
        sudoku.cpp \
    lib/libvalidate.cpp \
    model/board.cpp \
    lib/libsudoku.cpp \
    controller.cpp

HEADERS  += sudoku.h \
    lib/libvalidate.h \
    model/board.h \
    lib/libsudoku.h \
    controller.h

FORMS    += sudoku.ui \
    frame.ui
