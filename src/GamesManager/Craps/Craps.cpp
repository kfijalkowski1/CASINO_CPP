#include "Craps.h"
// METHODES FOR DICE CLASS

unsigned int Dice::getValue() const noexcept
{
    return value;
}

void Dice::roll() noexcept
{
    srand(rand());
    (*this).value = (rand() % 6) + 1;
}

void Dice::drawEmptyRow(ImageBuffer &image, Position pos)
{
    for (int i = 0; i < 3; ++i)
    {
        (*this).drawSpace(image, pos);
        pos += Position(1, 0);
    }
    pos += Position(-3, 0);
}

void Dice::drawTwoInRow(ImageBuffer &image, Position pos)
{
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawMiddleRow(ImageBuffer &image, Position pos)
{
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawLeftRow(ImageBuffer &image, Position pos)
{
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawRightRow(ImageBuffer &image, Position pos)
{
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawDot(ImageBuffer &image, Position pos)
{
    image.setPixel(pos, U'⦿', Color::RGB(1, 2, 3), Color::RGB(5, 5, 5));
}

void Dice::drawSpace(ImageBuffer &image, Position pos)
{
    image.setPixel(pos, ' ', Color::RGB(1, 2, 3), Color::RGB(5, 5, 5));
}

void Dice::draw(ImageBuffer &img, int x, int y)
{
    Position pos = Position(x, y);

    switch (value)
    {
    case 1:
        (*this).drawEmptyRow(img, pos);
        pos += Position(0, 1);
        (*this).drawMiddleRow(img, pos);
        pos += Position(0, 1);
        (*this).drawEmptyRow(img, pos);
        break;
    case 2:
        (*this).drawLeftRow(img, pos);
        pos += Position(0, 1);
        (*this).drawEmptyRow(img, pos);
        pos += Position(0, 1);
        (*this).drawRightRow(img, pos);
        break;
    case 3:
        (*this).drawLeftRow(img, pos);
        pos += Position(0, 1);
        (*this).drawMiddleRow(img, pos);
        pos += Position(0, 1);
        (*this).drawRightRow(img, pos);
        break;
    case 4:
        (*this).drawTwoInRow(img, pos);
        pos += Position(0, 1);
        (*this).drawEmptyRow(img, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(img, pos);
        break;
    case 5:
        (*this).drawTwoInRow(img, pos);
        pos += Position(0, 1);
        (*this).drawMiddleRow(img, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(img, pos);
        break;
    case 6:
        (*this).drawTwoInRow(img, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(img, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(img, pos);
        break;
    }
}

bool Dice::operator==(unsigned int const &value) const noexcept
{
    return this->value == value;
}

// METHODS FOR DICES

Dices::Dices()
{
    Dice temp1;
    Dice temp2;
    dices.push_back(temp1);
    dices.push_back(temp2);
}

void Dices::draw(ImageBuffer &img)
{
    int x = 0, y = 0;
    for (int i = 0; i < dices.size(); ++i)
    {
        dices[i].draw(img, x, y);
        if (x < 72) // ImageBuffer::width check if not in screen width anymore
        {
            x += 4;
        }
        else
        {
            x = 0;
            y += 4;
        }
    }
}

void Dices::addDice()
{
    Dice temp;
    dices.push_back(temp);
}

void Dices::roll()
{
    for (int i = 0; i < dices.size(); ++i)
    {
        dices[i].roll();
    }
};

unsigned int Dices::sum()
{
    unsigned int sum;
    for (auto d : dices)
    {
        sum += d.getValue();
    }
    return sum;
};
std::vector<Dice> Dices::getDices()
{
    return dices;
}

// METHODES FOR CR PLAYER

// static void CrPlayer::setBets(unsigned int bet, unsigned int betType, unsigned int bet1, unsigned int bet2)
// {
//     this->bet = bet;
//     this->betType = betType;
//     this->diceVal1 = bet1;
//     this->diceVal2 = bet2;
// }
void CrPlayer::giveDices(Dices dices)
{
    Score resultScore;
    resultScore.gameId = 444;
    resultScore.playerId = playerPtr->id;
    if (betType == 1)
    {
        if (dices.sum() == diceVal1)
        {
            resultScore.score = (bet * 2);
        }
    }
    else if (betType == 2)
    {
        if ((dices.getDices()[0] == diceVal1) && (dices.getDices()[0] == diceVal1))
        {
            resultScore.score = (bet * 3);
        }
    }
    else if (betType == 3)
    {
        if ((dices.getDices()[1] == diceVal1) && (dices.getDices()[0] == diceVal2))
        {
            resultScore.score = (bet * 4);
        }
    }
    if (resultScore.score == 0)
    {
        playerPtr->cash -= bet;
        result = -1 * bet;
    }
    playerPtr->cash += resultScore.score;
    // Save score to LBMenager
    result = resultScore.score;
}

// Methods for Craps

void Craps::drawResult()
{
    Position pos(20, 20);
    crPlayer.giveDices(dices);
    std::string mess;
    if (crPlayer.result < 0)
    {
        std::string mess = "You lost: ";
    }
    else
    {
        std::string mess = "You won: ";
    }
    mess += std::to_string(crPlayer.result);
    mess += " coins";
    CrapsImage.writeText(pos, mess);
}
Craps::Craps(Player *player)
{
    crPlayer.playerPtr = player;
}
void Craps::addPlayer(Player *newPlayer)
{
    crPlayer.playerPtr = newPlayer;
}

void Craps::chooseAction(unsigned int a)
{
    mainManager.removeUIController();
    if (a == 0)
    {
        state = State::setBetMenu;
        mainManager.addUIController(new TextInputMenu(
            setBets, Box(10, 0, 70, 24), U"Enter bet amount(cash): "));
    }
    else
    {
        state = State::exit;
        mainManager.removeUIController();
    }
}

void Craps::setBets(std::string bet)
{
    mainManager.removeUIController();
    int betNum;
    switch (betsCount)
    {
    case 0:
        betNum = stoi(bet);
        crPlayer.bet = betNum;
        betsCount++;
        mainManager.addUIController(new TextInputMenu(
            setBets, Box(10, 0, 70, 24), U"Enter bet type(1->sum, 2->pair, 3->specific)): "));
        break;
    case 1:
        betNum = stoi(bet);
        crPlayer.betType = betNum;
        betsCount++;
        if (crPlayer.betType == 1)
        {
            mainManager.addUIController(new TextInputMenu(
                setBets, Box(10, 0, 70, 24), U"Enter sum value: "));
        }
        if (crPlayer.betType == 2)
        {
            mainManager.addUIController(new TextInputMenu(
                setBets, Box(10, 0, 70, 24), U"Enter one dice value: "));
        }
        if (crPlayer.betType == 3)
        {
            mainManager.addUIController(new TextInputMenu(
                setBets, Box(10, 0, 70, 24), U"Enter one dice num,second dice num: "));
        }
        break;
    case 2:
        if (crPlayer.betType == 3)
        {
            std::size_t pos = bet.find(","); // position of "live" in str
            ++pos;
            crPlayer.diceVal2 = stoi(bet.substr(pos));
            crPlayer.diceVal1 = stoi(bet.substr(0, pos));
            break;
        }
        if (crPlayer.betType == 2)
        {
            crPlayer.diceVal1 = stoi(bet) / 2;
            break;
        }
        if (crPlayer.betType == 1)
        {
            crPlayer.diceVal1 = stoi(bet);
            break;
        }
    }
    mainManager.removeUIController();
    state = State::craps;
    //  Secon(SetBet2) -> cout setów -> startRolls -> ustawiam state na Crabs -> wybieram kosci -> zabieram/ daje monety
}

void Craps::processKeyPress(KeyPress)
{
    if (state == State::Result)
    {
        state = State::mainMenu;
    }
}

void Craps::tick()
{
    if (state == State::mainMenu)
    {
        mainManager.addUIController(new SelectionMenu(
            chooseAction, Box(0, 0, 80, 24), {U"Play crabes", U"Quit"}, U"Crabes")); // globalne menu, choose action doatanie int
    }
    else if (state == State::setBetMenu)
    {
        // MainMenu.. this lines are never gonna be in
    }
    else if (state == State::craps)
    {
        while (counter < 80)
        {
            dices.roll();
            dices.draw(CrapsImage);
        }
        dices.draw(CrapsImage);
        mainManager.graphicsManager.show(CrapsImage);
        counter++;
        if (counter > 100)
        {
            counter = 0;
            drawResult();
            state = State::result;
        }
    }
    else if (state == State::result)
    {
        mainManager.graphicsManager.show(CrapsImage);
    }
    else if (state == State::exit)
    {
        mainManager.removeUIController();
    }
}