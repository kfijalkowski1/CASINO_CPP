#include <string>
#include <vector>

const std::vector<std::string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};                           // Trefl, Karo, Kier, Pik
const std::vector<std::string> values = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}; // 10 ruins char idea...

class Card
{
private:
    unsigned int number; // 2-10 numbers, 11 - Jack, 12 - Queen, 13 - King, 14 - Ace                    why unsigned __int8 does not work?!!!!!!!!
    unsigned int suit;   // why int and not string? When dealing with large number of games -> even larger number of decks -> even larger number of cards...

public:
    Card(unsigned int number, unsigned int suit);
    Card(std::string number, std::string suit);
    Card(std::string representation);
    unsigned int getNumber();
    unsigned int getSuit();
    std::string to_string();
    //~Card();
};
class Deck
{
private:
    bool withJoker = false;
    // size_t  nCardsLeft = 52;
    // size_t  nStandardDecks = 1;
    std::vector<Card> cards;
    std::vector<Card> usedCards;

public:
    Deck();
    Deck(bool withJoker, unsigned int nOfStdDecks);
    Deck(bool withJoker, std::vector<Card>);
    void shuffle();

    //~Deck();
};
