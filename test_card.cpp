#include <head-unit.h>
#include <memory>
#include "card.hpp"

using namespace std;

static Card *threeD;
static Card *twoH;
static Card *fiveD;
static Card *jackD;
static Card *sevenH;
static Card *tenD;
static Card *tenH;
static Card *tenS;
static Card *tenC;
static Card *aceH;
static Card *nineC;

static void setup(void)
{
    threeD = new Card(THREE, DIAMONDS);
    twoH = new Card(TWO, HEARTS);
    fiveD = new Card(FIVE, DIAMONDS) ;
    jackD = new Card(JACK, DIAMONDS) ;
    sevenH = new Card(SEVEN, HEARTS) ;
    tenD = new Card(TEN, DIAMONDS) ;
    tenH = new Card(TEN, HEARTS) ;
    tenS = new Card(TEN, SPADES) ;
    tenC = new Card(TEN, CLUBS) ;
    aceH = new Card(ACE, HEARTS) ;
    nineC = new Card(NINE, CLUBS) ;
}

static void testThreeLowerThanTwo(void)
{
    assert_true(Card::shCompare(*threeD, *twoH)) ;
}

static void testFiveLowerThanTwo(void)
{
    assert_true(Card::shCompare(*fiveD, *twoH)) ;
}

static void testJackLowerThanSeven(void)
{
    assert_true(Card::shCompare(*jackD, *sevenH)) ;
}

static void testTwoSpecial(void)
{
    assert_true(twoH->special()) ;
}

static void testSevenSpecial(void)
{
    assert_true(sevenH->special()) ;
}

static void testTenSpecial(void)
{
    assert_true(tenD->special()) ;
}

static void testRanksEqual(void)
{
    assert_true(tenD->equalsRank(*tenH)) ;
}

static void testRanksNotEqual(void)
{
    assert_false(tenD->equalsRank(*aceH)) ;
}

static void testAllRanksEqual(void)
{
    vector<Card> cards ;
    cards.push_back(*tenS) ;
    cards.push_back(*tenD) ;
    cards.push_back(*tenC) ;
    cards.push_back(*tenH) ;

    assert_true(Card::allRanksEqual(cards)) ;
}

static void testNotAllRanksEqual(void)
{
    vector<Card> cards ;
    cards.push_back(*tenS) ;
    cards.push_back(*tenD) ;
    cards.push_back(*nineC) ;
    cards.push_back(*tenH) ;

    assert_false(Card::allRanksEqual(cards)) ;
}

void register_card_tests()
{
    TEST_MODULE("test_card");
    SETUP(setup);
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

