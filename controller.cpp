#include "controller.h"

void Controller::changeValue(int x, int y, int value) {
    matrix<bool> toMark = board.setXY(x,y,value);
    checkIfGameEnds();
    emit markFields(toMark);
}

void Controller::checkIfGameEnds() {
    matrix<int> field = board.getField();
    bool allFilledUp = true;
    for ( int i = 0; i < 9 && allFilledUp; i++) {
        for ( int j = 0; j < 9 && allFilledUp; j++) {
            if ( field(i,j) < 0 || field(i,j) > 9 ) allFilledUp = false;
        }
    }
    if ( board.isBoardValid() && allFilledUp ) {
        if ( !cheated ) {
            gameEnd();
        } else {
            emit gameEndCheatedDialogue();
        }
    }
}

void Controller::gameEnd() {
    emit stopTimer();
    bool ok;
    Record newRecord;
    newRecord.username = "dummy";
    newRecord.difficulty = currentDifficulty;
    newRecord.seconds = lastMoveTime;
    if ( !recordsLoaded ) {
        records = LibSudoku::getRecordsFromFile(RECORDS_FILE);
        recordsLoaded = true;
    }
    if ( LibSudoku::hasMadeItIntoTheRecords(newRecord, records) ) {
            QString text = QInputDialog::getText(0, tr("Enter Name"),tr("User name:"), QLineEdit::Normal,"", &ok);
        newRecord.username = text.toUtf8().constData();
        LibSudoku::addToRecord(newRecord, &records);
        emit displayRecords(records);
        LibSudoku::writeRecordsToFile(records, RECORDS_FILE);
    }
}

void Controller::saveState() {

    QString path = QFileDialog::getSaveFileName();
    LibSudoku::addFieldToFile(board.getField(), path.toUtf8().constData());
}

void Controller::loadState() {
    QString fileName = QFileDialog::getOpenFileName();
    matrix<int> field = LibSudoku::loadField(fileName.toUtf8().constData());
    emit setGameState(field);
    emit markFields(board.getAllDoubles());
    cheated = true;
}

void Controller::resetGame() {
    board = Board(initialState);
    emit setGameState(initialState);
    //just in case
    emit markFields(board.getAllDoubles());
}

void Controller::newGame(int difficulty) {
    //TODO get path;
    currentDifficulty = difficulty;
    std::string file =  MOTHER_BOARD;
    matrix<int> solvedField = LibSudoku::loadField(file);
    LibSudoku::permuteWell(&solvedField);
    matrix<int> field = LibSudoku::generateGame(solvedField, difficulty);
    solvedState = solvedField;
    initialState = field;
    board = Board(field);
    cheated = false;

    emit disableFields(initialState);
    emit setGameState(field);
    emit markFields(board.getAllDoubles());
    emit startTimer();
}

void Controller::getDoublesStateChanged(int state) {
   emit markFields(board.getAllDoubles());
}

void Controller::setLastMoveTime(int t) {
   lastMoveTime = t;
}

void Controller::getRandomFieldValue() {
    int nTimesWithoutFindingEmpty = 0;
    int n = LibSudoku::irand(0, 81);
    matrix<int> field = board.getField();
    while (nTimesWithoutFindingEmpty < 82 && n > -1) {
        for (int i = 0; i < 9 && n > -1; i++) {
            for (int j = 0; j < 9 && n > -1; j++) {
                nTimesWithoutFindingEmpty++;
                if ( field(i,j) < 0 || field(i,j) > 9 ) {
                    if ( n == 0 ) {
                        getFieldValue(i,j);
                        return;
                    }
                    nTimesWithoutFindingEmpty = 0;
                    n--;
                }
            }
        }
    }
}

void Controller::getAllFieldsValues() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            getFieldValue(i,j);
        }
    }
}

void Controller::getFieldValue(int x, int y) {
    //TODO change to true
    cheated = false;
    int val = solvedState(x,y);
    board.setXY(x,y, val);
    emit setGameState(board.getField());
}
