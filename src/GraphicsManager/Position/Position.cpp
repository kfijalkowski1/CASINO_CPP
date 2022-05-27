#include "Position.h"
#include "exceptions.h"

unsigned int Position::bufferWidth = 0, Position::bufferHeight = 0;
void Position::setBufferSize(unsigned int bufferWidth,
                             unsigned int bufferHeight)
{
    Position::bufferWidth = bufferWidth;
    Position::bufferHeight = bufferHeight;
}

Position::Position(unsigned int x, unsigned int y) : x(x), y(y)
{
    if (x >= bufferWidth || y >= bufferHeight)
        throw invalidPositionException;
}
