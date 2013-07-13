#ifndef CONTROLLER_H
#define CONTROLLER_H

#define MOTHER_BOARD "/home/dominik/code/qt/sudoku/motherSudoku.sdk"
#define RECORDS_FILE "/home/dominik/code/qt/sudoku/records.sdr"

#include <QObject>

#include "model/board.h"
#include "lib/libsudoku.h"
#include <QFileDialog>
#include <QInputDialog>
#include <fstream>
#include <sstream>
#include <string>

class Controller : public QObject {
    Q_OBJECT
// read interface
public:
    //singleton
    static Controller& getInstance() {
        static Controller instance;
        return instance;
    }

// qt change interface
public slots:
     void changeValue(int x, int y, int value);
     void resetGame();
     void saveState();
     void loadState();
     void newGame(int difficulty);
     void getDoublesStateChanged(int state);
     void getFieldValue(int x, int y);
     void getRandomFieldValue();
     void getAllFieldsValues();
     void checkIfGameEnds();
     void setLastMoveTime(int t);

// qt inform interface
signals:
     void disableFields(matrix<int> fields);
     void markFields(matrix<bool> toMark);
     void setGameState(matrix<int> fields);
     void gameEndCheatedDialogue();
     void gameEndDialogue();
     void startTimer();
     void stopTimer();
     void displayRecords(std::vector<Record>);

private:
     //singleton
     int currentDifficulty;
     int lastMoveTime;
     void gameEnd();
     Controller(Board board = LibSudoku::generateBoard(EASY)) {}
     Controller(Controller const&);
     void operator=(Controller const&);
     bool cheated;
     Board board;
     matrix<int> initialState;
     matrix<int> solvedState;
     bool recordsLoaded = false;
     std::vector<Record> records;
};

#endif // CONTROLLER_H
