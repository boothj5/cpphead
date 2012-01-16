#include <head-unit.h>

#include "card.hpp"

void testThreeLowerThanTwo(void)
{
    Card three(THREE, DIAMONDS) ;
    Card two(TWO, HEARTS) ;

    assert_true(Card::shCompare(&three, &two)) ;
}


void testFiveLowerThanTwo(void)
{
    Card five(FIVE, DIAMONDS) ;
    Card two(TWO, HEARTS) ;

    assert_true(Card::shCompare(&five, &two)) ;
}

void testJackLowerThanSeven(void)
{
    Card jack(JACK, DIAMONDS) ;
    Card seven(SEVEN, HEARTS) ;

    assert_true(Card::shCompare(&jack, &seven)) ;
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

void testAllRanksEqual(void)
{
    vector<Card *> cards ;
    Card tenspades(TEN, SPADES) ;
    Card tendiamonds(TEN, DIAMONDS) ;
    Card tenclubs(TEN, CLUBS) ;
    Card tenhearts(TEN, HEARTS) ;

    cards.push_back(&tenspades) ;
    cards.push_back(&tendiamonds) ;
    cards.push_back(&tenclubs) ;
    cards.push_back(&tenhearts) ;

    assert_true(Card::allRanksEqual(cards)) ;
}

void testNotAllRanksEqual(void)
{
    vector<Card *> cards ;
    Card tenspades(TEN, SPADES) ;
    Card tendiamonds(TEN, DIAMONDS) ;
    Card nineclubs(NINE, CLUBS) ;
    Card tenhearts(TEN, HEARTS) ;

    cards.push_back(&tenspades) ;
    cards.push_back(&tendiamonds) ;
    cards.push_back(&nineclubs) ;
    cards.push_back(&tenhearts) ;

    assert_false(Card::allRanksEqual(cards)) ;
}
void register_card_tests()
{
    TEST_MODULE("test_card");
    TEST(testThreeLowerThanTwo);
    TEST(testFiveLowerThanTwo);
    TEST(testJackLowerThanSeven);
    TEST(testTwoSpecial);
    TEST(testSevenSpecial);
    TEST(testTenSpecial);
    TEST(testRanksEqual);
    TEST(testRanksNotEqual);
    TEST(testAllRanksEqual);
    TEST(testNotAllRanksEqual);
}

