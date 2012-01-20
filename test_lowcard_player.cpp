#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "card.hpp"
#include "computer_players.hpp"
#include "shithead_exception.hpp"
#include "player_helper.hpp"

using namespace std ;

static Player *player;
static Card *fourD;
static Card *fiveH;
static Card *sixH;
static Card *sixC;
static Card *aceS;
static Card *aceD;
static Card *twoS;
static Card *tenC;

static void setup(void)
{
    fourD = new Card(FOUR, DIAMONDS);
    fiveH = new Card(FIVE, HEARTS);
    sixH = new Card(SIX, HEARTS);
    sixC = new Card(SIX, CLUBS);
    aceS = new Card(ACE, SPADES);
    aceD = new Card(ACE, DIAMONDS);
    twoS = new Card(TWO, SPADES);
    tenC = new Card(TEN, CLUBS);
}

static void teardown(void)
{
    delete fourD;
    delete fiveH;
    delete sixH;
    delete sixC;
    delete aceS;
    delete aceD;
    delete twoS;
    delete tenC;
}

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

static void choosesFirstWhenEmptyPile()
{
    player->addToHand(*fourD);
    player->addToHand(*sixH);
    player->addToHand(*aceS);
    player->sortHand();
    vector<Card> pile;
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(0, choice[0]);
}

static void choosesLowestPossibleOnPile()
{
    player->addToHand(*tenC);
    player->addToHand(*fourD);
    player->addToHand(*sixH);
    player->addToHand(*twoS);
    player->addToHand(*aceS);
    player->sortHand();
    vector<Card> pile;
    pile.push_back(*aceD);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(1, (int)choice.size());
    assert_equals(2, choice[0]);
}

static void choosesTwoCardsWhenCan()
{
    player->addToHand(*tenC);
    player->addToHand(*fourD);
    player->addToHand(*sixH);
    player->addToHand(*twoS);
    player->addToHand(*sixC);
    player->addToHand(*aceS);
    player->sortHand();
    vector<Card> pile;
    pile.push_back(*fiveH);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);

    assert_equals(2, (int)choice.size());

    vector<int>::const_iterator found;
    found = find(choice.begin(), choice.end(), 1);
    assert_false(found == choice.end());
    found = find(choice.begin(), choice.end(), 2);
    assert_false(found == choice.end());
}

static void choosesFromFaceFaceWhenNoHand()
{
    player->addToFaceUp(*tenC);
    player->addToFaceUp(*fourD);
    player->addToFaceUp(*sixH);
    vector<Card> pile;
    pile.push_back(*fiveH);
    PlayerHelper helper(pile);
    vector<int> choice = player->askMoveChoice(helper);
    
    assert_equals(1, (int)choice.size());
    assert_equals(2, choice[0]);
}

void register_lowcard_player_tests()
{
    TEST_MODULE("test_lowcard_player");
    SETUP(setup);
    BEFORETEST(beforetest);
    AFTERTEST(aftertest);
    TEST(testIsComputer);
    TEST(testCannotAskSwapChoice);
    TEST(testDoesntSwapCards);
    TEST(alwaysChoosesFirstFaceDownCard);
    TEST(choosesFirstWhenEmptyPile);
    TEST(choosesLowestPossibleOnPile);
    TEST(choosesTwoCardsWhenCan);
    TEST(choosesFromFaceFaceWhenNoHand);
    TEARDOWN(teardown);
}



