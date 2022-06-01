#include "BlackJack.h"
#include <iostream>

BlackJack::BlackJack(Player &player, unsigned int nOfStdDecks)
{
    BJPlayer temp(player);
    this->player = temp;
    Deck deck1(nOfStdDecks);
    deck = deck1;
}

void BlackJack::processDecision(unsigned int dec)
{
    // returns true if next player
    switch (dec)
    {
    case 0:
        // Hit
        // update hand, checkHand, makeMove
        break;
    case 1:
        // Stand
        // go to next Player, makeMove
        break;
    default:
        throw "Nie ma takiej opcji!";
    }
}

void BlackJack::processMainMenu(unsigned int dec)
{
    switch (dec)
    {
    case 0: // Play
        break;
    case 1: // Exit
        break;
    default:
        break;
    }
}
void BlackJack::processBet(std::string bet)
{
    int bet_int = std::stoi(bet);
    if (bet_int > player.player.cash)
    {
        state = State::errorBet;
    }
}
