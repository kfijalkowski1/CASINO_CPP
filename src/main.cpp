#include "MainManager/MainManager.h"
#include "UIController/SelectionMenuController/SelectionMenuController.h"
#include <exception>
#include <iostream>

#include <chrono>
#include <thread>

void callback(int result) { std::cout << result << std::endl; }

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds

    mainManager.init();
    mainManager.addUIController(
        new SelectionMenuController(callback, Box(0, 0, 80, 24), {}, "aaaa"));

    try
    {
        while (mainManager.tick())
            sleep_for(nanoseconds(20000000));
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    mainManager.cleanup();
}
