#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <vector>
#include "card.hpp"
#include "player_helper.hpp"

class Player {
    protected:
    const std::string name_;
    std::vector<Card> hand_;
    std::vector<Card> faceUp_;
    std::vector<Card> faceDown_;
    
    public:
    explicit Player(const std::string name);
    virtual ~Player();
    const std::string name() const;
    const std::vector<Card> hand() const;
    const std::vector<Card> faceUp() const;
    const std::vector<Card> faceDown() const;
    void addToHand(const Card& card);
    void addAllToHand(const std::vector<Card>&);
    void addToFaceUp(const Card& card);
    void addToFaceDown(const Card& card);
    void sortHand();
    void swap(const int, const int);
    void removeFromHand(const std::vector<int>&); 
    void removeFromFaceUp(const std::vector<int>&); 
    void removeFromFaceDown(const int); 
    bool hasCards() const;
    bool hasCardsInHand() const;
    bool hasCardsInFaceUp() const;

    virtual bool isComputer() const =0;
    virtual const std::pair<int, int> askSwapChoice() const =0;
    virtual bool askSwapCards() const =0;
    virtual const std::vector<int> askMoveChoice(const PlayerHelper&) const =0;
    virtual int askFaceDownMoveChoice() const =0;
};

#endif
