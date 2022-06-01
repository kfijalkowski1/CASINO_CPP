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
    image.setPixel(pos, '*', Color::RGB(1, 2, 3), Color::RGB(5, 5, 5));
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
    // while (true)
    // {
    //     test.show(img);

    //     test.draw();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    // }
    // catch (std::exception &e)
    // {
    //     std::cout << "Standard exception: " << e.what() << std::endl;
    // }
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
        if (x < ImageBuffer::width) // check if not in screen width anymore
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

// CrPlayer::CrPlayer(Player player)
// {
//     name = player.name;
//     id = player.id;
//     password = player.password;
//     cash = player.cash;
// }

void CrPlayer::setBets(unsigned int bet, unsigned int betType, unsigned int bet1, unsigned int bet2)
{
    this->bet = bet;
    this->betType = betType;
    this->diceVal1 = bet1;
    this->diceVal2 = bet2;
}
Score CrPlayer::giveDices(Dices dices)
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
    }
    playerPtr->cash += resultScore.score;
    return resultScore;
}

void Craps::addPlayer(Player *newPlayer)
{
    // CrPlayer *newCrplayerPtr = dynamic_cast<CrPlayer *>(newPlayer); do wyjebbanie
    // players.push_back(newCrplayerPtr); TODO
}

void Craps::startNewDeal()
{
    // rolls dices and asserts if someone won based on PAST SETBETS
    // rly imporatnt, first setBets, then use startNewDeal

    // TODO take bets and somehow recive them
    // std::string dec = fakeMenu();
    // fakeMenu("Enter bet amount", crPleyerEnterBet());

    dices.roll();
    (*this).draw();
    Score scrore = crPlayer.giveDices(dices);

    // LBMenager.pushBack(score);
    //(*this).drawResult()

    // fakeMenu(You won/lost  amount)
}

void Craps::mainMenu()
{
    switch (state)
    {
    case 0:
        // MainMe...show(ChooseAction);
        break;
    case 1:
        // MainMe..Bets..show();
    default:
        break;
    }
}

void Craps::chooseAction(unsigned int a)
{
    // UI..kill..yrs
    if (a == 0)
    {
        state = State::setBetMenu;
        // SecondMenu.........(SetBet1)
    }
    else
    {
        state = State::exit;
        // UI..kill..yrs
    }
}

void Craps::SetBet1()
{
    // UI..kill
    // if
    // SecondMenu
    //  player -> se
    //  Secon(SetBet2) -> cout setów -> startRolls -> ustawiam state na Crabs -> wybieram kosci -> zabieram/ daje monety
    // end if

    state = State::craps;
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
        // MainMenu...(chooseAction)     // globalne menu, choose action doatanie int
    }
    else if (state == State::setBetMenu)
    {
        // MainMenu..
    }
    else if (state == State::crabs)
    {
        dices.draw(CrapsImage);
        // UI...Show..(CrabsImage)
        counter++;
        if (counter > 100):
            state = State::Reasult;
        else if (state == State::result)
        {
            // rysuje i robie show result
        }
    }
}