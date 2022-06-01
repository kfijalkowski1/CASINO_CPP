#pragma once
#include "GraphicsManager/GraphicsManager.h"
#include "UIController/UIController.h"
#include <stack>

class MainManager
{
  private:
    std::stack<UIController *> controllers;

  public:
    MainManager();
    void init();
    void cleanup();
    bool tick();

    void addUIController(UIController *controller);
    void removeUIController();

    GraphicsManager graphicsManager;
    // leaderboard manager
    // other managers
};

extern MainManager mainManager;
