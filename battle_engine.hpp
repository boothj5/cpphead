#ifndef H_BATTLEENGINE
#define H_BATTLEENGINE

#include <string>
#include <vector>
#include <map>

typedef std::pair<char, std::string> typeName_t;
typedef std::map<std::string, int> shMap_t;
typedef std::vector<std::pair<std::string, int> > shVec_t;

class BattleEngine {
    private:
    static const int NUM_CARDS = 3;
    static const int THRESHOLD = 10000;
    int numGames_;
    int stalemates_;
    std::vector<typeName_t> pVec_;
    shMap_t shMap_;

    public:
    BattleEngine(const int);
    
    void run();

    private:
    static bool scoreOrder(std::pair<std::string, int>, 
        std::pair<std::string, int>);
};    

#endif
