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
    explicit BattleEngine(const int);
    ~BattleEngine();

    void run();

    private:
    void showStats(const clock_t, const clock_t) const;
    void showSummary(const clock_t, const clock_t) const;
    void showScores() const;
};

class CliEngine: public Engine {
    public:
    CliEngine();
    ~CliEngine();
    
    void run();
};    

namespace engine {

bool scoreOrder(const std::pair<std::string, int>&, 
    const std::pair<std::string, int>&);

} // namespace engine

#endif
