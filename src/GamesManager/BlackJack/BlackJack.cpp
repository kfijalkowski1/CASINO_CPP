#include "BlackJack.h"
#include <iostream>

#include <string>

unsigned int BlackJack::gameId = 777;

BlackJack::BlackJack(Player *player, unsigned int nOfStdDecks)
    : status(Status::mainMenu), player(player)
{
    Deck deck1(nOfStdDecks);
    deck = deck1;
    deck.shuffle();
}

void BlackJack::processDecision(unsigned int dec)
{
    mainManager->removeUIController();
    switch (dec)
    {
    case 0: // hit
        player.hand.addCard(deck.getCard());
        status = Status::animationSlideIn;
        break;
    case 1: // Stand
        counter = 0;
        status = Status::dealerHand;
        dealer.hand.addCard(deck.getCard());
        break;
    case 2: // look at cards
        status = Status::lookAtCards;
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
        player.hand.cards = {};
        counter = 0;
        status = Status::dealerCard;
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

    if (bet_int > player.player->cash)
    {
        status = Status::errorBet;
    }
    else
    {
        if (player.player->cash < bet_int)
            status = Status::errorBet;
        else
        {
            player.player->cash -= bet_int;
            player.bet = bet_int;
            mainManager->userManager.save();

            player.hand.addCard(deck.getCard());
            status = Status::animationSlideIn;
        }
    }
}
void BlackJack::tick()
{
    switch (status)
    {
    case Status::mainMenu:
        mainManager->graphicsManager.clear();
        mainManager->addUIController(new SelectionMenu(
            std::bind(&BlackJack::processMainMenu, this, std::placeholders::_1),
            Box(0, 0, 80, 24), {U"Play", U"Quit"}, U"BlackJack"));
        break;
    case Status::dealerCard:
        if (counter == 0)
        {
            dealer.hand.addCard(deck.getCard());
            dealer.hand.cards[0].draw(img, Position(0, 0));
            img_bck = img;
            counter++;
        }
        else if (counter < 100)
        {
            mainManager->graphicsManager.show(img);
            counter++;
        }
        else
        {
            status = Status::setBetMenu;
            counter = 0;
        }
        break;
    case Status::setBetMenu:
        mainManager->addUIController(new TextInputMenu(
            std::bind(&BlackJack::processBet, this, std::placeholders::_1),
            Box(30, 0, 50, 24), U"Enter your bet"));
        break;
    case Status::decisionMenu:
        mainManager->addUIController(new SelectionMenu(
            std::bind(&BlackJack::processDecision, this, std::placeholders::_1),
            Box(30, 8, 50, 16), {U"Hit", U"Stand", U"Look at cards"},
            U"What do you do?"));
        break;
    case Status::animationSlideIn:
        if (counter > 180)
        {
            img_bck = img;
            if (player.hand.getPoints() >= 21)
            {
                counter = 0;
                status = Status::dealerHand;
                dealer.hand.addCard(deck.getCard());
            }
            else
                status = Status::decisionMenu;
            counter = 0;
        }
        else
        {
            img = img_bck;
            size_t size = player.hand.cards.size();
            player.hand.cards[size - 1].draw(
                img, Position((unsigned int)(size - 1) * 3,
                              ((unsigned int)counter / 10)));
            mainManager->graphicsManager.show(img);
        }
        counter++;
        break;
    case Status::lookAtCards:
        if (counter < 100)
        {
            mainManager->graphicsManager.show(img);
            counter++;
        }
        else
        {
            status = Status::decisionMenu;
            counter = 0;
        }
        break;
    case Status::dealerHand:
        if (counter <= 30)
        {
            img = img_bck;
            size_t size = dealer.hand.cards.size();
            dealer.hand.cards[size - 1].draw(
                img, Position((unsigned int)(size - 1) * 3, 0));
            mainManager->graphicsManager.show(img);
            counter++;
        }
        else
        {
            img_bck = img;
            if (dealer.hand.getPoints() > 16)
            {
                status = Status::animationSlideOut;
                auto box = Box(0, ImageBuffer::height - 10, ImageBuffer::width,
                               ImageBuffer::height);
                img_bck.drawBoxCharacter(box, U' ');
                img_bck.drawBoxColor(box, Color::Default);
                img_bck.drawBoxBackground(box, Color::DefaultBackground);
            }
            else
            {
                dealer.hand.addCard(deck.getCard());
            }
            counter = 0;
        }
        break;
    case Status::animationSlideOut:
        if (counter <= 70)
        {
            img = img_bck;
            size_t size = player.hand.cards.size();
            for (int i = size - 1; i >= 0; i--)
            {
                int x = counter + size - i;
                if (x <= 75)
                    player.hand.cards[size - i - 1].draw(img, Position(x, 18));
            }
            mainManager->graphicsManager.show(img);
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
        status = Status::mainMenu;
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
    int plyPoints = player.hand.getPoints();
    int dlrPoints = dealer.hand.getPoints();
    if (plyPoints > 21)
        score = 0;
    else if (plyPoints < 21)
    {
        if (dlrPoints < plyPoints)
            score = 2 * player.bet;
        else
            score = 0;
    }
    else
        score = (player.bet) * 5 / 2;
    return score;
}

void BlackJack::processKeypress(Keypress)
{
    if (status == Status::result)
    {
        dealer.hand.cards = {};
        img = ImageBuffer();
        img_bck = ImageBuffer();
        status = Status::mainMenu;
    }
}
void BlackJack::drawResult()
{
    int score = calculateScore();
    player.player->cash += score;
    mainManager->userManager.save();

    Score leaderBoardScore = Score();
    leaderBoardScore.gameId = BlackJack::gameId;
    leaderBoardScore.score = score;
    leaderBoardScore.playerId = player.player->id;

    mainManager->leaderManager.pushBack(leaderBoardScore);

    std::string mess;
    if (score == 0)
    {
        mess = "You lost: ";
    }
    else
    {
        mess = "You won: ";
    }
    mess += std::to_string(score);
    mess += " coins";

    std::string dealerPointString =
        "Dealer has: " + std::to_string(dealer.hand.getPoints()) + " points";
    std::string playerPointString =
        "Player has: " + std::to_string(player.hand.getPoints()) + " points";

    Position row = Position(0, ImageBuffer::height / 2 - 2);
    img.writeText(Box(row, row + Position(ImageBuffer::width, 0)),
                  dealerPointString, ImageBuffer::TextAlignment::center);
    row += Position(0, 1);
    img.writeText(Box(row, row + Position(ImageBuffer::width, 0)),
                  playerPointString, ImageBuffer::TextAlignment::center);
    row += Position(0, 2);
    img.writeText(Box(row, row + Position(ImageBuffer::width, 0)), mess,
                  ImageBuffer::TextAlignment::center);
}