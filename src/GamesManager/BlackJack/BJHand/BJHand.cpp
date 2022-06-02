#include "BJHand.h"

BJHand::BJHand() {}
int BJHand::getPoints()
{
    int sum = 0;
    int numOfAces = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].getNumber() == 14)
        {
            numOfAces++;
            sum += 1;
        }
        sum += std::min(cards[i].getNumber(), (unsigned int)10);
        if (sum > 21 && numOfAces > 0)
        {
            sum -= 10;
            numOfAces--;
        }
    }
    return sum;
}
void BJHand::addCard(Card card) { cards.push_back(card); }
void BJHand::reset() { cards = {}; }