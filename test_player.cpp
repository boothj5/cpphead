#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "human_player.hpp"
#include "player_factory.hpp"

using namespace std ;

static Player *james;

static Card threeD(THREE, DIAMONDS);
static Card sevenD(SEVEN, DIAMONDS);
static Card fourS(FOUR, SPADES);
static Card aceC(ACE, CLUBS);
static Card sixH(SIX, HEARTS);
static Card twoS(TWO, SPADES);
static Card fiveD(FIVE, DIAMONDS);
static Card sevenC(SEVEN, CLUBS);
static Card kingS(KING, SPADES);
static Card aceH(ACE, HEARTS);

static void beforetest(void)
{
    james = new HumanPlayer("James");
}

static void aftertest(void)
{
    delete james;
}

static void testAddToHandAddsCard(void)
{
    james->addToHand(threeD);
    vector<Card> cards = james->hand();
    Card found = cards[0];

    assert_equals(found, threeD);
}

static void testAddAllToHandAddsCards(void)
{
    vector<Card> cards;
    cards.push_back(threeD);
    cards.push_back(sevenD);
    cards.push_back(fourS);
    cards.push_back(aceC);

    james->addAllToHand(cards);
    
    vector<Card>::const_iterator found;
    vector<Card> hand = james->hand();

    found = find(hand.begin(), hand.end(), threeD);
    assert_false(found == hand.end());
    
    found = find(hand.begin(), hand.end(), sevenD);
    assert_false(found == hand.end());
    
    found = find(hand.begin(), hand.end(), fourS);
    assert_false(found == hand.end());
    
    found = find(hand.begin(), hand.end(), aceC);
    assert_false(found == hand.end());
}

static void testAddToFaceUpAddsCard(void)
{
    james->addToFaceUp(threeD);
    vector<Card> cards = james->faceUp();
    Card found = cards[0];

    assert_equals(found, threeD);
}

static void testAddToFaceDownAddsCard(void)
{
    james->addToFaceDown(threeD);
    vector<Card> cards = james->faceDown();
    Card found = cards[0];

    assert_equals(found, threeD);
}

static void sortHandSortsHand(void) 
{
    james->addToHand(sixH);
    james->addToHand(threeD);
    james->addToHand(twoS);
    james->addToHand(fiveD);

    james->sortHand();

    assert_equals(james->hand()[0], threeD);
    assert_equals(james->hand()[1], fiveD);
    assert_equals(james->hand()[2], sixH);
    assert_equals(james->hand()[3], twoS);
}

static void swapSwapsCards(void)
{
    james->addToHand(threeD);
    james->addToHand(sixH);
    james->addToHand(twoS);
    james->addToFaceUp(fiveD);
    james->addToFaceUp(sevenC);
    james->addToFaceUp(fourS);
    
    james->swap(1, 2);
    
    assert_equals(james->hand()[0], threeD);    
    assert_equals(james->hand()[1], fourS);    
    assert_equals(james->hand()[2], twoS);    
    assert_equals(james->faceUp()[0], fiveD);    
    assert_equals(james->faceUp()[1], sevenC);    
    assert_equals(james->faceUp()[2], sixH);    
}

static void removeFromHandRemovesCard(void) 
{
    james->addToHand(sixH);
    james->addToHand(threeD);
    james->addToHand(twoS);
    james->addToHand(fiveD);

    vector<int> toRemove;
    toRemove.push_back(1);

    james->removeFromHand(toRemove); 
    james->sortHand();

    assert_equals(james->hand()[0], fiveD);
    assert_equals(james->hand()[1], sixH);
    assert_equals(james->hand()[2], twoS);
}

static void removeFromHandRemovesCards(void) 
{
    james->addToHand(sixH) ;
    james->addToHand(threeD) ;
    james->addToHand(twoS) ;
    james->addToHand(fiveD) ;
    james->addToHand(kingS) ;
    james->addToHand(aceH) ;

    vector<int> toRemove ;
    toRemove.push_back(3) ;
    toRemove.push_back(2) ;
    toRemove.push_back(5) ;

    james->removeFromHand(toRemove) ; 
    james->sortHand();

    assert_equals(james->hand()[0], threeD) ;
    assert_equals(james->hand()[1], sixH) ;
    assert_equals(james->hand()[2], kingS) ;
}

static void hasCardsWhenCardsInHand() 
{
    james->addToHand(sixH) ;
    assert_true(james->hasCards()) ;
}

static void hasCardsWhenCardsInFaceUp() 
{
    james->addToFaceUp(sixH) ;
    assert_true(james->hasCards()) ;
}

static void hasCardsWhenCardsInFaceDown() 
{
    james->addToFaceDown(sixH) ;

    assert_true(james->hasCards()) ;
}

static void notHasCardsWhenNone()
{
    assert_false(james->hasCards()) ;
}

void register_player_tests()
{
    TEST_MODULE("test_player");
    BEFORETEST(beforetest);
    AFTERTEST(aftertest);
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
}
