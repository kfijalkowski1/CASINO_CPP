#include "Color.h"
#include "exceptions.h"

Color::Color(unsigned char colorCode) : colorCode(colorCode) {}

Color Color::Default = Color(15);
Color Color::DefaultBackground = Color(0);

Color Color::RGB(unsigned char red, unsigned char green, unsigned char blue)
{
    if (red >= 6 || green >= 6 || blue >= 6)
        throw InvalidColorException();
    return Color(16 + 36 * red + 6 * green + blue);
}

Color Color::Grayscale(unsigned char brightness)
{
    if (brightness >= 24)
        throw InvalidColorException();
    return Color(232 + brightness);
}

Color Color::Standard(unsigned char colorCode)
{
    if (colorCode >= 8)
        throw InvalidColorException();
    return Color(colorCode);
}

Color Color::Intensive(unsigned char colorCode)
{
    if (colorCode >= 8)
        throw InvalidColorException();
    return Color(8 + colorCode);
}

bool Color::operator==(Color &color)
{
    return this->colorCode == color.colorCode;
}

bool Color::operator!=(Color &color)
{
    return this->colorCode != color.colorCode;
}
