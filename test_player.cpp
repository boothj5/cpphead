#include <head-unit.h>
#include <vector>
#include <algorithm>

#include "human_player.hpp"
#include "player_factory.hpp"

using namespace std ;

static Player *james;
static Card *threeD;
static Card *sevenD;
static Card *fourS;
static Card *aceC;
static Card *sixH;
static Card *twoS;
static Card *fiveD;
static Card *sevenC;
static Card *kingS;
static Card *aceH;

static void setup(void)
{
    threeD = new Card(THREE, DIAMONDS);
    sevenD = new Card(SEVEN, DIAMONDS);
    fourS = new Card(FOUR, SPADES);
    aceC = new Card(ACE, CLUBS);
    sixH = new Card(SIX, HEARTS);
    threeD = new Card(THREE, DIAMONDS);
    twoS = new Card(TWO, SPADES);
    fiveD = new Card(FIVE, DIAMONDS);
    sevenC = new Card(SEVEN, CLUBS);
    kingS = new Card(KING, SPADES);
    aceH = new Card(ACE, HEARTS);
}

static void testAddToHandAddsCard(void)
{
    james = new HumanPlayer("James");
    james->addToHand(*threeD);
    vector<Card> cards = james->hand();
    Card found = cards[0];

    assert_equals(found, *threeD);
    delete james;
}

static void testAddAllToHandAddsCards(void)
{
    james = new HumanPlayer("James");
    vector<Card> cards;
    cards.push_back(*threeD);
    cards.push_back(*sevenD);
    cards.push_back(*fourS);
    cards.push_back(*aceC);

    james->addAllToHand(cards);
    
    vector<Card>::const_iterator found;
    vector<Card> hand = james->hand();

    found = find(hand.begin(), hand.end(), *threeD);
    assert_false(found == hand.end());
    
    found = find(hand.begin(), hand.end(), *sevenD);
    assert_false(found == hand.end());
    
    found = find(hand.begin(), hand.end(), *fourS);
    assert_false(found == hand.end());
    
    found = find(hand.begin(), hand.end(), *aceC);
    assert_false(found == hand.end());
    delete james;
}

static void testAddToFaceUpAddsCard(void)
{
    james = new HumanPlayer("James");
    james->addToFaceUp(*threeD);
    vector<Card> cards = james->faceUp();
    Card found = cards[0];

    assert_equals(found, *threeD);
    delete james;
}

static void testAddToFaceDownAddsCard(void)
{
    james = new HumanPlayer("James");
    james->addToFaceDown(*threeD);
    vector<Card> cards = james->faceDown();
    Card found = cards[0];

    assert_equals(found, *threeD);
    delete james;
}

static void sortHandSortsHand(void) 
{
    james = new HumanPlayer("James");
    james->addToHand(*sixH);
    james->addToHand(*threeD);
    james->addToHand(*twoS);
    james->addToHand(*fiveD);

    james->sortHand();

    assert_equals(james->hand()[0], *threeD);
    assert_equals(james->hand()[1], *fiveD);
    assert_equals(james->hand()[2], *sixH);
    assert_equals(james->hand()[3], *twoS);
    delete james;
}

static void swapSwapsCards(void)
{
    james = new HumanPlayer("James");
    james->addToHand(*threeD);
    james->addToHand(*sixH);
    james->addToHand(*twoS);
    james->addToFaceUp(*fiveD);
    james->addToFaceUp(*sevenC);
    james->addToFaceUp(*fourS);
    
    james->swap(1, 2);
    
    assert_equals(james->hand()[0], *threeD);    
    assert_equals(james->hand()[1], *fourS);    
    assert_equals(james->hand()[2], *twoS);    
    assert_equals(james->faceUp()[0], *fiveD);    
    assert_equals(james->faceUp()[1], *sevenC);    
    assert_equals(james->faceUp()[2], *sixH);    
    delete james;
}

static void removeFromHandRemovesCard(void) 
{
    james = new HumanPlayer("James");
    james->addToHand(*sixH);
    james->addToHand(*threeD);
    james->addToHand(*twoS);
    james->addToHand(*fiveD);

    vector<int> toRemove;
    toRemove.push_back(1);

    james->removeFromHand(toRemove); 
    james->sortHand();

    assert_equals(james->hand()[0], *fiveD);
    assert_equals(james->hand()[1], *sixH);
    assert_equals(james->hand()[2], *twoS);
    delete james;
}

static void removeFromHandRemovesCards(void) 
{
    james = new HumanPlayer("James");
    james->addToHand(*sixH) ;
    james->addToHand(*threeD) ;
    james->addToHand(*twoS) ;
    james->addToHand(*fiveD) ;
    james->addToHand(*kingS) ;
    james->addToHand(*aceH) ;

    vector<int> toRemove ;
    toRemove.push_back(3) ;
    toRemove.push_back(2) ;
    toRemove.push_back(5) ;

    james->removeFromHand(toRemove) ; 
    james->sortHand();

    assert_equals(james->hand()[0], *threeD) ;
    assert_equals(james->hand()[1], *sixH) ;
    assert_equals(james->hand()[2], *kingS) ;
    delete james;
}

static void hasCardsWhenCardsInHand() 
{
    james = new HumanPlayer("James");
    james->addToHand(*sixH) ;
    assert_true(james->hasCards()) ;
    delete james;
}

static void hasCardsWhenCardsInFaceUp() 
{
    james = new HumanPlayer("James");
    james->addToFaceUp(*sixH) ;

    assert_true(james->hasCards()) ;
    delete james;
}

static void hasCardsWhenCardsInFaceDown() 
{
    james = new HumanPlayer("James");
    james->addToFaceDown(*sixH) ;

    assert_true(james->hasCards()) ;
    delete james;
}

static void notHasCardsWhenNone()
{
    james = new HumanPlayer("James");
    assert_false(james->hasCards()) ;
    delete james;
}

void register_player_tests()
{
    TEST_MODULE("test_player");
    SETUP(setup);
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
