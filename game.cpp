#include <iostream>
#include <vector>
#include <algorithm>
#include "game.hpp"
#include "console.hpp"
#include "player.hpp"
#include "player_helper.hpp"
#include "card.hpp"

#define DECK_SIZE 52

using namespace std ;

Game::Game(const vector<string>& names, const vector<char>& types, int numCards) 
{
    int i, rank, suit, numDecks ;
    numPlayers_ = names.size() ;
    numCards_ = numCards ;
    burnt_ = 0 ;
    for (i = 0 ; i < numPlayers_ ; i++) {
        Player *player = Player::createPlayer(names[i], types[i]) ;
        players_.push_back(player) ;
    }
    currentPlayer_ = players_.begin() ;

    numDecks = calcNumDecks(numPlayers_, numCards_) ;
    for (i = 0 ; i < numDecks ; i++)
        for (suit = HEARTS ; suit <= CLUBS ; suit++)
            for (rank = TWO ; rank <= ACE ; rank++)
                deck_.push_back(Card((cardrank)rank, (cardsuit)suit)) ;

    ptrdiff_t (*p_randomGen)(ptrdiff_t) = randomGen ;    
    random_shuffle(deck_.begin(), deck_.end(), p_randomGen) ;
}

PlayerHelper Game::getPlayerHelper() const
{
    PlayerHelper helper(pile_);
    return helper;
}

void Game::deal()
{
    int i ;
    
    vector<Player *>::iterator player ;
    for (player = players_.begin() ; player != players_.end() ; player++) {
        for (i = 0 ; i < numCards_ ; i++) {
            (*player)->addToHand(deck_.back()) ;
            deck_.pop_back() ;
            (*player)->addToFaceUp(deck_.back()) ;
            deck_.pop_back() ;
            (*player)->addToFaceDown(deck_.back()) ;
            deck_.pop_back() ;
        }
        (*player)->sortHand() ;
    }
}

void Game::swap(Player * player, int handChoice, int faceUpChoice)
{
    player->swap(handChoice, faceUpChoice) ;
}

void Game::firstMove()
{
    // assumes hands are not empty and are sorted
    vector<Card> lowestByPlayer ;
    vector<int> toLay ;
    int i ;

    // find player with lowest card    
    currentPlayer_ = players_.begin() ;
    for (i = 1 ; i < numPlayers_ ; i++) {
        Card playersLowest = players_[i]->hand()[0] ;
        Card currentLowest = (*currentPlayer_)->hand()[0] ;
        if (Card::shCompare(playersLowest, currentLowest))
            currentPlayer_ = players_.begin() + i ;
    }
     
    // get indexes of cards with same rank in players hand
    Card first = (*currentPlayer_)->hand()[0] ;
    for (i = 0 ; i < numCards_ ; i++) {
        Card current = (*currentPlayer_)->hand()[i] ;
        if (current.equalsRank(first))
            toLay.push_back(i) ;
    }

    // play them
    setLastHandMove(toLay) ;
    playFromHand(toLay) ;
    moveToNextPlayer() ;
}

bool Game::canContinue() const
{
    int playersWithCards = 0 ;

    vector<Player *>::const_iterator player ;
    for (player = players_.begin() ; player != players_.end() ; player++)
        if ((*player)->hasCards())
            playersWithCards++ ;

    return playersWithCards > 1 ;
}

void Game::makeMove(const vector<int>& choices)
{
    if ((*currentPlayer_)->hasCardsInHand()) {
        setLastHandMove(choices) ;
        playFromHand(choices) ;
    }
    else {
        setLastFaceUpMove(choices) ;
        playFromFaceUp(choices) ;
    }

    processSpecialCards() ;
}

void Game::makeFaceDownMove(int choice)
{
    setLastFaceDownMove(choice) ;
    playFromFaceDown(choice) ;

    processSpecialCards() ;
}

void Game::processSpecialCards()
{
    if (burnCardLaid())
        burnPile() ;
    else if (missAGoLaid())
        missAGo() ;
    else
        moveToNextPlayer() ;
}

void Game::burnPile()
{
    burnt_ += pile_.size() ;
    pile_.clear() ;
    lastMove_ = (*currentPlayer_)->name() ;
    lastMove_ += " burnt the pile." ;
}

void Game::missAGo()
{
    setLastMoveMissAGo() ;
    moveToNextPlayer() ;
    moveToNextPlayer() ;
}

bool Game::burnCardLaid() const
{
    if (pile_.back().isBurnCard())
        return true ;
    else if (pile_.size() > 3) {
        vector<Card> lastFour ;
        lastFour.push_back(pile_[pile_.size() - 1]) ;
        lastFour.push_back(pile_[pile_.size() - 2]) ;
        lastFour.push_back(pile_[pile_.size() - 3]) ;
        lastFour.push_back(pile_[pile_.size() - 4]) ;
        
        if (Card::allRanksEqual(lastFour))
            return true ;
    }
    return false ;
}

bool Game::missAGoLaid() const 
{
    return (pile_.back().isMissAGoCard()) ;
}

bool Game::validMove(const vector<int>& choices) const
{
    const Player *player = currentPlayer() ;
    vector<Card> toLay ;
    vector<int>::const_iterator index ;
    if (player->hasCardsInHand())
        for (index = choices.begin() ; index != choices.end() ; index++)
            if (*index >= player->hand().size())
                return false ;
            else
                toLay.push_back(player->hand()[*index]) ;
    else
        for (index = choices.begin() ; index != choices.end() ; index++)
            if (*index >= player->faceUp().size())
                return false ;
            else 
                toLay.push_back(player->faceUp()[*index]) ;

    return validMove(toLay) ;
}

bool Game::validMoveFromFaceDown(int choice) const
{
    const Player *player = currentPlayer() ;
    vector<Card> toLay ;
    toLay.push_back(player->faceDown()[choice]) ;
    return validMove(toLay) ;
}

bool Game::validMove(const vector<Card>& cards) const
{
    if (!Card::allRanksEqual(cards)) 
        return false ;
    else
        return Game::canLay(cards.back(), pile_) ;
}

bool Game::currentPlayerCanMove() const
{
    if (pile_.empty())
        return true ;
    
    const Player *player = currentPlayer() ;    
    if (player->hasCardsInHand())
        return canMoveWithOneOf(player->hand()) ;
    else if (player->hasCardsInFaceUp())
        return canMoveWithOneOf(player->faceUp()) ;
    else
        return false ;
}
    
bool Game::playingFromFaceDown() const
{
    const Player *player = currentPlayer() ;
    return (!player->hasCardsInHand() && !player->hasCardsInFaceUp()) ;
}

void Game::pickUp()
{
    (*currentPlayer_)->addAllToHand(pile_) ;
    (*currentPlayer_)->sortHand() ;

    pile_.clear() ;

    setLastMovePickUp() ;
    moveToNextPlayer() ;
}

void Game::pickUpPileAndFaceDown(int choice)
{
    (*currentPlayer_)->addAllToHand(pile_) ;
    (*currentPlayer_)->addToHand((*currentPlayer_)->faceDown()[choice]) ;
    (*currentPlayer_)->sortHand() ;
    (*currentPlayer_)->removeFromFaceDown(choice) ;

    pile_.clear() ;
    
    lastMove_ = (*currentPlayer_)->name() ;
    lastMove_ += " picked up." ;
    moveToNextPlayer() ;
}

void Game::playFromHand(const vector<int>& toLay)
{
    int i ;
    for (i = 0 ; i < toLay.size() ; i++)
        pile_.push_back((*currentPlayer_)->hand()[toLay[i]]) ;
    
    (*currentPlayer_)->removeFromHand(toLay) ;

    while (deck_.size() > 0 && (*currentPlayer_)->hand().size() < numCards_) {
        (*currentPlayer_)->addToHand(deck_.back()) ;
        deck_.pop_back() ;
    }

    (*currentPlayer_)->sortHand() ;
}

void Game::playFromFaceUp(const vector<int>& toLay)
{
    int i ;
    for (i = 0 ; i < toLay.size() ; i++)
        pile_.push_back((*currentPlayer_)->faceUp()[toLay[i]]) ;
    
    (*currentPlayer_)->removeFromFaceUp(toLay) ;
}

void Game::playFromFaceDown(int choice)
{
    pile_.push_back((*currentPlayer_)->faceDown()[choice]) ;
    (*currentPlayer_)->removeFromFaceDown(choice) ;
}

void Game::setLastHandMove(const vector<int>& toLay) 
{
    const Player *player = currentPlayer() ;
    lastMove_ = "" ;
    lastMove_ += player->name() ;
    lastMove_ += " laid " ;
    int i ;
    for (i = 0 ; i < toLay.size() ; i++) {
        lastMove_ += player->hand()[toLay[i]].toString() ;
        if (i < toLay.size())
            lastMove_ += ", " ;
    }
}

void Game::setLastFaceUpMove(const vector<int>& toLay) 
{
    const Player *player = currentPlayer() ;
    lastMove_ = "" ;
    lastMove_ += player->name() ;
    lastMove_ += " laid " ;
    int i ;
    for (i = 0 ; i < toLay.size() ; i++) {
        lastMove_ += player->faceUp()[toLay[i]].toString() ;
        if (i < toLay.size())
            lastMove_ += ", " ;
    }
}

void Game::setLastFaceDownMove(int choice)
{
    const Player *player = currentPlayer() ;
    lastMove_ = player->name() ;
    lastMove_ += " laid the " ;
    lastMove_ += player->faceDown()[choice].toString() ;
}

void Game::setLastMoveMissAGo()
{
    lastMove_ = (*currentPlayer_)->name() ;
    lastMove_ += " laid miss a go card." ;
}

void Game::setLastMovePickUp() 
{
    const Player *player = currentPlayer() ;
    lastMove_ = player->name() ; 
    lastMove_ += " picked up." ;
}

void Game::moveToNextPlayer()
{
    currentPlayer_++ ;
    if (currentPlayer_ == players_.end())
        currentPlayer_ = players_.begin() ;
    while (!(*currentPlayer_)->hasCards()) 
        moveToNextPlayer() ;
}

bool Game::canMoveWithOneOf(const vector<Card>& cards) const
{
    int i ;
    for (i = 0 ; i < cards.size() ; i++)
        if (Game::canLay(cards[i], pile_))
            return true ;
    return false ;   

}

bool Game::canLay(Card card, const vector<Card>& cards)
{
    if (cards.empty())
        return true ;
    else if (card.special())
        return true ;
    else if (cards.back().isInvisible()) {
        vector<Card> newPile = cards ;
        newPile.pop_back() ;
        return canLay(card, newPile) ;
    }
    else if (card.rank() < cards.back().rank())
        return false ;
    else
        return true ;
}

int Game::calcNumDecks(int numPlayers, int numCards)
{
    int decksRequired, totalCards, div, add ;
    totalCards = numPlayers * (numCards * 3) ;
    div = totalCards / DECK_SIZE ;
    add = ((totalCards % DECK_SIZE) > 0) ;
    decksRequired = div + add ;
    return decksRequired ;
}

ptrdiff_t Game::randomGen(ptrdiff_t i)
{
    int seed = static_cast<int>(time(0));
    srand(seed) ;
    return rand() % i ; 
}

string Game::getCppHead() const
{
    vector<Player *>::const_iterator player ;
    for (player = players_.begin() ; player != players_.end() ; player++)
        if ((*player)->hasCards())
            return (*player)->name() ;
    return players_[0]->name() ;
}

const vector<Player *> Game::players() const 
{ 
    return players_ ; 
}

const Player * Game::currentPlayer() const 
{
    return *currentPlayer_ ; 
}

vector<Card> Game::deck() const 
{ 
    return deck_ ; 
}

vector<Card> Game::pile() const 
{ 
    return pile_ ; 
}

int Game::burnt() const
{
    return burnt_ ;
}

string Game::lastMove() const 
{ 
    return lastMove_ ; 
}
