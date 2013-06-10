#include "sudoku.h" // hint you can switch to the header and back by pressing "F4"
#include "ui_sudoku.h"

sudoku::sudoku(QWidget *parent) :
    QMainWindow(parent),
    // we need the Ui parts to access the parts that we created in textfinder.ui
    ui(new Ui::sudoku)
{
    ui->setupUi(this);

    // create the buttons <- maybe we shouldn't use buttons what else can we use?
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            QToolButton *button = new QToolButton();
            button->setText(QString::number(i));
            connect(button, SIGNAL(clicked()), this, SLOT(increaseNumber()));

            buttons[i][j] = button;
        // we have a seperate array, that can later easily be passed to the
        // controller
            value[i][j] = i;
        }
     }

    // add our buttons to the layout
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

// desctructor - doesn't c++ suck? SCNR
sudoku::~sudoku()
{
    delete ui;
}

