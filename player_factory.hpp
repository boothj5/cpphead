#include <string>
#include "player.hpp"
#include "human_player.hpp"
#include "simple_player.hpp"
#include "lowcard_player.hpp"
#include "highcard_player.hpp"

namespace p_factory {

Player * createPlayer(std::string, char);

} // namespace p_factory
