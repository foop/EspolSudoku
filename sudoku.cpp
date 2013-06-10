#include "sudoku.h"
#include "ui_sudoku.h"

sudoku::sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudoku)
{
    ui->setupUi(this);

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            QToolButton *button = new QToolButton();
            button->setText(QString::number(i));
            connect(button, SIGNAL(clicked()), this, SLOT(increaseNumber()));
            buttons[i][j] = button;

            value[i][j] = i;
        }
     }
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            ui->gridLayout->addWidget(buttons[i][j],i,j);
        }
     }
}

void sudoku::increaseNumber() {
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    int digitValue = clickedButton->text().toInt();
     //TODO complete
     //change text of button *check*
     //change value in array - how can I find out which cordinate the button had?
     //                        how are the labeled internally
     //                         * can I change the labels?
     //                         * how can I access the label?
     //send new state event to controller

     // prefix magic
     clickedButton->setText(QString::number(++digitValue % 10));

}


sudoku::~sudoku()
{
    delete ui;
}

