#include "MainManager/MainManager.h"
#include <exception>
#include <iostream>

int main()
{
    try
    {
        mainManager = new MainManager();
        mainManager->init();

        while (mainManager->tick())
        {
            mainManager->timingManager.tick();
            mainManager->timingManager.printStats(); // for debugging
        }

        mainManager->cleanup();
        delete mainManager;
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
}
