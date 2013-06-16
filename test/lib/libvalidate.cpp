#include "libvalidate.h"

LibValidate::LibValidate()
{

}

//TODO silly name
std::list<std::list<int> > LibValidate::findDouble(int field[]) {
    // first save result here
    std::list<int> occurrences[9];
    // return this list
    std::list<std::list<int> > packedOccurrences;

    for (int i = 0; i < sizeof(field); i++) {
        // out of range value is assumed to be non-existent
        if (field[i] > 0 && field[i] < 10) {
            occurrences[field[i]].push_back(i);
        }
    }

    for (int i = 0; i < sizeof(occurrences); i++) {
        if (occurrences[i].size() > 1) {
            packedOccurrences.push_back(occurrences[i]);
        }
    }
    return packedOccurrences;
}


