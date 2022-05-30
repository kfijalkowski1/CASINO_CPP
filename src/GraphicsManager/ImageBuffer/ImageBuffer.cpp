#include "ImageBuffer.h"
#include "exceptions.h"

unsigned int ImageBuffer::width = 0, ImageBuffer::height = 0;
ImageBuffer::ImageBuffer()
    : characters(width, std::vector<char>(height, ' ')),
      colors(width, std::vector<Color>(height, Color::Default)),
      backgrounds(width, std::vector<Color>(height, Color::DefaultBackground))
{
}
void ImageBuffer::setSize(unsigned int width, unsigned int height)
{
    ImageBuffer::width = width;
    ImageBuffer::height = height;
}

void ImageBuffer::setPixel(Position pos, char character)
{
    if (pos.x >= width || pos.y >= height)
        throw invalidPositionException;
    characters[pos.x][pos.y] = character;
}
void ImageBuffer::setPixel(Position pos, char character, Color color)
{
    setPixel(pos, character);
    setColor(pos, color);
}
void ImageBuffer::setPixel(Position pos, char character, Color color,
                           Color background)
{
    setPixel(pos, character);
    setColor(pos, color);
    setBackground(pos, background);
}
void ImageBuffer::setColor(Position pos, Color color)
{
    colors[pos.x][pos.y] = color;
}
void ImageBuffer::setBackground(Position pos, Color background)
{
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
