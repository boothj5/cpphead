#include "card.hpp"

#include <string>
#include "shithead_exception.hpp"

using namespace std ;

Card::Card()
    : rank_(ACE),
      suit_(SPADES)
{}

Card::Card(const cardrank rank, const cardsuit suit) 
    : rank_(rank), 
      suit_(suit) 
{}

bool Card::operator==(const Card& other) const
{
    return rank_ == other.rank_ && suit_ == other.suit_;
}

bool Card::operator!=(const Card& other) const
{
    return rank_ != other.rank_ || suit_ != other.suit_;
}

cardrank Card::rank() const
{
    return rank_;
}

bool Card::special() const 
{ 
    return rank_ == TWO || rank_ == SEVEN || rank_ == TEN; 
}

bool Card::isInvisible() const
{
    return rank_ == SEVEN;
}

bool Card::isBurnCard() const
{
    return rank_ == TEN;
}

bool Card::isMissAGoCard() const
{
    return rank_ == EIGHT;
}

bool Card::equalsRank(const Card& card)  const
{ 
    return rank_ == card.rank_; 
}

const string Card::toString() const 
{ 
    string rankStr;
    switch(rank_) {
    case TWO:   
        rankStr = "TWO";
        break;
    case THREE: 
        rankStr = "THREE";
        break;
    case FOUR:  
        rankStr = "FOUR";
        break;
    case FIVE:  
        rankStr = "FIVE";
        break;
    case SIX:   
        rankStr = "SIX";
        break;
    case SEVEN: 
        rankStr = "SEVEN";
        break;
    case EIGHT: 
        rankStr = "EIGHT";
        break;
    case NINE:  
        rankStr = "NINE";
        break;
    case TEN:   
        rankStr = "TEN";
        break;
    case JACK:  
        rankStr = "JACK";
        break;
    case QUEEN: 
        rankStr = "QUEEN";
        break;
    case KING:  
        rankStr = "KING";
        break;
    case ACE:   
        rankStr = "ACE";
        break;
    default:    
        throw ShitheadException("Card has invalid rank");
    }
    
    string suitStr;
    switch(suit_) {
    case HEARTS:   
        suitStr = "HEARTS";
        break;
    case DIAMONDS: 
        suitStr = "DIAMONDS";
        break;
    case CLUBS:    
        suitStr = "CLUBS";
        break;
    case SPADES:   
        suitStr = "SPADES";
        break;
    default:       
        throw ShitheadException("Card has invalid suit");
    }

    return rankStr + " of " + suitStr; 
}

namespace card {

bool shCompare(const Card& c1, const Card& c2)
{   
    if (c1.special() && c2.special())
        return c1.rank() < c2.rank();
    else if (c1.special() && !c2.special())
        return false;
    else if (c2.special())
        return true;
    else
        return c1.rank() < c2.rank();
}

bool allRanksEqual(const vector<Card>& cards)
{
    const Card first = cards[0];

    int i;
    for (i = 1 ; i < cards.size() ; i++)
        if (!cards[i].equalsRank(first))
            return false;
    return true;
}

} // namespace card

ostream& operator<<(ostream& strm, const Card& card)
{
    return strm << card.toString();
}

