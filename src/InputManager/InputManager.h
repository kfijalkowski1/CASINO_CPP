#pragma once
#include "Keypress/Keypress.h"

class InputManager
{
  private:
    int getBytesWaiting();

  public:
    void init();
    bool inputAvailable();
    Keypress getKeypress();
};