#include <iostream>
#include <string>
#include "console.hpp"
#include "player.hpp"

using namespace std ;

void clearScreen()
{
    if (CLEARSCREEN) {
        int i = 0 ;
        for (i = 0 ; i < 100 ; i++) {
            cout << endl ;
        }
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

void showPlayers(const vector<Player>& players)
{
    int i ;
    for (i = 0 ; i < players.size() ; i++) {
        showPlayer(players[i]) ;
        cout << endl ;
    }
}

void showPlayer(const Player& player) 
{
    cout << player.getName() << endl ;
    showHand("HAND :     ", player.getHand()) ;
    showHand("FACEUP :   ", player.getFaceUp()) ;
    showHand("FACEDOWN : ", player.getFaceDown()) ;
}

void showHand(string name, const vector<Card>& cards)
{
    cout << name ;
    int i ;
    for (i = 0 ; i < cards.size() ; i++) {
        cout << cards[i].toString() << ", " ;
    }
    cout << endl ;
}

bool requestSwapCards(string name)
{
    string response ;
    cout << name << " do you want to swap cards (y/n) : " ;
    cin >> response ;
    return (response == "Y" || response == "y") ;
}

bool requestSwapMore(string name) 
{
    string response ;
    cout << name << " do you want to swap more cards (y/n) : " ;
    cin >> response ;
    return (response == "Y" || response == "y") ;
}

int requestHandChoice() 
{
    int response ;
    cout << "Enter a hand card: " ;
    cin >> response ;
    return response - 1 ;
}

int requestFaceUpChoice()
{
    int response ;
    cout << "Enter a face up card: " ;
    cin >> response ;
    return response - 1 ;
}

void showGame(const Game& game)
{
    clearScreen() ;
    showPile(game.getPile()) ;
    cout << game.getDeck().size() << " on deck" << endl << endl ;
    cout << "0 burnt" << endl ;
    cout << endl ;
    
    showPlayers(game.getPlayers()) ;
    cout << endl ;
    cout << game.getLastMove() << endl ;
}

void showPile(const vector<Card>& pile)
{
    cout << pile.size() << " on pile:" << endl ;
    int i ;
    for (i = 0 ; i < pile.size() ; i++)
        cout << "    " << pile[i].toString() << endl ;
    cout << endl ;
}
