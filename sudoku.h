#ifndef SUDOKU_H
#define SUDOKU_H

//CONSTANTS
#define DIM 9

#include "top10.h"
#include <QTimer>
#include <QMainWindow>
#include <QToolButton>
#include <QLineEdit>
#include <boost/bind.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "model/board.h"
#include "choosedifficultydialogue.h"
#include "lib/libsudoku.h"
#include "controller.h"
#include "top10.h"

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
    void newGame();
    // void decreaseNumber(); Issue No3

public slots:
    void markFields(matrix<bool> toMark);
    void setGameState(matrix<int> values);
    void disableFields(matrix<int> values);
    void startTimer();
    void stopTimer();
    void showTime();
    void displayTop10(std::vector<Record> records);

//inform interface
signals:
     void safeState();
     void loadState();
     void changeValue(int x, int y, int value);
     void lastMoveTime(int t);
     void addTop10Entry(QString s);

private:
    int time;
    QTimer *timer;
    Ui::Sudoku *ui;
    QLineEdit *qcasillas[DIM][DIM];
    Controller *mcs;
    bool timerExists = false;
    bool mcsAssigned = false;
};

#endif // SUDOKU_H
