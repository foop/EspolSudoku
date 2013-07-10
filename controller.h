#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "model/board.h"
#include "lib/libsudoku.h"
#include <QFileDialog>
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
     void saveState();
     void loadState();

// qt inform interface
signals:
     void markFields(matrix<bool> toMark);
     void setGameState(matrix<int> fields);

private:
     //singleton
     Controller(Board board = LibSudoku::generateBoard(EASY)) {}
     Controller(Controller const&);
     void operator=(Controller const&);
     Board board;
};

#endif // CONTROLLER_H
