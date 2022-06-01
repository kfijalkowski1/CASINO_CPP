#include "MainManager.h"
#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"

MainManager *mainManager;

MainManager::MainManager() : graphicsManager(80, 24), timingManager(60) {}

void MainManager::init()
{
    GraphicsCommands::hideCursor();
    graphicsManager.init();
    timingManager.init();
    inputManager.init();

    mainManager->addUIController(new UIController());
    menuManager.init();
}

void MainManager::cleanup()
{
    GraphicsCommands::showCursor();
    GraphicsCommands::moveCursor(ImageBuffer::width, ImageBuffer::height - 1);
}

bool MainManager::tick()
{
    pause = false;
    if (controllers.size() == 1)
        return false;

    while (inputManager.inputAvailable())
        if (!pause)
            controllers.top()->processKeypress(inputManager.getKeypress());

    if (!pause)
        controllers.top()->tick();
    if (!pause)
        graphicsManager.draw();
    if (!pause)
        controllers.top()->postDraw();

    return true;
}

void MainManager::addUIController(UIController *controller)
{
    bufferHistory.push(graphicsManager.currentBuffer);
    controllers.push(controller);

    controllers.top()->init();
}

void MainManager::removeUIController()
{
    delete controllers.top();
    controllers.pop();

    graphicsManager.show(bufferHistory.top());
    bufferHistory.pop();

    pause = true;
}
