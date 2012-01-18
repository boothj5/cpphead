#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "player.hpp"
#include "human_player.hpp"
#include "shithead_exception.hpp"

using namespace std ;

void testIsHuman(void)
{
    HumanPlayer player("James");
    assert_false(player.isComputer());
}

void testCannotAskSwapCards(void)
{
    HumanPlayer player("James");
    bool thrown = false;
    
    try {
        player.askSwapCards();
    } catch (ShitheadException& e) {
        thrown = true;
    }

    assert_true(thrown);
}

void testCannotAskSwapChoice(void)
{
    HumanPlayer player("James");
    bool thrown = false;
    
    try {
        player.askSwapChoice();
    } catch (ShitheadException& e) {
        thrown = true;
    }

    assert_true(thrown);
}

void register_human_player_tests()
{
    TEST_MODULE("test_human_player");
    TEST(testIsHuman);
    TEST(testCannotAskSwapCards);
    TEST(testCannotAskSwapChoice);
}



