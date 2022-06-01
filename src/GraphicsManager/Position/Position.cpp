#include "Position.h"

Position::Position(int x, int y) : x(x), y(y) {}

Position Position::operator+(const Position &that) const
{
    return Position(*this) += that;
}
Position &Position::operator+=(const Position &that)
{
    x += that.x;
    y += that.y;
    return *this;
}
