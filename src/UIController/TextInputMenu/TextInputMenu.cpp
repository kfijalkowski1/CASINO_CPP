#include "TextInputMenu.h"
#include "MainManager/MainManager.h"

TextInputMenu::TextInputMenu(void (*callback)(std::string), Box space,
                             std::u32string header)
    : callback(callback), space(space), textInputPosition(0, 0), textPosition(0)
{
    initBuffer(header);
}

void TextInputMenu::initBuffer(std::u32string &header)
{
    int width = space.bottomRight.x - space.topLeft.x;
    int height = space.bottomRight.y - space.topLeft.y;

    int topPadding = (height - 3) / 2;
    Box line = space;
    line.topLeft.y += topPadding;
    line.bottomRight.y = line.topLeft.y + 1;

    mainBuffer.writeText(line, header, ImageBuffer::TextAlignment::center);

    line += Position(0, 2);
    mainBuffer.drawBoxBackground(line, Color::Grayscale(5));

    textInputPosition = line.topLeft;
}

void TextInputMenu::init() { drawTextInput(); }

void TextInputMenu::drawTextInput()
{
    ImageBuffer buffer = mainBuffer;
    buffer.writeText(textInputPosition, text);

    buffer.setColor(textInputPosition + Position(textPosition, 0),
                    Color::DefaultBackground);
    buffer.setBackground(textInputPosition + Position(textPosition, 0),
                         Color::Default);

    mainManager.graphicsManager.show(buffer);
}

void TextInputMenu::tick() {}
void TextInputMenu::processKeypress(Keypress key)
{
    if (key.arrow)
    {
        switch (key.direction)
        {
        case Keypress::Direction::right:
            if (textPosition < text.length())
                textPosition++;
            break;
        case Keypress::Direction::left:
            if (textPosition >= 1)
                textPosition--;
            break;
        }
    }
    else
    {
        switch (key.character)
        {
        case '\n':
            callback(text);
            return;
        case 127: // backspace
            if (textPosition > 0)
                text.erase(--textPosition, 1);
            break;
        case 27: // delete
            if (textPosition < text.length())
                text.erase(textPosition, 1);
            break;
        default:
            text.insert(textPosition++, std::string(1, key.character));
            break;
        }
    }
    drawTextInput();
}

void TextInputMenu::postDraw() {}