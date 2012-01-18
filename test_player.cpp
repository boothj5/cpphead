#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "human_player.hpp"
#include "player_factory.hpp"

using namespace std ;

void testAddToHandAddsCard(void)
{
    HumanPlayer james("James") ;
    Card three(THREE, DIAMONDS) ;
    james.addToHand(three) ;
    vector<Card> cards = james.hand() ;
    Card found = cards[0] ;

    assert_equals(found, three) ;
}

void testAddAllToHandAddsCards(void)
{
    HumanPlayer james("James") ;
    Card three(THREE, DIAMONDS) ;
    Card seven(SEVEN, DIAMONDS) ;
    Card four(FOUR, SPADES) ;
    Card ace(ACE, CLUBS) ;

    vector<Card> cards ;
    cards.push_back(three) ;
    cards.push_back(seven) ;
    cards.push_back(four) ;
    cards.push_back(ace) ;

    james.addAllToHand(cards) ;
    
    vector<Card>::const_iterator found ;
    vector<Card> hand = james.hand();

    found = find(hand.begin(), hand.end(), three);
    assert_false(found == hand.end()) ;
    
    found = find(hand.begin(), hand.end(), seven);
    assert_false(found == hand.end()) ;
    
    found = find(hand.begin(), hand.end(), four);
    assert_false(found == hand.end()) ;
    
    found = find(hand.begin(), hand.end(), ace);
    assert_false(found == hand.end()) ;
}

void testAddToFaceUpAddsCard(void)
{
    HumanPlayer james("James") ;
    Card three(THREE, DIAMONDS) ;
    james.addToFaceUp(three) ;
    vector<Card> cards = james.faceUp() ;
    Card found = cards[0] ;

    assert_equals(found, three) ;
}

void testAddToFaceDownAddsCard(void)
{
    HumanPlayer james("James") ;
    Card three(THREE, DIAMONDS) ;
    james.addToFaceDown(three) ;
    vector<Card> cards = james.faceDown() ;
    Card found = cards[0] ;

    assert_equals(found, three) ;
}

void sortHandSortsHand(void) 
{
    HumanPlayer james("James") ;
    Card six(SIX, HEARTS) ;
    Card three(THREE, DIAMONDS) ;
    Card two(TWO, SPADES) ;
    Card five(FIVE, DIAMONDS) ;
    james.addToHand(six) ;
    james.addToHand(three) ;
    james.addToHand(two) ;
    james.addToHand(five) ;

    james.sortHand() ;

    assert_equals(james.hand()[0], three) ;
    assert_equals(james.hand()[1], five) ;
    assert_equals(james.hand()[2], six) ;
    assert_equals(james.hand()[3], two) ;
}

void swapSwapsCards(void)
{
    HumanPlayer james("James") ;
    Card six(SIX, HEARTS) ;
    Card three(THREE, DIAMONDS) ;
    Card two(TWO, SPADES) ;
    Card five(FIVE, DIAMONDS) ;
    Card seven(SEVEN, CLUBS) ;
    Card four(FOUR, SPADES) ;
    james.addToHand(three) ;
    james.addToHand(six) ;
    james.addToHand(two) ;
    james.addToFaceUp(five) ;
    james.addToFaceUp(seven) ;
    james.addToFaceUp(four) ;
    
    james.swap(1, 2) ;
    
    assert_equals(james.hand()[0], three) ;    
    assert_equals(james.hand()[1], four) ;    
    assert_equals(james.hand()[2], two) ;    
    assert_equals(james.faceUp()[0], five) ;    
    assert_equals(james.faceUp()[1], seven) ;    
    assert_equals(james.faceUp()[2], six) ;    
}

void removeFromHandRemovesCard(void) 
{
    HumanPlayer james("James") ;
    Card six(SIX, HEARTS) ;
    Card three(THREE, DIAMONDS) ;
    Card two(TWO, SPADES) ;
    Card five(FIVE, DIAMONDS) ;
    james.addToHand(six) ;
    james.addToHand(three) ;
    james.addToHand(two) ;
    james.addToHand(five) ;

    vector<int> toRemove ;
    toRemove.push_back(1) ;

    james.removeFromHand(toRemove) ; 
    james.sortHand();

    assert_equals(james.hand()[0], five) ;
    assert_equals(james.hand()[1], six) ;
    assert_equals(james.hand()[2], two) ;
}

void removeFromHandRemovesCards(void) 
{
    HumanPlayer james("James") ;
    Card six(SIX, HEARTS) ;
    Card three(THREE, DIAMONDS) ;
    Card two(TWO, SPADES) ;
    Card five(FIVE, DIAMONDS) ;
    Card king(KING, SPADES);
    Card ace(ACE, HEARTS);
    james.addToHand(six) ;
    james.addToHand(three) ;
    james.addToHand(two) ;
    james.addToHand(five) ;
    james.addToHand(king) ;
    james.addToHand(ace) ;

    vector<int> toRemove ;
    toRemove.push_back(3) ;
    toRemove.push_back(2) ;
    toRemove.push_back(5) ;

    james.removeFromHand(toRemove) ; 
    james.sortHand();

    assert_equals(james.hand()[0], three) ;
    assert_equals(james.hand()[1], six) ;
    assert_equals(james.hand()[2], king) ;
}

void hasCardsWhenCardsInHand() 
{
    HumanPlayer james("James") ;
    Card six(SIX, HEARTS) ;
    james.addToHand(six) ;

    assert_true(james.hasCards()) ;
}

void hasCardsWhenCardsInFaceUp() 
{
    HumanPlayer james("James") ;
    Card six(SIX, HEARTS) ;
    james.addToFaceUp(six) ;

    assert_true(james.hasCards()) ;
}

void hasCardsWhenCardsInFaceDown() 
{
    HumanPlayer james("James") ;
    Card six(SIX, HEARTS) ;
    james.addToFaceDown(six) ;

    assert_true(james.hasCards()) ;
}

void notHasCardsWhenNone()
{
    HumanPlayer james("James") ;
    assert_false(james.hasCards()) ;
}

void createComputerPlayer()
{
    Player * player = PlayerFactory::createPlayer("Computer", 'r');
    assert_true(player->isComputer());
    string name = "Computer";
    assert_equals(player->name(), name);
}

void createHumanPlayer()
{
    Player * player = PlayerFactory::createPlayer("James", 'h');
    assert_false(player->isComputer());
    string name = "James";
    assert_equals(player->name(), name);
}

void register_player_tests()
{
    TEST_MODULE("test_player");
    TEST(testAddToHandAddsCard);
    TEST(testAddAllToHandAddsCards);
    TEST(testAddToFaceUpAddsCard);
    TEST(testAddToFaceDownAddsCard);
    TEST(sortHandSortsHand);
    TEST(swapSwapsCards);
    TEST(removeFromHandRemovesCard);
    TEST(removeFromHandRemovesCards);
    TEST(hasCardsWhenCardsInHand);
    TEST(hasCardsWhenCardsInFaceUp);
    TEST(hasCardsWhenCardsInFaceDown);
    TEST(notHasCardsWhenNone);
    TEST(createComputerPlayer);
    TEST(createHumanPlayer);
}



