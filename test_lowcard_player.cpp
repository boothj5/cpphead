#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "card.hpp"
#include "computer_players.hpp"
#include "shithead_exception.hpp"
#include "player_helper.hpp"

using namespace std ;

static Player *player;

static Card fourD(FOUR, DIAMONDS);
static Card fiveH(FIVE, HEARTS);
static Card sixH(SIX, HEARTS);
static Card sixC(SIX, CLUBS);
static Card aceS(ACE, SPADES);
static Card aceD(ACE, DIAMONDS);
static Card twoS(TWO, SPADES);
static Card tenC(TEN, CLUBS);

static void beforetest(void)
{
    player = new LowCardPlayer("James");
}

static void aftertest(void)
{
    delete player;
}

static void testIsComputer(void)
{
    assert_true(player->isComputer());
}

static void testCannotAskSwapChoice()
{
    bool thrown = false;

    try {
        player->askSwapChoice();
    } catch (ShitheadException& e) {
        thrown = true;
    }

    assert_true(thrown);
}

static void testDoesntSwapCards()
{
    assert_false(player->askSwapCards());
}

static void alwaysChoosesFirstFaceDownCard()
{
    assert_equals(0, player->askFaceDownMoveChoice());
}

static void choosesLowFromHandWhenEmptyPile()
{
    player->addToHand(fourD);
    player->addToHand(sixH);
    player->addToHand(aceS);
    player->sortHand();
    vector<Card> pile;
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(fourD, player->hand()[choice[0]]);
}

static void choosesLowFromFaceUpWhenEmptyPile()
{
    player->addToFaceUp(sixH);
    player->addToFaceUp(fourD);
    player->addToFaceUp(aceS);
    vector<Card> pile;
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(fourD, player->faceUp()[choice[0]]);
}

static void choosesLowestFromHandOnPile()
{
    player->addToHand(tenC);
    player->addToHand(fourD);
    player->addToHand(sixH);
    player->addToHand(twoS);
    player->addToHand(aceS);
    player->sortHand();
    vector<Card> pile;
    pile.push_back(aceD);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(aceS, player->hand()[choice[0]]);
}

static void choosesLowestFromFaceUpOnPile()
{
    player->addToFaceUp(tenC);
    player->addToFaceUp(fourD);
    player->addToFaceUp(sixH);
    player->addToFaceUp(twoS);
    player->addToFaceUp(aceS);
    vector<Card> pile;
    pile.push_back(sixC);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(sixH, player->faceUp()[choice[0]]);
}

static void choosesTwoCardsFromHandWhenCan()
{
    player->addToHand(tenC);
    player->addToHand(fourD);
    player->addToHand(sixH);
    player->addToHand(twoS);
    player->addToHand(sixC);
    player->addToHand(aceS);
    player->sortHand();
    vector<Card> pile;
    pile.push_back(fiveH);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(2, (int)choice.size());

    vector<Card> cards;
    cards.push_back(player->hand()[choice[0]]);
    cards.push_back(player->hand()[choice[1]]);
    
    vector<Card>::const_iterator found;
    found = find(cards.begin(), cards.end(), sixH);
    assert_false(found == cards.end());
    found = find(cards.begin(), cards.end(), sixC);
    assert_false(found == cards.end());
}

static void choosesTwoCardsFromFaceUpWhenCan()
{
    player->addToFaceUp(tenC);
    player->addToFaceUp(fourD);
    player->addToFaceUp(sixH);
    player->addToFaceUp(twoS);
    player->addToFaceUp(sixC);
    player->addToFaceUp(aceS);
    vector<Card> pile;
    pile.push_back(fiveH);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(2, (int)choice.size());

    vector<Card> cards;
    cards.push_back(player->faceUp()[choice[0]]);
    cards.push_back(player->faceUp()[choice[1]]);
    
    vector<Card>::const_iterator found;
    found = find(cards.begin(), cards.end(), sixH);
    assert_false(found == cards.end());
    found = find(cards.begin(), cards.end(), sixC);
    assert_false(found == cards.end());
}

void register_lowcard_player_tests()
{
    TEST_MODULE("test_lowcard_player");
    BEFORETEST(beforetest);
    AFTERTEST(aftertest);
    TEST(testIsComputer);
    TEST(testCannotAskSwapChoice);
    TEST(testDoesntSwapCards);
    TEST(alwaysChoosesFirstFaceDownCard);
    TEST(choosesLowFromHandWhenEmptyPile);
    TEST(choosesLowFromFaceUpWhenEmptyPile);
    TEST(choosesLowestFromHandOnPile);
    TEST(choosesLowestFromFaceUpOnPile);
    TEST(choosesTwoCardsFromHandWhenCan);
    TEST(choosesTwoCardsFromFaceUpWhenCan);
}



