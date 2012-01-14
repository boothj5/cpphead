#include <algorithm>
#include <string>
#include "computer_player.hpp"
#include "simple_player.hpp"
#include "player_helper.hpp"
#include "game.hpp"

using namespace std;

SimplePlayer::SimplePlayer(string name) : ComputerPlayer(name) 
{
    // do nothing
}

pair<int, int> SimplePlayer::askSwapChoice() const
{
    return pair<int, int>(0,0);
}

bool SimplePlayer::askSwapCards() const
{
    return false;
}

vector<int> SimplePlayer::askMoveChoice(const PlayerHelper helper) const
{
    int first = 0;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand
        
        // find the first card I can lay and save the rank
        int i;
        for (i = 0; i < hand_.size(); i++) {
            if (Game::canLay(hand_[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of this rank to my choice
        for (i = 0; i < hand_.size(); i++) {
            if (hand_[i].equalsRank(hand_[first])) {
                choices.push_back(i);
            }
        }
    } else {
        // play from faceUp
        
        // find the first card I can lay and save the rank
        int i;
        for (i = 0; i < faceUp_.size(); i++) {
            if (Game::canLay(faceUp_[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of this rank to my choice
        for (i = 0; i < faceUp_.size(); i++) {
            if (faceUp_[i].equalsRank(faceUp_[first])) {
                choices.push_back(i);
            }
        }
    }

    return choices;
}

int SimplePlayer::askFaceDownMoveChoice() const
{
    return 0;
}
