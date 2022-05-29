#pragma once
#include "../Cards/Cards.h"
#include "../Game/Game.h"

/*
    std::string name;
    Rules rules;
    std::vector<Player> players;
    std::vector<Score> Score_cashe;
    virtual void draw() = 0;
*/

class Decision
{
public:
};
class BJHand
{
public:
    std::vector<Card> hand;
    void addCard(Card card);
    void clear();
    int sumPoints();
};
class BJPlayer : public Player
{
private:
    BJHand hand;
};

class BlackJack : public Game
{
private:
    Player dealer();

public:
    BlackJack();
    void addPlayer(Player &player);
    void initalDistribiution();
    void makeMove(Player &player, Decision decision);
};
