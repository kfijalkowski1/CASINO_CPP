#pragma once
#include "GraphicsManager/Position/Position.h"

class Box
{
  public:
    Position topLeft, bottomRight;
    Box(Position topLeft, Position bottomRight);
    Box(int left, int top, int right, int bottom);

    Box operator+(const Position &that) const;
    Box &operator+=(const Position &that);
};
