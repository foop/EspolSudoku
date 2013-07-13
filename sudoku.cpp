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

void Sudoku::displayTop10(std::vector<Record> records) {
    Top10 top10(this);
    int noOfRecords = records[0].seconds;
    connect(this, SIGNAL(addTop10Entry(QString)), &top10, SLOT(addEntry(QString)));
    for (int i = 1; i < noOfRecords; i++) {
       Record r = records[i];
       QString recordString = QString("%1/%2/%3/%4").arg(QString::number(i), QString::fromStdString(r.username),
                              QString::number(r.difficulty), QString::number(r.seconds));
       emit addTop10Entry(recordString);
    }
    disconnect(this, SIGNAL(addTop10Entry(QString)), &top10, SLOT(addEntry(QString)));
    top10.exec();
}

void Sudoku::textChanged(const QString & text) {
    QLineEdit *editedField = qobject_cast<QLineEdit *>(sender());
    int index = ui->gridLayout->indexOf(editedField);
    if ( index != -1 ) {
        int row, col, col_span, row_span;
        ui->gridLayout->getItemPosition(index, &row, &col, &row_span, &col_span);
        bool ok;
        int intValue = text.toInt(&ok, 10);
        emit lastMoveTime(time);
        emit changeValue(row, col, intValue);
    }
}

void Sudoku::disableFields(matrix<int> values) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++ ) {
            if ( values(i,j) > 0 && values(i,j) < 10) {
                qcasillas[i][j]->setDisabled(1);
            } else {
                qcasillas[i][j]->setEnabled(1);
            }
        }
    }
}

void Sudoku::setGameState(matrix<int> values) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
           if ( values(i,j) < 10 && values (i,j) > 0 ) qcasillas[i][j]->setText(QString::number(values(i,j)));
           else qcasillas[i][j]->setText("");
        }
    }
}

void Sudoku::markFields(matrix<bool> toMark) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if ( ui->showDoubles->isChecked() && toMark(i,j) ) qcasillas[i][j]->setStyleSheet("background: #ff00ff");
                else        qcasillas[i][j]->setStyleSheet("background: #ffffff");
        }
    }
}

void Sudoku::stopTimer() {
    time = 0;
    if ( timerExists ) {
        timer->stop();
    }
}

void Sudoku::startTimer() {
    time = 0;
    if ( !timerExists) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
        timerExists = true;
    }
    timer->start(1000);
}

void Sudoku::showTime() {
    //QString timeString;
    time++;
    ui->lcdNumber->display(time);
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
       connect(ui->actionSave,      SIGNAL(triggered()), mcs, SLOT(saveState()));
       connect(ui->actionLoad,      SIGNAL(triggered()), mcs, SLOT(loadState()));
       connect(ui->actionGet_Field, SIGNAL(triggered()), mcs, SLOT(getRandomFieldValue()));
       connect(ui->actionSolve,     SIGNAL(triggered()), mcs, SLOT(getAllFieldsValues()));
       connect(ui->resetGame,       SIGNAL(clicked()),   mcs, SLOT(resetGame()));
       connect(ui->showDoubles,     SIGNAL(stateChanged(int)), mcs, SLOT(getDoublesStateChanged(int)));
       connect(ui->newGame,         SIGNAL(clicked()),   this, SLOT(newGame()));

       //from controller
       connect(mcs, SIGNAL(disableFields(matrix<int>)), this, SLOT(disableFields(matrix<int>)));
       connect(mcs, SIGNAL(setGameState(matrix<int>)),  this, SLOT(setGameState(matrix<int>)));
       connect(mcs, SIGNAL(markFields(matrix<bool>)),   this, SLOT(markFields(matrix<bool>)));
       connect(mcs, SIGNAL(startTimer()),               this, SLOT(startTimer()));
       connect(mcs, SIGNAL(stopTimer()),                this, SLOT(stopTimer()));
       connect(mcs, SIGNAL(displayRecords(std::vector<Record>)), this, SLOT(displayTop10(std::vector<Record>)));
       mcsAssigned = true;
   }
}

void Sudoku::newGame() {
    ChooseDifficultyDialogue d(this);
    d.registerController(mcs);
    d.exec();
    d.raise();
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
