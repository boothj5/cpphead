#include <iostream>
#include <iomanip>
#include <vector>
#include "engines.hpp"
#include "game.hpp"
#include "player_interaction.hpp"
#include "util.hpp"

using namespace std;

BattleEngine::BattleEngine(const int numGames)
    : numGames_(numGames),
      stalemates_(0)
{
    // initialise player list
    pVec_.push_back(make_pair('s', "SimplePlayer"));
    pVec_.push_back(make_pair('l', "LowCardPlayer"));
    pVec_.push_back(make_pair('p', "Pyromaniac"));

    // initialise shithead map
    vector<typeName_t>::const_iterator tnIter;
    for (tnIter = pVec_.begin(); tnIter!=pVec_.end(); tnIter++) {
        shMap_[tnIter->second] = 0;
    }
}

void BattleEngine::run()
{
    clock_t start_ = clock();
    int ngame;
    for (ngame = 0; ngame < numGames_; ngame++) {
        // make sure players in different order for each game
        util::shuffle<typeName_t>(pVec_);

        // set up player names and types for game creation
        vector<string> names;
        vector<char> types;
        vector<typeName_t>::const_iterator iter;
        for (iter = pVec_.begin(); iter!=pVec_.end(); iter++) {
            types.push_back(iter->first);
            names.push_back(iter->second);
        }
    
        Game *game = new Game(names, types, NUM_CARDS);
    
        game->deal();
    
        // ask players to swap
        vector<Player *> players = game->players();
        int i;
        for (i = 0 ; i < players.size() ; i++)
            player_swap(players[i], *game);
        
        game->firstMove();
    
        // main game play, count moves for stalemates
        int moves = 0;
        while (game->canContinue() && moves < THRESHOLD) {
            const Player *currentPlayer = game->currentPlayer();
            if (game->playingFromFaceDown())
                player_facedown_move(currentPlayer, *game);
            else
                player_move(currentPlayer, *game);
            
            moves++;
        }

        // log stalemates if game didn't complete
        if (moves == THRESHOLD) {
            stalemates_++;
        }
        else { // add to shithead count for loser
            string loser = game->getCppHead();
            ++shMap_[loser];
        }
    
        delete game;
    }

    clock_t end = clock();

    double totalTime = (end - start_) / (CLOCKS_PER_SEC / 1000);
    float avgGameTime = totalTime / numGames_;

    cout << endl << "SUMMARY" << endl;
    cout << "Total games : " << numGames_ << endl;

    if (totalTime >= 60000) {
        int minutes = totalTime / 60000;
        int seconds = (totalTime - (minutes * 60000)) / 1000;
        cout << "Total time : ";
        cout << minutes << " minutes, ";
        cout << seconds << " seconds" << endl;
    } else if (totalTime >= 1000) {
        int seconds = totalTime / 1000;
        cout << "Total time : "; 
        cout << seconds << " seconds" << endl;
    } else {
        cout << "Total time : ";
        cout << totalTime << " milliseconds" << endl;
    }

    cout << "Average game: "; 
    cout << avgGameTime << " milliseconds" << endl;

    float stalematePercent = ((double)stalemates_ / (double)numGames_) * 100.0;

    cout << "Stalemates: ";
    cout << stalemates_ << ", " << stalematePercent << "%" << endl;
    cout << endl;

    cout << "SCORES" << endl;

    shVec_t shVec;
    copy(shMap_.begin(), shMap_.end(), back_inserter(shVec));
    sort(shVec.begin(), shVec.end(), scoreOrder);

    cout << left;
    cout << setw(20) << "Name:";
    cout << setw(10) << "Shithead";
    cout << setw(10) << "Lose rate";
    cout << endl;
    cout << setw(40) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    shVec_t::const_iterator iter;
    for (iter = shVec.begin(); iter!=shVec.end(); iter++) {
        float percentSh = ((double)iter->second / (double)numGames_) * 100.0;
        cout << setw(20) << iter->first;
        cout << setw(10) << iter->second;
        cout << setprecision(2);
        cout << percentSh << "%" << endl;
    }

    cout << endl;
}

bool BattleEngine::scoreOrder(pair<string, int> player1, pair<string, int> player2)
{
    return player1.second < player2.second;
}

