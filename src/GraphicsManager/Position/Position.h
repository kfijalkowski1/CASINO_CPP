#pragma once

class Position
{
  public:
    unsigned int x, y;
    Position(unsigned int x, unsigned int y);

    Position operator+(const Position &that) const;
    Position &operator+=(const Position &that);
};
