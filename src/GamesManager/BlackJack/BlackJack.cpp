#include "BlackJack.h"
//#include <algorithm>

BJHand::BJHand()
{
}
void BJHand::addCard(Card card)
{
    hands[0].push_back(card);
    // points[0] += std::min(card.getNumber(), (unsigned int)10);
}
void BJHand::addCard(Card card, bool toSplitted)
{
    hands[(int)toSplitted].push_back(card);
    // points[(int)toSplitted] += std::min(card.getNumber(), (unsigned int)10);
}
void BJHand::reset()
{
    isSplitted = false;
    // points = {0, 0};
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
    // add all new players to the game
    players.insert(players.begin(), playerBuffor.begin(), playerBuffor.end());
    // from this ***
    if (!(deck.checkIfEnough()))
    {
        deck.shuffle(); // Deck is now mixed and all used cards returned to deck
    }
    dealer.hand.addCard(deck.getCard());
    // draw and wait
    for (auto player : players)
    {
        player.hand.addCard(deck.getCard());
        // draw and wait
    }
    // to this *** is a initialDistribution()
    for (auto player : players)
    {

        // player.bet = getBet();
        //  take bets ? cin?
        //  draw
    }
}

void BlackJack::addPlayer(Player &newPlayer)
{
    // BJPlayer newBJPlayer(newPlayer);
    // playerBuffor.push_back(newBJPlayer);
}
void BlackJack::makeMove(Player &player, char decision)
{
    switch (decision)
    {
    case 'H':
        // Hit
        // update hand
        break;

    default:
        break;
    }
}
