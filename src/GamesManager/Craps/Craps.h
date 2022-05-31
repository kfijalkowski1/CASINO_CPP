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
#include <exception>
#include <iostream>

#include <chrono>
#include <thread>

class Dice
{
    // class for dice
private:
    unsigned int value = (rand() % 6) + 1;
    void drawDot(ImageBuffer image, Position pos);
    void drawSpace(ImageBuffer image, Position pos);
    void drawEmptyRow(ImageBuffer image, Position pos); // position is starting position
    void drawTwoInRow(ImageBuffer image, Position pos);
    void drawMiddleRow(ImageBuffer image, Position pos);
    void drawLeftRow(ImageBuffer image, Position pos);
    void drawRightRow(ImageBuffer image, Position pos);

public:
    Dice(){};
    unsigned int getValue() const noexcept;
    void roll() noexcept;

    bool operator==(unsigned int const &value) const noexcept;

    // opetarions for drawing a Dice
    void draw(int x = 0, int y = 0); // x and y are the beggining positions for draw
};

class Dices
{
    // normaly there are always two dices used, but for futhure expend, it's a dices vector
private:
    std::vector<Dice> dices;

public:
    // wektor obiektów klay dice, każda kość ma draw
    Dices(){};
    void roll();
    void draw(); // donno if ness yet
    std::vector<Dice> getDices();
    unsigned int sum();
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
    void setBets(unsigned int bet, unsigned int betType, unsigned int bet1, unsigned int bet2);
    Score giveDices(Dices dices);
};

class Craps : public Game
{
private:
    unsigned int gameId = 444;
    Dices dices;
    std::vector<CrPlayer> players;

public:
    Craps(std::vector<CrPlayer> players);
    Craps(std::vector<Player> players);
    Craps(){};
    void addPlayer(Player &player);
    void summarise();
    void startNewDeal();
    // draw -> cały stan na ekran,
};
