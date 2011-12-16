#include <iostream>
using namespace std;

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

int requestNumPlayers() {
    int result ;
    cout << "Please enter number of players: " ;
    cin >> result ;
    return result ;
}

int requestNumCards() {
    int result ;
    cout << "Please enter number of cards each: " ;
    cin >> result ;
    return result ;
}
        
int main()
{
    int numPlayers, numCardsEach ;
    clearScreen() ;
    showWelcomeMessage() ;
    numPlayers = requestNumPlayers() ;
    numCardsEach = requestNumCards() ;
    return 0 ;
}
    
