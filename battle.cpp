#include <iostream>
#include <iomanip>
#include <sstream>  
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>
#include "player_factory.hpp"
#include "player.hpp"
#include "game.hpp"
#include "player_interaction.hpp"
#include "shithead_exception.hpp"
#include "util.hpp"

#define THRESHOLD 10000
#define NUM_CARDS 5

using namespace std;

bool scoreOrder(pair<string, int> player1, pair<string, int> player2)
{
    return player1.second < player2.second;
}

int main(int argc, char *argv[])
{
    typedef pair<char, string> typeName_t;
    typedef map<string, int> shMap_t;
    typedef vector<pair<string, int> > shVec_t;

    clock_t start, end;
    double totalTime;
    float avgGameTime;
    int numGames, game;
    int stalemates = 0;
    shMap_t shMap;
    
    stringstream(argv[1]) >> numGames;

    // initialise player list
    vector<typeName_t> pVec;
    pVec.push_back(make_pair('s', "SimplePlayer"));
    pVec.push_back(make_pair('l', "LowCardPlayer"));
    pVec.push_back(make_pair('p', "Pyromaniac"));

    // initialise shithead map
    vector<typeName_t>::const_iterator tnIter;
    for (tnIter = pVec.begin(); tnIter!=pVec.end(); tnIter++) {
        shMap[tnIter->second] = 0;
    }
            
    start = clock();

    try {
        for (game = 0; game < numGames; game++) {
            int i;           
 
            // make sure players in different order for each game
            util::shuffle<typeName_t>(pVec);

            // set up player names and types for game creation
            vector<string> names;
            vector<char> types;
            vector<typeName_t>::const_iterator iter;
            for (iter = pVec.begin(); iter!=pVec.end(); iter++) {
                types.push_back(iter->first);
                names.push_back(iter->second);
            }

            Game *game = new Game(names, types, NUM_CARDS);
            
            game->deal();

            // ask players to swap
            vector<Player *> players = game->players();
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
                stalemates++;
            }
            else { // add to shithead count for loser
                string loser = game->getCppHead();
                ++shMap[loser];       
            }
            delete game;
        }
    } catch (ShitheadException e) {
        cout << e.getMessage() << endl;
        return 1;
    }

    end = clock();

    totalTime = (end - start) / (CLOCKS_PER_SEC / 1000);
    avgGameTime = totalTime / numGames;

    cout << endl << "SUMMARY" << endl;
    cout << "Total games : " << numGames << endl;
    
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

    float stalematePercent = ((double)stalemates / (double)numGames) * 100.0;

    cout << "Stalemates: ";
    cout << stalemates << ", " << stalematePercent << "%" << endl;
    cout << endl;

    cout << "SCORES" << endl;

    // copy the shMap to a vector and sort it by score
    shVec_t shVec;
    copy(shMap.begin(), shMap.end(), back_inserter(shVec));
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
        float percentSh = ((double)iter->second / (double)numGames) * 100.0;
        cout << setw(20) << iter->first;
        cout << setw(10) << iter->second;
        cout << setprecision(2);
        cout << percentSh << "%" << endl;
    }
    
    cout << endl;

    return 0;
}
    
