#include <head-unit-cpp.h>

#include "testsuite.hpp"
#include "card.hpp"

void testThreeLowerThanTwo(void)
{
    Card three(THREE, DIAMONDS) ;
    Card two(TWO, HEARTS) ;

    assert_true(Card::shCompare(three, two)) ;
}


void testFiveLowerThanTwo(void)
{
    Card five(FIVE, DIAMONDS) ;
    Card two(TWO, HEARTS) ;

    assert_true(Card::shCompare(five, two)) ;
}

void testJackLowerThanSeven(void)
{
    Card jack(JACK, DIAMONDS) ;
    Card seven(SEVEN, HEARTS) ;

    assert_true(Card::shCompare(jack, seven)) ;
}

void testTwoSpecial(void)
{
    Card two(TWO, DIAMONDS) ;
    assert_true(two.special()) ;
}

void testSevenSpecial(void)
{
    Card seven(SEVEN, DIAMONDS) ;
    assert_true(seven.special()) ;
}

void testTenSpecial(void)
{
    Card ten(TEN, DIAMONDS) ;
    assert_true(ten.special()) ;
}

void testRanksEqual(void)
{
    Card tend(TEN, DIAMONDS) ;
    Card tenh(TEN, HEARTS) ;

    assert_true(tend.equalsRank(tenh)) ;
}

void testRanksNotEqual(void)
{
    Card ten(TEN, DIAMONDS) ;
    Card ace(ACE, HEARTS) ;

    assert_false(ten.equalsRank(ace)) ;
}

void register_card_tests()
{
    add_suite("test_card") ;
    add_test(testThreeLowerThanTwo, "testThreeLowerThanTwo") ;
    add_test(testFiveLowerThanTwo, "testFiveLowerThanTwo") ;
    add_test(testJackLowerThanSeven, "testJackLowerThanSeven") ;
    add_test(testTwoSpecial, "testTwoSpecial") ;
    add_test(testSevenSpecial, "testSevenSpecial") ;
    add_test(testTenSpecial, "testTenSpecial") ;
    add_test(testRanksEqual, "testRanksEqual") ;
    add_test(testRanksNotEqual, "testRanksNotEqual") ;
}

