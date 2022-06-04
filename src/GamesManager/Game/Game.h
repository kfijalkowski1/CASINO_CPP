#pragma once
#include "GraphicsManager/ImageBuffer/ImageBuffer.h"
#include "GraphicsManager/Position/Position.h"
#include "LeaderBoardManager/Score/Score.h"
#include "UIController/UIController.h"
#include "UserManager/Player/Player.h"
#include <string>

class Rules
{
  public:
    std::string content;
    // std::string std_format();
    // std::string other_format();
};

class Game : public UIController
{
  public:
    // AllManager pointer?
    static std::string name;
    static Rules rules;
};