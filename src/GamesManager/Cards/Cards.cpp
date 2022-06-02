#include "Cards.h"
#include <map>
#include <algorithm>
#include <experimental/random>

std::map<std::string, unsigned int> suit_to_i = {{"Clubs", 0}, {"Diamonds", 1}, {"Hearts", 2}, {"Spades", 3}};
std::map<unsigned int, std::string> i_to_suit = {{0, "Clubs"}, {1, "Diamonds"}, {2, "Hearts"}, {3, "Spades"}};
std::map<unsigned int, char32_t> i_to_symbol = {{0, u'♣'}, {1, u'♦'}, {2, u'♥'}, {3, u'♠'}};
// std::map<unsigned int, char> i_to_symbol = {{0, '!'}, {1, '@'}, {2, '#'}, {3, '$'}};
std::map<char, unsigned int> val_to_i = {
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'1', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14}};
std::map<unsigned int, char> i_to_val = {
    {2, '2'},
    {3, '3'},
    {4, '4'},
    {5, '5'},
    {6, '6'},
    {7, '7'},
    {8, '8'},
    {9, '9'},
    {10, '1'},
    {11, 'J'},
    {12, 'Q'},
    {13, 'K'},
    {14, 'A'}};
Color Card::bck_color = Color::Intensive(7);
Color Card::red = Color::RGB(5, 0, 0);
Color Card::black = Color::Grayscale(0);
Color Card::gray = Color::Grayscale(15);
Card::Card(unsigned int number, unsigned int suit)
{
    this->number = number;
    this->suit = suit;
}
Card::Card(char number, std::string suit)
{

    this->number = val_to_i[number];
    this->suit = suit_to_i[suit];
}

unsigned int Card::getNumber() const
{
    return number;
}
char Card::getNumber_str() const
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
            Card card((unsigned int)v, (unsigned int)s);
            for (unsigned int i = nOfStdDecks; i > 0; i--)
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
            stdDeckInOrder.push_back(Card((unsigned int)v, (unsigned int)s));
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

void Deck::shuffle()
{
    int random_number1 = std::experimental::randint(0, (int)getNofCards());
    int random_number2;
    cards.insert((cards.begin() + random_number1), usedCards.begin(), usedCards.end());
    usedCards = {};
    for (int i = getNofCards(); i > 0; i--)
    {
        random_number1 = std::experimental::randint(0, (int)getNofCards());
        random_number2 = std::experimental::randint(0, (int)getNofCards());
        std::swap(cards[random_number1], cards[random_number2]);
    }
}
bool Deck::checkIfEnough()
{
    return (cards.size() > 50);
}
void Card::draw(ImageBuffer &img, Position pos) // pos of top left corner of such card
{
    draw_frame(img, pos);
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            char c = sprites[number - 2][y][x][0];
            img.setPixel(Position(x + pos.x + 1, y + pos.y + 1), c, getColor(), Card::gray);
        }
    }
}

void Card::draw_frame(ImageBuffer &img, Position pos)
{
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            img.setPixel(Position(x + pos.x, y + pos.y), ' ', getColor(), Card::bck_color);
        }
    }
    img.setPixel(pos, i_to_val[number]);
    img.setPixel(pos + Position(0, 1), i_to_symbol[suit]);
    img.setPixel(pos + Position(4, 3), i_to_symbol[suit]);
    img.setPixel(pos + Position(4, 4), i_to_val[number]);
}
Color &Card::getColor()
{
    if (suit == 0 || suit == 3)
    {
        return Card::black;
    }
    else
        return Card::red;
}

std::vector<std::vector<std::vector<std::string>>> Card::sprites =
    {
        {{"/", "^", ")"}, // 2
         {" ", "/", " "},
         {"L", "_", "_"}},
        {{"-", "-", "#"}, // 3
         {" ", "-", "#"},
         {"_", "_", "#"}},
        {{"/", " ", " "}, // 4
         {"L", "_", "|"},
         {" ", " ", "|"}},
        {{"/", "~", "~"}, // 5
         {"L", "-", "\\"},
         {"_", "_", "/"}},
        {{"/", "~", "~"}, // 6
         {"L", "-", "\\"},
         {"L", "_", "/"}},
        {{"-", "-", "-"}, // 7
         {" ", "/", " "},
         {"/", " ", " "}},
        {{"/", "-", "\\"}, // 8
         {"|", "-", "|"},
         {"\\", "_", "/"}},
        {{"/", "-", "\\"}, // 9
         {"\\", "-", "|"},
         {"_", "_", "/"}},
        {{"|", "[", "]"}, // 10
         {"|", "|", "|"},
         {"|", "[", "]"}},
        {{" ", "-", "|"}, // J
         {" ", " ", "|"},
         {"-", "_", "/"}},
        {{"/", "^", "\\"}, // Q
         {"|", " ", "|"},
         {"\\", "_", "%"}},
        {{"|", " ", "/"}, // K
         {"|", "/", " "},
         {"|", " ", "\\"}},
        {{"/", "^", "\\"}, // A
         {"|", "_", "|"},
         {"|", " ", "|"}}};