#pragma once
#include "InputManager/Keypress/Keypress.h"

class UIController
{
  public:
    virtual void init();
    virtual void tick();
    virtual void processKeypress(Keypress key);
    virtual void postDraw();
};