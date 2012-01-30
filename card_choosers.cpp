#include <vector>
#include <algorithm>
#include "card_choosers.hpp"
#include "card.hpp"
#include "game.hpp"
#include "player_helper.hpp"
#include "util.hpp"
#include "shithead_exception.hpp"

using namespace std;

namespace choose {

// Helper functions -----------------------------------------------------------

// go through cards, return index of first playable card found
static int firstPlayableFrom(const vector<Card>& cards, 
    const PlayerHelper& helper)
{
    int i;
    for (i = 0; i < cards.size(); i++)
        if (game::canLay(cards[i], helper.getPile()))
            return i;

    throw ShitheadException("Computer could not find a card to play.");
}

// go through cards backwards, return index of first playable card found
static int lastPlayableFrom(const vector<Card>& cards, 
    const PlayerHelper& helper)
{
    int i;
    for (i = cards.size()-1; i >= 0; i--)
        if (game::canLay(cards[i], helper.getPile()))
            return i;

    throw ShitheadException("Computer could not find a card to play.");
}

// add cards of same rank to choice, assuming cards are sorted
static void addSimilarFromSorted(const vector<Card>& cards, 
    const Card& first, vector<int>& choices)
{
    int i;
    bool found = false;
    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(first)) {
            choices.push_back(i);
            found = true;
        } else if (found) {
            break;
        }
    }
}

// add cards of same rank to choice, assuming cards are not sorted
static void addSimilarFromUnsorted(const vector<Card>& cards, 
    const Card& first, vector<int>& choices)
{
    int i;
    for (i = 0; i < cards.size(); i++) {
        if (cards[i].equalsRank(first)) {
            choices.push_back(i);
        }
    }
}

// Functions callable by players ----------------------------------------------

// Choose all lowest cards of same rank, assumes the cards are already sorted
void lowestFromSorted(const vector<Card>& cards, const PlayerHelper& helper, 
    vector<int>& choices)
{
    int first = choose::firstPlayableFrom(cards, helper);
    choose::addSimilarFromSorted(cards, cards[first], choices);
}

// Choose all lowest cards of same rank, assumes the cards are not sorted
void lowestFromUnsorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    vector<Card> sorted = cards;
    sort(sorted.begin(), sorted.end(), card::shCompare);

    int first = choose::firstPlayableFrom(sorted, helper);
    choose::addSimilarFromUnsorted(cards, sorted[first], choices);
}

// Choose all highest cards of same rank, assumes the cards are already sorted
void highestFromSorted(const vector<Card>& cards, const PlayerHelper& helper, 
    vector<int>& choices)
{
    int first = choose::lastPlayableFrom(cards, helper);

    int i;
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

// Choose all highest cards of same rank, assumes the cards are not sorted
void highestFromUnsorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    vector<Card> sorted = cards;
    sort(sorted.begin(), sorted.end(), card::shCompare);

    int first = choose::lastPlayableFrom(sorted, helper);
    choose::addSimilarFromUnsorted(cards, sorted[first], choices);    
}

// Choose randomly cards of same rank, assumes the cards are sorted
void randomFromSorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    int i;
    
    vector<int> possibleChoices;
    for (i = 0; i < cards.size(); i++) {
        possibleChoices.push_back(i);
    }

    util::shuffle(possibleChoices);

    int first = 0;
    for (i = 0; i < possibleChoices.size(); i++) {
        if (game::canLay(cards[possibleChoices[i]], helper.getPile())) {
            first = possibleChoices[i];
            break;
        }
    }

    choose::addSimilarFromSorted(cards, cards[first], choices);
}

// Choose randomly cards of same rank, assumes the cards are not sorted
void randomFromUnsorted(const vector<Card>& cards, const PlayerHelper& helper,
    vector<int>& choices)
{
    int first = choose::firstPlayableFrom(cards, helper);
    choose::addSimilarFromUnsorted(cards, cards[first], choices);
}

// Chooses burn cards first, then low cards, assumes cards are sorted
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

    int first = choose::firstPlayableFrom(cards, helper);
    choose::addSimilarFromSorted(cards, cards[first], choices);
}

// Chooses burn cards first, then low cards, assumes cards are not sorted
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

    int first = choose::firstPlayableFrom(sorted, helper);
    choose::addSimilarFromUnsorted(cards, sorted[first], choices);
}

} // namespace choose
