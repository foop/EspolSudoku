#include "sudoku.h"
#include "ui_sudoku.h"

sudoku::sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudoku)
{
    ui->setupUi(this);

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; i < DIM; i++) {
            QToolButton *button = new QToolButton();
            button->setText(QString::number(i));
            connect(button, SIGNAL(clicked()), this, SLOT(increaseNumber()));
            buttons[i][j] = button;

            value[i][j] = i;
        }
     }
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; i < DIM; i++) {
            ui->gridLayout->addWidget(buttons[i][j],i,j);
        }
     }
}

void sudoku::increaseNumber() {
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    int digitValue = clickedButton->text().toInt();
     //TODO complete
     //change text of button
     //change value in array
}

sudoku::~sudoku()
{
    delete ui;
}

