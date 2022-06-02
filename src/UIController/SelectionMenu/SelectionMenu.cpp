#include "SelectionMenu.h"
#include "MainManager/MainManager.h"

SelectionMenu::SelectionMenu(std::function<void(int)> callback, Box space,
                             std::vector<std::u32string> options,
                             std::u32string header)
    : callback(callback), space(space), options(options), selection(0)
{
    initBuffer(header);
}

void SelectionMenu::initBuffer(std::u32string &header)
{
    mainBuffer = mainManager->graphicsManager.currentBuffer;

    int width = space.bottomRight.x - space.topLeft.x;
    int height = space.bottomRight.y - space.topLeft.y;

    int topPadding =
        (height - (options.size() + (header.length() > 0) ? 2 : 0)) / 2;
    Box line = space;
    line.topLeft.y += topPadding;
    line.bottomRight.y = line.topLeft.y + 1;

    if (header.length() > 0)
    {
        mainBuffer.writeText(line, header, ImageBuffer::TextAlignment::center);

        line += Position(0, 2);
    }
    for (auto option : options)
    {
        optionPositions.push_back(mainBuffer.writeText(
            line, option, ImageBuffer::TextAlignment::center));
        line += Position(0, 1);
    }
}

void SelectionMenu::init() { drawSelection(); }

void SelectionMenu::drawSelection()
{
    ImageBuffer buffer = mainBuffer;
    Position pos = optionPositions[selection];
    buffer.drawBoxBackground(
        Box(pos, pos + Position(options[selection].length(), 1)),
        Color::Intensive(7));
    buffer.drawBoxColor(
        Box(pos, pos + Position(options[selection].length(), 1)),
        Color::Standard(0));

    mainManager->graphicsManager.show(buffer);
}

void SelectionMenu::tick() { drawSelection(); }
void SelectionMenu::processKeypress(Keypress key)
{
    if (key.arrow)
    {
        switch (key.direction)
        {
        case Keypress::Direction::down:
            if (selection < options.size() - 1)
                selection++;
            break;
        case Keypress::Direction::up:
            if (selection >= 1)
                selection--;
            break;
        }
        drawSelection();
    }
    else
    {
        if (key.character == '\n')
        {
            callback(selection);
            return;
        }
    }
}