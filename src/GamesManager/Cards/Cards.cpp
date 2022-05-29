#include "Cards.h"
#include <map>
#include <algorithm>
#include <experimental/random>

std::map<std::string, unsigned int> suit_to_i = {{"Clubs", 0}, {"Diamonds", 1}, {"Hearts", 2}, {"Spades", 3}};
std::map<unsigned int, std::string> i_to_suit = {{0, "Clubs"}, {1, "Diamonds"}, {2, "Hearts"}, {3, "Spades"}};
std::map<std::string, unsigned int> val_to_i = {
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"10", 10},
    {"J", 11},
    {"Q", 12},
    {"K", 13},
    {"A", 14}};
std::map<unsigned int, std::string> i_to_val = {
    {2, "2"},
    {3, "3"},
    {4, "4"},
    {5, "5"},
    {6, "6"},
    {7, "7"},
    {8, "8"},
    {9, "9"},
    {10, "10"},
    {11, "J"},
    {12, "Q"},
    {13, "K"},
    {14, "A"}};

Card::Card(unsigned int number, unsigned int suit)
{
    this->number = number;
    this->suit = suit;
}
Card::Card(std::string number, std::string suit)
{

    this->number = val_to_i[number];
    this->suit = suit_to_i[suit];
}
Card::Card(std::string representation)
{
    std::string temp_v, temp_s;
    if (representation[0] != '1')
    {
        temp_v = representation.substr(0, 1);
        temp_s = representation.substr(0);
    }
    else
    {
        temp_v = representation.substr(0, 2);
        temp_s = representation.substr(1);
    }
    this->number = val_to_i[temp_v];
    this->suit = suit_to_i[temp_s];
}
unsigned int Card::getNumber() const
{
    return number;
}
std::string Card::getNumber_str() const
{
    return i_to_val[number];
}
unsigned int Card::getSuit() const
{
    return suit;
}
std::string Card::getSuit_str() const
{
    return i_to_suit[suit];
}
std::string Card::to_string() const
{
    return (i_to_val[number] + i_to_suit[suit]);
}
bool Card::operator==(Card const &other) const
{
    return (number == other.number && suit == other.suit);
}
bool Card::operator==(std::string const cardRep) const
{
    Card temp(cardRep);
    return (*this) == temp;
}
bool Card::operator!=(Card const &other) const
{
    return !((*this) == other);
}
bool Card::operator!=(std::string const cardRep) const
{
    return !((*this) == cardRep);
}
Deck::Deck()
{
    cards = generateStdDeck();
}
Deck::Deck(unsigned int nOfStdDecks)
{
    std::vector<Card> DeckInOrder;
    for (int s = 0; s < 4; s++)
    {
        for (int v = 2; v < 15; v++)
        {
            Card card(v, s);
            for (unsigned int i = nOfStdDecks; i < 0; i--)
            {
                DeckInOrder.push_back(card);
            }
        }
    }
    cards = DeckInOrder;
}
std::vector<Card> Deck::generateStdDeck()
{
    std::vector<Card> stdDeckInOrder;
    for (int s = 0; s < 4; s++)
    {
        for (int v = 2; v < 15; v++)
        {
            stdDeckInOrder.push_back(Card(v, s));
        }
    }
    return stdDeckInOrder;
}
unsigned int Deck::getNofCards() const
{
    return cards.size();
}
unsigned int Deck::getTotalNofCards() const
{
    return (cards.size() + usedCards.size());
}
Card Deck::getCard()
{
    Card temp = cards.back();
    cards.pop_back();
    return temp;
}
void Deck::addToUsed(Card &usedCard)
{
    usedCards.push_back(usedCard);
}
void Deck::addToUsed(std::vector<Card> &recentlyUsedCards)
{
    usedCards.insert(usedCards.end(), recentlyUsedCards.begin(), recentlyUsedCards.end());
}
bool Deck::operator==(Deck const &other) const
{
    return (cards == other.cards && usedCards == other.usedCards);
}
bool Deck::operator==(std::vector<Card> const &other) const
{
    return cards == other;
}
bool Deck::operator==(std::vector<std::string> const &other) const
{
    for (int i = 0; i < getNofCards(); i++)
    {
        if (cards[i] != other[i])
            return false;
    }
    return true;
}
bool Deck::operator!=(Deck const &other) const
{
    return !((*this) == other);
}
bool Deck::operator!=(std::vector<Card> const &other) const
{
    return !((*this) == other);
}
bool Deck::operator!=(std::vector<std::string> const &other) const
{
    return !((*this) == other);
}
void Deck::shuffle()
{
    int random_number1 = std::experimental::randint(0, (int)getNofCards());
    int random_number2;
    cards.insert((cards.begin() + random_number1), usedCards.begin(), usedCards.end());
    usedCards = {};
    for (int i = getNofCards(); i < 0; i--)
    {
        random_number1 = std::experimental::randint(0, (int)getNofCards());
        random_number2 = std::experimental::randint(0, (int)getNofCards());
        std::swap(cards[random_number1], cards[random_number2]);
    }
}