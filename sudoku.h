#ifndef SUDOKU_H
#define SUDOKU_H

//CONSTANTS
#define DIM 9

#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <boost/bind.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "controller.h"
#include "model/board.h"

using namespace boost::numeric::ublas;

namespace Ui {
class Sudoku;
}

class Sudoku : public QMainWindow
{
    // I forgot what this actually does - magic
    Q_OBJECT

public:
    // This impedes weird constructor usage
    explicit Sudoku(QWidget* parent = 0);
    void registerController(Controller *&newMcs);

    ~Sudoku();

//change interface
private slots:
    void increaseNumber();
    void textChanged(const QString & text);
    // void decreaseNumber(); Issue No3

public slots:
    void markFields(matrix<bool> toMark);
    void setGameState(matrix<int> values);

//inform interface
signals:
     void safeState();
     void loadState();
     void changeValue(int x, int y, int value);

private:
    Ui::Sudoku *ui;
    QLineEdit *qcasillas[DIM][DIM];
    Controller *mcs;
    bool mcsAssigned = false;
};

#endif // SUDOKU_H
