#pragma once
#include "GraphicsManager/GraphicsManager.h"
#include "InputManager/InputManager.h"
#include "MenuManager/MenuManger.h"
#include "TimingManager/TimingManager.h"
#include "UIController/UIController.h"
#include "LeaderBoardManager/LBManager.h"
#include "UserManager/UserManager.h"
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

  Player *currentPlayer;

  GraphicsManager graphicsManager;
  TimingManager timingManager;
  InputManager inputManager;
  LBReader leaderManager;
  MenuManager menuManager;
  UserManager userManager;
};

extern MainManager *mainManager;
