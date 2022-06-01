#pragma once
#include <string>

class MenuManager
{
  private:
    void createTitleMenu();
    void callbackTitleMenu(int sel);

    void createLoginMenu();
    void callbackLoginMenu(std::string login);

    void createPasswordMenu();
    void callbackPasswordMenu(std::string password);

    void createMainMenu();
    void callbackMainMenu(int sel);

    void createGameMenu();
    void callbackGameMenu(int sel);

  public:
    void init();
};