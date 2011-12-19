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
   
    string rankStr() const ;
    string suitStr() const ;
 
    public:
    Card(cardrank, cardsuit) ;

    string toString() const { return rankStr() + " of " + suitStr() ; }
    bool special() const { return rank == TWO || rank == SEVEN || rank == TEN ; }
    bool equalsRank(Card card) { return this->rank == card.rank ; }

    static bool shCompare(Card c1, Card c2) ;   
} ;    

#endif
