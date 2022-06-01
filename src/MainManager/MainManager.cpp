#include "MainManager.h"
#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"
#include "UIController/Keypress/Keypress.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

MainManager mainManager;

MainManager::MainManager() : graphicsManager(80, 24) {}

void MainManager::init()
{
    // https://stackoverflow.com/a/59923166
    termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    term.c_lflag &= ~ICANON;
    tcsetattr(fileno(stdin), 0, &term);

    GraphicsCommands::hideCursor();
    graphicsManager.init();
}

void MainManager::cleanup() { GraphicsCommands::showCursor(); }

bool MainManager::tick()
{
    if (controllers.size() == 0)
        return false;

    int bytesWaiting;
    ioctl(fileno(stdin), FIONREAD, &bytesWaiting);

    while (bytesWaiting > 0)
    {
        char character = getchar();
        bytesWaiting--;

        Keypress key(character);

        if (character == '\x1b')
        {
            getchar();
            character = getchar();
            if ('A' <= character && character <= 'D')
                key = Keypress((Keypress::Direction)(character - 'A'));

            bytesWaiting -= 2;
            while (bytesWaiting-- > 0)
                getchar();
        }

        controllers.top()->processKeypress(key);
        if (controllers.size() == 0)
            return false;
    }
    controllers.top()->tick();
    if (controllers.size() == 0)
        return false;
    graphicsManager.draw();
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
