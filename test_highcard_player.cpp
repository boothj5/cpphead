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
static Card tenH(TEN, HEARTS);

static void beforetest(void)
{
    player = new HighCardPlayer("James");
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

static void choosesHighFromHandWhenEmptyPile()
{
    player->addToHand(fourD);
    player->addToHand(sixH);
    player->addToHand(aceS);
    player->sortHand();
    vector<Card> pile;
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(aceS, player->hand()[choice[0]]);
}

static void choosesHighFromFaceUpWhenEmptyPile()
{
    player->addToFaceUp(sixH);
    player->addToFaceUp(fourD);
    player->addToFaceUp(aceS);
    vector<Card> pile;
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(aceS, player->faceUp()[choice[0]]);
}

static void choosesHighestFromHandOnPile()
{
    player->addToHand(fourD);
    player->addToHand(sixH);
    player->addToHand(aceS);
    player->sortHand();
    vector<Card> pile;
    pile.push_back(sixC);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(aceS, player->hand()[choice[0]]);
}

static void choosesHighestFromFaceUpOnPile()
{
    player->addToFaceUp(fourD);
    player->addToFaceUp(sixH);
    player->addToFaceUp(aceS);
    vector<Card> pile;
    pile.push_back(sixC);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(aceS, player->faceUp()[choice[0]]);
}

static void choosesTwoCardsFromHandWhenCan()
{
    player->addToHand(tenC);
    player->addToHand(fourD);
    player->addToHand(sixH);
    player->addToHand(sixC);
    player->addToHand(tenH);
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
    found = find(cards.begin(), cards.end(), tenH);
    assert_false(found == cards.end());
    found = find(cards.begin(), cards.end(), tenC);
    assert_false(found == cards.end());
}

static void choosesTwoCardsFromFaceUpWhenCan()
{
    player->addToFaceUp(tenC);
    player->addToFaceUp(fourD);
    player->addToFaceUp(sixH);
    player->addToFaceUp(sixC);
    player->addToFaceUp(tenH);
    vector<Card> pile;
    pile.push_back(fiveH);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(2, (int)choice.size());

    vector<Card> cards;
    cards.push_back(player->faceUp()[choice[0]]);
    cards.push_back(player->faceUp()[choice[1]]);
    
    vector<Card>::const_iterator found;
    found = find(cards.begin(), cards.end(), tenH);
    assert_false(found == cards.end());
    found = find(cards.begin(), cards.end(), tenC);
    assert_false(found == cards.end());
}

void register_highcard_player_tests()
{
    TEST_MODULE("test_highcard_player");
    BEFORETEST(beforetest);
    AFTERTEST(aftertest);
    TEST(testIsComputer);
    TEST(testCannotAskSwapChoice);
    TEST(testDoesntSwapCards);
    TEST(alwaysChoosesFirstFaceDownCard);
    TEST(choosesHighFromHandWhenEmptyPile);
    TEST(choosesHighFromFaceUpWhenEmptyPile);
    TEST(choosesHighestFromHandOnPile);
    TEST(choosesHighestFromFaceUpOnPile);
    TEST(choosesTwoCardsFromHandWhenCan);
    TEST(choosesTwoCardsFromFaceUpWhenCan);
}



