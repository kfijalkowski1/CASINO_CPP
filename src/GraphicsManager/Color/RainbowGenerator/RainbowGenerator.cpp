#include "RainbowGenerator.h"

RainbowGenerator::RainbowGenerator() : red(5), green(0), blue(0), stage(0) {}
Color RainbowGenerator::nextColor()
{
    switch (stage)
    {
    case 0:
        if (++green == 5)
            stage++;
        break;
    case 1:
        if (--red == 0)
            stage++;
        break;
    case 2:
        if (++blue == 5)
            stage++;
        break;
    case 3:
        if (--green == 0)
            stage++;
        break;
    case 4:
        if (++red == 5)
            stage++;
        break;
    case 5:
        if (--blue == 0)
            stage = 0;
        break;
    }
    return Color::RGB(red, green, blue);
}