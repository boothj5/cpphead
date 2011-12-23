#ifndef H_CONSOLE
#define H_CONSOLE
#include <string>
#include "player.hpp"
#include "game.hpp"

#define CLEARSCREEN true

using namespace std ;

void clearScreen() ;
void showWelcomeMessage() ;
int requestNumPlayers() ; 
int requestNumCards() ;
string * requestPlayerNames(int) ;
void showPlayers(const vector<Player>&) ;
void showPlayer(const Player&) ;
void showHand(string, const vector<Card>&) ;
bool requestSwapCards(string) ;
int requestHandChoice() ;
int requestFaceUpChoice() ;
bool requestSwapMore(string) ;
void showGame(const Game&) ;
void showPile(const vector<Card>&) ;
vector<int> requestMove(string) ;

#endif
