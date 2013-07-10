#include <QApplication>
#include "sudoku.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller *c = & Controller::getInstance();
    Sudoku w;
    w.registerController(c);
    w.show();
    
    return a.exec();
}
