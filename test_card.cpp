#include <head-unit.h>
#include <memory>
#include "card.hpp"

using namespace std;

static Card threeD(THREE, DIAMONDS);
static Card twoH(TWO, HEARTS);
static Card fiveD(FIVE, DIAMONDS);
static Card jackD(JACK, DIAMONDS);
static Card sevenH(SEVEN, HEARTS);
static Card tenD(TEN, DIAMONDS);
static Card tenH(TEN, HEARTS);
static Card tenS(TEN, SPADES);
static Card tenC(TEN, CLUBS);
static Card aceH(ACE, HEARTS);
static Card nineC(NINE, CLUBS);

static void testThreeLowerThanTwo(void)
{
    assert_true(Card::shCompare(threeD, twoH));
}

static void testFiveLowerThanTwo(void)
{
    assert_true(Card::shCompare(fiveD, twoH));
}

static void testJackLowerThanSeven(void)
{
    assert_true(Card::shCompare(jackD, sevenH));
}

static void testTwoSpecial(void)
{
    assert_true(twoH.special());
}

static void testSevenSpecial(void)
{
    assert_true(sevenH.special());
}

static void testTenSpecial(void)
{
    assert_true(tenD.special());
}

static void testRanksEqual(void)
{
    assert_true(tenD.equalsRank(tenH));
}

static void testRanksNotEqual(void)
{
    assert_false(tenD.equalsRank(aceH));
}

static void testAllRanksEqual(void)
{
    vector<Card> cards;
    cards.push_back(tenS);
    cards.push_back(tenD);
    cards.push_back(tenC);
    cards.push_back(tenH);

    assert_true(Card::allRanksEqual(cards));
}

static void testNotAllRanksEqual(void)
{
    vector<Card> cards;
    cards.push_back(tenS);
    cards.push_back(tenD);
    cards.push_back(nineC);
    cards.push_back(tenH);

    assert_false(Card::allRanksEqual(cards));
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

