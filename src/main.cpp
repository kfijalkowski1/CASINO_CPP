#include "MainManager/MainManager.h"
#include "UIController/SelectionMenuController/SelectionMenuController.h"
#include <exception>
#include <iostream>

void callback(int result) { std::cout << result << std::endl; }

int main()
{
    mainManager.init();
    mainManager.addUIController(new UIController());
    mainManager.addUIController(
        new SelectionMenuController(callback, Box(0, 0, 80, 24), {}, "aaaa"));

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
