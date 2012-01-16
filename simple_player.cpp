#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include "card.hpp"
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "game.hpp"
#include "util.hpp"

using namespace std;

const string SimplePlayer::description = "SimplePlayer: Plays random cards.";

SimplePlayer::SimplePlayer(const string name) : ComputerPlayer(name) {}

const pair<int, int> SimplePlayer::askSwapChoice() const
{
    return pair<int, int>(0,0);
}

bool SimplePlayer::askSwapCards() const
{
    return false;
}

const vector<int> SimplePlayer::askMoveChoice(const PlayerHelper& helper) const
{
    int first = 0;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand
        
        // unsort it
        vector<Card> unsorted = hand_;
        util::shuffle(unsorted);

        // find the first card I can lay and save its index
        int i;
        for (i = 0; i < unsorted.size(); i++) {
            if (Game::canLay(unsorted[i], helper.getPile())) {
                first = i;
                break;
            }
        }

        // add all cards of this rank from my hand to my choice
        for (i = 0; i < hand_.size(); i++) {
            if (hand_[i].equalsRank(unsorted[first])) {
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
