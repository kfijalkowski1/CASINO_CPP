#include "BJHand.h"

BJHand::BJHand()
{
}
int BJHand::getPoints()
{
    int sum = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        sum += std::min(cards[i].getNumber(), (unsigned int)10);
    }
    return sum;
}
void BJHand::addCard(Card card)
{
    cards.push_back(card);
}
void BJHand::reset()
{
    cards = {};
}