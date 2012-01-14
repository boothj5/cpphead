#include <map>
#include <string>
#include "player_factory.hpp"
#include "player.hpp"
#include "human_player.hpp"
#include "simple_player.hpp"
#include "lowcard_player.hpp"
#include "highcard_player.hpp"
#include "shithead_exception.hpp"

using namespace std;

namespace p_factory {

static Player * createHumanPlayer(string name)
{
    return new HumanPlayer(name);
}

static Player * createSimplePlayer(string name)
{
    return new SimplePlayer(name);
}

static Player * createLowCardPlayer(string name)
{
    return new LowCardPlayer(name);
}

static Player * createHighCardPlayer(string name)
{
    return new HighCardPlayer(name);
}

Player * createPlayer(string name, char type)
{
    typedef Player* (*createPlayerFunction)(string);
    typedef map<char, createPlayerFunction> playerMap_t;

    playerMap_t playerMap;
    playerMap.insert(make_pair('h', &createHumanPlayer));
    playerMap.insert(make_pair('s', &createSimplePlayer));
    playerMap.insert(make_pair('l', &createLowCardPlayer));
    playerMap.insert(make_pair('a', &createHighCardPlayer));

    playerMap_t::const_iterator iter = playerMap.find(type);
    if (iter == playerMap.end())
        throw ShitheadException("Unknown player type");
    else
        return (*iter).second(name);
}

} // namespace p_factory
