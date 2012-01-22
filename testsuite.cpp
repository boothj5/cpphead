#include <head-unit.h>
#include "testsuite.hpp"

int main(void)
{
    register_card_tests() ;
    register_player_tests() ;
    register_random_player_tests() ;
    register_human_player_tests() ;
    register_lowcard_player_tests() ;
    register_highcard_player_tests() ;
    run_suite() ;
    return 0 ;
}
