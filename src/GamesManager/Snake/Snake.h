#pragma once

#include "GamesManager/Game/Game.h"
#include "GraphicsManager/Color/RainbowGenerator/RainbowGenerator.h"
#include <map>
#include <queue>

class Snake : public Game
{
  private:
    enum Direction
    {
        right,
        down,
        left,
        up
    };
    static const std::map<Direction, Position> offsetMap;
    static const Color appleColor;
    static const char32_t snakeFace;

    Box arena;

    ImageBuffer mainBuffer;
    Direction headDirection;
    RainbowGenerator headColor;
    std::deque<Position> snakePositions;
    Position applePosition;
    unsigned int score;

    Player *player;

    void initBuffer();
    void moveHead();
    void drawApple();
    void drawScore();
    void drawSnake();

    Position &headPosition();

    Position generateRandomPosition();
    bool checkCollision(Position pos);

    int frameCounter;

  public:
    Snake(Player *player);
    static const std::string name;

    void init();
    void tick();
    void processKeypress(Keypress key);
};