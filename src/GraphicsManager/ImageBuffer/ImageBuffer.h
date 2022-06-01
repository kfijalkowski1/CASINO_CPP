#pragma once
#include "GraphicsManager/Color/Color.h"
#include "GraphicsManager/Position/Position.h"
#include <vector>

class ImageBuffer
{
  private:
    std::vector<std::vector<char32_t>> characters;
    std::vector<std::vector<Color>> colors;
    std::vector<std::vector<Color>> backgrounds;

    static unsigned int width, height;
    static void setSize(unsigned int width, unsigned int height);
    friend class GraphicsManager;

  public:
    ImageBuffer();

    void setPixel(Position pos, char32_t character);
    void setPixel(Position pos, char32_t character, Color color);
    void setPixel(Position pos, char32_t character, Color color,
                  Color background);
    void setColor(Position pos, Color color);
    void setBackground(Position pos, Color background);

    void clear();
};
