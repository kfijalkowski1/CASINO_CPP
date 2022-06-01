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
    // fakeMenu();
}
void BlackJack::startNewDeal()
{
    dealer.hand.addCard(deck.getCard());
    players[0]->hand.addCard(deck.getCard());
}

void BlackJack::addPlayer(Player *newPlayer)
{
    BJPlayer *newBJPlayerPtr = dynamic_cast<BJPlayer *>(newPlayer);
    players.push_back(newBJPlayerPtr);
    // playerBuffor.push_back(newBJPlayerPtr);
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
    choice(dec);
}
void BlackJack::startChoice(int dec)
{
    switch (dec)
    {
    case 0: // add Player
        /* code */
        break;
    case 1: // Play
        startNewDeal();
        break;
    case 2: // exit
        // mainManager.stack.pop();
        break;
    default:
        break;
    }
}
void BlackJack::choice(int i)
{
    switch (state.stateNumber)
    {
    case 0:
        startChoice(i);
        break;
    case 1:
        BetChoice(i);
        break;
    case 2:
        actionChoice(i);
        break;
    default:

        break;
    }
}
void BlackJack::BetChoice(int i)
{
    players[state.playerIndex]->bet += i;
    state.stateNumber = 2;
    fakeMenu();
}
void BlackJack::actionChoice(int i)
{
    switch (i)
    {
    case 0: // Hit
        hit();
        break;
    case 1: // Stand
        state.playerIndex += 1;
        break;
    case 2: // DoubleDown
        doubleDown();
        break;
    // case 3: // Split
    //     split();
    //     break;
    default:
        break;
    }
    fakeMenu();
}
void BlackJack::hit()
{
    (*players[state.playerIndex]).hand.hands[0].push_back(deck.getCard());
    // if((*players[state.playerIndex]).hand.getPoints(false)> 21); should check if greater than 21
}
void BlackJack::doubleDown()
{
    (*players[state.playerIndex]).bet *= 2;
    hit();
}
void BlackJack::draw(ImageBuffer &img, Position pos)
{
    // ImageBuffer temp = this->img;
    dealer.hand.hands[0][0].draw(img, pos);
    players[0]->hand.hands[0][0].draw(img, pos + Position(0, 7));
    // img = temp;
}
// void BlackJack::split() {}
