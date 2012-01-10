#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "player.hpp"
#include "human_player.hpp"

using namespace std ;

void testIsHuman(void)
{
    HumanPlayer player("Comp");
    assert_false(player.isComputer());
}

void register_human_player_tests()
{
    TEST_MODULE("test_human_player");
    TEST(testIsHuman);
}



