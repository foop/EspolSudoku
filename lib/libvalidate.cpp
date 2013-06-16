#include "libvalidate.h"

LibValidate::LibValidate()
{

}

//TODO silly name Doubles does not refer to the Datatype
std::list<std::list<int> > LibValidate::findDouble(int field[]) {
    // first save result here
    // we waste one spot for the sake of easier addressing later on
    std::list<int> occurrences[10];
    // return this list
    std::list<std::list<int> > packedOccurrences;

    for (int i = 0; i < 9; i++) {
        // out of range value is assumed to be non-existent
        if (field[i] > 0 && field[i] < 10) {
            occurrences[field[i]].push_back(i);
        }
    }

    std::cout << ":: checkpoint ::" << std::endl;
    for (int i = 0; i < sizeof(occurrences) / sizeof(occurrences[0]); i++) {
        if (occurrences[i].size() > 1) {
            packedOccurrences.push_back(occurrences[i]);
        }
    }
    return packedOccurrences;
}


