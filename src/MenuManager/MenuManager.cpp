#include "MainManager/MainManager.h"
#include "MenuManger.h"
#include "UIController/SelectionMenu/SelectionMenu.h"
#include "UIController/TextInputMenu/TextInputMenu.h"

void MenuManager::createTitleMenu()
{
    mainManager->addUIController(new SelectionMenu(
        std::bind(&MenuManager::callbackTitleMenu, this, std::placeholders::_1),
        Box(0, 0, ImageBuffer::width, ImageBuffer::height), {U"Login", U"Quit"},
        U"Casino.o"));
}
void MenuManager::callbackTitleMenu(int sel)
{
    mainManager->removeUIController();
    switch (sel)
    {
    case 0:
        createLoginMenu();
        break;
    case 1:
        break;
    }
}

void MenuManager::createLoginMenu()
{
    ImageBuffer buffer;
    buffer.writeText(Position(10, ImageBuffer::height / 2 + 1), "Login:");

    mainManager->graphicsManager.show(buffer);

    mainManager->addUIController(new TextInputMenu(
        std::bind(&MenuManager::callbackLoginMenu, this, std::placeholders::_1),
        Box(20, 0, ImageBuffer::width - 10, ImageBuffer::height), U"Casino.o"));
}
void MenuManager::callbackLoginMenu(std::string login)
{
    mainManager->removeUIController();

    mainManager->currentPlayer = mainManager->userManager.getPlayer(login);

    createMainMenu();
}

void MenuManager::createMainMenu()
{
    mainManager->graphicsManager.clear();
    mainManager->addUIController(new SelectionMenu(
        std::bind(&MenuManager::callbackMainMenu, this, std::placeholders::_1),
        Box(0, 0, ImageBuffer::width, ImageBuffer::height),
        {U"Play", U"Leaderboard", U"Quit"}, U"Casino.o"));
}
void MenuManager::callbackMainMenu(int sel)
{
    switch (sel)
    {
    case 0:
        createGameMenu();
        break;
    case 1:
        // show leaderboard
        break;
    case 2:
        mainManager->removeUIController();
        break;
    }
}

void MenuManager::createGameMenu()
{
    mainManager->graphicsManager.clear();
    mainManager->addUIController(new SelectionMenu(
        std::bind(&MenuManager::callbackGameMenu, this, std::placeholders::_1),
        Box(0, 0, ImageBuffer::width, ImageBuffer::height),
        {U"Black Jack", U"Craps", U"<- Back"}, U"Casino.o"));
}
void MenuManager::callbackGameMenu(int sel)
{
    switch (sel)
    {
    case 0:
        // run blackjack
        break;
    case 1:
        // run craps
        break;
    case 2:
        mainManager->removeUIController();
        break;
    }
}

void MenuManager::init() { createTitleMenu(); }