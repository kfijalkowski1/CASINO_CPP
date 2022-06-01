#pragma once
#include <string>

class Keypress
{
  public:
    enum Direction
    {
        up,
        down,
        right,
        left,
    };

    Keypress(char input);
    Keypress(Direction direction);

    bool arrow;
    char character;
    Direction direction;
};