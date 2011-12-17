#ifndef H_CONSOLE
#define H_CONSOLE
#include <string>

using namespace std ;

void clearScreen(void) ;

void showWelcomeMessage(void) ;

int requestNumPlayers(void) ; 

int requestNumCards(void) ;

string * requestPlayerNames(int) ;
#endif
