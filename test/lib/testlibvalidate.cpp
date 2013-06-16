#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "../../lib/libvalidate.h"

BOOST_AUTO_TEST_CASE( findDouble_noDoubles ) {
    int testArray[9] = {1,2,3,4,5,6,7,8,9};
    BOOST_CHECK( LibValidate::findDouble(testArray).size() == 0 );
}

BOOST_AUTO_TEST_CASE( findDouble_oneDouble_01 ) {
    int testArray[9] = {1,1,3,4,5,6,7,8,9};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    // we get a list of lists containing the indices of the fields that contain doubles
    // since we only got one such case the length must be 1
    BOOST_CHECK( result.size() == 1 );

    // now test that the first sublists contains exactly two indices 
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 1
    BOOST_CHECK( result.back().back() == 1 );
    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 0 );
}

BOOST_AUTO_TEST_CASE( findDouble_oneDouble_07 ) {
    int testArray[9] = {1,2,3,4,5,6,7,1,9};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    // we get a list of lists containing the indices of the fields that contain doubles
    // since we only got one such case the length must be 1
    BOOST_CHECK( result.size() == 1 );

    // now test that the first sublists contains exactly two indices 
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 7
    BOOST_CHECK( result.back().back() == 7 );
    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 0 );
}

BOOST_AUTO_TEST_CASE( findDouble_oneTriple_017 ) {
    int testArray[9] = {1,1,3,4,5,6,7,1,9};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    // we get a list of lists containing the indices of the fields that contain doubles
    // since we only got one such case the length must be 1
    BOOST_CHECK( result.size() == 1 );

    // now test that the first sublists contains exactly tree indices 
    BOOST_CHECK( result.back().size() == 3);
    // last index must be 7
    BOOST_CHECK( result.back().back() == 7 );
    result.back().pop_back();
    // middle index must be 1
    BOOST_CHECK( result.back().back() == 1 );

    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 0 );
}

BOOST_AUTO_TEST_CASE( findDouble_twoDoubles_0179 ) {
    int testArray[9] = {1,1,3,4,5,6,7,8,8};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    BOOST_CHECK( result.size() == 2 );
    
    // last sublist 
    // now test that the first sublists contains exactly two indices 
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 1
    BOOST_CHECK( result.back().back() == 8 );
    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 7 );

    // first sublist
    result.pop_back();
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 1
    BOOST_CHECK( result.back().back() == 1 );
    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 0 );
}


BOOST_AUTO_TEST_CASE( findDouble_threeDoubles_013479 ) {
    int testArray[9] = {1,1,3,5,5,6,7,8,8};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    BOOST_CHECK( result.size() == 3 );
    
    // last sublist 
    // now test that the first sublists contains exactly two indices 
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 1
    BOOST_CHECK( result.back().back() == 8 );
    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 7 );

    // middle sublist
    result.pop_back();
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 4
    BOOST_CHECK( result.back().back() == 4 );
    result.back().pop_back();
    // first index must be 3
    BOOST_CHECK( result.back().back() == 3 );

    // first sublist
    result.pop_back();
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 1
    BOOST_CHECK( result.back().back() == 1 );
    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 0 );
}

BOOST_AUTO_TEST_CASE( findDouble_all_the_same ) {
    int testArray[9] = {1,1,1,1,1,1,1,1,1};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    BOOST_CHECK( result.size() == 1 );
    
    // last sublist 
    BOOST_CHECK( result.back().size() == 9 );
    BOOST_CHECK( result.back().back() == 8 );
    for (int i = 8; i > 0; i--) {
        result.back().pop_back();
    }    
    BOOST_CHECK( result.back().back() == 0 ); 
}

BOOST_AUTO_TEST_CASE( findDouble_all_the_same_with_invalid ) {
    int testArray[9] = {-1,1,1,0,1,1,1,1,11};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    BOOST_CHECK( result.size() == 1 );
    
    // last sublist 
    BOOST_CHECK( result.back().size() == 6 );
    BOOST_CHECK( result.back().back() == 7 );
    for (int i = 5; i > 0; i--) {
        result.back().pop_back();
    }    
    BOOST_CHECK( result.back().back() == 1 ); 
}

BOOST_AUTO_TEST_CASE( findDouble_oneDouble_twoTriples_with_invalid_01234678 ) {
    int testArray[9] = {1,1,5,5,5,-1,8,8,8};
    std::list<std::list<int> > result = LibValidate::findDouble(testArray);
    BOOST_CHECK( result.size() == 3 );
    
    // last sublist 
    // now test that the first sublists contains exactly two indices 
    BOOST_CHECK( result.back().size() == 3 );
    BOOST_CHECK( result.back().back() == 8 );
    result.back().pop_back();
    BOOST_CHECK( result.back().back() == 7 );
    result.back().pop_back();
    BOOST_CHECK( result.back().back() == 6 );

    // middle sublist
    result.pop_back();
    BOOST_CHECK( result.back().size() == 3 );
    BOOST_CHECK( result.back().back() == 4 );
    result.back().pop_back();
    BOOST_CHECK( result.back().back() == 3 );
    result.back().pop_back();
    BOOST_CHECK( result.back().back() == 2 );

    // first sublist
    result.pop_back();
    BOOST_CHECK( result.back().size() == 2 );
    // last index must be 1
    BOOST_CHECK( result.back().back() == 1 );
    result.back().pop_back();
    // first index must be 0
    BOOST_CHECK( result.back().back() == 0 );
}

// EOF
