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

#define THRESHOLD 5000

using namespace std;

bool scoreOrder(pair<string, int> player1, pair<string, int> player2)
{
    return player1.second < player2.second;
}

int main(int argc, char *argv[])
{
    clock_t start, end;
    double totalTime;
    float avgGameTime;
    
    typedef map<string, int> shMap_t;
    typedef vector<pair<string, int> > shVec_t;
    shMap_t shMap;
    
    int numGames;
    
    stringstream(argv[1]) >> numGames;

    int game;
    int stalemates = 0;

    shMap["SimplePlayer"] = 0;
    shMap["LowCardPlayer"] = 0;
    shMap["HighCardPlayer"] = 0;
    shMap["Pyromaniac"] = 0;
            
    start = clock();

    try {
        for (game = 0; game < numGames; game++) {
            vector<string> names;
            names.push_back("SimplePlayer");
            names.push_back("LowCardPlayer");
            names.push_back("HighCardPlayer");
            names.push_back("Pyromaniac");

            vector<char> types;
            types.push_back('s');
            types.push_back('l');
            types.push_back('a');
            types.push_back('p');

            Game *game = new Game(names, types, 3);
            game->deal();

            vector<Player *> players = game->players();
            int i;    
            for (i = 0 ; i < players.size() ; i++)
                player_swap(players[i], *game);

            game->firstMove();

            int moves = 0;        
    
            while (game->canContinue() && moves < THRESHOLD) {
                const Player *currentPlayer = game->currentPlayer();
                if (game->playingFromFaceDown())
                    player_facedown_move(currentPlayer, *game);
                else
                    player_move(currentPlayer, *game);
                
                moves++;
            }

            if (moves == THRESHOLD) {
                stalemates++;
            }
            else {
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
        cout << "Total time : " << minutes << " minutes, " << seconds << " seconds" << endl;
    } else if (totalTime >= 1000) {
        int seconds = totalTime / 1000;
        cout << "Total time : " << seconds << " seconds" << endl;
    } else {
        cout << "Total time : " << totalTime << " milliseconds" << endl;
    }

    cout << "Average game: " << avgGameTime << " milliseconds" << endl;

    float stalematePercent = ((double)stalemates / (double)numGames) * 100.0;
    cout << "Stalemates: " << stalemates << ", " << stalematePercent << "%" << endl;
    cout << endl;

    cout << "SCORES" << endl;

    shVec_t shVec;
    copy(shMap.begin(), shMap.end(), back_inserter(shVec));
    sort(shVec.begin(), shVec.end(), scoreOrder);

    cout << setw(20) << left << "Name:";
    cout << setw(10) << "Shithead";
    cout << setw(10) << "Lose rate" << endl;
    cout << setfill('-') << setw(40) << "-" << endl;
    cout << setfill(' ');

    shVec_t::const_iterator iter;
    for (iter = shVec.begin(); iter!=shVec.end(); iter++) {
        float percentSh = ((double)iter->second / (double)numGames) * 100.0;
        cout << setw(20) << left << iter->first;
        cout << setw(10) << iter->second;
        cout << setprecision(2) << percentSh << "%" << endl;
    }
    
    cout << endl;

    return 0;
}
    
