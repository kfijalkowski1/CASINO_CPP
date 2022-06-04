#pragma once
#include "../Color.h"

class RainbowGenerator
{
  private:
    unsigned char red, green, blue;
    unsigned char stage;

  public:
    RainbowGenerator();
    Color nextColor();
};