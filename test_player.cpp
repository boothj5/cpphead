#include <head-unit-cpp.h>
#include <vector>
#include <algorithm>

#include "testsuite.hpp"
#include "player.hpp"

using namespace std ;

void testAddToHandAddsCard(void)
{
    Player james("James") ;
    Card three(THREE, DIAMONDS) ;
    james.addToHand(three) ;
    vector<Card> cards = james.hand() ;
    Card found = cards[0] ;

    assert_string_equals(found.toString(), three.toString()) ;
}

void testAddAllToHandAddsCards(void)
{
    Player james("James") ;
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
    
    vector<Card>::iterator found ;
    vector<Card> hand = james.hand() ;
    found = find(hand.begin(), hand.end(), three) ;
    assert_false(found == hand.end()) ;
    found = find(hand.begin(), hand.end(), seven) ;
    assert_false(found == hand.end()) ;
    found = find(hand.begin(), hand.end(), four) ;
    assert_false(found == hand.end()) ;
    found = find(hand.begin(), hand.end(), ace) ;
    assert_false(found == hand.end()) ;
}

void testAddToFaceUpAddsCard(void)
{
    Player james("James") ;
    Card three(THREE, DIAMONDS) ;
    james.addToFaceUp(three) ;
    vector<Card> cards = james.faceUp() ;
    Card found = cards[0] ;

    assert_string_equals(found.toString(), three.toString()) ;
}

void testAddToFaceDownAddsCard(void)
{
    Player james("James") ;
    Card three(THREE, DIAMONDS) ;
    james.addToFaceDown(three) ;
    vector<Card> cards = james.faceDown() ;
    Card found = cards[0] ;

    assert_string_equals(found.toString(), three.toString()) ;
}

void sortHandSortsHand(void) 
{
    Player james("James") ;
    Card six(SIX, HEARTS) ;
    Card three(THREE, DIAMONDS) ;
    Card two(TWO, SPADES) ;
    Card five(FIVE, DIAMONDS) ;
    james.addToHand(six) ;
    james.addToHand(three) ;
    james.addToHand(two) ;
    james.addToHand(five) ;

    james.sortHand() ;

    assert_string_equals(james.hand()[0].toString(), three.toString()) ;
    assert_string_equals(james.hand()[1].toString(), five.toString()) ;
    assert_string_equals(james.hand()[2].toString(), six.toString()) ;
    assert_string_equals(james.hand()[3].toString(), two.toString()) ;
}

void swapSwapsCards(void)
{
    Player james("James") ;
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
    
    assert_string_equals(james.hand()[0].toString(), three.toString()) ;    
    assert_string_equals(james.hand()[1].toString(), four.toString()) ;    
    assert_string_equals(james.hand()[2].toString(), two.toString()) ;    
    assert_string_equals(james.faceUp()[0].toString(), five.toString()) ;    
    assert_string_equals(james.faceUp()[1].toString(), seven.toString()) ;    
    assert_string_equals(james.faceUp()[2].toString(), six.toString()) ;    
}

void removeFromHandRemovesCard(void) 
{
    Player james("James") ;
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

    assert_string_equals(james.hand()[0].toString(), five.toString()) ;
    assert_string_equals(james.hand()[1].toString(), six.toString()) ;
    assert_string_equals(james.hand()[2].toString(), two.toString()) ;
}

void hasCardsWhenCardsInHand() 
{
    Player james("James") ;
    Card six(SIX, HEARTS) ;
    james.addToHand(six) ;

    assert_true(james.hasCards()) ;
}

void hasCardsWhenCardsInFaceUp() 
{
    Player james("James") ;
    Card six(SIX, HEARTS) ;
    james.addToFaceUp(six) ;

    assert_true(james.hasCards()) ;
}

void hasCardsWhenCardsInFaceDown() 
{
    Player james("James") ;
    Card six(SIX, HEARTS) ;
    james.addToFaceDown(six) ;

    assert_true(james.hasCards()) ;
}

void notHasCardsWhenNone()
{
    Player james("James") ;
    assert_false(james.hasCards()) ;
}

void register_player_tests()
{
    add_suite("test_player") ;
    add_test(testAddToHandAddsCard, "testAddToHandAddsCard") ;
    add_test(testAddAllToHandAddsCards, "testAddAllToHandAddsCards") ;
    add_test(testAddToFaceUpAddsCard, "testAddToFaceUpAddsCard") ;
    add_test(testAddToFaceDownAddsCard, "testAddToFaceDownAddsCard") ;
    add_test(sortHandSortsHand, "sortHandSortsHand") ;
    add_test(swapSwapsCards, "swapSwapsCards") ;
    add_test(removeFromHandRemovesCard, "removeFromHandRemovesCard") ;
    add_test(hasCardsWhenCardsInHand, "hasCardsWhenCardsInHand") ;
    add_test(hasCardsWhenCardsInFaceUp, "hasCardsWhenCardsInFaceUp") ;
    add_test(hasCardsWhenCardsInFaceDown, "hasCardsWhenCardsInFaceDown") ;
    add_test(notHasCardsWhenNone, "notHasCardsWhenNone") ;
}



