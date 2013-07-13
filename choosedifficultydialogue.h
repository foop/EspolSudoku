#ifndef CHOOSEDIFFICULTYDIALOGUE_H
#define CHOOSEDIFFICULTYDIALOGUE_H

#include <QDialog>
#include "lib/libsudoku.h"
#include "controller.h"

namespace Ui {
class ChooseDifficultyDialogue;
}

class ChooseDifficultyDialogue : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChooseDifficultyDialogue(QWidget *parent = 0);
    void registerController(Controller* &newMcs);
    ~ChooseDifficultyDialogue();

public slots:

signals:
    void newGame(int difficulty);

private slots:
    void newGameEasy();
    void newGameMedium();
    void newGameHard();

private:
    Ui::ChooseDifficultyDialogue *ui;
    Controller *mcs;
};

#endif // CHOOSEDIFFICULTYDIALOGUE_H
