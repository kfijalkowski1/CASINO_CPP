#pragma once
#include "GraphicsManager/ImageBuffer/ImageBuffer.h"
#include <map>
#include <string>

class GraphicsManager
{
  private:
    unsigned int terminalWidth, terminalHeight;
    unsigned int startX, startY;

  public:
    GraphicsManager(unsigned int width, unsigned int height);

    ImageBuffer currentBuffer;

    void init();
    void draw();
    void show(ImageBuffer newBuffer);
    void clear();
};
