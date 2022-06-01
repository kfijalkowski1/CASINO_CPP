// Craps is a dice game in which players bet on the outcomes of a pair of dice
// Players can wager money against each other.
// the rules are:
// you can bet on 3 diff things:
// sum, pair(eg. 2, 2), specific(eg. 1, 2)

#pragma once
#include "GamesManager/Game/Game.h"
#include "UserManager/Player/Player.h"
#include "GraphicsManager/GraphicsManager.h"
#include "UserManager/Player/Player.h"
#include "MainManager/MainManager.h"
#include "UIController/SelectionMenu/SelectionMenu.h"
#include "UIController/TextInputMenu/TextInputMenu.h"
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

#include <chrono>
#include <thread>

class Dice
{
    // class for dice
private:
    void drawDot(ImageBuffer &image, Position pos);
    void drawSpace(ImageBuffer &image, Position pos);
    void drawEmptyRow(ImageBuffer &image, Position pos); // position is starting position
    void drawTwoInRow(ImageBuffer &image, Position pos);
    void drawMiddleRow(ImageBuffer &image, Position pos);
    void drawLeftRow(ImageBuffer &image, Position pos);
    void drawRightRow(ImageBuffer &image, Position pos);

public:
    unsigned int value = 0;
    Dice(){};
    void roll() noexcept;
    void setValue(unsigned int a)
    {
        value = a;
    }

    bool operator==(unsigned int const &value) const noexcept;

    // opetarions for drawing a Dice
    void draw(ImageBuffer &img, int x = 5, int y = 5); // x and y are the beggining positions for draw
};

class Dices
{
    // normaly there are always two dices used, but for futhure expend, it's a dices vector
public:
    std::vector<Dice> dices;
    // wektor obiektów klay dice, każda kość ma draw
    Dices(); // constructor pushes two dices into vector
    void addDice();
    void roll();
    void draw(ImageBuffer &img); // donno if ness yet
    std::vector<Dice> getDices();
    unsigned int sum();
};

class CrPlayer
{
public:
    Player *playerPtr;
    CrPlayer(){};
    CrPlayer(Player *player);
    unsigned int bet = 0;      // cach value
    unsigned int betType = 1;  // 1 -> sum, 2 -> pair, 3 -> specific, used for mux of return if win
    unsigned int diceVal1 = 0; // used for specific player bets eg. if sum -> bet1 is sum, if pair -> bet1 is what of
    unsigned int diceVal2 = 0;
    void setBets(unsigned int bet, unsigned int betType, unsigned int bet1, unsigned int bet2);
    void giveDices(Dices dices);
    int result;
};

enum class State // -> stan -> mainMenu -> setBetMenu -> kostki..
{
    mainMenu,
    setBetMenu,
    craps,
    exit,
    result
};

class Craps : public Game
{
private:
    unsigned int gameId = 444;
    unsigned int counter = 0;
    Dices dices;
    // std::vector<CrPlayer *> players;
    CrPlayer crPlayer;
    State state;
    int betsCount = 0;

public:
    ImageBuffer CrapsImage;
    Craps(std::vector<CrPlayer> players);
    Craps(std::vector<Player> players);
    Craps(Player *player);
    Craps(){};

    // Logic methods
    void roll() { dices.roll(); };
    void addPlayer(Player *player);
    void summarise();
    void startNewDeal();

    // IO methods
    void processKeypress(Keypress);
    void drawResult();
    void setBets(std::string bet);
    void setBetsNum(unsigned int type);
    void mainMenu();
    void chooseAction(unsigned int a);
    void tick(); // drows all dices and writes if won
    std::string fakeMenu(std::string message);
    void takeImput(std::string imput, CrPlayer &player);
};
