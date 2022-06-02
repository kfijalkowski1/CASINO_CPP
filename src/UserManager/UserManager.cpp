#include "UserManager.h"

void UserManager::save()
{
    file.save();
}
UserManager::UserManager() : file("../data/players.csv") {}

Player *UserManager::getPlayer(std::string login)
{
    for (auto &player : file)
    {
        if (player.name == login)
            return &player;
    }
    int nextId = 0;
    if (file.size() > 0)
        nextId = file.back().id + 1;

    Player newPlayer(nextId, login, "");
    file.push_back(newPlayer);
    file.save();

    return &(file.back());
}
