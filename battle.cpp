#include <iostream>
#include <iomanip>
#include <sstream>  
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>
#include "battle_engine.hpp"
#include "shithead_exception.hpp"

#define THRESHOLD 10000
#define NUM_CARDS 5

using namespace std;

int main(int argc, char *argv[])
{
    int numGames;
    stringstream(argv[1]) >> numGames;    

    BattleEngine engine(numGames);

    try {
        engine.run();
    } catch (ShitheadException e) {
        cout << e.getMessage() << endl;
        return 1;
    }

    return 0;
}
    
