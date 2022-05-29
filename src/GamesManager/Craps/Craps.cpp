#include "Craps.h"

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
Score CrPlayer::giveDices(unsigned int dice1, unsigned int dice2)
{
    Score resultScore;
    resultScore.gameId = 444;
    resultScore.playerId = this->id;
    if (betType == 1)
    {
        if ((dice1 + dice2) == bet1)
        {
            resultScore.score = (bet * 2);
        }
    }
    else if (betType == 2)
    {
        if ((dice1 == bet1) && (dice2 == bet1))
        {
            resultScore.score = (bet * 3);
        }
    }
    else if (betType == 3)
    {
        if ((dice1 == bet1) && (dice2 == bet2))
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
        Score tempScore = player.giveDices(dices.dice1, dices.dice2);
        //@TODO somehow send this tempScore to Score board
    }
}