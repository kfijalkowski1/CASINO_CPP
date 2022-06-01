#pragma once
#include "GraphicsManager/Box/Box.h"
#include "GraphicsManager/ImageBuffer/ImageBuffer.h"
#include "UIController/UIController.h"

#include <string>
#include <vector>

class SelectionMenuController : public UIController
{
  private:
    void (*callback)(int);
    Box space;
    std::vector<std::string> options;
    std::string header;

    unsigned int selection;

    ImageBuffer mainBuffer;
    ImageBuffer animationBuffer;

    Position start, finish;

  public:
    SelectionMenuController(void (*callback)(int), Box space,
                            std::vector<std::string> options,
                            std::string header);
    void tick();
    void processKeypress(Keypress key);
};
