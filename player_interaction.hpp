#ifndef H_PLAYER_INTERACTION
#define H_PLAYER_INTERACTION

#include "player.hpp"
#include "game.hpp"

namespace interact {

void swap(Player *player, Game& game);
void move(const Player *player, Game& game);
void facedown_move(const Player *player, Game& game);

} // namespace interact

#endif
