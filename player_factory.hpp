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
    static Player * createPlayer(std::string, char);
    static playerDescMap_t getPlayerDescriptions();
    static std::vector<char> getPlayerTypes();
};
