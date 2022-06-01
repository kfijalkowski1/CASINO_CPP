#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"
#include <codecvt>
#include <iostream>
#include <locale>

std::string GraphicsCommands::SequencePrefix = "\x1b[";
void GraphicsCommands::eraseDisplay() { std::cout << SequencePrefix << "2J"; }
void GraphicsCommands::setColor(Color color)
{
    std::cout << SequencePrefix << "38;5;" << (int)color.colorCode << "m";
};
void GraphicsCommands::setBackground(Color background)
{
    std::cout << SequencePrefix << "48;5;" << (int)background.colorCode << "m";
};

void GraphicsCommands::moveCursor(unsigned int x, unsigned int y)
{
    std::cout << SequencePrefix << 1 << ';' << 1 << 'H';
    if (x > 0)
        std::cout << SequencePrefix << x << 'C';
    if (y > 0)
        std::cout << SequencePrefix << y << 'B';

    // std::cout << SequencePrefix << y + 1 << ':' << x + 1 << 'H';
};

// https://stackoverflow.com/a/56341756
std::string GraphicsCommands::codepointToUTF8(char32_t codepoint)
{
    static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.to_bytes(&codepoint, &codepoint + 1);
}

void GraphicsCommands::printCharacter(char32_t character)
{
    std::cout << codepointToUTF8(character);
}
