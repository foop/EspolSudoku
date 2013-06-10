#ifndef SUDOKU_H
#define SUDOKU_H

//CONSTANTS
#define DIM 9

#include <QMainWindow>
#include <QToolButton>


namespace Ui {
class sudoku;
}

class sudoku : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit sudoku(QWidget *parent = 0);
    ~sudoku();
    
private slots:
    void increaseNumber();

private:
    Ui::sudoku *ui;
    // we'll strore the values in a seperate array so that we can
    // easily pass it to the controller later on
    //TODO really *bla?
    int value[DIM][DIM];
    QToolButton *buttons[DIM][DIM];
};

#endif // SUDOKU_H
