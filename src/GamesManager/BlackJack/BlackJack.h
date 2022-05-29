#pragma once
#include "../Cards/Cards.h"
#include "../Game/Game.h"

/*
    std::string name;
    Rules rules;
    std::vector<Player *> players;
    std::vector<Score> Score_cashe;
    virtual void draw() = 0;
*/

class Decision
{
    // Hit = H, Stand = S, DoubleDown = D, Split = P
public:
    char dec;
};
class BJHand
{
public:
    BJHand();
    bool isSplitted = false;
    std::vector<int> points = {0, 0};
    std::vector<std::vector<Card>> hands = {{}, {}};
    void addCard(Card card);
    void addCard(Card card, bool toSplitted);
    void reset();
};
class BJPlayer : public Player
{
public:
    BJHand hand;
    unsigned int bet = 0;
};

class BlackJack : public Game
{
private:
    BJPlayer dealer;
    Deck deck;

public:
    BlackJack(unsigned int nOfStdDecks);
    void startNewDeal();
    void addPlayer(Player &player);
    void initalDistribiution(); // Distribute one card to each player and take bets
    void makeMove(Player &player, Decision decision);
    void summarise(); // each player: 1.update money and bets 2.Write Score to buf 3.reset hands
    void draw();      // draws current state of game (usually after each move and at the beggining)
};
