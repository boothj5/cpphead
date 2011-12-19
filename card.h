#ifndef H_CARD
#define H_CARD

#include <iostream>
#include <string>

using namespace std ;

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE } ;

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS } ;

class Card {
    cardrank rank ;
    cardsuit suit ;
   
    string rankStr() ;
    string suitStr() ;
 
    public:
    Card(cardrank, cardsuit) ;
    string toString() ;
} ;    

#endif
