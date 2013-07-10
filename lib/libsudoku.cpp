#include "libsudoku.h"

using namespace std;

LibSudoku::LibSudoku()
{

}

Board LibSudoku::generateBoard(int level) {
    matrix<int> field = matrix<int>(9,9);
    matrix<bool> doubles = matrix<bool>(9,9);
    for (int i = 0; i < field.size1(); i++) {
        for (int j = 0; j < field.size2(); j++) {
            field(i,j) = -1;
            doubles(i,j) = false;
        }
    }
    Board b = Board(field, doubles);
    return b;
}

void LibSudoku::addFieldToFile(matrix<int> f, string fileName) {
  ofstream fh;
  fh.open(fileName, ios::app);
  string s = xorEnDecrypt(fieldToString(f));
  fh << s << "\n";
  fh.close();
}


string LibSudoku::fieldToString(matrix<int> field) {
    char toReturn[81];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            toReturn[i * 9 + j] = '0' + field(i,j);
        }
    }
    return toReturn;
}

matrix<int> LibSudoku::stringToField(string s) {
   s = xorEnDecrypt(s);
   matrix<int> field = matrix<int>(9,9);
   for (int i = 0; i < 9; i++) {
       for (int j = 0; j < 9; j++) {
           int nexti = (int) (s[i * 9 + j] - '0');
           field(i,j) = nexti;
       }
   }
   return field;
}

string LibSudoku::xorEnDecrypt(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = s[i] ^ secret[i];
    }
    return s;
}


void LibSudoku::swap(matrix<int> *toSwap, int x1, int y1, int x2, int y2) {
    int tmp = (*toSwap)(x1,y1);
    (*toSwap)(x1,y1) = (*toSwap)(x2, y2);
    (*toSwap)(x2,y2) = tmp;
}

void LibSudoku::permuteRows(matrix<int> *toPermute, int y1, int y2) {
    for (int i = 0; i < 9; i++) {
        LibSudoku::swap(toPermute, i, y1, i, y2);
    }
}

void LibSudoku::permuteCols(matrix<int> *toPermute, int x1, int x2) {
    for (int i = 0; i < 9; i++) {
        LibSudoku::swap(toPermute, x1, i, x2, i);
    }
}

void LibSudoku::permuteGroupRow(matrix<int> *toPermute, int x1, int x2) {
    for (int i = 0; i < 3; i++) {
        LibSudoku::permute(toPermute, x1 * 3 + i, x2 * 3 + i);
    }
}

void LibSudoku::permuteGroupRow(matrix<int> *toPermute, int y1, int y2) {
    for (int i = 0; i < 3; i++) {
        LibSudoku::permute(toPermute, y1 * 3 + i, y2 * 3 + i);
    }
}

void LibSudoku::permuteAdd(matrix<int> *toPermute, int valToAdd) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            toPermute(i,y) = ((toPermute(i,y) + valToAdd - 1) % 9) + 1;
        }
    }
}

void LibSudoku::permuteSwap(matrix<int> *toPermute, int val1, int val2) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ( toPermute(i,j) == val1 ) toPermute(i,j) = val2;
            else if ( toPermute(i,j) == val2 ) toPermute(i,j) = val1;
        }
    }
}
