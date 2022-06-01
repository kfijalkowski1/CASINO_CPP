#pragma once
#include "LeaderBoardManager/Score/Score.h"
#include "UserManager/Player/Player.h"
#include <string>
#include "GraphicsManager/ImageBuffer/ImageBuffer.h"
#include "GraphicsManager/Position/Position.h"

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
  std::vector<Score> Score_cashe;
  // virtual void draw(ImageBuffer &img, Position pos) = 0;
};