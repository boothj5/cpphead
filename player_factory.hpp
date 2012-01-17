#include <string>
#include <map>
#include "player.hpp"

typedef Player* (*createFunc)(std::string);
typedef std::map<char, createFunc> playerFuncMap_t;
typedef std::map<char, std::string> playerDescMap_t;

class PlayerFactory {
    static const std::pair<playerFuncMap_t, playerDescMap_t> initPlayers();
    static const playerFuncMap_t playerFuncMap();
    static const playerDescMap_t playerDescMap();
 
    public:
    static Player * createPlayer(const std::string, const char);
    static const playerDescMap_t getPlayerDescriptions();
};

template <class T>
Player * createPlayer(const std::string name)
{
    return new T(name);
}

template <class T>
void registerPlayer(const char type, playerFuncMap_t& funcMap, 
    playerDescMap_t& descMap)
{
    funcMap.insert(std::make_pair(type, &createPlayer<T>));
    descMap.insert(std::make_pair(type, T::description));
}
