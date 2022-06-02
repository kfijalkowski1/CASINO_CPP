#pragma once
#include "BJPlayer/BJPlayer.h"
#include "GamesManager/Cards/Cards.h"
#include "GamesManager/Game/Game.h"
#include "GraphicsManager/GraphicsManager.h"
#include "MainManager/MainManager.h"
#include "UIController/SelectionMenu/SelectionMenu.h"
#include "UIController/TextInputMenu/TextInputMenu.h"
#include "UserManager/Player/Player.h"
#include <exception>
#include <iostream>
#include <string>

#include <chrono>
#include <thread>

enum class Status
{
    mainMenu,
    dealerCard,
    setBetMenu,
    decisionMenu,
    animationSlideIn,
    lookAtCards,
    dealerHand,
    animationSlideOut,
    result,
    errorBet,
    exit
};

class BlackJack : public Game
{
  private:
    Status status;

    const static int rowIndex = 10;

    unsigned int counter = 0;

    BJPlayer dealer;
    BJPlayer player;

    void processDecision(unsigned int dec);
    void processMainMenu(unsigned int dec);
    void processBet(std::string bet);
    void processKeypress(Keypress);

    void drawResult();

    int calculateScore();

  public:
    static unsigned gameId;

    Deck deck;
    ImageBuffer img;
    ImageBuffer img_bck;
    BlackJack(Player *player, unsigned int nOfStdDecks);

    void tick();
};
