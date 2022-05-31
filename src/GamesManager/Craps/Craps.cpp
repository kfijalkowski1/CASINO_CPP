#include "Craps.h"
// METHODES FOR DICE CLASS

unsigned int Dice::getValue() const noexcept
{
    return value;
}

void Dice::roll() noexcept
{
    value = (rand() % 6) + 1;
}

void Dice::drawEmptyRow(ImageBuffer image, Position pos)
{
    for (int i = 0; i < 3; ++i)
    {
        (*this).drawSpace(image, pos);
        pos += Position(1, 0);
    }
    pos += Position(-3, 0);
}

void Dice::drawTwoInRow(ImageBuffer image, Position pos)
{
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawMiddleRow(ImageBuffer image, Position pos)
{
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawLeftRow(ImageBuffer image, Position pos)
{
    (*this).drawDot(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawRightRow(ImageBuffer image, Position pos)
{
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawSpace(image, pos);
    pos += Position(1, 0);
    (*this).drawDot(image, pos);
    pos += Position(-2, 0);
}

void Dice::drawDot(ImageBuffer image, Position pos)
{
    image.setPixel(pos, '✦', Color::RGB(255, 255, 255), Color::RGB(1, 3, 3));
}

void Dice::drawSpace(ImageBuffer image, Position pos)
{
    image.setPixel(pos, ' ', Color::RGB(255, 255, 255), Color::RGB(1, 3, 3));
}

void Dice::draw(int x, int y)
{

    GraphicsManager test(80, 24);
    ImageBuffer image;

    Position pos = Position(x, y);

    switch (value)
    {
    case 1:
        (*this).drawEmptyRow(image, pos);
        pos += Position(0, 1);
        (*this).drawMiddleRow(image, pos);
        pos += Position(0, 1);
        (*this).drawEmptyRow(image, pos);
    case 2:
        (*this).drawLeftRow(image, pos);
        pos += Position(0, 1);
        (*this).drawEmptyRow(image, pos);
        pos += Position(0, 1);
        (*this).drawRightRow(image, pos);
    case 3:
        (*this).drawLeftRow(image, pos);
        pos += Position(0, 1);
        (*this).drawMiddleRow(image, pos);
        pos += Position(0, 1);
        (*this).drawRightRow(image, pos);
    case 4:
        (*this).drawTwoInRow(image, pos);
        pos += Position(0, 1);
        (*this).drawEmptyRow(image, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(image, pos);
    case 5:
        (*this).drawTwoInRow(image, pos);
        pos += Position(0, 1);
        (*this).drawMiddleRow(image, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(image, pos);
    case 6:
        (*this).drawTwoInRow(image, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(image, pos);
        pos += Position(0, 1);
        (*this).drawTwoInRow(image, pos);
    }
    while (true)
    {
        test.show(image);

        test.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    }
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

void Dices::roll()
{
    for (auto d : dices)
    {
        d.roll();
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

CrPlayer::CrPlayer(Player player)
{
    name = player.name;
    id = player.id;
    password = player.password;
    cash = player.cash;
}

void CrPlayer::setBets(unsigned int bet, unsigned int betType, unsigned int bet1, unsigned int bet2)
{
    this->bet = bet;
    this->betType = betType;
    this->bet1 = bet1;
    this->bet2 = bet2;
}
Score CrPlayer::giveDices(Dices dices)
{
    Score resultScore;
    resultScore.gameId = 444;
    resultScore.playerId = this->id;
    if (betType == 1)
    {
        if (dices.sum() == bet1)
        {
            resultScore.score = (bet * 2);
        }
    }
    else if (betType == 2)
    {
        if ((dices.getDices()[0] == bet1) && (dices.getDices()[0] == bet1))
        {
            resultScore.score = (bet * 3);
        }
    }
    else if (betType == 3)
    {
        if ((dices.getDices()[1] == bet1) && (dices.getDices()[0] == bet2))
        {
            resultScore.score = (bet * 4);
        }
    }
    this->cash += resultScore.score;
    return resultScore;
}

void Craps::addPlayer(Player &newPlayer)
{
    CrPlayer newCrplayer(newPlayer);
    players.push_back(newCrplayer);
}

void Craps::startNewDeal()
{
    // rolls dices and asserts if someone won based on PAST SETBETS
    // rly imporatnt, first setBets, then use startNewDeal

    dices.roll();
    for (auto player : players)
    {
        Score tempScore = player.giveDices(dices);
        //@TODO somehow send this tempScore to Score board
    }
}