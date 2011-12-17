#include "card.h"

#include <string>

using namespace std ;

Card::Card()
{
    rank = TWO ;
    suit = DIAMONDS ;
}

Card::Card(cardrank rank, cardsuit suit)
{
    this->rank = rank ;
    this->suit = suit ;
}

string Card::rankStr()
{
    switch(rank) {
    case TWO:
        return "TWO" ;
    case THREE:
        return "THREE" ;
    case FOUR:
        return "FOUR" ;
    case FIVE:
        return "FIVE" ;
    case SIX:
        return "SIX" ;
    case SEVEN:
        return "SEVEN" ;
    case EIGHT:
        return "EIGHT" ;
    case NINE:
        return "NINE" ;
    case TEN:
        return "TEN" ;
    case JACK:
        return "JACK" ;
    case QUEEN:
        return "QUEEN" ;
    case KING:
        return "KING" ;
    case ACE:
        return "ACE" ;
    default:
        return "ERROR!!!" ;
    }
}

string Card::suitStr()
{
    switch(suit) {
    case HEARTS:
        return "HEARTS" ;
    case DIAMONDS:
        return "DIAMONDS" ;
    case CLUBS:
        return "CLUBS" ;
    case SPADES:
        return "SPADES" ;
    default:
        return "ERROR!!!!" ;
    }
}

string Card::toString()
{
    return rankStr() + " of " + suitStr() ;
}

