#include "CSVManager/CSVfile.h"
#include "GraphicsManager/GraphicsManager.h"
#include "UserManager/Player/Player.h"
#include <exception>
#include <iostream>
#include <stdio.h> //
#include <chrono>
#include <thread>
#include <GamesManager/Cards/Cards.h>
#include <GamesManager/BlackJack/BlackJack.h>

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds

    try
    {
        GraphicsManager test(80, 24);
        ImageBuffer image;
        ImageBuffer background = image;

        Position pos = Position(0, 0);

        int count = 0;
        int direction = 0;
        while (true)
        {
            image = background;
            char32_t a = U'❤';

            switch (direction)
            {
            case 0:
                pos += Position(1, 0);
                break;
            case 1:
                pos += Position(0, 1);
                break;
            case 2:
                pos += Position(-1, 0);
                break;
            case 3:
                pos += Position(0, -1);
                break;
            }
            count++;
            if (count >= 5)
            {
                count = 0;
                direction++;
                direction %= 4;
            }

            test.show(image);
            test.draw();

            sleep_for(nanoseconds(300000000));
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
}
