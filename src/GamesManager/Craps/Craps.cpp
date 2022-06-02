#include "Craps.h"
// METHODES FOR DICE CLASS

void Dice::roll() noexcept
{
    (*this).value = (rand() % 6) + 1;
}

void Dice::drawEmptyRow(ImageBuffer &image, Position pos)
{
    for (int i = 0; i < 6; ++i)
    {
        (*this).drawSpace(image, pos);
        pos += Position(1, 0);
    }
    pos += Position(-6, 0);
}

void Dice::drawTwoInRow(ImageBuffer &image, Position pos)
{
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-5, 0);
}

void Dice::drawMiddleRow(ImageBuffer &image, Position pos)
{
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-5, 0);
}

void Dice::drawLeftRow(ImageBuffer &image, Position pos)
{
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-5, 0);
}

void Dice::drawRightRow(ImageBuffer &image, Position pos)
{
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-5, 0);
}

void Dice::drawDot(ImageBuffer &image, Position pos)
{
    image.setPixel(pos, U'✦', Color::RGB(1, 2, 3), Color::RGB(5, 5, 5));
}

void Dice::drawSpace(ImageBuffer &image, Position pos)
{
    image.setPixel(pos, ' ', Color::RGB(1, 2, 3), Color::RGB(5, 5, 5));
}

void Dice::draw(ImageBuffer &img, int x, int y) // function for drowing single dice
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

bool Dice::operator==(unsigned int const &value) const noexcept // compere operators for one dice
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

void Dices::draw(ImageBuffer &img) // draw all dices in dices
{
    int x = 0, y = 0;
    for (int i = 0; i < dices.size(); ++i)
    {
        dices[i].draw(img, x, y);
        if (x < 72) // ImageBuffer::width check if not in screen width anymore
        {
            x += 8;
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

void Dices::roll() // change value of every dice to rand value
{
    for (int i = 0; i < dices.size(); ++i)
    {
        dices[i].roll();
    }
};

unsigned int Dices::sum()
{
    unsigned int sum;
    for (int i = 0; i < dices.size(); ++i)
    {
        sum += dices[i].value;
    }
    return sum;
};
std::vector<Dice> Dices::getDices() { return dices; }

// METHODES FOR CR PLAYER

void CrPlayer::giveDices(Dices dices)
{
    Score resultScore;
    resultScore.gameId = 444;
    resultScore.playerId = playerPtr->id;
    if (betType == 1)
    {
        if ((dices.dices[0].value + dices.dices[1].value) == diceVal1)
        {
            resultScore.score = (bet * 2);
        }
    }
    else if (betType == 2)
    {
        if ((dices.getDices()[0] == diceVal1) &&
            (dices.getDices()[0] == diceVal1))
        {
            resultScore.score = (bet * 3);
        }
    }
    else if (betType == 3)
    {
        if ((dices.getDices()[1] == diceVal1) &&
            (dices.getDices()[0] == diceVal2))
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
    mainManager->leaderManager.pushBack(resultScore);
    mainManager->userManager.save();
    result = resultScore.score;
}

// Methods for Craps

void Craps::drawResult()
{
    Position pos(10, 10);
    crPlayer.giveDices(dices);
    std::string mess;
    if (crPlayer.result <= 0)
    {
        mess = "You lost: ";
    }
    else
    {
        mess = "You won: ";
    }
    mess += std::to_string(crPlayer.result);
    mess += " coins";
    CrapsImage.writeText(pos, mess);
}
Craps::Craps(Player *player) : state(State::mainMenu)
{
    crPlayer.playerPtr = player;
}
void Craps::addPlayer(Player *newPlayer) { crPlayer.playerPtr = newPlayer; }

void Craps::chooseAction(unsigned int a)
{
    mainManager->removeUIController();
    if (a == 0)
    {
        state = State::setBetMenu;
        this->betsCount = 0;
        mainManager->addUIController(
            new TextInputMenu(std::bind(&Craps::setBets, this, std::placeholders::_1),
                              Box(10, 0, 70, 24), U"Enter bet amount(cash): "));
    }
    else
    {
        state = State::exit;
        mainManager->removeUIController();
    }
}

void Craps::setBetsNum(unsigned int type)
{
    mainManager->removeUIController();
    mainManager->graphicsManager.clear();
    crPlayer.betType = type + 1;
    betsCount++;
    if (crPlayer.betType == 1)
    {
        mainManager->addUIController(
            new TextInputMenu(std::bind(&Craps::setBets, this, std::placeholders::_1),
                              Box(10, 0, 70, 24), U"Enter sum value: "));
    }
    if (crPlayer.betType == 2)
    {
        mainManager->addUIController(
            new TextInputMenu(std::bind(&Craps::setBets, this, std::placeholders::_1),
                              Box(10, 0, 70, 24), U"Enter one dice value: "));
    }
    if (crPlayer.betType == 3)
    {
        mainManager->addUIController(
            new TextInputMenu(std::bind(&Craps::setBets, this, std::placeholders::_1),
                              Box(10, 0, 70, 24), U"Enter one dice num,second dice num: "));
    }
}

void Craps::setBets(std::string bet)
{
    mainManager->removeUIController();
    mainManager->graphicsManager.clear();
    int betNum;
    std::istringstream ss(bet);

    switch (betsCount)
    {
    case 0:
        ss >> betNum;
        if (ss.fail())
        {
            state = State::mainMenu;
            return;
        }
        // betNum = stoi(bet);
        if (crPlayer.playerPtr->cash < betNum)
        {
            state = State::mainMenu;
            return;
        }
        crPlayer.bet = betNum;
        betsCount++;
        // if
        mainManager->addUIController(
            new SelectionMenu(std::bind(&Craps::setBetsNum, this, std::placeholders::_1),
                              Box(10, 0, 70, 24), {U"Sum (try to guess the sum of dices (2-12)", U"Pair", U"Specific Dices"}, U"Bet Type"));
        break;
    case 2:
        state = State::craps;
        if (crPlayer.betType == 3)
        {
            std::size_t pos = bet.find(","); // position of "," in str, for two values
            ++pos;
            crPlayer.diceVal2 = stoi(bet.substr(pos));
            crPlayer.diceVal1 = stoi(bet.substr(0, pos));
            state = State::craps;
            break;
        }
        else if (crPlayer.betType == 2)
        {
            ss >> betNum;
            if (ss.fail())
            {
                state = State::mainMenu;
                return;
            }
            crPlayer.diceVal1 = stoi(bet) / 2;
            if ((crPlayer.diceVal1 > 6) || (crPlayer.diceVal1 < 1))
            {
                state = State::mainMenu;
                return;
            }
            state = State::craps;
            break;
        }
        else if (crPlayer.betType == 1)
        {
            ss >> betNum;
            if (ss.fail())
            {
                state = State::mainMenu;
                return;
            }
            crPlayer.diceVal1 = stoi(bet);
            state = State::craps;
            break;
        }
    }

    //  Secon(SetBet2) -> cout setów -> startRolls -> ustawiam state na Crabs ->
    //  wybieram kosci -> zabieram/ daje monety
}

void Craps::processKeypress(Keypress)
{
    if (state == State::result)
    {
        state = State::mainMenu;
    }
}

void Craps::tick()
{
    if (state == State::mainMenu)
    {
        mainManager->graphicsManager.clear();
        mainManager->addUIController(
            new SelectionMenu(std::bind(&Craps::chooseAction, this, std::placeholders::_1),
                              Box(10, 0, 70, 24), {U"Plaay crabs", U"Quit"}, U"CRAAAAABS")); // globalne menu, choose action doatanie int
    }
    else if (state == State::setBetMenu)
    {
        // MainMenu.. this lines are never gonna be in
    }
    else if (state == State::craps)
    {
        if (counter < 80)
        {
            if (counter % 3 == 0)
            {
                dices.roll();
            }
        }
        dices.draw(CrapsImage);
        mainManager->graphicsManager.show(CrapsImage);
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
        mainManager->graphicsManager.show(CrapsImage);
    }
    else if (state == State::exit)
    {
        mainManager->removeUIController();
    }
}