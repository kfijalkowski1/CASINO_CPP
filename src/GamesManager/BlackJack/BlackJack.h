#pragma once
#include "GamesManager/Cards/Cards.h"
#include "GamesManager/Game/Game.h"

class BJState
{
public:
    int stateNumber = 0;
    int playerIndex = 0;
};
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

    BJPlayer dealer;
    Deck deck;

    BJState state;

    void hit();
    void doubleDown();
    // void split();

public:
    std::vector<BJPlayer *> players; // private
    BlackJack(unsigned int nOfStdDecks);
    void startNewDeal();
    ImageBuffer img;

    void choice(int i);

    void startChoice(int i);
    void BetChoice(int i);
    void actionChoice(int i);

    void addPlayer(Player *player);
    // void initalDistribiution(); // Distribute one card to each player and take bets
    bool makeMove(Player &player, char decision);
    // void summarise(); // each player: 1.update money and bets 2.Write Score to
    //  buf 3.reset hands
    // void draw();      // draws current state of game (usually after each move and at
    //  the beggining)
    void fakeMenu(); // argmenty menu: tj: 1.header 2. opcje 3. align 4. color 5. function callback(int i) mainManager.addUIController(menuController)
    void draw(ImageBuffer &img, Position pos);
};
