#include <iostream>
#include <vector>
#include <algorithm>
#include "game.hpp"
#include "console.hpp"
#include "player_factory.hpp"
#include "player.hpp"
#include "player_helper.hpp"
#include "card.hpp"
#include "util.hpp"

#define DECK_SIZE 52

using namespace std ;

Game::Game(const vector<string>& names, const vector<char>& types, int numCards) 
    : players_(0), 
      deck_(0),
      pile_(0),
      burnt_(0),
      numCards_(numCards),
      numPlayers_(names.size()),
      currentPlayer_(NULL),
      lastMove_("")
{
	//Create the players of the user-specified types
    int i, rank, suit, numDecks ;
    for (i = 0 ; i < numPlayers_ ; i++) {
        Player *player = PlayerFactory::createPlayer(names[i], types[i]) ;
        players_.push_back(player) ;
    }
    currentPlayer_ = players_.begin() ;

	//Create the user-specified number of decks and shuffle them
    numDecks = game::calcNumDecks(numPlayers_, numCards_) ;
    for (i = 0 ; i < numDecks ; i++)
        for (suit = HEARTS ; suit <= CLUBS ; suit++)
            for (rank = TWO ; rank <= ACE ; rank++) {
                Card card((cardrank)rank, (cardsuit)suit);
                deck_.push_back(card) ;
            }
    
    util::shuffle(deck_);
}

Game::~Game()
{
    vector<Player *>::iterator iter;
    for (iter = players_.begin(); iter!=players_.end(); iter++)
        delete *iter;
    players_.clear();
    deck_.clear();
    pile_.clear();
}

const PlayerHelper Game::getPlayerHelper() const
{
    PlayerHelper helper(pile_);
    return helper;
}

//Deals each player their facedown, faceup, and cards in hand from the deck
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
	//Rank from lowest (3) to highest (special/burn cards)
        (*player)->sortHand() ;
    }
}

void Game::swap(Player& player, const int handChoice, const int faceUpChoice)
{
    player.swap(handChoice, faceUpChoice) ;
    player.sortHand();
}

void Game::firstMove()
{
    // assumes hands are not empty and are sorted
    vector<Card> lowestByPlayer ;
    vector<int> toLay ;
    int i ;

    // find player with lowest card    
    currentPlayer_ = players_.begin() ;
    Card currentLowest = (*currentPlayer_)->hand()[0] ;
    for (i = 1 ; i < numPlayers_ ; i++) {
        Card playersLowest = players_[i]->hand()[0] ;
        if (card::shCompare(playersLowest, currentLowest))
            currentPlayer_ = players_.begin() + i ;
    }
     
    // get indexes of cards with same rank in players hand
    const Card first = (*currentPlayer_)->hand()[0] ;
    for (i = 0 ; i < numCards_ ; i++) {
        const Card current = (*currentPlayer_)->hand()[i] ;
        if (current.equalsRank(first))
            toLay.push_back(i) ;
    }

    // play them
    setLastHandMove(toLay) ;
    playFromHand(toLay) ;
    (*currentPlayer_)->sortHand();
    moveToNextPlayer() ;
}

//Determine if the game is over or not
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
	//Play cards from hand first
    if ((*currentPlayer_)->hasCardsInHand()) {
        setLastHandMove(choices) ;
        playFromHand(choices) ;
        (*currentPlayer_)->sortHand();
    } else { //If they have none, pay their choice from face up cards
        setLastFaceUpMove(choices) ;
        playFromFaceUp(choices) ;
    }

    processSpecialCards() ;
}

void Game::makeFaceDownMove(const int choice)
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

//Removes all cards in the discard (pile)
//so that future players will not pick them up
void Game::burnPile()
{
    burnt_ += pile_.size() ;
    pile_.clear() ;
    lastMove_ = (*currentPlayer_)->name() ;
    lastMove_ += " burnt the pile." ;

    if (!(*currentPlayer_)->hasCards()) {
        moveToNextPlayer();
    }
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
        return true;
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
	//Make sure all choices are within the proper bounds for no seg faults
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
    //Now that there are no errors, check if the cards themselves are valid
    return validMove(toLay) ;
}

bool Game::validMoveFromFaceDown(const int choice) const
{
    const Player *player = currentPlayer() ;
    vector<Card> toLay ;
    toLay.push_back(player->faceDown()[choice]) ;
    return validMove(toLay) ;
}

bool Game::validMove(const vector<Card>& cards) const
{
    //If cards are all of the same type, it is a valid move
    if (!card::allRanksEqual(cards)) 
        return false ;
    else
        return game::canLay(cards.back(), pile_) ;
}

bool Game::currentPlayerCanMove() const
{
    //Every card can be laid on an empty discard
    if (pile_.empty())
        return true ;
    
    //Check if any of the cards in hand (or face-up, accordingly) are higher than
    //current top card in the discard
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
    //Pick up all cards in the discard and put them in the current player's hand
    (*currentPlayer_)->addAllToHand(pile_) ;

    //Sort new cards into hand
    (*currentPlayer_)->sortHand() ;

    //Reset the discard
    pile_.clear() ;

    //Skip the rest of player's turn
    setLastMovePickUp() ;
    moveToNextPlayer() ;
}

//Function to call when whichever facedown choice couldn't be played on discard
void Game::pickUpPileAndFaceDown(const int choice)
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

//Given indices are valid and ranks are valid, play cards from hand
void Game::playFromHand(const vector<int>& toLay)
{
    int cardstoLay = 0;
    vector<int>::const_iterator iter;
    //Add cards to discard
    for (iter = toLay.begin(); iter!=toLay.end(); iter++){
        cardstoLay++;
        pile_.push_back((*currentPlayer_)->hand()[*iter]);
    }

    //Remove cards from hand    
    (*currentPlayer_)->removeFromHand(toLay) ;

    //Draw up to the number of cards (default is 3) if player went below
    while (deck_.size() > 0 && (*currentPlayer_)->hand().size() < numCards_) {
        (*currentPlayer_)->addToHand(deck_.back()) ;
        deck_.pop_back() ;
    }

    //If player laid 4 of a kind, burn the pile
    if(cardstoLay == 4){
        burnPile();
    }
}

//Play from face-up array as opposed to hand-array
void Game::playFromFaceUp(const vector<int>& toLay)
{
    int cardstoLay = 0;
    vector<int>::const_iterator iter;
    for (iter = toLay.begin(); iter!=toLay.end(); iter++){
	cardstoLay++;
        pile_.push_back((*currentPlayer_)->faceUp()[*iter]);
    }
    
    (*currentPlayer_)->removeFromFaceUp(toLay);

    if(cardstoLay == 4){
	burnPile();
    }
}

//Play from face-down array
void Game::playFromFaceDown(const int choice)
{
    pile_.push_back((*currentPlayer_)->faceDown()[choice]) ;
    (*currentPlayer_)->removeFromFaceDown(choice) ;
    //No burn check required, this is always one card
}

void Game::setLastHandMove(const vector<int>& toLay) 
{
    const Player *player = currentPlayer() ;
    lastMove_ = "" ;
    lastMove_ += player->name() ;
    lastMove_ += " laid " ;
    
    vector<int>::const_iterator iter;
    for (iter = toLay.begin(); iter!=toLay.end(); iter++) {
        lastMove_ += player->hand()[*iter].toString() ;
        if (iter != toLay.end())
            lastMove_ += ", " ;
    }
}

void Game::setLastFaceUpMove(const vector<int>& toLay) 
{
    const Player *player = currentPlayer() ;
    lastMove_ = "" ;
    lastMove_ += player->name() ;
    lastMove_ += " laid " ;
    
    vector<int>::const_iterator iter;
    for (iter = toLay.begin(); iter!=toLay.end(); iter++) {
        lastMove_ += player->faceUp()[*iter].toString() ;
        if (iter != toLay.end())
            lastMove_ += ", " ;
    }
}

void Game::setLastFaceDownMove(const int choice)
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

//End current player's turn and loop through players that are still in the game
void Game::moveToNextPlayer()
{
    currentPlayer_++;
    if (currentPlayer_ == players_.end())
        currentPlayer_ = players_.begin();
    while (!(*currentPlayer_)->hasCards()) {
        currentPlayer_++ ;
        if (currentPlayer_ == players_.end())
            currentPlayer_ = players_.begin();
    }
}

//Check if any of the given cards are higher than the current top in the discard
bool Game::canMoveWithOneOf(const vector<Card>& cards) const
{
    vector<Card>::const_iterator iter;
    for (iter = cards.begin(); iter!=cards.end(); iter++)
        if (game::canLay(*iter, pile_))
            return true ;
    return false ;   

}

const string Game::getCppHead() const
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

const vector<Card> Game::deck() const 
{ 
    return deck_ ; 
}

const vector<Card> Game::pile() const 
{ 
    return pile_ ; 
}

int Game::burnt() const
{
    return burnt_ ;
}

const string Game::lastMove() const 
{ 
    return lastMove_ ; 
}

namespace game {

bool canLay(const Card& card, const vector<Card>& cards)
{
    if (cards.empty())
        return true ;		//You can always lay no cards
    else if (card.special())
        return true ;		//Skip/burn/reset/invisible cards can be played on anything
    else if (cards.back().isInvisible()) {
        vector<Card> newPile = cards ;
        newPile.pop_back() ;
        return game::canLay(card, newPile) ;	//If top card is a 7, remove it and try again (7 doesn't increase/decrease threshold)
    }
    else if (card.rank() < cards.back().rank())
        return false ;		//If card is of lower value than top card, player cannot lay that card
    else
        return true ;
}

int calcNumDecks(const int numPlayers, const int numCards)
{
    int decksRequired, totalCards, div, add ;
    totalCards = numPlayers * (numCards * 3) ;
    div = totalCards / DECK_SIZE ;
    add = ((totalCards % DECK_SIZE) > 0) ;
    decksRequired = div + add ;
    return decksRequired ;
}

} // namespace game