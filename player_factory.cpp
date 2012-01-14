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

PLAYER(SimplePlayer)
PLAYER(LowCardPlayer)
PLAYER(HighCardPlayer)

const playerFuncMap_t PlayerFactory::getPlayerMap()
{
    static playerFuncMap_t playerMap;
    if (playerMap.empty()) {
        REGISTER_PLAYER('s', SimplePlayer);
        REGISTER_PLAYER('l', LowCardPlayer);
        REGISTER_PLAYER('a', HighCardPlayer);
    }

    return playerMap; 
}

Player * PlayerFactory::createPlayer(string name, char type)
{
    if (type == 'h') {
        return new HumanPlayer(name);
    }
    else {
        const playerFuncMap_t playerMap = PlayerFactory::getPlayerMap();

        playerFuncMap_t::const_iterator iter = playerMap.find(type);
        if (iter == playerMap.end())
            throw ShitheadException("Unknown player type");
        else
            return iter->second(name);
    }
}

vector<char> PlayerFactory::getPlayerTypes()
{
    vector<char> types;
    types.push_back('h');
    const playerFuncMap_t playerMap = PlayerFactory::getPlayerMap();
    
    playerFuncMap_t::const_iterator iter;
    for (iter = playerMap.begin(); iter!=playerMap.end(); iter++) {
        types.push_back(iter->first);
    }
    
    return types;  
}
