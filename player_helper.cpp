#include <vector>
#include "card.hpp"
#include "player_helper.hpp"

using namespace std;

PlayerHelper::PlayerHelper(const vector<Card *> pile) 
    : pile_(pile)
{}

vector<Card *> PlayerHelper::getPile() const 
{
    return pile_ ; 
}
