#include "BlackJack.h"
#include <iostream>

#include <string>

BlackJack::BlackJack(Player &player, unsigned int nOfStdDecks)
    : status(Status::mainMenu)
{
    BJPlayer temp(player);
    this->player = temp;
    Deck deck1(nOfStdDecks);
    deck = deck1;
}

void BlackJack::processDecision(unsigned int dec)
{
    mainManager->removeUIController();
    // returns true if next player
    switch (dec)
    {
    case 0: // hit
        player.hand.addCard(deck.getCard());
        status = Status::animationSlideIn;
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
    mainManager->removeUIController();
    switch (dec)
    {
    case 0: // Play
        status = Status::setBetMenu;
        break;
    case 1: // Exit
        mainManager->removeUIController();
        break;
    default:
        break;
    }
}
void BlackJack::processBet(std::string bet)
{
    mainManager->removeUIController();
    int bet_int = std::stoi(bet);
    if (bet_int > player.player.cash)
    {
        status = Status::errorBet;
    }
    else
    {
        player.player.cash -= bet_int;
        status = Status::decisionMenu;
    }
}
void BlackJack::tick()
{
    switch (status)
    {
    case Status::mainMenu:
        mainManager->addUIController(new SelectionMenu(
            std::bind(&BlackJack::processMainMenu, this, std::placeholders::_1),
            Box(0, 0, 80, 24), {U"Play", U"Quit"}, U"BlackJack"));
        break;
    case Status::setBetMenu:
        mainManager->addUIController(new TextInputMenu(
            std::bind(&BlackJack::processBet, this, std::placeholders::_1),
            Box(10, 0, 70, 24), U"Enter your bet"));
        break;
    case Status::decisionMenu:
        mainManager->addUIController(new SelectionMenu(
            std::bind(&BlackJack::processDecision, this, std::placeholders::_1),
            Box(0, 0, 80, 24), {U"Hit", U"Stand"}, U"What do you do?"));
        break;
    case Status::animationSlideIn:
        if (counter > 180)
        {
            img_bck = img;
            status = Status::decisionMenu;
            counter = 0;
        }
        else
        {
            img = img_bck;
            size_t size = player.hand.cards.size();
            player.hand.cards[size - 1].draw(
                img,
                Position((unsigned int)size, ((unsigned int)counter / 10)));
            mainManager->graphicsManager.show(img);
        }
        counter++;
        break;
    case Status::animationSlideOut:
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
            status = Status::result;
            counter = 0;
            drawResult();
        }
    case Status::result:
        mainManager->graphicsManager.show(img);
        break;
    case Status::errorBet:
        // MainMenu.UIMenu(ErrorPopUp);
        break;
    case Status::exit:
        mainManager->removeUIController();
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

void BlackJack::processKeypress(Keypress)
{
    if (status == Status::result)
    {
        status = Status::mainMenu;
    }
}
void BlackJack::drawResult()
{
    Position pos(10, 0);
    int score = calculateScore();
    std::string mess;
    if (score == 0)
    {
        std::string mess = "You lost: ";
    }
    else
    {
        std::string mess = "You won: ";
    }
    mess += std::to_string(score);
    mess += " coins";
    img.writeText(pos, mess);
}