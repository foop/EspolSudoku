#ifndef BOARD_H
#define BOARD_H

#include <list>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <set>


using namespace boost::numeric::ublas;

struct Coordinate {
    int x, y;
    Coordinate(int ax, int ay) : x( ax ), y ( ay ) {}
    bool operator== (const Coordinate& c) {
       return (x == c.x && y == c.y);
    }
    bool operator< (const Coordinate& c) {
       if ( x < c.x ) {
           return true;
       }
       return (y < c.y);
    }
};


class Board {
public:
    Board();
    Board(matrix<int> f, matrix<bool> d);
    Board(matrix <int> f);
    matrix<int> getField();
    matrix<bool> setXY(int x, int y, int value);
    bool isBoardValid();
    matrix<bool> getAllDoubles();

private:
    void analyse(std::vector<std::list<Coordinate *> > toAnalyse );
    bool areRowsValid();
    bool areColsValid();
    bool areGroupsValid();
    bool isGroupValid(int x, int y);
    void getColDoubles(int x);
    void getGroupDoubles(int x, int y);
    void getRowDoubles(int y);
    void resetDoubles();
    matrix<int> fields = matrix<int>(9,9);
    matrix<bool> doubles = matrix<bool>(9,9);
};

#endif // BOARD_H
