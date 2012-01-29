#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include "card.hpp"
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "game.hpp"
#include "shithead_exception.hpp"

using namespace std;

const string LowCardPlayer::description = "LowCardPlayer: Plays low cards.";

LowCardPlayer::LowCardPlayer(const string name) : ComputerPlayer(name) {}

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
    int first = 0;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand
        
        // assume my hand is sorted
        
        // find the first card I can lay and save its index
        int i;
        for (i = 0; i < hand_.size(); i++) {
            if (game::canLay(hand_[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of same rank from my hand to my choice
        bool found = false;
        for (i = 0; i < hand_.size(); i++) {
            if (hand_[i].equalsRank(hand_[first])) {
                choices.push_back(i);
                found = true;
            } else if (found) {
                break;
            }
        }
    } else {
        // play from faceUp
        
        // copy and sort my faceUp
        vector<Card> sorted = faceUp_;
        sort(sorted.begin(), sorted.end(), card::shCompare);
        
        // find the first card I can lay and save its index
        int i;
        for (i = 0; i < sorted.size(); i++) {
            if (game::canLay(sorted[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of this rank to my choice
        for (i = 0; i < faceUp_.size(); i++) {
            if (faceUp_[i].equalsRank(sorted[first])) {
                choices.push_back(i);
            }
        }
    }

    return choices;
}

int LowCardPlayer::askFaceDownMoveChoice() const
{
    return 0;
}
