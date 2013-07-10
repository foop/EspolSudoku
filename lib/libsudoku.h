#ifndef LIBSUDOKU_H
#define LIBSUDOKU_H

#include <boost/numeric/ublas/matrix.hpp>
#include "model/board.h"
#include <string>
#include <fstream>

#define EASY 0
#define MEDIUM 1
#define HARD 2

class LibSudoku {
public:
    LibSudoku();
    static Board generateBoard(int level);
    static void addFieldToFile(matrix<int> f, std::string fileName);
    static matrix<int> stringToField(std::string s);
    static std::string fieldToString(matrix<int> field);
    static void permuteRows(matrix<int> *toPermute, int y1, int y2);
    static void permuteCols(matrix<int> *toPermute, int x1, int x2);
    static void permuteGroupRow(matrix<int> *toPermute, int x1, int x2);
    static void permuteGroupRow(matrix<int> *toPermute, int y1, int y2);
    static void permuteAdd(matrix<int> *toPermute, int valToAdd);
    static void permuteSwap(matrix<int> *toPermute, int val1, int val2);

private:
    static std::string xorEnDecrypt(std::string s);
    static void swap(matrix<int> *toSwap, int x1, int y1, int x2, int y2);
};

static const std::string secret = "verysecretandsecurepassworstringfoobarblatest1212abcdefghijklmnuqurstuvdiatreuia dtrenai eniadter niadet riadet rnaie aiutre nudraie naiudre iuanerduiatrne uidornuai drnueadr naiuor dnaiudetr aiuedrnt uiadne iudrae uinaeugvcghudiae";

#endif // LIBSUDOKU_H
