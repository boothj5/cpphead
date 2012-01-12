#include <algorithm>
#include <string>
#include "player.hpp"
#include "computer_player.hpp"
#include "player_helper.hpp"
#include "game.hpp"

using namespace std;

ComputerPlayer::ComputerPlayer(string name) : Player(name) 
{
    // do nothing
}

bool ComputerPlayer::isComputer() const
{
    return true;
}

pair<int, int> ComputerPlayer::askSwapChoice() const
{
    return pair<int, int>(0,0);
}

bool ComputerPlayer::askSwapCards() const
{
    return false;
}

vector<int> ComputerPlayer::askMoveChoice(const PlayerHelper helper) const
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
