#ifndef H_CARD
#define H_CARD

#include <string>

using namespace std ;

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE } ;

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS } ;

class Card {
    cardrank rank_ ;
    cardsuit suit_ ;
   
    public:
    Card(cardrank, cardsuit) ;

    string toString() const ;
    cardrank rank() const ;
    bool special() const ;
    bool isInvisible() const ;
    bool equalsRank(Card card) ;

    static bool shCompare(Card c1, Card c2) ;   
    
    private:
    string rankStr() const ;
    string suitStr() const ;
} ;    

#endif
