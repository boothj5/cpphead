#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "player.hpp"
#include "human_player.hpp"
#include "shithead_exception.hpp"

using namespace std ;

static Player *player;

static void setup(void)
{
    player = new HumanPlayer("James");
}

static void teardown(void)
{
    delete player;
}

static void testIsHuman(void)
{
    assert_false(player->isComputer());
}

static void testCannotAskSwapCards(void)
{
    bool thrown = false;
    
    try {
        player->askSwapCards();
    } catch (ShitheadException& e) {
        thrown = true;
    }

    assert_true(thrown);
}

static void testCannotAskSwapChoice(void)
{
    bool thrown = false;
    
    try {
        player->askSwapChoice();
    } catch (ShitheadException& e) {
        thrown = true;
    }

    assert_true(thrown);
}

void register_human_player_tests()
{
    TEST_MODULE("test_human_player");
    SETUP(setup);
    TEST(testIsHuman);
    TEST(testCannotAskSwapCards);
    TEST(testCannotAskSwapChoice);
    TEARDOWN(teardown);
}



