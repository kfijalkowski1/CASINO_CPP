#include "Box.h"

Box::Box(Position topLeft, Position bottomRight)
    : topLeft(topLeft), bottomRight(bottomRight)
{
}
Box::Box(int left, int top, int right, int bottom)
    : topLeft(left, top), bottomRight(right, bottom)
{
}

Box Box::operator+(const Position &that) const { return Box(*this) += that; }
Box &Box::operator+=(const Position &that)
{
    topLeft += that;
    bottomRight += that;
    return *this;
}