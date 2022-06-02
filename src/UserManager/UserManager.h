#pragma once
#include "CSVManager/CSVfile.h"
#include "Player/Player.h"

class UserManager
{
  private:
    CSVfile<Player> file;

  public:
    UserManager();
    Player *getPlayer(std::string login);
};