#ifndef H_ENGINES
#define H_ENGINES

#include <string>
#include <vector>
#include <map>

typedef std::pair<char, std::string> typeName_t;
typedef std::map<std::string, int> shMap_t;
typedef std::vector<std::pair<std::string, int> > shVec_t;

class Engine {
    public:
    Engine() {};
    virtual ~Engine() {};
    virtual void run() =0;
};

class BattleEngine: public Engine {
    private:
    static const int NUM_CARDS = 3;
    static const int THRESHOLD = 10000;
    int numGames_;
    int stalemates_;
    std::vector<typeName_t> pVec_;
    shMap_t shMap_;

    public:
    BattleEngine(const int);
    ~BattleEngine();

    void run();

    private:
    void summary(const clock_t, const clock_t) const;
    static bool scoreOrder(std::pair<std::string, int>,
        std::pair<std::string, int>);
};

class CliEngine: public Engine {
    public:
    CliEngine();
    ~CliEngine();
    
    void run();
};    

#endif
