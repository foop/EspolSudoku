#include <QApplication>
#include "sudoku.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sudoku w;
    w.show();
    
    return a.exec();
}
