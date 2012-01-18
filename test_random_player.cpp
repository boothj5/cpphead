#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "computer_players.hpp"
#include "shithead_exception.hpp"

using namespace std ;

void testIsComputer(void)
{
    RandomPlayer player("Comp");
    assert_true(player.isComputer());
}

void testThrowsExceptionOnAskSwapChoice()
{
    bool thrown = false;

    RandomPlayer player("Comp");
    try {
        player.askSwapChoice();
    } catch (ShitheadException& e) {
        thrown = true;
    }

    assert_true(thrown);
}

void register_random_player_tests()
{
    TEST_MODULE("test_random_player");
    TEST(testIsComputer);
    TEST(testThrowsExceptionOnAskSwapChoice);
}



