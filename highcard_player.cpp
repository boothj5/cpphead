#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include "card.hpp"
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "game.hpp"

using namespace std;

const string HighCardPlayer::description = "HighCardPlayer: Plays high cards.";

HighCardPlayer::HighCardPlayer(const string name) : ComputerPlayer(name) {}

const pair<int, int> HighCardPlayer::askSwapChoice() const
{
    return pair<int, int>(0,0);
}

bool HighCardPlayer::askSwapCards() const
{
    return false;
}

const vector<int> HighCardPlayer::askMoveChoice(const PlayerHelper& helper) const
{
    int first = 0;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand, assume its sorted
 
        // go through it backwards,
        // find the first card I can lay and save its index
        int i;
        for (i = hand_.size()-1; i >= 0; i--) {
            if (Game::canLay(hand_[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of same rank from my hand to my choice
        bool found = false;
        for (i = hand_.size()-1; i >= 0; i--) {
            if (hand_[i].equalsRank(hand_[first])) {
                choices.push_back(i);
                found = true;
            } else if (found) {
                break;
            }
        }
    } else {
        // play from faceUp
        
        // copy and reverse sort my faceUp
        vector<Card> sorted = faceUp_;
        sort(sorted.begin(), sorted.end(), Card::shCompare);
        reverse(sorted.begin(), sorted.end());
        
        // find the first card I can lay and save its index
        int i;
        for (i = 0; i < sorted.size(); i++) {
            if (Game::canLay(sorted[i], helper.getPile())) {
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

int HighCardPlayer::askFaceDownMoveChoice() const
{
    return 0;
}
