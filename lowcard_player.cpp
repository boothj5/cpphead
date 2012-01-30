#include <vector>
#include <string>
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "shithead_exception.hpp"
#include "card_choosers.hpp"

using namespace std;

const string LowCardPlayer::description = "LowCardPlayer: Plays low cards.";

LowCardPlayer::LowCardPlayer(const string name) 
    : ComputerPlayer(name) 
{}

const pair<int, int> LowCardPlayer::askSwapChoice() const
{
    throw ShitheadException("Cannot ask LowCardPlayer for swap choice.");
}

bool LowCardPlayer::askSwapCards() const
{
    return false;
}

const vector<int> LowCardPlayer::askMoveChoice(const PlayerHelper& helper) const
{
    vector<int> choices;

    if (hasCardsInHand())
        choose::lowestFromSorted(hand(), helper, choices);
    else
        choose::lowestFromUnsorted(faceUp(), helper, choices);

    return choices;
}

int LowCardPlayer::askFaceDownMoveChoice() const
{
    return 0;
}
