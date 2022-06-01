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
    // using namespace std::this_thread; // sleep_for, sleep_until
    // using namespace std::chrono;      // nanoseconds, system_clock, seconds

    try
    {
        GraphicsManager grafika(80, 24);
        ImageBuffer image;
        ImageBuffer background = image;

        Player Jacek;
        Jacek.name = "Jacek";
        Jacek.id = 1;
        Jacek.cash = 100000;
        Jacek.password = "haslo";

        BlackJack game(6);
        game.addPlayer(&Jacek);
        Card karta(2, 3);

        Position pos = Position(0, 0);

        while (true)
        {
            // karta.draw(image, pos);
            game.startNewDeal();
            game.draw(image, pos);
            grafika.show(image);
            grafika.draw();
            // sleep_for(nanoseconds(300000000));
        }

        /*
        int count = 0;
        int direction = 0;
        while (true)
        {
            // stos
            image = background;

            karta.draw(image, pos);
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
        */
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
}
