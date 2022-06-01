#pragma once
#include "GamesManager/Cards/Cards.h"
#include "GamesManager/Game/Game.h"
#include "BJPlayer/BJPlayer.h"
#include "MainManager/MainManager.h"

enum class State
{
    mainMenu,
    setBetMenu,
    decisionMenu,
    animationSlideIn,
    animationSlideOut,
    result,
    errorBet,
    exit
};

class BlackJack : public Game
{
private:
    Deck deck;
    State state;

    const static int rowIndex = 10;

    unsigned int counter = 0;

    BJPlayer dealer;
    BJPlayer player;

    void processDecision(unsigned int dec);
    void processMainMenu(unsigned int dec);
    void processBet(std::string bet);
    void processKeyPress();

    int calculateScore();

public:
    ImageBuffer img;
    ImageBuffer img_bck;
    BlackJack(Player &player, unsigned int nOfStdDecks);

    void tick();
};
