#include "controller.h"

void Controller::changeValue(int x, int y, int value) {
    matrix<bool> toMark = board.setXY(x,y,value);
    emit markFields(toMark);
}

void Controller::saveState() {

    QString path = QFileDialog::getSaveFileName();
    LibSudoku::addFieldToFile(board.getField(), path.toUtf8().constData());
}

void Controller::loadState() {
    QString fileName = QFileDialog::getOpenFileName();
    std::ifstream infile(fileName.toUtf8().constData());
    std::string nextLine;
    std::getline(infile, nextLine);
    matrix<int> field = LibSudoku::stringToField(nextLine);
    emit setGameState(field);
    emit markFields(board.getAllDoubles());
    infile.close();
}
