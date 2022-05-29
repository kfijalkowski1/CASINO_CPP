// Craps is a dice game in which players bet on the outcomes of a pair of dice
// Players can wager money against each other.
// the rules are:
// you can bet on 3 diff things:
// sum, pair(eg. 2, 2), specific(eg. 1, 2)

#pragma once
#include "../Cards/Cards.h"
#include "../Game/Game.h"
class Dices
{
    // there are always two dices and they are just 2 radnom num in 0-6 range
public:
    unsigned int dice1 = rand() % 6;
    unsigned int dice2 = rand() % 6;

    Dices(){};
    void roll()
    {
        dice1 = rand() % 6;
        dice2 = rand() % 6;
    }
};
class CrPlayer : public Player
{
public:
    CrPlayer();
    CrPlayer(Player player);
    unsigned int bet = 0;
    unsigned int betType = 1; // 1 -> sum, 2 -> pair, 3 -> specific, used for mux of return if win
    unsigned int bet1 = 0;    // used for specific player bets eg. if sum -> bet1 is sum, if pair -> bet1 is what of
    unsigned int bet2 = 0;
    void setBets(unsigned int bet, unsigned int betType, unsigned int bet1, unsigned int bet2 = 0);
    Score giveDices(unsigned int dice1, unsigned int dice2);
};

class Craps : public Game
{
private:
    unsigned int gameId = 444;
    Dices dices;
    std::vector<CrPlayer> players;

public:
    Craps(std::vector<CrPlayer> players)
    {
        this->players = players;
    }
    Craps(){};
    void addPlayer(Player &player);
    void summarise();
    void startNewDeal();
};
