#ifndef H_PLAYER_INTERACTION
#define H_PLAYER_INTERACTION

#include "player.hpp"
#include "game.hpp"

void player_swap(Player *player, Game& game);
void player_move(const Player *player, Game& game);
void player_facedown_move(const Player *player, Game& game);
#endif
