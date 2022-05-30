#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"
#include <iostream>

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
