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
void showPlayer(Player&) ;
void showHand(string, vector<Card>) ;
#endif
