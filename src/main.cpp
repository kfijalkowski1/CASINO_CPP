#include "CSVManager/CSVfile.h"
#include "UserManager/Player/Player.h"
#include <exception>
#include <iostream>

int main()
{
    try
    {
        /*CSVfile<Player> test("../data/players.csv");
        //
        Player row = test[1];
        std::cout << row.id << ' ' << row.name << ' ' << std::endl;
        for (auto row : test)
        {
            std::cout << row.id << ' ' << row.name << ' ' << row.cash
                      << std::endl;
        }*/
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
}
