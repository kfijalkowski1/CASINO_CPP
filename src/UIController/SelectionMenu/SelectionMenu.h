#pragma once
#include "GraphicsManager/Box/Box.h"
#include "GraphicsManager/ImageBuffer/ImageBuffer.h"
#include "UIController/UIController.h"

#include <string>
#include <vector>

class SelectionMenu : public UIController
{
  private:
    void (*callback)(int);
    Box space;
    std::vector<std::u32string> options;
    std::string header;

    unsigned int selection;
    std::vector<Position> optionPositions;

    ImageBuffer mainBuffer;

    void initBuffer(std::u32string &header);
    void drawSelection();

  public:
    SelectionMenu(void (*callback)(int), Box space,
                  std::vector<std::u32string> options, std::u32string header);
    void init() override;
    void tick() override;
    void processKeypress(Keypress key) override;
};
