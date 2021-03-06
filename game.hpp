#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include "player.hpp"
#include "player_helper.hpp"
#include "card.hpp"

class Game {
    std::vector<Player *> players_;
    std::vector<Card> deck_;
    std::vector<Card> pile_;
    int burnt_;
    int numCards_;
    int numPlayers_;
    std::vector<Player *>::iterator currentPlayer_;
    std::string lastMove_;

    public:
    Game(const std::vector<std::string>&, const std::vector<char>&, int);
    ~Game();
    
    const PlayerHelper getPlayerHelper() const;
    void deal();
    void swap(Player&, const int, const int);
    void firstMove();
    const std::vector<Player *> players() const;
    const Player * currentPlayer() const;
    const std::vector<Card> deck() const;
    const std::vector<Card> pile() const;
    int burnt() const;
    const std::string lastMove() const;
    bool canContinue() const;
    void makeMove(const std::vector<int>&);
    void makeFaceDownMove(const int);
    bool currentPlayerCanMove() const;
    bool playingFromFaceDown() const;
    void pickUp();
    void pickUpPileAndFaceDown(const int);
    bool validMove(const std::vector<int>&) const;
    bool validMoveFromFaceDown(const int) const;
    const std::string getCppHead() const;

    
    private:
    void playFromHand(const std::vector<int>&);
    void setLastHandMove(const std::vector<int>&);
    void playFromFaceUp(const std::vector<int>&);
    void playFromFaceDown(const int);
    void setLastFaceUpMove(const std::vector<int>&);
    void setLastFaceDownMove(const int);
    void setLastMovePickUp();
    void setLastMoveMissAGo();
    void moveToNextPlayer();
    void processSpecialCards();
    bool canMoveWithOneOf(const std::vector<Card>&) const;
    bool validMove(const std::vector<Card>&) const;
    bool burnCardLaid() const;
    bool missAGoLaid() const;
    void burnPile();
    void missAGo();
};

namespace game {

bool canLay(const Card&, const std::vector<Card>&);

int calcNumDecks(int, int);

} // namespace game

#endif
