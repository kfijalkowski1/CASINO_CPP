#pragma once
#include "GamesManager/Cards/Cards.h"
#include "GamesManager/Game/Game.h"
#include "BJPlayer/BJPlayer.h"

enum class State
{
    mainMenu,
    setBetMenu,
    decisionMenu,
    result,
    errorBet,
    exit
};

class BlackJack : public Game
{
private:
    Deck deck;
    State state;

    BJPlayer dealer;
    BJPlayer player;

    void processDecision(unsigned int dec);
    void processMainMenu(unsigned int dec);
    void processBet(std::string bet);

public:
    ImageBuffer img;
    BlackJack(Player &player, unsigned int nOfStdDecks);

    void tick();
};
