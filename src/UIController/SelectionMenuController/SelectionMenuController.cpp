#include "SelectionMenuController.h"
#include "MainManager/MainManager.h"
#include <iostream>

SelectionMenuController::SelectionMenuController(
    void (*callback)(int), Box space, std::vector<std::string> options,
    std::string header)
    : callback(callback), space(space), start(10, 10), finish(60, 10)
{
}

void SelectionMenuController::tick()
{
    start += Position(1, 0);
    finish += Position(1, 0);

    if (start.x == 70)
        start.x = 10;
    if (finish.x == 70)
        finish.x = 10;

    animationBuffer.setBackground(start, Color::RGB(5, 1, 4));
    animationBuffer.setBackground(finish, Color::DefaultBackground);

    mainManager.graphicsManager.show(animationBuffer);
}
void SelectionMenuController::processKeypress(Keypress key)
{
    animationBuffer.drawBoxCharacter(Box(0, 5, 80, 6), ' ');
    if (key.arrow)
    {
        animationBuffer.writeText(Box(0, 5, 80, 5), "Arrow!",
                                  ImageBuffer::TextAlignment::center);
    }
    else
    {
        if (key.character == '\n')
        {
            callback(selection);
            mainManager.removeUIController();
        }
        animationBuffer.writeText(Box(0, 5, 80, 5), "Not an arrow :(",
                                  ImageBuffer::TextAlignment::center);
    }
    mainManager.graphicsManager.show(animationBuffer);
}