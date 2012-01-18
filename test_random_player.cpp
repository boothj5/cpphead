#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "computer_players.hpp"

using namespace std ;

void testIsComputer(void)
{
    RandomPlayer player("Comp");
    assert_true(player.isComputer());
}

void register_random_player_tests()
{
    TEST_MODULE("test_random_player");
    TEST(testIsComputer);
}



