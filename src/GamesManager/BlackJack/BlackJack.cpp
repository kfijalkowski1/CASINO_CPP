#include "BlackJack.h"
#include <iostream>

BJHand::BJHand()
{
}
int BJHand::getPoints(bool Splitted)
{
    int sum = 0;
    for (int i = 0; i < hands[(int)Splitted].size(); i++)
    {
        sum += std::min(hands[(int)Splitted][i].getNumber(), (unsigned int)10);
    }
    return sum;
}
void BJHand::addCard(Card card)
{
    hands[0].push_back(card);
}
void BJHand::addCard(Card card, bool toSplitted)
{
    hands[(int)toSplitted].push_back(card);
}
void BJHand::reset()
{
    isSplitted = false;
    hands = {{}, {}};
}
// bool BJPlayer::operator==(Player &other)
//{
///    return name == other.name;
//}
BlackJack::BlackJack(unsigned int nOfStdDecks)
{
    Deck deck1(nOfStdDecks);
    deck = deck1;
    rules.content = "BlackJack rules:\n - rule1\n - rule2 \n.\n.\n.\n."; // nwm czy tutaj
}
void BlackJack::startNewDeal()
{
    // add all new players to the game
    players.insert(players.end(), playerBuffor.begin(), playerBuffor.end());
    // zer
    //  from this ***
    if (!(deck.checkIfEnough()))
    {
        deck.shuffle(); // Deck is now mixed and all used cards returned to deck
    }
    dealer.hand.addCard(deck.getCard());
    // draw and wait
    for (auto player : players)
    {
        (*player).hand.addCard(deck.getCard());
    }
    // to this *** is a initialDistribution()
    for (auto player : players)
    {

        // player.bet = getBet();
        //  take bets ? cin?
    }
}

void BlackJack::addPlayer(Player *newPlayer)
{
    BJPlayer *newBJPlayerPtr = dynamic_cast<BJPlayer *>(newPlayer);
    playerBuffor.push_back(newBJPlayerPtr);
}
bool BlackJack::makeMove(Player &player, char decision)
{
    // returns true if next player
    switch (decision)
    {
    case 'H':
        // Hit
        // update hand, checkHand, makeMove
        return false;
    case 'S':
        // Stand
        // go to next Player, makeMove
        return true;
    case 'D':
        // DoubleDown
        // update bet and hand, checkHand, makeMove
        return false;
    case 'P':
        // Split
        // update hand, makeMove
        return false;
    default:
        throw "Nie ma takiej opcji!";
    }
}
void BlackJack::fakeMenu()
{
    int dec;
    std::cin >> dec;
    // nazwafunkcji(dec);
}