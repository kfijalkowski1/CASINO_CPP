#pragma once
#include "GraphicsManager/Color/Color.h"
#include <string>

class GraphicsCommands
{
  public:
    static std::string SequencePrefix;
    static void eraseDisplay();
    static void setColor(Color color);
    static void setBackground(Color background);
    static void moveCursor(unsigned int x, unsigned int y);
    static std::string codepointToUTF8(char32_t codepoint);
    static void printCharacter(char32_t character);
};
