#ifndef H_CARD
#define H_CARD

#include <string>
#include <vector>

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE };

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS };

class Card {
    cardrank rank_;
    cardsuit suit_;
   
    public:
    Card();
    Card(const cardrank, const cardsuit);

    const std::string toString() const;
    bool operator==(const Card&) const;
    bool operator!=(const Card&) const;
    cardrank rank() const;
    bool special() const;
    bool isInvisible() const;
    bool isBurnCard() const;
    bool isMissAGoCard() const;
    bool equalsRank(const Card& card) const;
};    

namespace card {

bool shCompare(const Card&, const Card&);   

bool allRanksEqual(const std::vector<Card>&);

} // namespace card

std::ostream& operator<<(std::ostream&, const Card&);

#endif
