#ifndef BOARD_H
#define BOARD_H

#include "group.h"
#include <list>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <set>

struct Coordinate {
    int x, y;
    Coordinate(int, ax, int ay) : x( ax ), y ( a ) {}
    bool operator== (const Coordinate &c) {
       return (x == c.x && y == c.y);
    }
};

class Board
{
public:
    Board(Group g[]);
    std::list<std::list<std::list<int> > >checkStateOfXY(int x, int y);
    std::list<std::list<int> >checkState();
private:

boost::numeric::ublas::matrix<int> fields;
};

#endif // BOARD_H
