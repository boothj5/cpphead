#include <vector>
#include <algorithm>
#include "card_choosers.hpp"
#include "card.hpp"
#include "game.hpp"
#include "player_helper.hpp"
#include "util.hpp"

using namespace std;

namespace choose {

void lowestFromSorted(const vector<Card>& cards, const PlayerHelper& helper, 
    vector<int>& choices)
{
    int i;
    int first = 0;
    for (i = 0; i < cards.size(); i++) {
        if (game::canLay(cards[i], helper.getPile())) {
            first = i;
            break;
        }
    }

    bool found = false;
    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(cards[first])) {
            choices.push_back(i);
            found = true;
        } else if (found) {
            break;
        }
    }
}

void lowestFromUnsorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    int i;
    int first = 0;
    
    vector<Card> sorted = cards;
    sort(sorted.begin(), sorted.end(), card::shCompare);

    for (i = 0; i < sorted.size(); i++) {
        if (game::canLay(sorted[i], helper.getPile())) {
            first = i;
            break;
        }
    }

    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(sorted[first])) {
            choices.push_back(i);
        }
    }
}

void highestFromSorted(const vector<Card>& cards, const PlayerHelper& helper, 
    vector<int>& choices)
{
    int i;
    int first = 0;

    for (i = cards.size()-1; i >= 0; i--) {
        if (game::canLay(cards[i], helper.getPile())) {
            first = i;
            break;
        }
    }
    
    bool found = false;
    for (i = cards.size()-1; i >= 0; i--) {
        if (cards[i].equalsRank(cards[first])) {
            choices.push_back(i);
            found = true;
        } else if (found) {
            break;
        }
    }
}

void highestFromUnsorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    int i;
    int first = 0;
    
    vector<Card> sorted = cards;
    sort(sorted.begin(), sorted.end(), card::shCompare);
    reverse(sorted.begin(), sorted.end());

    for (i = 0; i < sorted.size(); i++) {
        if (game::canLay(sorted[i], helper.getPile())) {
            first = i;
            break;
        }
    }

    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(sorted[first])) {
            choices.push_back(i);
        }
    }
}

void randomFromSorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    int i;
    int first = 0;
    
    vector<int> possibleChoices;
    for (i = 0; i < cards.size(); i++) {
        possibleChoices.push_back(i);
    }

    util::shuffle(possibleChoices);

    for (i = 0; i < possibleChoices.size(); i++) {
        if (game::canLay(cards[possibleChoices[i]], helper.getPile())) {
            first = possibleChoices[i];
            break;
        }
    }

    bool found = false;
    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(cards[first])) {
            choices.push_back(i);
            found = true;
        } else if (found) {
            break;
        }
    }
}

void randomFromUnsorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    int i;
    int first = 0;

    for (i = 0; i < cards.size(); i++) {
        if (game::canLay(cards[i], helper.getPile())) {
            first = i;
            break;
        }
    }

    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(cards[first])) {
            choices.push_back(i);
        }
    }
}

void burnThenLowestFromSorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    int i;
    for (i = cards.size()-1; i >= 0; i--) {
        if (cards[i].isBurnCard()) {
            choices.push_back(i);
        }
        else if (!cards[i].special()) {
            break;
        }
    }

    if (choices.size() > 0) {
        return;
    }

    int first = 0;
    for (i = 0; i < cards.size(); i++) {
        if (game::canLay(cards[i], helper.getPile())) {
            first = i;
            break;
        }
    }

    bool found = false;
    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(cards[first])) {
            choices.push_back(i);
            found = true;
        } else if (found) {
            break;
        }
    }
}

void burnThenLowestFromUnsorted(const vector<Card>& cards, 
    const PlayerHelper& helper, vector<int>& choices)
{
    int i;
    for (i = 0; i < cards.size(); i++) {
        if (cards[i].isBurnCard()) {
            choices.push_back(i);
        }
    }

    if (choices.size() > 0) {
        return;
    }

    vector<Card> sorted = cards;
    sort(sorted.begin(), sorted.end(), card::shCompare);

    int first = 0;
    for (i = 0; i < sorted.size(); i++) {
        if (game::canLay(sorted[i], helper.getPile())) {
            first = i;
            break;
        }
    }

    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(sorted[first])) {
            choices.push_back(i);
        }
    }
}

} // namespace choose
