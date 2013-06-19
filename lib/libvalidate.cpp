//#include "libvalidate.h"

//LibValidate::LibValidate()
//{

//}

//TODO silly name Doubles does not refer to the Datatype
//std::list<std::list<int> > LibValidate::findDouble(std::vector<int> field) {
//    // first save result here
//    // we waste one spot for the sake of easier addressing later on
//    std::list<int> occurrences[10];
//    // return this list
//    std::list<std::list<int> > packedOccurrences;

//    std::vector<int>::iterator it = field.begin();
//    for (int i = 0; it != field.end(); ++it, i++) {
//        // out of range value is assumed to be non-existent
//        if (field[i] > 0 && field[i] < 10) {
//            occurrences[field[i]].push_back(i);
//        }
//    }

//    //TODO change to iterator code
//    for (int i = 0; i < sizeof(occurrences) / sizeof(occurrences[0]); i++) {
//        if (occurrences[i].size() > 1) {
//            packedOccurrences.push_back(occurrences[i]);
//        }
//    }
//    return packedOccurrences;
//}


