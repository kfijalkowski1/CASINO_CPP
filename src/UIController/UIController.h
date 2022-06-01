#pragma once
#include "Keypress/Keypress.h"

class UIController
{
  public:
    virtual void tick() = 0;
    virtual void processKeypress(Keypress key) = 0;
};