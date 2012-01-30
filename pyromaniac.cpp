#include <vector>
#include <string>
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "shithead_exception.hpp"
#include "card_choosers.hpp"

using namespace std;

const string Pyromaniac::description = 
    "Pyromaniac: Lays burn if has one, then low cards.";

Pyromaniac::Pyromaniac(const string name) : ComputerPlayer(name) {}

const pair<int, int> Pyromaniac::askSwapChoice() const
{
    throw ShitheadException("Pyromaniac asked to swap cards");
}

bool Pyromaniac::askSwapCards() const
{
    return false;
}

const vector<int> Pyromaniac::askMoveChoice(const PlayerHelper& helper) const
{
    vector<int> choices;
   
    if (hasCardsInHand())
        choose::burnThenLowestFromSorted(hand(), helper, choices);
    else
        choose::burnThenLowestFromUnsorted(faceUp(), helper, choices);

    return choices;
}

int Pyromaniac::askFaceDownMoveChoice() const
{
    return 0;
}
