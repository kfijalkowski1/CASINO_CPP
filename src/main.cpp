#include "CSVManager/CSVfile.h"
#include "GraphicsManager/GraphicsManager.h"
#include "UserManager/Player/Player.h"
#include <exception>
#include <iostream>

#include <chrono>
#include <thread>

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds
    try
    {
        /*
        CSVfile<Player> test("../data/players.csv");
        //
        Player row = test[1];
        std::cout << row.id << ' ' << row.name << ' ' << std::endl;
        for (auto row : test)
        {
            std::cout << row.id << ' ' << row.name << ' ' << row.cash
                      << std::endl;
        }
        auto newPlayer = Player();
        newPlayer.cash = 100000;
        newPlayer.id = 10;
        newPlayer.name = "Tester";
        newPlayer.password = "123";
        test.push_back(newPlayer);

        test.save();
        */
        GraphicsManager test(80, 24);
        ImageBuffer image;
        image.setPixel(Position(0, 0), "a");
        image.setPixel(Position(1, 1), "b");
        image.setPixel(Position(2, 2), "c");
        image.setPixel(Position(3, 3), "d");
        image.setBackground(Position(3, 3), Color::RGB(2, 3, 4));
        image.setColor(Position(5, 5), Color::Grayscale(10));
        image.setPixel(Position(5, 5), "*");

        ImageBuffer background = image;

        Position pos = Position(0, 0);
        int count = 0;
        int direction = 0;
        while (true)
        {
            image = background;

            image.setPixel(pos, "❤", Color::RGB(1, 3, 3));
            image.setColor(pos, Color::RGB(1, 3, 3));

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
            sleep_for(nanoseconds(100000000));
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
}
