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
    playerFuncMap.insert(make_pair(CHAR, &create ## CLASSNAME)); \
    playerDescMap.insert(make_pair(CHAR, CLASSNAME::description))

using namespace std;

PLAYER(SimplePlayer)
PLAYER(LowCardPlayer)
PLAYER(HighCardPlayer)
PLAYER(Pyromaniac)

const pair<playerFuncMap_t, playerDescMap_t> PlayerFactory::initPlayers()
{
    static playerFuncMap_t playerFuncMap;
    static playerDescMap_t playerDescMap;

    if (playerFuncMap.empty()) {
        REGISTER_PLAYER('s', SimplePlayer);
        REGISTER_PLAYER('l', LowCardPlayer);
        REGISTER_PLAYER('a', HighCardPlayer);
        REGISTER_PLAYER('p', Pyromaniac);
    }

    return make_pair(playerFuncMap, playerDescMap);
    
}

const playerFuncMap_t PlayerFactory::playerFuncMap()
{
    pair<playerFuncMap_t, playerDescMap_t> maps = PlayerFactory::initPlayers();

    return maps.first;
}

const playerDescMap_t PlayerFactory::playerDescMap()
{
    pair<playerFuncMap_t, playerDescMap_t> maps = PlayerFactory::initPlayers();

    return maps.second;
}

Player * PlayerFactory::createPlayer(string name, char type)
{
    if (type == 'h') {
        return new HumanPlayer(name);
    }
    else {
        const playerFuncMap_t playerFuncMap = PlayerFactory::playerFuncMap();

        playerFuncMap_t::const_iterator iter = playerFuncMap.find(type);
        if (iter == playerFuncMap.end())
            throw ShitheadException("Unknown player type");
        else
            return iter->second(name);
    }
}

playerDescMap_t PlayerFactory::getPlayerDescriptions()
{
    return playerDescMap();
}

vector<char> PlayerFactory::getPlayerTypes()
{
    const playerDescMap_t playerDescMap = PlayerFactory::playerDescMap();
    vector<char> playerTypes;
    
    playerDescMap_t::const_iterator iter;
    for (iter = playerDescMap.begin(); iter!=playerDescMap.end(); iter++) {
        playerTypes.push_back(iter->first);
    }

    return playerTypes;
}
