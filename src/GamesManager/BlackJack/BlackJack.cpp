#include "BlackJack.h"
#include <iostream>

#include <string>

BlackJack::BlackJack(Player &player, unsigned int nOfStdDecks)
{
    BJPlayer temp(player);
    this->player = temp;
    Deck deck1(nOfStdDecks);
    deck = deck1;
}

void BlackJack::processDecision(unsigned int dec)
{
    // returns true if next player
    switch (dec)
    {
    case 0:
        // Hit
        // update hand, checkHand, makeMove
        break;
    case 1:
        // Stand
        // go to next Player, makeMove
        break;
    default:
        throw "Nie ma takiej opcji!";
    }
}

void BlackJack::processMainMenu(unsigned int dec)
{
    switch (dec)
    {
    case 0: // Play
        break;
    case 1: // Exit
        break;
    default:
        break;
    }
}
void BlackJack::processBet(std::string bet)
{
    int bet_int = std::stoi(bet);
    if (bet_int > player.player.cash)
    {
        state = State::errorBet;
    }
}
void BlackJack::tick()
{
    switch (state)
    {
    case State::mainMenu:
        // mainManager.addUIController(new SelectionMenu(processMainMenu, Box(0, 0, 80, 24), {U"Play", U"Quit"}, U"BlackJack"));
        break;
    case State::setBetMenu:
        // mainManager.addUIController(new TextInputMenu(processBet, Box(10, 0, 70, 24), U"Enter your bet"));
        break;
    case State::decisionMenu:
        // mainManager.addUIController(new SelectionMenu(processDecision, Box(0, 0, 80, 24), {U"Hit", U"Stand"}, U"What do you do?"));
        break;
    case State::animationSlideIn:
        if (counter > rowIndex)
        {
            img_bck = img;
            state = State::decisionMenu;
            counter = 0;
        }
        else
        {
            img = img_bck;
            size_t size = player.hand.cards.size();
            player.hand.cards[size - 1].draw(img, Position((unsigned int)size, counter));
        }
        counter++;
        break;
    case State::animationSlideOut:
        if (counter <= 75)
        {
            img = img_bck;
            size_t size = player.hand.cards.size();
            for (int i = size; i > 0; i--)
            {
                int x = counter + size;
                if (x <= 75)
                    player.hand.cards[i - 1].draw(img, Position(x, rowIndex));
            }
            counter++;
        }
        else
        {
            state = State::result;
            counter = 0;
        }
    case State::result:
        // int score = calculateScore();
        //  how to convert int to vector<u32_string>;
        //  mainManager.addUIController(new SelectionMenu(processKeyPress, Box(0, 0, 80, 24), {U"Quit"}, U"Variable with your score"));
        break;
    case State::errorBet:
        // MainMenu.UIMenu(ErrorPopUp);
        break;
    case State::exit:
        mainManager.removeUIController();
        break;
    default:
        break;
    }
}

int BlackJack::calculateScore()
{
    int score;
    int points = player.hand.getPoints();
    if (points > 21)
    {
        score = 0;
    }
    else if (points == 21)
    {
        score = player.bet * 3 / 2;
    }
    else
        score = player.bet;
    return score;
}

void BlackJack::processKeyPress()
{
    if (state == State::result)
    {
        state = State::mainMenu;
    }
}