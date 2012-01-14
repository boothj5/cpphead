#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "simple_player.hpp"

using namespace std ;

void testIsComputer(void)
{
    SimplePlayer player("Comp");
    assert_true(player.isComputer());
}

void register_simple_player_tests()
{
    TEST_MODULE("test_simple_player");
    TEST(testIsComputer);
}



