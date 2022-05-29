#pragma once
#include <string>
#include "../../UserManager/Player/Player.h"
#include "../../LeaderBoardManager/Score/Score.h"

class Rules
{
public:
    std::string content;
    // std::string std_format();
    // std::string other_format();
};

class Game
{
public:
    // AllManager pointer?
    std::string name;
    Rules rules;
    std::vector<Player> players;
    std::vector<Score> Score_cashe;
    virtual void draw() = 0;
};