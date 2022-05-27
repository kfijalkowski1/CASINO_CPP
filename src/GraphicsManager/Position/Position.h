#pragma once
#include "GraphicsManager/GraphicsManager.h"

class Position
{
  private:
    static unsigned int bufferWidth, bufferHeight;
    static void setBufferSize(unsigned int bufferWidth,
                              unsigned int bufferHeight);
    friend class GraphicsManager;

  public:
    unsigned int x, y;
    Position(unsigned int x, unsigned int y);
};
