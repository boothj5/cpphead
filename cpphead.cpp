#include <iostream>
#include <sstream>
#include <memory>
#include "engines.hpp"
#include "engine_factory.hpp"
#include "shithead_exception.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    int numGames;
    
    if (argc == 1) {
        numGames = 0;
    }
    else if (argc == 2) {
        stringstream(argv[1]) >> numGames;
    }
    else { 
        cout << "Usage: cpphead <num_games>" << endl;
        cout << "    Omit num_games for interactive mode." << endl;
        return 1;
    }

    auto_ptr<Engine> engine(enginefactory::createEngine(numGames));

    try {
        engine->run();    
    } catch (ShitheadException *e) {
        cout << e->getMessage() << endl;
        return 1;
    }

    return 0;
}
    
