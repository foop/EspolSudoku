#include "board.h"

using namespace boost::numeric::ublas;
using namespace std;


Board::Board() {
    matrix<int> fields = matrix<int>(9,9);
    matrix<bool> doubles = matrix<bool>(9,9);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fields(i,j) = -1;
            doubles(i,j) = false;
        }
    }
}

Board::Board(matrix<int> f, matrix<bool> d) {
    fields = f;
    doubles = d;
}

matrix<int> Board::getField() {
    return fields;
}

matrix<bool> Board::setXY(int x, int y, int value) {
    fields(x,y) = value;
    return getAllDoubles();
}


void Board::resetDoubles() {
    for ( int i = 0; i < 9; i++) {
        for ( int j = 0; j < 9; j++) {
            doubles(i,j) = false;
        }
    }
}

matrix<bool> Board::getAllDoubles() {
    resetDoubles();
    for (int i = 0; i < 9; i++) {
        getRowDoubles(i);
        getColDoubles(i);
    }
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j+= 3) {
            getGroupDoubles(i, j);
        }
    }
    return doubles;
}

bool Board::isBoardValid() {
    return areRowsValid() && areColsValid() && areGroupsValid();
}

bool Board::areRowsValid() {
    int nextVal;
    std::vector<bool> alreadyTaken(10);
    for (int j = 0; j < 9; j++) {
        for (int k = 1; k < 10; k++) {
           alreadyTaken[k] = false;
        }
        for (int i = 0; i < 9; i++) {
            nextVal = fields(i,j);
            if ( nextVal > 0 && nextVal < 10) {
                if ( alreadyTaken[nextVal] ) {
                    return false;
                }
                alreadyTaken[nextVal] = true;
            }
        }
    }
    return true;
}

bool Board::areColsValid() {
    int nextVal;
    std::vector<bool> alreadyTaken(10);
    for (int j = 0; j < 9; j++) {
        for (int k = 1; k < 10; k++) {
            alreadyTaken[k] = false;
        }
        for (int i = 0; i < 9; i++) {
            nextVal = fields(j,i);
            if ( nextVal > 0 && nextVal < 10) {
                if ( alreadyTaken[nextVal] ) {
                    return false;
                }
                alreadyTaken[nextVal] = true;
            }
        }
    }
    return true;
}

bool Board::areGroupsValid() {
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if ( !isGroupValid(i,j) ) {
                return false;
            }
        }
    }
    return true;
}

bool Board::isGroupValid(int x, int y) {
    int nextVal;
    std::vector<bool> alreadyTaken(10);
    for (int k = 1; k < 10; k++) {
        alreadyTaken[k] = false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nextVal = fields(x + i, y + j);
            if ( alreadyTaken[nextVal] ) return false;
        }
    }
    return true;
}

void Board::getRowDoubles(int y) {
    std::vector<std::list<Coordinate *> > rowTemp(10);
    for (int i = 0; i < 9; i++) {
        // reset doubles matrix
        // safety check
        if ( fields(i,y) > 0 && fields(i,y) < 10 ) {
            Coordinate * c = new Coordinate(i, y);
            rowTemp[fields(i,y)].push_back(c);
        }
    }
    analyse(rowTemp);
}

void Board::getColDoubles(int x) {
    std::vector<std::list<Coordinate *> > colTemp(10);
    //check column
    for (int i = 0; i < 9; i++) {
        // reset doubles matrix
        if ( fields(x,i) > 0 && fields(x,i) < 10 ) {
            // safety check
            Coordinate * c = new Coordinate(x, i);
            colTemp[fields(x,i)].push_back(c);
        }
    }
    analyse(colTemp);
}

void Board::getGroupDoubles(int x, int y) {
    std::vector<std::list<Coordinate *> > groupTemp(10);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int nextx = x + i;
            int nexty = y + j;
            if ( fields(nextx,nexty) > 0 && fields(nextx, nexty) < 10 ) {
                Coordinate * c = new Coordinate(nextx, nexty);
                groupTemp[fields(nextx,nexty)].push_back(c);
            }
        }
        analyse(groupTemp);
    }
}

void Board::analyse(std::vector<std::list<Coordinate *> > toAnalyse ) {
    for (int i = 1; i < 10; i++) {
        if ( toAnalyse[i].size() > 1 ) {
            for ( Coordinate * c : toAnalyse[i] ) {
                doubles(c->x, c->y) = true;
            }
        }
    }
}
