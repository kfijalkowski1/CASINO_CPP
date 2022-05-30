#include "GraphicsManager.h"
#include "GraphicsCommands/GraphicsCommands.h"
#include "Position/Position.h"
#include <iostream>

GraphicsManager::GraphicsManager(unsigned int width, unsigned int height)
{
    GraphicsCommands::eraseDisplay();
    ImageBuffer::setSize(width, height);

    currentBuffer = ImageBuffer();
    startX = 0;
    startY = 0;
}

void GraphicsManager::draw()
{
    unsigned int x = startX, y = startY;

    for (int y = 0; y < ImageBuffer::height; y++)
    {
        Color prevColor = Color::Default,
              prevBackround = Color::DefaultBackground;
        GraphicsCommands::moveCursor(startX + 0, startY + y);

        for (int x = 0; x < ImageBuffer::width; x++)
        {
            Color &color = currentBuffer.colors[x][y];
            Color &background = currentBuffer.backgrounds[x][y];
            char character = currentBuffer.characters[x][y];
            if (prevColor != color)
            {
                GraphicsCommands::setColor(color);
                prevColor = color;
            }
            if (prevBackround != background)
            {
                GraphicsCommands::setBackground(background);
                prevBackround = background;
            }

            std::cout << character;
        }
        GraphicsCommands::setColor(Color::Default);
        GraphicsCommands::setBackground(Color::DefaultBackground);
    }
    std::cout << std::flush;
}

void GraphicsManager::show(ImageBuffer newBuffer) { currentBuffer = newBuffer; }
void GraphicsManager::clear() { currentBuffer = ImageBuffer(); }