#pragma once
#include "GraphicsManager/GraphicsManager.h"
#include "InputManager/InputManager.h"
#include "TimingManager/TimingManager.h"
#include "UIController/UIController.h"
#include "LeaderBoardManager/LBManager.h"

#include <stack>

class MainManager
{
private:
  std::stack<UIController *> controllers;
  std::stack<ImageBuffer> bufferHistory;

  bool pause;

public:
  MainManager();
  void init();
  void cleanup();
  bool tick();

  void addUIController(UIController *controller);
  void removeUIController();

  GraphicsManager graphicsManager;
  TimingManager timingManager;
  InputManager inputManager;
  LBReader leaderManager;
  // leaderboard manager
  // other managers
};

extern MainManager mainManager;
