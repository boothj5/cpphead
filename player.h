#ifndef H_PLAYER
#define H_PLAYER

#include <string>

using namespace std ;

class Player {
    string name ;
    
    public:
    Player() ;
    Player(string) ;
    string getName(void) ;
} ;

#endif
