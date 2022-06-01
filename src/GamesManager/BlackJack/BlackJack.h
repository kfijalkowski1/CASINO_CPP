#pragma once
#include "GamesManager/Cards/Cards.h"
#include "GamesManager/Game/Game.h"

class BJHand
{
public:
    BJHand();
    bool isSplitted = false;
    int getPoints(bool Splitted);
    std::vector<std::vector<Card>> hands = {{}, {}};
    void addCard(Card card);
    void addCard(Card card, bool toSplitted);
    void reset();
};
class BJPlayer : public Player
{
public:
    // BJPlayer(Player player);
    BJHand hand;
    unsigned int bet = 0;
    // bool operator==(Player &other);
};

class BlackJack : public Game
{
private:
    std::vector<BJPlayer *> playerBuffor = {};
    std::vector<BJPlayer *> players;
    BJPlayer dealer;
    Deck deck;
    // int getBet();

public:
    BlackJack(unsigned int nOfStdDecks);
    void startNewDeal();
    void addPlayer(Player *player);
    // void initalDistribiution(); // Distribute one card to each player and take bets
    bool makeMove(Player &player, char decision);
    // void summarise(); // each player: 1.update money and bets 2.Write Score to
    //  buf 3.reset hands
    // void draw();      // draws current state of game (usually after each move and at
    //  the beggining)
    void fakeMenu(); // argmenty menu: tj: 1.header 2. opcje 3. align 4. color 5. function callback mainManager.addUIController(menuController)
};
class BJState
{
public:
    int stateNumber = 0;
    // operator++
};