#include <iostream>
#include <string>
#include <vector>
#include "cli_engine.hpp"
#include "shithead_exception.hpp"

using namespace std;

int main()
{
    CliEngine engine;
    try {
        engine.run();    
    } catch (ShitheadException *e) {
        cout << e->getMessage() << endl;
        return 1;
    }

    return 0;
}
    
