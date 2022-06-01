#pragma once
#include "GraphicsManager/Box/Box.h"
#include "GraphicsManager/ImageBuffer/ImageBuffer.h"
#include "UIController/UIController.h"

#include <string>
#include <vector>

class TextInputMenu : public UIController
{
  private:
    void (*callback)(std::string);
    Box space;
    std::string header;

    ImageBuffer mainBuffer;

    std::string text;
    Position textInputPosition;
    unsigned int textPosition;

    void initBuffer(std::u32string &header);
    void drawTextInput();

  public:
    TextInputMenu(void (*callback)(std::string), Box space,
                  std::u32string header);
    void init() override;
    void tick() override;
    void processKeypress(Keypress key) override;
    void postDraw() override;
};
