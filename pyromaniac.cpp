#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include "card.hpp"
#include "computer_players.hpp"
#include "player_helper.hpp"
#include "game.hpp"

using namespace std;

const string Pyromaniac::description = 
    "Pyromaniac: Lays burn if has one, then low cards.";

Pyromaniac::Pyromaniac(const string name) : ComputerPlayer(name) {}

const pair<int, int> Pyromaniac::askSwapChoice() const
{
    return pair<int, int>(0,0);
}

bool Pyromaniac::askSwapCards() const
{
    return false;
}

const vector<int> Pyromaniac::askMoveChoice(const PlayerHelper& helper) const
{
    int i;
    int first = 0;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand

        // if i have a burn cards save their indexes
        for (i = 0; i < hand_.size(); i++) {
            if (hand_[i].isBurnCard()) {
                choices.push_back(i);
            }
        }

        // if i found some, return them as my choice
        if (choices.size() > 0) {
            return choices;
        } 
               
        // otherwise

        // copy and sort my hand
        vector<Card> sorted = hand_;
        sort(sorted.begin(), sorted.end(), Card::shCompare);
        
        // find the first card I can lay and save its index
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

        // if i have a burn cards save their indexes
        for (i = 0; i < faceUp_.size(); i++) {
            if (faceUp_[i].isBurnCard()) {
                choices.push_back(i);
            }
        }

        // if i found some, return them as my choice
        if (choices.size() > 0) {
            return choices;
        } 
        // copy and sort my faceUp
        vector<Card> sorted = faceUp_;
        sort(sorted.begin(), sorted.end(), Card::shCompare);
        
        // find the first card I can lay and save its index
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

int Pyromaniac::askFaceDownMoveChoice() const
{
    return 0;
}
