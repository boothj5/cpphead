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
void showPlayers(const vector<Player>& players) ;
void showPlayer(const Player&) ;
void showHand(string, const vector<Card>&) ;
bool requestSwapCards(string name) ;
int requestHandChoice() ;
int requestFaceUpChoice() ;
bool requestSwapMore(string name) ;

#endif
