#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"
#include "MainManager/MainManager.h"
#include "UIController/SelectionMenu/SelectionMenu.h"
#include "UIController/TextInputMenu/TextInputMenu.h"
#include <exception>
#include <iostream>

void getText(std::string result)
{
    mainManager.removeUIController();
    GraphicsCommands::moveCursor(81, 5);
    std::cout << result << std::endl;
}

void mainAction(int selection)
{
    switch (selection)
    {
    case 0:
        mainManager.addUIController(new TextInputMenu(
            getText, Box(10, 0, 70, 24), U"Enter player name"));
        break;
    case 1:
        mainManager.removeUIController();
        break;
    }
}

int main()
{
    mainManager.init();
    mainManager.addUIController(new UIController());
    mainManager.addUIController(new SelectionMenu(
        mainAction, Box(0, 0, 80, 24), {U"Play", U"Quit"}, U"Casino.o"));

    try
    {
        while (mainManager.tick())
        {
            mainManager.timingManager.tick();
            mainManager.timingManager.printStats(); // for debugging
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    mainManager.cleanup();
}
