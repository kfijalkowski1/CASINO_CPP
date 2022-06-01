#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"
#include "MainManager/MainManager.h"
#include "UIController/SelectionMenu/SelectionMenu.h"
#include "UIController/TextInputMenu/TextInputMenu.h"
#include <exception>
#include <iostream>

void callback(std::string result)
{
    mainManager.removeUIController();
    GraphicsCommands::moveCursor(81, 5);
    std::cout << result << std::endl;
}

int main()
{
    mainManager.init();
    mainManager.addUIController(new UIController());
    // mainManager.addUIController(new SelectionMenu(
    //     callback, Box(0, 0, 80, 24), {U"Play", U"Quit"}, U"Casino.o"));
    mainManager.addUIController(
        new TextInputMenu(callback, Box(10, 0, 70, 24), U"Casino.o"));

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
