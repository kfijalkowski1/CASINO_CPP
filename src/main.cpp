#include "MainManager/MainManager.h"
#include <exception>
#include <iostream>

int main()
{
    mainManager = new MainManager();
    mainManager->init();

    try
    {
        while (mainManager->tick())
        {
            mainManager->timingManager.tick();
            mainManager->timingManager.printStats(); // for debugging
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    mainManager->cleanup();
    delete mainManager;
}
