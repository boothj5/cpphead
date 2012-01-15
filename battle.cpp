#include <iostream>
#include <sstream>  
#include <vector>
#include <string>
#include <map>
#include "player_factory.hpp"
#include "player.hpp"
#include "game.hpp"
#include "player_interaction.hpp"
#include "shithead_exception.hpp"

#define THRESHOLD 5000

using namespace std;

int main(int argc, char *argv[])
{
    typedef map<string, int> shMap_t;
    shMap_t shMap;
    
    int numGames;
    
    stringstream(argv[1]) >> numGames;

    int game;
    int stalemates = 0;

    shMap["SimplePlayer"] = 0;
    shMap["LowCardPlayer"] = 0;
    shMap["HighCardPlayer"] = 0;
    shMap["Pyromaniac"] = 0;
            
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

    shMap_t::const_iterator iter;
    for (iter = shMap.begin(); iter!=shMap.end(); iter++) {
        string name = iter->first;
        cout << name << ": " << shMap[name] << endl;
    }

    cout << endl << "Stalemates: " << stalemates << endl;

    return 0;
}
    
