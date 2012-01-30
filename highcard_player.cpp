#include <vector>
#include <string>
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "shithead_exception.hpp"
#include "card_choosers.hpp"

using namespace std;

const string HighCardPlayer::description = "HighCardPlayer: Plays high cards.";

HighCardPlayer::HighCardPlayer(const string name) : ComputerPlayer(name) {}

const pair<int, int> HighCardPlayer::askSwapChoice() const
{
    throw ShitheadException("Cannot ask HighCardPlayer for swap choice");
}

bool HighCardPlayer::askSwapCards() const
{
    return false;
}

const vector<int> HighCardPlayer::askMoveChoice(const PlayerHelper& helper) const
{
    vector<int> choices;

    if (hasCardsInHand())
        choose::highestFromSorted(hand(), helper, choices);
    else
        choose::highestFromUnsorted(faceUp(), helper, choices);

    return choices;
}

int HighCardPlayer::askFaceDownMoveChoice() const
{
    return 0;
}
