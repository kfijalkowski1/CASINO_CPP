#pragma once
#include <string>
#include <vector>
#include "GraphicsManager/GraphicsManager.h"

class Card
{
private:
    static std::vector<std::vector<std::vector<std::string>>> sprites;
    static std::map<unsigned int, char32_t> i_to_symbol;
    static std::map<unsigned int, char> i_to_val;
    unsigned int number; // 2-10 numbers, 11 - Jack, 12 - Queen, 13 - King, 14 - Ace
    unsigned int suit;   // why int and not string? When dealing with large number of games -> even larger number of decks -> even larger number of cards...
    static Color bck_color;
    static Color red;
    static Color black;
    static Color gray;
    Color &getColor();
    void draw_frame(ImageBuffer &img, Position pos);

public:
    Card(unsigned int number, unsigned int suit);
    unsigned int getNumber() const;

    void draw(ImageBuffer &img, Position pos);
};
class Deck
{
private:
    std::vector<Card> cards;
    std::vector<Card> usedCards = {};

    std::vector<Card> generateStdDeck();

public:
    Deck();
    Deck(unsigned int nOfStdDecks);

    bool checkIfEnough();
    void shuffle();
    unsigned int getNofCards() const;
    unsigned int getTotalNofCards() const;
    Card getCard();
    void addToUsed(Card &usedCard);
    void addToUsed(std::vector<Card> &usedCards);
};
