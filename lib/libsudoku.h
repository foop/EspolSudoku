#ifndef LIBSUDOKU_H
#define LIBSUDOKU_H

#include <boost/numeric/ublas/matrix.hpp>
#include "model/board.h"
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>

#define EASY 1 
#define MEDIUM 2 
#define HARD 3

struct Record {
    std::string username;
    int difficulty;
    int seconds;
    bool operator< (const Record &r) const {
        if ( difficulty > r.difficulty ) {
            return true;
        } else if ( difficulty < r.difficulty ) {
            return false;
        } else {
            return seconds < r.seconds;
        }
    }
};

class LibSudoku {
public:
    LibSudoku();
    static bool hasMadeItIntoTheRecords(Record r, std::vector<Record> records);
    static void addToRecord(Record r, std::vector<Record> *records);
    static matrix<int> loadField(std::string fileName);
    static matrix<int> generateGame(matrix<int> field, int difficulty);
    static Board generateBoard(int level);
    static void addFieldToFile(matrix<int> f, std::string fileName);
    static matrix<int> stringToField(std::string s);
    static std::string fieldToString(matrix<int> field);
    static void permuteWell( matrix<int> *toPermute );
    static int irand(int min, int max);
    static std::vector<Record> getRecordsFromFile(std::string fileName);
    static void writeRecordsToFile(std::vector<Record> records, std::string fileName);

private:
    static matrix<int> digHardHoles(matrix<int> field, int holesToBeDug);
    static matrix<int> digEasyHoles(matrix<int> field, int holesToBeDug);
    static bool hasUniqueSolution(matrix<int> toSolve);
    static std::string xorEncrypt(std::string s);
    static std::string xorDecrypt(std::string s);
    static Record encryptedStringToRecord(std::string s);
    static std::string recordToEncryptedString(Record r);
    static std::string xorEnDecrypt(std::string s);
    static void swap(matrix<int> *toSwap, int x1, int y1, int x2, int y2);
    static void permuteRows(matrix<int> *toPermute, int y1, int y2);
    static void permuteCols(matrix<int> *toPermute, int x1, int x2);
    static void permuteGroupCols(matrix<int> *toPermute, int x1, int x2);
    static void permuteGroupRows(matrix<int> *toPermute, int y1, int y2);
    static void permuteAdd(matrix<int> *toPermute, int valToAdd);
    static void permuteSwap(matrix<int> *toPermute, int val1, int val2);
};
static const std::string secret = "verysecretandsecurepassworstringfoobarblatest1212abcdefghijklmnuqurstuvdiatreuia dtrenai eniadter niadet riadet rnaie aiutre nudraie naiudre iuanerduiatrne uidornuai drnueadr naiuor dnaiudetr aiuedrnt uiadne iudrae uinaeugvcghudiae";

#endif // LIBSUDOKU_H
