#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <vector>
#include "card.hpp"
#include "player_helper.hpp"

class Player {
    protected:
    std::string name_;
    std::vector<Card *> hand_;
    std::vector<Card *> faceUp_;
    std::vector<Card *> faceDown_;
    
    public:
    Player(std::string name);
    ~Player();
    std::string name() const;
    std::vector<Card *> hand() const;
    std::vector<Card *> faceUp() const;
    std::vector<Card *> faceDown() const;
    void addToHand(Card *card);
    void addAllToHand(const std::vector<Card *>&);
    void addToFaceUp(Card *card);
    void addToFaceDown(Card *card);
    void sortHand();
    void swap(int, int);
    void removeFromHand(std::vector<int>); 
    void removeFromFaceUp(std::vector<int>); 
    void removeFromFaceDown(int); 
    bool hasCards() const;
    bool hasCardsInHand() const;
    bool hasCardsInFaceUp() const;

    static Player * createPlayer(std::string, char);

    virtual bool isComputer() const =0;
    virtual std::pair<int, int> askSwapChoice() const =0;
    virtual bool askSwapCards() const =0;
    virtual std::vector<int> askMoveChoice(const PlayerHelper) const =0;
    virtual int askFaceDownMoveChoice() const =0;
};

#endif
