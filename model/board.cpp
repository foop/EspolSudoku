//#include "board.h"

//using namespace boost::numeric::ublas;

//Board::Board(matrix<int> f) {
//    fields = f;
//}

//std::set<Coordinate> Board::checkStateOfXY(int x, int y) {
//    std::list<Coordinate> coordinates;
//    std::vector<std::list<Coordinate> > = rowTemp(10);
//    std::vector<std::list<Coordinate> > = colTemp(10);
//    std::vector<std::list<Coordinate> > = groupTemp(10);
//    //check row
//    for (int i = 0; i < 9; i++) {
//        if ( matrix(i,y) > 0 && matrix(i,y) < 10 ) {
//            Coordinate * c = new Coordinate(i, y);
//            rowTemp[matrix(i,y)].push_back(c);
//        }
//    }

//    //TODO save entries > 1
//    //check column
//    for (int i = 0; i < 9; i++) {
//        if ( matrix(x,i) > 0 && matrix(x,i) < 10 ) {
//            Coordinate * c = new Coordinate(x, i);
//            colTemp[matrix(x,i)].push_back(c);
//        }
//    }

//    //check group
//    int startx = x / 3;
//    int starty = y / 3;

//    for (int i = 0; i < 3 ; i++ ) {
//        for (int j = 0; j < 3 ; j++ ) {
//            int nextx = startx + j;
//            int nexty = starty + i;
//            if ( matrix(nextx, nexty) > 0 && matrix(nextx, nexty) < 10 ) {
//                Coordinate * c = new Coordiante(nextx, nexty);
//                groupTemp[matrix(x,i)].push_back(c);
//            }
//        }
//    }

//    std::list<Coordinate> filteredRow   = compressMoreThanOnce(rowTemp);
//    std::list<Coordinate> filteredCol   = compressMoreThanOnce(colTemp);
//    std::list<Coordinate> filteredGroup = compressMoreThanOnce(groupTemp);

//    std::set<Coordiante> result = filterSuperflousCoordinates(filteredRow, filteredCol);
//    //TODO does this cause bugs?
//    std::set<Coordiante> result = filterSuperflousCoordinates(filteredRow, filteredGroup);
//    return result;
//}

//std::set<Coordinate> filterSuperflousCoordinates(std::list<Coordinate> firstList, std::list<Coordinate> secondList) {
//    std::set<Coordinate> result;
//    for ( std::list<Coordinate> c : firstList ) {
//        result.insert(c);
//    }
//    for ( std::list<Coordinate> c : secondList ) {
//        result.insert(c);
//    }
//    return result;
//}

//std::list<Coordinate> filterMoreThanOnce(std::vector<std::list<Coordinate> > checkedFields) {
//    std::list<Coordinate> result;
//    for (std::list<Coordinate> c : checkedFields) {
//        if ( c.size > 1 ) result.push_back(c);
//    }
//    return result;
//}

//std::list<std::list<int> >Board::checkState() {

//}
