#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include "card.hpp"
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "game.hpp"

using namespace std;

string LowCardPlayer::description = "LowCardPlayer: Plays low cards.";

LowCardPlayer::LowCardPlayer(string name) : ComputerPlayer(name) 
{
    // do nothing
}

pair<int, int> LowCardPlayer::askSwapChoice() const
{
    return pair<int, int>(0,0);
}

bool LowCardPlayer::askSwapCards() const
{
    return false;
}

vector<int> LowCardPlayer::askMoveChoice(const PlayerHelper helper) const
{
    int first = 0;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand
        
        // copy and sort my hand
        vector<Card> sorted = hand_;
        sort(sorted.begin(), sorted.end(), Card::shCompare);
        
        // find the first card I can lay and save its index
        int i;
        for (i = 0; i < sorted.size(); i++) {
            if (Game::canLay(sorted[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of same rank from my hand to my choice
        for (i = 0; i < hand_.size(); i++) {
            if (hand_[i].equalsRank(sorted[first])) {
                choices.push_back(i);
            }
        }
    } else {
        // play from faceUp
        
        // copy and sort my faceUp
        vector<Card> sorted = faceUp_;
        sort(sorted.begin(), sorted.end(), Card::shCompare);
        
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

int LowCardPlayer::askFaceDownMoveChoice() const
{
    return 0;
}
