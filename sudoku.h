#ifndef SUDOKU_H
#define SUDOKU_H

//CONSTANTS
#define DIM 9

#include <QMainWindow>
#include <QToolButton>
#include <QPushButton>
#include <model/tablero.h>



namespace Ui {
class sudoku;
}

class sudoku : public QMainWindow
{
    // I forgot what this actually does - magic
    Q_OBJECT

public:
    // This impedes weird constructor usage
    explicit sudoku(QWidget *parent = 0);
    ~sudoku();
    
private slots:
    void increaseNumber();
    // void decreaseNumber(); Issue No3
    void clickedNumber();

private:
    Ui::sudoku *ui;
    QPushButton *numbers[9][9];
    Tablero *tabla;
    // we'll strore the values in a seperate array so that we can
    // easily pass it to the controller later on
    //int value[DIM][DIM];
    //QLineEdit *qcasillas[DIM][DIM];
};

#endif // SUDOKU_H
