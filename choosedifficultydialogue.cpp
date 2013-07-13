#include "choosedifficultydialogue.h"
#include "ui_choosedifficultydialogue.h"

ChooseDifficultyDialogue::ChooseDifficultyDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDifficultyDialogue)
{
    ui->setupUi(this);
}


void ChooseDifficultyDialogue::registerController(Controller* &newMcs) {
    mcs = newMcs;

    //toProxy
    connect(ui->buttonEasy, SIGNAL(clicked()), this, SLOT(newGameEasy()));
    connect(ui->buttonMedium, SIGNAL(clicked()), this, SLOT(newGameMedium()));
    connect(ui->buttonHard, SIGNAL(clicked()), this, SLOT(newGameHard()));

    //to Controller
    connect(this, SIGNAL(newGame(int)), mcs, SLOT(newGame(int)));
}

void ChooseDifficultyDialogue::newGameEasy() {
    emit newGame(EASY);
    close();
}

void ChooseDifficultyDialogue::newGameMedium() {
    emit newGame(MEDIUM);
    close();
}

void ChooseDifficultyDialogue::newGameHard() {
    emit newGame(HARD);
    close();
}

ChooseDifficultyDialogue::~ChooseDifficultyDialogue()
{
    delete ui;
}
