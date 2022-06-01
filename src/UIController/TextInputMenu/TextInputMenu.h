#pragma once
#include "GraphicsManager/Box/Box.h"
#include "GraphicsManager/ImageBuffer/ImageBuffer.h"
#include "UIController/UIController.h"

#include <functional>
#include <string>
#include <vector>

class TextInputMenu : public UIController
{
  private:
    std::function<void(std::string)> callback;
    Box space;
    std::string header;

    ImageBuffer mainBuffer;

    std::string text;
    Position textInputPosition;
    unsigned int textPosition;

    void initBuffer(std::u32string &header);
    void drawTextInput();

  public:
    TextInputMenu(std::function<void(std::string)> callback, Box space,
                  std::u32string header);
    void init() override;
    void tick() override;
    void processKeypress(Keypress key) override;
    void postDraw() override;
};
