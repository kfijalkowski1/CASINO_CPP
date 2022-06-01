#pragma once
#include "GamesManager/Cards/Cards.h"

class BJHand
{
public:
    BJHand();
    int getPoints();
    std::vector<Card> cards;
    void addCard(Card card);
    void reset();
};