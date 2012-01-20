#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "computer_players.hpp"
#include "shithead_exception.hpp"

using namespace std ;

static Player *player;

static void setup(void)
{
    player = new RandomPlayer("James");
}

static void teardown(void)
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

void register_random_player_tests()
{
    TEST_MODULE("test_random_player");
    SETUP(setup);
    TEST(testIsComputer);
    TEST(testCannotAskSwapChoice);
    TEST(testDoesntSwapCards);
    TEST(alwaysChoosesFirstFaceDownCard);
    TEARDOWN(teardown);
}



