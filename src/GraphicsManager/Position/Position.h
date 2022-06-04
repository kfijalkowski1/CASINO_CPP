#pragma once

class Position
{
  public:
    int x, y;
    Position(int x, int y);

    Position operator+(const Position &that) const;
    Position &operator+=(const Position &that);

    bool operator==(const Position &that) const;
};
