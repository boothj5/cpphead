#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "player.hpp"
#include "computer_player.hpp"

using namespace std ;

void testIsComputer(void)
{
    ComputerPlayer player("Comp");
    assert_true(player.isComputer());
}

void register_computer_player_tests()
{
    TEST_MODULE("test_computer_player");
    TEST(testIsComputer);
}



