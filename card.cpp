#include "card.hpp"

#include <string>

using namespace std ;

Card::Card(cardrank rank, cardsuit suit)
{
    rank_ = rank ;
    suit_ = suit ;
}

string Card::toString() const 
{ 
    return rankStr() + " of " + suitStr() ; 
}

bool Card::operator==(const Card& other) const
{
    return rank_ == other.rank_ && suit_ == other.suit_ ;
}

bool Card::operator!=(const Card& other) const
{
    return rank_ != other.rank_ || suit_ != other.suit_ ;
}

ostream& operator<<(ostream& strm, const Card& card)
{
    return strm << card.toString();
}

cardrank Card::rank() const
{
    return rank_ ;
}

bool Card::special() const 
{ 
    return rank_ == TWO || rank_ == SEVEN || rank_ == TEN ; 
}

bool Card::isInvisible() const
{
    return rank_ == SEVEN ;
}

bool Card::isBurnCard() const
{
    return rank_ == TEN ;
}

bool Card::isMissAGoCard() const
{
    return rank_ == EIGHT ;
}

bool Card::equalsRank(Card card)  const
{ 
    return rank_ == card.rank_ ; 
}

string Card::rankStr() const
{
    switch(rank_) {
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

string Card::suitStr() const
{
    switch(suit_) {
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

bool Card::shCompare(Card c1, Card c2)
{   
    if (c1.special() && c2.special())
        return false ;
    else if (c1.special() && !c2.special())
        return false ;
    else if (c2.special())
        return true ;
    else
        return c1.rank_ < c2.rank_ ;
}

bool Card::allRanksEqual(const vector<Card>& cards)
{
    Card first = cards[0] ;

    int i ;
    for (i = 0 ; i < cards.size() ; i++)
        if (!cards[i].equalsRank(first))
            return false ;
    return true ;
}

