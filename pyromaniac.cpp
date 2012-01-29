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

const string Pyromaniac::description = 
    "Pyromaniac: Lays burn if has one, then low cards.";

Pyromaniac::Pyromaniac(const string name) : ComputerPlayer(name) {}

const pair<int, int> Pyromaniac::askSwapChoice() const
{
    throw ShitheadException("Pyromaniac asked to swap cards");
}

bool Pyromaniac::askSwapCards() const
{
    return false;
}

const vector<int> Pyromaniac::askMoveChoice(const PlayerHelper& helper) const
{
    int i;
    int first = 0;
    bool burnFound = false;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand, assume hand is sorted

        // go through hand backwards

        // if i have a burn cards save their indexes
        for (i = hand().size()-1; i >= 0; i--) {
            if (hand()[i].isBurnCard()) {
                choices.push_back(i);
            } 
            else if (!hand()[i].special()) {
                break;
            }
        }

        // if i found some, return them as my choice
        if (choices.size() > 0) {
            return choices;
        } 
               
        // otherwise

        // find the first card I can lay and save its index
        for (i = 0; i < hand().size(); i++) {
            if (game::canLay(hand()[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of same rank from my hand to my choice
        bool found = false;
        for (i = 0; i < hand().size(); i++) {
            if (hand()[i].equalsRank(hand()[first])) {
                choices.push_back(i);
                found = true;
            } else if (found) {
                break;
            }
        }
    } else {
        // play from faceUp

        // if i have a burn cards save their indexes
        for (i = 0; i < faceUp().size(); i++) {
            if (faceUp()[i].isBurnCard()) {
                choices.push_back(i);
            }
        }

        // if i found some, return them as my choice
        if (choices.size() > 0) {
            return choices;
        } 
        // copy and sort my faceUp
        vector<Card> sorted = faceUp();
        sort(sorted.begin(), sorted.end(), card::shCompare);
        
        // find the first card I can lay and save its index
        for (i = 0; i < sorted.size(); i++) {
            if (game::canLay(sorted[i], helper.getPile())) {
                first = i;
                break;
            }
        }
        
        // add all cards of this rank to my choice
        for (i = 0; i < faceUp().size(); i++) {
            if (faceUp()[i].equalsRank(sorted[first])) {
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
