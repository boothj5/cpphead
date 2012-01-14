#include <string>
#include <map>
#include "player.hpp"

typedef Player* (*createFunc)(std::string);
typedef std::map<char, createFunc> playerFuncMap_t;

class PlayerFactory {
    static const playerFuncMap_t getPlayerMap();
 
    public:
    static Player * createPlayer(std::string, char);
    static std::vector<char> getPlayerTypes();
};
