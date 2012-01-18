#include "engines.hpp"

namespace enginefactory {

Engine * createEngine(const int numGames)
{
    if (numGames == 0)
        return new CliEngine();
    else
        return new BattleEngine(numGames);
}

} // namespace enginefactory
