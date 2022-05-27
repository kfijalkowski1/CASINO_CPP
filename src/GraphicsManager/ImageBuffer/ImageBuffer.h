#pragma once
#include "GraphicsManager/Color/Color.h"
#include "GraphicsManager/GraphicsManager.h"
#include "GraphicsManager/Position/Position.h"
#include <string>
#include <vector>

class ImageBuffer
{
  private:
    std::vector<std::vector<char>> characters;
    std::vector<std::vector<Color>> colors;
    std::vector<std::vector<Color>> backgrounds;
    friend class GraphicsManager;

  public:
    ImageBuffer(unsigned int width, unsigned int height);

    void setPixel(Position pos, char character);
    void setPixel(Position pos, char character, Color color);
    void setPixel(Position pos, char character, Color color, Color background);
    void setColor(Position pos, Color color);
    void setBackground(Position pos, Color background);

    void clear();
};
