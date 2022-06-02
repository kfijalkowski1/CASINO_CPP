#include "ImageBuffer.h"

unsigned int ImageBuffer::width = 0, ImageBuffer::height = 0;
ImageBuffer::ImageBuffer()
    : characters(width, std::vector<char32_t>(height, ' ')),
      colors(width, std::vector<Color>(height, Color::Default)),
      backgrounds(width, std::vector<Color>(height, Color::DefaultBackground))
{
}
void ImageBuffer::setSize(unsigned int width, unsigned int height)
{
    ImageBuffer::width = width;
    ImageBuffer::height = height;
}

void ImageBuffer::setPixel(Position pos, char32_t character)
{
    if (0 <= pos.x && pos.x < width && 0 <= pos.y && pos.y < height)
        characters[pos.x][pos.y] = character;
}
void ImageBuffer::setPixel(Position pos, char32_t character, Color color)
{
    setPixel(pos, character);
    setColor(pos, color);
}
void ImageBuffer::setPixel(Position pos, char32_t character, Color color,
                           Color background)
{
    setPixel(pos, character);
    setColor(pos, color);
    setBackground(pos, background);
}
void ImageBuffer::setColor(Position pos, Color color)
{
    if (0 <= pos.x && pos.x < width && 0 <= pos.y && pos.y < height)
        colors[pos.x][pos.y] = color;
}
void ImageBuffer::setBackground(Position pos, Color background)
{
    if (0 <= pos.x && pos.x < width && 0 <= pos.y && pos.y < height)
        backgrounds[pos.x][pos.y] = background;
}

void ImageBuffer::clear()
{
    for (auto &column : characters)
        std::fill(column.begin(), column.end(), ' ');

    for (auto &column : colors)
        std::fill(column.begin(), column.end(), Color::Default);

    for (auto &column : backgrounds)
        std::fill(column.begin(), column.end(), Color::DefaultBackground);
}

void ImageBuffer::writeText(Position pos, std::u32string text)
{
    for (auto character : text)
    {
        setPixel(pos, character);
        pos += Position(1, 0);
    }
}
Position ImageBuffer::writeText(Box space, std::u32string text,
                                TextAlignment align)
{
    int width = space.bottomRight.x - space.topLeft.x;
    int freeSpace = width - text.length();

    Position textPos(space.topLeft);
    switch (align)
    {
    case TextAlignment::center:
        textPos += Position(freeSpace / 2, 0);
        break;
    case TextAlignment::right:
        textPos += Position(freeSpace, 0);
        break;
    }
    writeText(textPos, text);
    return textPos;
}
void ImageBuffer::writeText(Position pos, std::string text)
{
    std::u32string converted(text.begin(), text.end());
    writeText(pos, converted);
}
Position ImageBuffer::writeText(Box space, std::string text,
                                TextAlignment align)
{
    std::u32string converted(text.begin(), text.end());
    return writeText(space, converted, align);
}

void ImageBuffer::drawBoxCharacter(Box box, char32_t character)
{
    Position pos(box.topLeft);
    for (; pos.x < box.bottomRight.x; pos.x++)
    {
        for (pos.y = box.topLeft.y; pos.y < box.bottomRight.y; pos.y++)
        {
            setPixel(pos, character);
        }
    }
}
void ImageBuffer::drawBoxColor(Box box, Color color)
{
    Position pos(box.topLeft);
    for (; pos.x < box.bottomRight.x; pos.x++)
    {
        for (pos.y = box.topLeft.y; pos.y < box.bottomRight.y; pos.y++)
        {
            setColor(pos, color);
        }
    }
}
void ImageBuffer::drawBoxBackground(Box box, Color background)
{
    Position pos(box.topLeft);
    for (; pos.x < box.bottomRight.x; pos.x++)
    {
        for (pos.y = box.topLeft.y; pos.y < box.bottomRight.y; pos.y++)
        {
            setBackground(pos, background);
        }
    }
}
