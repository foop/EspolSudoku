#include "libsudoku.h"

using namespace std;

LibSudoku::LibSudoku()
{

}

Record LibSudoku::encryptedStringToRecord(std::string s) {
    std::string dS =  xorDecrypt(s);
    int difficulty = std::stoi(dS.substr(dS.length() - 1,1));
    std::string secondsString = dS.substr(dS.length() - 9, 8);
    int seconds = std::stoi(secondsString);
    std::string username = dS.substr(0, dS.length() - 9);
    struct Record record;
    record.difficulty = difficulty;
    record.seconds = seconds;
    record.username = username;
    return record;
}

bool LibSudoku::hasMadeItIntoTheRecords(Record r, std::vector<Record> records) {
    sort(records.begin(), records.end());
    int lastRecord = records[0].seconds;
    if ( lastRecord < 10 ) return true;
    return r < records[lastRecord];
}

void LibSudoku::addToRecord(Record r, std::vector<Record> *records) {
    int lastRecord = (*records)[0].seconds;
    sort(records->begin(), records->end());
    if ( lastRecord < 10 ) {
         (*records)[lastRecord + 1] = r;
     (*records)[0].seconds += 1;
    } else {
         (*records)[lastRecord] = r;
    }
}

std::string LibSudoku::recordToEncryptedString(Record r) {
    std::string toEncrypt = r.username;
    int numberOfDigitsOfSeconds = r.seconds > 0 ? (int) log10 ((double) r.seconds) + 1 : 1;
    int numberOfTrailingZeros = 8 - numberOfDigitsOfSeconds;
    for ( int i = 0; i < numberOfTrailingZeros; i++) {
        toEncrypt.append("0");
    }
    toEncrypt.append(std::to_string(r.seconds));
    toEncrypt.append(std::to_string(r.difficulty));
    return xorEncrypt(toEncrypt);
}

void LibSudoku::writeRecordsToFile(std::vector<Record> records, std::string fileName) {
    int maxRecords = records[0].seconds < 10 ? records[0].seconds : 10;
        ofstream fh;
        fh.open(fileName, ios::trunc);
    for (int i = 1; i <= maxRecords; i++) {
        string s = recordToEncryptedString(records[i]);
        fh << s << "\n";
    }
    fh.close();
}


std::vector<Record> LibSudoku::getRecordsFromFile(std::string fileName) {
    std::vector<Record> toProcess = std::vector<Record>(11);
    std::ifstream infile(fileName);
    std::string nextLine;
    int i = 1;
    while ( infile.good() && i < 11) {
        getline(infile, nextLine);
        if ( nextLine != "") {
            toProcess[i] = encryptedStringToRecord(nextLine);
            i++;
        }
    }
    i--;
    infile.close();
    int numberOfRecords = i < 11 ? i : 10;
    // dummyRecord serves as a means of providing meta information
    // it (dummyRecord.seconds) indicates the size of the records vectior
    struct Record dummyRecord;
    // let's set the difficulty higher than possible
    // thus dummyRecord will always be first in the list
    dummyRecord.difficulty = HARD + 1;
    dummyRecord.seconds = numberOfRecords;
    dummyRecord.username = "dummyRecord";
    toProcess[0] = dummyRecord;
    return toProcess;
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

matrix<int> LibSudoku::loadField(string fileName) {
    std::ifstream infile(fileName);
    std::string nextLine;
    std::getline(infile, nextLine);
    matrix<int> field = LibSudoku::stringToField(nextLine);
    infile.close();
    return field;
}


void LibSudoku::addFieldToFile(matrix<int> f, string fileName) {
  ofstream fh;
   //todo maybe ios::trunc
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


string LibSudoku::xorEncrypt(string s) {
    for ( int i = 0; i < s.length(); i++) {
        int c = (s[i] ^ secret[i]);
        s[i] = c + 'z';
    }
    return s;
}

string LibSudoku::xorDecrypt(string s) {
    for ( int i = 0; i < s.length(); i++) {
        int c = (s[i] - 'z');
        c = c ^ secret[i];
        s[i] = c;
    }
    return s;
}

string LibSudoku::xorEnDecrypt(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = s[i] ^ secret[i];
    }
    return s;
}


int LibSudoku::irand(int min, int max) {
    return ((double)rand() / ((double)RAND_MAX + 1.0)) * (max - min + 1) + min;
}

void LibSudoku::permuteWell( matrix<int> *toPermute ) {
    for (int i = 0; i < irand(50,100); i++) {
        if ( irand(0,1) ) {
            permuteSwap(toPermute, irand(1,9), irand(1,9));
        }
        if ( irand(0,1) ) {
            int rowGroup = irand(0,2);
            int row1 = irand(0,2);
            int row2 = irand(0,2);
            permuteRows(toPermute, rowGroup * 3 + row1, rowGroup * 3 + row2);
        }
        if ( irand(0,1) ) {
            int colGroup = irand(0,2);
            int col1 = irand(0,2);
            int col2 = irand(0,2);
            permuteCols(toPermute, colGroup * 3 + col1, colGroup * 3 + col2);
        }
        if ( irand(0,1) ) {
            permuteGroupCols(toPermute, irand(0,2), irand(0,2));
        }
        if ( irand(0,1) ) {
            permuteGroupRows(toPermute, irand(0,2), irand(0,2));
        }
        if ( irand(0,1) ) {
           permuteAdd(toPermute, irand(1,8));
        }
    }
}

bool LibSudoku::hasUniqueSolution(matrix<int> toSolve) {
    bool stillLooking = true;
    int x;
    int y;
    for ( x = 0; x < 9 && stillLooking; x++) {
        for ( y = 0; y < 9 && stillLooking; y++ ) {
            if ( toSolve(x,y) < 1 || toSolve(x,y) > 9 ) {
                 stillLooking = false;
         //dirty dirty dirty
         x--;
                 y--;
            }
        }
    }
    // we are full and valid!
    if (stillLooking) return 1;
    // or not
    int numberOfSolutions = 0;
    for (int i = 1; i < 10; i++) {
        toSolve(x,y) = i;
        Board b = Board(toSolve);
        if ( b.isBoardValid() ) {
            numberOfSolutions += hasUniqueSolution(toSolve);
            if ( numberOfSolutions > 1 ) return false;
        }
    } 
    return numberOfSolutions;
}

matrix<int> LibSudoku::generateGame(matrix<int> field, int difficulty) {
    switch ( difficulty ) {
        case EASY:
        return digEasyHoles(field, 30);
        break;

        case MEDIUM:
        return digEasyHoles(field, 40);
        break;

        case HARD:
        return digHardHoles(field, 45 );
        break;
    }
    return field;
}


matrix<int> LibSudoku::digHardHoles(matrix<int> field, int holesToBeDug) {
    matrix<int> safeField = field;
    matrix<bool> canBeDug = matrix<bool>(9,9);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            canBeDug(i,j) = true;
        }
     }
    for ( int j = 0; j < 2; j++) {
        for ( int i = j; i < 81; i += 2) {
            if ( holesToBeDug <= 0 ) return field;
            int x = i / 9;
            int y = i % 9;
            if ( canBeDug(x,y) ) {
                int safeValue = field(x,y);
                canBeDug(x,y) = false;
                field(x,y) = -1;
                if ( hasUniqueSolution(field) ) {
                    holesToBeDug--;
                } else {
                    field(x,y) = safeValue;
                }
            }
        }
    }
    // no solution? try again
    permuteWell(&safeField);
    generateGame(safeField, HARD);
}

matrix<int> LibSudoku::digEasyHoles(matrix<int> field, int holesToBeDug) {
    int holesToBeDugSafe = holesToBeDug;
    matrix<int> fieldSafe = field;
    matrix<bool> canBeDug = matrix<bool>(9,9);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            canBeDug(i,j) = true;
        }
     }
    int endlessPrevention = 900;
    while (holesToBeDug && endlessPrevention ) {
        endlessPrevention--;
        int x = irand(0,8);
        int y = irand(0,8);
        if ( canBeDug(x,y) ) {
           canBeDug(x,y) = false;
           int safeValue = field(x,y);
           field(x,y) = -1;
           if ( hasUniqueSolution(field) ) {
                holesToBeDug--;
           } else {
                field(x,y) = safeValue;
           }
        }
    }
    if (endlessPrevention) return field;
    return digEasyHoles(fieldSafe, holesToBeDugSafe);
}


void LibSudoku::swap(matrix<int> *toSwap, int x1, int y1, int x2, int y2) {
    int tmp = (*toSwap)(x1,y1);
    (*toSwap)(x1,y1) = (*toSwap)(x2, y2);
    (*toSwap)(x2,y2) = tmp;
}

void LibSudoku::permuteRows(matrix<int> *toPermute, int y1, int y2) {
    if ( y1 != y2 ) {
        for (int i = 0; i < 9; i++) {
            LibSudoku::swap(toPermute, i, y1, i, y2);
        }
    }
}

void LibSudoku::permuteCols(matrix<int> *toPermute, int x1, int x2) {
    if ( x1 != x2 ) {
        for (int i = 0; i < 9; i++) {
            LibSudoku::swap(toPermute, x1, i, x2, i);
        }
    }
}

void LibSudoku::permuteGroupCols(matrix<int> *toPermute, int x1, int x2) {
    if ( x1 != x2 ) {
        for (int i = 0; i < 3; i++) {
            LibSudoku::permuteCols(toPermute, x1 * 3 + i, x2 * 3 + i);
        }
    }
}

void LibSudoku::permuteGroupRows(matrix<int> *toPermute, int y1, int y2) {
    if ( y1 != y2 ) {
        for (int i = 0; i < 3; i++) {
            LibSudoku::permuteRows(toPermute, y1 * 3 + i, y2 * 3 + i);
        }
    }
}

void LibSudoku::permuteAdd(matrix<int> *toPermute, int valToAdd) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            (*toPermute)(i,j) = (((*toPermute)(i,j) + valToAdd - 1) % 9) + 1;
        }
    }
}

void LibSudoku::permuteSwap(matrix<int> *toPermute, int val1, int val2) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ( (*toPermute)(i,j) == val1 ) (*toPermute)(i,j) = val2;
            else if ( (*toPermute)(i,j) == val2 ) (*toPermute)(i,j) = val1;
        }
    }
}
