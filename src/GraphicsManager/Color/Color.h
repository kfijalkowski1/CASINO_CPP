#pragma once

class Color
{
  private:
    unsigned char colorCode;

  public:
    Color(unsigned char colorCode);

    static Color RGB(unsigned char red, unsigned char green,
                     unsigned char blue);
    static Color Grayscale(unsigned char brightness);
    static Color Standard(unsigned char colorCode);
    static Color Intensive(unsigned char colorCode);

    static Color Default;
    static Color DefaultBackground;
};
