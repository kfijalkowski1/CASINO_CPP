#include "BlackJack.h"
//#include <algorithm>

BJHand::BJHand()
{
}
void BJHand::addCard(Card card)
{
    hands[0].push_back(card);
    points[0] += std::min(card.getNumber(), (unsigned int)10);
}
void BJHand::addCard(Card card, bool toSplitted)
{
    hands[(int)toSplitted].push_back(card);
    points[(int)toSplitted] += std::min(card.getNumber(), (unsigned int)10);
}
void BJHand::reset()
{
    isSplitted = false;
    points = {0, 0};
    hands = {{}, {}};
}
BlackJack::BlackJack(unsigned int nOfStdDecks)
{
    Deck deck1(nOfStdDecks);
    deck = deck1;
    rules.content = "BlackJack rules:\n - rule1\n - rule2 \n.\n.\n.\n.";
}
void BlackJack::startNewDeal()
{
    dealer.hand.addCard(deck.getCard());
    // draw
    for (auto *player : players)
    {
        // player.hand tu jest ten problem <------- !!!!!!
    }
}