#include "sudoku.h" // hint you can switch to the header and back by pressing "F4"
#include "ui_sudoku.h"

sudoku::sudoku(QWidget *parent) :
    QMainWindow(parent),
    // we need the Ui parts to access the parts that we created in textfinder.ui
    ui(new Ui::sudoku)
{
    ui->setupUi(this);

    // create the buttons <- maybe we shouldn't use buttons what else can we use?
    //cambiado a QLineEdit me parece mas apropiado
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            QLineEdit *cas = new QLineEdit();
            cas->setText(QString::number(i));
            qcasillas[i][j] = cas;

            qcasillas[i][j]->setStyleSheet("border: 1px solid black; font-size: 20px;");
            qcasillas[i][j]->setMaxLength(1);
            qcasillas[i][j]->setCursorPosition(0);
            qcasillas[i][j]->setFixedSize(50,50);

            qcasillas[i][j]->setAlignment(Qt::AlignCenter);

            qcasillas[i][j]->setValidator( new QIntValidator(1, 9, this) );


         // we have a seperate array, that can later easily be passed to the
        // controller2
            value[i][j] = i;
        }
      //  qcasillas[0][0]->setStyleSheet("border-top: 2px solid red; font-size: 20px;");

     }

    // add our buttons to the layout
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            ui->gridLayout->addWidget(qcasillas[i][j],i,j);
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

