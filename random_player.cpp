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
#include "shithead_exception.hpp"

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
    int first = 0;
    vector<int> choices;
    if (hasCardsInHand()) {
        // play from hand
        
        // shuffle posisble indexes
        vector<int> possibleChoices;
        int i;
        for (i = 0; i < hand_.size(); i++) {
            possibleChoices.push_back(i);
        }
        util::shuffle(possibleChoices);

        // find the first card I can lay and save its index
        for (i = 0; i < possibleChoices.size(); i++) {
            if (Game::canLay(hand_[possibleChoices[i]], helper.getPile())) {
                first = possibleChoices[i];
                break;
            }
        }

        // add all cards of this rank from my hand to my choice
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

int RandomPlayer::askFaceDownMoveChoice() const
{
    return 0;
}
