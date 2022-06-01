#pragma once
#include <string>
#include <vector>
#include "GraphicsManager/GraphicsManager.h"

enum class Suit
{
    Clubs,
    Diamonds,
    Hearts,
    Spades
};
const std::vector<std::string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};                           // Trefl, Karo, Kier, Pik
const std::vector<std::string> values = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}; // 10 ruins char idea...

class Card
{
private:
    unsigned int number; // 2-10 numbers, 11 - Jack, 12 - Queen, 13 - King, 14 - Ace                    why unsigned __int8 does not work?!!!!!!!!
    unsigned int suit;   // why int and not string? When dealing with large number of games -> even larger number of decks -> even larger number of cards...
    static Color bck_color;
    static Color red;
    static Color black;
    static Color gray;
    static std::vector<std::vector<std::vector<std::string>>> sprites;
    Color &getColor();
    void draw_frame(ImageBuffer &img, Position pos);

public:
    Card(unsigned int number, unsigned int suit);
    Card(char number, std::string suit);
    // Card(std::string representation);
    unsigned int getNumber() const;
    char getNumber_str() const;
    unsigned int getSuit() const;
    std::string getSuit_str() const;
    std::string to_string() const;

    // bool operator==(Card const &other) const;
    //  bool operator==(std::string const cardRep) const;
    // bool operator!=(Card const &other) const;
    //  bool operator!=(std::string const cardRep) const;

    //~Card();
    void draw(ImageBuffer &img, Position pos);
};
class Deck
{
private:
    // bool withJoker = false;
    //  size_t  nCardsLeft = 52;
    //  size_t  nStandardDecks = 1;
    std::vector<Card> cards;
    std::vector<Card> usedCards = {};

    std::vector<Card> generateStdDeck();

public:
    Deck();
    Deck(unsigned int nOfStdDecks);

    // Deck(bool withJoker, unsigned int nOfStdDecks);
    // Deck(std::vector<Card>);
    bool checkIfEnough();
    void shuffle();
    unsigned int getNofCards() const;
    unsigned int getTotalNofCards() const;
    // void use(Card cardToUse);
    Card getCard();
    // Card getCard(int index);
    void addToUsed(Card &usedCard);
    void addToUsed(std::vector<Card> &usedCards);

    // Deck operator+(Deck &other);
    // void operator+=(Deck &other);
    // void operator-=(Card &cardToUse);

    // bool operator==(Deck const &other) const;
    // bool operator==(std::vector<Card> const &other) const;
    // bool operator==(std::vector<std::string> const &other) const;
    // bool operator!=(Deck const &other) const;
    // bool operator!=(std::vector<Card> const &other) const;
    // bool operator!=(std::vector<std::string> const &other) const;

    //~Deck();
    // void draw(Position pos);
};
