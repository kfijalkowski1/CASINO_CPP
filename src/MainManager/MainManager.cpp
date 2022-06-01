#include "MainManager.h"
#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"

MainManager mainManager;

MainManager::MainManager() : graphicsManager(80, 24), timingManager(60) {}

void MainManager::init()
{
    GraphicsCommands::hideCursor();
    graphicsManager.init();
    timingManager.init();
    inputManager.init();
}

void MainManager::cleanup() { GraphicsCommands::showCursor(); }

bool MainManager::tick()
{
    if (controllers.size() == 1)
        return false;

    while (inputManager.inputAvailable())
        controllers.top()->processKeypress(inputManager.getKeypress());

    controllers.top()->tick();
    graphicsManager.draw();
    controllers.top()->postDraw();

    return true;
}

void MainManager::addUIController(UIController *controller)
{
    controllers.push(controller);
}

void MainManager::removeUIController()
{
    delete controllers.top();
    controllers.pop();
}
