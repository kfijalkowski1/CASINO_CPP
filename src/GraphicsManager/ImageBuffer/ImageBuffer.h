#pragma once
#include "GraphicsManager/Box/Box.h"
#include "GraphicsManager/Color/Color.h"
#include "GraphicsManager/Position/Position.h"
#include <string>
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
    enum TextAlignment
    {
        left,
        center,
        right
    };
    ImageBuffer();

    void setPixel(Position pos, char32_t character);
    void setPixel(Position pos, char32_t character, Color color);
    void setPixel(Position pos, char32_t character, Color color,
                  Color background);
    void setColor(Position pos, Color color);
    void setBackground(Position pos, Color background);

    void writeText(Position pos, std::string text);
    void writeText(Position pos, std::u32string text);
    void writeText(Box space, std::string text, TextAlignment align);
    void writeText(Box space, std::u32string text, TextAlignment align);

    void drawBoxCharacter(Box box, char32_t character);
    void drawBoxColor(Box box, Color color);
    void drawBoxBackground(Box box, Color background);

    void clear();
};
