#pragma once
#include "../BJHand/BJHand.h"
#include "UserManager/Player/Player.h"

class BJPlayer
{
  public:
    BJPlayer();
    BJPlayer(Player *player);
    Player *player;
    BJHand hand;
    unsigned int bet = 0;
};