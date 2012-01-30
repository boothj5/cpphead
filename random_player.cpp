#include <vector>
#include <string>
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "shithead_exception.hpp"
#include "card_choosers.hpp"

using namespace std;

const string RandomPlayer::description = "RandomPlayer: Plays random cards.";

RandomPlayer::RandomPlayer(const string name) : ComputerPlayer(name) {}

const pair<int, int> RandomPlayer::askSwapChoice() const
{
    throw ShitheadException("Random player asked to swap cards");
}

bool RandomPlayer::askSwapCards() const
{
    return false;
}

const vector<int> RandomPlayer::askMoveChoice(const PlayerHelper& helper) const
{
    vector<int> choices;

    if (hasCardsInHand())
        choose::randomFromSorted(hand(), helper, choices);
    else
        choose::randomFromUnsorted(faceUp(), helper, choices);

    return choices;
}

int RandomPlayer::askFaceDownMoveChoice() const
{
    return 0;
}
