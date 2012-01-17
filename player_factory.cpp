#include <map>
#include <string>
#include "player_factory.hpp"
#include "player.hpp"
#include "human_player.hpp"
#include "computer_players.hpp"
#include "shithead_exception.hpp"

using namespace std;

const pair<playerFuncMap_t, playerDescMap_t> PlayerFactory::initPlayers()
{
    static playerFuncMap_t playerFuncMap;
    static playerDescMap_t playerDescMap;

    if (playerFuncMap.empty()) {
        registerPlayer<SimplePlayer>('s', playerFuncMap, playerDescMap);
        registerPlayer<LowCardPlayer>('l', playerFuncMap, playerDescMap);
        registerPlayer<HighCardPlayer>('a', playerFuncMap, playerDescMap);
        registerPlayer<Pyromaniac>('p', playerFuncMap, playerDescMap);
    }

    return make_pair(playerFuncMap, playerDescMap);
}

const playerFuncMap_t PlayerFactory::playerFuncMap()
{
    const pair<playerFuncMap_t, playerDescMap_t> maps = PlayerFactory::initPlayers();

    return maps.first;
}

const playerDescMap_t PlayerFactory::playerDescMap()
{
    pair<playerFuncMap_t, playerDescMap_t> maps = PlayerFactory::initPlayers();

    return maps.second;
}

Player * PlayerFactory::createPlayer(const string name, const char type)
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

const playerDescMap_t PlayerFactory::getPlayerDescriptions()
{
    return playerDescMap();
}
