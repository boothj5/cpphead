#include <iostream>
#include <string>
#include "console.h"
#include "player.h"

using namespace std ;

void clearScreen()
{
    int i = 0 ;
    for (i = 0 ; i < 100 ; i++) {
        cout << endl ;
    }
}

void showWelcomeMessage()
{
    cout << "Welcome to C++Head!" << endl << endl ;
}

int requestNumPlayers() 
{
    int result ;
    cout << "Please enter number of players: " ;
    cin >> result ;
    return result ;
}

int requestNumCards() 
{
    int result ;
    cout << "Please enter number of cards each: " ;
    cin >> result ;
    return result ;
}

string * requestPlayerNames(int numPlayers)
{
    string * names = new string[numPlayers] ;
    int i ;
    for (i = 0 ; i < numPlayers ; i++) {
        cout << "Enter name for player " << i+1 << ": " ;
        cin >> names[i] ;
    }
    return names ;
}

void showPlayer(Player player) 
{
    cout << player.getName() << endl ;
    cout << "HAND : " ;
    int i ;
    for (i = 0 ; i < player.getHand().size() ; i++) {
        cout << player.getHand()[i].toString() << ", " ;
    }
    cout << endl ;
    cout << "FACEUP : " ;
    for (i = 0 ; i < player.getFaceUp().size() ; i++) {
        cout << player.getFaceUp()[i].toString() << ", " ;
    }
    cout << endl ;
    cout << "FACEDOWN : " ;
    for (i = 0 ; i < player.getFaceDown().size() ; i++) {
        cout << player.getFaceDown()[i].toString() << ", " ;
    }
    cout << endl ;
}
