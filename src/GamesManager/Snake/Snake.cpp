#include "Snake.h"
#include "MainManager/MainManager.h"
#include <iomanip>
#include <sstream>

const std::string Snake::name = "Snake";

const std::map<Snake::Direction, Position> Snake::offsetMap = {
    {Snake::Direction::right, Position(1, 0)},
    {Snake::Direction::down, Position(0, 1)},
    {Snake::Direction::left, Position(-1, 0)},
    {Snake::Direction::up, Position(0, -1)},
};
const Color Snake::appleColor = Color::RGB(5, 2, 1);
const char32_t Snake::snakeFace = U'⍨';

Snake::Snake(Player *player)
    : player(player), mainBuffer(),
      arena(1, 2, ImageBuffer::width - 1, ImageBuffer::height - 1),
      headDirection(right),
      snakePositions({Position(arena.width() / 2, arena.height() / 2)}),
      applePosition(generateRandomPosition()), score(0), frameCounter(0)
{
}

void Snake::init() { initBuffer(); }
void Snake::tick()
{
    if (frameCounter++ < 4)
        return;
    frameCounter = 0;

    moveHead();
    if (checkCollision(headPosition()))
    {
        mainManager->removeUIController();
        return;
    }

    if (headPosition() == applePosition)
    {
        applePosition = generateRandomPosition();

        score++;
        drawScore();
    }
    else
        snakePositions.pop_back();

    drawSnake();
    mainManager->graphicsManager.show(mainBuffer);
}
void Snake::processKeypress(Keypress key)
{
    if (key.arrow)
    {
        switch (key.direction)
        {
        case Keypress::Direction::right:
            headDirection = Snake::Direction::right;
            break;
        case Keypress::Direction::down:
            headDirection = Snake::Direction::down;
            break;
        case Keypress::Direction::left:
            headDirection = Snake::Direction::left;
            break;
        case Keypress::Direction::up:
            headDirection = Snake::Direction::up;
            break;
        }
    }
}

void Snake::initBuffer()
{
    mainBuffer.drawBoxCharacter(Box(1, 1, ImageBuffer::width - 1, 2), U'-');
    mainBuffer.drawBoxCharacter(Box(1, ImageBuffer::height - 1,
                                    ImageBuffer::width - 1,
                                    ImageBuffer::height),
                                U'-');
    mainBuffer.drawBoxCharacter(Box(0, 2, 1, ImageBuffer::height - 1), U'|');
    mainBuffer.drawBoxCharacter(Box(ImageBuffer::width - 1, 2,
                                    ImageBuffer::width,
                                    ImageBuffer::height - 1),
                                U'|');

    mainBuffer.setPixel(Position(0, 1), U'+');
    mainBuffer.setPixel(Position(ImageBuffer::width - 1, 1), U'+');
    mainBuffer.setPixel(Position(0, ImageBuffer::height - 1), U'+');
    mainBuffer.setPixel(
        Position(ImageBuffer::width - 1, ImageBuffer::height - 1), U'+');

    mainBuffer.drawBoxColor(Box(0, 1, ImageBuffer::width, ImageBuffer::height),
                            Color::Grayscale(10));

    mainBuffer.writeText(Box(0, 0, ImageBuffer::width, 1), U"Snake",
                         ImageBuffer::TextAlignment::center);

    drawSnake();
    drawScore();
    mainManager->graphicsManager.show(mainBuffer);
}
void Snake::moveHead()
{
    snakePositions.push_front(headPosition() +
                              offsetMap.find(headDirection)->second);

    headColor.nextColor();
}
void Snake::drawApple()
{
    mainBuffer.setBackground(applePosition + arena.topLeft, appleColor);
}
void Snake::drawScore()
{
    std::stringstream stream;
    stream << "Score: " << std::setw(5) << score;
    mainBuffer.writeText(Box(0, 0, ImageBuffer::width, 1), stream.str(),
                         ImageBuffer::TextAlignment::right);
}
void Snake::drawSnake()
{
    mainBuffer.drawBoxCharacter(arena, U' ');
    mainBuffer.drawBoxBackground(arena, Color::DefaultBackground);

    RainbowGenerator color = headColor;
    for (auto currPos : snakePositions)
    {
        mainBuffer.setBackground(currPos + arena.topLeft, color.nextColor());
    }
    mainBuffer.setPixel(snakePositions.front() + arena.topLeft, snakeFace);

    drawApple();
}

bool Snake::checkCollision(Position pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.x >= arena.width() ||
        pos.y >= arena.height())
        return true;

    bool first = true;
    for (auto currPos : snakePositions)
    {
        if (pos == currPos && !first)
            return true;

        first = false;
    }
    return false;
}
Position Snake::generateRandomPosition()
{
    Position result(-1, -1);
    bool coliding = false;
    do
    {
        result = Position(rand() % arena.width(), rand() % arena.height());
    } while (checkCollision(result));

    return result;
}

Position &Snake::headPosition() { return snakePositions.front(); }