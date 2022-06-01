#include "InputManager.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

void InputManager::init()
{
    // https://stackoverflow.com/a/59923166
    termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    term.c_lflag &= ~ICANON;
    tcsetattr(fileno(stdin), 0, &term);
}

int InputManager::getBytesWaiting()
{
    int bytesWaiting;
    ioctl(fileno(stdin), FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
bool InputManager::inputAvailable() { return (bool)getBytesWaiting(); }

Keypress InputManager::getKeypress()
{
    int bytesWaiting = getBytesWaiting();
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

    return key;
}