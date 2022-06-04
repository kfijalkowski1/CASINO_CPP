#include "RainbowGenerator.h"

RainbowGenerator::RainbowGenerator() : red(5), green(0), blue(0), stage(0) {}
Color RainbowGenerator::nextColor()
{
    switch (stage)
    {
    case 0:
        red--;
        green++;
        if (red == 0)
            stage++;
        break;
    case 1:
        green--;
        blue++;
        if (green == 0)
            stage++;
        break;
    case 2:
        blue--;
        red++;
        if (blue == 0)
            stage = 0;
        break;
    }
    return Color::RGB(red, green, blue);
}