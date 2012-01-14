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
    playerFuncMap.insert(make_pair(CHAR, &create ## CLASSNAME))

using namespace std;

PLAYER(SimplePlayer)
PLAYER(LowCardPlayer)
PLAYER(HighCardPlayer)

const playerFuncMap_t PlayerFactory::playerFuncMap()
{
    static playerFuncMap_t playerFuncMap;
    if (playerFuncMap.empty()) {
        REGISTER_PLAYER('s', SimplePlayer);
        REGISTER_PLAYER('l', LowCardPlayer);
        REGISTER_PLAYER('a', HighCardPlayer);
    }

    return playerFuncMap; 
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



vector<char> PlayerFactory::getPlayerTypes()
{
    vector<char> types;
    types.push_back('h');
    const playerFuncMap_t playerFuncMap = PlayerFactory::playerFuncMap();
    
    playerFuncMap_t::const_iterator iter;
    for (iter = playerFuncMap.begin(); iter!=playerFuncMap.end(); iter++) {
        types.push_back(iter->first);
    }
    
    return types;  
}
