#include <map>
#include <string>
#include "player_factory.hpp"
#include "player.hpp"
#include "human_player.hpp"
#include "computer_players.hpp"
#include "shithead_exception.hpp"

#define PLAYER(CLASSNAME) \
    static Player * create ## CLASSNAME(string name) \
    { return new CLASSNAME(name); }

#define REGISTER_PLAYER(CHAR, CLASSNAME) \
    playerMap.insert(make_pair(CHAR, &create ## CLASSNAME))

using namespace std;

namespace p_factory {

PLAYER(HumanPlayer)
PLAYER(SimplePlayer)
PLAYER(LowCardPlayer)
PLAYER(HighCardPlayer)

Player * createPlayer(string name, char type)
{
    typedef Player* (*createPlayerFunction)(string);
    typedef map<char, createPlayerFunction> playerMap_t;

    playerMap_t playerMap;
    REGISTER_PLAYER('h', HumanPlayer);
    REGISTER_PLAYER('s', SimplePlayer);
    REGISTER_PLAYER('l', LowCardPlayer);
    REGISTER_PLAYER('a', HighCardPlayer);

    playerMap_t::const_iterator iter = playerMap.find(type);
    if (iter == playerMap.end())
        throw ShitheadException("Unknown player type");
    else
        return (*iter).second(name);
}

} // namespace p_factory
