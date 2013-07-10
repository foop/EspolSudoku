#include "sudoku.h" // hint you can switch to the header and back by pressing "F4"
#include "ui_sudoku.h"

using namespace std;
using namespace boost;

Sudoku::Sudoku(QWidget *parent)  : QMainWindow(parent), ui(new Ui::Sudoku) {
    ui->setupUi(this);
    //fields
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            QLineEdit *cas = new QLineEdit();
            cas->setText("");
            qcasillas[i][j] = cas;
            qcasillas[i][j]->setStyleSheet("border: 1px solid black; font-size: 20px;");
            qcasillas[i][j]->setMaxLength(1);
            qcasillas[i][j]->setCursorPosition(0);
            qcasillas[i][j]->setFixedSize(50,50);
            if ( j % 3 == 0 && i % 3 == 0) qcasillas[i][j]->setStyleSheet("margin-right: 5px");
            else if ( i % 3 == 0 ) qcasillas[i][j]->setStyleSheet("margin-top: 5px");
            else if ( j % 3 == 0 ) qcasillas[i][j]->setStyleSheet("margin-top: 5px");
            else qcasillas[i][j]->setStyleSheet("width: 15px; height: 15px;");
            qcasillas[i][j]->setAlignment(Qt::AlignCenter);

            qcasillas[i][j]->setValidator( new QIntValidator(1, 9, this) );
            connect(qcasillas[i][j], SIGNAL( textChanged(const QString & )), this, SLOT(textChanged(const  QString & )));
        }
     }
    // add our buttons to the layout
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            ui->gridLayout->addWidget(qcasillas[i][j],i,j);
        }
     }
}

void Sudoku::textChanged(const QString & text) {
    QLineEdit *editedField = qobject_cast<QLineEdit *>(sender());
    int index = ui->gridLayout->indexOf(editedField);
    if ( index != -1 ) {
        int row, col, col_span, row_span;
        ui->gridLayout->getItemPosition(index, &row, &col, &row_span, &col_span);
        bool ok;
        int intValue = text.toInt(&ok, 10);
        emit changeValue(row, col, intValue);
    }
}

void Sudoku::setGameState(matrix<int> values) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
           if ( values(i,j) < 10 && values (i,j) > 0 ) qcasillas[i][j]->setText(QString::number(values(i,j)));
        }
    }
}

void Sudoku::markFields(matrix<bool> toMark) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (toMark(i,j) ) qcasillas[i][j]->setStyleSheet("background: #ff00ff");
            else        qcasillas[i][j]->setStyleSheet("background: #ffffff");
        }
    }
}

void Sudoku::registerController(Controller* &newMcs) {
   if ( mcs == newMcs) return   ;
   if (mcsAssigned) {
    //TODO disconnect
       disconnect(this, SIGNAL(changeValue(int, int, int)), mcs, SLOT(changeValue(int, int, int)));
       mcsAssigned = false;
   }
   mcs = newMcs;
   if ( mcs ) {
       //to controller
       connect(this, SIGNAL(changeValue(int, int, int)), mcs, SLOT(changeValue(int, int, int)));
       connect(ui->actionSave, SIGNAL(triggered()), mcs, SLOT(saveState()));
       connect(ui->actionLoad, SIGNAL(triggered()), mcs, SLOT(loadState()));

       //from controller
       connect(mcs, SIGNAL(setGameState(matrix<int>)), this, SLOT(setGameState(matrix<int>)));
       connect(mcs, SIGNAL(markFields(matrix<bool>)), this, SLOT(markFields(matrix<bool>)));
       mcsAssigned = true;
   }
}

//todo can we still use this?
void Sudoku::increaseNumber() {
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

Sudoku::~Sudoku()
{
    delete ui;
}
