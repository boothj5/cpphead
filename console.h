#ifndef H_CONSOLE
#define H_CONSOLE
#include <string>
#include "player.h"

using namespace std ;

void clearScreen() ;
void showWelcomeMessage() ;
int requestNumPlayers() ; 
int requestNumCards() ;
string * requestPlayerNames(int) ;
void showPlayer(const Player&) ;
void showHand(string, const vector<Card>&) ;
#endif
