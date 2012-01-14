#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include "console.hpp"
#include "player.hpp"
#include "player_factory.hpp"

using namespace std ;
using namespace boost ;

namespace console {

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
    string inp ;
    int num;
    cout << "Please enter number of players: " ;
    getline(cin, inp) ;
    stringstream(inp) >> num;

    return num ;
}

int requestNumCards() 
{
    string inp ;
    int num;
    cout << "Please enter number of cards each: " ;
    getline(cin, inp) ;
    stringstream(inp) >> num;

    return num ;
}

string requestPlayerName(int num)
{
    string name;
    cout << "Enter name for player " << num << ": ";
    getline(cin, name);

    return name;
}

char requestPlayerType(int num)
{
    string inp;
    char type;
    
    cout << endl << "Enter player type for player " << num << ":" << endl;
    
    cout << endl << "h --> Human player." << endl;

    playerDescMap_t playerDescMap = PlayerFactory::getPlayerTypes();

    playerDescMap_t::const_iterator iter;
    for (iter = playerDescMap.begin(); iter!=playerDescMap.end(); iter++) {
        cout << iter->first << " --> " << iter->second << endl; 
    }
    
    cout << endl;
    
    getline(cin, inp);
    type = inp[0];

    return type;
}

void showPlayers(const vector<Player* >& players)
{
    vector<Player *>::const_iterator player ;
    for (player = players.begin() ; player != players.end() ; player++) {
        showPlayer(**player) ;
        cout << endl ;
    }
}

void showPlayer(const Player& player) 
{
    cout << player.name() << endl ;
    showHand("HAND :     ", player.hand(), false) ;
    showHand("FACEUP :   ", player.faceUp(), false) ;
    showHand("FACEDOWN : ", player.faceDown(), true) ;
}

void showHand(string name, const vector<Card>& cards, bool hide)
{
    cout << name ;
    
    vector<Card>::const_iterator card ;
    int i = 1 ;
    for (card = cards.begin() ; card != cards.end() ; card++) {
        if (hide)
            cout << "(" << i << ")" << "****" ; 
        else
            cout << "(" << i << ")" << *card ; 
        if (i != cards.size())
            cout << ", " ;
        i++ ;
    }

    cout << endl ;
}

bool requestSwapCards(string name)
{
    string response ;
    cout << name << " do you want to swap cards (y/n) : " ;
    getline(cin, response) ;
    return (response == "Y" || response == "y") ;
}

bool requestSwapMore(string name) 
{
    string response ;
    cout << name << " do you want to swap more cards (y/n) : " ;
    getline(cin, response) ;
    return (response == "Y" || response == "y") ;
}

int requestHandChoice() 
{
    string inp;
    int choice ;
    cout << "Enter a hand card: " ;
    getline(cin, inp) ;
    stringstream(inp) >> choice;
    return choice - 1 ;
}

int requestFaceUpChoice()
{
    string inp;
    int choice ;
    cout << "Enter a face up card: " ;
    getline(cin, inp) ;
    stringstream(inp) >> choice;
    return choice - 1 ;
}

void showGame(const Game& game)
{
    clearScreen() ;
    showPile(game.pile()) ;
    cout << game.deck().size() << " on deck" << endl << endl ;
    cout << game.burnt() << " burnt" << endl ;
    cout << endl ;
    
    showPlayers(game.players()) ;
    cout << endl ;
    cout << game.lastMove() ;
    wait_user();
}

void showPile(const vector<Card>& pile)
{
    cout << pile.size() << " on pile:" << endl ;
    int i ;
    for (i = pile.size() ; i > 0 ; i--)
        cout << "    " << pile[i-1] << endl ;
    cout << endl ;
}

static vector<int> parseChoices(string strChoices)
{
    vector<int> choices ;
    vector<string> splitString ;
    split(splitString, strChoices, is_any_of(","));
    int i ;
    for (i = 0 ; i < splitString.size() ; i++) {
        string choice = splitString[i] ;
        stringstream str(choice) ;
        int choiceInt ;
        str >> choiceInt ;
        if (!str) {
            choices.clear() ;
            return choices ;
        }
        else {
            choices.push_back(choiceInt - 1) ;
        }
    }

    return choices ;
}

vector<int> requestMove(string name)
{
    vector<int> choices ;
    string response ;
    cout << name << " choose cards to lay: " ;
    getline(cin, response) ;
    choices = parseChoices(response) ;
    while (choices.size() == 0) {
        cout << "Enter numbers seperated by commas: " ;
        getline(cin, response) ;
        choices = parseChoices(response) ;
    }
    return choices ;
}

void showPickUpMessage(string name)
{
    cout << name << " you must pick up!" ;
    wait_user() ;
}

void wait_user()
{
    cout << endl << endl << "Press ENTER to continue";
    cin.ignore( std::numeric_limits<streamsize>::max(), '\n' );
}

void showBadMove()
{
    cout << "You can't do that!" << endl ;
}

int requestFaceDownCard(string name) 
{
    string inp;
    int choice ;
    cout << name << " please choose a face down card: " ;
    getline(cin, inp) ;
    stringstream(inp) >> choice;
    return choice - 1 ;
}

void showFaceDownWin(const Card& card)
{
    cout << "WHEW you chose the " << card ;
    wait_user() ;
}

void showFaceDownFail(const Card& card)
{
    cout << "OH DEAR! You chose the " << card ;
    wait_user() ;
}

void showShithead(string name)
{
    cout << endl << "!!!!!!!! GAME OVER !!!!!!!!" << endl ;
    cout << name << " is a shithead!!" << endl ;
}

} // namespace console
